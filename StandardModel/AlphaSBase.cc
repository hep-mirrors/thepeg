// -*- C++ -*-
//
// AlphaSBase.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AlphaSBase class.
//

#include "AlphaSBase.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

void AlphaSBase::doinit() {
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

