// -*- C++ -*-

// This file contains the implementations of the declarations in
// ThePEG.h.

#include "ThePEG/Config/ThePEG.h"

using namespace ThePEG;

void Base::debug() const {
  debugme();
}

void Base::debugme() const {
  cerr << "(#ref: " << referenceCount() << ")";
}

