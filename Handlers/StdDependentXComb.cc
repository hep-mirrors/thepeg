// -*- C++ -*-
//
// StdDependentXComb.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2010 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StdDependentXComb class.
//

#include "StdDependentXComb.h"
#include "StdXCombGroup.h"
#include "ThePEG/MatrixElement/MEGroup.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

StdDependentXComb::StdDependentXComb(tStdXCombPtr newHead,
				     const PBPair & newPartonBins, tMEPtr newME,
				     const DiagramVector & newDiagrams)
  : StandardXComb(newHead,newPartonBins,newME,newDiagrams) {}

StdDependentXComb::StdDependentXComb()
  : StandardXComb() {}

StdDependentXComb::~StdDependentXComb() { }

CrossSection StdDependentXComb::dSigDR(const double * r) {

  matrixElement()->flushCaches();

  matrixElement()->setXComb(this);

  if ( !matrixElement()->apply() ) {
    subProcess(SubProPtr());
    lastCrossSection(ZERO);
    return ZERO;
  }

  meMomenta().resize(mePartonData().size());

  if ( !matrixElement()->generateKinematics(r) ) {
    subProcess(SubProPtr());
    lastCrossSection(ZERO);
    return ZERO;
  }

  setIncomingPartons();

  lastScale(head()->lastScale());
  lastAlphaS(head()->lastAlphaS());
  lastAlphaEM(head()->lastAlphaEM());

  if ( (!willPassCuts() && 
	!matrixElement()->headCuts() &&
	!matrixElement()->ignoreCuts()) ||
       !matrixElement()->apply() ) {
    subProcess(SubProPtr());
    lastCrossSection(ZERO);
    return ZERO;
  }

  lastPDFWeight(head()->lastPDFWeight());

  matrixElement()->setKinematics();
  CrossSection xsec = matrixElement()->dSigHatDR() * lastPDFWeight();

  subProcess(SubProPtr());
  lastCrossSection(xsec);

  return xsec;

}

void StdDependentXComb::Init() {}

void StdDependentXComb::persistentOutput(PersistentOStream &) const {
}

void StdDependentXComb::persistentInput(PersistentIStream &, int) {
}

ClassDescription<StdDependentXComb> StdDependentXComb::initStdDependentXComb;

