// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinBase class.
//

#include "SpinBase.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinBase.tcc"
#endif

using namespace ThePEG;

SpinBase::~SpinBase() {}

bool SpinBase::hasPolarization() const {
  return false;
}

DPair SpinBase::polarization() const {
  return DPair();
}

void SpinBase::transform(const LorentzMomentum &, LorentzRotation r) {}

NoPIOClassDescription<SpinBase> SpinBase::initSpinBase;

void SpinBase::Init() {}

