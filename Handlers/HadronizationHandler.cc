// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HadronizationHandler class.
//

#include "HadronizationHandler.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HadronizationHandler.tcc"
#endif

using namespace ThePEG;

HadronizationHandler::~HadronizationHandler() {}

AbstractNoPIOClassDescription<HadronizationHandler>
HadronizationHandler::initHadronizationHandler;

void HadronizationHandler::Init() {

  static ClassDocumentation<HadronizationHandler> documentation
    ("This is the base class to be used by all models for hadronization.");

}

