// -*- C++ -*-
#ifndef ThePEG_EventGenerator_H
#define ThePEG_EventGenerator_H
// This is the declaration of the EventGenerator class.

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

/**
 * The EventGenerator class manages a whole event generator run. It
 * keeps a list of all Interfaced objects which are needed for a
 * particular run (these objects each have a pointer back to the
 * EventGenerator). Some objects are special, such as a default
 * RandomGenerator object, a StandardModelBase object and a Strategy
 * object and lists of ParticleData and MatcherBase objects used in
 * the run.
 *
 * The <code>EventGenerator</code> also manages information about the
 * run such as the exceptions being thrown, files to write output and
 * error messages to, etc.
 *
 * There are three main external member functions:<BR>
 * go() generates a specified number of events and * exits.<BR>
 *
 * shoot() generates one Event and returns it.<BR>
 *
 * partialEvent() takes an initial Step as argument and generates
 * subsequent steps defined in the generator.<BR>
 *
 * doShoot() is a pure virtual function called by shoot() and needs to
 * be implemented the sub-classes.<BR>
 *
 * doPartialEvent() is a pure virtual function called by
 * partialEvent() and needs to be implemented the sub-classes.
 *
 * @see Interfaced,
 * @see RandomGenerator,
 * @see StandardModelBase,
 * @see Strategy,
 * @see ParticleData,
 * @see Event,
 * @see Step,
 * @see FullEventGenerator.
 * 
 */
class EventGenerator: public Interfaced {

  /** The Repository is a friend. */
  friend class Repository;

public:

  /** A map of integers giving the number of times an exception of the
   *  key type has been thrown. */
  typedef map<const type_info *, int> ExceptionMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  EventGenerator();

  /**
   * Copy-constructor.
   */
  EventGenerator(const EventGenerator &);

  /**
   * Destructor.
   */
  virtual ~EventGenerator();
  //@}

public:

  /** @name Access special objects in the run. */
  //@{
  /**
   * Return a pointer to the standard model parameters.
   */
  inline tSMPtr standardModel() const;

  /**
   * Return a pointer to the strategy object containing a set of
   * non-default particles to use.
   */
  inline tStrategyPtr strategy() const;

  /**
   * Get the currently active (partial) collision handler.
   */
  inline tPartCollHdlPtr currentCollisionHandler() const;

  /**
   * Set the currently active (partial) collision handler.
   */
  inline void currentCollisionHandler(tPartCollHdlPtr);

  /**
   * Get the currently active step handler.
   */
  inline tStepHdlPtr currentStepHandler() const;

  /**
   * Set the currently active step handler.
   */
  inline void currentStepHandler(tStepHdlPtr);

  /**
   * Return a reference to the default RandomGenerator object in this
   * run.
   */
  inline RandomGenerator & random() const;

  /**
   * Return a reference to the RandomEngine object used in the default
   * RandomGenerator object in this run.
   */
  inline RandomEngine & randomEngine() const;
  //@}

public:

  /** @name Main functions to controll the run. */
  //@{
  /**
   * Initialize this generator. This is done automatically if 'go()'
   * is used. Calls the virtual method doInitialize().
   */
  void initialize();

  /**
   * Run this EventGenerator session. Calls the virtual method doGo().
   *
   * @param next the number of the firts event to be
   * generated. Default is 1.
   * @param maxevent the maximum number of events to be generated. If negative
   * the N() is used instead. Default is -1.
   */
  void go(long next = 1, long maxevent = -1);

  /**
   * Generate one event. Calls the virtual method doShoot();
   */
  EventPtr shoot();

  /**
   * Finish generating an \a event which has already been partially
   * constructed from the outside.  Calls the virtual method do
   * doPartialEvent().
   */
  EventPtr partialEvent(tEventPtr event);

  /**
   * Indicate that the run has ended and call finish() for all objects
   * including this one. Note that finish() should not be called
   * directly.
   */
  void finalize();

  /**
   * Return the maximum center of mass energy possible for an
   * event. Return zero if this is only a partial generator.
   */
  virtual Energy maximumCMEnergy() const;

  /**
   * The number of the event currently being generated.
   */
  inline long currentEventNumber() const;

  /**
   * Return the event being generated.
   */
  virtual tcEventPtr currentEvent() const = 0;

  /**
   * Dump the full state of the current run - including the number of
   * generated events, so that it can be fully continued from this point.
   */
  virtual void dump() const;

  /**
   * Register a given object as used. Only objects registered in this
   * way will be included in the file with model references.
   */
  void use(const Interfaced & i);

  /**
   * Return a simple flat random number in the range ]0,1[.
   */
  inline double rnd();

  /**
   * Log a given exception.
   */
  void logWarning(const Exception &);

  /**
   * The number of events to be generated in this run.
   */
  inline long N() const;
  //@}

