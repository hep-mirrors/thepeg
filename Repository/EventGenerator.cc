// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the EventGenerator class.
//

#include "EventGenerator.h"
#include "EventGenerator.xh"
#include "ThePEG/Handlers/EventHandler.h"
#include "Repository.h"
#include "ThePEG/Utilities/HoldFlag.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/MatcherBase.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Repository/Strategy.h"
#include "ThePEG/Repository/CurrentGenerator.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Handlers/SubProcessHandler.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Config/algorithm.h"
#include <cstdlib>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "EventGenerator.tcc"
#endif

using namespace ThePEG;

EventGenerator::EventGenerator()
  : thePath("."), theNumberOfEvents(1000), theQuickSize(7000), ieve(0),
    theDebugLevel(0), maxWarnings(10), maxErrors(10), theCurrentRandom(0),
    theCurrentGenerator(0) {}

EventGenerator::EventGenerator(const EventGenerator & eg)
  : Interfaced(eg), theDefaultObjects(eg.theDefaultObjects),
    theLocalParticles(eg.theLocalParticles),
    theStandardModel(eg.theStandardModel),
    theStrategy(eg.theStrategy), theRandom(eg.theRandom),
    thePath(eg.thePath), theRunName(eg.theRunName),
    theNumberOfEvents(eg.theNumberOfEvents), theObjects(eg.theObjects),
    theObjectMap(eg.theObjectMap),
    theParticles(eg.theParticles), theQuickParticles(eg.theQuickParticles),
    theQuickSize(eg.theQuickSize), theMatchers(eg.theMatchers),
    usedObjects(eg.usedObjects), theDebugLevel(eg.theDebugLevel),
    maxWarnings(eg.maxWarnings), maxErrors(eg.maxErrors), theCurrentRandom(0),
    theCurrentGenerator(0),
    theCurrentCollisionHandler(eg.theCurrentCollisionHandler),
    theCurrentStepHandler(eg.theCurrentStepHandler) {}

EventGenerator::~EventGenerator() {
  if ( theCurrentRandom ) delete theCurrentRandom;
  if ( theCurrentGenerator ) delete theCurrentGenerator;
}

void
EventGenerator::setup(string newRunName,
		      ObjectSet & newObjects,
		      ParticleMap & newParticles,
		      MatcherSet & newMatchers) {
  theRunName = newRunName;
  theObjects.swap(newObjects);
  theParticles.swap(newParticles);
  theMatchers.swap(newMatchers);
  theObjectMap.clear();
  for ( ObjectSet::const_iterator it = objects().begin();
	it != objects().end(); ++it ) theObjectMap[(**it).fullName()] = *it;
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  init();

}

IBPtr EventGenerator::getPointer(string name) const {
  ObjectMap::const_iterator it = objectMap().find(name);
  if ( it == objectMap().end() ) return IBPtr();
  else return it->second;
}

void EventGenerator::openOutputFiles() {
  logfile().open((filename() + ".log").c_str());
  outfile().open((filename() + ".out").c_str());
}

void EventGenerator::closeOutputFiles() {
  outfile().close();
  logfile().close();
}

void EventGenerator::doinit() throw (InitException) {

  Interfaced::doinit();
  random().init();

  UseRandom useRandom(theRandom);
  CurrentGenerator currentGenerator(this);

  theQuickParticles.clear();
  theQuickParticles.resize(2*theQuickSize);
  for ( ParticleMap::const_iterator pit = theParticles.begin();
	pit != theParticles.end(); ++pit )
    if ( abs(pit->second->id()) < theQuickSize )
      theQuickParticles[pit->second->id()+theQuickSize] = pit->second;

  // Then call the init method for all objects. Start with the
  // standard model and the strategy.
  standardModel()->init();
  if ( strategy() ) strategy()->init();
  for_each(objects(), mem_fun(&InterfacedBase::init));
}

void EventGenerator::doinitrun() {

  Interfaced::doinitrun();
  random().initrun();

  // Then call the init method for all objects. Start with the
  // standard model and the strategy.
  standardModel()->initrun();
  if ( strategy() ) strategy()->initrun();
  for_each(objects(), mem_fun(&InterfacedBase::initrun));

}

PDPtr EventGenerator::getParticleData(long newId) const {
  if ( abs(newId) < theQuickSize ) return theQuickParticles[newId+theQuickSize];
  ParticleMap::const_iterator it = theParticles.find(newId);
  if ( it == theParticles.end() ) return PDPtr();
  return it->second;
}

PPtr EventGenerator::getParticle(long newId) const {
  tcPDPtr pd = getParticleData(newId);
  if ( !pd ) return PPtr();
  return pd->produceParticle();
}

void EventGenerator::finalize() {
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  finish();
}

