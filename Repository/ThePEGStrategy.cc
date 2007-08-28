// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ThePEGStrategy class.
//

#include "ThePEGStrategy.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/ParticleData.h"

using namespace ThePEG;

IBPtr ThePEGStrategy::clone() const {
  return new_ptr(*this);
}

IBPtr ThePEGStrategy::fullclone() const {
  return new_ptr(*this);
}

NoPIOClassDescription<ThePEGStrategy> ThePEGStrategy::initThePEGStrategy;

void ThePEGStrategy::Init() {
  static ClassDocumentation<ThePEGStrategy> interfaceDescription
    ("This class represents the default ThePEG strategy", "", "");


}

