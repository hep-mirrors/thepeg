// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantParticle class.
//

#include "RemnantParticle.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/RemnantDecayer.h"
#include "ThePEG/EventRecord/MultiColour.h"
#include "ThePEG/Config/algorithm.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantParticle::
RemnantParticle(const Particle & particle, RemDecPtr decayer, tPPtr parton)
  : Particle(new_ptr(RemnantData(particle.dataPtr(), decayer))) {
  remData = const_ptr_cast<tRemPDPtr>(dynamic_ptr_cast<tcRemPDPtr>(dataPtr()));
  set5Momentum(particle.momentum());
  colourInfo(new_ptr(MultiColour()));
  extract(parton);
  parent = &particle;
}

bool RemnantParticle::extract(tPPtr parton, bool fixcolour) {
  LorentzMomentum pnew = momentum() - parton->momentum();
  if ( pnew.e() < 0.0*GeV ) return false;
  if ( !remData->extract(parton->dataPtr()) ) return false;
  extracted.push_back(parton);
  setMomentum(pnew);
  rescaleMass();
  if ( fixcolour ) fixColourLines(parton);
  return true;
}

bool RemnantParticle::reextract(tPPtr oldp, tPPtr newp, bool fixcolour) {
  LorentzMomentum pnew = momentum() + oldp->momentum() - newp->momentum();
  if ( pnew.e() < 0.0*GeV ) return false;
  PVector::iterator it = find(extracted, oldp);
  if ( it == extracted.end() ) return false;
  if ( !remData->reextract(oldp->dataPtr(), newp->dataPtr()) ) return false;
  extracted[it - extracted.begin()] = newp;
  setMomentum(pnew);
  rescaleMass();
  if ( oldp->colourLine() ) oldp->colourLine()->removeAntiColoured(this);
  if ( oldp->antiColourLine() ) oldp->antiColourLine()->removeColoured(this);
  if ( fixcolour )  fixColourLines(newp);
  return true;
}

bool RemnantParticle::remove(tPPtr oldp) {
  LorentzMomentum pnew = momentum() + oldp->momentum();
  PVector::iterator it = find(extracted, oldp);
  if ( it == extracted.end() ) return false;
  if ( !remData->remove(oldp->dataPtr()) ) return false;
  extracted.erase(it);
  setMomentum(pnew);
  rescaleMass();
  if ( oldp->colourLine() ) oldp->colourLine()->removeAntiColoured(this);
  if ( oldp->antiColourLine() ) oldp->antiColourLine()->removeColoured(this);
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
  os << remData << parent << extracted;
}

void RemnantParticle::persistentInput(PersistentIStream & is, int) {
  is >> remData >> parent >> extracted;
}

ClassDescription<RemnantParticle> RemnantParticle::initRemnantParticle;
// Definition of the static class description member.

void RemnantParticle::Init() {}

