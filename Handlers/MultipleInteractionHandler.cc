// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultipleInteractionHandler class.
//

#include "MultipleInteractionHandler.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultipleInteractionHandler.tcc"
#endif

using namespace ThePEG;

MultipleInteractionHandler::~MultipleInteractionHandler() {}

AbstractNoPIOClassDescription<MultipleInteractionHandler>
MultipleInteractionHandler::initMultipleInteractionHandler;

void MultipleInteractionHandler::Init() {

  static ClassDocumentation<MultipleInteractionHandler> documentation
    ("There is no documentation for the "
     "ThePEG::MultipleInteractionHandler class");

}

