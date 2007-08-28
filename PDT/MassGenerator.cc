// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MassGenerator class.
//

#include "MassGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

AbstractNoPIOClassDescription<MassGenerator> MassGenerator::initMassGenerator;

void MassGenerator::Init() {

  static ClassDocumentation<MassGenerator> documentation
    ("This is the base class for models giving specific masses to particle "
     "instances.");

}

