// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NoPDF class.
//

#include "NoPDF.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/PDT/ParticleData.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoPDF.tcc"
#endif

using namespace ThePEG;

NoPDF::~NoPDF() {}

bool NoPDF::canHandleParticle(tcPDPtr particle) const {
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
xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale, double l,
    Energy2 particleScale) const {
  return ( l == 0 && particle == parton )? 1.0: 0.0;
}

NoPIOClassDescription<NoPDF> NoPDF::initNoPDF;

void NoPDF::Init() {}

