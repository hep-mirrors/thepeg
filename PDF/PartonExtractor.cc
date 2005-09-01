// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PartonExtractor class.
//

#include "PartonExtractor.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/KinematicalCuts.h"
#include "ThePEG/PDF/NoPDF.h"
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/PDF/BeamParticleData.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/Step.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonExtractor.tcc"
#endif

using namespace ThePEG;

PartonExtractor::PartonExtractor()
  : theMaxTries(100), flatSHatY(false) {}

PartonExtractor::PartonExtractor(const PartonExtractor & x)
  : HandlerBase(x), LastXCombInfo<>(x),
    partonBinInstances(x.partonBinInstances),
    theSpecialDensities(x.theSpecialDensities), theNoPDF(x.theNoPDF),
    theMaxTries(x.theMaxTries), flatSHatY(x.flatSHatY) {}


PartonExtractor::~PartonExtractor() {}

void PartonExtractor::doinit() throw(InitException) {
  HandlerBase::doinit();
}

PartonPairVec PartonExtractor::
getPartons(Energy maxEnergy, const cPDPair & incoming,
	   const KinematicalCuts & kc) const {
  PartonPairVec result;
  PartonVector first;
  PDFCuts cuts1(kc, true, maxEnergy);
  PBPtr p1 =
    new_ptr(PartonBin(PDPtr(), PBPtr(), incoming.first, PDFPtr(), cuts1));
  addPartons(p1, cuts1, first);
  PartonVector second;
  PDFCuts cuts2(kc, false, maxEnergy);
  PBPtr p2 =
    new_ptr(PartonBin(PDPtr(), PBPtr(), incoming.second, PDFPtr(), cuts2));
  addPartons(p2, cuts2, second);
  for ( PartonVector::iterator it1 = first.begin();
	it1 != first.end(); ++it1 )
    for ( PartonVector::iterator it2 = second.begin();
	it2 != second.end(); ++it2 )
      result.push_back(PBPair(*it1, *it2));

  // We add the original parton bins as well to avoid them being
  // deleted.
  result.push_back(PBPair(p1, p2));
  return result;
}

void PartonExtractor::
addPartons(tPBPtr incoming, const PDFCuts & cuts, PartonVector & pbins) const {
  tcPDFPtr pdf = getPDF(incoming->parton());
  if ( dynamic_ptr_cast<Ptr<NoPDF>::tcp>(pdf) ||
       incoming->parton() == incoming->particle() ) {
    pbins.push_back(incoming);
    return;
  }
  cPDVector partons = pdf->partons(incoming->parton());
  for ( int i = 0, N = partons.size(); i < N; ++i ) {
    PBPtr pb =
      new_ptr(PartonBin(incoming->parton(), incoming, partons[i], pdf, cuts));
    incoming->addOutgoing(pb);
    addPartons(pb, cuts, pbins);
  }

}

tcPDFPtr PartonExtractor::getPDF(tcPDPtr particle) const {
  for ( vector<PDFPtr>::const_iterator it = theSpecialDensities.begin();
	it != theSpecialDensities.end(); ++it )
    if ( (**it).canHandle(particle) ) return *it;
  Ptr<BeamParticleData>::tcp p = 
    dynamic_ptr_cast<Ptr<BeamParticleData>::tcp>(particle);
  if ( !p || !p->pdf() ) return noPDF();
  return p->pdf();
}

void PartonExtractor::
select(tXCombPtr newXComb) {
  theLastXComb = newXComb;
}

tPBIPtr PartonExtractor::partonBinInstance(tcPPtr p) const {
  PartonBinInstanceMap::const_iterator it = partonBinInstances.find(p);
  return it == partonBinInstances.end()? PBIPtr(): it->second;
}

void PartonExtractor::
colourConnect(tPPtr particle, tPPtr parton, const tPVector & remnants) const {

  // Sorry cannot handle coloured resolved particles.
  if ( particle->coloured() ) throw RemColException(*this);

  // First connect the loose colour line from the extacted parton.
  if ( parton->hasColour() )
    findConnect(parton->colourLine(), parton, true,
		remnants.rbegin(), remnants.rend());

  // First connect the loose anti-colour line from the extacted parton.
  if ( parton->hasAntiColour() )
    findConnect(parton->antiColourLine(), parton, false,
		remnants.begin(), remnants.end());

  // Go through the rest of the remnants and create new colour lines
  // if needed. Go through it forwards and backwards to catch possible
  // inconsistencies.
  for ( tPVector::const_iterator it = remnants.begin();
	it != remnants.end(); ++it ) {
    if ( (**it).hasAntiColour() && !(**it).antiColourLine() )
      findConnect(ColourLine::create(*it, true), *it, false,
		it + 1, remnants.end());
  }
  for ( tPVector::const_reverse_iterator it = remnants.rbegin();
	it != remnants.rend(); ++it ) {
    if ( (**it).hasColour() && !(**it).colourLine() )
      findConnect(ColourLine::create(*it), *it, true, it + 1, remnants.rend());
  } 
}

