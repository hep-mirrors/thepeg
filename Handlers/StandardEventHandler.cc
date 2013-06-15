// -*- C++ -*-
//
// StandardEventHandler.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
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
#include "ThePEG/Handlers/StdXCombGroup.h"
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
#include "ThePEG/MatrixElement/MEGroup.h"
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
  : EventHandler(false), collisionCuts(true), theBinStrategy(2),
    theLumiDim(0) {
  setupGroups();
}

StandardEventHandler::~StandardEventHandler() {}

void StandardEventHandler::reject(double w) {
  tStdXCombPtr last = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( !last ) return;
  last->reject(w);
}

void StandardEventHandler::reweight(double factor) const {
  tStdXCombPtr last = dynamic_ptr_cast<tStdXCombPtr>(lastXCombPtr());
  if ( !currentEvent() || !last )
    return;
  double weight = currentEvent()->weight();
  last->reweight(weight,factor*weight);
  currentEvent()->weight(factor*weight);
  for ( map<string,double>::iterator w = 
	  currentEvent()->optionalWeights().begin();
	w != currentEvent()->optionalWeights().end(); ++w )
    w->second *= factor;
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
      tCascHdlPtr ckkw, tMEPtr me, const PBPair & pBins,
      const PartonPairVec& allPBins) {
  typedef MEBase::DiagramVector DiagramVector;
  typedef map<string,DiagramVector> DiagramMap;
  cPDPair pin(pBins.first->parton(), pBins.second->parton());
  DiagramVector diag = me->diagrams();
  DiagramMap tdiag;
  DiagramMap tmdiag;
  for ( int i = 0, N = diag.size(); i < N; ++i ) {
    cPDPair din(diag[i]->partons()[0], diag[i]->partons()[1]);
    if (!me->noMirror())
      if ( din.first->id() < din.second->id() ) swap(din.first, din.second); 
    if ( din == pin ) tdiag[diag[i]->getTag()].push_back(diag[i]);
    if (!me->noMirror())
      if ( din.first == pin.second && din.second == pin.first )
	tmdiag[diag[i]->getTag()].push_back(diag[i]);
  }

  if ( tdiag.empty() ) tdiag = tmdiag;
  for ( DiagramMap::iterator dit = tdiag.begin(); dit != tdiag.end(); ++dit ) {
    cPDPair din(dit->second.back()->partons()[0],
		dit->second.back()->partons()[1]);
    // check
    assert(me->noMirror() ? din == pin : true);
    StdXCombPtr xcomb = me->makeXComb(maxEnergy, incoming(), this, sub, extractor,
				      ckkw, pBins, cuts, dit->second, din != pin,
				      allPBins);
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
  if ( collisionCuts )
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
	    meit != (**sit).MEs().end(); ++meit ) {
	addME(maxEnergy, *sit, pextract, kincuts, ckkw, *meit, *ppit,vpc);
      }
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

  int i = 0;
  if ( binStrategy() != 2 )
    i = upper_bound(xSecs().begin(), xSecs().end(), rnd()*xSecs().back())
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

struct StatisticsBase {

  double sumWeights;
  double sumWeights2;
  CrossSection integratedXSec;
  CrossSection integratedXSecErr;

  double nPointsEffective;
  CrossSection referenceXSec;

  double sumWeightsGenerated;
  double sumWeights2Generated;

  double sumWeightsGeneratedNoReweight;
  double sumWeights2GeneratedNoReweight;

  unsigned long nPointsGenerated;
  unsigned long nPointsAttempted;

  StatisticsBase()
    : sumWeights(0.0), sumWeights2(0.0),
      integratedXSec(ZERO), integratedXSecErr(ZERO),
      nPointsEffective(0.0), referenceXSec(ZERO),
      sumWeightsGenerated(0.0), sumWeights2Generated(0.0),
      sumWeightsGeneratedNoReweight(0.0), sumWeights2GeneratedNoReweight(0.0),
      nPointsGenerated(0), nPointsAttempted(0) {}

  explicit StatisticsBase(tcSamplerPtr referenceSampler)
    : sumWeights(referenceSampler->sumWeights()),
      sumWeights2(referenceSampler->sumWeights2()),
      integratedXSec(referenceSampler->integratedXSec()),
      integratedXSecErr(referenceSampler->integratedXSecErr()),
      nPointsEffective(sumWeights != 0.0 ? sumWeights*
		       (sqr(integratedXSec)-sqr(integratedXSecErr))/
		       (sumWeights2*sqr(integratedXSec)/sumWeights-sumWeights*sqr(integratedXSecErr)) : ZERO),
      referenceXSec(sumWeights != 0.0 ? nPointsEffective*integratedXSec/sumWeights : ZERO),
	    sumWeightsGenerated(0.0), sumWeights2Generated(0.0), 
	    sumWeightsGeneratedNoReweight(0.0), sumWeights2GeneratedNoReweight(0.0),
	    nPointsGenerated(0), nPointsAttempted(0) {}
		 
  StatisticsBase& operator+=(const XSecStat& xstat) {
    sumWeightsGenerated += xstat.sumWeights();
    sumWeights2Generated += xstat.sumWeights2();
    sumWeightsGeneratedNoReweight += xstat.sumWeightsNoReweight();
    sumWeights2GeneratedNoReweight += xstat.sumWeights2NoReweight();
    nPointsGenerated += xstat.accepted();
    nPointsAttempted += xstat.attempts();
    return *this;
  }
  
  CrossSection xSec() const {
    if ( sumWeights == 0.0 )
      return integratedXSec;
    return integratedXSec*sumWeightsGenerated/sumWeights;
  }

  CrossSection xSecErr() const {
    if ( sumWeights == 0.0 )
      return integratedXSec;

    double denom = abs(nPointsEffective*sumWeights2 - sqr(sumWeights));
    if ( denom == 0 )
      return xSec();

    double num = abs(nPointsEffective*sumWeights2Generated - sqr(sumWeightsGenerated));
    return 
      integratedXSecErr*sqrt(num/denom);
  }

  CrossSection xSecNoReweight() const {
    if ( sumWeights == 0.0 )
      return integratedXSec;
    return integratedXSec*sumWeightsGeneratedNoReweight/sumWeights;
  }

  CrossSection xSecErrNoReweight() const {
    if ( sumWeights == 0.0 )
      return integratedXSec;
    return 
      integratedXSecErr*
      sqrt(abs(nPointsEffective*sumWeights2GeneratedNoReweight - sqr(sumWeightsGeneratedNoReweight))/
	   abs(nPointsEffective*sumWeights2 - sqr(sumWeights)));
  }

};
 
void StandardEventHandler::statistics(ostream & os) const {
  if ( statLevel() == 0 ) return;
  map<cPDPair, StatisticsBase> partonMap;
  map<MEPtr, StatisticsBase> meMap;
  map<PExtrPtr, StatisticsBase> extractMap;
  StatisticsBase tot(sampler());

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    if ( partonMap.find(x.partons()) == partonMap.end() )
      partonMap[x.partons()] = StatisticsBase(sampler());
    partonMap[x.partons()] += x.stats();
    if ( meMap.find(x.matrixElement()) == meMap.end() )
      meMap[x.matrixElement()] = StatisticsBase(sampler());
    meMap[x.matrixElement()] += x.stats();
    if ( extractMap.find(x.pExtractor()) == extractMap.end() )
      extractMap[x.pExtractor()] = StatisticsBase(sampler());
    extractMap[x.pExtractor()] += x.stats();
    tot += x.stats();
  }

  string line = string(78, '=') + "\n";

  if ( tot.nPointsGenerated <= 0 ) {
    os << line << "No events generated by event handler '" << name() << "'."
       << endl;
      return;
  }

  os << line << "Statistics for event handler \'" << name() << "\':\n"
     << "                                       "
     << "generated    number of    Cross-section\n"
     << "                                       "
     << "   events     attempts             (nb)\n";

  os << line << "Total (from   weighted events): including vetoed events" << setw(23)
     << ouniterr(sampler()->integratedXSec(), 
		 sampler()->integratedXSecErr(), nanobarn)
     << endl;
  os << line << "Total (from "
     << (weighted() ? "  weighted" : "unweighted") << " events):" 
     << setw(17) << tot.nPointsGenerated << setw(13)
     << tot.nPointsAttempted << setw(17)
     << ouniterr(tot.xSec(),tot.xSecErr() , nanobarn)
     << endl << line;

  if ( statLevel() == 1 ) return;

  os << "Per matrix element breakdown:\n";
  for ( map<MEPtr, StatisticsBase>::iterator i = meMap.begin();
	i != meMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.nPointsGenerated << setw(13)
       << i->second.nPointsAttempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  if ( statLevel() == 2 ) return;

  os << "Per parton extractor breakdown:\n";
  for ( map<PExtrPtr, StatisticsBase>::iterator i = extractMap.begin();
	i != extractMap.end(); ++i ) {
    string n = i->first->name();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.nPointsGenerated << setw(13)
       << i->second.nPointsAttempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  os << "Per incoming partons breakdown:\n";
  for ( map<cPDPair, StatisticsBase>::iterator i = partonMap.begin();
	i != partonMap.end(); ++i ) {
    string n = i->first.first->PDGName() + " " + i->first.second->PDGName();
    n.resize(37, ' ');
    os << n << setw(11) << i->second.nPointsGenerated << setw(13)
       << i->second.nPointsAttempted << setw(17)
       << ouniterr(i->second.xSec(), i->second.xSecErr(), nanobarn)
       << endl;
  }
  os << line;

  if ( statLevel() == 3 ) return;

  os << "Detailed breakdown:\n";

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    StatisticsBase xstat(sampler());
    xstat += x.stats();
    os << "(" << x.pExtractor()->name() << ") "
       << x.partons().first->PDGName() << " "
       << x.partons().second->PDGName()
       << " (" << x.matrixElement()->name() << " "
       << x.lastDiagram()->getTag() << ") " << endl
       << setw(48) << xstat.nPointsGenerated << setw(13) << xstat.nPointsAttempted
       << setw(17)
       << ouniterr(xstat.xSec(), xstat.xSecErr(), nanobarn) << endl;
  }

  os << line;

}

CrossSection StandardEventHandler::histogramScale() const {
  StatisticsBase tot(sampler());
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    tot += x.stats();
  }
  return tot.xSec()/tot.sumWeightsGenerated;
}

