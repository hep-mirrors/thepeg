// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FixedCMSLuminosity class.
//

#include "FixedCMSLuminosity.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FixedCMSLuminosity.tcc"
#endif

using namespace ThePEG;

FixedCMSLuminosity::~FixedCMSLuminosity() {}

void FixedCMSLuminosity::persistentOutput(PersistentOStream & os) const {
  os << ounit(theEnergy, GeV);
}

void FixedCMSLuminosity::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theEnergy, GeV);
}

ClassDescription<FixedCMSLuminosity>
FixedCMSLuminosity::initFixedCMSLuminosity;

 void FixedCMSLuminosity::Init() {

  static ClassDocumentation<FixedCMSLuminosity> documentation
    ("The \\classname{FixedCMSLuminosity} class describes an experiment "
     "with incoming particles colliding with precicely defined and "
     "opposite momenta. It is derived from the "
     "\\classname{LuminosityFunction} base class.");

  static Parameter<FixedCMSLuminosity,Energy> interfaceEnergy
    ("Energy",
     "The total energy in GeV in the cms of the colliding particles.",
     &FixedCMSLuminosity::theEnergy, GeV, 91.2*GeV, 0.0*GeV,
     Constants::MaxEnergy, false, false, true);
}

