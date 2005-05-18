// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardXComb class.
//

#include "StandardXComb.h"
#include "ThePEG/Handlers/StandardEventHandler.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Handlers/KinematicalCuts.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "StandardXComb.tcc"
#endif

using namespace ThePEG;

StandardXComb::StandardXComb()
  : XComb(), theNAttempted(0), theNAccepted(0), theSumWeight(0.0),
    isMirror(false), theNDim(0),
    partonDims(make_pair(0, 0)), theLastDiagramIndex(0) {}

StandardXComb::
StandardXComb(Energy newMaxEnergy, const cPDPair & inc,
      tStdEHPtr newEventHandler, tSubHdlPtr newSubProcessHandler,
      tPExtrPtr newExtractor, const PBPair & newPartonBins, tKinCutPtr newCuts,
      tMEPtr newME, const DiagramVector & newDiagrams, bool mir)
  : XComb(newMaxEnergy, inc, newEventHandler,
	  newExtractor, newPartonBins, newCuts),
    theSubProcessHandler(newSubProcessHandler), theME(newME),
    theNAttempted(0), theNAccepted(0), theSumWeight(0.0),
    theDiagrams(newDiagrams), isMirror(mir),  theLastDiagramIndex(0) {
  partonDims = pExtractor()->nDims(partonBins());
  theNDim = matrixElement()->nDim() + partonDims.first + partonDims.second;
  mePartonData() = lastDiagram()->partons();
}

StandardXComb::StandardXComb(const StandardXComb & x)
  : XComb(x), theSubProcessHandler(x.theSubProcessHandler), theME(x.theME),
    theNAttempted(x.theNAttempted), theNAccepted(x.theNAccepted),
    theSumWeight(x.theSumWeight), theDiagrams(x.theDiagrams),
    isMirror(x.isMirror), theNDim(x.theNDim), partonDims(x.partonDims),
    theMEMomenta(x.theMEMomenta), theMEPartons(x.theMEPartons),
    theMEPartonData(x.theMEPartonData),
    theLastDiagramIndex(x.theLastDiagramIndex), theMEInfo(x.theMEInfo) {}

StandardXComb::StandardXComb(tMEPtr me, const tPVector & parts, DiagramIndex indx)
  : theME(me), theNAttempted(0), theNAccepted(0), theSumWeight(0.0),
    isMirror(false), theNDim(0), partonDims(make_pair(0, 0)), theMEPartons(parts),
    theLastDiagramIndex(0) {
  
  for ( int i = 0, N = parts.size(); i < N; ++i ) {
    theMEPartonData.push_back(parts[i]->dataPtr());
    theMEMomenta.push_back(parts[i]->momentum());
  }
  lastSHat((meMomenta()[0] + meMomenta()[1]).m2());
  string tag = me->diagrams()[indx]->getTag();
  for ( int i = 0, N = me->diagrams().size(); i < N; ++i )
    if ( me->diagrams()[i]->getTag() == tag )
      theDiagrams.push_back(me->diagrams()[i]);
  createPartonBinInstances();
}

StandardXComb::~StandardXComb() {}

bool StandardXComb::checkInit() {
  Energy summin = 0.0*GeV;
  for ( int i = 2, N = mePartonData().size(); i < N; ++i ) {
    summin += mePartonData()[i]->massMin();
  }
  return ( summin < min(maxEnergy(), cuts()->mHatMax()) );
}

