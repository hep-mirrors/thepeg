// -*- C++ -*-
//
// StandardEventHandler.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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
#include "ThePEG/Utilities/LoopGuard.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/MatrixElement/MEBase.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Handlers/SamplerBase.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/Config/algorithm.h"
#include <iomanip>
#include <sstream>

using namespace ThePEG;

StandardEventHandler::StandardEventHandler()
  : EventHandler(false), theBinStrategy(2), weightedEvents(false),
    theLumiDim(0) {
  setupGroups();
}

StandardEventHandler::~StandardEventHandler() {}

void StandardEventHandler::reject(double w) {
  tStdXCombPtr last = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( !last ) return;
  last->reject(w);
}

void StandardEventHandler::doupdate() {
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

void StandardEventHandler::doinit() {
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
    cPDPair din(diag[i]->partons()[0], diag[i]->partons()[1]);
    if ( din.first->id() < din.second->id() ) swap(din.first, din.second);
    if ( din == pin ) tdiag[diag[i]->getTag()].push_back(diag[i]);
    if ( din.first == pin.second && din.second == pin.first )
      tmdiag[diag[i]->getTag()].push_back(diag[i]);
  }

  if ( tdiag.empty() ) tdiag = tmdiag;
  for ( DiagramMap::iterator dit = tdiag.begin(); dit != tdiag.end(); ++dit ) {
    cPDPair din(dit->second.back()->partons()[0],
		dit->second.back()->partons()[1]);
    StdXCombPtr xcomb =
      new_ptr(StandardXComb(maxEnergy, incoming(), this, sub, extractor,
			    ckkw, pBins, cuts, me, dit->second, din != pin));
    if ( xcomb->checkInit() ) xCombs().push_back(xcomb);
    else generator()->logWarning(
      StandardEventHandlerInitError() << "The matrix element '"
      << xcomb->matrixElement()->name() 
      << "' cannot generate the diagram '"
      << dit->first 
      << "' when used together with the parton extractor '"
      << xcomb->pExtractor()->name()
      << "'.\nThe corresponding diagram is switched off, " 
      << "check the collision energy and/or the cuts."
      << Exception::warning);
  }
}

void StandardEventHandler::initGroups() {
  tStdXCombPtr lastXC = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( lastXC ) optGroups = lastXC->subProcessHandler()->groups();
  EventHandler::initGroups();
}

tCollPtr StandardEventHandler::performCollision() {
  tStdXCombPtr lastXC = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( CKKWHandler() ) CKKWHandler()->setXComb(lastXCombPtr());
  lastExtractor()->select(lastXC);
  currentCollision(new_ptr(Collision(lastParticles(), currentEvent(), this)));
  if ( currentEvent() ) currentEvent()->addCollision(currentCollision());
  currentStep(new_ptr(Step(currentCollision())));
  currentCollision()->addStep(currentStep());

  currentStep()->addSubProcess(lastXC->construct());

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
  CrossSection sum = ZERO;
  for ( int i = 0, N = xv.size(); i < N; ++i )
    xSecs()[i] = ( sum += xv[i]->dSigDR(ll, nr, r) );
  return sum;
}

tStdXCombPtr StandardEventHandler::select(int bin, double & weight) {

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
  lastXC->matrixElement()->setXComb(lastXC);
  weight /= lastXC->matrixElement()->preWeight();
  lastXC->select(weight);
  lastXC->accept();
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

  Stat() : attempted(0), accepted(0), sumw(0.0), sumw2(),
	   maxXSec(CrossSection()), totsum(0.0) {}
  Stat(long att, long acc, double w, double w2, CrossSection x,
       double sumw, double genrerr)
    : attempted(att), accepted(acc), sumw(w), sumw2(w2), maxXSec(x),
      totsum(sumw), totrerr(genrerr) {}

  inline CrossSection xSec() const {
    return totsum >0.0? maxXSec*sumw/totsum: maxXSec;
  }

  inline CrossSection xSecErr() const {
    if ( totsum <= 0.0 ) return maxXSec;
    if ( sumw <= 0.0 ) return xSec();
    return xSec()*sqrt(sqr(totrerr) + sumw2/sqr(sumw));
  }

  long attempted;
  long accepted;
  double sumw;
  double sumw2;
  CrossSection maxXSec;
  double totsum;
  double totrerr;

  const Stat & operator+= (const Stat & s) {
    attempted += s.attempted;
    accepted += s.accepted;
    sumw += s.sumw;
    sumw2 += s.sumw2;
    totsum = max(totsum, s.totsum);
    if ( totsum > 0.0 )
      maxXSec = max(maxXSec, s.maxXSec);
    else
      maxXSec += s.maxXSec;
    totrerr = s.totrerr;
    return *this;
  }
};
 
