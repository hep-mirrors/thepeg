// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardEventHandler class.
//

#include "StandardEventHandler.h"
#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Utilities/LoopGuard.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Handlers/SamplerBase.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/Config/algorithm.h"

using namespace ThePEG;

StandardEventHandler::StandardEventHandler()
  : EventHandler(false), theBinStrategy(2), weightedEvents(false),
    theLumiDim(0) {
  setupGroups();
}

StandardEventHandler::StandardEventHandler(const StandardEventHandler & eh)
  : EventHandler(eh), theIncomingA(eh.theIncomingA),
    theIncomingB(eh.theIncomingB), theSubProcesses(eh.theSubProcesses),
    theCuts(eh.theCuts), theXCombs(eh.theXCombs), theXSecs(eh.theXSecs),
    theBinStrategy(eh.theBinStrategy), theMEXMap(eh.theMEXMap),
    theMaxDims(eh.theMaxDims), theCurrentEventBoost(eh.theCurrentEventBoost),
    weightedEvents(eh.weightedEvents),
    theSampler(eh.theSampler),
    theLumiDim(eh.theLumiDim) {}

StandardEventHandler::~StandardEventHandler() {}

void StandardEventHandler::reject(double) {
  tStdXCombPtr last = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( !last ) return;
  last->reject();
}

void StandardEventHandler::doupdate() throw(UpdateException) {
  EventHandler::doupdate();
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
      throw StandardEventHandlerUpdateException()
	<<  "Cannot use the parton extractor '" << (**sit).pExtractor()->name()
	<< "' in the SubProcessHandler '" << (**sit).name() << "' in the "
	<< "StandardEventHandler '" << name() << "' since it cannot handle "
	<< "the requested types of incoming particles ("
	<< theIncomingA->name() << "," << theIncomingB->name() << ").";
}

void StandardEventHandler::doinit() throw(InitException) {
  EventHandler::doinit();
  if ( !lumiFnPtr() ) throw StandardEventHandlerUpdateException()
    << "The StandardEventHandler '" << name() << "' does not have any "
    << "LuminosityFunction object assigned to it, which it needs to be "
    << "able to generate events." << Exception::warning;
}

IBPtr StandardEventHandler::clone() const {
  return new_ptr(*this);
}

IBPtr StandardEventHandler::fullclone() const {
  return new_ptr(*this);
}

void StandardEventHandler::
addME(Energy maxEnergy, tSubHdlPtr sub, tPExtrPtr extractor, tCutsPtr cuts,
      tCascHdlPtr ckkw, tMEPtr me, const PBPair & pBins) {
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
    StdXCombPtr xcomb =
      new_ptr(StandardXComb(maxEnergy, incoming(), this, sub, extractor,
			    ckkw, pBins, cuts, me, dit->second, mirror));
    if ( xcomb->checkInit() ) xCombs().push_back(xcomb);
    else generator()->logWarning(
      StandardEventHandlerInitError() << "The matrix element '"
      << xcomb->matrixElement()->name() << "' cannot generate the diagram '"
      << dit->first << "' when used together with the parton extractor '"
      << xcomb->pExtractor()->name()
      << "'. The corresponding diagram is switched off." << Exception::warning);
  }
}

void StandardEventHandler::initGroups() {
  tStdXCombPtr lastXC = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( lastXC ) optGroups = lastXC->subProcessHandler()->groups();
  EventHandler::initGroups();
}

tCollPtr StandardEventHandler::performCollision() {
  Timer<6> timer1("StandardEventHandler::performCollision()");
  tStdXCombPtr lastXC = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( CKKWHandler() ) CKKWHandler()->setXComb(lastXCombPtr());
  lastExtractor()->select(lastXC);
  currentCollision(new_ptr(Collision(lastParticles(), currentEvent(), this)));
  if ( currentEvent() ) currentEvent()->addCollision(currentCollision());
  currentStep(new_ptr(Step(currentCollision())));
  currentCollision()->addStep(currentStep());

  Timer<36> timer2("StandardEventHandler::performCollision():2");
  currentStep()->addSubProcess(lastXC->construct());

  Timer<37> timer3("StandardEventHandler::performCollision():3");
  lastExtractor()->construct(lastXC->partonBinInstances(), currentStep());
  if ( !lastCuts().passCuts(*currentCollision()) ) throw Veto();
  initGroups();
  if ( ThePEG_DEBUG_ITEM(1) ) {
    if ( currentEvent() )    
      generator()->logfile() << *currentEvent();
    else
      generator()->logfile() << *currentCollision();
  }
  return continueCollision();
}