void EventGenerator::dofinish() {

  // Call the finish method for all other objects.
  for_each(objects(), mem_fun(&InterfacedBase::finish));

  generateReferences();

  if ( theExceptions.empty() ) {
    log() << "No exceptions reported in this run.\n";
  } else {

    log() << endl
	  << "The following exception classes were reported in this run:"
	  << endl;
    for ( ExceptionMap::iterator it = theExceptions.begin();
	  it != theExceptions.end(); ++it )
      log() << it->first->name() << " (" << it->second << " times)" << endl;
  }

  closeOutputFiles();

  if ( theCurrentRandom ) delete theCurrentRandom;
  if ( theCurrentGenerator ) delete theCurrentGenerator;
  theCurrentRandom = 0;
  theCurrentGenerator = 0;

}

void EventGenerator::initialize() {
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  doInitialize();
}

void EventGenerator::go(long next, long maxevent) {
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  doGo(next, maxevent);
}

EventPtr EventGenerator::shoot() {
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  return doShoot();
}

EventPtr EventGenerator::partialEvent(tEventPtr e) {
  UseRandom currentRandom(theRandom);
  CurrentGenerator currentGenerator(this);
  return doPartialEvent(e);
}

void EventGenerator::doInitialize() {

  openOutputFiles();

  init();
  initrun();

}

void EventGenerator::doGo(long next, long maxevent) {

  if ( maxevent >= 0 ) N(maxevent);

  initialize();

  ieve = next-1;

  try {
    while ( shoot() ) {}
  }
  catch ( ... ) {
    finish();
    throw;
  }

  finish();

}

Energy EventGenerator::maximumCMEnergy() const {
  return 0.0*GeV;
}

void EventGenerator::dump() const {
  PersistentOStream file((filename() + ".dump").c_str());
  file << tcEGPtr(this);
}

void EventGenerator::use(const Interfaced & i) {
  IBPtr ip = getPtr(i);
  if ( ip ) usedObjects.insert(ip);
}

void EventGenerator::generateReferences() {
  typedef map<string,string> StringMap;
  StringMap references;

  // First get all model descriptions and model references from the
  // used objects. Put them in a map indexed by the description to
  // avoid duplicates.
  for ( ObjectSet::iterator it = usedObjects.begin();
	it != usedObjects.end(); ++it )
    references[Repository::getModelDescription(*it)] =
      Repository::getModelReferences(*it);

  // Now get the main strategy description which should put first and
  // remove it from the map.
  string stratdesc;
  string stratref;
  if ( strategy() ) {
    stratdesc = Repository::getModelDescription(strategy());
    stratref = Repository::getModelReferences(strategy());
    references.erase(stratdesc);
  }

  // Open the file and write out an appendix header
  reffile().open((filename() + ".tex").c_str());
  reffile() << "\\documentclass{article}" << endl
	    << "\\usepackage{graphics}" << endl
	    << "\\begin{document}" << endl
	    << "\\appendix" << endl
	    << "\\section[xxx]{T\\scalebox{0.8}{HE}PEG\\cite{ThePEG} Run "
	    << "Information}" << endl << "Run name: \\textbf{" << runName()
	    << "}:\\\\\n";
  if ( !stratdesc.empty() )
    reffile() << "This run was generated using " << stratdesc <<
      " and the following models:\n";
  else
    reffile() << "The following models were used:\n";

  reffile() << "\\begin{itemize}" << endl;

  // Write out all descriptions.
  for ( StringMap::iterator it = references.begin();
	it != references.end(); ++it )
    reffile() << "\\item " << it->first << endl;

  // Write out thebibliography header and all references.
  reffile() << "\\end{itemize}" << endl << endl
	    << "\\begin{thebibliography}{99}" << endl
	    << "\\bibitem{ThePEG} L.~L\\\"onnblad, "
	    << "Comput.~Phys.~Commun.\\ {\\bf 118} (1999) 213." << endl;
  if ( !stratref.empty() ) reffile() << stratref << endl;
  for ( StringMap::iterator it = references.begin();
	it != references.end(); ++it )
    reffile() << it->second << endl;
  reffile() << "\\end{thebibliography}" << endl
	    << "\\end{document}" << endl;
  reffile().close();
}

void EventGenerator::strategy(StrategyPtr s) {
  theStrategy = s;
}

int EventGenerator::count(const Exception & ex) {
  return ++theExceptions[&typeid(ex)];
}

void EventGenerator::printException(const Exception & ex) {
  switch ( ex.severity() ) {
  case Exception::info:
    log() << "* An information";
        break;
  case Exception::warning:
    log() << "* A warning";
    break;
  case Exception::eventerror:
    log() << "** An event";
    break;
  case Exception::runerror:
    log() << "*** An run";
    break;
  case Exception::maybeabort:
  case Exception::abortnow:
    log() << "**** A serious";
    break;
  default:
    log() << "**** An unknown";
    break;
  }
  log() << " exception occurred while generating event number "
	    << ieve << ": " << endl << ex.message() << endl;
  if ( ex.severity() == Exception::eventerror )
    log() << "The event will be discarded." << endl;
}

