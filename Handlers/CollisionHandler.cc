// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CollisionHandler class.
//

#include "CollisionHandler.h"
#include "ThePEG/Handlers/Hint.h"

#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Handlers/MultipleInteractionHandler.h"
#include "ThePEG/Handlers/HadronizationHandler.h"
#include "ThePEG/Handlers/DecayHandler.h"
#include "ThePEG/Handlers/KinematicalCuts.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Repository/EventGenerator.h"

using namespace ThePEG;

CollisionHandler::CollisionHandler()
  : theBinStrategy(2) {
  setupGroups();
}

CollisionHandler::~CollisionHandler() {}

CollisionHandler::CollisionHandler(const CollisionHandler & ch)
  : PartialCollisionHandler(ch), theIncomingA(ch.theIncomingA),
    theIncomingB(ch.theIncomingB), theSubProcesses(ch.theSubProcesses),
    theCuts(ch.theCuts), theXCombs(ch.theXCombs), theXSecs(ch.theXSecs),
    theBinStrategy(ch.theBinStrategy), theMEXMap(ch.theMEXMap),
    theMaxDims(ch.theMaxDims), theCurrentEventBoost(ch.theCurrentEventBoost) {}

void CollisionHandler::doupdate() throw(UpdateException) {
  HandlerBase::doupdate();
  bool redo = touched();
  UpdateChecker::check(theIncomingA, redo);
  UpdateChecker::check(theIncomingB, redo);
  for_each(subProcesses(), UpdateChecker(redo));
  if ( !redo ) return;
  theIncoming.first = theIncomingA;
  theIncoming.second = theIncomingB;
  for ( SubHandlerList::iterator sit = subProcesses().begin();
	sit != subProcesses().end(); ++sit )
    if ( !(**sit).pExtractor()->canHandle(incoming()) )
      throw CollHdlExtractorError(*this, **sit, *((**sit).pExtractor()),
				  incoming());
}

void CollisionHandler::doinit() throw(InitException) {
  HandlerBase::doinit();
}

void CollisionHandler::dofinish() {
  HandlerBase::dofinish();
}

IBPtr CollisionHandler::clone() const {
  return new_ptr(*this);
}

IBPtr CollisionHandler::fullclone() const {
  return new_ptr(*this);
}

void CollisionHandler::
addME(Energy maxEnergy, tSubHdlPtr sub, tPExtrPtr extractor, tKinCutPtr cuts,
      tMEPtr me, const PBPair & pBins) {
  typedef MEBase::DiagramVector DiagramVector;
  typedef map<string,DiagramVector> DiagramMap;
  cPDPair pin(pBins.first->parton(), pBins.second->parton());
  DiagramVector diag = me->diagrams();
  DiagramMap tdiag;
  DiagramMap tmdiag;
  for ( int i = 0, N = diag.size(); i < N; ++i ) {
    if ( diag[i]->partons()[0] == pin.first &&
	 diag[i]->partons()[1] == pin.second )
      tdiag[diag[i]->getTag()].push_back(diag[i]);
    if ( diag[i]->partons()[0] == pin.second &&
	 diag[i]->partons()[1] == pin.first )
      tmdiag[diag[i]->getTag()].push_back(diag[i]);
  }

  bool mirror = false;
  if ( ( mirror = tdiag.empty() ) ) tdiag = tmdiag;
  for ( DiagramMap::iterator dit = tdiag.begin(); dit != tdiag.end(); ++dit ) {
    XCombPtr xcomb = new_ptr(XComb(maxEnergy, incoming(), this, sub, extractor,
				   pBins, cuts, me, dit->second, mirror));
    if ( xcomb->checkInit() ) xCombs().push_back(xcomb);
    else generator()->logWarning(
      CollHdlInitWarning() << "The matrix element '"
      << xcomb->matrixElement()->name() << "' cannot generate the diagram '"
      << dit->first << "' when used together with the parton extractor '"
      << xcomb->pExtractor()->name()
      << "'. The corresponding diagram is switched off." << Exception::warning);
  }
}

void CollisionHandler::initGroups() {
  optGroups = lastSubHandler().groups();
  PartialCollisionHandler::initGroups();
}

