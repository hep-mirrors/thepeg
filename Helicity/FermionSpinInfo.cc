// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FermionSpinInfo class.
//
// Author: Peter Richardson
//

#include "FermionSpinInfo.h"
#include "ThePEG/Repository/CurrentGenerator.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

FermionSpinInfo::~FermionSpinInfo() {}

NoPIOClassDescription<FermionSpinInfo> FermionSpinInfo::initFermionSpinInfo;
// Definition of the static class description member.

void FermionSpinInfo::Init() {}

void FermionSpinInfo::transform(const LorentzMomentum & m, LorentzRotation r) {
  if(isNear(m)) {
    for(unsigned int ix=0;ix<2;++ix){_currentstates[ix].transform(r);}
    SpinInfo::transform(m,r);
  }
}
