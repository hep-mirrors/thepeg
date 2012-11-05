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
  : StandardXComb(newHead->maxEnergy(),newHead->particles(),
		  newHead->eventHandlerPtr(),
		  const_ptr_cast<tSubHdlPtr>(newHead->subProcessHandler()),
		  newHead->pExtractor(),newHead->CKKWHandler(),
		  newPartonBins,newHead->cuts(),newME,newDiagrams,newHead->mirror(),
		  newHead) {}

StdDependentXComb::StdDependentXComb()
  : StandardXComb() {}

StdDependentXComb::~StdDependentXComb() { }

tSubProPtr StdDependentXComb::construct() {
  matrixElement()->setXComb(this);
  if ( !matrixElement()->apply() )
    return tSubProPtr();
  matrixElement()->setKinematics();
  // first get the meMomenta in their CMS, as this may
  // not be the case
  Boost cm = (meMomenta()[0] + meMomenta()[1]).findBoostToCM();
  if ( cm.mag2() > Constants::epsilon ) {
    for ( vector<Lorentz5Momentum>::iterator m = meMomenta().begin();
	  m != meMomenta().end(); ++m ) {
      *m = m->boost(cm);
    }
  }
  tSubProPtr sub = StandardXComb::construct();
  sub->head(head()->subProcess());
  sub->groupWeight(lastCrossSection()/head()->lastCrossSection());
  return sub;
}

void StdDependentXComb::setProcess() { 
  meMomenta().resize(mePartonData().size());
}

void StdDependentXComb::setPartonBinInstances(Energy2 scale) {

  PBIPair newBins;

  Direction<0> dir(true);
  newBins.first =
    new_ptr(PartonBinInstance(lastPartons().first,partonBins().first,scale));

  dir.reverse();
  newBins.second =
    new_ptr(PartonBinInstance(lastPartons().second,partonBins().second,scale));

  resetPartonBinInstances(newBins);
  setPartonBinInfo();

  lastPartons().first->scale(partonBinInstances().first->scale());
  lastPartons().second->scale(partonBinInstances().second->scale());

}

void StdDependentXComb::setIncomingPartons() {

  clean();
  createPartonBinInstances();
  setPartonBinInfo();

  lastParticles(head()->lastParticles());

  lastPartons(make_pair(mePartonData()[0]->produceParticle(Lorentz5Momentum()),
			mePartonData()[1]->produceParticle(Lorentz5Momentum())));

  Lorentz5Momentum pFirst = meMomenta()[0];
  Lorentz5Momentum pSecond = meMomenta()[1];

  if ( head()->matrixElement()->wantCMS() ) {
    Boost toLab = (head()->lastPartons().first->momentum() + 
		   head()->lastPartons().second->momentum()).boostVector();
    if ( toLab.mag2() > Constants::epsilon ) {
      pFirst.boost(toLab);
      pSecond.boost(toLab);
    }
  }

  lastPartons().first->set5Momentum(pFirst);
  lastPartons().second->set5Momentum(pSecond);

  lastS((lastParticles().first->momentum() +
	 lastParticles().second->momentum()).m2());
  lastSHat((lastPartons().first->momentum() +
	    lastPartons().second->momentum()).m2());
  lastP1P2(make_pair(0.0, 0.0));

  double x1 = 
    lastPartons().first->momentum().plus()/
    lastParticles().first->momentum().plus();
  double x2 = 
    lastPartons().second->momentum().minus()/
    lastParticles().second->momentum().minus();

  lastX1X2(make_pair(x1,x2));
  lastY(log(lastX1()/lastX2())*0.5);

}

CrossSection StdDependentXComb::dSigDR(const double * r) {

  matrixElement()->flushCaches();

  matrixElement()->setXComb(this);

  if ( !matrixElement()->apply() ) {
    subProcess(SubProPtr());
    lastCrossSection(ZERO);
    return ZERO;
  }

  if ( !matrixElement()->generateKinematics(r) ) {
    subProcess(SubProPtr());
    lastCrossSection(ZERO);
    return ZERO;
  }

  remakeIncoming();
  setProcess();
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

