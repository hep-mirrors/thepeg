// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AlphaEMBase class.
//

#include "AlphaEMBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

AbstractNoPIOClassDescription<AlphaEMBase> AlphaEMBase::initAlphaEMBase;

void AlphaEMBase::Init() {

  static ClassDocumentation<AlphaEMBase> documentation
    ("An abstract base class used by the StandardModelBase class to "
     "implement the electro-magnetic coupling.");

}

