// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the EventHandler class.
//

#include "EventHandler.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
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

using namespace ThePEG;

EventHandler::EventHandler()
  : weightedEvents(false), theMaxLoop(100000), theStatLevel(2),
    theLumiDim(0), theNDim(0) {}

EventHandler::EventHandler(const EventHandler & eh)
  : CollisionHandler(eh), theLumiFn(eh.theLumiFn),
    weightedEvents(eh.weightedEvents), theMaxLoop(eh.theMaxLoop),
    theStatLevel(eh.theStatLevel), theSampler(eh.theSampler),
    theLumiDim(eh.theLumiDim), theNDim(eh.theNDim) {}

EventHandler::~EventHandler() {}

void EventHandler::lumiFn(LumiFnPtr newLumiFn) {
  if ( newLumiFn->canHandle(incoming()) ) theLumiFn = newLumiFn;
  else throw EventLumiFnErr(*this, *newLumiFn);
}

void EventHandler::reject(double weight) {
  if ( !lastXCombPtr() ) return;
  lastXCombPtr()->unAccept();
  lastXCombPtr()->sumWeight(-weight);
}

void EventHandler::doupdate() throw(UpdateException) {
  CollisionHandler::doupdate();
  bool redo = touched();
  UpdateChecker::check(theLumiFn, redo);
  if ( !redo ) return;
  if ( !lumiFn().canHandle(incoming()) ) throw EventLumiFnErr(*this, lumiFn());
}

IBPtr EventHandler::clone() const {
  return new_ptr(*this);
}

IBPtr EventHandler::fullclone() const {
  return new_ptr(*this);
}

struct Stat {

  Stat() : attempted(0), accepted(0), sumw(0.0), maxXSec(CrossSection()),
    totsum(0.0) {}
  Stat(long att, long acc, double w, CrossSection x, double sumw)
    : attempted(att), accepted(acc), sumw(w), maxXSec(x*sqr(hbarc)),
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
 

void EventHandler::statistics(ostream & os) const {
  if ( statLevel() == 0 ) return;
  map<cPDPair, Stat> partonMap;
  map<MEPtr, Stat> meMap;
  map<PExtrPtr, Stat> extractMap;
  Stat tot;

  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const XComb & x = *xCombs()[i];
    Stat s;
    s = Stat(x.nAttempted(), x.nAccepted(), x.sumWeight(),
	     sampler()->integratedXSec(), sampler()->sumWeights());
    partonMap[x.partons()] += s;
    meMap[x.matrixElement()] += s;
    extractMap[x.pExtractor()] += s;
    tot += s;
  }


  string line = "======================================="
    "=======================================\n";

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
  double xsectot = sampler()->integratedXSec()*sqr(hbarc)/
    (sampler()->sumWeights()*nanobarn);
  for ( int i = 0, N = xCombs().size(); i < N; ++i ) {
    const XComb & x = *xCombs()[i];
    os << "(" << x.pExtractor()->name() << ") "
       << x.partons().first->PDGName() << " "
       << x.partons().second->PDGName()
      
       << " (" << x.matrixElement()->name() << " "
       << x.lastDiagram()->getTag() << ") " << endl
       << setw(48) << x.nAccepted() << setw(13) << x.nAttempted()
       << setw(17) << x.sumWeight()*xsectot << endl;
  }

  os << line;

}

void EventHandler::initialize() {
  theLumiDim = lumiFn().nDim(incoming());
  CollisionHandler::initialize(lumiFn().maximumCMEnergy());
  sampler()->setEventHandler(this);
  sampler()->initialize();
}

double EventHandler::dSigDR(const vector<double> & r) {
  double jac = 1.0;
  pair<double,double> ll = lumiFn().generateLL(&r[0], jac);
  Energy2 maxS = sqr(lumiFn().maximumCMEnergy())/exp(ll.first + ll.second);
  int bin = sampler()->lastBin();
  CrossSection x = jac*lumiFn().value(incoming(), ll.first, ll.second)
    *CollisionHandler::dSigDR(ll, maxS, bin,
			      nDim(bin) - lumiDim(), &r[lumiDim()]);
  return x;
}

