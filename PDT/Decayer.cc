// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Decayer class.
//

#include "Decayer.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Reference.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Decayer.tcc"
#endif

using namespace ThePEG;

Decayer::~Decayer() {}

double Decayer::brat(const DecayMode &,
		     const ParticleData &, double b) const {
  return b;

}

double Decayer::brat(const DecayMode &, const Particle &, double b) const {
  return b;
}

AbstractNoPIOClassDescription<Decayer> Decayer::initDecayer;

void Decayer::Init() {

  static Reference<Decayer,Amplitude> interfaceAmplitude
    ("Amplitude",
     "The eventual amplitude associated to this decay matrix element.",
     &Decayer::theAmplitude, false, false, true, true);

}

void Decayer::persistentOutput(PersistentOStream & os) const {
  os << theAmplitude;
}

void Decayer::persistentInput(PersistentIStream & is, int) {
  is >> theAmplitude;
}

