// -*- C++ -*-
#ifndef ThePEG_EventGenerator_H
#define ThePEG_EventGenerator_H
//
// This is the declaration of the <!id>EventGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>EventGenerator<!!id> class manages a whole event generator
// run. It keeps a list of all <!class>Interfaced<!!class> objects
// which are needed for a particular run (these objects each have a
// pointer back to the <!id>EventGenerator<!!id>). Some objects are
// special, such as a default <!class>RandomGenerator<!!class> object,
// a <!class>StandardModelBase<!!class> object and a
// <!class>Strategy<!!class> object and a list of
// <!class>ParticleData<!!class> objects used in the run.
//
// The <!id>EventGenerator<!!id> also manages information about the
// run such as the exceptions being thrown, files to write output and
// error messages to, etc.
//
// There are three main external member functions:<BR><!id>go()<!!id>
// generates the specified numbewr of events and
// exits.<BR><!id>shoot()<!!id> generates one <!class>Event<!!class>
// and returns it.<BR><!id>partialEvent()<!!id> takes an initial
// <!class>Step<!!class> as argument and generates subsequent steps
// defined in the generator.<BR><!id>shoot()<!!id> is a pure virtual
// and needs to be implemented the <!class>FullEventGenerator<!!class>
// sub-class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Interfaced.html">Interfaced.h</a>,
// <a href="http:RandomGenerator.html">RandomGenerator.h</a>,
// <a href="http:StandardModelBase.html">StandardModelBase.h</a>,
// <a href="http:Strategy.html">Strategy.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:Event.html">Event.h</a>,
// <a href="http:Step.html">Step.h</a>,
// <a href="http:FullEventGenerator.html">FullEventGenerator.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Named.h"
#include "EventGenerator.fh"
#include "RandomGenerator.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/CurrentGenerator.fh"
#include "ThePEG/Utilities/ClassDescription.h"
#include <fstream>
#include "EventGenerator.xh"

namespace ThePEG {

class EventGenerator: public Interfaced {

  friend class Repository;

public:

  typedef map<const type_info *, int> ExceptionMap;

public:

  EventGenerator();
  EventGenerator(const EventGenerator &);
  virtual ~EventGenerator();
  // Standard constructord and destructors

public:

  inline tSMPtr standardModel() const;
  // Return a pointer to the standard model parameters.

  inline tStrategyPtr strategy() const;
  // Return a pointer to the strategy object containing a set of
  // non-default particles to use.

  inline tPartCollHdlPtr currentCollisionHandler() const;
  inline void currentCollisionHandler(tPartCollHdlPtr);
  // Get/set the currently active (partial) collision handler.

  inline tStepHdlPtr currentStepHandler() const;
  inline void currentStepHandler(tStepHdlPtr);
  // Get/set the currently active step handler.

public:
  // The following functions are only relevant during the actual event
  // generation

  void initialize();
  // Initialize this generator. This is done automatically if 'go()'
  // is used. Calls the virtual method doInitialize().

  void go(long next = 1, long maxevent = -1);
  // Run this EventGenerator session. Calls the virtual method doGo().

  EventPtr shoot();
  // Generate one event. Calls the virtual method doShoot();

  EventPtr partialEvent(tEventPtr);
  // Finish generating an event constructed from the outside.  Calls
  // the virtual method do doPartialEvent().

  void finalize();
  // Indicate that the run has ended and call finish() for all objects
  // including this one. Note that finish() should not be called
  // directly.

  virtual Energy maximumCMEnergy() const;
  // Return the maximum center of mass energy possible for an
  // event. Return zero if this is only a partial generator.

  inline long N() const;
  inline long currentEventNumber() const;
  // The number of events to be generated in this run.

  virtual tcEventPtr currentEvent() const = 0;
  // Return the event being generated.

  virtual void dump() const;
  // Dump the full state of the current run - including the number of
  // generated events, so that it can be fully continued from this point.

