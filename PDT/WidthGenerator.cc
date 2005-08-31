// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the WidthGenerator class.
//

#include "WidthGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "WidthGenerator.tcc"
#endif

#include "ThePEG/CLHEPWrap/RandExponential.h"
#include "ThePEG/CLHEPWrap/PhysicalConstants.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Repository/UseRandom.h"

using namespace ThePEG;

WidthGenerator::~WidthGenerator() {}

Length WidthGenerator::lifeTime(const ParticleData &, Energy, Energy w) const {
  return RandExponential::shoot(&(UseRandom::currentEngine()), hbarc/w/mm)*mm;
}

WidthGenerator::DecayMap WidthGenerator::rate(const Particle & p) {
  DecayMap dm(p.data().decaySelector());
  return dm;
}

Energy WidthGenerator::width(const Particle & p) const {
  return width(p.data(), p.mass());
}

AbstractNoPIOClassDescription<WidthGenerator>
WidthGenerator::initWidthGenerator;

void WidthGenerator::Init() {

  static ClassDocumentation<WidthGenerator> documentation
    ("There is no documentation for the ThePEG::WidthGenerator class");

}

