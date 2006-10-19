// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantDecayer class.
//

#include "RemnantDecayer.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/RemnantData.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantDecayer::~RemnantDecayer() {}

bool RemnantDecayer::accept(const DecayMode &) const {
  return false;
}

bool RemnantDecayer::needsFullStep() const {
  return true;
}

bool RemnantDecayer::
canHandle(tcPDPtr, const multiset<tcPDPtr> &) const {
  return false;
}

ParticleVector RemnantDecayer::
decay(const DecayMode & dm, const Particle &) const {
  ParticleVector children = dm.produceProducts();
  return children;
}

ParticleVector RemnantDecayer::
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

void RemnantDecayer::persistentOutput(PersistentOStream & ) const {
  // *** ATTENTION *** os << ; // Add all member variable which should be written persistently here.
}

void RemnantDecayer::persistentInput(PersistentIStream & , int) {
  // *** ATTENTION *** is >> ; // Add all member variable which should be read persistently here.
}

ClassDescription<RemnantDecayer> RemnantDecayer::initRemnantDecayer;
// Definition of the static class description member.

void RemnantDecayer::Init() {

  static ClassDocumentation<RemnantDecayer> documentation
    ("There is no documentation for the RemnantDecayer class");

}

