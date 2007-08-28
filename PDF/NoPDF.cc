// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NoPDF class.
//

#include "NoPDF.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/PDT/ParticleData.h"

using namespace ThePEG;

IBPtr NoPDF::clone() const {
  return new_ptr(*this);
}

IBPtr NoPDF::fullclone() const {
  return new_ptr(*this);
}

bool NoPDF::canHandleParticle(tcPDPtr) const {
  return true;
}

bool NoPDF::canHandle(tcPDPtr particle) const {
  return canHandleParticle(particle) && remnantHandler() &&
    remnantHandler()->canHandle(particle, cPDVector());
}

cPDVector NoPDF::partons(tcPDPtr p) const {
  return cPDVector(1, p);
}

double NoPDF::
xfl(tcPDPtr particle, tcPDPtr parton, Energy2, double l,
    Energy2) const {
  return ( l == 0 && particle == parton )? 1.0: 0.0;
}

NoPIOClassDescription<NoPDF> NoPDF::initNoPDF;

void NoPDF::Init() {}

