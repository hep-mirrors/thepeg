// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ScalarSpinInfo class.
//
// Author: Peter Richardson
//

#include "ScalarSpinInfo.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

NoPIOClassDescription<ScalarSpinInfo> ScalarSpinInfo::initScalarSpinInfo;
// Definition of the static class description member.

void ScalarSpinInfo::Init() {}

void ScalarSpinInfo::transform(const LorentzMomentum & m, LorentzRotation r) {
  if(isNear(m))
    SpinInfo::transform(m,r);
}
