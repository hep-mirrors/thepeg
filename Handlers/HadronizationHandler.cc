// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HadronizationHandler class.
//

#include "HadronizationHandler.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

AbstractNoPIOClassDescription<HadronizationHandler>
HadronizationHandler::initHadronizationHandler;

void HadronizationHandler::Init() {

  static ClassDocumentation<HadronizationHandler> documentation
    ("This is the base class to be used by all models for hadronization.");

}

