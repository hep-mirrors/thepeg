// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FlavourGenerator class.
//

#include "FlavourGenerator.h"
#include "ThePEG/PDT/ParticleData.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlavourGenerator.tcc"
#endif

using namespace ThePEG;

FlavourGenerator::~FlavourGenerator() {}

tcPDPtr FlavourGenerator::getBaryon(tcPDPtr q1, tcPDPtr q2, tcPDPtr q3) const {
  return getBaryon(q1->id(), q2->id(), q3->id());
}

tcPDPtr FlavourGenerator::getBaryon(long iq1, long iq2, long iq3) const {
  return getBaryon(getParticleData(iq1),
		   getParticleData(iq2),
		   getParticleData(iq3));
}

tcPDPtr FlavourGenerator::getHadron(tcPDPtr q1, tcPDPtr q2) const {
  return getHadron(q1->id(), q2->id());
}

tcPDPtr FlavourGenerator::getHadron(long iq1, long iq2) const {
  return getHadron(getParticleData(iq1), getParticleData(iq2));
}

AbstractNoPIOClassDescription<FlavourGenerator>
 FlavourGenerator::initFlavourGenerator;

void FlavourGenerator::Init() {}

