// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HardSphereYukawaFormFactor class.
//

#include "HardSphereYukawaFormFactor.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

IBPtr HardSphereYukawaFormFactor::clone() const {
  return new_ptr(*this);
}

IBPtr HardSphereYukawaFormFactor::fullclone() const {
  return new_ptr(*this);
}

void HardSphereYukawaFormFactor::persistentOutput(PersistentOStream & os) const {
  os<< ounit(aFact_,femtometer) << ounit(yukawaRange_,femtometer);
}

void HardSphereYukawaFormFactor::persistentInput(PersistentIStream & is, int) {
  is >> iunit(aFact_,femtometer) >> iunit(yukawaRange_,femtometer);
}

// The following static variable is needed for the type
// description system in ThePEG.
DescribeClass<HardSphereYukawaFormFactor,NucleonFormFactor>
describeThePEGHardSphereYukawaFormFactor("ThePEG::HardSphereYukawaFormFactor", "NucleonFormFactor.so");

void HardSphereYukawaFormFactor::Init() {

  static ClassDocumentation<HardSphereYukawaFormFactor> documentation
    ("The HardSphereYukawaFormFactor class implements a hard sphere + yukwaw form for the nucelon form factor");

    static Parameter<HardSphereYukawaFormFactor,Length> interfaceYukawaRange
    ("YukawaRange",
     "The range of the Yukawa potential",
     &HardSphereYukawaFormFactor::yukawaRange_, femtometer, 0.7*femtometer, 0.0*femtometer, 10.0*femtometer,
     false, false, Interface::limited);

  static Parameter<HardSphereYukawaFormFactor,Length> interfaceaParameter
    ("aParameter",
     "The parameter for the relationship between the nuclear mass number and radius",
     &HardSphereYukawaFormFactor::aFact_, femtometer, 1.2*femtometer, 0.0*femtometer, 10.0*femtometer,
     false, false, Interface::limited);

}