Energy2 PartonExtractor::newScale() {
  return lastScale();
}

pair<int,int> PartonExtractor::nDims(const PBPair & pbins) {
  return make_pair(pbins.first->nDim(false), pbins.second->nDim(false));
}

void PartonExtractor::prepare(const PBIPair & pbins) {
  partonBinInstances.clear();
  pbins.first->prepare();
  pbins.second->prepare();
}

bool PartonExtractor::
generateL(const PBIPair & pbins, const double * r1, const double * r2) {
  Direction<0> dir(true);
  generateL(*pbins.first, r1);
  dir.reverse();
  generateL(*pbins.second, r2);
  if ( !flatSHatY ) return true;

  Energy2 shmax = lastCuts().sHatMax();
  shmax = min(shmax, lastCuts().x1Max()*lastCuts().x2Max()*lastS());
  Energy2 shmin = lastCuts().sHatMin();
  shmin = max(shmin, lastCuts().tHatMin());
  shmin = max(shmin, lastCuts().uHatMin());
  shmin = max(shmin, sqr(2.0*lastCuts().pTHatMin()));
  shmin = max(shmin, lastCuts().x1Min()*lastCuts().x2Min()*lastS());
  Energy2 sh = shmin*pow(shmax/shmin, *r1);
  double ymax = lastCuts().yStarMax();
  double ymin = lastCuts().yStarMin();
  ymax = min(ymax, 0.5*log(lastCuts().x1Max()/lastCuts().x2Min()));
  ymin = max(ymin, 0.5*log(lastCuts().x1Min()/lastCuts().x2Max()));
  double km = log(shmax/shmin);
  ymax = min(ymax, log(lastCuts().x1Max()*sqrt(lastS()/sh)));
  ymin = max(ymin, -log(lastCuts().x2Max()*sqrt(lastS()/sh)));

  double y = ymin + (*r2)*(ymax - ymin);
  double l1 = 0.5*log(lastS()/sh) - y;
  double l2 = 0.5*log(lastS()/sh) + y;

  pbins.first->li(l1 - pbins.first->l() + pbins.first->li());
  pbins.first->l(l1);
  pbins.first->jacobian(km*(ymax - ymin));
  pbins.second->li(l2 - pbins.second->l() + pbins.second->li());
  pbins.second->l(l2);
  pbins.second->jacobian(1.0);
  return ( pbins.first->li() >= 0.0 && pbins.second->li() >= 0.0 );
}

Energy2 PartonExtractor::
generateSHat(Energy2 s, const PBIPair & pbins,
	     const double * r1, const double * r2) {

  Direction<0> dir(true);
  pbins.first->scale(-lastScale());
  if ( !generate(*pbins.first, r1, lastSHat(),
		 pbins.first->getFirst()->parton()->momentum()) )
    return -1.0*GeV2;
  dir.reverse();
  pbins.second->scale(-lastScale());
  if ( !generate(*pbins.second, r2, lastSHat(),
		 pbins.second->getFirst()->parton()->momentum()) )
    return -1.0*GeV2;
  
  return (pbins.first->parton()->momentum() +
	  pbins.second->parton()->momentum()).m2();
}

void PartonExtractor::
generateL(PartonBinInstance & pb, const double * r) {
  if ( !pb.incoming() ) return;

  pb.parton(pb.partonData()->produceParticle(Lorentz5Momentum()));
  generateL(*pb.incoming(), r + pb.bin()->pdfDim() + pb.bin()->remDim());
  pb.particle(pb.incoming()->parton());
  if ( pb.li() >= 0 ) return;
  double jac = 1.0;
  if ( pb.bin()->pdfDim() )
    pb.li(pb.pdf()->flattenL(pb.particleData(), pb.partonData(),
				       pb.bin()->cuts(), *r++, jac));
  pb.scale(-1.0*GeV2);
  if ( pb.bin()->pdfDim() > 1 )
    pb.scale(pb.pdf()->flattenScale(pb.particleData(), pb.partonData(),
				    pb.bin()->cuts(), pb.li(), *r++, jac));
  pb.jacobian(jac);
  pb.l(pb.incoming()->l() + pb.li());
}

