// -*- C++ -*-
#ifndef ThePEG_MultipleInteractionHandler_H
#define ThePEG_MultipleInteractionHandler_H
// This is the declaration of the MultipleInteractionHandler class.

#include "StepHandler.h"

namespace ThePEG {

/**
 * The MultipleInteractionHandler is the base class of all
 * handlers implementing models for multiple interactions. It is
 * derived from the more general StepHandler class,
 * and does not introduce more functioanality as it stands.
 *
 * @see StepHandler
 * @see CollisionHandler
 * @see SubProcessHandler
 */
class MultipleInteractionHandler: public StepHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MultipleInteractionHandler();

  /**
   * Copy-constructor.
   */
  inline MultipleInteractionHandler(const MultipleInteractionHandler &);

  /**
   * Destructor.
   */
  virtual ~MultipleInteractionHandler();
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<MultipleInteractionHandler>
    initMultipleInteractionHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  MultipleInteractionHandler & operator=(const MultipleInteractionHandler &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of MultipleInteractionHandler.
 */
template <>
struct BaseClassTrait<MultipleInteractionHandler,1> {
  /** Typedef of the base class of MultipleInteractionHandler. */
  typedef StepHandler NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * MultipleInteractionHandler class.
 */
template <>
struct ClassTraits<MultipleInteractionHandler>:
    public ClassTraitsBase<MultipleInteractionHandler> {
  /** Return the class name. */
  static string className() { return "/ThePEG/MultipleInteractionHandler"; }
};

}

#include "MultipleInteractionHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultipleInteractionHandler.tcc"
#endif

#endif /* ThePEG_MultipleInteractionHandler_H */
