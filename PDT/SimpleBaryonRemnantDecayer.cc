// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleBaryonRemnantDecayer class.
//

#include "SimpleBaryonRemnantDecayer.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/PDF/BeamParticleData.h"
#include "ThePEG/Repository/UseRandom.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleBaryonRemnantDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleBaryonRemnantDecayer::~SimpleBaryonRemnantDecayer() {}

bool SimpleBaryonRemnantDecayer::accept(const DecayMode &) const {
  return true;
}

bool SimpleBaryonRemnantDecayer::
canHandle(tcPDPtr particle, tcPDPtr parton) const {
  return BaryonMatcher::Check(*particle) &&
    StandardQCDPartonMatcher::Check(*parton);
}

ParticleVector SimpleBaryonRemnantDecayer::
decay(const DecayMode &, const Particle & p, Step &) const {
  ParticleVector children;
  tcRemPPtr remnant = dynamic_ptr_cast<tcRemPPtr>(&p);
  if ( !remnant ) return children;
  tRemPDPtr rpd = data(remnant);
  PVector ex = extracted(remnant);
  tPPtr particle = parent(remnant);
  if ( !particle || ex.empty() || !rpd ) return children;

  // We can't handle multiple extractions (yet)
  if ( ex.size() != 1 ) return children;

  tPPtr parton = ex[0];
  tPVector subsys = getSubSystem(particle, parton);
  tPVector subpart = subsys;

  Energy2 s = 0.0*GeV2;
  Energy2 shat = 0.0*GeV2;
  LorentzMomentum subp;
  Energy minmass = particle->nominalMass() +
    2.0*parton->nominalMass() + margin();

  while ( !subpart.empty() ) {

    subp = Utilities::sumMomentum(subpart);

    s = (remnant->momentum() + subp).m2();
    shat = subp.m2();

    if ( sqrt(s) > sqrt(shat) + minmass ) break;

    subpart.pop_back();

  }

  if ( subpart.empty() ) return children;

  const BaryonContent & bi = getBaryonInfo(particle->dataPtr());

  // Check if we are extracting a valence quark
  int iq = parton->id();
  vector<int> vflav = bi.flav;
  vector<int>::iterator v = find(vflav.begin(), vflav.end(), bi.sign*iq);
  double pval = 0.0;
  if (  v != vflav.end() ) {
    vflav.erase(v);
    tcPDFPtr pdf;
    const BeamParticleData * beamp =
      dynamic_cast<const BeamParticleData *>(&*particle->dataPtr());
    if ( beamp ) pdf = beamp->pdf();
    if ( pdf && !specialValence() ) {
      Energy2 scale = abs(parton->scale());
      double x = shat/s;
      pval = pdf->xfvx(particle->dataPtr(), parton->dataPtr(), scale, x)/
	pdf->xfx(particle->dataPtr(), parton->dataPtr(), scale, x);
    } else {
      pval = 1;
    }
  }

  Energy mr2 = 0.0*GeV2;

  while ( true ) {

    children.clear();

    if ( rndbool(pval) ) {

      // A simple valence remnant.
      int idqr = 1000*max(vflav[0], vflav[1]) +	100*min(vflav[0], vflav[1]) + 3;
      if ( vflav[0] != vflav[1] && rndbool(0.25) ) idqr -= 2;
      children.push_back(getParticleData(bi.sign*idqr)->produceParticle());
      mr2 = sqr(children[0]->mass());

    } else {
      // We haven't extracted a valence so we first divide up the baryon
      // in a quark and a diquark.
      pair<int,int> r = bi.flavsel.select(UseRandom::current());
      int iqr = r.first*bi.sign;
      int idqr = r.second*bi.sign;

      if ( iq == ParticleID::g ) {
	children.push_back(getParticleData(iqr)->produceParticle());
	children.push_back(getParticleData(idqr)->produceParticle());
      } else if ( iq*iqr > 0 ) {
	children.push_back(getParticleData(idqr)->produceParticle());
	children.push_back(flavourGenerator().getHadron
			   (getParticleData(-iq),
			    getParticleData(iqr))->produceParticle());
      } else {
	children.push_back(getParticleData(iqr)->produceParticle());
	children.push_back(flavourGenerator().getHadron
			   (getParticleData(-iq),
			    getParticleData(idqr))->produceParticle());
      }
      
      TransverseMomentum ptr = pTGenerator()->generate();
      Energy2 mt02 = children[0]->momentum().mass2() + ptr.pt2();
      Energy2 mt12 = children[1]->momentum().mass2() + ptr.pt2();
      double z = zGenerator().generate(children[1]->dataPtr(),
				       children[0]->dataPtr(), mt12);
      mr2 = mt02/(1.0 - z) + mt12/z;

      Energy mr = sqrt(mr2);

      if ( sqrt(s) <= sqrt(shat) + mr ) continue;

      children[0]->set3Momentum(static_cast<const LorentzMomentum &>
				(lightCone((1.0 - z)*mr,
					   mt02/((1.0 - z)*mr), ptr)));
      children[1]->set3Momentum(static_cast<const LorentzMomentum &>
				(lightCone(z*mr, mt12/(z*mr), -ptr)));
    }







  }

  return children;
}

