// -*- C++ -*-
#ifndef ThePEG_HadronizationHandler_H
#define ThePEG_HadronizationHandler_H
// This is the declaration of the HadronizationHandler class.

#include "StepHandler.h"

namespace ThePEG {

/**
 * The HadronizationHandler is the base class of all handlers
 * implementing models for hadronization of coloured particles. It is
 * derived from the more general StepHandler class, but does not
 * introduce more functioanality as it stands.
 *
 * @see StepHandler
 * @see CollisionHandler
 * @see SubProcessHandler
 * 
 */
class HadronizationHandler: public StepHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline HadronizationHandler();

  /**
   * Copy-constructor.
   */
  inline HadronizationHandler(const HadronizationHandler &);

  /**
   * Destructor.
   */
  virtual ~HadronizationHandler();
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
   * Return a vector of all pointers to Interfaced objects used in this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<HadronizationHandler>
    initHadronizationHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  HadronizationHandler & operator=(const HadronizationHandler &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of HadronizationHandler.
 */
template <>
struct BaseClassTrait<HadronizationHandler,1> {
  /** Typedef of the base class of HadronizationHandler. */
  typedef StepHandler NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * HadronizationHandler class.
 */
template <>
struct ClassTraits<HadronizationHandler>:
    public ClassTraitsBase<HadronizationHandler> {
  /** Return the class name. */
  static string className() { return "ThePEG::HadronizationHandler"; }
};

}

#include "HadronizationHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HadronizationHandler.tcc"
#endif

#endif /* ThePEG_HadronizationHandler_H */