void EventGenerator::logWarning(const Exception & ex) {
  if ( ex.severity() != Exception::info &&
       ex.severity() != Exception::warning ) throw ex;
  if ( count(ex) > maxWarnings ) return;
  printException(ex);
  ex.handle();  
}

bool EventGenerator::
logException(const Exception & ex, tcEventPtr event) {
  bool noEvent = !event;
  int c = count(ex);
  ex.handle();
  if ( c <= maxWarnings ) {
    printException(ex);
    if ( c == maxWarnings )
      log() << "No more warnings of this kind will be reported." << endl;
  }
  if ( ex.severity() == Exception::info ||
       ex.severity() == Exception::warning ) {
    ex.handle();
    return false;
  }
  if ( ex.severity() == Exception::eventerror ) {
    if ( c < maxErrors || maxErrors <= 0 ) {
      ex.handle();
      if ( ThePEG_DEBUG_LEVEL > 0 && !noEvent ) log() << *event;
      return false;
    }
    if ( c > maxErrors ) printException(ex);
    log() << "Too many (" << c << ") exceptions of this kind has occurred. "
      "Execution will be stopped.\n";
  } else {
    log() << "This exception is too serious. Execution will be stopped.\n";
  }
  if ( !noEvent ) log() << *event;
  else log()
    << "An exception occurred before any event object was created!\n";
  dump();
  return true;
}

struct MatcherOrdering {
  bool operator()(tcPMPtr m1, tcPMPtr m2) {
    return m1->name() < m2->name() ||
      ( m1->name() == m2->name() && m1->fullName() < m2->fullName() );
  }
};

struct ObjectOrdering {
  bool operator()(tcIBPtr i1, tcIBPtr i2) {
    return i1->fullName() < i2->fullName();
  }
};

void EventGenerator::persistentOutput(PersistentOStream & os) const {
  set<tcPMPtr,MatcherOrdering> match(theMatchers.begin(), theMatchers.end());
  set<tcIBPtr,ObjectOrdering> usedset(usedObjects.begin(), usedObjects.end());
  os << theDefaultObjects << theLocalParticles << theStandardModel
     << theStrategy << theRandom << thePath << theRunName
     << theNumberOfEvents << theObjectMap << theParticles
     << theQuickParticles << theQuickSize << match << usedset
     << ieve << theDebugLevel << maxWarnings << maxErrors
     << theCurrentCollisionHandler << theCurrentStepHandler;
}

void EventGenerator::persistentInput(PersistentIStream & is, int) {
  is >> theDefaultObjects >> theLocalParticles >> theStandardModel
     >> theStrategy >> theRandom >> thePath >> theRunName
     >> theNumberOfEvents >> theObjectMap >> theParticles
     >> theQuickParticles >> theQuickSize >> theMatchers >> usedObjects
     >> ieve >> theDebugLevel >> maxWarnings >> maxErrors
     >> theCurrentCollisionHandler >> theCurrentStepHandler;
  theObjects.clear();
  for ( ObjectMap::iterator it = theObjectMap.begin();
	it != theObjectMap.end(); ++it ) theObjects.insert(it->second);
}

void EventGenerator::setLocalParticles(PDPtr pd, int) {
  localParticles()[pd->id()] = pd;
}
  
void EventGenerator::insLocalParticles(PDPtr pd, int) {
  localParticles()[pd->id()] = pd;
}
  
void EventGenerator::delLocalParticles(int place) {
  ParticleMap::iterator it = localParticles().begin();
  while ( place-- && it != localParticles().end() ) ++it;
  if ( it != localParticles().end() ) localParticles().erase(it);
}

vector<PDPtr> EventGenerator::getLocalParticles() const {
  vector<PDPtr> ret;
  for ( ParticleMap::const_iterator it = localParticles().begin();
 	it != localParticles().end(); ++it ) ret.push_back(it->second);
  return ret;
}

void EventGenerator::setPath(string newPath) {
  if ( std::system(("mkdir -p " + newPath).c_str()) ) throw EGNoPath(newPath);
  if ( std::system(("touch " + newPath + "/.ThePEG").c_str()) )
    throw EGNoPath(newPath);
  if ( std::system(("rm -f " + newPath + "/.ThePEG").c_str()) )
    throw EGNoPath(newPath);
  thePath = newPath;
}

string EventGenerator::defPath() const {
  char * env = std::getenv("ThePEG_RUN_DIR");
  if ( env ) return string(env);
  return string(".");
}

