// -*- C++ -*-
//
// StandardXComb.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardXComb class.
//

#include "StandardXComb.h"
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
    partonDims(make_pair(0, 0)), theLastDiagramIndex(0) {}

StandardXComb::
StandardXComb(Energy newMaxEnergy, const cPDPair & inc,
	      tEHPtr newEventHandler, tSubHdlPtr newSubProcessHandler,
	      tPExtrPtr newExtractor, tCascHdlPtr newCKKW,
	      const PBPair & newPartonBins, tCutsPtr newCuts,
	      tMEPtr newME, const DiagramVector & newDiagrams, bool mir)
  : XComb(newMaxEnergy, inc, newEventHandler,
	  newExtractor, newCKKW, newPartonBins, newCuts),
    theSubProcessHandler(newSubProcessHandler), theME(newME),
    theDiagrams(newDiagrams), isMirror(mir),  theLastDiagramIndex(0) {
  partonDims = pExtractor()->nDims(partonBins());
  theNDim = matrixElement()->nDim() + partonDims.first + partonDims.second;
  mePartonData() = lastDiagram()->partons();
}

StandardXComb::StandardXComb(tMEPtr me, const tPVector & parts,
			     DiagramIndex indx)
  : theME(me), isMirror(false), theNDim(0), partonDims(make_pair(0, 0)),
    theLastDiagramIndex(0) {
  
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

CrossSection StandardXComb::
dSigDR(const pair<double,double> ll, int nr, const double * r) {
  //  attempt();

  pExtractor()->select(this);
  setPartonBinInfo();
  lastP1P2(ll);
  lastS(sqr(maxEnergy())/exp(lastP1() + lastP2()));

  if ( !pExtractor()->generateL(partonBinInstances(),
				r, r + nr - partonDims.second) )
    return ZERO;

  lastSHat(lastS()/exp(partonBinInstances().first->l() +
		       partonBinInstances().second->l()));
  lastPartons(make_pair(partonBinInstances().first->parton(),
			partonBinInstances().second->parton()));

  if ( lastSHat()  < cuts()->sHatMin() ) return ZERO;

  lastY(0.5*(partonBinInstances().second->l() -
	     partonBinInstances().first->l()));
  if ( !cuts()->initSubProcess(lastSHat(), lastY(), mirror()) ) return ZERO;

  meMomenta().resize(mePartonData().size());
  meMomenta()[0] = lastPartons().first->momentum();
  meMomenta()[1] = lastPartons().second->momentum();
  if ( mirror() ) swap(meMomenta()[0], meMomenta()[1]);
  SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  Energy summ = ZERO;
  if ( meMomenta().size() == 3 )
    meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  else {
    for ( int i = 2, N = meMomenta().size(); i < N; ++i ) {
      meMomenta()[i] = Lorentz5Momentum(mePartonData()[i]->mass());
      summ += mePartonData()[i]->massMin();
    }
    if ( sqr(summ) >= lastSHat() ) return ZERO;
  }
  
  matrixElement()->setXComb(this);
  //  if ( !matrixElement()->generateKinematics(r + partonDims.first) ) return ZERO;
  // lastScale(matrixElement()->scale());
  lastScale(max(lastSHat()/4.0, cuts()->scaleMin()));

  lastSHat(pExtractor()->generateSHat(lastS(), partonBinInstances(),
				      r, r + nr - partonDims.second));

  if ( !cuts()->sHat(lastSHat()) ) return ZERO;

  r += partonDims.first;

  lastX1X2(make_pair(lastPartons().first->momentum().plus()/
		     lastParticles().first->momentum().plus(),
		     lastPartons().second->momentum().minus()/
		     lastParticles().second->momentum().minus()));

  if ( !cuts()->x1(lastX1()) || !cuts()->x2(lastX2()) ) return ZERO;
  
  lastY((lastPartons().first->momentum() +
	 lastPartons().second->momentum()).rapidity());
  if ( !cuts()->yHat(lastY()) ) return ZERO;
  if ( !cuts()->initSubProcess(lastSHat(), lastY(), mirror()) ) return ZERO;

  meMomenta()[0] = lastPartons().first->momentum();
  meMomenta()[1] = lastPartons().second->momentum();
  if ( mirror() ) swap(meMomenta()[0], meMomenta()[1]);
  SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  if ( meMomenta().size() == 3 )
    meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  else {
    if ( sqr(summ) >= lastSHat() ) return ZERO;
  }

  matrixElement()->setXComb(this);
  if ( !matrixElement()->generateKinematics(r) ) return ZERO;
  lastScale(matrixElement()->scale());
  if ( !cuts()->scale(lastScale()) ) return ZERO;

  double pdf = pExtractor()->fullFn(partonBinInstances(), lastScale());
  if ( pdf == 0.0 ) return ZERO;
  matrixElement()->setKinematics();
  CrossSection xsec = matrixElement()->dSigHatDR() * pdf;

  lastAlphaS(matrixElement()->alphaS());
  lastAlphaEM(matrixElement()->alphaEM());

  subProcess(SubProPtr());
  if ( CKKWHandler() && matrixElement()->maxMultCKKW() > 0 &&
       matrixElement()->maxMultCKKW() > matrixElement()->minMultCKKW() ) {
    newSubProcess();
    CKKWHandler()->setXComb(this);
    xsec *= CKKWHandler()->reweightCKKW(matrixElement()->minMultCKKW(),
					matrixElement()->maxMultCKKW());
  }

  return xsec * matrixElement()->reWeight() * matrixElement()->preWeight();
}

void StandardXComb::newSubProcess() {
  if ( subProcess() ) return;

  subProcess(new_ptr(SubProcess(lastPartons(), tCollPtr(), matrixElement())));
  lastDiagramIndex(matrixElement()->diagram(diagrams()));
  const ColourLines & cl = matrixElement()->selectColourGeometry(lastDiagram());
  Lorentz5Momentum p1 = lastPartons().first->momentum();
  Lorentz5Momentum p2 = lastPartons().second->momentum();
  tPPair inc = lastPartons();
  if ( mirror() ) swap(inc.first, inc.second);
  LorentzRotation r =  Utilities::boostToCM(inc);
  lastDiagram()->construct(subProcess(), *this, cl);
  subProcess()->transform(r.inverse());
  lastPartons().first->set5Momentum(p1);
  lastPartons().second->set5Momentum(p2);
  lastPartons().first->scale(lastScale());
  lastPartons().second->scale(lastScale());
  for ( int i = 0, N = subProcess()->outgoing().size(); i < N; ++i )
    subProcess()->outgoing()[i]->scale(lastScale());
  // construct the spin information for the interaction
  matrixElement()->constructVertex(subProcess());
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
     << theLastDiagramIndex << theMEInfo << theMEPartonData
     << theLastDiagramIndex << theMEInfo;
}

void StandardXComb::persistentInput(PersistentIStream & is, int) {
  is >> theSubProcessHandler >> theME >> theStats
     >> theDiagrams >> isMirror >> theNDim >> partonDims
     >> theLastDiagramIndex >> theMEInfo >> theMEPartonData
     >> theLastDiagramIndex >> theMEInfo;
}

ClassDescription<StandardXComb> StandardXComb::initStandardXComb;

