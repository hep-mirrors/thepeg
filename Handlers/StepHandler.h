// -*- C++ -*-
#ifndef ThePEG_StepHandler_H
#define ThePEG_StepHandler_H
//
// This is the declaration of the <!id>StepHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>StepHandler<!!id> is the base class for implementing any model
// for a step in the event generation chain. It has one main virtual
// method, <!id>handle<!!id>, which should be overridden by sub
// classes. The handle method is given a reference to a
// <!class>PartialCollisionHandler<!!class>, a vector of particles and
// a <!class>Hint<!!class> as arguments. The handler is only allowed
// to treat particles which are in the vector. The
// <!class>Hint<!!class> may be cast dynamically to a sub class and do
// whatever it wishes with the information found there. The
// <!class>PartialCollisionHandler<!!class> can be used to add other
// <!id>StepHandler<!!id>s and <!class>Hint<!!class>s to modify
// the subsequent generation. If the <!id>StepHandler<!!id> actually
// performs some action, the resulting particles should be added to a
// new <!class>Step<!!class> which should be aquired with the
// <!id>PartialCollisionHandler::newStep()<!!id> method.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>
// <a href="http:Hint.html">Hint.h</a>
// <a href="http:Step.html">Step.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Exception.fh"
#include "ThePEG/Handlers/HandlerBase.h"
#include <stdexcept>

namespace ThePEG {

class StepHandler: public HandlerBase {

public:

  inline StepHandler();
  inline StepHandler(const StepHandler &);
  virtual ~StepHandler();
  // Standard ctors and dtor

public:

  virtual void handle(PartialCollisionHandler & ch, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception)) = 0;
  // The main virtual method to be overridden by subclasse.

  inline tPartCollHdlPtr collisionHandler() const;
  void collisionHandler(tPartCollHdlPtr);
  // Get/set a pointer to the (partial) collision handler which made
  // the last call to handle().

  inline tStepPtr newStep();
  // Return a pointer to a new step. If one has alredy been created in
  // the last call to handle(), that step will be returned.

  inline tStepPtr currentStep();
  // If a new step has been created, return it, otherwise return the
  // current step from the collisionHandler().

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  void createNewStep();
  // Use the collision handler to create a new step.

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  tPartCollHdlPtr theCollisionHandler;
  // A pointer to the (partial) collision handler which made the current
  // call to handle().

  tStepPtr theNewStep;
  // A pointer to a new step if created in the last call to handle().

  tStepPtr theCurrentStep;
  // A pointer to the current step. is equal to theNewStep if one was
  // created in the current call to handle().

private:

  static AbstractNoPIOClassDescription<StepHandler> initStepHandler;

  StepHandler & operator=(const StepHandler &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<StepHandler,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<StepHandler>: public ClassTraitsBase<StepHandler> {
  static string className() { return "/ThePEG/StepHandler"; }
};

}

#include "StepHandler.icc"

#endif /* ThePEG_StepHandler_H */