ostream & EventGenerator::out() {
  return outfile().is_open()? outfile(): BaseRepository::cout();
}

ostream & EventGenerator::log() {
  return logfile().is_open()? logfile(): BaseRepository::clog();
}

ostream & EventGenerator::ref() {
  return reffile().is_open()? reffile(): BaseRepository::cout();
}

AbstractClassDescription<EventGenerator> EventGenerator::initEventGenerator;

void EventGenerator::Init() {
  
  static ClassDocumentation<EventGenerator> documentation
    ("There is no documentation for the ThePEG::EventGenerator class");

  static Reference<EventGenerator,StandardModelBase> interfaceStandardModel
    ("StandardModelParameters",
     "The ThePEG::StandardModelBase object to be used to access standard "
     "model parameters in this run.",
     &EventGenerator::theStandardModel, false, false, true, false);

  static RefVector<EventGenerator,ParticleData> interfaceLocalParticles
    ("LocalParticles",
     "Special versions of ThePEG::ParticleData objects to be used "
     "in this run. Note that to delete an object, its number in the list "
     "should be given, rather than its id number.",
     0, 0, false, false, true, false,
     &EventGenerator::setLocalParticles, &EventGenerator::insLocalParticles,
     &EventGenerator::delLocalParticles, &EventGenerator::getLocalParticles);

  static RefVector<EventGenerator,Interfaced> interfaceDefaultObjects
    ("DefaultObjects",
     "A vector of pointers to default objects. In a ThePEG::Reference or "
     "ThePEG::RefVector interface with the defaultIfNull() flag set, if a "
     "null pointer is encountered this vector is gone through until an "
     "acceptable object is found in which case the null pointer is replaced "
     "by a pointer to this object.",
     &EventGenerator::theDefaultObjects, 0, true, false, true, false, false);

  static Reference<EventGenerator,Strategy> interfaceStrategy
    ("Strategy",
     "An ThePEG::Strategy with additional ThePEG::ParticleData objects to "
     "be used in this run.",
     &EventGenerator::theStrategy, false, false, true, true);

  static Reference<EventGenerator,RandomGenerator> interfaceRandomGenerator
    ("RandomNumberGenerator",
     "An ThePEG::RandomGenerator object which should typically interaface to "
     "a CLHEP Random object. This will be the default random number generator "
     "for the run, but individual objects may use their own random generator "
     "if they wish.",
     &EventGenerator::theRandom, true, false, true, false);

//   static Parameter<EventGenerator,string> interfacePath
//     ("Path",
//      "The directory where the output files are put.",
//      &EventGenerator::thePath, ".", ".", ".", true, false, false,
//      &EventGenerator::setPath, 0, 0, 0, &EventGenerator::defPath);

//   static Parameter<EventGenerator,string> interfaceRunName
//     ("RunName",
//      "The name of this run. This name will be used in the output filenames.",
//      &EventGenerator::theRunName, "", "", "", true, false, false,
//      0, 0, 0, 0, &EventGenerator::name);

  static Parameter<EventGenerator,long> interfaceNumberOfEvents
    ("NumberOfEvents",
     "The number of events to be generated in this run. If less than zero, "
     "the number of events is unlimited",
     &EventGenerator::theNumberOfEvents, 1000, -1, Constants::MaxInt,
     true, false, true);

  static Parameter<EventGenerator,int> interfaceDebugLevel
    ("DebugLevel",
     "The level of debug information sent out to the log file in the run. "
     "Level 0 only gives a limited ammount of warnings and error messages. "
     "Level 1 will print the first few events. "
     "Level 5 will print every event. "
     "Level 9 will print every step in every event.",
     &EventGenerator::theDebugLevel, 0, 0, 9, true, false, true);

  static Parameter<EventGenerator,int> interfaceMaxWarnings
    ("MaxWarnings",
     "The maximum number of warnings of each type which will be printed.",
     &EventGenerator::maxWarnings, 10, 1, 100, true, false, true);

  static Parameter<EventGenerator,int> interfaceMaxErrors
    ("MaxErrors",
     "The maximum number of errors of each type which will be tolerated. "
     "If more errors are reported, the run will be aborted.",
     &EventGenerator::maxErrors, 10, 1, 100, true, false, true);

  static Parameter<EventGenerator,int> interfaceQuickSize
    ("QuickSize",
     "The max absolute id number of particle data objects which are accessed "
     "quickly through a vector indexed by the id number.",
     &EventGenerator::theQuickSize, 7000, 0, 50000, true, false, true);

}

EGNoPath::EGNoPath(string path) {
  theMessage << "Cannot set the directory path for output files to '" << path
	     << "' because the directory did not exist and could not be "
	     << "created.";
  severity(warning);
}

