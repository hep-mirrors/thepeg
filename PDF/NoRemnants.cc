// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NoRemnants class.
//

#include "NoRemnants.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/EventRecord/Particle.h"
#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoRemnants.tcc"
#endif

using namespace ThePEG;

NoRemnants::~NoRemnants() {}

PVector NoRemnants::
getRemnants(const PartonBin & pb, Energy2 sMax, TransverseMomentum & kt,
	    const PVector & prev) const {
  if ( pb.particle() != pb.parton() || pb.lastPartialL() > 0.0 )
    throw RemnantHandlerException
      (pb.particle()->name(), pb.parton()->name(), name(),
       "This remnant handler cannot handle any remnants!");
  return PVector();
}


Lorentz5Momentum NoRemnants::
generate(PartonBin & pb, const double * r,
	 Energy2 scale, const LorentzMomentum & p) const {
  if ( pb.particle() != pb.parton() || pb.lastPartialL() > 0.0 )
    throw RemnantHandlerException
      (pb.particle()->name(), pb.parton()->name(), name(),
       "This remnant handler cannot handle any remnants!");
  return p;
}

Lorentz5Momentum NoRemnants::
generate(PartonBinInstance & pb, const double * r,
	 Energy2 scale, const LorentzMomentum & p) const {
  if ( pb.particleData() != pb.partonData() || pb.li() > 0.0 )
    throw RemnantHandlerException
      (pb.particleData()->name(), pb.partonData()->name(), name(),
       "This remnant handler cannot handle any remnants!");
  return p;
}

NoPIOClassDescription<NoRemnants> NoRemnants::initNoRemnants;

void NoRemnants::Init() {}