const SimpleBaryonRemnantDecayer::BaryonContent &
SimpleBaryonRemnantDecayer::getBaryonInfo(tcPDPtr baryon) const {
  map<tcPDPtr,BaryonContent>::iterator it = baryonmap.find(baryon);
  if ( it != baryonmap.end() ) return it->second;
  BaryonContent & bi = baryonmap[baryon];
  int pid = baryon->id();
  bi.sign = pid < 0? -1: 1;
  bi.flav = vector<int>(3);
  bi.flav[0] = (pid = abs(pid)/10)%10;
  bi.flav[1] = (pid /= 10)%10;
  bi.flav[2] = (pid /= 10)%10;
  bi.flavsel = VSelector< pair<int,int> >();
  for ( int iq1 = 0; iq1 < 3; ++iq1 ) {
    int iq2 = (iq1 + 1)%3;
    int iq3 = (iq2 + 1)%3;
    int idq = 1000*max(bi.flav[iq2], bi.flav[iq3]) +
      100*min(bi.flav[iq2], bi.flav[iq3]) + 3;
    bi.flavsel.insert(3.0, make_pair(bi.flav[iq1], idq));
    if ( bi.flav[iq2] == bi.flav[iq3] ) continue;
    bi.flavsel.insert(1.0, make_pair(bi.flav[iq1], idq - 2));
  }
  return bi;
}


void SimpleBaryonRemnantDecayer::
persistentOutput(PersistentOStream & os) const {
  os << theZGenerator << theFlavourGenerator << theMargin << useSpecialValence;
}

void SimpleBaryonRemnantDecayer::
persistentInput(PersistentIStream & is, int) {
  is >> theZGenerator >> theFlavourGenerator >> theMargin >> useSpecialValence;
}

ClassDescription<SimpleBaryonRemnantDecayer> SimpleBaryonRemnantDecayer::initSimpleBaryonRemnantDecayer;
// Definition of the static class description member.

void SimpleBaryonRemnantDecayer::Init() {

  static ClassDocumentation<SimpleBaryonRemnantDecayer> documentation
    ("The SimpleBaryonRemnantDecayer class inherits from the RemnantDecayer "
     "class and is able to decay RemnantParticles produced by the "
     "SoftRemnantHandler class for the cases when a single parton has been "
     "extracted from a baryon.");

  static Reference<SimpleBaryonRemnantDecayer,ZGenerator> interfaceZGenerator
    ("ZGenerator",
     "The object responsible for generating momentum fractions in case "
     "of more than one remnant.",
     &SimpleBaryonRemnantDecayer::theZGenerator, false, false, true, false, true);

  static Reference<SimpleBaryonRemnantDecayer,FlavourGenerator>
    interfaceFlavourGenerator
    ("FlavourGenerator",
     "The object responsible for handling the flavour contents of a baryon.",
     &SimpleBaryonRemnantDecayer::theFlavourGenerator,
     false, false, true, false, true);

  static Parameter<SimpleBaryonRemnantDecayer,Energy> interfaceMargin
    ("EnergyMargin",
     "The energy margin (in GeV) to be added to the sum of the parent and "
     "parton masses to determine if it is possible to construct the remnants "
     "with the given (upper limit of the) virtuality of the extracted parton.",
     &SimpleBaryonRemnantDecayer::theMargin, GeV, 1.0*GeV, 0.0*GeV, 10.0*GeV,
     false, false, true);

  static Switch<SimpleBaryonRemnantDecayer,bool> interfaceSpecialValence
    ("SpecialValence",
     "If true, an extracted valence quark will always give a di-quark remnant.",
     &SimpleBaryonRemnantDecayer::useSpecialValence, false, true, false);
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

  interfaceZGenerator.rank(8);
  interfaceFlavourGenerator.rank(7);

}

