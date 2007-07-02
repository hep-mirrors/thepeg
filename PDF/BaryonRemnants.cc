// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BaryonRemnants class.
//

#include "BaryonRemnants.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/PDF/PDFBase.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/VSelector.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Repository/UseRandom.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BaryonRemnants.tcc"
#endif

using namespace ThePEG;

BaryonRemnants::BaryonRemnants()
  : theMargin(1.0*GeV), useSpecialValence(false) {}

BaryonRemnants::BaryonRemnants(const BaryonRemnants & x)
  : RemnantHandler(x), thePtGeneratorQ(x.thePtGeneratorQ),
    thePtGeneratorR(x.thePtGeneratorR), theZGenerator(x.theZGenerator),
    theFlavourGenerator(x.theFlavourGenerator), theMargin(x.theMargin),
    useSpecialValence(x.useSpecialValence) {}

BaryonRemnants::~BaryonRemnants() {}

void BaryonRemnants::doinit() throw(InitException) {
  RemnantHandler::doinit();
}

bool BaryonRemnants::
canHandle(tcPDPtr particle, const cPDVector & partons) const {
  if ( !BaryonMatcher::Check(*particle) ) return false;
  for ( int i = 0, N = partons.size(); i < N; ++i )
    if ( !StandardQCDPartonMatcher::Check(*partons[i]) ) return false;
  return true;
}

Lorentz5Momentum BaryonRemnants::
generate(PartonBinInstance & pb, const double *,
	 Energy2 scale, const LorentzMomentum & parent) const {
  Timer<16> timer("BaryonRemnants::generate(...)");
  LorentzMomentum p(0.0*GeV, 0.0*GeV, parent.rho(), parent.e());

  double x = pb.xi();
  double eps = pb.eps();
  Energy2 smax = (parent.m2()*x*eps + eps*max(abs(scale), parent.m2()))/x;
  if ( smax < sqr(pb.particle()->nominalMass() +
		  2.0*pb.parton()->nominalMass() + margin()) ) {
    pb.remnantWeight(0.0);
    return parent;
  }
 
  Timer<17> timera("BaryonRemnants::generate(...):accepted");
  PVector rem;
  rem.reserve(2);

  typedef Ptr<BaryonRemInfo>::pointer BRemIPtr;

  BRemIPtr ip;
  if ( !(ip = dynamic_ptr_cast<BRemIPtr>(pb.remnantInfo())) ) {
    // If this is the first time for this parton bin, generate some
    // information to save.
    ip = new_ptr(BaryonRemInfo());
    pb.remnantInfo(ip);
    BaryonRemInfo & i = *ip;

    // Get the extracted flavour.
    i.iq = pb.partonData()->id();
    int pid = pb.particleData()->id();
    i.sign = pid < 0? -1: 1;

    // Get all valence flavours and check if extracted parton may be
    // valens.
    i.flav = i.vflav = vector<int>(3);
    i.flav[0] = i.vflav[0] = (pid = abs(pid)/10)%10;
    i.flav[1] = i.vflav[1] = (pid /= 10)%10;
    i.flav[2] = i.vflav[2] = (pid /= 10)%10;
    vector<int>::iterator v = find(i.vflav.begin(), i.vflav.end(), i.sign*i.iq);
    if ( v != i.vflav.end() ) {
      i.vflav.erase(v);
      i.mayval = true;
    } else {
      i.mayval = false;
    }

    // Weight possible combinations of valens quarks.
    for ( int iq1 = 0; iq1 < 3; ++iq1 ) {
      int iq2 = (iq1 + 1)%3;
      int iq3 = (iq2 + 1)%3;
      int idq = 1000*max(i.flav[iq2], i.flav[iq3]) +
	100*min(i.flav[iq2], i.flav[iq3]) + 3;
      i.flavsel.insert(3.0, make_pair(i.flav[iq1], idq));
      if ( i.flav[iq2] == i.flav[iq3] ) continue;
      i.flavsel.insert(1.0, make_pair(i.flav[iq1], idq - 2));
    }
  }
  BaryonRemInfo & i = *ip;

  Timer<19> timerc("BaryonRemnants::generate(...):loop");

  while ( true ) {

    rem.clear();
    Energy2 s = 0.0*GeV2;


    // If the extracted quark was a valence quark simply return a di-quark.

    if ( i.mayval &&
	 rndbool(pb.pdf()->xfvl(pb.particleData(), pb.partonData(),
				abs(pb.scale()), pb.li()),
		 pb.pdf()->xfl(pb.particleData(), pb.partonData(),
			       abs(pb.scale()), pb.li())) ) {
      int idqr = 1000*max(i.vflav[0], i.vflav[1]) +
	100*min(i.vflav[0], i.vflav[1]) + 3;
      if ( i.vflav[0] != i.vflav[1] && rnd() < 0.25 ) idqr -= 2;
      rem.push_back(getParticleData(i.sign*idqr)->produceParticle());
      s = sqr(rem[0]->mass());
    } else {
      // We haven't extracted a valence so we first divide up the baryon
      // in a quark and a diquark.
      pair<int,int> r = i.flavsel.select(UseRandom::current());
      int iqr = r.first*i.sign;
      int idqr = r.second*i.sign;

      if ( i.iq == ParticleID::g ) {
	rem.push_back(getParticleData(iqr)->produceParticle());
	rem.push_back(getParticleData(idqr)->produceParticle());
      } else if ( i.iq*iqr > 0 ) {
	rem.push_back(getParticleData(idqr)->produceParticle());
	rem.push_back(flavourGenerator().getHadron
		      (getParticleData(-i.iq),
		       getParticleData(iqr))->produceParticle());
      } else {
	rem.push_back(getParticleData(iqr)->produceParticle());
	rem.push_back(flavourGenerator().getHadron
		      (getParticleData(-i.iq),
		       getParticleData(idqr))->produceParticle());
      }
      TransverseMomentum ptr = ptGeneratorR().generate();
      Energy2 mt02 = rem[0]->momentum().mass2() + ptr.pt2();
      Energy2 mt12 = rem[1]->momentum().mass2() + ptr.pt2();
      double z = zGenerator().generate(rem[1]->dataPtr(),
				       rem[0]->dataPtr(), mt12);
      s = mt02/(1.0 - z) + mt12/z;
      Energy W = sqrt(s);
      rem[0]->set3Momentum(static_cast<const LorentzMomentum &>
			   (lightCone((1.0 - z)*W, mt02/((1.0 - z)*W), ptr)));
      rem[1]->set3Momentum(static_cast<const LorentzMomentum &>
			   (lightCone(z*W, mt12/(z*W), -ptr)));
    }

    TransverseMomentum kt;
   
    if ( scale <= 0.0*GeV2 ) {
      kt = ptGeneratorQ().generate();
      if ( kt.pt2() > smax*x - s*x ) continue;
    } else {
      Energy2 kt2 = parent.m2()*x*eps - s*x + eps*scale;
      double phi = rnd(2.0*Constants::pi);
      kt = TransverseMomentum(sqrt(kt2)*cos(phi), sqrt(kt2)*sin(phi));
    }

    pb.remnants(rem);

    p = lightCone(x*p.plus(), p.minus() - (s + kt.pt2())/(eps*p.plus()), kt);
    p.rotateY(parent.theta());
    p.rotateZ(parent.phi());
	      
    return p;
  }
}

