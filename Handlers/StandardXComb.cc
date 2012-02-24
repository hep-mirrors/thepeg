// -*- C++ -*-
//
// StandardXComb.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
// Copyright (C) 2009-2011 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardXComb class.
//

#include "StandardXComb.h"
#include "StdXCombGroup.h"
#include "ThePEG/Handlers/StandardEventHandler.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Maths.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/SubProcessGroup.h"
#include "ThePEG/Vectors/LorentzRotation.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/EventRecord/TmpTransform.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "StandardXComb.tcc"
#endif

using namespace ThePEG;

StandardXComb::StandardXComb()
  : XComb(), isMirror(false), theNDim(0),
    partonDims(make_pair(0, 0)), theLastDiagramIndex(0), theLastPDFWeight(0.0),
    theLastCrossSection(ZERO), theLastJacobian(1.0), theLastME2(-1.0), 
    theLastMECrossSection(ZERO), theLastMEPDFWeight(1.0) {}

StandardXComb::
StandardXComb(Energy newMaxEnergy, const cPDPair & inc,
	      tEHPtr newEventHandler, tSubHdlPtr newSubProcessHandler,
	      tPExtrPtr newExtractor, tCascHdlPtr newCKKW,
	      const PBPair & newPartonBins, tCutsPtr newCuts,
	      tMEPtr newME, const DiagramVector & newDiagrams, bool mir,
	      tStdXCombPtr newHead)
  : XComb(newMaxEnergy, inc, newEventHandler,
	  newExtractor, newCKKW, newPartonBins, newCuts),
    theSubProcessHandler(newSubProcessHandler), theME(newME),
    theDiagrams(newDiagrams), isMirror(mir),  theLastDiagramIndex(0),
    theLastPDFWeight(0.0), 
    theLastCrossSection(ZERO), theLastME2(-1.0), theLastMECrossSection(ZERO), 
    theLastMEPDFWeight(1.0), theHead(newHead) {
  partonDims = pExtractor()->nDims(partonBins());
  if ( matrixElement()->haveX1X2() ) {
    partonDims.first = 0;
    partonDims.second = 0;
  }
  theNDim = matrixElement()->nDim() + partonDims.first + partonDims.second;
  mePartonData() = lastDiagram()->partons();
}

StandardXComb::StandardXComb(tMEPtr me, const tPVector & parts,
			     DiagramIndex indx)
  : theME(me), isMirror(false), theNDim(0), partonDims(make_pair(0, 0)),
    theLastDiagramIndex(0), theLastPDFWeight(0.0), theLastCrossSection(ZERO),
    theLastME2(-1.0), theLastMECrossSection(ZERO), theLastMEPDFWeight(1.0) {
  
  subProcess(new_ptr(SubProcess(make_pair(parts[0], parts[1]),
				tCollPtr(), me)));
  for ( int i = 0, N = parts.size(); i < N; ++i ) {
    subProcess()->addOutgoing(parts[i], false);
    theMEPartonData.push_back(parts[i]->dataPtr());
    theMEMomenta.push_back(parts[i]->momentum());
  }
  lastSHat((meMomenta()[0] + meMomenta()[1]).m2());
  string tag = me->diagrams()[indx]->getTag();
  for ( int i = 0, N = me->diagrams().size(); i < N; ++i )
    if ( me->diagrams()[i]->getTag() == tag )
      theDiagrams.push_back(me->diagrams()[i]);
}

StandardXComb::~StandardXComb() {}

bool StandardXComb::checkInit() {
  Energy summin = ZERO;
  for ( int i = 2, N = mePartonData().size(); i < N; ++i ) {
    summin += mePartonData()[i]->massMin();
  }
  return ( summin < min(maxEnergy(), cuts()->mHatMax()) );
}

bool StandardXComb::willPassCuts() const {

  if ( lastSHat() <= cuts()->sHatMin() ||
       lastSHat() > cuts()->sHatMax() )
    return false;

  cuts()->initSubProcess(lastSHat(), lastY(), mirror());

  tcPDVector outdata(mePartonData().begin()+2,mePartonData().end());
  vector<LorentzMomentum> outmomenta(meMomenta().begin()+2,meMomenta().end());
  Boost tocm = (meMomenta()[0]+meMomenta()[1]).findBoostToCM();
  if ( tocm.mag2() > Constants::epsilon ) {
    for ( vector<LorentzMomentum>::iterator p = outmomenta.begin();
	  p != outmomenta.end(); ++p ) {
      p->boost(tocm);
    }
  }

  if ( !cuts()->passCuts(outdata,outmomenta,mePartonData()[0],mePartonData()[1]) ) {
    return false;
  }

  return true;

}

