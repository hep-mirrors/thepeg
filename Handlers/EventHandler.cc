// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the EventHandler class.
//

#include "EventHandler.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/Hint.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Handlers/MultipleInteractionHandler.h"
#include "ThePEG/Handlers/HadronizationHandler.h"
#include "ThePEG/Handlers/DecayHandler.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Handlers/KinematicalCuts.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/LuminosityFunction.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventHandler.tcc"
#endif

using namespace ThePEG;

EventHandler::EventHandler(bool warnincomplete)
: theMaxLoop(100000), theStatLevel(2), warnIncomplete(warnincomplete) {
  setupGroups();
}

EventHandler::
EventHandler(const EventHandler & x)
  : HandlerBase(x), LastXCombInfo<>(x),
    theMaxLoop(x.theMaxLoop), theStatLevel(x.theStatLevel),
    theLumiFn(x.theLumiFn), theKinematicalCuts(x.theKinematicalCuts),
    thePartonExtractor(x.thePartonExtractor),
    theSubprocessGroup(x.theSubprocessGroup),
    theCascadeGroup(x.theCascadeGroup), theMultiGroup(x.theMultiGroup),
    theHadronizationGroup(x.theHadronizationGroup),
    theDecayGroup(x.theDecayGroup), warnIncomplete(x.warnIncomplete),
    theIncoming(x.theIncoming) {
  setupGroups();
}

EventHandler::~EventHandler() {}

void EventHandler::lumiFn(LumiFnPtr newLumiFn) {
  if ( newLumiFn->canHandle(incoming()) ) theLumiFn = newLumiFn;
  else throw LumiFuncError()
    << "Cannot use '" << newLumiFn->name()
    << "' as the luminosity function in the event handler '" << name()
    << "' since it cannot handle the requested incoming particles."
    << Exception::warning;
}

void EventHandler::setupGroups() {
  theGroups.clear();
  theGroups.push_back(&theSubprocessGroup);
  theGroups.push_back(&theCascadeGroup);
  theGroups.push_back(&theMultiGroup);
  theGroups.push_back(&theHadronizationGroup);
  theGroups.push_back(&theDecayGroup);
  optGroups.clear();
  optGroups.push_back(&optSubprocessGroup);
  optGroups.push_back(&optCascadeGroup);
  optGroups.push_back(&optMultiGroup);
  optGroups.push_back(&optHadronizationGroup);
  optGroups.push_back(&optDecayGroup);
}

void EventHandler::initGroups() {
  for ( unsigned int i = 0; i < groups().size(); ++i )
    groups()[i]->init(*optGroups[i]);
}

EventPtr EventHandler::generateEvent() {
  throw EventHandlerIncompleteError()
    << "The function generateEvent() was called for the EventHandler '" << name()
    << "' which is not capable of generating complete events."
    << Exception::runerror;
  return EventPtr();
}

tEventPtr EventHandler::generateEvent(tStepPtr s) {
  EventPtr e = new_ptr(Event(PPair(), tcEventBasePtr(), generator()->runName(),
			     generator()->currentEventNumber()));
  e->newCollision()->addStep(s);
  return generateEvent(tEventPtr(e));
}

tEventPtr EventHandler::generateEvent(tEventPtr e) {
  clearEvent();
  e->setInfo(this, generator()->runName(),
	     generator()->currentEventNumber(), 1.0);
  currentEvent(e);
  if ( e->collisions().empty() || !e->collisions().back()->finalStep()) {
    throw EventHandlerIncompleteError()
      << "The function generateEvent() was called with an empty Event "
      << "for the EventHandler '" << name()
      << "' which is not capable of generating complete events."
      << Exception::runerror;
  }
  currentCollision(e->collisions().back());
  currentStep(currentCollision()->finalStep());
  EventHandler::initGroups();
  continueCollision();
  return currentEvent();
}

tCollPtr EventHandler::continueCollision() {
  Timer<45> timer("EventHandler::continueCollision()");
  generator()->currentEventHandler(this);
  while (1) {
    bool done = true;
    for ( GroupVector::iterator git = groups().begin();
	  git != groups().end(); ++git ) {
      HandlerGroupBase & group = **git;
      HandlerGroupBase::StepWithHint sh;
      sh = group.next();
      if ( !group.empty() ) {
	performStep(sh.first, sh.second);
	done = false;
	break;
      }
    }
    if ( done ) break;
  }
  return currentCollision();
}

