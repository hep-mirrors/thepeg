// -*- C++ -*-
#ifndef ThePEG_FullEventGenerator_H
#define ThePEG_FullEventGenerator_H
// This is the declaration of the FullEventGenerator class.

#include "ThePEG/Repository/EventGenerator.h"
// #include "FullEventGenerator.fh"
// #include "FullEventGenerator.xh"

namespace ThePEG {

/**
 * <code>FullEventGenerator</code> inherits from the EventGenerator
 * class and has a pointer to an EventHandler which is able to
 * generate complete events. It also has a list of AnalysisHandlers to
 * perform analysis on the generated Events, and an EventManipulator
 * to externally manipulate the generated events.
 *
 * @see EventGenerator,
 * @see EventHandler,
 * @see AnalysisHandler,
 * @see Event,
 * @see EventManipulator.
 */
class FullEventGenerator: public EventGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  FullEventGenerator();

  /**
   * Copy-constructor.
   */
  FullEventGenerator(const FullEventGenerator &);

  /**
   * Destructor.
   */
  virtual ~FullEventGenerator();
  //@}

public:

  /** @name Access special object in this run. */
  //@{
  /**
   * Return a pointer to the EventHandler.
   */
  inline tEHPtr eventHandler() const;

  /**
   * Return the vector of analysis objects to be used in the run.
   */
  inline AnalysisVector & analysisHandlers();

  /**
   * Return the EventManipulator used in the run.
   */
  inline tEvtManipPtr manipulator() const;
  //@}

  /** @name Public virtual functions required by the base class. */
  //@{
  /**
   * Return the maximum center of mass energy possible for an
   * event. Return zero if this is only a partial generator.
   */
  virtual Energy maximumCMEnergy() const;

  /**
   * Return the event being generated.
   */
  virtual tcEventPtr currentEvent() const;
  //@}

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

  /** @name Main protected virtual functions required by the base class. */
  //@{
  /**
   * Generate one event. 
   */
  virtual EventPtr doShoot();

  /**
   * Finish generating an event constructed from the outside. 
   */
  virtual EventPtr doPartialEvent(tEventPtr);
  //@}


protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}


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

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Pointer to the event handler used to generate the indivudual
   * events.
   */
  EHPtr theEventHandler;

  /**
   * A vector of all analysis handlers to be called after each event.
   */
  AnalysisVector theAnalysisHandlers;

  /**
   * A pointer to an optional event manipulator object.
   */
  EvtManipPtr theEventManipulator;

  /**
   * If the debug level is higher than 0, print the first 'printEvent'
   * events to the logfile.
   */
  int printEvent;

  /**
   * If the dubug level is higher than 0, dump the complete state of
   * this run to the default dump file every 'dumpPeriod' events.
   */
  long dumpPeriod;

  /**
   * If the dubug level is higher than 0, step up to the highest debug
   * level just before the event with number debugEvent is performed.
   */
  long debugEvent;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<FullEventGenerator> initFullEventGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  FullEventGenerator & operator=(const FullEventGenerator &);

};

/** This template specialization informs ThePEG about the base classes
 *  of FullEventGenerator. */
template <>
struct BaseClassTrait<FullEventGenerator,1> {
  /** Typedef of the first base class of FullEventGenerator. */
  typedef EventGenerator NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  FullEventGenerator class. */
template <>
struct ClassTraits<FullEventGenerator>:
    public ClassTraitsBase<FullEventGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::FullEventGenerator"; }
};

}

#include "FullEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FullEventGenerator.tcc"
#endif

#endif /* ThePEG_FullEventGenerator_H */
