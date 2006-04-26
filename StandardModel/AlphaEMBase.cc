// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AlphaEMBase class.
//

#include "AlphaEMBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AlphaEMBase.tcc"
#endif

using namespace ThePEG;

AlphaEMBase::~AlphaEMBase() {}

AbstractNoPIOClassDescription<AlphaEMBase> AlphaEMBase::initAlphaEMBase;

void AlphaEMBase::Init() {

  static ClassDocumentation<AlphaEMBase> documentation
    ("An abstract base class used by the StandardModelBase class to "
     "implement the electro-magnetic coupling.");

}