void StandardEventHandler::setScale(Energy2 scale) {
  lastXCombPtr()->lastScale(scale);
}

void StandardEventHandler::initialize() {

  theLumiDim = lumiFn().nDim(incoming());
  Energy maxEnergy = lumiFn().maximumCMEnergy();

  xCombs().clear();
  xSecs().clear();

  cuts()->initialize(sqr(maxEnergy), lumiFn().Y());

  for ( SubHandlerList::const_iterator sit = subProcesses().begin();
	sit != subProcesses().end(); ++sit ) {
    CutsPtr kincuts = (**sit).cuts()? (**sit).cuts(): cuts();
    if ( (**sit).cuts() ) kincuts->initialize(sqr(maxEnergy), lumiFn().Y());
    PExtrPtr pextract = (**sit).pExtractor();

    tCascHdlPtr ckkw = (**sit).CKKWHandler();
    if ( !ckkw ) ckkw = CKKWHandler();

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
	addME(maxEnergy, *sit, pextract, kincuts, ckkw, *meit, *ppit);
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

  sampler()->setEventHandler(this);
  sampler()->initialize();
}

CrossSection StandardEventHandler::
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

tStdXCombPtr StandardEventHandler::select(int bin, double weight) {

  int i = upper_bound(xSecs().begin(), xSecs().end(), rnd()*xSecs().back())
      - xSecs().begin();
  tStdXCombPtr lastXC;
  switch ( binStrategy() ) {
  case 0:
    lastXC = xCombs()[i];
    break;
  case 1: {
    MEXMap::iterator mei = theMEXMap.begin();
    for ( int j = 0; j < bin; ++j) ++mei;
    lastXC = mei->second[i];
    break;
  } 
  case 2:
    lastXC = xCombs()[bin];
    break;
  }
  // clean up the old XComb object before switching to a new one
  if ( theLastXComb && theLastXComb != lastXC ) theLastXComb->clean();
  theLastXComb = lastXC;
  lastXC->select(weight);
  lastXC->accept();
  lastXC->matrixElement()->setXComb(lastXC);
  return lastXC;
}

int StandardEventHandler::nBins() const {
  switch ( binStrategy() ) {
  case 0: return 1;
  case 1: return theMEXMap.size();
  case 2: return xCombs().size();
  }
  return -1;
}

struct Stat {

  Stat() : attempted(0), accepted(0), sumw(0.0), maxXSec(CrossSection()),
    totsum(0.0) {}
  Stat(long att, long acc, double w, CrossSection x, double sumw)
    : attempted(att), accepted(acc), sumw(w), maxXSec(x),
      totsum(sumw) {}

  inline CrossSection xSec() const {
    return maxXSec*sumw/totsum;
  }

  long attempted;
  long accepted;
  double sumw;
  CrossSection maxXSec;
  double totsum;

  const Stat & operator+= (const Stat & s) {
    attempted += s.attempted;
    accepted += s.accepted;
    sumw += s.sumw;
    totsum = max(totsum, s.totsum);
    if ( totsum > 0.0 )
      maxXSec = max(maxXSec, s.maxXSec);
    else
      maxXSec += s.maxXSec;
    return *this;
  }
};
 

void StandardEventHandler::statistics(ostream & os) const {
  if ( statLevel() == 0 ) return;
  map<cPDPair, Stat> partonMap;
  map<MEPtr, Stat> meMap;
  map<PExtrPtr, Stat> extractMap;
  Stat tot;

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), sampler()->integratedXSec(),
	     sampler()->sumWeights());
    partonMap[x.partons()] += s;
    meMap[x.matrixElement()] += s;
    extractMap[x.pExtractor()] += s;
    tot += s;
  }

  string line = "======================================="
    "=======================================\n";

  if ( tot.accepted <= 0 ) {
    os << line << "No events generated by event handler '" << name() << "'."
       << endl;
      return;
  }

  os << line << "Statistics for event handler \'" << name() << "\':\n"
     << "                                       "
     << "generated    number of    Cross-section\n"
     << "                                       "
     << "   events     attempts             (nb)\n";

  os << line << "Total:" << setw(42) << tot.accepted << setw(13)
     << tot.attempted << setw(17) << tot.xSec()/nanobarn << endl
     << line;

  if ( statLevel() == 1 ) return;

  os << "Per matrix element breakdown:\n";
  for ( map<MEPtr, Stat>::iterator i = meMap.begin();
	i != meMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17) << i->second.xSec()/nanobarn << endl;
  }
  os << line;

  if ( statLevel() == 2 ) return;

  os << "Per parton extractor breakdown:\n";
  for ( map<PExtrPtr, Stat>::iterator i = extractMap.begin();
	i != extractMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17) << i->second.xSec()/nanobarn << endl;
  }
  os << line;

  os << "Per incoming partons breakdown:\n";
  for ( map<cPDPair, Stat>::iterator i = partonMap.begin();
	i != partonMap.end(); ++i ) {
    string n = i->first.first->PDGName() + " " + i->first.second->PDGName();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17) << i->second.xSec()/nanobarn << endl;
  }
  os << line;

  if ( statLevel() == 3 ) return;

  os << "Detailed breakdown:\n";
  double xsectot = sampler()->integratedXSec()/
    (sampler()->sumWeights()*nanobarn);
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    os << "(" << x.pExtractor()->name() << ") "
       << x.partons().first->PDGName() << " "
       << x.partons().second->PDGName()
      
       << " (" << x.matrixElement()->name() << " "
       << x.lastDiagram()->getTag() << ") " << endl
       << setw(48) << x.stats().accepted() << setw(13) << x.stats().attempts()
       << setw(17) << x.stats().sumWeights()*xsectot << endl;
  }

  os << line;

}