bool PartonExtractor::
generate(PartonBinInstance & pb, const double * r,
	 Energy2 shat, const Lorentz5Momentum & first) {
  if ( !pb.incoming() ) return true;
  if ( !generate(*pb.incoming(), r + pb.bin()->pdfDim() + pb.bin()->remDim(),
		 shat/pb.xi(), first) )
    return false;;
  pb.remnantWeight(1.0);
  pb.parton()->setMomentum
    (pb.remnantHandler()->generate(pb, r, pb.scale(), shat,
				   pb.particle()->momentum()));
  if ( pb.remnantWeight() <= 0.0 ) return false;
  partonBinInstances[pb.parton()] = &pb;
  return true;
}

void PartonExtractor::
constructRemnants(const PBIPair & pbins, tSubProPtr sub, tStepPtr step) const {
  partonBinInstances.clear();
  LorentzMomentum k1 = pbins.first->parton()->momentum();
  LorentzMomentum k2 = pbins.second->parton()->momentum();
  LorentzMomentum Ph = k1 + k2;
  LorentzMomentum Phold = Ph;

  bool pickside = rndbool();
  if ( pickside && pbins.first->incoming() ) {
    Direction<0> dir(true);
    constructRemnants(*pbins.first, Ph, k2);
    construct(*pbins.first, step);
  }
  if ( pbins.second->incoming() ) {
    Direction<0> dir(false);
    constructRemnants(*pbins.second, Ph, pbins.first->parton()->momentum());
    construct(*pbins.second, step);
  }
  if ( (!pickside) && pbins.first->incoming() ) {
    Direction<0> dir(true);
    constructRemnants(*pbins.first, Ph, pbins.second->parton()->momentum());
    construct(*pbins.first, step);
  }
  LorentzRotation rot = Utilities::transformToMomentum(Phold, Ph);
  Utilities::transform(sub->outgoing(), rot);
  Utilities::transform(sub->intermediates(), rot);
  k1 = pbins.first->parton()->momentum();
  k2 = pbins.second->parton()->momentum();
  Ph = k1 + k2;
  if ( abs(Ph.m2() - Phold.m2())/Phold.m2() > 0.000001 )
    cerr << Ph.m2()/GeV2 << " was (" << Phold.m2()/GeV2 << ")" << endl;
}

void PartonExtractor::
constructRemnants(PartonBinInstance & pb, LorentzMomentum & Ph,
		  const LorentzMomentum & k) const {
  LorentzMomentum P = pb.particle()->momentum();
  DVector r = UseRandom::rndvec(pb.bin()->remDim());
  pb.remnantHandler()->generate(pb, &r[0], pb.scale(), Ph.m2(), P);
  pb.remnantHandler()->createRemnants(pb);
  LorentzMomentum Pr = Utilities::sumMomentum(pb.remnants());
  transformRemnants(Ph, Pr, k, pb.particle()->momentum());
  pb.parton()->setMomentum(pb.particle()->momentum() - Pr);
  Utilities::setMomentum(pb.remnants().begin(),
			 pb.remnants().end(),
			 (const LorentzMomentum &)Pr);
  partonBinInstances[pb.parton()] = &pb;
  if ( !pb.incoming()->incoming() ) return;

  // We get here if we need to construct remnants recursively.
  LorentzMomentum Phnew = Ph + Pr;
  constructRemnants(*pb.incoming(), Phnew, k);
  LorentzRotation rot = Utilities::transformToMomentum(Ph + Pr, Phnew);
  Utilities::transform(pb.remnants(), rot);
  Ph.transform(rot);
}