  /** @name Functions for accessing output files. */
  //@{
  /**
   * The base filename used in this run. The actual files are called
   * <code>filename.run</code>, <code>filename.dump</code>,
   * <code>filename.out</code>, <code>filename.log</code> and
   * <code>filename.tex</code> for the input configuration file,
   * output dump file, output file, log file, and reference
   * file respectively. The filename is constructed from the path()
   * and runName().
   */
  inline string filename() const;

  /**
   * Return the name assigned to this run. If no name is given, the
   * name of the EventGenerator object is returned.
   */
  inline string runName() const;

  /**
   * The directory in which the filename() is located
   */
  inline string path() const;

  /**
   * Open all ouput files.
   */
  void openOutputFiles();

  /**
   * Close all ouput files.
   */
  void closeOutputFiles();

  /**
   * Return a reference to the output file stream.
   */
  inline ofstream & outfile();

  /**
   * Return a reference to the log file stream.
   */
  inline ofstream & logfile();

  /**
   * Return a reference to the reference file stream. This file is
   * used to output LaTeX text with information about the models used
   * in the run.
   */
  inline ofstream & reffile();

  /**
   * Return a reference to the stream connected to the file for
   * general output. If no file is connected, the
   * BaseRepository::cout() will be used instead.
   */
  ostream & out();

  /**
   * Return a reference to the stream connected to the file for logging
   * information. If no file is connected, BaseRepository::clog() will
   * be used instead.
   */
  ostream & log();

  /**
   * Return a reference to the stream connected to the filea for
   * references from used objects. If no file is connected,
   * BaseRepository::cout() will be used instead.
   */
  ostream & ref();
  //@}

  /** @name Access objects included in this run. */
  //@{
  /**
   * Return the set of objects used in this run.
   */
  const ObjectSet & objects() const;

  /**
   * Return the map of objects used in this run indexed by their name.
   */
  const ObjectMap & objectMap() const;

  /**
   * Return a garbage collected pointer to a given object. If the
   * object is not included in the run, a null pointer will be
   * returned.
   */
  template <typename T>
  typename Ptr<T>::pointer getPtr(const T &) const;

  /**
   * Return a pointer to an object present in this run given its full
   * name. Return the null pointer if non-existent.
   */
  IBPtr getPointer(string name) const;

  /**
   * Return a pointer to an object of type T present in this run given
   * its full name. Return the null pointer if non-existent. Calls
   * getPointer(string) and dynamically casts the result to the
   * requested pointer type.
   */
  template <typename T>
  inline typename Ptr<T>::pointer getObject(string name) const;

  /**
   * Return the default object for class T. Returns the null pointer
   * if non-existent.
   */
  template <typename T>
  typename Ptr<T>::pointer getDefault() const;

  /**
   * Create a particle instance corresponding to the given \a id
   * number.
   */
  PPtr getParticle(long id) const;

  /**
   * Return a pointer to the ParticleData object corresponding to the
   * given \a id number.
   */
  PDPtr getParticleData(long id) const;

  /**
   * Return a reference to the complete list of matchers in this
   * generator.
   */
  inline const MatcherSet & matchers() const;

  /**
   * Return a reference to the complete map of particle data objects
   * in this generator, indexed by their id numbers.
   */
  inline const ParticleMap & particles() const;

  /**
   * Return a reference to the set of objects which have been
   * registered as used during the current run.
   */
  inline const ObjectSet & used() const;
  //@}

protected:

  /**
   * Finish the setup of an event generator run. Set run name, all
   * particles, matchers and other objects to be used. Is used by the
   * Repository when isolating an EventGenerator.
   */
  void setup(string newRunName, ObjectSet & newObjects,
	     ParticleMap & newParticles, MatcherSet & newMatchers);

  /** @name Main virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Run this EventGenerator session. Is called from go(long,long).
   */
  virtual void doGo(long next, long maxevent);

  /**
   * Initialize this generator. Is called from initialize().
   */
  virtual void doInitialize();

  /**
   * Generate one event. Is called from shoot().
   */
  virtual EventPtr doShoot() = 0;

  /**
   * Finish generating an event constructed from the outside. Is
   * called by partialEvent(tEventPtr).
   */
  virtual EventPtr doPartialEvent(tEventPtr) = 0;
  //@}

  /**
   * Print the message of an exception to the log file.
   */
  void printException(const Exception &);

  /**
   * Log a given exception.
   */
  bool logException(const Exception &, tcEventPtr);

  /**
   * Set number of events to be generated.
   */
  inline void N(long);

  /**
   * Set the name of this run
   */
  inline void runName(string);

private:

  /**
   * Return the vector of default objects.
   */
  inline const vector<IPtr> & defaultObjects() const;

  /**
   * Access the special particles used in this generator. Not relevant
   * in the run phase.
   */
  inline ParticleMap & localParticles();

  /**
   * Access the special particles used in this generator. Not relevant
   * in the run phase.
   */
  inline const ParticleMap & localParticles() const;

  /**
   * Set the directory where the output files will be stored.
   */
  inline void path(string);

