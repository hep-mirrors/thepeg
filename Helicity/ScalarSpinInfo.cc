// -*- C++ -*-
//
// ScalarSpinInfo.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2011 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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

void ScalarSpinInfo::transform(const LorentzMomentum & m, 
			       const LorentzRotation & r) {
  if(isNear(m))
    SpinInfo::transform(m,r);
}
