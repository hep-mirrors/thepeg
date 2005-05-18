// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ReweightConstant class.
//

#include "ReweightConstant.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Parameter.h"

using namespace ThePEG;

ReweightConstant::~ReweightConstant() {}

double ReweightConstant::weight() const {
  return C;
}

void ReweightConstant::persistentOutput(PersistentOStream & os) const {
  os << C;
}

void ReweightConstant::persistentInput(PersistentIStream & is, int) {
  is >> C;
}

ClassDescription<ReweightConstant> ReweightConstant::initReweightConstant;
// Definition of the static class description member.

void ReweightConstant::Init() {

  static ClassDocumentation<ReweightConstant> documentation
    ("The ReweightConstant class is a simple ReweightBase sub-class which "
     "simply reweight an event with a constant");

  static Parameter<ReweightConstant,double> interfaceC
    ("C",
     "The constant with which to reweight an event.",
     &ReweightConstant::C, 1.0, 0, 0,
     true, false, Interface::nolimits);


}

