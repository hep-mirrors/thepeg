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

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LeptonLeptonRemnant.tcc"
#endif

using namespace ThePEG;

LeptonLeptonRemnant::LeptonLeptonRemnant() {}

LeptonLeptonRemnant::LeptonLeptonRemnant(const LeptonLeptonRemnant & x)
  : RemnantHandler(x), photon(x.photon) {}

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
generate(PartonBin & pb, const double * r,
	 Energy2 scale, const LorentzMomentum & parent) const {
  if ( pb.particle() != pb.parton() )
    throw RemnantHandlerException
      (pb.particle()->name(), pb.parton()->name(), name(),
       "The remnant handler can only extract leptons from "
       "leptons of the same type.");
  LorentzMomentum p(0.0, 0.0, parent.rho(), parent.e());
  TransverseMomentum qt;
  Energy2 qt2 = 0.0*GeV2;
  if ( scale >= 0.0*GeV2 ) {
    qt2 = pb.lastPartialEps()*(pb.lastPartialX()*parent.m2() + scale);
    double phi = rnd(2.0*Constants::pi);
    qt = TransverseMomentum(sqrt(qt2)*cos(phi), sqrt(qt2)*sin(phi));
  }
  Energy pl = p.plus()*pb.lastPartialEps();
  PPtr rem = 
    photon->produceParticle(lightCone(pl, qt2/pl, qt));
  rem->rotateY(parent.theta());
  rem->rotateZ(parent.phi());
  pb.lastRemnants(PVector(1, rem));
  return parent - rem->momentum();
}

void LeptonLeptonRemnant::persistentOutput(PersistentOStream & os) const {
  os << photon;
}

void LeptonLeptonRemnant::persistentInput(PersistentIStream & is, int) {
  is >> photon;
}

ClassDescription<LeptonLeptonRemnant>
LeptonLeptonRemnant::initLeptonLeptonRemnant;

void LeptonLeptonRemnant::Init() {}

