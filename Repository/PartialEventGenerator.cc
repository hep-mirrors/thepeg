// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PartialEventGenerator class.
//

#include "PartialEventGenerator.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Handlers/PartialCollisionHandler.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Interface/Reference.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialEventGenerator.tcc"
#endif

using namespace ThePEG;

PartialEventGenerator::PartialEventGenerator() {}

PartialEventGenerator::
PartialEventGenerator(const PartialEventGenerator & x)
  : EventGenerator(x), theHandler(x.theHandler) {}

PartialEventGenerator::~PartialEventGenerator() {}

EventPtr PartialEventGenerator::doShoot() {
  return EventPtr();
}

tcEventPtr PartialEventGenerator::currentEvent() const {
  return handler()->currentEvent();
}

EventPtr PartialEventGenerator::doPartialEvent(tEventPtr e) {
  if ( N() >= 0 && ++ieve > N() ) return EventPtr();
  EventPtr event = e;
  try {
    event = handler()->partialCollision(e);
  }
  catch (Exception & ex) {
    if ( logException(ex, handler()->currentEvent()) ) throw;
  }
  catch (...) {
    dump();
    event = handler()->currentEvent();
    if ( event ) event = e;
      log() << *event << endl;
    throw;
  }
  return event;
}

void PartialEventGenerator::persistentOutput(PersistentOStream & os) const {
  os << theHandler;
}

void PartialEventGenerator::persistentInput(PersistentIStream & is, int) {
  is >> theHandler;
}

ClassDescription<PartialEventGenerator>
PartialEventGenerator::initPartialEventGenerator;

void PartialEventGenerator::Init() {

  static Reference<PartialEventGenerator,PartialCollisionHandler> interfaceHdl
    ("PartialCollisionHandler",
     "The \\class{PartialCollisionHandler} object to be used to generate "
     "the individual events in this run.",
     &PartialEventGenerator::theHandler, false, false, true, false);

}