void StandardEventHandler::statistics(ostream & os) const {
  if ( statLevel() == 0 ) return;
  map<cPDPair, Stat> partonMap;
  map<MEPtr, Stat> meMap;
  map<PExtrPtr, Stat> extractMap;
  Stat tot;
  double genrerr = sampler()->integratedXSecErr()/sampler()->integratedXSec();

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s(x.stats().attempts(), x.stats().accepted(),
	   x.stats().sumWeights(), x.stats().sumWeights2(),
	   sampler()->integratedXSec(), sampler()->sumWeights(), genrerr);
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
     << tot.attempted << setw(17)
     << ouniterr(tot.xSec(),tot.xSecErr() , nanobarn)
     << endl << line;

  if ( statLevel() == 1 ) return;

  os << "Per matrix element breakdown:\n";
  for ( map<MEPtr, Stat>::iterator i = meMap.begin();
	i != meMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  if ( statLevel() == 2 ) return;

  os << "Per parton extractor breakdown:\n";
  for ( map<PExtrPtr, Stat>::iterator i = extractMap.begin();
	i != extractMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  os << "Per incoming partons breakdown:\n";
  for ( map<cPDPair, Stat>::iterator i = partonMap.begin();
	i != partonMap.end(); ++i ) {
    string n = i->first.first->PDGName() + " " + i->first.second->PDGName();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.accepted << setw(13)
       << i->second.attempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  if ( statLevel() == 3 ) return;

  os << "Detailed breakdown:\n";
  CrossSection xsectot = sampler()->integratedXSec()/sampler()->sumWeights();

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    os << "(" << x.pExtractor()->name() << ") "
       << x.partons().first->PDGName() << " "
       << x.partons().second->PDGName()
      
       << " (" << x.matrixElement()->name() << " "
       << x.lastDiagram()->getTag() << ") " << endl
       << setw(48) << x.stats().accepted() << setw(13) << x.stats().attempts()
       << setw(17)
       << ouniterr(x.stats().sumWeights()*xsectot,
		   sqrt(x.stats().sumWeights2())*xsectot, nanobarn) << endl;
  }

  os << line;

}

CrossSection StandardEventHandler::histogramScale() const {
  Stat tot;
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), x.stats().sumWeights2(),
	     sampler()->integratedXSec(), sampler()->sumWeights(), 1.0);
    tot += s;
  }

  return tot.xSec()/tot.sumw;
}

CrossSection StandardEventHandler::integratedXSec() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();

  Stat tot;
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), x.stats().sumWeights2(),
	     sampler()->integratedXSec(), sampler()->sumWeights(), 1.0);
    tot += s;
  }

  return tot.xSec();
}

CrossSection StandardEventHandler::integratedXSecErr() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();

  Stat tot;
  double genrerr = sampler()->integratedXSecErr()/sampler()->integratedXSec();
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.stats().attempts(), x.stats().accepted(),
	     x.stats().sumWeights(), x.stats().sumWeights2(),
	     sampler()->integratedXSec(), sampler()->sumWeights(), genrerr);
    tot += s;
  }

  return tot.xSecErr();

}

void StandardEventHandler::doinitrun() {
  EventHandler::doinitrun();
  for ( SubHandlerList::iterator sit = subProcesses().begin();
	sit != subProcesses().end(); ++sit )
    (**sit).initrun();
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

    try {

      lumiFn().select(lastXC);

      currentEventBoost() = lumiFn().getBoost();

      currentEvent(new_ptr(Event(lastParticles(), this, generator()->runName(),
				 generator()->currentEventNumber(), weight)));

      performCollision();
      if ( !currentCollision() ) throw Veto();

      currentEvent()->transform(currentEventBoost());

      return currentEvent();

    }
    catch (Veto) {
      reject(weight);
    }
    catch (Stop) {
      break;
    }
    catch (Exception &) {
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
  catch (Exception &) {
    reject(currentEvent()->weight());
    throw;
  }
  return currentEvent(); 
}

void StandardEventHandler::dofinish() {
  if ( theLastXComb ) theLastXComb->clean();
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