void EventHandler::clearEvent() {
  for ( GroupVector::const_iterator git = groups().begin();
	git != groups().end(); ++git ) (**git).clear();
}

bool EventHandler::empty() const {
  for ( GroupVector::const_iterator git = groups().begin();
	git != groups().end(); ++git )
    if ( !(**git).empty() ) return false;
  return true;
}

void EventHandler::
performStep(tStepHdlPtr handler, tHintPtr hint) {
  if ( !lastXCombPtr() ) theLastXComb = new_ptr(XComb());

  if ( hint->stop() ) throw Stop();
  tStepPtr oldStep = currentStep();
  currentStepHandler(handler);
  handler->eventHandler(this);
  try {
    generator()->currentStepHandler(handler);
    handler->handle(*this, hint->tagged(*oldStep), *hint);
    generator()->currentStepHandler(tStepHdlPtr());
  }
  catch (...) {
    generator()->currentStepHandler(tStepHdlPtr());
    if ( oldStep != currentStep() ) popStep();
    throw;
  }

  while ( currentStep()->nullStep() ) popStep();
      
  if ( ThePEG_DEBUG_ITEM(2) && oldStep != currentStep() )
    generator()->logfile() << *currentStep();
}

void EventHandler::
addStep(Group::Level level, Group::Handler group, tStepHdlPtr s, tHintPtr h) {
  if ( !h ) h = Hint::Default();
  switch ( level ) {
  case Group::main:
    if ( s && !groups()[group]->setHandler(s, *optGroups[group]) )
      throw EventHandlerStepError()
	<< "Cannot add the StepHandler '" << s->name()
	<< "' to the list of step handlers in the EventHandler '" << name()
	<< "' because it is not of class '" << groups()[group]->handlerClass()
	<< "'." << Exception::abortnow;
    groups()[group]->addHint(h, *optGroups[group]);
    break;
  case Group::before:
    groups()[group]->addPreHandler(s, h, *optGroups[group]);
    break;
  case Group::after:
    groups()[group]->addPostHandler(s, h, *optGroups[group]);
    break;
  }
  for ( long gr = group + 1; gr <= Group::decay; ++gr )
    groups()[gr]->addHint(Hint::Default(), *optGroups[group]);
}

void EventHandler::throwCurrent() {
  clean();
}

void EventHandler::clean() {
  currentEvent(EventPtr());
  currentCollision(CollPtr());
  currentStep(StepPtr());
}

void EventHandler::statistics(ostream &) const {}

void EventHandler::initialize() {}

EventPtr EventHandler::continueEvent() {
  try {
    continueCollision();
  }
  catch (Veto) {
  }
  catch (Stop) {
  }
  catch (Exception & ex) {
    throw;
  }
  return currentEvent(); 
}

CrossSection EventHandler::histogramScale() const {
  generator()->logWarning(
    EventHandlerHistError()
    << "The event handler '" << name() << "' was not able give a cross "
    "section for scaling histograms. The resulting histograms will not "
    "yeald correct cross section." << Exception::warning);
  return 1.0*picobarn;
}

void EventHandler::persistentOutput(PersistentOStream & os) const {
  os << theLastXComb << theMaxLoop << theStatLevel << theLumiFn
     << theKinematicalCuts << thePartonExtractor
     << theSubprocessGroup << theCascadeGroup << theMultiGroup
     << theHadronizationGroup << theDecayGroup << theCurrentEvent
     << theCurrentCollision << theCurrentStep << theCurrentStepHandler
     << warnIncomplete << theIncoming;
}

void EventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theLastXComb >> theMaxLoop >> theStatLevel >> theLumiFn
     >> theKinematicalCuts >> thePartonExtractor
     >> theSubprocessGroup >> theCascadeGroup >> theMultiGroup
     >> theHadronizationGroup >> theDecayGroup >> theCurrentEvent
     >> theCurrentCollision >> theCurrentStep >> theCurrentStepHandler
     >> warnIncomplete >> theIncoming;
}

//  ClassDescription<EventHandler>
//  EventHandler::initEventHandler;

ThePEG_IMPLEMENT_CLASS_DESCRIPTION(EventHandler);

