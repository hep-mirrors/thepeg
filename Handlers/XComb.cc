// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the XComb class.
//

#include "XComb.h"
#include "ThePEG/Handlers/CollisionHandler.h"
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
#include "XComb.tcc"
#endif

using namespace ThePEG;

XComb::XComb()
  : theNAttempted(0), theNAccepted(0), theSumWeight(0.0),
    theLastS(Energy2()), theLastSHat(Energy2()), theLastY(0.0),
    theLastP1P2(make_pair(1.0, 1.0)), theLastL1L2(make_pair(1.0, 1.0)),
    theLastX1X2(make_pair(1.0, 1.0)), theLastE1E2(make_pair(0.0, 0.0)),
    theLastScale(0.0*GeV2), theMaxEnergy(0.0*GeV), isMirror(false), theNDim(0),
    partonDims(make_pair(0, 0)), theLastDiagramIndex(0) {}

XComb::
XComb(Energy newMaxEnergy, const cPDPair & inc,
      tCollHdlPtr newCollisionHandler, tSubHdlPtr newSubProcessHandler,
      tPExtrPtr newExtractor, const PBPair & newPartonBins, tKinCutPtr newCuts,
      tMEPtr newME, const DiagramVector & newDiagrams, bool mir)
  : theCollisionHandler(newCollisionHandler),
    theSubProcessHandler(newSubProcessHandler),
    thePartonExtractor(newExtractor), theCuts(newCuts), theParticles(inc),
    thePartonBins(newPartonBins), theNAttempted(0), theNAccepted(0),
    theSumWeight(0.0), theLastS(Energy2()), theLastSHat(Energy2()),
    theLastY(0.0), theLastP1P2(make_pair(1.0, 1.0)),
    theLastL1L2(make_pair(1.0, 1.0)), theLastX1X2(make_pair(1.0, 1.0)),
    theLastE1E2(make_pair(0.0, 0.0)), theLastScale(0.0*GeV2),
    theMaxEnergy(newMaxEnergy), theME(newME),
    theDiagrams(newDiagrams), isMirror(mir), theLastDiagramIndex(0) {
  thePartons = cPDPair(partonBins().first->parton(),
		       partonBins().second->parton());
  partonDims = pExtractor()->nDims(partonBins());
  theNDim = matrixElement()->nDim() + partonDims.first + partonDims.second;
  theMEPartonData = lastDiagram()->partons();
}

XComb::XComb(tMEPtr me, const tPVector & parts, DiagramIndex indx)
  : theNAttempted(0), theNAccepted(0), theSumWeight(0.0),
    theLastS(Energy2()), theLastSHat(Energy2()), theLastY(0.0),
    theLastP1P2(make_pair(1.0, 1.0)), theLastL1L2(make_pair(1.0, 1.0)),
    theLastX1X2(make_pair(1.0, 1.0)), theLastE1E2(make_pair(0.0, 0.0)),
    theMaxEnergy(0.0*GeV), isMirror(false),
    theNDim(0), partonDims(make_pair(0, 0)), theMEPartons(parts),
    theLastDiagramIndex(0) {
  
  for ( int i = 0, N = parts.size(); i < N; ++i ) {
    theMEPartonData.push_back(parts[i]->dataPtr());
    theMEMomenta.push_back(parts[i]->momentum());
  }
  theLastSHat = (meMomenta()[0] + meMomenta()[1]).m2();
  string tag = me->diagrams()[indx]->getTag();
  for ( int i = 0, N = me->diagrams().size(); i < N; ++i )
    if ( me->diagrams()[i]->getTag() == tag )
      theDiagrams.push_back(me->diagrams()[i]);
}

XComb::XComb(const XComb & x)
  : theCollisionHandler(x.theCollisionHandler),
    theSubProcessHandler(x.theSubProcessHandler),
    thePartonExtractor(x.thePartonExtractor),
    theCuts(x.theCuts), theParticles(x.theParticles),
    thePartons(x.thePartons), thePartonBins(x.thePartonBins),
    thePartonBinInstances(x.thePartonBinInstances),
    theNAttempted(x.theNAttempted), theNAccepted(x.theNAccepted),
    theSumWeight(x.theSumWeight), theLastParticles(x.theLastParticles),
    theLastPartons(x.theLastPartons), theLastS(x.theLastS),
    theLastSHat(x.theLastSHat), theLastY(x.theLastY),
    theLastP1P2(x.theLastP1P2), theLastL1L2(x.theLastL1L2),
    theLastX1X2(x.theLastX1X2), theLastE1E2(x.theLastE1E2),
    theLastScale(x.theLastScale), theMaxEnergy(x.theMaxEnergy),
    theME(x.theME), theDiagrams(x.theDiagrams),
    isMirror(x.isMirror), theNDim(x.theNDim), partonDims(x.partonDims),
    theMEMomenta(x.theMEMomenta), theMEPartons(x.theMEPartons),
    theMEPartonData(x.theMEPartonData),
    theLastDiagramIndex(x.theLastDiagramIndex), theMEInfo(x.theMEInfo) {}

