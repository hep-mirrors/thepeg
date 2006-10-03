// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DummyDecayer class.
//

#include "DummyDecayer.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DummyDecayer.tcc"
#endif

using namespace ThePEG;

DummyDecayer::~DummyDecayer() {}

bool DummyDecayer::accept(const DecayMode &) const {
  return true;
}

ParticleVector DummyDecayer::decay(const DecayMode &,
				  const Particle &) const {
  throw std::logic_error("Tried to decay with the DummyDecayer class.");
}

double DummyDecayer::
brat(const DecayMode &, const ParticleData &, double) const {
  return 0.0;
}

double DummyDecayer::brat(const DecayMode &, const Particle &, double) const {
  return 0.0;
}


NoPIOClassDescription<DummyDecayer> DummyDecayer::initDummyDecayer;
// Definition of the static class description member.

void DummyDecayer::Init() {

  static ClassDocumentation<DummyDecayer> documentation
    ("This is a dummy decayer class to be used for symbolic decay "
     "channels. If it for some reason is called to perform a decay, it "
     "will throw a std::logic_error.");

}