void EventHandler::Init() {

  static ClassDocumentation<EventHandler> documentation
    ("There is no documentation for the ThePEG::EventHandler class");

  static Parameter<EventHandler,long> interfaceMaxLoop
    ("MaxLoop",
     "The maximum number of attempts per event when selecting a sub-process.",
     &EventHandler::theMaxLoop, 100000, 100, 100000000, true, false, true);

  static Switch<EventHandler,int> interfaceStatLevel
    ("StatLevel",
     "Controlls the amount of statistics written out after each run to "
     "the EventGenerators .out file.",
     &EventHandler::theStatLevel, 2, true, false);
  static SwitchOption interfaceStatLevelNone
    (interfaceStatLevel, "None", "No statistics is written out.", 0);
  static SwitchOption interfaceStatLevelTot
    (interfaceStatLevel, "TotalXSec",
     "Only the total cross-section is written out.", 1);
  static SwitchOption interfaceStatLevelME
    (interfaceStatLevel, "MatrixElements",
     "The cross-section for each subprocess group is written out.", 2);
  static SwitchOption interfaceStatLevelBins
    (interfaceStatLevel, "Bins",
     "The cross-sections for individual subprocesses are written out.", 3);
  static SwitchOption interfaceStatLevelFull
    (interfaceStatLevel, "Full",
     "A detailed account of the cross-sections of the generated sub-processes "
     "is written out.", 4);

  static Reference<EventHandler,LuminosityFunction> interfaceLumifn
    ("LuminosityFunction",
     "An object derived from the ThePEG::LuminosityFunction class, "
     "which describes the beams in the collider under study.",
     &EventHandler::theLumiFn, false, false, true, true,
     &EventHandler::lumiFn);

  static Reference<EventHandler,KinematicalCuts> interfaceCuts
    ("Cuts",
     "Kinematical cuts to be used by subclasses which do not provide "
     "their own. Note that this may be overridden by subclasses.",
     &EventHandler::theKinematicalCuts, true, false, true, true, false);

  static Reference<EventHandler,PartonExtractor> interfacePartonExtractor
    ("PartonExtractor",
     "A PartonExtractor object to be used by subclasses which do not "
     "provide their own. Note that this may be overridden by subclasses.",
     &EventHandler::thePartonExtractor, true, false, true, true, false);

  ThePEG_DECLARE_PREPOST_OBJECTS(EventHandler, SubProcessHandler,
				  Post, after);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(EventHandler,
					 CascadeHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(EventHandler,
					 MultipleInteractionHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(EventHandler,
					 HadronizationHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(EventHandler, DecayHandler);


  static Switch<EventHandler,bool> interfaceWarnIncomplete
    ("WarnIncomplete",
     "Emit a warning during the initialization that this EventHandler is "
     "incomplete. Should only be manipulated if the object is in fact an "
     "incomlete EventHandler and you do not want a warning.",
     &EventHandler::warnIncomplete, true, true, false);
  static SwitchOption interfaceWarnIncompleteYes
    (interfaceWarnIncomplete,
     "Yes",
     "This is an incomplete EventHandler and warning should be emitted.",
     true);
  static SwitchOption interfaceWarnIncompleteNo
    (interfaceWarnIncomplete,
     "No",
     "This EventHandler is either complete or no warning should be emitted "
     "in either case.",
     false);
}

ThePEG_IMPLEMENT_PREPOST_GROUP(EventHandler,SubProcessHandler,
				theSubprocessGroup,Post) \

ThePEG_IMPLEMENT_GROUPINTERFACE(EventHandler,CascadeHandler,
				 theCascadeGroup,CascHdlPtr) \

ThePEG_IMPLEMENT_GROUPINTERFACE(EventHandler,
				 MultipleInteractionHandler,
				 theMultiGroup,MIHdlPtr)  \

ThePEG_IMPLEMENT_GROUPINTERFACE(EventHandler,HadronizationHandler,
				 theHadronizationGroup,HadrHdlPtr) \

ThePEG_IMPLEMENT_GROUPINTERFACE(EventHandler,DecayHandler,
				 theDecayGroup,DecayHdlPtr) \


EventHandler::EventLoopException::
EventLoopException(const EventHandler & eh) {
  theMessage << "The maximum number of attempts per event (" << eh.maxLoop()
	     << ") in event handler '" << eh.name() << "' was exceeded.";
  severity(maybeabort);
}

