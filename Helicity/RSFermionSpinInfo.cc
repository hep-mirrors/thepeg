// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RSFermionSpinInfo class.
//
// Author: Peter Richardson
//

#include "RSFermionSpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RSFermionSpinInfo.tcc"
#endif


using namespace ThePEG;
using namespace Helicity;

RSFermionSpinInfo::~RSFermionSpinInfo() {}

NoPIOClassDescription<RSFermionSpinInfo> RSFermionSpinInfo::initRSFermionSpinInfo;
// Definition of the static class description member.

void RSFermionSpinInfo::Init() {

  static ClassDocumentation<RSFermionSpinInfo> documentation
    ("There is no documentation for the \\classname{RSFermionSpinInfo} class");

}