LorentzRotation PartonExtractor::
boostRemnants(PBIPair & bins, LorentzMomentum k1, LorentzMomentum k2,
	 bool side1, bool side2) const {
  if ( !side1 && !side2 ) return LorentzRotation();

  LorentzMomentum P1 = bins.first->parton()->momentum();
  LorentzMomentum Pr1;
  if ( side1 ) {
    P1 = bins.first->particle()->momentum();
    Pr1 = Utilities::sumMomentum(bins.first->remnants());
  }
  LorentzMomentum P2 = bins.second->parton()->momentum();
  LorentzMomentum Pr2;
  if ( side2 ) {
    P2 = bins.second->particle()->momentum();
    Pr2 = Utilities::sumMomentum(bins.second->remnants());
  }
  LorentzMomentum Ph = k1 + k2;
  LorentzMomentum Phold = Ph;

  bool otherside = rndbool();
  if ( otherside && side2 ){
    Direction<0> dir(false);
    transformRemnants(Ph, Pr2, k1, P2);
    k2 = P2 - Pr2;
  }
  if ( side1 ){
    Direction<0> dir(true);
    transformRemnants(Ph, Pr1, k2, P1);
    k1 = P1 - Pr1;
  }
  if ( side2 && !otherside ) {
    Direction<0> dir(false);
    transformRemnants(Ph, Pr2, k1, P2);
    k2 = P2 - Pr2;
  }
  Utilities::setMomentum(bins.first->remnants().begin(),
			 bins.first->remnants().end(),
			 (const LorentzMomentum &)Pr1);
  bins.second->parton()->setMomentum(k1);
  Utilities::setMomentum(bins.second->remnants().begin(),
			 bins.second->remnants().end(),
			 (const LorentzMomentum &)Pr2);
  bins.second->parton()->setMomentum(k2);

  return Utilities::transformToMomentum(Phold, Ph);

}

void PartonExtractor::
transformRemnants(LorentzMomentum & Ph, LorentzMomentum & Pr,
		  const LorentzMomentum & k, const LorentzMomentum & P) const {
  TransverseMomentum pt = Pr;
  try {
    if ( Direction<0>::pos() )
      SimplePhaseSpace::CMS(Pr, Ph, (P + k).m2(), 1.0, 0.0);
    else
      SimplePhaseSpace::CMS(Ph, Pr, (k + P).m2(), 1.0, 0.0);
    LorentzRotation rpt;
    if ( sqr(Pr.z()) > 0.0*GeV2 ) rpt.rotateY(asin(pt.pt()/Pr.z()));
    rpt.rotateZ(pt.phi());
    rpt = Direction<0>::pos()?
      Utilities::getBoostFromCM(make_pair(P, k))*rpt:
      Utilities::getBoostFromCM(make_pair(k, P))*rpt;
    Ph.transform(rpt);
    Pr.transform(rpt);
  } catch ( ImpossibleKinematics ) {}
}


double PartonExtractor::fullFn(const PBIPair & pbins, Energy2 scale) {
  pbins.first->scale(scale);
  pbins.second->scale(scale);
  return fullFn(*pbins.first)*fullFn(*pbins.second);
}

double PartonExtractor::fullFn(const PartonBinInstance & pb) {
  if ( !pb.incoming() ) return 1.0;
  return fullFn(*pb.incoming()) * pb.jacobian() * pb.remnantWeight() *
    pb.pdf()->xfl(pb.particleData(), pb.partonData(), pb.scale(),
		  pb.li(), pb.incoming()->scale());
}

void PartonExtractor::
construct(const PBIPair & pbins, tStepPtr step) const {
  Direction<0> dir(true);
  construct(*pbins.first, step);
  dir.reverse();
  construct(*pbins.second, step);
}

void PartonExtractor::
construct(PartonBinInstance & pb, tStepPtr step) const {
  if ( !pb.incoming() ) return;
  if ( pb.remnants().empty() ) pb.remnantHandler()->createRemnants(pb);
  tPVector rem(pb.remnants().begin(), pb.remnants().end());
  if ( !step->addDecayProduct(pb.particle(), rem.begin(), rem.end(), false) );
  colourConnect(pb.particle(), pb.parton(), rem);
  if ( pb.incoming()->incoming() ) step->addIntermediate(pb.particle());
  construct(*pb.incoming(), step);
}

PBIPair PartonExtractor::newRemnants(tPPair oldp, tPPair newp, tStepPtr step) {
  PBIPair pb;
  Direction<0> dir(true);
  pb.first = newRemnants(partonBinInstance(oldp.first),
			 newp.first, newp.second->momentum());
  dir.reverse();
  pb.second = newRemnants(partonBinInstance(oldp.second),
			  newp.second, newp.first->momentum());
  addNewRemnants(partonBinInstance(oldp.first), pb.first, step);
  addNewRemnants(partonBinInstance(oldp.second), pb.second, step);
  return pb;
}

