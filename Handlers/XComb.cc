// -*- C++ -*-
//
// XComb.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the XComb class.
//

#include "XComb.h"
#include "ThePEG/Handlers/EventHandler.h"
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
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Vectors/LorentzRotation.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/MatrixElement/ColourLines.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "XComb.tcc"
#endif

using namespace ThePEG;

XComb::XComb()
  : theLastS(Energy2()), theLastSHat(Energy2()), theLastY(0.0),
    theLastP1P2(make_pair(1.0, 1.0)), theLastL1L2(make_pair(1.0, 1.0)),
    theLastX1X2(make_pair(1.0, 1.0)), theLastE1E2(make_pair(0.0, 0.0)),
    theLastScale(0.0*GeV2), theLastAlphaS(-1.0), theLastAlphaEM(-1.0),
    theMaxEnergy(0.0*GeV) {}

XComb::
XComb(Energy newMaxEnergy, const cPDPair & inc, tEHPtr newEventHandler,
      tPExtrPtr newExtractor, tCascHdlPtr newCKKW, const PBPair & newPartonBins,
      tCutsPtr newCuts)
  : theEventHandler(newEventHandler),
    thePartonExtractor(newExtractor), theCKKW(newCKKW), theCuts(newCuts),
    theParticles(inc), thePartonBins(newPartonBins), theLastS(Energy2()),
    theLastSHat(Energy2()), theLastY(0.0), theLastP1P2(make_pair(1.0, 1.0)),
    theLastL1L2(make_pair(1.0, 1.0)), theLastX1X2(make_pair(1.0, 1.0)),
    theLastE1E2(make_pair(0.0, 0.0)), theLastScale(0.0*GeV2),
    theLastAlphaS(-1.0), theLastAlphaEM(-1.0), theMaxEnergy(newMaxEnergy) {
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
    thePartonExtractor(x.thePartonExtractor), theCKKW(x.theCKKW),
    theCuts(x.theCuts), theParticles(x.theParticles),
    thePartons(x.thePartons), thePartonBins(x.thePartonBins),
    theParticleBins(x.theParticleBins),
    thePartonBinInstances(x.thePartonBinInstances),
    theLastParticles(x.theLastParticles),
    theLastPartons(x.theLastPartons), theLastS(x.theLastS),
    theLastSHat(x.theLastSHat), theLastY(x.theLastY),
    theLastP1P2(x.theLastP1P2), theLastL1L2(x.theLastL1L2),
    theLastX1X2(x.theLastX1X2), theLastE1E2(x.theLastE1E2),
    theLastScale(x.theLastScale), theLastAlphaS(x.theLastAlphaS),
    theLastAlphaEM(x.theLastAlphaEM), theMaxEnergy(x.theMaxEnergy),
    theMEInfo(x.theMEInfo), theSub(x.theSub) {}

XComb::~XComb() {}

void XComb::clean() {
  theLastParticles = PPair();
  theLastPartons = PPair();
  theLastS = theLastSHat = theLastScale = 0.0*GeV2;
  theLastAlphaS = theLastAlphaEM = -1.0;
  theLastY = 0.0;
  theLastP1P2 = theLastL1L2 = theLastX1X2 = theLastE1E2 = DPair(0.0, 0.0);
  theSub = SubProPtr();
  thePartonBinInstances = PBIPair();
}

void XComb::prepare(const PPair & inc) {
  clean();
  createPartonBinInstances();
  theLastParticles = inc;
  pExtractor()->prepare(partonBinInstances());
}

void XComb::subProcess(tSubProPtr sp) {
  theSub = sp;
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

  os << theEventHandler << thePartonExtractor << theCKKW
     << theCuts << theParticles << thePartons << thePartonBins
     << theParticleBins << thePartonBinInstances
     << theLastParticles << theLastPartons
     << ounit(theLastS, GeV2) << ounit(theLastSHat, GeV2) << theLastY
     << theLastP1P2 << theLastL1L2 << theLastX1X2 << theLastE1E2
     << ounit(theLastScale, GeV2) << theLastAlphaS << theLastAlphaEM
     << ounit(theMaxEnergy, GeV) << theMEInfo << theSub;
}

void XComb::persistentInput(PersistentIStream & is, int) {
  is >> theEventHandler >> thePartonExtractor >> theCKKW
     >> theCuts >> theParticles >> thePartons >> thePartonBins
     >> theParticleBins >> thePartonBinInstances
     >> theLastParticles >> theLastPartons
     >> iunit(theLastS, GeV2) >> iunit(theLastSHat, GeV2) >> theLastY
     >> theLastP1P2 >> theLastL1L2 >> theLastX1X2 >> theLastE1E2
     >> iunit(theLastScale, GeV2) >> theLastAlphaS >> theLastAlphaEM
     >> iunit(theMaxEnergy, GeV) >> theMEInfo >> theSub;
}

ClassDescription<XComb> XComb::initXComb;

