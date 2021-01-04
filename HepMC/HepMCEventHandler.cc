// -*- C++ -*-
//
//


#include "HepMCEventHandler.h"
#include "HepMCReader.h"
/* #include "ThePEG/" */
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Utilities/Throw.h"
#include "ThePEG/Utilities/Debug.h"

#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/CascadeHandler.h"
/* #include "ThePEG/Cuts/Cuts.h" */
#include "ThePEG/PDF/PartonExtractor.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"



using namespace ThePEG;

HepMCEventHandler::~HepMCEventHandler() {}


IBPtr HepMCEventHandler::clone() const {
  return new_ptr(*this);
}

IBPtr HepMCEventHandler::fullclone() const {
  return new_ptr(*this);
}


void HepMCEventHandler::doinit() {
  EventHandler::doinit();

}

void HepMCEventHandler::doinitrun() {
  // init reader
  EventHandler::doinitrun();
  /* reader.initialize(*this); */
}


void HepMCEventHandler::dofinish() {
  EventHandler::dofinish();
}

void HepMCEventHandler::initialize() {

  if ( !reader() )
    Throw<HepMCInitError> ()
      << "No reader were defined for the HepMCEventHandler '"
      << name() << "'" << Exception::warning;
  reader()->initialize(*this);

  PDPair incoming;
  //TODO: just a work around
  // set incoming particles fixed to protons
  incoming.first = getParticleData(2212);
  incoming.second = getParticleData(2212);

  theIncoming = incoming;
}

EventPtr HepMCEventHandler::generateEvent() {
  while( reader()->readEvent() ) {
    /* Throw<HepMCOpenError> () */
    /*   << "Couldn't read event from file " << reader()->filename() << "." */
    /*   << Exception::runerror; */
    // TODO: Don't know if this works, in LesHouchesEventHandler LastXCombInfo::lastParticles
    try {
      theLastXComb = reader()->getXComb();
      // is used to access the incoming particles
      /* PPair inParts = PPair(reader()->incoming()[0], reader()->incoming()[1]); */
      PPair inParts = PPair(reader()->incoming().first, reader()->incoming().second);
      currentEvent(new_ptr(Event(inParts, this, generator()->runName(),
              generator()->currentEventNumber())));

      //TODO: not working right now
      performCollision();
      //TODO: addParticles is a portected function
      /* currentEvent()->addParticles(reader()->outgoing().begin(), reader()->outgoing().end()); */

      return currentEvent();
    }
    catch (Stop) {
    }
    catch (Exception &) {
      throw;
    }
  }
}

tCollPtr HepMCEventHandler::performCollision() {
  lastExtractor()->select(lastXCombPtr());
  if ( CKKWHandler() ) CKKWHandler()->setXComb(lastXCombPtr());
  /* PPair inParts = PPair(reader()->incoming()[0], reader()->incoming()[1]); */
  /* PPair inParts = PPair(reader()->incoming().first, reader()->incoming().second); */
  currentCollision(new_ptr(Collision(lastParticles(), currentEvent(), this)));

  if ( currentEvent() ) currentEvent()->addCollision(currentCollision());
  currentStep(new_ptr(Step(currentCollision(), this)));
  currentCollision()->addStep(currentStep());
  //TODO: need XComb with partons
  currentStep()->addSubProcess(reader()->getSubProcess());
  lastExtractor()->constructRemnants(lastXCombPtr()->partonBinInstances(),
      subProcess(), currentStep());
  /* if ( !currentReader()->cuts().passCuts(*currentCollision()) ) throw Veto(); */

  initGroups();
  if ( ThePEG_DEBUG_ITEM(1) ) {
    if ( currentEvent() )
      generator()->logfile() << *currentEvent();
    /* else */
    /*   generator()->logfile() << *currentCollision(); */
  }

  return continueCollision();
}

EventPtr HepMCEventHandler::continueEvent() {
  // TODO: Don't know at all if this will work
  try {
    continueCollision();
  }
  catch (Veto) {
  }
  catch (Stop) {
  }
  catch (Exception &) {
    throw;
  }
  return currentEvent();
}

void HepMCEventHandler::persistentOutput(PersistentOStream & os) const {
  os << theReader << theIncoming;
}

void HepMCEventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theReader >> theIncoming;
}

ClassDescription<HepMCEventHandler> HepMCEventHandler::initHepMCEventHandler;
// Definition of the static class description member.

// init function
// with these paramters it is possible to set option in
// in file
void HepMCEventHandler::Init() {
  static ClassDocumentation<HepMCEventHandler> documentation
    ("This is the main class administrating the event read "
     "by ThePEG::HepMCReader object.");

  /* stores the reader Object */
  static Reference<HepMCEventHandler,HepMCReader> interfaceHepMCReader
    ("HepMCReader",
     "Object for reading HepMC files",
     &HepMCEventHandler::theReader,
     true, false, true, true, false);
  /* TODO: more options */

  /* static Reference<EventHandler,PartonExtractor> interfacePartonExtractor */
  /*   ("PartonExtractor", */
  /*    "A PartonExtractor object to be used by subclasses which do not " */
  /*    "provide their own. Note that this may be overridden by subclasses.", */
  /*    &EventHandler::thePartonExtractor, true, false, true, true, false); */

}
