// -*- C++ -*-
#ifndef ThePEG_EventHandler_H
#define ThePEG_EventHandler_H
// This is the declaration of the EventHandler class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Handlers/CollisionHandler.h"
#include "ThePEG/Handlers/EventHandler.xh"
#include "ThePEG/Repository/Strategy.fh"
#include "ThePEG/Handlers/SamplerBase.fh"
#include <fstream>

namespace ThePEG {

/**
 * The EventHandler class is the main class for generating simple
 * events without overlayed collisions. It is derived from the
 * CollisionHandler class and introduces a LuminosityFunction to
 * describe the momentum distribution of incoming particles.
 *
 * Besides the standard doinit() method, the EventHandler needs to be
 * separately initialized with the initialize() method. In the
 * dofinish() method statistics is written out to the EventGenerators
 * default output file.
 *
 * @see CollisionHandler
 * @see LuminosityFunction
 * @see EventGenerator
 * @see Event
 * 
 */
class EventHandler: public CollisionHandler {

public:

  /**
   * Copy-constructor.
   */
  EventHandler(const EventHandler &);

  /**
   * Default constructor.
   */
  EventHandler();

  /**
   * Destructor.
   */
  ~EventHandler();

public:

  /**
   * Initialize this event handler and all related objects needed to
   * generate events.
   */
  virtual void initialize();

  /**
   * Write out accumulated statistics about intergrated cross sections
   * and stuff.
   */
  virtual void statistics(ostream &) const;

  /** @name Functions used for the actual generation */
  //@{
  /**
   * Return the cross section for the chosen phase space point.
   * @param r a vector of random numbers to be used in the generation
   * of a phase space point.
   */
  virtual CrossSection dSigDR(const vector<double> & r);

  /**
   * Generate an event.
   */
  virtual EventPtr generateEvent();

  /**
   * Continue generating an event if the generation has been stopped
   * before finishing.
   */
  virtual EventPtr continueEvent();
  //@}

  /** @name Simple access functions */
  //@{
  /**
   * Return the maximum number attemts allowed to select a sub-process
   * for each event.
   */
  inline long maxLoop() const;

  /**
   * The level of statistics. Controlls the amount of statistics
   * written out after each run to the <code>EventGenerator</code>s
   * <code>.out</code> file.
   */
  inline int statLevel() const;

  /**
   * Return true if this event handler should produce weightes events
   */
  inline bool weighted() const;

  /**
   * Returns true if we are currently in a compensating mode after
   * encountering a weight larger than 1.
   */
  inline bool compensating() const;

  /**
   * Access the luminosity function.
   */
  inline const LuminosityFunction & lumiFn() const;

  /**
   * The number of phase space dimensions used by the luminosity
   * function.
   */
  inline int lumiDim() const;

  /**
   * The number of dimensions of the basic phase space to generate
   * sub-processes in for a given bin of XComb objects.
   */
  inline int nDim(int bin) const;
  //@}

public:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Writes out statistics on the generation.
   */
  virtual void dofinish();
  //@}

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

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

  /**
   * Access to the luminosity function.
   */
  inline LuminosityFunction & lumiFn();

  /**
   * Reject a (partially) generated event.
   * @param weight the weight given for the event.
   */
  void reject(double weight);

  /**
   * Return the sampler assigned to this event handler.
   */
  inline tSamplerPtr sampler();

  /**
   * Return the sampler assigned to this event handler.
   */
  inline tcSamplerPtr sampler() const;

private:

  /**
   * Set the luminosity function
   */
  void lumiFn(LumiFnPtr);

private:

  /**
   * Pointer to the luminosity function.
   */
  LumiFnPtr theLumiFn;

  /**
   * True if this event handler should produce weightes events
   */
  bool weightedEvents;

  /**
   * The maximum number of attempts to select a sub-process allowed
   * per event.
   */
  long theMaxLoop;

  /**
   * Controlls the amount of statistics written out after each run to
   * the EventGenerators .out file.
   */
  int theStatLevel;

  /**
   * The phase space sampler responsible for generating phase space
   * points according to the cross section given by this event
   * handler.
   */
  SamplerPtr theSampler;

  /**
   * The number of phase space dimensions used by the luminosity
   * function.
   */
  int theLumiDim;

  /**
   * The number of dimensions of the basic phase space to generate
   * sub-processes in.
   */
  int theNDim;

  /**
   * Standard Initialization object.
   */
  static ClassDescription<EventHandler> initEventHandler;

private:

  /**
   * Private and non-existent assignment operator.
   */
  const EventHandler & operator=(const EventHandler &);

};

/**
 * The following template specialization informs ThePEG about the
 * base class of EventHandler.
 */
template <>
struct BaseClassTrait<EventHandler,1> {
  /** Typedef of the base class of EventHandler. */
  typedef CollisionHandler NthBase;
};

/**
 * The following template specialization informs ThePEG about the name
 * of theEventHandler class and the shared object where it is defined.
 */
template <>
struct ClassTraits<EventHandler>: public ClassTraitsBase<EventHandler> {
  /**
   * Return the class name.
   */
  static string className() { return "/ThePEG/EventHandler"; }
};

}

#include "EventHandler.icc"

#endif /* ThePEG_EventHandler_H */
