// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PartialCollisionHandler class.
//

#include "PartialCollisionHandler.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/Hint.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Handlers/MultipleInteractionHandler.h"
#include "ThePEG/Handlers/HadronizationHandler.h"
#include "ThePEG/Handlers/DecayHandler.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialCollisionHandler.tcc"
#endif

using namespace ThePEG;

PartialCollisionHandler::PartialCollisionHandler() {
  setupGroups();
}

PartialCollisionHandler::
PartialCollisionHandler(const PartialCollisionHandler & x)
  : HandlerBase(x), LastXCombInfo<>(x),
    theSubprocessGroup(x.theSubprocessGroup),
    theCascadeGroup(x.theCascadeGroup), theMultiGroup(x.theMultiGroup),
    theHadronizationGroup(x.theHadronizationGroup),
    theDecayGroup(x.theDecayGroup) {
  setupGroups();
}

PartialCollisionHandler::~PartialCollisionHandler() {}

void PartialCollisionHandler::setupGroups() {
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

void PartialCollisionHandler::initGroups() {
  for ( unsigned int i = 0; i < groups().size(); ++i )
    groups()[i]->init(*optGroups[i]);
}

tEventPtr PartialCollisionHandler::partialCollision(tStepPtr s) {
  EventPtr e = new_ptr(Event(PPair(), tcEventBasePtr(), generator()->runName(),
			     generator()->currentEventNumber()));
  e->newCollision()->addStep(s);
  return partialCollision(tEventPtr(e));
}

tEventPtr PartialCollisionHandler::partialCollision(tEventPtr e) {
  clearEvent();
  e->setInfo(this, generator()->runName(),
	     generator()->currentEventNumber(), 1.0);
  currentEvent(e);
  if ( e->collisions().empty() ) currentCollision(e->newCollision());
  else currentCollision(e->collisions().back());
  if ( currentCollision()->finalStep() )
    currentStep(currentCollision()->finalStep());
  else
    currentStep(currentCollision()->newStep());
  PartialCollisionHandler::initGroups();
  continueCollision();
  return currentEvent();
}

tCollPtr PartialCollisionHandler::continueCollision() {
  Timer<45> timer("PartialCollisionHandler::continueCollision()");
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
      }
    }
    if ( done ) break;
  }
  return currentCollision();
}

void PartialCollisionHandler::clearEvent() {
  for ( GroupVector::const_iterator git = groups().begin();
	git != groups().end(); ++git ) (**git).clear();
}

bool PartialCollisionHandler::empty() const {
  for ( GroupVector::const_iterator git = groups().begin();
	git != groups().end(); ++git )
    if ( !(**git).empty() ) return false;
  return true;
}

void PartialCollisionHandler::
performStep(tStepHdlPtr handler, tHintPtr hint) {
  if ( !lastXCombPtr() ) theLastXComb = new_ptr(XComb());

  if ( hint->stop() ) throw Stop();
  tStepPtr oldStep = currentStep();
  currentStepHandler(handler);
  handler->collisionHandler(this);
  try {
    handler->handle(*this, hint->tagged(*oldStep), *hint);
  }
  catch (...) {
    if ( oldStep != currentStep() ) currentCollision()->popStep();
    throw;
  }

  while ( currentStep()->nullStep() ) popStep();
      
  if ( ThePEG_DEBUG_ITEM(2) && oldStep != currentStep() )
    generator()->logfile() << *currentStep();
}

void PartialCollisionHandler::
addStep(Group::Level level, Group::Handler group, tStepHdlPtr s, tHintPtr h) {
  switch ( level ) {
  case Group::main:
    if ( s &&
	 !groups()[group]->setHandler(s, *optGroups[group]) )
      throw CollHdlStepException(*this, *s, groups()[group]->handlerClass());
    groups()[group]->addHint(h, *optGroups[group]);
    break;
  case Group::before:
    groups()[group]->addPreHandler(s, h, *optGroups[group]);
    break;
  case Group::after:
    groups()[group]->addPostHandler(s, h, *optGroups[group]);
    break;
  }
}

void PartialCollisionHandler::throwCurrent() {
  clean();
}

void PartialCollisionHandler::clean() {
  currentEvent(EventPtr());
  currentCollision(CollPtr());
  currentStep(StepPtr());
}

void PartialCollisionHandler::persistentOutput(PersistentOStream & os) const {
  os << theLastXComb << theSubprocessGroup << theCascadeGroup << theMultiGroup
     << theHadronizationGroup << theDecayGroup << theCurrentEvent
     << theCurrentCollision << theCurrentStep << theCurrentStepHandler;
}

void PartialCollisionHandler::persistentInput(PersistentIStream & is, int) {
  is >> theLastXComb >> theSubprocessGroup >> theCascadeGroup >> theMultiGroup
     >> theHadronizationGroup >> theDecayGroup >> theCurrentEvent
     >> theCurrentCollision >> theCurrentStep >> theCurrentStepHandler;
}

//  ClassDescription<PartialCollisionHandler>
//  PartialCollisionHandler::initPartialCollisionHandler;

ThePEG_IMPLEMENT_CLASS_DESCRIPTION(PartialCollisionHandler);

void PartialCollisionHandler::Init() {
  ThePEG_DECLARE_PREPOST_OBJECTS(PartialCollisionHandler, SubProcessHandler,
				  Post, after);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(PartialCollisionHandler,
					 CascadeHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(PartialCollisionHandler,
					 MultipleInteractionHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(PartialCollisionHandler,
					 HadronizationHandler);
  ThePEG_DECLARE_GROUPINTERFACE_OBJECTS(PartialCollisionHandler, DecayHandler);
}

CollHdlStepException::
CollHdlStepException(const PartialCollisionHandler & ch, const StepHandler & sh,
		     string cname) {
  theMessage << "Cannot add the StepHandler '" << sh.name() << "' to the "
	     << "list of step handlers in the PartialCollisionHandler '"
	     << ch.name() << "' because it is not of class '" << cname << "'.";
  severity(abortnow);
}



ThePEG_IMPLEMENT_PREPOST_GROUP(PartialCollisionHandler,SubProcessHandler,
				theSubprocessGroup,Post) \

ThePEG_IMPLEMENT_GROUPINTERFACE(PartialCollisionHandler,CascadeHandler,
				 theCascadeGroup,CascHdlPtr) \

ThePEG_IMPLEMENT_GROUPINTERFACE(PartialCollisionHandler,
				 MultipleInteractionHandler,
				 theMultiGroup,MIHdlPtr)  \

ThePEG_IMPLEMENT_GROUPINTERFACE(PartialCollisionHandler,HadronizationHandler,
				 theHadronizationGroup,HadrHdlPtr) \

ThePEG_IMPLEMENT_GROUPINTERFACE(PartialCollisionHandler,DecayHandler,
				 theDecayGroup,DecayHdlPtr) \


