// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DipoleFormFactor class.
//

#include "DipoleFormFactor.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

IBPtr DipoleFormFactor::clone() const {
  return new_ptr(*this);
}

IBPtr DipoleFormFactor::fullclone() const {
  return new_ptr(*this);
}

void DipoleFormFactor::persistentOutput(PersistentOStream & os) const {
  os << ounit(q02_,GeV2);
}

void DipoleFormFactor::persistentInput(PersistentIStream & is, int) {
  is >> iunit(q02_,GeV2);
}

// The following static variable is needed for the type
// description system in ThePEG. 
DescribeClass<DipoleFormFactor,NucleonFormFactor>
describeThePEGDipoleFormFactor("ThePEG::DipoleFormFactor", "NucleonFormFactor.so");

void DipoleFormFactor::Init() {
  
  static ClassDocumentation<DipoleFormFactor> documentation
    ("The DipoleFormFactor class implements a dipole form for the nucleon form factor");
  
  static Parameter<DipoleFormFactor,Energy2> interfaceDipoleScale
    ("DipoleScale",
     "The scale for the dipole form factor",
     &DipoleFormFactor::q02_, GeV2, 0.71*GeV2, 0.0*GeV2, 10.0*GeV2,
     false, false, Interface::limited);

}

