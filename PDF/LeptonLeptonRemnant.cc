// -*- C++ -*-
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
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LeptonLeptonRemnant.tcc"
#endif

using namespace ThePEG;

LeptonLeptonRemnant::LeptonLeptonRemnant()
  : minX(1.0e-10) {}

LeptonLeptonRemnant::LeptonLeptonRemnant(const LeptonLeptonRemnant & x)
  : RemnantHandler(x), minX(x.minX), photon(x.photon) {}

LeptonLeptonRemnant::~LeptonLeptonRemnant() {}

void LeptonLeptonRemnant::doinit() throw(InitException) {
  photon = getParticleData(ParticleID::gamma);
  RemnantHandler::doinit();
}

bool LeptonLeptonRemnant::
canHandle(tcPDPtr particle, const cPDVector & partons) const {
  for ( cPDVector::const_iterator it = partons.begin();
	it != partons.end(); ++it )
    if ( (**it).id() != particle->id() ) return false;
  return true;
}

Lorentz5Momentum LeptonLeptonRemnant::
generate(PartonBinInstance & pb, const double *,
	 Energy2 scale, const LorentzMomentum & parent) const {
  if ( pb.particleData() != pb.partonData() )
    throw RemnantHandlerException
      (pb.particleData()->name(), pb.partonData()->name(), name(),
       "The remnant handler can only extract leptons from "
       "leptons of the same type.");
  if ( pb.eps() < minX ) {
    pb.remnants(PVector());
    return parent;
  }
  LorentzMomentum p(0.0*GeV, 0.0*GeV, parent.rho(), parent.e());
  TransverseMomentum qt;
  Energy2 qt2 = 0.0*GeV2;
  if ( scale >= 0.0*GeV2 ) {
    qt2 = pb.eps()*(pb.xi()*parent.m2() + scale);
    double phi = rnd(2.0*Constants::pi);
    qt = TransverseMomentum(sqrt(qt2)*cos(phi), sqrt(qt2)*sin(phi));
  }
  Energy pl = p.plus()*pb.eps();
  LorentzMomentum prem = lightCone(pl, qt2/pl, qt);
  prem.rotateY(parent.theta());
  prem.rotateZ(parent.phi());
  PPtr rem = photon->produceParticle(prem, 0.0*GeV);
  pb.remnants(PVector(1, rem));
  return parent - rem->momentum();
}

Lorentz5Momentum LeptonLeptonRemnant::
generate(PartonBinInstance & pb, const double *, Energy2 scale, Energy2,
	 const LorentzMomentum & parent) const {
  if ( pb.particleData() != pb.partonData() )
    throw RemnantHandlerException
      (pb.particleData()->name(), pb.partonData()->name(), name(),
       "The remnant handler can only extract leptons from "
       "leptons of the same type.");
  if ( pb.eps() < minX ) {
    pb.remnants(PVector());
    return parent;
  }
  LorentzMomentum p(0.0*GeV, 0.0*GeV, parent.rho(), parent.e());
  TransverseMomentum qt;
  Energy2 qt2 = 0.0*GeV2;
  if ( scale >= 0.0*GeV2 ) {
    qt2 = pb.eps()*(pb.xi()*parent.m2() + scale);
    double phi = rnd(2.0*Constants::pi);
    qt = TransverseMomentum(sqrt(qt2)*cos(phi), sqrt(qt2)*sin(phi));
  }
  Energy pl = p.plus()*pb.eps();
  LorentzMomentum prem = lightCone(pl, qt2/pl, qt);
  prem.rotateY(parent.theta());
  prem.rotateZ(parent.phi());
  PPtr rem = photon->produceParticle(prem, 0.0*GeV);
  pb.remnants(PVector(1, rem));
  return parent - rem->momentum();
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