XComb::~XComb() {
  if ( thePartonBinInfo.first ) delete thePartonBinInfo.first;
  if ( thePartonBinInfo.second ) delete thePartonBinInfo.second;
}

void XComb::clean() {
  theLastParticles = PPair();
  theLastPartons = PPair();
  theLastS = theLastSHat = theLastScale = 0.0*GeV2;
  theLastY = 0.0;
  theLastP1P2 = theLastL1L2 = theLastX1X2 = theLastE1E2 = DPair(0.0, 0.0);
  theLastOutgoing.clear();
}

void XComb::prepare(const PPair & inc) {
  clean();
  theLastParticles = inc;
  pExtractor()->prepare(partonBins());
}

void XComb::prepareNEW(const PPair & inc) {
  clean();
  theLastParticles = inc;
  pExtractor()->prepare(partonBinInstances());
}

void XComb::setPartonBinInfo() {
  if ( !thePartonBinInfo.first )
    thePartonBinInfo.first = partonBins().first->createInfo();
  partonBins().first->setInfo(thePartonBinInfo.first, lastParticles().first);
  if ( !thePartonBinInfo.second )
    thePartonBinInfo.second = partonBins().second->createInfo();
  partonBins().second->setInfo(thePartonBinInfo.second, lastParticles().second);
}

void XComb::setPartonBinInfoNEW() {
  if ( !thePartonBinInstances.first )
    thePartonBinInstances.first =
      new_ptr(PartonBinInstance(partonBins().first));
  if ( !thePartonBinInstances.second )
    thePartonBinInstances.second =
      new_ptr(PartonBinInstance(partonBins().second));
}

CrossSection XComb::
dSigDR(const pair<double,double> ll, int nr, const double * r) {
  Timer<7> timera("XComb::dSigDR()");
  CrossSection zero = 0.0*nanobarn;
  ++theNAttempted;

  pExtractor()->select(this);
  setPartonBinInfo();
  theLastP1P2 = ll;
  theLastS = sqr(maxEnergy())/exp(lastP1() + lastP2());

  Timer<22> timerb("XComb::dSigDR():generateL");
  if ( !pExtractor()->generateL(partonBins(), r, r + nr - partonDims.second) )
    return zero;

  theLastSHat = lastS()/exp(partonBins().first->lastL() +
			    partonBins().second->lastL());
  theLastPartons = make_pair(partonBins().first->lastParton(),
			     partonBins().second->lastParton());

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
  
  Timer<23> timerc("XComb::dSigDR():generateKinematics-1");
  matrixElement()->setXComb(this);
  if ( !matrixElement()->generateKinematics(r + partonDims.first) ) return zero;
  lastScale(matrixElement()->scale());

  Timer<24> timerd("XComb::dSigDR():generateSHat");
  theLastSHat = pExtractor()->generateSHat(lastS(), partonBins(),
					   r, r + nr - partonDims.second);

  if ( !cuts()->sHat(lastSHat()) ) return zero;

  r += partonDims.first;

  theLastX1X2 = make_pair(lastPartons().first->momentum().plus()/
			  lastParticles().first->momentum().plus(),
			  lastPartons().second->momentum().minus()/
			  lastParticles().second->momentum().minus());
  theLastL1L2 = make_pair(-log(lastX1()), -log(lastX2()));

  if ( !cuts()->x1(lastX1()) || !cuts()->x2(lastX2()) ) return zero;
  
  theLastE1E2 = make_pair(Math::exp1m(-lastL1()), Math::exp1m(-lastL2()));

  theLastY = (lastPartons().first->momentum() +
	      lastPartons().second->momentum()).rapidity();
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
  Timer<25> timere("XComb::dSigDR():generateKinematics-2");
  if ( !matrixElement()->generateKinematics(r) ) return zero;
  for ( int i = 2, N = meMomenta().size(); i < N; ++i )
    if ( !cuts()->pTHat(meMomenta()[i].perp()) ) return zero;
  Timer<26> timerf("XComb::dSigDR():dSigHatDR");
  CrossSection xsec = matrixElement()->dSigHatDR();
  lastScale(matrixElement()->scale());
  if ( !cuts()->scale(lastScale()) ) return zero;

  return xsec * pExtractor()->fullFn(partonBins(), lastScale()) *
    matrixElement()->reWeight() * matrixElement()->preWeight();
}

