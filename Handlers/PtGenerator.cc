// -*- C++ -*-
//$Id$
// --------------------------------------------------------
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PtGenerator class.
//

#include "PtGenerator.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"


#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PtGenerator.tcc"
#endif

using namespace ThePEG;

PtGenerator::~PtGenerator() {}




// *** Standard Interfaced functions ***

AbstractClassDescription<PtGenerator> PtGenerator::initPtGenerator;

void PtGenerator::Init() {

  static ClassDocumentation<PtGenerator> documentation
    ("There is no documentation for the ThePEG::PtGenerator class");

}








