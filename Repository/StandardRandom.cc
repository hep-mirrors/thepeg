// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardRandom class.
//

#include "StandardRandom.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardRandom.tcc"
#endif

using namespace ThePEG;

StandardRandom::~StandardRandom() {}

IBPtr StandardRandom::clone() const {
  return new_ptr(*this);
}

IBPtr StandardRandom::fullclone() const {
  return new_ptr(*this);
}

RandomEngine & StandardRandom::randomGenerator() {
  return theRandomGenerator;
}

void StandardRandom::setSeed(long seed) {
  theRandomGenerator.setSeed(seed);
}

void StandardRandom::persistentOutput(PersistentOStream & os) const {
  ostringstream oss;
  oss << theRandomGenerator;
  os << oss.str();
}

void StandardRandom::persistentInput(PersistentIStream & is, int) {
  string ss;
  is >> ss;
  istringstream iss(ss);
  iss >> theRandomGenerator;
}

ClassDescription<StandardRandom> StandardRandom::initStandardRandom;

void StandardRandom::Init() {

  static ClassDocumentation<StandardRandom> documentation
    ("There is no documentation for the ThePEG::StandardRandom class");

}

