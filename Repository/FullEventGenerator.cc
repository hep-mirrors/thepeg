// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FullEventGenerator class.
//

#include "FullEventGenerator.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/Utilities/HoldFlag.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Handlers/AnalysisHandler.h"
#include "ThePEG/Handlers/EventManipulator.h"
#include "ThePEG/Handlers/LuminosityFunction.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FullEventGenerator.tcc"
#endif

using namespace ThePEG;

FullEventGenerator::FullEventGenerator()
  : printEvent(0), dumpPeriod(0), debugEvent(0) {}

FullEventGenerator::FullEventGenerator(const FullEventGenerator & x)
  : EventGenerator(x), theEventHandler(x.theEventHandler),
    theAnalysisHandlers(x.theAnalysisHandlers),
    theEventManipulator(x.theEventManipulator),
    printEvent(x.printEvent), dumpPeriod(x.dumpPeriod),
    debugEvent(x.debugEvent) {}

FullEventGenerator::~FullEventGenerator() {}

tcEventPtr FullEventGenerator::currentEvent() const {
  return eventHandler()->currentEvent();
}

void FullEventGenerator::doinit() throw(InitException) {
  // First initialize the base class
  EventGenerator::doinit();

  // Then initialize the Event Handler calculating initial cross
  // sections and stuff.
  eventHandler()->initialize();
}

void FullEventGenerator::doinitrun() {
  // First initialize the base class
  EventGenerator::doinitrun();

}

void FullEventGenerator::dofinish() {
  // first write out statistics from the event handler.
  eventHandler()->statistics(out());
  // Then call finish for the base class.
  EventGenerator::dofinish();
}

EventPtr FullEventGenerator::doShoot() {
  EventPtr event;
  if ( N() >= 0 && ++ieve > N() ) return event;
  HoldFlag<int> debug(Debug::level, theDebugLevel);
  do { 
    int state = 0;
    int loop = 1;
    eventHandler()->clearEvent();
    try {
      do {
	// Generate a full event or part of an event
	if ( eventHandler()->empty() ) event = eventHandler()->generateEvent();
	else event = eventHandler()->continueEvent();

	if ( eventHandler()->empty() ) loop = -loop;
	
	// Analyze the possibly uncomplete event
	for ( AnalysisVector::iterator it = analysisHandlers().begin();
	      it != analysisHandlers().end(); ++it )
	  (**it).analyze(event, ieve, loop, state);
	
	// Manipulate the current event, possibly deleting some steps
	// and telling the event handler to redo them.
	if ( manipulator() )
	  state = manipulator()->manipulate(eventHandler(), event);
	
	// If the event was not completed, continue generation and continue.
	loop = abs(loop) + 1;
      } while ( !eventHandler()->empty() );
    }
    catch (Exception & ex) {
      if ( logException(ex, eventHandler()->currentEvent()) ) throw;
    }
    catch (...) {
      dump();
      event = eventHandler()->currentEvent();
      if ( event )
	log() << *event;
      else
	log() << "An exception occurred before any event object was created!";
      log() << endl;
      throw;
    }
    if ( ThePEG_DEBUG_LEVEL ) {
      if ( ( ThePEG_DEBUG_LEVEL == Debug::printEveryEvent ||
	     ieve < printEvent ) && event ) log() << *event;
      if ( debugEvent > 0 && ieve + 1 >= debugEvent )
	Debug::level = Debug::full;
      if ( dumpPeriod > 0 && ieve%dumpPeriod == 0 ) dump();
    }
  } while ( !event );
  return event;
}

EventPtr FullEventGenerator::doPartialEvent(tEventPtr e) {
  if ( N() >= 0 && ++ieve > N() ) return EventPtr();
  EventPtr event = e;
  try {
    event = eventHandler()->partialCollision(e);
  }
  catch (Exception & ex) {
    if ( logException(ex, eventHandler()->currentEvent()) ) throw;
  }
  catch (...) {
    dump();
    event = eventHandler()->currentEvent();
    if ( !event ) event = e;
    log() << *event << endl;
    throw;
  }
  return event;
}

Energy FullEventGenerator::maximumCMEnergy() const {
  tcEHPtr eh = eventHandler();
  return eh->lumiFn().maximumCMEnergy();
}

void FullEventGenerator::persistentOutput(PersistentOStream & os) const {
  os << theEventHandler << theAnalysisHandlers << theEventManipulator
     << printEvent << dumpPeriod << debugEvent;
}

void FullEventGenerator::persistentInput(PersistentIStream & is, int) {
  is >> theEventHandler >> theAnalysisHandlers >> theEventManipulator
     >> printEvent >> dumpPeriod >> debugEvent;
}

ClassDescription<FullEventGenerator> FullEventGenerator::initFullEventGenerator;

void FullEventGenerator::Init() {

  static Reference<FullEventGenerator,EventHandler> interfaceEventHandler
    ("EventHandler",
     "The \\class{EventHandler} object to be used to generate the individual "
     "events in this run.",
     &FullEventGenerator::theEventHandler, false, false, true, false);

  static RefVector<FullEventGenerator,AnalysisHandler> interfaceAnalysisHandlers
    ("AnalysisHandlers",
     "\\class{AnalysisHandler} objects to be used to analyze the produced "
     "events in this run.",
     &FullEventGenerator::theAnalysisHandlers, 0, true, false, true, false);

  static Reference<FullEventGenerator,EventManipulator> interfaceEventManip
    ("EventManipulator",
     "An \\class{EventManipulator} called each time the generation of an "
     "event is stopped. The \\class{EventManipulator} object is able to "
     "manipulate the generated event, as opposed to an "
     "\\class{AnalysisHandler} which may only look at the event.",
     &FullEventGenerator::theEventManipulator, true, false, true, true);

  static Parameter<FullEventGenerator,int> interfacePrintEvent
    ("PrintEvent",
     "If the debug level is above zero, print the first 'PrintEvent' events.",
     &FullEventGenerator::printEvent, 0, 0, 1000, true, false, true);

  static Parameter<FullEventGenerator,long> interfaceDumpPeriod
    ("DumpPeriod",
     "If the debug level is above zero, dump the full state of the run every "
     "'DunpPeriod' events.",
     &FullEventGenerator::dumpPeriod, 0, 0, Constants::MaxInt,
     true, false, true);

  static Parameter<FullEventGenerator,long> interfaceDebugEvent
    ("DebugEvent",
     "If the debug level is above zero, step up to the highest debug level "
     "befor event number 'DebugEvent'.",
     &FullEventGenerator::debugEvent, 0, 0, Constants::MaxInt,
     true, false, true);

}

