// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PartonBinInstance class.
//

#include "PartonBinInstance.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBinInstance.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

PartonBinInstance::PartonBinInstance()
  : theJacobian(1.0), theXi(-1.0), theEps(-1.0), theLi(-1.0), theX(-1.0),
    theL(-1.0), theScale(0.0*GeV2), theRemnantWeight(0.0) {}

PartonBinInstance::PartonBinInstance(const PartonBinInstance & x)
  : theBin(x.theBin), theBins(x.theBins), theIncoming(x.theIncoming),
    theJacobian(x.theJacobian), theParticle(x.theParticle),
    theParton(x.theParton), thePartons(x.thePartons), theXi(x.theXi),
    theEps(x.theEps), theLi(x.theLi), theX(x.theX), theL(x.theL),
    theScale(x.theScale), theKT(x.theKT), theRemnantWeight(x.theRemnantWeight),
    theRemnants(x.theRemnants), theRemInfo(x.theRemInfo) {}

PartonBinInstance::PartonBinInstance(tcPBPtr pb, tPBIPtr pbi)
  : theBin(pb), theJacobian(1.0), theXi(-1.0), theEps(-1.0), theLi(-1.0),
    theX(-1.0), theL(-1.0), theScale(0.0*GeV2), theRemnantWeight(0.0) {
  if ( pbi ) theIncoming = pbi;
  else if ( bin()->incoming() )
    theIncoming = new_ptr(PartonBinInstance(bin()->incoming()));
}

PartonBinInstance::~PartonBinInstance() {}

tPBIPtr PartonBinInstance::getFirst() {
  return incoming()? incoming()->getFirst(): tPBIPtr(this);
}

void PartonBinInstance::reset(double lx, Energy2 Q2) {
  l(lx);
  li(lx);
  scale(Q2);
  particle(tPPtr());
  parton(tPPtr());
  theRemnants.clear();
  thePartons.clear();
  remnantWeight(1.0);
}

void PartonBinInstance::prepare() {
  li(-1.0);
  l(0.0);
  if ( !incoming() ) return;
  li(-1.0);
  l(-1.0);
  incoming()->prepare();
}

void PartonBinInstance::generate(const double * r) {
  scale(0.0*GeV2);
  if ( !incoming() ) return;
  if ( li() >= 0 ) return;
  li(0.0);
  jacobian(1.0);
  remnantWeight(1.0);
  if ( bin()->pdfDim() )
    li(pdf()->flattenL(particleData(), partonData(), bin()->cuts(),
		       *r++, theJacobian));
  if ( bin()->pdfDim() > 1 )
    scale(pdf()->flattenScale(particleData(), partonData(), bin()->cuts(),
			      li(), *r++, theJacobian));
  incoming()->generate(r);
  l(li() + incoming()->l());
}

double PartonBinInstance::fullFn(Energy2 newScale) {
  if ( !incoming() ) return 1.0;
  if ( newScale > 0.0*GeV2 ) scale(newScale);
  return incoming()->fullFn() * jacobian() *
    pdf()->xfl(particleData(), partonData(),
	       scale(), li(), incoming()->scale());
}
  
void PartonBinInstance::persistentOutput(PersistentOStream & os) const {
  os << theBin << theBins << theIncoming << theJacobian << theParticle
     << theParton << thePartons << theXi << theEps << theLi << theX << theL
     << ounit(theScale, GeV2) << ounit(theKT, GeV) << theRemnantWeight
     << theRemnants;
}

void PartonBinInstance::persistentInput(PersistentIStream & is, int) {
  is >> theBin >> theBins >> theIncoming >> theJacobian >> theParticle
     >> theParton >> thePartons >> theXi >> theEps >> theLi >> theX >> theL
     >> iunit(theScale, GeV2) >> iunit(theKT, GeV) >> theRemnantWeight
     >> theRemnants;
  theRemInfo = RemIPtr();
}

ClassDescription<PartonBinInstance> PartonBinInstance::initPartonBinInstance;
// Definition of the static class description member.

void PartonBinInstance::Init() {

}

