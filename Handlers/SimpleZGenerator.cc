// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleZGenerator class.
//

#include "SimpleZGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleZGenerator.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleZGenerator::~SimpleZGenerator() {}

double SimpleZGenerator::generate(cPDPtr q1, cPDPtr q2, Energy2) const {
  if ( BaryonMatcher::Check(*q1) || DiquarkMatcher::Check(*q1) ) {
    if ( BaryonMatcher::Check(*q2) || DiquarkMatcher::Check(*q2) )
      return rnd();
    else
      return sqrt(rnd());
  } else {
    if ( BaryonMatcher::Check(*q2) || DiquarkMatcher::Check(*q2) )
      return 1.0 - sqrt(rnd());
    else
      return rnd();
  }
}

void SimpleZGenerator::persistentOutput(PersistentOStream &) const {}

void SimpleZGenerator::persistentInput(PersistentIStream &, int) {}

ClassDescription<SimpleZGenerator> SimpleZGenerator::initSimpleZGenerator;
// Definition of the static class description member.

void SimpleZGenerator::Init() {

  static ClassDocumentation<SimpleZGenerator> documentation
    ("Implements a naive unphysical model to generate the momentum fraction "
     "\\f$z\\f$ taken by hadrons produced in a hadronization scenario. It "
     "should only be used for testing purposes.");

}

