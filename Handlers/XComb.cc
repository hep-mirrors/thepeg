// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the XComb class.
//

#include "XComb.h"
#include "ThePEG/Handlers/EventHandler.h"
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
  : theLastS(Energy2()), theLastSHat(Energy2()), theLastY(0.0),
    theLastP1P2(make_pair(1.0, 1.0)), theLastL1L2(make_pair(1.0, 1.0)),
    theLastX1X2(make_pair(1.0, 1.0)), theLastE1E2(make_pair(0.0, 0.0)),
    theLastScale(0.0*GeV2), theMaxEnergy(0.0*GeV) {}

XComb::
XComb(Energy newMaxEnergy, const cPDPair & inc, tEHPtr newEventHandler,
      tPExtrPtr newExtractor, const PBPair & newPartonBins, tKinCutPtr newCuts)
  : theEventHandler(newEventHandler),
    thePartonExtractor(newExtractor), theCuts(newCuts), theParticles(inc),
    thePartonBins(newPartonBins), theLastS(Energy2()), theLastSHat(Energy2()),
    theLastY(0.0), theLastP1P2(make_pair(1.0, 1.0)),
    theLastL1L2(make_pair(1.0, 1.0)), theLastX1X2(make_pair(1.0, 1.0)),
    theLastE1E2(make_pair(0.0, 0.0)), theLastScale(0.0*GeV2),
    theMaxEnergy(newMaxEnergy) {
  thePartons = cPDPair(partonBins().first->parton(),
		       partonBins().second->parton());
  thePartonBinInstances.first =
    new_ptr(PartonBinInstance(partonBins().first));
  thePartonBinInstances.second =
    new_ptr(PartonBinInstance(partonBins().second));
  theParticleBins.first = thePartonBins.first->getFirst();
  theParticleBins.second = thePartonBins.second->getFirst();
}

XComb::XComb(const XComb & x)
  : Base(x),
    theEventHandler(x.theEventHandler),
    thePartonExtractor(x.thePartonExtractor),
    theCuts(x.theCuts), theParticles(x.theParticles),
    thePartons(x.thePartons), thePartonBins(x.thePartonBins),
    theParticleBins(x.theParticleBins),
    thePartonBinInstances(x.thePartonBinInstances),
    theLastParticles(x.theLastParticles),
    theLastPartons(x.theLastPartons), theLastS(x.theLastS),
    theLastSHat(x.theLastSHat), theLastY(x.theLastY),
    theLastP1P2(x.theLastP1P2), theLastL1L2(x.theLastL1L2),
    theLastX1X2(x.theLastX1X2), theLastE1E2(x.theLastE1E2),
    theLastScale(x.theLastScale), theMaxEnergy(x.theMaxEnergy) {}

XComb::~XComb() {}

void XComb::clean() {
  theLastParticles = PPair();
  theLastPartons = PPair();
  theLastS = theLastSHat = theLastScale = 0.0*GeV2;
  theLastY = 0.0;
  theLastP1P2 = theLastL1L2 = theLastX1X2 = theLastE1E2 = DPair(0.0, 0.0);
}

void XComb::prepare(const PPair & inc) {
  clean();
  theLastParticles = inc;
  pExtractor()->prepare(partonBinInstances());
}

void XComb::setPartonBinInfo() {
  partonBinInstances().first->getFirst()->parton(lastParticles().first);
  partonBinInstances().second->getFirst()->parton(lastParticles().second);
}

void XComb::createPartonBinInstances() {
  thePartonBinInstances.first =
    new_ptr(PartonBinInstance(partonBins().first));
  thePartonBinInstances.second =
    new_ptr(PartonBinInstance(partonBins().second));
}

void XComb::setPartonBinInstances(PBIPair pbip, Energy2 scale) {
  clean();
  thePartonBinInstances = pbip;
  theLastParticles = PPair(pbip.first->getFirst()->parton(),
			   pbip.second->getFirst()->parton());
  theLastPartons = PPair(pbip.first->parton(),
			 pbip.second->parton());
  lastS((lastParticles().first->momentum() +
	 lastParticles().second->momentum()).m2());
  lastSHat((lastPartons().first->momentum() +
	    lastPartons().second->momentum()).m2());
  lastP1P2(make_pair(0.0, 0.0));
  lastX1X2(make_pair(lastPartons().first->momentum().plus()/
		     lastParticles().first->momentum().plus(),
		     lastPartons().second->momentum().minus()/
		     lastParticles().second->momentum().minus()));
  lastY(log(lastX1()/lastX2())*0.5);
  lastScale(scale);
}


void XComb::Init() {}

void XComb::persistentOutput(PersistentOStream & os) const {

  os << theEventHandler << thePartonExtractor
     << theCuts << theParticles << thePartons << thePartonBins
     << theParticleBins << thePartonBinInstances
     << theLastParticles << theLastPartons
     << ounit(theLastS, GeV2) << ounit(theLastSHat, GeV2) << theLastY
     << theLastP1P2 << theLastL1L2 << theLastX1X2 << theLastE1E2
     << ounit(theLastScale, GeV2) << ounit(theMaxEnergy, GeV);
}

void XComb::persistentInput(PersistentIStream & is, int) {
  is >> theEventHandler >> thePartonExtractor
     >> theCuts >> theParticles >> thePartons >> thePartonBins
     >> theParticleBins >> thePartonBinInstances
     >> theLastParticles >> theLastPartons
     >> iunit(theLastS, GeV2) >> iunit(theLastSHat, GeV2) >> theLastY
     >> theLastP1P2 >> theLastL1L2 >> theLastX1X2 >> theLastE1E2
     >> iunit(theLastScale, GeV2) >> iunit(theMaxEnergy, GeV);
}

ClassDescription<XComb> XComb::initXComb;

