// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BreitWignerMass class.
//

#include "BreitWignerMass.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/CLHEPWrap/RandBreitWigner.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BreitWignerMass.tcc"
#endif

using namespace ThePEG;

BreitWignerMass::~BreitWignerMass() {}

Energy BreitWignerMass::mass(const ParticleData & pd) const {
  return RandBreitWigner::shootM2(&(generator()->randomEngine()), pd.mass()/GeV,
				  pd.width()/GeV, pd.widthCut()/GeV)*GeV;
}

NoPIOClassDescription<BreitWignerMass> BreitWignerMass::initBreitWignerMass;

void BreitWignerMass::Init() {}