CrossSection StandardEventHandler::histogramScale() const {
  Stat tot;
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), sampler()->integratedXSec(),
	     sampler()->sumWeights());
    tot += s;
  }

  return tot.xSec()/tot.sumw;
}

CrossSection StandardEventHandler::integratedXSec() const {
  Stat tot;
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), sampler()->integratedXSec(),
	     sampler()->sumWeights());
    tot += s;
  }

  return tot.xSec();
}

void StandardEventHandler::doinitrun() {
  EventHandler::doinitrun();
  sampler()->initrun();
  for ( int i = 0, N = xCombs().size(); i < N; ++i )
    xCombs()[i]->reset();
}

CrossSection StandardEventHandler::dSigDR(const vector<double> & r) {
  double jac = 1.0;
  pair<double,double> ll = lumiFn().generateLL(&r[0], jac);
  Energy2 maxS = sqr(lumiFn().maximumCMEnergy())/exp(ll.first + ll.second);
  int bin = sampler()->lastBin();
  CrossSection x = jac*lumiFn().value(incoming(), ll.first, ll.second)
    *dSigDR(ll, maxS, bin, nDim(bin) - lumiDim(), &r[lumiDim()]);
  return x;
}

EventPtr StandardEventHandler::generateEvent() {

  LoopGuard<EventLoopException,StandardEventHandler>
    loopGuard(*this, maxLoop());

  while (1) {
    loopGuard();

    clean();

    double weight = sampler()->generate();

    tStdXCombPtr lastXC = select(sampler()->lastBin(), weight);
    weight /= lastXC->matrixElement()->preWeight();

    try {

      lumiFn().select(lastXC);

      currentEventBoost() = lumiFn().getBoost();

      currentEvent(new_ptr(Event(lastParticles(), this, generator()->runName(),
				 generator()->currentEventNumber(), weight)));

      //      cerr << endl << "Constructing the event..."; //////DEBUG//////

      performCollision();
      if ( !currentCollision() ) throw Veto();

      currentEvent()->transform(currentEventBoost());
      //      cerr << endl << "Done." << endl; //////DEBUG//////
      return currentEvent();

    }
    catch (Veto) {
      reject(weight);
    }
    catch (Stop) {
      break;
    }
    catch (Exception & ex) {
      reject(weight);
      throw;
    }
  }
  return currentEvent();
}

