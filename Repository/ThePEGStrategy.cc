// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ThePEGStrategy class.
//

#include "ThePEGStrategy.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ThePEGStrategy.tcc"
#endif

using namespace ThePEG;

ThePEGStrategy::~ThePEGStrategy() {}

NoPIOClassDescription<ThePEGStrategy> ThePEGStrategy::initThePEGStrategy;

void ThePEGStrategy::Init() {
  static ClassDocumentation<ThePEGStrategy> interfaceDescription
    ("This class represents the default ThePEG strategy", "", "");


}