CrossSection StandardEventHandler::integratedXSec() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();
  StatisticsBase tot(sampler());
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    tot += x.stats();
  }
  return tot.xSec();
}

CrossSection StandardEventHandler::integratedXSecErr() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();
  StatisticsBase tot(sampler());
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    tot += x.stats();
  }
  return tot.xSecErr();
}

CrossSection StandardEventHandler::integratedXSecNoReweight() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();
  StatisticsBase tot(sampler());
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    tot += x.stats();
  }
  return tot.xSecNoReweight();
}

CrossSection StandardEventHandler::integratedXSecErrNoReweight() const {
  if ( sampler()->integratedXSec() == ZERO )
    return sampler()->maxXSec();
  StatisticsBase tot(sampler());
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const StandardXComb & x = *xCombs()[i];
    tot += x.stats();
  }
  return tot.xSecErrNoReweight();
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

    EventHandler::clean();

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
      reject(currentEvent()->weight());
    }
    catch (Stop) {
      break;
    }
    catch (Exception &) {
      reject(currentEvent()->weight());
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

void StandardEventHandler::select(tXCombPtr newXComb) {
  EventHandler::select(newXComb);
  lastExtractor()->select(newXComb);
}

void StandardEventHandler::clean() {
  if ( theLastXComb ) theLastXComb->clean();
  for (size_t i=0; i < theXCombs.size(); ++i )
    if ( theXCombs[i] ) theXCombs[i]->clean();
  EventHandler::clean();
}

void StandardEventHandler::dofinish() {
  clean();
  EventHandler::dofinish();
}

ClassDescription<StandardEventHandler>
StandardEventHandler::initStandardEventHandler;	// 

void StandardEventHandler::setIncomingA(PDPtr p) {
  theIncomingA = p;
  theIncoming.first = p;
}

void StandardEventHandler::setIncomingB(PDPtr p) {
  theIncomingB = p;
  theIncoming.second = p;
}

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
     &StandardEventHandler::theIncomingA, false, false, true, false,
     &StandardEventHandler::setIncomingA);

  static Reference<StandardEventHandler,ParticleData> interfaceIncomingB
    ("BeamB",
     "The type of particles in second beam",
     &StandardEventHandler::theIncomingB, false, false, true, false,
     &StandardEventHandler::setIncomingB);

  static RefVector<StandardEventHandler,SubProcessHandler> interfaceSubhandlers
    ("SubProcessHandlers",
     "The list of sub-process handlers used in this StandardEventHandler. ",
     &StandardEventHandler::theSubProcesses, 0, false, false, true, false);

  static Reference<StandardEventHandler,Cuts> interfaceCuts
    ("Cuts",
     "Common kinematical cuts for this StandardEventHandler. These cuts "
     "may be overidden in individual sub-process handlers.",
     &StandardEventHandler::theCuts, false, false, true, false);

  static Switch<StandardEventHandler,bool> interfaceCollisionCuts
    ("CollisionCuts",
     "Switch on or off cuts on collision objects",
     &StandardEventHandler::collisionCuts, true, false, false);
  static SwitchOption interfaceCollisionCutsOn
    (interfaceCollisionCuts,
     "On",
     "Switch on cuts on collision objects",
     true);
  static SwitchOption interfaceCollisionCutsOff
    (interfaceCollisionCuts,
     "Off",
     "Switch off cuts on collision cuts",
     false);

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
  os << theIncomingA << theIncomingB << theSubProcesses << theCuts << collisionCuts
     << theXCombs << ounit(theXSecs, nanobarn)
     << theBinStrategy << theMaxDims << theMEXMap
     << theSampler << theLumiDim;
}

void StandardEventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theIncomingA >> theIncomingB >> theSubProcesses >> theCuts >> collisionCuts
     >> theXCombs >> iunit(theXSecs, nanobarn)
     >> theBinStrategy >> theMaxDims>> theMEXMap
     >> theSampler >> theLumiDim;
}