Lorentz5Momentum BaryonRemnants::
generate(PartonBinInstance & pb, const double *, Energy2 scale,
	 Energy2 shat, const LorentzMomentum & parent) const {
  Timer<16> timer("BaryonRemnants::generate(...)");
  LorentzMomentum p(0.0*GeV, 0.0*GeV, parent.rho(), parent.e());

  double x = pb.xi();
  double eps = pb.eps();
  Energy2 stot = shat/x;
  Energy mrmax = sqrt(stot) - sqrt(shat);
  if ( scale > 0.0*GeV2 )
    mrmax = sqrt((parent.m2()*x*eps + eps*max(abs(scale), parent.m2()))/x);
  if ( mrmax < pb.particle()->nominalMass() +
               2.0*pb.parton()->nominalMass() + margin() ) {
    pb.remnantWeight(0.0);
    return parent;
  }
 
  Timer<17> timera("BaryonRemnants::generate(...):accepted");
  PVector rem;
  rem.reserve(2);

  typedef Ptr<BaryonRemInfo>::pointer BRemIPtr;

  BRemIPtr ip;
  if ( !(ip = dynamic_ptr_cast<BRemIPtr>(pb.remnantInfo())) ) {
    // If this is the first time for this parton bin, generate some
    // information to save.
    ip = new_ptr(BaryonRemInfo());
    pb.remnantInfo(ip);
    BaryonRemInfo & i = *ip;

    // Get the extracted flavour.
    i.iq = pb.partonData()->id();
    int pid = pb.particleData()->id();
    i.sign = pid < 0? -1: 1;

    // Get all valence flavours and check if extracted parton may be
    // valens.
    i.flav = i.vflav = vector<int>(3);
    i.flav[0] = i.vflav[0] = (pid = abs(pid)/10)%10;
    i.flav[1] = i.vflav[1] = (pid /= 10)%10;
    i.flav[2] = i.vflav[2] = (pid /= 10)%10;
    vector<int>::iterator v = find(i.vflav.begin(), i.vflav.end(), i.sign*i.iq);
    if ( v != i.vflav.end() ) {
      i.vflav.erase(v);
      i.mayval = true;
    } else {
      i.mayval = false;
    }

    // Weight possible combinations of valens quarks.
    for ( int iq1 = 0; iq1 < 3; ++iq1 ) {
      int iq2 = (iq1 + 1)%3;
      int iq3 = (iq2 + 1)%3;
      int idq = 1000*max(i.flav[iq2], i.flav[iq3]) +
	100*min(i.flav[iq2], i.flav[iq3]) + 3;
      i.flavsel.insert(3.0, make_pair(i.flav[iq1], idq));
      if ( i.flav[iq2] == i.flav[iq3] ) continue;
      i.flavsel.insert(1.0, make_pair(i.flav[iq1], idq - 2));
    }
  }
  BaryonRemInfo & i = *ip;

  Timer<19> timerc("BaryonRemnants::generate(...):loop");

  while ( true ) {

    rem.clear();
    Energy2 s = 0.0*GeV2;


    // If the extracted quark was a valence quark simply return a di-quark.

    if ( i.mayval && ( specialValence() ||
	 rndbool(pb.pdf()->xfvl(pb.particleData(), pb.partonData(),
				abs(pb.scale()), pb.li()),
		 pb.pdf()->xfl(pb.particleData(), pb.partonData(),
			       abs(pb.scale()), pb.li())) ) ) {
      int idqr = 1000*max(i.vflav[0], i.vflav[1]) +
	100*min(i.vflav[0], i.vflav[1]) + 3;
      if ( i.vflav[0] != i.vflav[1] && rnd() < 0.25 ) idqr -= 2;
      rem.push_back(getParticleData(i.sign*idqr)->produceParticle());
      s = sqr(rem[0]->mass());
    } else {
      // We haven't extracted a valence so we first divide up the baryon
      // in a quark and a diquark.
      pair<int,int> r = i.flavsel.select(UseRandom::current());
      int iqr = r.first*i.sign;
      int idqr = r.second*i.sign;

      if ( i.iq == ParticleID::g ) {
	rem.push_back(getParticleData(iqr)->produceParticle());
	rem.push_back(getParticleData(idqr)->produceParticle());
      } else if ( i.iq*iqr > 0 ) {
	rem.push_back(getParticleData(idqr)->produceParticle());
	rem.push_back(flavourGenerator().getHadron
		      (getParticleData(-i.iq),
		       getParticleData(iqr))->produceParticle());
      } else {
	rem.push_back(getParticleData(iqr)->produceParticle());
	rem.push_back(flavourGenerator().getHadron
		      (getParticleData(-i.iq),
		       getParticleData(idqr))->produceParticle());
      }
      TransverseMomentum ptr = ptGeneratorR().generate();
      Energy2 mt02 = rem[0]->momentum().mass2() + ptr.pt2();
      Energy2 mt12 = rem[1]->momentum().mass2() + ptr.pt2();
      double z = zGenerator().generate(rem[1]->dataPtr(),
				       rem[0]->dataPtr(), mt12);
      s = mt02/(1.0 - z) + mt12/z;
      Energy W = sqrt(s);
      if ( W > mrmax ) continue;
      rem[0]->set3Momentum(static_cast<const LorentzMomentum &>
			   (lightCone((1.0 - z)*W, mt02/((1.0 - z)*W), ptr)));
      rem[1]->set3Momentum(static_cast<const LorentzMomentum &>
			   (lightCone(z*W, mt12/(z*W), -ptr)));
    }

    // calculate the total longitudinal momentum available for the
    // remnat in the rest system together with the hard sub-system.
    Energy pz =  SimplePhaseSpace::getMagnitude(stot, sqrt(shat), sqrt(s));

    TransverseMomentum kt;
   
    if ( scale <= 0.0*GeV2 ) {
      kt = ptGeneratorQ().generate();
      //      if ( kt.pt2() > smax*x - s*x ) continue;
    } else {
      Energy2 kt2 = parent.m2()*x*eps - s*x + eps*scale;
      double phi = rnd(2.0*Constants::pi);
      kt = TransverseMomentum(sqrt(kt2)*cos(phi), sqrt(kt2)*sin(phi));
    }
    if ( kt.pt() >= pz ) continue;

    pb.remnants(rem);

    p = lightCone(x*p.plus(), p.minus() - (s + kt.pt2())/(eps*p.plus()), kt);
    p.rotateY(parent.theta());
    p.rotateZ(parent.phi());
	      
    return p;
  }
}