  inline string filename() const;
  // The base filename used in this run. The actual files are called
  // 'filename.run', 'filename.dump', 'filename.out', 'filename.log'
  // and filename.tex' for the input configuration file, output
  // configuration file, output file, log file, and reference file
  // respectively. The filename is constructed from the path() and
  // runName().

  inline string runName() const;
  // Return the name assigned to this run. If no name is given, the
  // name of the EventGenerator object is returned.

  inline string path() const;
  // The directory in which the 'filename()' is located

  void openOutputFiles();
  void closeOutputFiles();
  // open/close ouput files.

  inline ofstream & outfile();
  inline ofstream & logfile();
  inline ofstream & reffile();
  // Return references to the streams connected to the files for
  // general output, logging information and references from used
  // objects.

  ostream & out();
  ostream & log();
  ostream & ref();
  // Return references to the streams connected to the files for
  // general output, logging information and references from used
  // objects. If no file is connected, the BaseRepository::cout(),
  // BaseRepository::clog() and BaseRepository::cout() will be used
  // instead.

  void use(const Interfaced & i);
  // Register a given object as used.

  const ObjectSet & objects() const;
  const ObjectMap & objectMap() const;
  // Return the set/map of objects used in this run.

  template <typename T>
  typename Ptr<T>::pointer getPtr(const T &) const;
  // Return a garbage collected pointer to a given object. If the
  // object is not found, a null pointer will be returned.

  IBPtr getPointer(string name) const;
  // Return a pointer to an object present in this run given its full
  // name. Return the null pointer if non-existent.

  template <typename T>
  inline typename Ptr<T>::pointer getObject(string name) const;
  // Return a pointer to an object of type T present in this run given
  // its full name. Return the null pointer if non-existent.

  template <typename T>
  typename Ptr<T>::pointer getDefault() const;
  // Return the default object for class T. Returns the null pointer
  // if non-existent.

  PPtr getParticle(long) const;
  // Create a particle instance corresponding to the given id number.

  PDPtr getParticleData(long) const;
  // Return a pointer to the ParticleData object corresponding to the
  // given id number.

  inline const MatcherSet & matchers() const;
  // Return a reference to the complete list of matchers in this
  // generator.

  inline const ParticleMap & particles() const;
  // Return a reference to the complete map of particle data objects
  // in this generator, indexed by their id numbers.

  inline const ObjectSet & used() const;
  // Return a reference to the set of objects which have been
  // registered as used during the current run.

  inline RandomGenerator & random() const;
  // Return a reference to the default RandomGenerator object in this
  // run.

  inline RandomEngine & randomEngine() const;
  // Return a reference to the RandomEngine object used in the default
  // RandomGenerator object in this run.

  inline double rnd();
  // Return a simple flat random number in the range ]0,1[.

  void logWarning(const Exception &);
  // Log a given exception.

protected:

  void setup(string newRunName, ObjectSet & newObjects,
	     ParticleMap & newParticles, MatcherSet & newMatchers);
  // Finish the setup of an event generator run. Set run name, all
  // particles, matchers and other objects to be used.

  virtual void doGo(long next, long maxevent);
  // Run this EventGenerator session.

  virtual void doInitialize();
  // Initialize this generator. This is done automatically if 'go()'
  // is used.

  virtual EventPtr doShoot() = 0;
  // Generate one event. 

  virtual EventPtr doPartialEvent(tEventPtr) = 0;
  // Finish generating an event constructed from the outside. 

  void printException(const Exception &);
  // Print the message of an exception to the log file.

  bool logException(const Exception &, tcEventPtr);
  // Log a given exception.

  inline void N(long);
  // Set number of events to be generated.

  inline void runName(string);
  // Set the name of this run

private:
  // The following methods are only used in the setup phase.

  inline const vector<IPtr> & defaultObjects() const;
  // Return the vector of default objects.

  inline ParticleMap & localParticles();
  inline const ParticleMap & localParticles() const;
  // Functions to manipulate the special particles used in this
  // generator.

