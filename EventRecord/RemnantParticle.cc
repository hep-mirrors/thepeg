// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantParticle class.
//

#include "RemnantParticle.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/RemnantDecayer.h"
#include "ThePEG/EventRecord/MultiColour.h"

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
  colourInfo(new_ptr(MultiColour()));
}

RemnantParticle::~RemnantParticle() {}

bool RemnantParticle::extract(tPPtr parton) {
  LorentzMomentum pnew = momentum() - parton->momentum();
  if ( pnew.e() < 0.0*GeV ) return false;
  if ( !remData->extract(parton->dataPtr()) ) return false;
  extracted.insert(parton);
  setMomentum(pnew);
  fixColourLines(parton);
  return true;
}

bool RemnantParticle::reextract(tPPtr oldp, tPPtr newp) {
  LorentzMomentum pnew = momentum() + oldp->momentum() - newp->momentum();
  if ( pnew.e() < 0.0*GeV ) return false;
  if ( !remData->reextract(oldp->dataPtr(), newp->dataPtr()) ) return false;
  ParticleSet::iterator it = extracted.find(oldp);
  if ( it == extracted.end() ) return false;
  extracted.erase(it);
  extracted.insert(newp);
  if ( oldp == primary ) primary = newp;
  setMomentum(pnew);
  if ( oldp->colourLine() ) oldp->colourLine()->removeAntiColoured(this);
  if ( oldp->antiColourLine() ) oldp->antiColourLine()->removeColoured(this);
  fixColourLines(newp);
  return true;
}

void RemnantParticle::fixColourLines(tPPtr parton) {
  if ( parton->hasColour() ) {
    if ( parton->colourLine() )
      parton->colourLine()->addAntiColoured(this);
    else
      ColourLine::create(parton, this);
  } 
  if ( parton->hasAntiColour() ) {
    if ( parton->antiColourLine() )
      parton->antiColourLine()->addColoured(this);
    else ColourLine::create(this, parton);
  }
}

void RemnantParticle::persistentOutput(PersistentOStream & os) const {
  os << remData << parent << extracted << primary;
}

void RemnantParticle::persistentInput(PersistentIStream & is, int) {
  is >> remData >> parent >> extracted >> primary;
}

ClassDescription<RemnantParticle> RemnantParticle::initRemnantParticle;
// Definition of the static class description member.

void RemnantParticle::Init() {}