EventPtr EventHandler::generateEvent() {

  LoopGuard<EventLoopException,EventHandler> loopGuard(*this, maxLoop());

  while (1) {
    loopGuard();

    clean();

    double weight = sampler()->generate();

    select(sampler()->lastBin(), weight);
    weight /= lastXComb().matrixElement()->preWeight();

    try {

      lumiFn().select(lastXCombPtr());

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

EventPtr EventHandler::continueEvent() {
  if ( !generator() ) throw EventInitException(*this);
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

void EventHandler::dofinish() {
  CollisionHandler::dofinish();
}

ClassDescription<EventHandler> EventHandler::initEventHandler;

void EventHandler::Init() {

  static Reference<EventHandler,LuminosityFunction> interfaceLumifn
    ("LuminosityFunction",
     "An object derived from the \\classname{LuminosityFunction} class, "
     "which describes the beams in the collider under study.",
     &EventHandler::theLumiFn, false, false, true, false,
     &EventHandler::lumiFn);

  static Parameter<EventHandler,long> interfaceMaxLoop
    ("MaxLoop",
     "The maximum number of attempts per event when selecting a sub-process.",
     &EventHandler::theMaxLoop, 100000, 100, 100000000, true, false, true);

  static Switch<EventHandler,int> interfaceStatLevel
    ("StatLevel",
     "Controlls the amount of statistics written out after each run to "
     "the EventGenerators .out file.",
     &EventHandler::theStatLevel, 2, true, false);
  static SwitchOption interfaceStatLevelNone
    (interfaceStatLevel, "None", "No statistics is written out.", 0);
  static SwitchOption interfaceStatLevelTot
    (interfaceStatLevel, "TotalXSec",
     "Only the total cross-section is written out.", 1);
  static SwitchOption interfaceStatLevelME
    (interfaceStatLevel, "MatrixElements",
     "The cross-section for each matrix element is written out.", 2);
  static SwitchOption interfaceStatLevelBins
    (interfaceStatLevel, "Bins",
     "The cross-section per matrix element, per parton extractor, etc. "
     "is written out.", 3);
  static SwitchOption interfaceStatLevelFull
    (interfaceStatLevel, "Full",
     "A detailed account of the cross-sections of the generated sub-processes "
     "is written out.", 4);

  static Switch<EventHandler,bool> interfaceWeighted
    ("Weighted",
     "If switched on, this event Handler will produce weighted events",
     &EventHandler::weightedEvents, true, false);
  static SwitchOption interfaceWeightedTrue
    (interfaceWeighted, "On",
     "This EventHandeler produces weighted events.", true);
  static SwitchOption interfaceWeightedFalse
    (interfaceWeighted, "Off",
     "This EventHandeler produces unweighted events.", false);

  static Reference<EventHandler,SamplerBase> interfaceSampler
    ("Sampler",
     "The phase space sampler responsible for generating phase space"
     "points according to the cross section given by this event handler",
     &EventHandler::theSampler, false, false, true, true);

}

void EventHandler::persistentOutput(PersistentOStream & os) const {
  os << theLumiFn << weightedEvents << theMaxLoop << theStatLevel
     << theSampler << theLumiDim << theNDim;
}

void EventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theLumiFn >> weightedEvents >> theMaxLoop >> theStatLevel
     >> theSampler >> theLumiDim >> theNDim;
}

EventInitException::EventInitException(const EventHandler & i) {
  theMessage << "The event handler '" << i.name() << "' had not been isolated "
	     << "from the setup phase before it was used.";
  severity(maybeabort);
}

EventLumiFnErr::
EventLumiFnErr(const EventHandler & eh, const LuminosityFunction& lf) {
  theMessage << "Cannot use '" << lf.name() << "' as the luminosity function "
	     << "in the event handler '" << eh.name() << " since it cannot "
	     << "handle the requested incoming particles.";
  severity(warning);
}

EventInitNoXSec::EventInitNoXSec(const EventHandler & eh) {
  theMessage << "The event handler '" << eh.name() << "' cannot be initialized "
	     << "because the cross-section for the selected sub-processes "
	     << "was zero.";
  severity(maybeabort);
}

EventLoopException::EventLoopException(const EventHandler & eh) {
  theMessage << "The maximum number of attempts per event (" << eh.maxLoop()
	     << ") in event handler '" << eh.name() << "' was exceeded.";
  severity(maybeabort);
}

