// -*- C++ -*-
#ifndef ThePEG_PartialCollisionHandler_H
#define ThePEG_PartialCollisionHandler_H
// This is the declaration of the PartialCollisionHandler class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/HandlerGroup.h"
#include "ThePEG/Handlers/StepHandler.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
// #include "PartialCollisionHandler.fh"
#include "PartialCollisionHandler.xh"

namespace ThePEG {

/**
 * The PartialCollisionHandler is used to administer all steps needed
 * to generate a Collision after the hard subprocess has been
 * performed by the CollisionHandler derived from
 * PartialCollisionHandler. The PartialCollisionHandler can also be
 * used from a PartialEventHandler to perform specified steps on a
 * user-defined initial condition.
 *
 * The PartialCollisionHandler maintains five groups of of
 * StepHandlers implemented as HandlerGroups. Each group have a main
 * step handler: SubProcessHandler, CascadeHandler,
 * MultipleInteractionHandler, HadronizationHandler and DecayHandler
 * respectively, whereof the first group only uses the post-handler
 * part of the group.
 *
 * The PartialCollisionHandler class also inherits from the
 * LastXCombInfo class to have easy interface to the information in
 * the last selected XComb in case the PartialCollisionHandler is used
 * a a sub-class of the CollisionHandler class.
 *
 * @see \ref PartialCollisionHandlerInterfaces "The interfaces"
 * defined for PartialCollisionHandler.
 * @see Collision
 * @see CollisionHandler
 * @see PartialEventHandler
 * @see StepHandler
 * @see HandlerGroup
 * @see SubProcessHandler
 * @see CascadeHandler
 * @see MultipleInteractionHandler
 * @see HadronizationHandler
 * @see DecayHandler
 */
class PartialCollisionHandler: public HandlerBase, public LastXCombInfo<> {

public:

  /** A vector of <code>HandlerGroup</code>s. */
  typedef vector<HandlerGroupBase *> GroupVector;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PartialCollisionHandler();

  /**
   * Copy-constructor.
   */
  PartialCollisionHandler(const PartialCollisionHandler &);

  /**
   * Destructor.
   */
  virtual ~PartialCollisionHandler();
  //@}

public:

  /**
   * Continue generating a collision, where the initial state of the
   * Event is supplied from the outside.
   * @return a pointer to the generated Event.
   */
  tEventPtr partialCollision(tEventPtr e);

  /**
   * Continue generating a collision, where the first Step of
   * an event is supplied from the outside.
   * @return a pointer to the generated Event.
   */
  tEventPtr partialCollision(tStepPtr s);

  /**
   * Continue generating a collision which was interrupted, or was
   * supplied from outside.
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
   * Gget current event.
   */
  inline tEventPtr currentEvent() const;

  /**
   * Set current event.
   */
  inline void currentEvent(tEventPtr e);

  /**
   * Get current collision.
   */
  inline tCollPtr currentCollision() const;

  /**
   * Set current collision.
   */
  inline void currentCollision(tCollPtr c);

  /**
   * Get current step.
   */
  inline tStepPtr currentStep() const;

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
   * Initialize this object after the setup phase before saving and
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

private:

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

private:

  ThePEG_DECLARE_PREPOST_GROUP(SubProcessHandler,Post);
  ThePEG_DECLARE_GROUPINTERFACE(CascadeHandler,CascHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(MultipleInteractionHandler,MIHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(HadronizationHandler,HadrHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(DecayHandler,DecayHdlPtr);

  ThePEG_DECLARE_CLASS_DESCRIPTION(PartialCollisionHandler);

  /**
   *  Private and non-existent assignment operator.
   */
  PartialCollisionHandler & operator=(const PartialCollisionHandler &);

};

ThePEG_DECLARE_CLASS_TRAITS(PartialCollisionHandler,HandlerBase);

}

#include "PartialCollisionHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialCollisionHandler.tcc"
#endif

#endif /* ThePEG_PartialCollisionHandler_H */
