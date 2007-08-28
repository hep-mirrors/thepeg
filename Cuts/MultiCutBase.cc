// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultiCutBase class.
//

#include "MultiCutBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Particle.h"

using namespace ThePEG;

Energy2 MultiCutBase::minS(const tcPDVector &) const {
  return 0.0*GeV2;
}

Energy2 MultiCutBase::maxS(const tcPDVector &) const {
  return Constants::MaxEnergy2;
}

bool MultiCutBase::passCuts(tcCutsPtr, const tcPDVector & ptype,
			    const vector<LorentzMomentum> & p) const {
  long NN = (1 << ptype.size());
  // NN is the number of different combinations that can be made.

  for ( long ii = 1; ii < NN; ++ii ) {
    long mask = ii;
    tcPDVector pt;
    LorentzMomentum sum;
    int i = -1;
    while ( mask ) {
      ++i;
      int sel = mask%2;
      mask /= 2;
      if ( !sel ) continue;
      pt.push_back(ptype[i]);
      sum += p[i];
    }
    if ( pt.size() < 2 ) continue;
    if ( sum.m2() < minS(pt) ) return false;
    if ( sum.m2() >= maxS(pt) ) return false;
  }
  return true;
}

bool MultiCutBase::passCuts(tcCutsPtr parent, const tcPVector & p) const {
  tcPDVector ptype(p.size());
  vector<LorentzMomentum> mom(p.size());
  for ( int i = 0, N = p.size(); i < N; ++i ) {
    ptype[i] = p[i]->dataPtr();
    mom[i] = p[i]->momentum();
  }
  return passCuts(parent, ptype, mom);
}

AbstractNoPIOClassDescription<MultiCutBase> MultiCutBase::initMultiCutBase;
// Definition of the static class description member.

void MultiCutBase::Init() {

  static ClassDocumentation<MultiCutBase> documentation
    ("This class corresponds to a kinematical cut to be made on a set of "
     "outgoing particles from a hard sub-process.");

}

