// -*- C++ -*-
//$Id$
// ----------------------------------------------------
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ZGenerator class.
//

#include "ZGenerator.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ZGenerator.tcc"
#endif

using namespace ThePEG;

ZGenerator::~ZGenerator() {}


// *** Standard Interfaced Functions ***
//void ZGenerator::persistentOutput(PersistentOStream & os) const {}
//void ZGenerator::persistentInput(PersistentIStream & is, int) { }
//void ZGenerator::Init() {}

AbstractClassDescription<ZGenerator> ZGenerator::initZGenerator;

void ZGenerator::Init(){

  static ClassDocumentation<ZGenerator> documentation
    ("There is no documentation for the ThePEG::ZGenerator class");

}