CrossSection XComb::
dSigDRNEW(const pair<double,double> ll, int nr, const double * r) {
  Timer<7> timera("XComb::dSigDR()");
  CrossSection zero = 0.0*nanobarn;
  ++theNAttempted;

  pExtractor()->select(this);
  setPartonBinInfoNEW();
  theLastP1P2 = ll;
  theLastS = sqr(maxEnergy())/exp(lastP1() + lastP2());

  Timer<22> timerb("XComb::dSigDR():generateL");
  if ( !pExtractor()->generateL(partonBinInstances(),
				r, r + nr - partonDims.second) )
    return zero;

  theLastSHat = lastS()/exp(partonBinInstances().first->l() +
			    partonBinInstances().second->l());
  theLastPartons = make_pair(partonBinInstances().first->parton(),
			     partonBinInstances().second->parton());

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
  
  Timer<23> timerc("XComb::dSigDR():generateKinematics-1");
  matrixElement()->setXComb(this);
  if ( !matrixElement()->generateKinematics(r + partonDims.first) ) return zero;
  lastScale(matrixElement()->scale());

  Timer<24> timerd("XComb::dSigDR():generateSHat");
  theLastSHat = pExtractor()->generateSHat(lastS(), partonBinInstances(),
					   r, r + nr - partonDims.second);

  if ( !cuts()->sHat(lastSHat()) ) return zero;

  r += partonDims.first;

  theLastX1X2 = make_pair(lastPartons().first->momentum().plus()/
			  lastParticles().first->momentum().plus(),
			  lastPartons().second->momentum().minus()/
			  lastParticles().second->momentum().minus());
  theLastL1L2 = make_pair(-log(lastX1()), -log(lastX2()));

  if ( !cuts()->x1(lastX1()) || !cuts()->x2(lastX2()) ) return zero;
  
  theLastE1E2 = make_pair(Math::exp1m(-lastL1()), Math::exp1m(-lastL2()));

  theLastY = (lastPartons().first->momentum() +
	      lastPartons().second->momentum()).rapidity();
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
  Timer<25> timere("XComb::dSigDR():generateKinematics-2");
  if ( !matrixElement()->generateKinematics(r) ) return zero;
  for ( int i = 2, N = meMomenta().size(); i < N; ++i )
    if ( !cuts()->pTHat(meMomenta()[i].perp()) ) return zero;
  Timer<26> timerf("XComb::dSigDR():dSigHatDR");
  CrossSection xsec = matrixElement()->dSigHatDR();
  lastScale(matrixElement()->scale());
  if ( !cuts()->scale(lastScale()) ) return zero;

  return xsec * pExtractor()->fullFn(partonBinInstances(), lastScale()) *
    matrixElement()->reWeight() * matrixElement()->preWeight();
}

void XComb::construct(tSubProPtr sub) {
  Timer<27> timera("XComb::construct()");

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
}

void XComb::constructNEW(tSubProPtr sub) {
  Timer<27> timera("XComb::construct()");

  matrixElement()->setXComb(this);
  setPartonBinInfoNEW();
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
}

void XComb::Init() {}

void XComb::persistentOutput(PersistentOStream & os) const {

  os << theCollisionHandler << theSubProcessHandler << thePartonExtractor
     << theCuts << theParticles << thePartons << thePartonBins << theNAttempted
     << theNAccepted << theSumWeight << theLastParticles << theLastPartons
     << ounit(theLastS, GeV2) << ounit(theLastSHat, GeV2) << theLastY
     << theLastP1P2 << theLastL1L2 << theLastX1X2 << theLastE1E2
     << ounit(theLastScale, GeV2) << ounit(theLastOutgoing, GeV)
     << ounit(theMaxEnergy, GeV) << theME << theDiagrams << isMirror << theNDim
     << partonDims << ounit(theMEMomenta, GeV) << theMEPartons
     << theMEPartonData << theLastDiagramIndex << theMEInfo;
}

void XComb::persistentInput(PersistentIStream & is, int) {
  is >> theCollisionHandler >> theSubProcessHandler >> thePartonExtractor
     >> theCuts >> theParticles >> thePartons >> thePartonBins >> theNAttempted
     >> theNAccepted >> theSumWeight >> theLastParticles >> theLastPartons
     >> iunit(theLastS, GeV2) >> iunit(theLastSHat, GeV2) >> theLastY
     >> theLastP1P2 >> theLastL1L2 >> theLastX1X2 >> theLastE1E2
     >> iunit(theLastScale, GeV2) >> iunit(theLastOutgoing, GeV)
     >> iunit(theMaxEnergy, GeV) >> theME >> theDiagrams >> isMirror >> theNDim
     >> partonDims >> iunit(theMEMomenta, GeV) >> theMEPartons
     >> theMEPartonData >> theLastDiagramIndex >> theMEInfo;
  if ( thePartonBinInfo.first ) delete thePartonBinInfo.first;
  if ( thePartonBinInfo.second ) delete thePartonBinInfo.second;
  thePartonBinInfo.first = thePartonBinInfo.second = 0;
}

ClassDescription<XComb> XComb::initXComb;

