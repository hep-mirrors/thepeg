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

using namespace ThePEG;

AbstractClassDescription<ZGenerator> ZGenerator::initZGenerator;

void ZGenerator::Init(){

  static ClassDocumentation<ZGenerator> documentation
    ("The base class for all classes implementing models to generate the "
     "momentum fraction, \\f$z\\f$, taken by hadrons produced in a "
     "hadronization scenario.");

}

