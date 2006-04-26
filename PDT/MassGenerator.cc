// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MassGenerator class.
//

#include "MassGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MassGenerator.tcc"
#endif

using namespace ThePEG;

MassGenerator::~MassGenerator() {}

AbstractNoPIOClassDescription<MassGenerator> MassGenerator::initMassGenerator;

void MassGenerator::Init() {

  static ClassDocumentation<MassGenerator> documentation
    ("This is the base class for models giving specific masses to particle "
     "instances.");

}

