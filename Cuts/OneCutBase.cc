// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the OneCutBase class.
//

#include "OneCutBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Cuts/Cuts.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "OneCutBase.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

OneCutBase::~OneCutBase() {}

Energy OneCutBase::minMaxKT(tcPDPtr p) const {
  return minKT(p);
}

double OneCutBase::minMaxEta(tcPDPtr p) const {
  return minEta(p);
}

double OneCutBase::maxMinEta(tcPDPtr p) const {
  return maxEta(p);
}

bool OneCutBase::passCuts(tcCutsPtr parent,
			  tcPDPtr ptype, LorentzMomentum p) const {
  if ( p.perp() <= minKT(ptype) ) return false;
  double y = p.rapidity() + parent->Y() + parent->currentYHat();
  if ( p.mt()*sinh(y) <= p.perp()*sinh(minEta(ptype)) ) return false;
  if ( p.mt()*sinh(y) >= p.perp()*sinh(maxEta(ptype)) ) return false;
  return true;
}

bool OneCutBase::passCuts(tcCutsPtr parent, tcPPtr p) const {
  return passCuts(parent, p->dataPtr(), p->momentum());
}

Energy OneCutBase::minKT(tcPDPtr) const {
  return 0.0*GeV;
}

double OneCutBase::minEta(tcPDPtr) const {
  return -Constants::MaxRapidity;
}

double OneCutBase::maxEta(tcPDPtr) const {
  return Constants::MaxRapidity;
}

AbstractNoPIOClassDescription<OneCutBase> OneCutBase::initOneCutBase;
// Definition of the static class description member.

void OneCutBase::Init() {

  static ClassDocumentation<OneCutBase> documentation
    ("This class corresponds to a kinematical cut to be made on a single "
     "outgoing parton from a hard sub-process.");

}