PBIPtr PartonExtractor::
newRemnants(tPBIPtr oldpb, tPPtr newp, const LorentzMomentum & k) {
  if ( ! oldpb || !oldpb->incoming() ) return oldpb;
  Energy2 shat = (k + newp->momentum()).m2();

  // Loop over all possible PartonBin sisters to find the one
  // corresponding to the newly extracted parton.
  const PartonBin::PBVector & sisters = oldpb->incoming()->bin()->outgoing();
  for ( int i = 0, N = sisters.size(); i < N; ++i )
    if ( sisters[i]->parton() == newp->dataPtr() ) {
      // Setup necessary info in new PartonBinInstance object.
      PBIPtr newpb = new_ptr(PartonBinInstance(sisters[i], oldpb->incoming()));
      newpb->particle(oldpb->particle());
      newpb->parton(newp);
      newpb->li(log(oldpb->particle()->momentum().dirPlus()/
		    newp->momentum().dirPlus()));
      newpb->l(oldpb->l() - oldpb->li() + newpb->li());
      Energy2 sc = -newp->scale();
      newpb->scale(newp->scale());
      if ( oldpb->incoming()->incoming() )
	sc = -newpb->particle()->momentum().m2();
      // Now we can construct the new remnants.
      newpb->remnantWeight(1.0);
      if ( !newpb->remnantHandler()->
	   recreateRemnants(*newpb, oldpb->parton(), newp, newpb->li(),
			    sc, shat, newpb->particle()->momentum()) )
	throw Veto();
      if ( newpb->remnantWeight() <= 0.0 ) throw Veto();
      return newpb;
    }
  throw Veto();
  return PBIPtr();
}

void PartonExtractor::
addNewRemnants(tPBIPtr oldpb, tPBIPtr newpb, tStepPtr step) {
  if ( oldpb == newpb ) return;
  if ( oldpb->parton() != newpb->parton() ) {
    step->removeDecayProduct(newpb->particle(), oldpb->parton());
    if ( !step->addDecayProduct(newpb->particle(), newpb->parton()) )
      throw Veto();
  }
  tPVector rem(newpb->remnants().begin(), newpb->remnants().end());
  step->removeDecayProduct(newpb->particle(), oldpb->remnants().begin(),
			   oldpb->remnants().end());
  if ( !step->addDecayProduct(newpb->particle(),
			      rem.begin(), rem.end(), false) )
    throw Veto();
  colourConnect(newpb->particle(), newpb->parton(), rem);
  partonBinInstances[newpb->parton()] = newpb;
}

void PartonExtractor::persistentOutput(PersistentOStream & os) const {
  os << theLastXComb << theSpecialDensities << theNoPDF << theMaxTries
     << flatSHatY;
}

void PartonExtractor::persistentInput(PersistentIStream & is, int) {
  is >> theLastXComb >> theSpecialDensities >> theNoPDF >> theMaxTries
     >> flatSHatY;
}

ClassDescription<PartonExtractor> PartonExtractor::initPartonExtractor;

void PartonExtractor::Init() {

  static ClassDocumentation<PartonExtractor> documentation
    ("There is no documentation for the ThePEG::PartonExtractor class");

  static RefVector<PartonExtractor,PDFBase> interfaceSpecialDensities
    ("SpecialDensities",
     "A list of parton density objects to be used for incoming particles "
     "overriding possible densities given for particles of the "
     "BeamParticleData class.",
     &PartonExtractor::theSpecialDensities, 0, false, false, true, false);

  static Reference<PartonExtractor,PDFBase> interfaceNoPDF
    ("NoPDF",
     "A fixed reference to a NoPDF object to be used for particles without "
     "substructure.",
     &PartonExtractor::theNoPDF, true, true, true, false);

  static Parameter<PartonExtractor,int> interfaceMaxTries
    ("MaxTries",
     "The maximum number of attempts allowed when trying to generate "
     "remnants.",
     &PartonExtractor::theMaxTries, 100, 1, 1000, false, false, true);

  static Switch<PartonExtractor,bool> interfaceFlatSHatY
    ("FlatSHatY",
     "The possibility to override the l-generation in the "
     "PDFs and generate a flat distribution in log(sHat) and y.",
     &PartonExtractor::flatSHatY, false, false, false);

  static SwitchOption interfaceFlatSHatY0
    (interfaceFlatSHatY,
     "Off", "Use the l-generation defined by the PDFs", false);

  static SwitchOption interfaceFlatSHatY1
    (interfaceFlatSHatY,
     "On", "Generate flat rapidity and \\f$\\log(\\hat{s})\\f$", true);

}

RemColException::RemColException(const PartonExtractor & pe) {
  theMessage << "Parton extractor '" << pe.name() << "' failed to connect "
	     << "the colours of the outgoing partons and the remnants.";
  severity(maybeabort);
}
  
