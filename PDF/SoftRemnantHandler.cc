// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SoftRemnantHandler class.
//

#include "SoftRemnantHandler.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/RemnantDecayer.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/EventRecord/RemnantParticle.h"

using namespace ThePEG;

SoftRemnantHandler::SoftRemnantHandler() {}

SoftRemnantHandler::SoftRemnantHandler(const SoftRemnantHandler & x)
  : RemnantHandler(x), remdec(x.remdec) {}

SoftRemnantHandler::~SoftRemnantHandler() {}

void SoftRemnantHandler::doinit() throw(InitException) {
  RemnantHandler::doinit();
}

bool SoftRemnantHandler::
canHandle(tcPDPtr particle, const cPDVector & partons) const {
  if ( !remdec ) return false;
  for ( int i = 0, N = partons.size(); i < N; ++i )
    if ( !remdec->canHandle(particle, partons[i]) ) return false;
  return true;
}

Lorentz5Momentum SoftRemnantHandler::
generate(PartonBinInstance & pb, const double *,
	 Energy2, const LorentzMomentum & parent) const {
  LorentzMomentum p(0.0, 0.0, parent.rho(), parent.e());
  pb.parton()->setMomentum
    (lightCone(p.plus()*pb.x(), 0.0*GeV, 0.0*GeV, 0.0*GeV));
  PPtr rem = new_ptr(RemnantParticle(*pb.particle(), remdec, pb.parton()));
  rem->rotateY(parent.theta());
  rem->rotateZ(parent.phi());
  pb.remnants(PVector(1, rem));
  return parent - rem->momentum();
}

Lorentz5Momentum SoftRemnantHandler::
generate(PartonBinInstance & pb, const double *, Energy2, Energy2,
	 const LorentzMomentum & parent) const {
  return generate(pb, 0, 0.0*GeV2, parent);
}

void SoftRemnantHandler::persistentOutput(PersistentOStream & os) const {
  os << remdec;
}

void SoftRemnantHandler::persistentInput(PersistentIStream & is, int) {
  is >> remdec;
}

void SoftRemnantHandler::setDecayer(RemDecPtr rd) {
  isMultiCapable = rd->multiCapable();
}

ClassDescription<SoftRemnantHandler>
SoftRemnantHandler::initSoftRemnantHandler;

void SoftRemnantHandler::Init() {

  static ClassDocumentation<SoftRemnantHandler> documentation
    ("SoftRemnantHandler inherits from the RemnantHandler and implements "
     "the generation of a single collinear RemnantParticle when anything "
     "is extracted from anything else. Such a RemnantParticle needs to be "
     "decayed by a special RemnantDecayer and the SoftRemnantHandler "
     "needs to be assign such a decayer to work properly.");

  static Reference<SoftRemnantHandler,RemnantDecayer> interfaceRemnantDecayer
    ("RemnantDecayer",
     "A RemnantDecayer object which is able to decay the produced "
     "RemnantParticle objects.",
     &SoftRemnantHandler::remdec, false, false, true, false, true,
     &SoftRemnantHandler::setDecayer);

}
