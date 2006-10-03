// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleDISCut class.
//

#include "SimpleDISCut.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/PDT/ParticleData.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleDISCut.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleDISCut::~SimpleDISCut() {}

bool SimpleDISCut::check(long idi, long ido) const {
  if ( abs(idi) <= 10 || abs(idi) > 16 ) return false;
  if ( idi*ido <= 0 ) return false;
  if ( chargedCurrent ) {
    if ( abs(idi)%2 ) return abs(idi) == abs(ido) - 1;
    else return abs(idi) == abs(ido) + 1;
  } else {
    return ( idi == ido );
  }
}

Energy2 SimpleDISCut::minTij(tcPDPtr pi, tcPDPtr po) const {
  if ( !check(pi->id(), po->id()) ) return 0.0*GeV2;
  return theMinQ2;
}
  
bool SimpleDISCut::passCuts(tcCutsPtr, tcPDPtr pitype, tcPDPtr pjtype,
			    LorentzMomentum pi, LorentzMomentum pj,
			    bool inci, bool incj) const {
  if ( inci ) {
    if ( incj ) return true;
    if ( !check(pitype->id(), pjtype->id()) ) return true;
    Energy2 Q2 = (pi - pj).m2();
    return Q2 > theMinQ2 && Q2 < theMaxQ2;
  }
  else if ( incj ) {
    if ( !check(pjtype->id(), pitype->id()) ) return true;
    Energy2 Q2 = (pj - pi).m2();
    return Q2 > theMinQ2 && Q2 < theMaxQ2;
  }
  return true;
}

Energy2 SimpleDISCut::minSij(tcPDPtr, tcPDPtr) const {
  return 0.0*GeV2;
}

double SimpleDISCut::minDeltaR(tcPDPtr, tcPDPtr) const {
  return 0.0;
}

Energy SimpleDISCut::minKTClus(tcPDPtr, tcPDPtr) const {
  return 0.0*GeV;
}

double SimpleDISCut::minDurham(tcPDPtr, tcPDPtr) const {
  return 0.0;
}

void SimpleDISCut::persistentOutput(PersistentOStream & os) const {
  os << ounit(theMinQ2, GeV2) << ounit(theMaxQ2, GeV2) << chargedCurrent;
}

void SimpleDISCut::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theMinQ2, GeV2) >> iunit(theMaxQ2, GeV2) >> chargedCurrent;
}

ClassDescription<SimpleDISCut> SimpleDISCut::initSimpleDISCut;
// Definition of the static class description member.

Energy SimpleDISCut::maxMinQ2() const {
  return theMaxQ2;
}

Energy SimpleDISCut::minMaxQ2() const {
  return theMinQ2;
}

void SimpleDISCut::Init() {

  static ClassDocumentation<SimpleDISCut> documentation
    ("SimpleDISCut inherits from TwoCutBase and omplements a simple "
     "\\f$Q^2\\f$ cut on the a scattered lepton, either neutral or charged "
     "current.");


  static Parameter<SimpleDISCut,Energy2> interfaceMinQ2
    ("MinQ2",
     "The minimum \\f$Q^2\\f$.",
     &SimpleDISCut::theMinQ2, GeV2, 1.0*GeV2, 0.0*GeV2, Constants::MaxEnergy2,
     true, false, Interface::limited,
     0, 0, 0, &SimpleDISCut::maxMinQ2, 0);

  static Parameter<SimpleDISCut,Energy2> interfaceMaxQ2
    ("MaxQ2",
     "The maximum \\f$Q^2\\f$. Note that this is only applied as a post-cut "
     "and will not affect the initial phase space cuts in the generation.",
     &SimpleDISCut::theMaxQ2, GeV2, 100.0*GeV2, 0.0*GeV2, 0.0*GeV2,
     true, false, Interface::lowerlim,
     0, 0, &SimpleDISCut::minMaxQ2, 0, 0);

  static Switch<SimpleDISCut,bool> interfaceCurrent
    ("Current",
     "Determines whether this cut should be applied to charged or neutral "
     "current events.",
     &SimpleDISCut::chargedCurrent, false, true, false);
  static SwitchOption interfaceCurrentCharged
    (interfaceCurrent,
     "Charged",
     "The cut is only applied to charged current events.",
     true);
  static SwitchOption interfaceCurrentNeutral
    (interfaceCurrent,
     "Neutral",
     "The cut is only applied to neutral current events.",
     false);

  interfaceMinQ2.rank(10);
  interfaceMaxQ2.rank(9);
  interfaceCurrent.rank(8);
}

