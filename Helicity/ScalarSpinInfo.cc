// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ScalarSpinInfo class.
//
// Author: Peter Richardson
//

#include "ScalarSpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ScalarSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

ScalarSpinInfo::~ScalarSpinInfo() {}

NoPIOClassDescription<ScalarSpinInfo> ScalarSpinInfo::initScalarSpinInfo;
// Definition of the static class description member.

void ScalarSpinInfo::Init() {

  static ClassDocumentation<ScalarSpinInfo> documentation
    ("There is no documentation for the \\classname{ScalarSpinInfo} class");

}


