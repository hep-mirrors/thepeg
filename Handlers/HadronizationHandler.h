// -*- C++ -*-
#ifndef ThePEG_HadronizationHandler_H
#define ThePEG_HadronizationHandler_H
// This is the declaration of the HadronizationHandler class.

#include "StepHandler.h"

namespace ThePEG {

/**
 * The <code>HadronizationHandler</code> is the base class of all
 * handlers implementing models for hadronization of coloured
 * particles. It is derived from the more general
 * StepHandler class, and does not introduce more
 * functioanality as it stands.
 *
 *
 * @see StepHandler
 * @see CollisionHandler
 * @see SubProcessHandler
 * 
 */
class HadronizationHandler: public StepHandler {

public:

  /**
   * Standard ctors and dtor
   */
  inline HadronizationHandler();
  /**
   * Standard ctors and dtor
   */
  inline HadronizationHandler(const HadronizationHandler &);
  /**
   * Standard ctors and dtor
   */
  virtual ~HadronizationHandler();

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /**
   * Standard Interfaced virtual functions.
   */
  inline virtual void doupdate() throw(UpdateException);
  /**
   * Standard Interfaced virtual functions.
   */
  inline virtual void doinit() throw(InitException);
  /**
   * Standard Interfaced virtual functions.
   */
  inline virtual void dofinish();

  /**
   * Change all pointers to Interfaced objects to corresponding clones.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return pointers to all Interfaced objects refered to by this.
   */
  inline virtual IVector getReferences();

private:

  static AbstractNoPIOClassDescription<HadronizationHandler>
    initHadronizationHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  HadronizationHandler & operator=(const HadronizationHandler &);

};

template <>
struct BaseClassTrait<HadronizationHandler,1> {
  typedef StepHandler NthBase;
};

template <>
struct ClassTraits<HadronizationHandler>:
    public ClassTraitsBase<HadronizationHandler> {
  static string className() { return "/ThePEG/HadronizationHandler"; }
};

}

#include "HadronizationHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HadronizationHandler.tcc"
#endif

#endif /* ThePEG_HadronizationHandler_H */
