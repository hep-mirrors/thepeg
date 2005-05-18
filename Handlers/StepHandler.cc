// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StepHandler class.
//

#include "StepHandler.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StepHandler.tcc"
#endif

using namespace ThePEG;

StepHandler::~StepHandler() {}

void StepHandler::eventHandler(tEHPtr eh) {
  theEventHandler = eh;
  theNewStep = tStepPtr();
  theCurrentStep = eh->currentStep();
}

void StepHandler::createNewStep() {
  useMe();
  theNewStep = eventHandler()->newStep(this);
}

AbstractNoPIOClassDescription<StepHandler> StepHandler::initStepHandler;

void StepHandler::Init() {

  static ClassDocumentation<StepHandler> documentation
    ("There is no documentation for the ThePEG::StepHandler class");

}

