// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the TensorSpinInfo class.
//
// Author: Peter Richardson
//

#include "TensorSpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "TensorSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

TensorSpinInfo::~TensorSpinInfo() {}

NoPIOClassDescription<TensorSpinInfo> TensorSpinInfo::initTensorSpinInfo;
// Definition of the static class description member.

void TensorSpinInfo::Init() {

  static ClassDocumentation<TensorSpinInfo> documentation
    ("There is no documentation for the \\classname{TensorSpinInfo} class");

}

