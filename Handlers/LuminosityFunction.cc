// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LuminosityFunction class.
//

#include "LuminosityFunction.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LuminosityFunction.tcc"
#endif

using namespace ThePEG;

LuminosityFunction::LuminosityFunction() {}

LuminosityFunction::LuminosityFunction(const LuminosityFunction & x)
  : HandlerBase(x), LastXCombInfo<>(x) {}

LuminosityFunction::~LuminosityFunction() {}

void LuminosityFunction::select(tXCombPtr xcomb) {
  theLastXComb = xcomb;
}

double LuminosityFunction::Y() const {
  return 0.0;
}

LorentzRotation LuminosityFunction::getBoost() const {
  LorentzRotation r;
  return r;
}

int LuminosityFunction::nDim(const cPDPair &) const {
  return 0;
}

double LuminosityFunction::
value(const cPDPair & pdp, double l1, double l2) const {
  return l1 == 0.0 && l2 == 0.0? 1.0: 0.0;
}

pair<double,double>
LuminosityFunction::
generateLL(const double *, double & jacobian) const {
  return make_pair(0.0, 0.0);
}

void LuminosityFunction::persistentOutput(PersistentOStream & os) const {
  os << theLastXComb;
}

void LuminosityFunction::persistentInput(PersistentIStream & is, int) {
  is >> theLastXComb;
}

AbstractClassDescription<LuminosityFunction> LuminosityFunction::
initLuminosityFunction;

void LuminosityFunction::Init() {

  static ClassDocumentation<LuminosityFunction> documentation
    ("This base class should be used by all classes describing the luminosity "
     "and energy distribution of colliding particle beams.");

}

