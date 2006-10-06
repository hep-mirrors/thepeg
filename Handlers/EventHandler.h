// -*- C++ -*-
#ifndef ThePEG_EventHandler_H
#define ThePEG_EventHandler_H
// This is the declaration of the EventHandler class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/HandlerGroup.h"
#include "ThePEG/Handlers/StepHandler.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/Handlers/SubProcessHandler.fh"
#include "ThePEG/Cuts/Cuts.fh"
#include "EventHandler.fh"

namespace ThePEG {

/**
 * The EventHandler is the base class used to implement event handlers
 * in ThePEG. Objects of this class is assigned to an EventGenerator
 * object which supervises a run. This base class is not able to
 * generate complete events, although it does have a virtual
 * generateEvent(). If the EventGenerator to which an EventGenerator
 * is assinged is asked to generate a full event, it will call the
 * generateEvent() function which will write an error message and
 * abort the run.
 *
 * Objects of this base class can, however, be used to administer the
 * evolution of a partially generated event supplied from the
 * outside. To specify this event evolution the EventHandler maintains
 * five groups of so-called StepHandlers implemented as
 * HandlerGroups. Each group have a main step handler:
 * SubProcessHandler, CascadeHandler, MultipleInteractionHandler,
 * HadronizationHandler and DecayHandler respectively, whereof the
 * first group only uses the post-handler part of the group.
 *
 * The EventHandler class inherits from the LastXCombInfo class to
 * have easy interface to the information in the last selected XComb
 * which carries information about the hard sub-process in the event.
 *
 * If a sub-class implements the generation of sub-processes and thus
 * becomes a full event handler it should implement the
 * generateEvent() function appropriately. It should also set the flag
 * warnIncomplete to false, to avoid warnings when initialized as the main
 * EventHandler of an Eventgenerator.
 *
 * @see \ref EventHandlerInterfaces "The interfaces" defined for EventHandler.
 * @see Collision
 * @see StepHandler
 * @see HandlerGroup
 * @see SubProcessHandler
 * @see CascadeHandler
 * @see MultipleInteractionHandler
 * @see HadronizationHandler
 * @see DecayHandler
 */
class EventHandler: public HandlerBase, public LastXCombInfo<> {

public:

  /** Enumerate the different levels of consistency checking. */
  enum ConsistencyLevel {
    clNoCheck,   /**< Do not perform consistency checks. */
    clCollision, /**< Check every Collision. */
    clStep       /**< Check every Step. */
  };

  /** A vector of <code>HandlerGroup</code>s. */
  typedef vector<HandlerGroupBase *> GroupVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  EventHandler(bool warnincomplete = true);

  /**
   * Copy-constructor.
   */
  EventHandler(const EventHandler &);

  /**
   * Destructor.
   */
  virtual ~EventHandler();
  //@}

public:

  /** @name Main functions, some of which may be overridden by subclasses. */
  //@{
  /**
   * Initialize this event handler and all related objects needed to
   * generate events.
   */
  virtual void initialize();

  /**
   * Generate an event. This base class is not capable of generating
   * complete events and calling this function will result in an
   * exception. Sub-classes which are capable of generating complete
   * events from scratch must override this function.
   */
  virtual EventPtr generateEvent();

  /**
   * Generate an Event, where the initial state is supplied
   * from the outside.
   * @return a pointer to the generated Event.
   */
  tEventPtr generateEvent(tEventPtr e);

  /**
   * Generate an Event, where the initial state is supplied as a
   * single step from the outside.
   * @return a pointer to the generated Event.
   */
  tEventPtr generateEvent(tStepPtr s);

  /**
   * Continue generating an event if the generation has been stopped
   * before finishing.
   */
  virtual EventPtr continueEvent();

  /**
   * Continue the generation of a Collision. Used if the generation
   * was previously interrupted.
   */
  tCollPtr continueCollision();

  /**
   * Clear all step handlers, making the handler ready for a new event.
   */
  void clearEvent();

  /**
   * Returns true if there are no step handlers left to apply to the
   * current event;
   */
  virtual bool empty() const;

  /**
   * Write out accumulated statistics about intergrated cross sections
   * and stuff.
   */
  virtual void statistics(ostream &) const;