void BaryonRemnants::boostRemnants(PartonBinInstance & pb) const {
  const LorentzMomentum pr =
    pb.particle()->momentum() - pb.parton()->momentum();
  const PVector & rem = pb.remnants();
  Energy2 s = Utilities::sumMomentum(rem).m2();
  Utilities::setMomentumFromCMS(rem.begin(), rem.end(), s, pr);
  for ( int i = 0, N = rem.size(); i < N; ++i )
    rem[i]->scale(pb.particle()->momentum().mass2());
}

bool BaryonRemnants::defaultInit() {
  if ( !setDefaultReference(thePtGeneratorQ, "ThePEG::GaussianPtGenerator",
			    "PtGenerator") ) return false;
  if ( !setDefaultReference(theZGenerator, "ThePEG::SimpleZGenerator",
			    "ZGenerator") ) return false;
  if ( !setDefaultReference(theFlavourGenerator, "ThePEG::SimpleFlavour",
			    "FlavourGenerator") ) return false;
  return true;
}

void BaryonRemnants::persistentOutput(PersistentOStream & os) const {
  os << thePtGeneratorQ << thePtGeneratorR << theZGenerator
     << theFlavourGenerator << ounit(theMargin,GeV) << useSpecialValence;
}

void BaryonRemnants::persistentInput(PersistentIStream & is, int) {
  is >> thePtGeneratorQ >> thePtGeneratorR >> theZGenerator
     >> theFlavourGenerator >> iunit(theMargin,GeV) >> useSpecialValence;
}

