// -*- C++ -*-
#ifndef ThePEG_StepHandler_H
#define ThePEG_StepHandler_H
// This is the declaration of the StepHandler class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Exception.fh"
#include "ThePEG/Handlers/HandlerBase.h"
#include <stdexcept>

namespace ThePEG {

/**
 * StepHandler is the base class for implementing any model for a step
 * in the event generation chain. It has one main virtual method,
 * handle(), which should be overridden by sub classes. The handle
 * method is given a reference to a EventHandler, a vector
 * of particles and a Hint as arguments. The handler is only allowed
 * to treat particles which are in the vector. The Hint may be cast
 * dynamically to a sub class and do whatever it wishes with the
 * information found there. The EventHandler can be used to
 * add other <code>StepHandler</code>s and Hints to modify the
 * subsequent generation. If the StepHandler actually performs some
 * action, the resulting particles should be added to a new Step which
 * should be aquired with the newStep() function.
 *
 * @see \ref StepHandlerInterfaces "The interfaces"
 * defined for StepHandler.
 * @see EventHandler
 * @see Hint
 * @see Step
 * 
 */
class StepHandler: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline StepHandler();

  /**
   * The copy constructor.
   */
  inline StepHandler(const StepHandler &);

  /**
   * The destructor.
   */
  virtual ~StepHandler();
  //@}

public:

  /** @name Virtual functions to be implemented by concrete sub-classes. */
  //@{
  /**
    * The main function called by the EventHandler class to
    * perform a step.
    * @param eh the EventHandler in charge of the Event generation.
    * @param tagged if not empty these are the only particles which should
    * be considered by the StepHandler.
    * @param hint a Hint object with possible information from previously
    * performed steps.
    * @throws Veto if the StepHandler requires the current step to be
    * discarded.
    * @throws Stop if the generation of the current Event should be stopped
    * after this call.
    * @throws Exception if something goes wrong.
    */
  virtual void handle(EventHandler & eh, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception)) = 0;

  //@}

  /** @name Access to the calling EventHandler and current Step. */
  //@{
  /**
   * Get a pointer to the EventHandler which made the last call to
   * handle().
   */
  inline tEHPtr eventHandler() const;

  /**
   * Set a pointer to the EventHandler which made the last call to
   * handle().
   */
  void eventHandler(tEHPtr);

  /**
   * Return a pointer to a new step. If one has alredy been created in
   * the last call to handle(), that step will be returned.
   */
  inline tStepPtr newStep();

  /**
   * If a new step has been created, return it, otherwise return the
   * current step from the eventHandler().
   */
  inline tStepPtr currentStep();
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /**
   * Use the collision handler to create a new step.
   */
  void createNewStep();

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

private:

  /**
   * A pointer to the (partial) collision handler which made the current
   * call to handle().
   */
  tEHPtr theEventHandler;

  /**
   * A pointer to a new step if created in the last call to handle().
   */
  tStepPtr theNewStep;

  /**
   * A pointer to the current step. Is equal to theNewStep if one was
   * created in the current call to handle().
   */
  tStepPtr theCurrentStep;

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<StepHandler> initStepHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  StepHandler & operator=(const StepHandler &);

};

/**
 * This template specialization informs ThePEG about the base class of
 * StepHandler.
 */
template <>
struct BaseClassTrait<StepHandler,1>: public ClassTraitsType {
  /** Typedef of the base class of StepHandler. */
  typedef HandlerBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * StepHandler class.
 */
template <>
struct ClassTraits<StepHandler>: public ClassTraitsBase<StepHandler> {
  /** Return the class name.  */
  static string className() { return "ThePEG::StepHandler"; }
};

}

#include "StepHandler.icc"

#endif /* ThePEG_StepHandler_H */