CrossSection StandardXComb::
dSigDR(const pair<double,double> ll, int nr, const double * r) {
  Timer<7> timera("StandardXComb::dSigDR()");
  CrossSection zero = 0.0*nanobarn;
  attempt();

  pExtractor()->select(this);
  setPartonBinInfo();
  lastP1P2(ll);
  lastS(sqr(maxEnergy())/exp(lastP1() + lastP2()));

  Timer<22> timerb("StandardXComb::dSigDR():generateL");
  if ( !pExtractor()->generateL(partonBinInstances(),
				r, r + nr - partonDims.second) )
    return zero;

  lastSHat(lastS()/exp(partonBinInstances().first->l() +
		       partonBinInstances().second->l()));
  lastPartons(make_pair(partonBinInstances().first->parton(),
			partonBinInstances().second->parton()));

  if ( lastSHat()  < cuts()->sHatMin() ) return zero;

  meMomenta().resize(mePartonData().size());
  mePartons().resize(mePartonData().size());
  mePartons()[0 + mirror()] = lastPartons().first;
  mePartons()[1 - mirror()] = lastPartons().second;
  meMomenta()[0] = mePartons()[0]->momentum();
  meMomenta()[1] = mePartons()[1]->momentum();
  SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  Energy summ = 0.0*GeV;
  if ( meMomenta().size() == 3 )
    meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  else {
    for ( int i = 2, N = meMomenta().size(); i < N; ++i ) {
      meMomenta()[i] = Lorentz5Momentum(mePartonData()[i]->generateMass());
      summ += meMomenta()[i].mass();
    }
    if ( sqr(summ) >= lastSHat() ) return zero;
  }
  
  Timer<23> timerc("StandardXComb::dSigDR():generateKinematics-1");
  matrixElement()->setXComb(this);
  if ( !matrixElement()->generateKinematics(r + partonDims.first) ) return zero;
  lastScale(matrixElement()->scale());

  Timer<24> timerd("StandardXComb::dSigDR():generateSHat");
  lastSHat(pExtractor()->generateSHat(lastS(), partonBinInstances(),
				      r, r + nr - partonDims.second));

  if ( !cuts()->sHat(lastSHat()) ) return zero;

  r += partonDims.first;

  lastX1X2(make_pair(lastPartons().first->momentum().plus()/
		     lastParticles().first->momentum().plus(),
		     lastPartons().second->momentum().minus()/
		     lastParticles().second->momentum().minus()));

  if ( !cuts()->x1(lastX1()) || !cuts()->x2(lastX2()) ) return zero;
  
  lastY((lastPartons().first->momentum() +
	 lastPartons().second->momentum()).rapidity());
  if ( !cuts()->yStar(lastY()) ) return zero;

  meMomenta()[0] = mePartons()[0]->momentum();
  meMomenta()[1] = mePartons()[1]->momentum();
  SimplePhaseSpace::CMS(meMomenta()[0], meMomenta()[1], lastSHat());

  if ( meMomenta().size() == 3 )
    meMomenta()[2] = Lorentz5Momentum(sqrt(lastSHat()));
  else {
    if ( sqr(summ) >= lastSHat() ) return zero;
  }

  matrixElement()->setXComb(this);
  Timer<25> timere("StandardXComb::dSigDR():generateKinematics-2");
  if ( !matrixElement()->generateKinematics(r) ) return zero;
  for ( int i = 2, N = meMomenta().size(); i < N; ++i )
    if ( !cuts()->pTHat(meMomenta()[i].perp()) ) return zero;
  Timer<26> timerf("StandardXComb::dSigDR():dSigHatDR");
  CrossSection xsec = matrixElement()->dSigHatDR();
  lastScale(matrixElement()->scale());
  if ( !cuts()->scale(lastScale()) ) return zero;

  return xsec * pExtractor()->fullFn(partonBinInstances(), lastScale()) *
    matrixElement()->reWeight() * matrixElement()->preWeight();
}

void StandardXComb::construct(tSubProPtr sub) {
  Timer<27> timera("StandardXComb::construct()");

  matrixElement()->setXComb(this);
  setPartonBinInfo();
  matrixElement()->setKinematics();

  lastDiagramIndex(matrixElement()->diagram(diagrams()));
  const ColourLines & cl = matrixElement()->selectColourGeometry(lastDiagram());
  Lorentz5Momentum p1 = lastPartons().first->momentum();
  Lorentz5Momentum p2 = lastPartons().second->momentum();
  LorentzRotation r =
    Utilities::boostToCM(make_pair(mePartons()[0], mePartons()[1]));
  mePartons() = lastDiagram()->construct(sub, *this, cl);
  cuts()->cut(*sub);
  sub->transform(r.inverse());
  lastPartons().first->set5Momentum(p1);
  lastPartons().second->set5Momentum(p2);
  lastPartons().first->scale(lastScale());
  lastPartons().second->scale(lastScale());
  for ( int i = 0, N = sub->outgoing().size(); i < N; ++i )
    sub->outgoing()[i]->scale(lastScale());
  // construct the spin information for the interaction
  matrixElement()->constructVertex(sub);
}

void StandardXComb::Init() {}

void StandardXComb::persistentOutput(PersistentOStream & os) const {

  os << theSubProcessHandler << theME
     << theNAttempted << theNAccepted << theSumWeight
     << theDiagrams << isMirror << theNDim << partonDims
     << theLastDiagramIndex << theMEInfo << theMEPartons << theMEPartonData
     << theLastDiagramIndex << theMEInfo;
}

void StandardXComb::persistentInput(PersistentIStream & is, int) {
  is >> theSubProcessHandler >> theME
     >> theNAttempted >> theNAccepted >> theSumWeight
     >> theDiagrams >> isMirror >> theNDim >> partonDims
     >> theLastDiagramIndex >> theMEInfo >> theMEPartons >> theMEPartonData
     >> theLastDiagramIndex >> theMEInfo;
}

ClassDescription<StandardXComb> StandardXComb::initStandardXComb;