CrossSection StandardXComb::
dSigDR(const pair<double,double> ll, int nr, const double * r) {

  matrixElement()->flushCaches();

  if ( matrixElement()->keepRandomNumbers() ) {
    lastRandomNumbers().resize(nDim());
    copy(r,r+nDim(),lastRandomNumbers().begin());
  }

  pExtractor()->select(this);
  setPartonBinInfo();
  lastP1P2(ll);
  lastS(sqr(maxEnergy())/exp(lastP1() + lastP2()));

  meMomenta().resize(mePartonData().size());
  matrixElement()->setXComb(this);

  PPair partons;

  if ( !matrixElement()->haveX1X2() ) {

    if ( !pExtractor()->generateL(partonBinInstances(),
				  r, r + nr - partonDims.second) ) {
      lastCrossSection(ZERO);
      return ZERO;
    }
    partons = make_pair(partonBinInstances().first->parton(),
			partonBinInstances().second->parton());
    lastSHat(lastS()/exp(partonBinInstances().first->l() +
			 partonBinInstances().second->l()));
    meMomenta()[0] = partons.first->momentum();
    meMomenta()[1] = partons.second->momentum();

  } else {
    if ( !matrixElement()->generateKinematics(r + partonDims.first) ) {
      lastCrossSection(ZERO);
      return ZERO;
    }
    lastSHat((meMomenta()[0]+meMomenta()[1]).m2());
    matrixElement()->setKinematics();

    lastScale(matrixElement()->scale());

    partons.first = mePartonData()[0]->produceParticle(meMomenta()[0]);
    partons.second = mePartonData()[1]->produceParticle(meMomenta()[1]);

    Direction<0> dir(true);
    partonBinInstances().first = 
      new_ptr(PartonBinInstance(lastParticles().first,partons.first,
				partonBins().first,lastScale()));
    dir.reverse();
    partonBinInstances().second = 
      new_ptr(PartonBinInstance(lastParticles().second,partons.second,
				partonBins().second,lastScale()));
  }

  lastPartons(partons);

  if ( lastSHat()  < cuts()->sHatMin() ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  lastY(0.5*(partonBinInstances().second->l() -
	     partonBinInstances().first->l()));
  if ( !cuts()->initSubProcess(lastSHat(), lastY(), mirror()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  if ( mirror() ) swap(meMomenta()[0], meMomenta()[1]);
  if ( matrixElement()->wantCMS() &&
       !matrixElement()->haveX1X2() ) 
    SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  Energy summ = ZERO;
  if ( meMomenta().size() == 3 ) {
    if ( !matrixElement()->haveX1X2() )
      meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  } else {
    for ( int i = 2, N = meMomenta().size(); i < N; ++i ) {
      if ( !matrixElement()->haveX1X2() )
	meMomenta()[i] = Lorentz5Momentum(mePartonData()[i]->mass());
      summ += mePartonData()[i]->massMin();
    }
    if ( sqr(summ) >= lastSHat() ) {
      lastCrossSection(ZERO);
      return ZERO;
    }
  }

  matrixElement()->setXComb(this);
  if ( !matrixElement()->haveX1X2() )
    lastScale(max(lastSHat()/4.0, cuts()->scaleMin()));

  lastSHat(pExtractor()->generateSHat(lastS(), partonBinInstances(),
				      r, r + nr - partonDims.second,
				      matrixElement()->haveX1X2()));

  if ( !cuts()->sHat(lastSHat()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  r += partonDims.first;

  lastX1X2(make_pair(lastPartons().first->momentum().plus()/
		     lastParticles().first->momentum().plus(),
		     lastPartons().second->momentum().minus()/
		     lastParticles().second->momentum().minus()));

  if ( !cuts()->x1(lastX1()) || !cuts()->x2(lastX2()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }
  
  lastY((lastPartons().first->momentum() +
	 lastPartons().second->momentum()).rapidity());
  if ( !cuts()->yHat(lastY()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }
  if ( !cuts()->initSubProcess(lastSHat(), lastY(), mirror()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  meMomenta()[0] = lastPartons().first->momentum();
  meMomenta()[1] = lastPartons().second->momentum();
  if ( mirror() ) swap(meMomenta()[0], meMomenta()[1]);
  if ( matrixElement()->wantCMS() &&
       !matrixElement()->haveX1X2() ) 
    SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  if ( meMomenta().size() == 3 ) {
    if ( !matrixElement()->haveX1X2() )
      meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  } else {
    if ( sqr(summ) >= lastSHat() ) {
      lastCrossSection(ZERO);
      return ZERO;
    }
  }

  matrixElement()->setXComb(this);
  if ( !matrixElement()->haveX1X2() ) {
    if ( !matrixElement()->generateKinematics(r) ) {
      lastCrossSection(ZERO);
      return ZERO;
    }
  }
  lastScale(matrixElement()->scale());
  if ( !cuts()->scale(lastScale()) ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  pair<bool,bool> evalPDFS = 
    make_pair(matrixElement()->havePDFWeight1(),
	      matrixElement()->havePDFWeight2());
  if ( mirror() )
    swap(evalPDFS.first,evalPDFS.second);
  lastPDFWeight(pExtractor()->fullFn(partonBinInstances(), lastScale(),
				     evalPDFS));
  if ( lastPDFWeight() == 0.0 ) {
    lastCrossSection(ZERO);
    return ZERO;
  }
  matrixElement()->setKinematics();
  CrossSection xsec = matrixElement()->dSigHatDR() * lastPDFWeight();
  if ( xsec == ZERO ) {
    lastCrossSection(ZERO);
    return ZERO;
  }

  lastAlphaS (matrixElement()->orderInAlphaS () >0 ?
	      matrixElement()->alphaS()  : -1.);
  lastAlphaEM(matrixElement()->orderInAlphaEW() >0 ?
	      matrixElement()->alphaEM() : -1.);

  subProcess(SubProPtr());
  if ( CKKWHandler() && matrixElement()->maxMultCKKW() > 0 &&
       matrixElement()->maxMultCKKW() > matrixElement()->minMultCKKW() ) {
    newSubProcess();
    CKKWHandler()->setXComb(this);
    xsec *= CKKWHandler()->reweightCKKW(matrixElement()->minMultCKKW(),
					matrixElement()->maxMultCKKW());
  }

  if ( matrixElement()->reweighted() ) {
    newSubProcess();
    xsec *= matrixElement()->reWeight() * matrixElement()->preWeight();
  }

  lastCrossSection(xsec);

  return xsec;

}

void StandardXComb::newSubProcess(bool group) {
  if ( subProcess() ) return;

  if ( !group )
    subProcess(new_ptr(SubProcess(lastPartons(), tCollPtr(), matrixElement())));
  else
    subProcess(new_ptr(SubProcessGroup(lastPartons(), tCollPtr(), matrixElement())));
  lastDiagramIndex(matrixElement()->diagram(diagrams()));
  const ColourLines & cl = matrixElement()->selectColourGeometry(lastDiagram());
  Lorentz5Momentum p1 = lastPartons().first->momentum();
  Lorentz5Momentum p2 = lastPartons().second->momentum();
  tPPair inc = lastPartons();
  if ( mirror() ) swap(inc.first, inc.second);
  if ( matrixElement()->wantCMS() &&
       !matrixElement()->haveX1X2() ) {
    LorentzRotation r =  Utilities::boostToCM(inc);
    lastDiagram()->construct(subProcess(), *this, cl);
    subProcess()->transform(r.inverse());
    lastPartons().first->set5Momentum(p1);
    lastPartons().second->set5Momentum(p2);
  } else {
    lastDiagram()->construct(subProcess(), *this, cl);
  }
  lastPartons().first ->scale(partonBinInstances().first ->scale());
  lastPartons().second->scale(partonBinInstances().second->scale());
  for ( int i = 0, N = subProcess()->outgoing().size(); i < N; ++i )
    subProcess()->outgoing()[i]->scale(lastScale());
  // construct the spin information for the interaction
  matrixElement()->constructVertex(subProcess());
  // set veto scales
  matrixElement()->setVetoScales(subProcess());
}

tSubProPtr StandardXComb::construct() {

  matrixElement()->setXComb(this);
  if ( !cuts()->initSubProcess(lastSHat(), lastY()) ) throw Veto();

  setPartonBinInfo();
  matrixElement()->setKinematics();

  newSubProcess();

  TmpTransform<tSubProPtr>
    tmp(subProcess(), Utilities::getBoostToCM(subProcess()->incoming()));
  if ( !cuts()->passCuts(*subProcess()) ) throw Veto();

  return subProcess();

}

void StandardXComb::Init() {}

void StandardXComb::persistentOutput(PersistentOStream & os) const {
  os << theSubProcessHandler << theME << theStats
     << theDiagrams << isMirror << theNDim << partonDims
     << theLastDiagramIndex << theMEInfo << theLastRandomNumbers << theMEPartonData
     << theLastPDFWeight << ounit(theLastCrossSection,nanobarn) << theLastJacobian
     << theLastME2 << ounit(theLastMECrossSection,nanobarn) << theLastMEPDFWeight
     << theHead;
}

void StandardXComb::persistentInput(PersistentIStream & is, int) {
  is >> theSubProcessHandler >> theME >> theStats
     >> theDiagrams >> isMirror >> theNDim >> partonDims
     >> theLastDiagramIndex >> theMEInfo >> theLastRandomNumbers >> theMEPartonData
     >> theLastPDFWeight >> iunit(theLastCrossSection,nanobarn) >> theLastJacobian
     >> theLastME2 >> iunit(theLastMECrossSection,nanobarn) >> theLastMEPDFWeight
     >> theHead;
}

ClassDescription<StandardXComb> StandardXComb::initStandardXComb;

