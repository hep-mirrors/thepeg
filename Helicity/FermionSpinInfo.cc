// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FermionSpinInfo class.
//
// Author: Peter Richardson
//

#include "FermionSpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FermionSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

FermionSpinInfo::~FermionSpinInfo() {}

NoPIOClassDescription<FermionSpinInfo> FermionSpinInfo::initFermionSpinInfo;
// Definition of the static class description member.

void FermionSpinInfo::Init() {

  static ClassDocumentation<FermionSpinInfo> documentation
    ("There is no documentation for the \\classname{FermionSpinInfo} class");
}
