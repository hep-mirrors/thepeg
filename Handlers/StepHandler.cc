// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StepHandler class.
//

#include "StepHandler.h"
#include "ThePEG/Handlers/PartialCollisionHandler.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StepHandler.tcc"
#endif

using namespace ThePEG;

StepHandler::~StepHandler() {}

void StepHandler::collisionHandler(tPartCollHdlPtr ch) {
  theCollisionHandler = ch;
  theNewStep = tStepPtr();
  theCurrentStep = ch->currentStep();
}

void StepHandler::createNewStep() {
  theNewStep = collisionHandler()->newStep();
}

AbstractNoPIOClassDescription<StepHandler> StepHandler::initStepHandler;

void StepHandler::Init() {}

