// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantParticle class.
//

#include "RemnantParticle.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/RemnantDecayer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantParticle.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantParticle::
RemnantParticle(const Particle & particle, RemDecPtr decayer, tPPtr)
  : Particle(new_ptr(RemnantData(particle.dataPtr(), decayer))) {
  remData = const_ptr_cast<tRemPDPtr>(dynamic_ptr_cast<tcRemPDPtr>(dataPtr()));
  set5Momentum(particle.momentum());
}

RemnantParticle::~RemnantParticle() {}

void RemnantParticle::persistentOutput(PersistentOStream & os) const {
  os << remData;
}

void RemnantParticle::persistentInput(PersistentIStream & is, int) {
  is >> remData;
}

ClassDescription<RemnantParticle> RemnantParticle::initRemnantParticle;
// Definition of the static class description member.

void RemnantParticle::Init() {

  static ClassDocumentation<RemnantParticle> documentation
    ("There is no documentation for the RemnantParticle class");

}

