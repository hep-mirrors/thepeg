// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the EventManipulator class.
//

#include "EventManipulator.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventManipulator.tcc"
#endif

using namespace ThePEG;

EventManipulator::~EventManipulator() {}

AbstractNoPIOClassDescription<EventManipulator>
EventManipulator::initEventManipulator;

void EventManipulator::Init() {

  static ClassDocumentation<EventManipulator> documentation
    ("There is no documentation for the ThePEG::EventManipulator class");

}