tCollPtr CollisionHandler::performCollision() {
  Timer<6> timer1("CollisionHandler::performCollision()");
  lastExtractor()->select(lastXCombPtr());
  currentCollision(new_ptr(Collision(lastParticles(), currentEvent(), this)));
  if ( currentEvent() ) currentEvent()->addCollision(currentCollision());
  currentStep(new_ptr(Step(currentCollision())));
  currentCollision()->addStep(currentStep());
  SubProPtr sub =
    new_ptr(SubProcess(lastPartons(), currentCollision(), lastME()));
  Timer<36> timer2("CollisionHandler::performCollision():2");
  lastXCombPtr()->construct(sub);
  Timer<37> timer3("CollisionHandler::performCollision():3");
  currentStep()->addSubProcess(sub);
  lastExtractor()->construct(lastXCombPtr()->partonBinInstances(),
			     currentStep());
  lastCuts().cut(*currentCollision(), currentEventBoost());
  initGroups();
  if ( ThePEG_DEBUG_ITEM(1) ) {
    if ( currentEvent() )    
      generator()->logfile() << *currentEvent();
    else
      generator()->logfile() << *currentCollision();
  }
  return continueCollision();
}

void CollisionHandler::setScale(Energy2 scale) {
  lastXCombPtr()->lastScale(scale);
}

void CollisionHandler::initialize(Energy maxEnergy) {

  xCombs().clear();
  xSecs().clear();

  for ( SubHandlerList::const_iterator sit = subProcesses().begin();
	sit != subProcesses().end(); ++sit ) {
    KinCutPtr kincuts = (**sit).cuts()? (**sit).cuts(): cuts();
    PExtrPtr pextract = (**sit).pExtractor();

    PartonPairVec vpc = pextract->getPartons(maxEnergy, incoming(), *kincuts);

    // The last parton bin pair was in fact the bins corresponding to
    // the incoming particles, so we remove them, but save them to
    // keep them referenced.
    PBPair orig = vpc.back();
    vpc.pop_back();
    for ( PartonPairVec::iterator ppit = vpc.begin();
	  ppit != vpc.end(); ++ppit )
      for ( MEVector::const_iterator meit = (**sit).MEs().begin();
	    meit != (**sit).MEs().end(); ++meit )
	addME(maxEnergy, *sit, pextract, kincuts, *meit, *ppit);
  }
  xSecs().resize(xCombs().size());

  theMaxDims.clear();
  switch ( binStrategy() ) {
  case 0: {
    theMaxDims.push_back(0);
    for ( int i = 0, N = xCombs().size(); i < N; ++i )
      theMaxDims[0] = max(theMaxDims[0], xCombs()[i]->nDim());
    break;
  }
  case 1: {
    for ( int i = 0, N = xCombs().size(); i < N; ++i )
      theMEXMap[xCombs()[i]->matrixElement()].push_back(xCombs()[i]);
    MEXMap::const_iterator mei = theMEXMap.begin();
    for ( int i = 0, N = theMEXMap.size(); i < N; ++i, ++mei) {
      theMaxDims.push_back(0);
      for ( int j = 0, M = mei->second.size(); j < M; ++j )
	theMaxDims[i] = max(theMaxDims[i], mei->second[j]->nDim());
    }
    break;
  }
  case 2: {
    for ( int i = 0, N = xCombs().size(); i < N; ++i )
      theMaxDims.push_back(xCombs()[i]->nDim());
    break;
  }
  }

}

CrossSection CollisionHandler::
dSigDR(const pair<double,double> ll, Energy2 maxS,
       int ibin, int nr, const double * r) {
  PPair inc = make_pair(incoming().first->produceParticle(),
			incoming().second->produceParticle());
  SimplePhaseSpace::CMS(inc, maxS);

  XVector xv;
  switch ( binStrategy() ) {
  case 0:
    xv = xCombs();
    break;
  case 1: {
    MEXMap::iterator mei = theMEXMap.begin();
    for ( int i = 0; i < ibin; ++i) ++mei;
    xv = mei->second;
    break;
  }
  case 2:
    xv = XVector(1, xCombs()[ibin]);
    break;
  }
    
  xSecs().resize(xv.size());
  for ( int i = 0, N = xv.size(); i < N; ++i ) xv[i]->prepare(inc);
  CrossSection sum = 0.0*nanobarn;
  for ( int i = 0, N = xv.size(); i < N; ++i )
    xSecs()[i] = ( sum += xv[i]->dSigDR(ll, nr, r) );
  return sum;
}

