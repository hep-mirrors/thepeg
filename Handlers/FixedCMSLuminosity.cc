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

using namespace ThePEG;

FixedCMSLuminosity::~FixedCMSLuminosity() {}

void FixedCMSLuminosity::setEnergy(Energy e) {
  beamEMaxA(e*0.5);
  beamEMaxB(e*0.5);
}

Energy FixedCMSLuminosity::getEnergy() const {
  return energy();
}

NoPIOClassDescription<FixedCMSLuminosity>
FixedCMSLuminosity::initFixedCMSLuminosity;

 void FixedCMSLuminosity::Init() {

  static ClassDocumentation<FixedCMSLuminosity> documentation
    ("The ThePEG::FixedCMSLuminosity class describes an experiment "
     "with incoming particles colliding with precicely defined and "
     "opposite momenta given by half the <interface>Energy</interface>.");

  static Parameter<FixedCMSLuminosity,Energy> interfaceEnergy
    ("Energy",
     "The total energy in GeV in the cms of the colliding particles.",
     0, GeV, 91.2*GeV, 0.0*GeV, 0*GeV,
     true, false, Interface::lowerlim,
     &FixedCMSLuminosity::setEnergy, &FixedCMSLuminosity::getEnergy,
     (Energy(FixedCMSLuminosity::*)()const)(0),
     (Energy(FixedCMSLuminosity::*)()const)(0),
     (Energy(FixedCMSLuminosity::*)()const)(0));

  interfaceEnergy.rank(11);

}