EventPtr StandardEventHandler::continueEvent() {
  if ( !generator() ) throw StandardEventHandlerInitError()
    << "The event handler '" << name() << "' had not been isolated "
    << "from the setup phase before it was used." << Exception::maybeabort;
  try {
    continueCollision();
  }
  catch (Veto) {
    reject(currentEvent()->weight());
  }
  catch (Stop) {
  }
  catch (Exception & ex) {
    reject(currentEvent()->weight());
    throw;
  }
  return currentEvent(); 
}

void StandardEventHandler::dofinish() {
  EventHandler::dofinish();
}

ClassDescription<StandardEventHandler>
StandardEventHandler::initStandardEventHandler;	// 

void StandardEventHandler::Init() {

  static ClassDocumentation<StandardEventHandler> documentation
    ("This is the standard event handler to generate hard sub-processes "
     "within ThePEG. It must specify a pair of incoming particle beams "
     "in <interface>BeamA</interface> and <interface>BeamB</interface> "
     "and a suiteable <interface>LuminosityFunction</interface>. In "
     "addition at least one object describing the sub-processes to be "
     "generated must be specified in "
     "<interface>SubProcessHandlers</interface>.");

  static Reference<StandardEventHandler,ParticleData> interfaceIncomingA
    ("BeamA",
     "The type of particles in first beam",
     &StandardEventHandler::theIncomingA, false, false, true, false);

  static Reference<StandardEventHandler,ParticleData> interfaceIncomingB
    ("BeamB",
     "The type of particles in second beam",
     &StandardEventHandler::theIncomingB, false, false, true, false);

  static RefVector<StandardEventHandler,SubProcessHandler> interfaceSubhandlers
    ("SubProcessHandlers",
     "The list of sub-process handlers used in this StandardEventHandler. ",
     &StandardEventHandler::theSubProcesses, 0, false, false, true, false);

  static Reference<StandardEventHandler,Cuts> interfaceCuts
    ("Cuts",
     "Common kinematical cuts for this StandardEventHandler. These cuts "
     "may be overidden in individual sub-process handlers.",
     &StandardEventHandler::theCuts, false, false, true, false);

  static Switch<StandardEventHandler,int> interfaceBinStrategy
    ("BinStrategy",
     "The strategy to be used when sampling different ThePEG::XComb "
     "objects. An ThePEG::XComb objet represents a pair of incoming "
     "parton types as defined by a THePEG::PartonExtractor and a "
     "matrix element.",
     &StandardEventHandler::theBinStrategy, 2, false, false);

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

  static Switch<StandardEventHandler,bool> interfaceWeighted
    ("Weighted",
     "If switched on, this event Handler will produce weighted events",
     &StandardEventHandler::weightedEvents, true, false);
  static SwitchOption interfaceWeightedTrue
    (interfaceWeighted, "On",
     "This EventHandeler produces weighted events.", true);
  static SwitchOption interfaceWeightedFalse
    (interfaceWeighted, "Off",
     "This EventHandeler produces unweighted events.", false);

  static Reference<StandardEventHandler,SamplerBase> interfaceSampler
    ("Sampler",
     "The phase space sampler responsible for generating phase space"
     "points according to the cross section given by this event handler",
     &StandardEventHandler::theSampler, false, false, true, true);

  interfaceSubhandlers.rank(11);
  interfaceIncomingA.rank(3);
  interfaceIncomingB.rank(2);

}

void StandardEventHandler::persistentOutput(PersistentOStream & os) const {
  os << theIncomingA << theIncomingB << theSubProcesses << theCuts
     << theXCombs << ounit(theXSecs, nanobarn)
     << theBinStrategy << theMaxDims << theMEXMap
     << weightedEvents
     << theSampler << theLumiDim;
}

void StandardEventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theIncomingA >> theIncomingB >> theSubProcesses >> theCuts
     >> theXCombs >> iunit(theXSecs, nanobarn)
     >> theBinStrategy >> theMaxDims>> theMEXMap
     >> weightedEvents
     >> theSampler >> theLumiDim;
}

