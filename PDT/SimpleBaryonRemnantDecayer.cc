// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleBaryonRemnantDecayer class.
//

#include "SimpleBaryonRemnantDecayer.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/StandardMatchers.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleBaryonRemnantDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleBaryonRemnantDecayer::~SimpleBaryonRemnantDecayer() {}

bool SimpleBaryonRemnantDecayer::
canHandle(tcPDPtr particle, tcPDPtr parton) const {
  return BaryonMatcher::Check(*particle) &&
    StandardQCDPartonMatcher::Check(*parton);
}

ParticleVector SimpleBaryonRemnantDecayer::
decay(const DecayMode & dm, const Particle & p, Step &) const {
  ParticleVector children;
  tcRemPPtr remnant = dynamic_ptr_cast<tcRemPPtr>(&p);
  if ( !remnant ) return children;
  tRemPDPtr rpd = data(remnant);
  PVector ex = extracted(remnant);
  tPPtr par = parent(remnant);
  if ( !par || ex.empty() || !rpd ) return children;
  children= dm.produceProducts();
  return children;
}

void SimpleBaryonRemnantDecayer::
persistentOutput(PersistentOStream &) const {
}

void SimpleBaryonRemnantDecayer::
persistentInput(PersistentIStream &, int) {
}

ClassDescription<SimpleBaryonRemnantDecayer> SimpleBaryonRemnantDecayer::initSimpleBaryonRemnantDecayer;
// Definition of the static class description member.

void SimpleBaryonRemnantDecayer::Init() {

  static ClassDocumentation<SimpleBaryonRemnantDecayer> documentation
    ("The SimpleBaryonRemnantDecayer class inherits from the RemnantDecayer "
     "class and is able to decay RemnantParticles produced by the "
     "SoftRemnantHandler class for the cases when a single parton has been "
     "extracted from a baryon.");

}