  inline void path(string);
  // Set the directory where the output files will be stored.

  void strategy(StrategyPtr);
  // Set a pointer to the strategy object containing a set of
  // non-default particles to use.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:
  // The following methods are only relevant during the actual event
  // generation.

  inline virtual void doupdate() throw(UpdateException);
  // Check sanity during setup phase.

  void doinit() throw (InitException);
  // Initialize the run.

  void doinitrun();
  // Initialize the run.

  void dofinish();
  // Finish off this run. Write run statistics on the output file,
  // references to the reference file and call the 'finish' function
  // for all used objects.

  inline ObjectSet & objects();
  inline ObjectMap & objectMap();
  // Return the set/map of all objects to be used in this run.

  void generateReferences();
  // Print out the .tex file with descriptions and references to all
  // models used in the run.

  int count(const Exception &);
  // Increase and return the count for the given exception.

private:
  // Member variables:

  vector<IPtr> theDefaultObjects;
  // A vector of default objects.

  ParticleMap theLocalParticles;
  // Map of non-default particles used in this EventGenerator.

  SMPtr theStandardModel;
  // Pointer to an object containing standard model parameters.

  StrategyPtr theStrategy;
  // Pointer to a strategy object with other non-default particles to
  // be used in this EventGenerator.

  RanGenPtr theRandom;
  // Pointer to the default RandomGenerator to be used in this run.

  string thePath;
  string theRunName;
  // The file name is constructed from the path and the run name.

  ofstream theOutfile;
  ofstream theLogfile;
  ofstream theReffile;
  // The output streams are connected with files corresponding to the
  // base file name with suffixes '.out', '.log' and '.tex'

  long theNumberOfEvents;
  // Number of events to be generated in this run.

  ObjectSet theObjects;
  // The set of all objects to be used in this run.

  ObjectMap theObjectMap;
  // All objects to be used in this run mapped to their name.

  ParticleMap theParticles;
  // The map of all particles to be used in this run, indexed by the
  // id number.
  PDVector theQuickParticles;
  int theQuickSize;
  // A vector of particles indexed by the id number for quick access.
  // Only particles with id number less than theQuickSize are available.

  MatcherSet theMatchers;
  // The set of all matchers to be used in this run.

  ObjectSet usedObjects;
  // The set of objects which have actually been used in this run.

protected:

  long ieve;
  // The current event number;

  int theDebugLevel;
  // The debug level.

private:

  int maxWarnings;
  int maxErrors;
  // The maximum number of warnings and errors reported of each
  // type.

  ExceptionMap theExceptions;
  // A map of all Exceptions which have been caught by the event
  // generator and the number of time each exception type has been
  // caught.

private:

  void setLocalParticles(PDPtr pd, int);
  void insLocalParticles(PDPtr pd, int);
  void delLocalParticles(int place);
  vector<PDPtr> getLocalParticles() const;
  void setPath(string newPath);
  string defPath() const;
  // Utility functions for the interfaces.

  UseRandom * theCurrentRandom;
  // The UseRandom object constructed for the duration of an
  // EventGenerator run so that the default random number generator
  // always can be accessed through the static methods of the
  // UseRandom class.

  CurrentGenerator * theCurrentGenerator;
  // The CurrentGenerator object constructed for the duration of an
  // EventGenerator run so that the default event generator always can
  // be accessed through the static methods of the CurrentGenerator
  // class.

  tPartCollHdlPtr theCurrentCollisionHandler;
  // The currently active (partial) collision handler.

  tStepHdlPtr theCurrentStepHandler;
  // The currently active step handler.

private:

  static AbstractClassDescription<EventGenerator> initEventGenerator;

  EventGenerator & operator=(const EventGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<EventGenerator,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<EventGenerator>:
    public ClassTraitsBase<EventGenerator> {
  static string className() {
    return "/ThePEG/EventGenerator";
  }
};

}

#include "EventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "EventGenerator.tcc"
#endif

#endif /* ThePEG_EventGenerator_H */
