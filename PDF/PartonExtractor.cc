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
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/UtilityBase.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonExtractor.tcc"
#endif

using namespace ThePEG;

PartonExtractor::PartonExtractor()
  : theMaxTries(100), flatSHatY(false) {}

PartonExtractor::PartonExtractor(const PartonExtractor & x)
  : HandlerBase(x), LastXCombInfo<>(x), theLastPartonBins(x.theLastPartonBins),
    thePartonBinInstances(x.thePartonBinInstances),
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
  lastPartonBins().clear();
  theLastXComb = newXComb;
  lastPartonBins()[lastPartons().first] = newXComb->partonBins().first;
  lastPartonBins()[lastPartons().second] = newXComb->partonBins().second;
}

tPBPtr PartonExtractor::partonBin(tcPPtr p) const {
  PartonBinMap::const_iterator it = lastPartonBins().find(p);
  return it == lastPartonBins().end()? PBPtr(): it->second;
}

tPBIPtr PartonExtractor::partonBinInstance(tcPPtr p) const {
  PartonBinInstanceMap::const_iterator it = partonBinInstances().find(p);
  return it == partonBinInstances().end()? PBIPtr(): it->second;
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

void PartonExtractor::prepare(const PBPair & pbins) {
  lastPartonBins().clear();
  pbins.first->prepare();
  pbins.second->prepare();
}

void PartonExtractor::prepare(const PBIPair & pbins) {
  partonBinInstances().clear();
  pbins.first->prepare();
  pbins.second->prepare();
}

bool PartonExtractor::
generateL(const PBPair & pbins, const double * r1, const double * r2) {
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

  pbins.first->lastPartialL(l1 - pbins.first->lastL() +
			    pbins.first->lastPartialL());
  pbins.first->lastL(l1);
  pbins.first->lastJacobian(km*(ymax - ymin));
  pbins.second->lastPartialL(l2 - pbins.second->lastL() +
			     pbins.second->lastPartialL());
  pbins.second->lastL(l2);
  pbins.second->lastJacobian(1.0);
  return ( pbins.first->lastPartialL() >= 0.0 &&
	   pbins.second->lastPartialL() >= 0.0 );
  
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
generateSHat(Energy2 s, const PBPair & pbins,
	     const double * r1, const double * r2) {

  Direction<0> dir(true);
  pbins.first->lastScale(-lastScale());
  if ( !generate(*pbins.first, r1,
		 pbins.first->getFirst()->lastParton()->momentum()) )
    return -1.0*GeV2;
  dir.reverse();
  pbins.second->lastScale(-lastScale());
  if ( !generate(*pbins.second, r2,
		 pbins.second->getFirst()->lastParton()->momentum()) )
    return -1.0*GeV2;
  
  return (pbins.first->lastParton()->momentum() +
	  pbins.second->lastParton()->momentum()).m2();
}

Energy2 PartonExtractor::
generateSHat(Energy2 s, const PBIPair & pbins,
	     const double * r1, const double * r2) {

  Direction<0> dir(true);
  pbins.first->scale(-lastScale());
  if ( !generate(*pbins.first, r1,
		 pbins.first->getFirst()->parton()->momentum()) )
    return -1.0*GeV2;
  dir.reverse();
  pbins.second->scale(-lastScale());
  if ( !generate(*pbins.second, r2,
		 pbins.second->getFirst()->parton()->momentum()) )
    return -1.0*GeV2;
  
  return (pbins.first->parton()->momentum() +
	  pbins.second->parton()->momentum()).m2();
}

void PartonExtractor::
generateL(PartonBin & pb, const double * r) {
  if ( !pb.incoming() ) return;

  pb.lastParton(pb.parton()->produceParticle(Lorentz5Momentum()));
  generateL(*pb.incoming(), r + pb.pdfDim() + pb.remDim());
  pb.lastParticle(pb.incoming()->lastParton());
  if ( pb.lastPartialL() >= 0 ) return;
  double jac = 1.0;
  if ( pb.pdfDim() )
    pb.lastPartialL(pb.pdf()->flattenL(pb.particle(), pb.parton(),
				       pb.cuts(), *r++, jac));
  pb.lastScale(-1.0*GeV2);
  if ( pb.pdfDim() > 1 )
    pb.lastScale(pb.pdf()->flattenScale(pb.particle(), pb.parton(), pb.cuts(),
					pb.lastPartialL(), *r++, jac));
  pb.lastJacobian(jac);
  pb.lastL(pb.incoming()->lastL() + pb.lastPartialL());
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
generate(PartonBin & pb, const double * r, const Lorentz5Momentum & first) {
  if ( !pb.incoming() ) return true;
  if ( !generate(*pb.incoming(), r + pb.pdfDim() + pb.remDim(), first) )
    return false;;
  pb.remnantWeight(1.0);
  pb.lastParton()->setMomentum
    (pb.remnantHandler()->generate(pb, r, pb.lastScale(),
				   pb.lastParticle()->momentum()));
  if ( pb.remnantWeight() <= 0.0 ) return false;
  lastPartonBins()[pb.lastParton()] = &pb;
  return true;
}

bool PartonExtractor::
generate(PartonBinInstance & pb, const double * r,
	 const Lorentz5Momentum & first) {
  if ( !pb.incoming() ) return true;
  if ( !generate(*pb.incoming(),
		 r + pb.bin()->pdfDim() + pb.bin()->remDim(), first) )
    return false;;
  pb.remnantWeight(1.0);
  pb.parton()->setMomentum
    (pb.remnantHandler()->generate(pb, r, pb.scale(),
				   pb.particle()->momentum()));
  if ( pb.remnantWeight() <= 0.0 ) return false;
  partonBinInstances()[pb.parton()] = &pb;
  return true;
}

double PartonExtractor::fullFn(const PBPair & pbins, Energy2 scale) {
  pbins.first->lastScale(scale);
  pbins.second->lastScale(scale);
  return fullFn(*pbins.first)*fullFn(*pbins.second);
}

double PartonExtractor::fullFn(const PBIPair & pbins, Energy2 scale) {
  pbins.first->scale(scale);
  pbins.second->scale(scale);
  return fullFn(*pbins.first)*fullFn(*pbins.second);
}

double PartonExtractor::fullFn(const PartonBin & pb) {
  if ( !pb.incoming() ) return 1.0;
  return fullFn(*pb.incoming()) * pb.lastJacobian() * pb.remnantWeight() *
    pb.pdf()->xfl(pb.particle(), pb.parton(), pb.lastScale(),
		  pb.lastPartialL(), pb.incoming()->lastScale());
}

double PartonExtractor::fullFn(const PartonBinInstance & pb) {
  if ( !pb.incoming() ) return 1.0;
  return fullFn(*pb.incoming()) * pb.jacobian() * pb.remnantWeight() *
    pb.pdf()->xfl(pb.particleData(), pb.partonData(), pb.scale(),
		  pb.li(), pb.incoming()->scale());
}

void PartonExtractor::
construct(const PBPair & pbins, tStepPtr step) {
  Direction<0> dir(true);
  construct(*pbins.first, step);
  dir.reverse();
  construct(*pbins.second, step);
}

void PartonExtractor::
construct(const PBIPair & pbins, tStepPtr step) {
  Direction<0> dir(true);
  construct(*pbins.first, step);
  dir.reverse();
  construct(*pbins.second, step);
}

void PartonExtractor::
construct(PartonBin & pb, tStepPtr step) {
  if ( !pb.incoming() ) return;
  Energy2 m2 = pb.lastParticle()->momentum().m2();
  LorentzMomentum p = lightCone(sqrt(abs(m2)), m2/sqrt(abs(m2)));
  pb.remnantHandler()->createRemnants(pb);
  tPVector rem(pb.lastRemnants().begin(), pb.lastRemnants().end());
  if ( !step->addDecayProduct(pb.lastParticle(),
			      rem.begin(), rem.end(), false) );
  colourConnect(pb.lastParticle(), pb.lastParton(), rem);
  if ( pb.incoming()->incoming() ) step->addIntermediate(pb.lastParticle());
  construct(*pb.incoming(), step);
}

void PartonExtractor::
construct(PartonBinInstance & pb, tStepPtr step) {
  if ( !pb.incoming() ) return;
  Energy2 m2 = pb.particle()->momentum().m2();
  LorentzMomentum p = lightCone(sqrt(abs(m2)), m2/sqrt(abs(m2)));
  pb.remnantHandler()->createRemnants(pb);
  tPVector rem(pb.remnants().begin(), pb.remnants().end());
  if ( !step->addDecayProduct(pb.particle(), rem.begin(), rem.end(), false) );
  colourConnect(pb.particle(), pb.parton(), rem);
  if ( pb.incoming()->incoming() ) step->addIntermediate(pb.particle());
  construct(*pb.incoming(), step);
}

PBIPair PartonExtractor::newRemnants(tPPair oldp, tPPair newp, tStepPtr step) {
  PBIPair pb;
  Direction<0> dir(true);
  pb.first = newRemnants(partonBinInstance(oldp.first), newp.first);
  dir.reverse();
  pb.second = newRemnants(partonBinInstance(oldp.second), newp.second);
  addNewRemnants(partonBinInstance(oldp.first), pb.first, step);
  addNewRemnants(partonBinInstance(oldp.second), pb.second, step);
  return pb;
}

PBIPtr PartonExtractor::newRemnants(tPBIPtr oldpb, tPPtr newp) {
  if ( ! oldpb || !oldpb->incoming() ) return oldpb;
  const PartonBin::tPBVector & sisters = oldpb->incoming()->bin()->outgoing();
  for ( int i = 0, N = sisters.size(); i < N; ++i )
    if ( sisters[i]->parton() == newp->dataPtr() ) {
      PBIPtr newpb = new_ptr(PartonBinInstance(sisters[i], oldpb->incoming()));
      newpb->particle(oldpb->particle());
      newpb->parton(newp);
      newpb->li(log(oldpb->particle()->momentum().dirPlus()/
		    newp->momentum().dirPlus()));
      newpb->l(oldpb->l() - oldpb->li() + newpb->li());
      Energy2 sc = -newp->scale();
      if ( oldpb->incoming()->incoming() )
	sc = -newpb->particle()->momentum().m2();
      newpb->remnantWeight(1.0);
      if ( !newpb->remnantHandler()->
	   recreateRemnants(*newpb, oldpb->parton(), newp, newpb->li(),
			    sc, newpb->particle()->momentum()) ) throw Veto();
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
  partonBinInstances()[newpb->parton()] = newpb;
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
     "On", "Generate flat rapidity and $\\log(\\hat{s})$", true);

}

RemColException::RemColException(const PartonExtractor & pe) {
  theMessage << "Parton extractor '" << pe.name() << "' failed to connect "
	     << "the colours of the outgoing partons and the remnants.";
  severity(maybeabort);
}
  