  /**
   * Set a pointer to the strategy object containing a set of
   * non-default particles to use.
   */
  void strategy(StrategyPtr);

public:


  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:



protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  virtual void dofinish();
  //@}

  /**
   * Return the set of all objects to be used in this run.
   */
  inline ObjectSet & objects();

  /**
   * Return the map of all objects to be used in this run indexed by
   * their name.
   */
  inline ObjectMap & objectMap();

  /**
   * Print out the .tex file with descriptions of and references to
   * all models used in the run.
   */
  void generateReferences();

  /**
   * Increase and return the count for the given exception.
   */
  int count(const Exception &);

private:


  /**
   * A vector of default objects.
   */
  vector<IPtr> theDefaultObjects;

  /**
   * Map of non-default particles used in this EventGenerator.
   */
  ParticleMap theLocalParticles;

  /**
   * Pointer to an object containing standard model parameters.
   */
  SMPtr theStandardModel;

  /**
   * Pointer to a strategy object with other non-default particles to
   * be used in this EventGenerator.
   */
  StrategyPtr theStrategy;

  /**
   * Pointer to the default RandomGenerator to be used in this run.
   */
  RanGenPtr theRandom;

  /**
   * The directory where the input and output files resides.
   */
  string thePath;

  /**
   * THe name of this run.
   */
  string theRunName;

  /**
   * A reference to the output file stream.
   */
  ofstream theOutfile;

  /**
   * A reference to the log file stream.
   */
  ofstream theLogfile;

  /**
   * A reference to the reference file stream.
   */
  ofstream theReffile;

  /**
   * Number of events to be generated in this run.
   */
  long theNumberOfEvents;

  /**
   * The set of all objects to be used in this run.
   */
  ObjectSet theObjects;

  /**
   * All objects to be used in this run mapped to their name.
   */
  ObjectMap theObjectMap;

  /**
   * The map of all particles to be used in this run, indexed by the
   * id number.
   */
  ParticleMap theParticles;
  /**
   * A vector of particles indexed by the id number for quick access.
   * Only particles with id number less than theQuickSize are
   * available.
   */
  PDVector theQuickParticles;

  /**
   * Only particles with id number less than theQuickSize are
   * available in theQuickParticles.
   */
  int theQuickSize;

  /**
   * The set of all matchers to be used in this run.
   */
  MatcherSet theMatchers;

  /**
   * The set of objects which have actually been used in this run.
   */
  ObjectSet usedObjects;

protected:

  /**
   * The current event number;
   */
  long ieve;

  /**
   * The debug level.
   */
  int theDebugLevel;

private:

  /**
   * The maximum number of warnings reported of each type. If more
   * than maxWarnings warnings of one type is issued, the generation
   * will continue without reporting this warning.
   */
  int maxWarnings;

  /**
   * The maximum number of warnings and errors reported of each
   * type. If more than maxErrors errors is reported for one type the
   * run will be aborted.
   */
  int maxErrors;

  /**
   * A map of all Exceptions which have been caught by the event
   * generator and the number of time each exception type has been
   * caught.
   */
  ExceptionMap theExceptions;

private:

  /**
   * Utility function for the interface.
   */
  void setLocalParticles(PDPtr pd, int);

  /**
   * Utility function for the interface.
   */
  void insLocalParticles(PDPtr pd, int);

  /**
   * Utility function for the interface.
   */
  void delLocalParticles(int place);

  /**
   * Utility function for the interface.
   */
  vector<PDPtr> getLocalParticles() const;

  /**
   * Utility function for the interface.
   */
  void setPath(string newPath);

  /**
   * Utility function for the interface.
   */
  string defPath() const;

  /**
   * The UseRandom object constructed for the duration of an
   * EventGenerator run so that the default random number generator
   * always can be accessed through the static methods of the
   * UseRandom class.
   */
  UseRandom * theCurrentRandom;

  /**
   * The CurrentGenerator object constructed for the duration of an
   * EventGenerator run so that the default event generator always can
   * be accessed through the static methods of the CurrentGenerator
   * class.
   */
  CurrentGenerator * theCurrentGenerator;

  /**
   * The currently active (partial) collision handler.
   */
  tPartCollHdlPtr theCurrentCollisionHandler;

  /**
   * The currently active step handler.
   */
  tStepHdlPtr theCurrentStepHandler;

private:

  /**
   * Describe an abstract class with persistent data.
   */
  static AbstractClassDescription<EventGenerator> initEventGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  EventGenerator & operator=(const EventGenerator &);

};

/** This template specialization informs ThePEG about the base classes
 *  of EventGenerator. */
template <>
struct BaseClassTrait<EventGenerator,1>: public ClassTraitsType {
  /** Typedef of the first base class of EventGenerator. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  EventGenerator class. */
template <>
struct ClassTraits<EventGenerator>: public ClassTraitsBase<EventGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::EventGenerator"; }
};

}

#include "EventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "EventGenerator.tcc"
#endif

#endif /* ThePEG_EventGenerator_H */