void CollisionHandler::select(int bin, double weight) {

  int i = upper_bound(xSecs().begin(), xSecs().end(), rnd()*xSecs().back())
      - xSecs().begin();
  switch ( binStrategy() ) {
  case 0:
    theLastXComb = xCombs()[i];
    break;
  case 1: {
    MEXMap::iterator mei = theMEXMap.begin();
    for ( int j = 0; j < bin; ++j) ++mei;
    theLastXComb = mei->second[i];
    break;
  } 
  case 2:
    theLastXComb = xCombs()[bin];
    break;
  }
  lastXCombPtr()->sumWeight(weight);
  lastXCombPtr()->accept();
  lastXCombPtr()->matrixElement()->setXComb(lastXCombPtr());
}

int CollisionHandler::nBins() const {
  switch ( binStrategy() ) {
  case 0: return 1;
  case 1: return theMEXMap.size();
  case 2: return xCombs().size();
  }
  return -1;
}

void CollisionHandler::persistentOutput(PersistentOStream & os) const {
  os << theIncomingA << theIncomingB << theIncoming
     << theSubProcesses << theCuts << theXCombs << ounit(theXSecs, nanobarn)
     << theBinStrategy << theMaxDims << theMEXMap;
}

void CollisionHandler::persistentInput(PersistentIStream & is, int) {
  is >> theIncomingA >> theIncomingB >> theIncoming
     >> theSubProcesses >> theCuts  >> theXCombs >> iunit(theXSecs, nanobarn)
     >> theBinStrategy >> theMaxDims>> theMEXMap;
}

ClassDescription<CollisionHandler> CollisionHandler::initCollisionHandler;

void CollisionHandler::Init() {

  static Reference<CollisionHandler,ParticleData> interfaceIncomingA
    ("BeamA",
     "The type of particles in first beam",
     &CollisionHandler::theIncomingA, false, false, true, false);

  static Reference<CollisionHandler,ParticleData> interfaceIncomingB
    ("BeamB",
     "The type of particles in second beam",
     &CollisionHandler::theIncomingB, false, false, true, false);

  static RefVector<CollisionHandler,SubProcessHandler> interfaceSubhandlers
    ("SubProcessHandlers",
     "The list of sub-process handlers used in this CollisionHandler. ",
     &CollisionHandler::theSubProcesses, 0, false, false, true, false);

  static Reference<CollisionHandler,KinematicalCuts> interfaceCuts
    ("Cuts",
     "Common kinematical cuts for this CollisionHandler. These cuts "
     "may be overidden in individual sub-process handlers.",
     &CollisionHandler::theCuts, false, false, true, false);

  static Switch<CollisionHandler,int> interfaceBinStrategy
    ("BinStrategy",
     "The strategy to be used when sampling different \\classname{XComb} "
     "objects. An \\classname{XComb} object represent a pair of incoming "
     "parton types s as defined by a \\classname{PartonExtractor} and a "
     "matrix element.",
     &CollisionHandler::theBinStrategy, 2, false, false);

  static SwitchOption interfaceBinStrategy0
    (interfaceBinStrategy,
     "AllAtOnce",
     "All bins are sampled together.",
     0);

  static SwitchOption interfaceBinStrategy1
    (interfaceBinStrategy,
     "PerME",
     "All bins which have the same matrix element object are sampled together.",
     1);

  static SwitchOption interfaceBinStrategy2
    (interfaceBinStrategy,
     "Individual",
     "All bins are sampled individually.",
     2);

}

CollHdlExtractorError::
CollHdlExtractorError(const CollisionHandler & ch, const SubProcessHandler & sh,
		      const PartonExtractor & px, const cPDPair & pp) {
  theMessage << "Cannot use the parton extractor '" << px.name()
	     << "' in the SubProcessHandler '" << sh.name() << "' in the "
	     << "CollisionHandler '" << ch.name() << "' since it cannot handle "
	     << "the requested types of incoming particles ("
	     << pp.first->name() << "," << pp.second->name() << ").";
  severity(warning);
}

