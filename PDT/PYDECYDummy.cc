// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PYDECYDummy class.
//

#include "PYDECYDummy.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PYDECYDummy.tcc"
#endif

using namespace ThePEG;

void PYDECYDummy::readSetup(istream & is) throw(SetupException) {
  is >> theME;
}

bool PYDECYDummy::accept(const DecayMode &) const {
  return true;
}

ParticleVector PYDECYDummy::decay(const DecayMode &, const Particle &) const {
  throw std::logic_error("Tried to decay with the PYDECYDummy decayer.");
}

double PYDECYDummy::brat(const DecayMode &,
			 const ParticleData &, double) const {
  return 0.0;
}

double PYDECYDummy::brat(const DecayMode &, const Particle &, double) const {
  return 0.0;
}


IBPtr PYDECYDummy::clone() const {
  return new_ptr(*this);
}

IBPtr PYDECYDummy::fullclone() const {
  return new_ptr(*this);
}

void PYDECYDummy::persistentOutput(PersistentOStream & os) const {
  os << theME;
}

void PYDECYDummy::persistentInput(PersistentIStream & is, int) {
  is >> theME;
}

ClassDescription<PYDECYDummy> PYDECYDummy::initPYDECYDummy;

void PYDECYDummy::Init() {}

