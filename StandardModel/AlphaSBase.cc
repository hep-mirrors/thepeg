// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AlphaSBase class.
//

#include "AlphaSBase.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

void AlphaSBase::doinit() throw(InitException) {
  theFlavourThresholds = flavourThresholds();
  theLambdaQCDs = LambdaQCDs();
  Interfaced::doinit();
}

void AlphaSBase::persistentOutput(PersistentOStream & os) const {
  os << ounit(theFlavourThresholds, GeV2) << ounit(theLambdaQCDs, GeV);
}

void AlphaSBase::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theFlavourThresholds, GeV2) >> iunit(theLambdaQCDs, GeV);
}

AbstractClassDescription<AlphaSBase> AlphaSBase::initAlphaSBase;

void AlphaSBase::Init() {

  static ClassDocumentation<AlphaSBase> documentation
    ("An abstract base class used by the StandardModelBase to implement the "
     "QCD coupling.");

}

