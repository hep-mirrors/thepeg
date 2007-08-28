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

using namespace ThePEG;

// *** Standard Interfaced functions ***

AbstractClassDescription<PtGenerator> PtGenerator::initPtGenerator;

void PtGenerator::Init() {

  static ClassDocumentation<PtGenerator> documentation
    ("This base class should be used by models describing intrinsic "
     "transverse momenta distributions in hadrons.");

}
