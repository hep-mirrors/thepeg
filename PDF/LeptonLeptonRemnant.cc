// -*- C++ -*-
//
// LeptonLeptonRemnant.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LeptonLeptonRemnant class.
//

#include "LeptonLeptonRemnant.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/Maths.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

IBPtr LeptonLeptonRemnant::clone() const {
  return new_ptr(*this);
}

IBPtr LeptonLeptonRemnant::fullclone() const {
  return new_ptr(*this);
}

LeptonLeptonRemnant::LeptonLeptonRemnant()
  : minX(1.0e-10) {}

void LeptonLeptonRemnant::doinit() throw(InitException) {
  photon = getParticleData(ParticleID::gamma);
  RemnantHandler::doinit();
}

bool LeptonLeptonRemnant::
canHandle(tcPDPtr particle, const cPDVector & partons) const {
  for ( cPDVector::const_iterator it = partons.begin(); it != partons.end(); ++it ) {
    if ( (**it).id() != particle->id()    &&
	 (**it).id() != ParticleID::gamma ) return false;
  }
  return true;
}

Lorentz5Momentum LeptonLeptonRemnant::
generate(PartonBinInstance & pb, const double *,
	 Energy2 scale, const LorentzMomentum & parent) const {
  // photon into hard process and lepton remnant
  if ( pb.particleData() != pb.partonData() && 
       pb.partonData()->id() == ParticleID::gamma) {
    Energy  ppl = pb.xi()*(abs(parent.z())+parent.t());
    Energy2 qt2 = pb.eps()*scale-sqr(pb.xi()*parent.m());
    Energy  pmi = (qt2-scale)/ppl;
    Lorentz5Momentum pgam;
    pgam.setMass(-sqrt(scale));
    pgam.setT(0.5*(ppl+pmi));
    if(parent.z() < ZERO) 
      pgam.setZ(-0.5*(ppl-pmi));
    else
      pgam.setZ(0.5*(ppl-pmi));
    double phi = rnd(2.0*Constants::pi);
    pgam.setX(sqrt(qt2)*cos(phi));
    pgam.setY(sqrt(qt2)*sin(phi));
    pgam.rotateY(parent.theta());
    pgam.rotateZ(parent.phi());
    Lorentz5Momentum prem=parent-pgam;
    PPtr rem = pb.particleData()->produceParticle(prem, pb.particleData()->mass());
    pb.remnants(PVector(1, rem));
    return pgam;
  }
  else if( pb.particleData() == pb.partonData() ) {
    if ( pb.eps() < minX ) {
      pb.remnants(PVector());
      return parent;
    }
    LorentzMomentum p(ZERO, ZERO, parent.rho(), parent.e());
    TransverseMomentum qt;
    Energy2 qt2 = ZERO;
    if ( scale >= ZERO ) {
      qt2 = pb.eps()*(pb.xi()*parent.m2() + scale);
      double phi = rnd(2.0*Constants::pi);
      qt = TransverseMomentum(sqrt(qt2)*cos(phi), sqrt(qt2)*sin(phi));
    }
    Energy pl = p.plus()*pb.eps();
    LorentzMomentum prem = lightCone(pl, qt2/pl, qt);
    prem.rotateY(parent.theta());
    prem.rotateZ(parent.phi());
    PPtr rem = photon->produceParticle(prem, ZERO);
    pb.remnants(PVector(1, rem));
    return parent - rem->momentum();
  }
  else {
    if ( pb.particleData() != pb.partonData() )
      throw RemnantHandlerException
	(pb.particleData()->name(), pb.partonData()->name(), name(),
	 "The remnant handler can only extract leptons from "
	 "leptons of the same type or photons.");
    else
      throw RemnantHandlerException
	(pb.particleData()->name(), pb.partonData()->name(), name(),
	 "Should not get here.");
  }
}

Lorentz5Momentum LeptonLeptonRemnant::
generate(PartonBinInstance & pb, const double *, Energy2 scale, Energy2,
	 const LorentzMomentum & parent) const {
  // photon into hard process and lepton remnant
  if ( pb.particleData() != pb.partonData() && 
       pb.partonData()->id() == ParticleID::gamma) {
    Energy  ppl = pb.xi()*(abs(parent.z())+parent.t());
    Energy2 qt2 = pb.eps()*scale-sqr(pb.xi()*parent.m());
    Energy  pmi = (qt2-scale)/ppl;
    Lorentz5Momentum pgam;
    pgam.setMass(-sqrt(scale));
    pgam.setT(0.5*(ppl+pmi));
    if(parent.z() < ZERO)
      pgam.setZ(-0.5*(ppl-pmi));
    else
      pgam.setZ(0.5*(ppl-pmi));
    double phi = rnd(2.0*Constants::pi);
    pgam.setX(sqrt(qt2)*cos(phi));
    pgam.setY(sqrt(qt2)*sin(phi));
    pgam.rotateY(parent.theta());
    pgam.rotateZ(parent.phi());
    Lorentz5Momentum prem=parent-pgam;
    PPtr rem = pb.particleData()->produceParticle(prem, pb.particleData()->mass());
    pb.remnants(PVector(1, rem));
    return pgam;
  }
  else if ( pb.particleData() == pb.partonData() ) {
    if ( pb.eps() < minX ) {
      pb.remnants(PVector());
      return parent;
    }
    LorentzMomentum p(ZERO, ZERO, parent.rho(), parent.e());
    TransverseMomentum qt;
    Energy2 qt2 = ZERO;
    if ( scale >= ZERO ) {
      qt2 = pb.eps()*(pb.xi()*parent.m2() + scale);
      double phi = rnd(2.0*Constants::pi);
      qt = TransverseMomentum(sqrt(qt2)*cos(phi), sqrt(qt2)*sin(phi));
    }
    Energy pl = p.plus()*pb.eps();
    LorentzMomentum prem = lightCone(pl, qt2/pl, qt);
    prem.rotateY(parent.theta());
    prem.rotateZ(parent.phi());
    PPtr rem = photon->produceParticle(prem, ZERO);
    pb.remnants(PVector(1, rem));
    return parent - rem->momentum();
  }
  else {
    if ( pb.particleData() != pb.partonData() )
      throw RemnantHandlerException
	(pb.particleData()->name(), pb.partonData()->name(), name(),
	 "The remnant handler can only extract leptons from "
	 "leptons of the same type or photons.");
    else
      throw RemnantHandlerException
	(pb.particleData()->name(), pb.partonData()->name(), name(),
	 "Should not get here.");
  }
}

void LeptonLeptonRemnant::persistentOutput(PersistentOStream & os) const {
  os << photon << minX;
}

void LeptonLeptonRemnant::persistentInput(PersistentIStream & is, int) {
  is >> photon >> minX;
}

ClassDescription<LeptonLeptonRemnant>
LeptonLeptonRemnant::initLeptonLeptonRemnant;

void LeptonLeptonRemnant::Init() {

  static ClassDocumentation<LeptonLeptonRemnant> documentation
    ("LeptonLeptonRemnant inherits from the RemnantHandler and implements "
     "the generation of a single collinear photon remnant when a lepton is "
     "extracted from a lepton.");

  static Parameter<LeptonLeptonRemnant,double> interfaceMinX
    ("MinX",
     "The minimum energy fraction allowed for a photon remnant. "
     "If less than this no remnant will be emitted.",
     &LeptonLeptonRemnant::minX, 1.0e-10, 0.0, 1.0,
     true, false, true);

  interfaceMinX.rank(10);

}