  /**
   * Histogram scale. A histogram bin which has been filled with the
   * weights associated with the Event objects should be scaled by
   * this factor to give the correct cross section. This version of
   * the function will produce an error message. It is up to a
   * sub-class able to generate full events to return the correct
   * value.
   */
  virtual CrossSection histogramScale() const;
  //@}

  /** @name Simple access functions. */
  //@{
  /**
   * Return the maximum number attemts allowed to select a sub-process
   * for each event.
   */
  inline long maxLoop() const;

  /**
   * The pair of incoming particle types. These are null if not set by
   * a subclass.
   */
  inline const cPDPair & incoming() const;

  /**
   * Access the luminosity function.
   */
  inline const LuminosityFunction & lumiFn() const;

  /**
   * Access the luminosity function.
   */
  inline tcLumiFnPtr lumiFnPtr() const;

  /**
   * Access to the luminosity function.
   */
  inline tLumiFnPtr lumiFnPtr();

  /**
   * The kinematical cuts to used by subclasses which do not provide their own.
   */
  inline tCutsPtr cuts() const;

  /**
   * A PartonExtractor object to be used by sub classes which do not
   * provide their own.
   */
  inline tPExtrPtr partonExtractor() const;

  /**
   * Return a pointer (possibly null) to the assigned main
   * CascadeHandler to be used as CKKW-reweighter.
   */
  tCascHdlPtr CKKWHandler() const;

  /**
   * Gget current event.
   */
  inline tEventPtr currentEvent() const;

  /**
   * Get current collision.
   */
  inline tCollPtr currentCollision() const;

  /**
   * Get current step.
   */
  inline tStepPtr currentStep() const;

  /**
   * The level of statistics. Controlls the amount of statistics
   * written out after each run to the <code>EventGenerator</code>s
   * <code>.out</code> file.
   */
  inline int statLevel() const;

  /**
   * Determines how often the event handler should check for charge
   * and energy-momentum conservation.
   */
  inline ConsistencyLevel consistencyLevel() const;

  /**
   * The maximum fraction of the total invariant mass of a collision
   * that any of the components of the summed momentum is allowed to
   * change during the generation.
   */
  inline double consistencyEpsilon() const;
  //@}

  /** @name Internal functions used by main functions and possibly
      from the outside. */
  //@{
  /**
   * Perform a given step using a handler and a hint.
   */
  void performStep(tStepHdlPtr handler, tHintPtr hint);

  /**
   * In the curresnt list of step handlers to go through, add another
   * step handler and/or hint.
   */
  void addStep(Group::Level, Group::Handler,
	       tStepHdlPtr = tStepHdlPtr(), tHintPtr = tHintPtr());

  /**
   * Create a new step and make it current. Optionally supply a
   * StepHandler which will be set as the handler for the created
   * Step.
   */
  inline tStepPtr newStep(tcStepHdlPtr sh = tcStepHdlPtr());

  /**
   * Remove the last step.
   */
  inline void popStep();

  /**
   * Initialize the groups of step handlers.
   */
  virtual void initGroups();

  /**
   * Set current event.
   */
  inline void currentEvent(tEventPtr e);

  /**
   * Set current collision.
   */
  inline void currentCollision(tCollPtr c);

  /**
   * Set current step.
   */
  inline void currentStep(tStepPtr s);

  /**
   * Get current StepHandler.
   */
  inline tStepHdlPtr currentStepHandler() const;
  /**
   * Set current StepHandler.
   */
  inline void currentStepHandler(tStepHdlPtr sh);

  /**
   * Throw away the current event/collision.
   */
  void throwCurrent();

  /**
   * Throw away the last generated event before generating a new one.
   */
  virtual void clean();

  /**
   * Check that the charge and energy-momentum in the last step of the
   * current collision is consistent with the incoming particles. If
   * not, a warning will be generated.
   */
  virtual void checkConsistency() const;

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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

protected:

  /**
   * Access to the luminosity function.
   */
  inline LuminosityFunction & lumiFn();

  /**
   * Setup the step handler groups.
   */
  void setupGroups();

  /**
   * Access the step handler groups
   */
  inline GroupVector & groups();

  /**
   * Access the step handler groups
   */
  inline const GroupVector & groups() const;

protected:

  /**
   * Set the luminosity function
   */
  void lumiFn(LumiFnPtr);

private:

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
   * Determines how often the event handler should check for charge
   * and energy-momentum conservation.
   */
  ConsistencyLevel theConsistencyLevel;

  /**
   * The maximum fraction of the total invariant mass of a collision
   * that any of the components of the summed momentum is allowed to
   * change during the generation.
   */
  double theConsistencyEpsilon;

  /**
   * Pointer to a luminosity function tobe used by subclasses.
   */
  LumiFnPtr theLumiFn;

  /**
   * The kinematical cuts to used by subclasses which do not provide
   * their own.
   */
  CutsPtr theCuts;

  /**
   * A PartonExtractor object to be used by sub classes which do not
   * provide their own.
   */
  PExtrPtr thePartonExtractor;

  /**
   * The SubProcessHandler group.
   */
  HandlerGroup<SubProcessHandler> theSubprocessGroup;

  /**
   * The CascadeHandler group.
   */
  HandlerGroup<CascadeHandler> theCascadeGroup;

  /**
   * The MultipleInteractionHandler group.
   */
  HandlerGroup<MultipleInteractionHandler> theMultiGroup;

  /**
   * The HadronizationHandler group.
   */
  HandlerGroup<HadronizationHandler> theHadronizationGroup;

  /**
   * The DecayHandler group.
   */
  HandlerGroup<DecayHandler> theDecayGroup;

  /**
   * The step handler groups.
   */
  GroupVector theGroups;

  /**
   * The current Event.
   */
  EventPtr theCurrentEvent;

  /**
   * The current Collision.
   */
  CollPtr theCurrentCollision;

  /**
   * The current Step.
   */
  StepPtr theCurrentStep;

  /**
   * The current StepHandler.
   */
  StepHdlPtr theCurrentStepHandler;

protected:

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  HandlerGroup<SubProcessHandler> optSubprocessGroup;

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  HandlerGroup<CascadeHandler> optCascadeGroup;

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  HandlerGroup<MultipleInteractionHandler> optMultiGroup;

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  HandlerGroup<HadronizationHandler> optHadronizationGroup;

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  HandlerGroup<DecayHandler> optDecayGroup;

protected:

  /**
   * Utility object to facilitate default selection of step handlers.
   */
  GroupVector optGroups;

protected:

  /**
   * Emit warning that this EventHandler is incomplete.
   */
  bool warnIncomplete;

  /**
   * The pair of incoming particle types. Should be set by a subclass
   * which implements a complete EventHandler.
   */
  cPDPair theIncoming;

protected:

  /** @cond EXCEPTIONCLASSES */
  /**
   * Exception class used by EventHandler when a StepHandler of the
   * wrong class was added.
   */
  class EventHandlerStepError: public Exception {};

  /**
   * Exception class used by EventHandler when not able to produce a
   * correct histogram scale.
   */
  class EventHandlerHistError: public Exception {};

  /**
   * Exception class used by EventHandler if asked to generate a
   * complete event.
   */
  class EventHandlerIncompleteError: public Exception {};

  /** Exception class used if too many attempts to generate an event
   *  failed. */
  struct EventLoopException: public Exception {
    /** Standard constructor. */
    EventLoopException(const EventHandler &);
  };

  /**
   * Exception class used if the assignment of a LuminosityFunction
   * failed
   */
  struct LumiFuncError: public Exception {};

  /**
   * Exception class used if inconsistent charge or energy-momentum was found.
   */
  struct ConsistencyException: public Exception {};

  /** @endcond */

private:

  ThePEG_DECLARE_PREPOST_GROUP(SubProcessHandler,Post);
  ThePEG_DECLARE_GROUPINTERFACE(CascadeHandler,CascHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(MultipleInteractionHandler,MIHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(HadronizationHandler,HadrHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(DecayHandler,DecayHdlPtr);

  ThePEG_DECLARE_CLASS_DESCRIPTION(EventHandler);

  /**
   *  Private and non-existent assignment operator.
   */
  EventHandler & operator=(const EventHandler &);

};

/** @cond TRAITSPECIALIZATIONS */
ThePEG_DECLARE_CLASS_TRAITS(EventHandler,HandlerBase);
/** @endcond */

}

#include "EventHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventHandler.tcc"
#endif

#endif /* ThePEG_EventHandler_H */
