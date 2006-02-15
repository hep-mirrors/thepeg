// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the TwoCutBase class.
//

#include "TwoCutBase.h"
#include "Cuts.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "TwoCutBase.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

TwoCutBase::~TwoCutBase() {}

Energy2 TwoCutBase::minSij(tcPDPtr pi, tcPDPtr pj) const {
  return 0.0*GeV2;
}

Energy2 TwoCutBase::minTij(tcPDPtr pi, tcPDPtr po) const {
  return 0.0*GeV2;
}

double TwoCutBase::minDeltaR(tcPDPtr pi, tcPDPtr pj) const {
  return 0.0;
}

Energy TwoCutBase::minKTClus(tcPDPtr pi, tcPDPtr pj) const {
  return 0.0*GeV;
}

double TwoCutBase::minDurham(tcPDPtr pi, tcPDPtr pj) const {
  return 0.0;
}

bool TwoCutBase::passCuts(tcCutsPtr parent, tcPDPtr pitype, tcPDPtr pjtype,
			  LorentzMomentum pi, LorentzMomentum pj,
			  bool inci, bool incj) const {
  if ( inci && incj ) return true;
  else if ( inci ) {
    if ( (pj - pi).m2() <= minTij(pitype, pjtype) ) return false;
    if ( pj.perp() <= minKTClus(tcPDPtr(), pjtype) ) return false;
  }
  else if ( incj ) {
    if ( (pi - pj).m2() <= minTij(pjtype, pitype) ) return false;
    if ( pi.perp() <= minKTClus(tcPDPtr(), pitype) ) return false;
  }
  else {
    if ( (pi + pj).m2() <= minSij(pitype, pjtype) ) return false;
    double deta2 = sqr(pi.eta() - pj.eta());
    double dphi = abs(pi.phi() - pi.phi());
    if ( dphi > Constants::pi ) dphi = 2.0*Constants::pi - dphi;
    double dr = sqrt(deta2 + sqr(dphi));
    if ( dr < minDeltaR(pitype, pjtype) ) return false;
    if ( min(pi.perp(), pj.perp())*dr <= minKTClus(pitype, pjtype) )
      return false;
    if ( 2.0*sqr(min(pi.e(), pj.e()))*(1.0 - cos(pi.angle(pj))) <
	 parent->currentSHat()*minDurham(pitype, pjtype) ) return false;
  }
  return true;
}

bool TwoCutBase::passCuts(tcCutsPtr parent, tcPPtr pi, tcPPtr pj,
			  bool inci, bool incj) const {
  return passCuts(parent, pi->dataPtr(), pj->dataPtr(),
		  pi->momentum(), pj->momentum(), inci, incj);
}

AbstractNoPIOClassDescription<TwoCutBase> TwoCutBase::initTwoCutBase;
// Definition of the static class description member.

void TwoCutBase::Init() {

  static ClassDocumentation<TwoCutBase> documentation
    ("This class corresponds to a kinematical cut to be made on a pair of "
     "particles in a hard sub-process.");

}