ClassDescription<BaryonRemnants>
BaryonRemnants::initBaryonRemnants;

void BaryonRemnants::Init() {

  static ClassDocumentation<BaryonRemnants> documentation
    ("There is no documentation for the ThePEG::BaryonRemnants class");

  static Reference<BaryonRemnants,PtGenerator> interfacePtGeneratorQ
    ("PtGeneratorQ",
     "The object responsible generating the primordial \\f$p_\\perp\\f$ "
     "of the struc quark.",
     &BaryonRemnants::thePtGeneratorQ, false, false, true, false, true);

  static Reference<BaryonRemnants,PtGenerator> interfacePtGeneratorR
    ("PtGeneratorR",
     "The object responsible generating the primordial \\f$p_\\perp\\f$ "
     "among the remnants. Of no object is specified, the PtGeneratorQ is "
     "used instead.",
     &BaryonRemnants::thePtGeneratorR, false, false, true, true, false);

  static Reference<BaryonRemnants,ZGenerator> interfaceZGenerator
    ("ZGenerator",
     "The object responsible for generating momentum fractions in case "
     "of more than one remnant.",
     &BaryonRemnants::theZGenerator, false, false, true, false, true);

  static Reference<BaryonRemnants,FlavourGenerator> interfaceFlavourGenerator
    ("FlavourGenerator",
     "The object responsible for handling the flavour contents of a baryon.",
     &BaryonRemnants::theFlavourGenerator, false, false, true, false, true);

  static Parameter<BaryonRemnants,Energy> interfaceMargin
    ("EnergyMargin",
     "The energy margin (in GeV) to be added to the sum of the parent and "
     "parton masses to determine if it is possible to construct the remnants "
     "with the given (upper limit of the) virtuality of the extracted parton.",
     &BaryonRemnants::theMargin, GeV, 1.0*GeV, 0.0*GeV, 10.0*GeV,
     false, false, true);

  static Switch<BaryonRemnants,bool> interfaceSpecialValence
    ("SpecialValence",
     "If true, an extracted valence quark will always give a di-quark remnant.",
     &BaryonRemnants::useSpecialValence, false, true, false);
  static SwitchOption interfaceSpecialValenceYes
    (interfaceSpecialValence,
     "Yes",
     "An extracted valence quark will always give a di-quark remnant.",
     true);
  static SwitchOption interfaceSpecialValenceNo
    (interfaceSpecialValence,
     "No",
     "An extracted valence flavour may be considered to be a sea-quark.",
     false);

  interfacePtGeneratorQ.rank(10);
  interfacePtGeneratorR.rank(9);
  interfaceZGenerator.rank(8);
  interfaceFlavourGenerator.rank(7);

}

