// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the VectorSpinInfo class.
//
// Author: Peter Richardson
//

#include "VectorSpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "VectorSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

VectorSpinInfo::~VectorSpinInfo() {}

NoPIOClassDescription<VectorSpinInfo> VectorSpinInfo::initVectorSpinInfo;
// Definition of the static class description member.

void VectorSpinInfo::Init() {

  static ClassDocumentation<VectorSpinInfo> documentation
    ("There is no documentation for the \\classname{VectorSpinInfo} class");
}


