// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NucleonFormFactor class.
//

#include "NucleonFormFactor.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"

using namespace ThePEG;

// The following static variable is needed for the type
// description system in ThePEG.
DescribeAbstractNoPIOClass<NucleonFormFactor,Interfaced>
describeThePEGNucleonFormFactor("ThePEG::NucleonFormFactor", "NucleonFormFactor.so");

void NucleonFormFactor::Init() {

  static ClassDocumentation<NucleonFormFactor> documentation
    ("The NucleonFormFactor class provides a base class for the impelmentation of nucleon form-factors");

}

