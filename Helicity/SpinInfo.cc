// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinInfo class.
//
// Author: Peter Richardson
//
#include "SpinInfo.h"
#include "ThePEG/Interface/ClassDocumentation.h"


using namespace ThePEG;
using namespace Helicity;

SpinInfo::~SpinInfo() {}

NoPIOClassDescription<SpinInfo> SpinInfo::initSpinInfo;
// Definition of the static class description member.

void SpinInfo::Init() {

  static ClassDocumentation<SpinInfo> documentation
    ("There is no documentation for the \\classname{SpinInfo} class");

}
