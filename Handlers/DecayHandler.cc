// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DecayHandler class.
//

#include "DecayHandler.h"
#include "CollisionHandler.h"
#include "Hint.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/PDT/Decayer.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/Step.h"
#include "ThePEG/EventRecord/Collision.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DecayHandler.tcc"
#endif

using namespace ThePEG;

DecayHandler::~DecayHandler() {}

void DecayHandler::
handle(PartialCollisionHandler & ch, const tPVector & tagged,
       const Hint & hint) ThePEG_THROW_SPEC((Veto, Stop, Exception)) {
  // First go through to see which of the tagged particles should be
  // decayed: Exit if none are found.
  Timer<46> timer("DecayHandler::handle");
  tPVector parents;
  for ( int i = 0, N = tagged.size(); i < N; ++i )
    if ( tagged[i] && !tagged[i]->data().stable() )
      parents.push_back(tagged[i]);

  if ( parents.empty() ) return;

  // Create a new step, decay all particles and add their children in
  // the new step.
  tStepPtr newStep = ch.newStep();
  for ( int i = 0, N = parents.size(); i < N; ++i )
    performDecay(newStep->find(parents[i]), *newStep);
}

void DecayHandler::
performDecay(tPPtr parent, Step & s) const
  ThePEG_THROW_SPEC((Veto, Exception)) {
  Timer<47> timer("DecayHandler::performDecay");
  long ntry = 0;
  while ( 1 ) {
    if ( ++ntry >= maxLoop() )
      throw DecHdlDecayFailed(parent->data(), maxLoop());
    tDMPtr dm = parent->data().selectMode(*parent);
    if ( !dm ) throw DecHdlNoDecayMode(parent->data());
    if ( !dm->decayer() ) throw DecHdlNoDecayer(parent->data(), *dm);
    try {
      ParticleVector children = dm->decayer()->decay(*dm, *parent);
      if ( !children.empty() ) {
	parent->decayMode(dm);
	for ( int i = 0, N = children.size(); i < N; ++i )
	  if ( !s.addDecayProduct(parent, children[i]) )
	    throw DecHdlChildFail(parent->data(), children[i]->data());
	for ( int i = 0, N = children.size(); i < N; ++i )
	  if ( !children[i]->data().stable() ) performDecay(children[i], s);
	return;
      }
    }
    catch (DecHdlChildFail) {
      throw;
    }
    catch (Veto) {}
  }
}

void DecayHandler::persistentOutput(PersistentOStream & os) const {
  os << theMaxLoop;
}

void DecayHandler::persistentInput(PersistentIStream & is, int) {
  is >> theMaxLoop;
}

ClassDescription<DecayHandler> DecayHandler::initDecayHandler;

void DecayHandler::Init() {
  static Parameter<DecayHandler,long> interfaceMaxLoop
    ("MaxLoop",
     "The maximum number of attempts per event when selecting a sub-process.",
     &DecayHandler::theMaxLoop, 100000, 100, 100000000, true, false, true);
}

DecHdlNoDecayMode::DecHdlNoDecayMode(const Interfaced & p) {
  theMessage << "An error occurred when trying to decay an unstable particle "
	     << "of type '" << p.name() << "'. No decay mode was found.";
  severity(runerror);
}

DecHdlNoDecayer::DecHdlNoDecayer(const Interfaced & p, const Interfaced & dm) {
  theMessage << "An error occurred when tryin to decay an unstable particle "
	     << "of type '" << p.name() << "'. The selected decay mode ("
	     << dm.name() << ") did not have a decayer associated with it.";
  severity(runerror);
}

DecHdlDecayFailed::DecHdlDecayFailed(const Interfaced & p, long n) {
  theMessage << "A possibly infinit loop was encountered while tryin to "
	     << "decay an unstable particle of type '" << p.name()
	     << "'. No acceptable decay mode found."
	     << "before reaching the limit of " << n << "iterations.";
  severity(eventerror);
}
  
DecHdlChildFail::DecHdlChildFail(const Interfaced & p, const Interfaced & c) {
  theMessage << "An error occurred when tryin to decay an unstable particle "
	     << "of type '" << p.name() << "'. One of the produced children "
	     << "(of type '" << c.name() << "') could not be added to the "
	     << "current step.";
  severity(abortnow);
}
