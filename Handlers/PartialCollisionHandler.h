// -*- C++ -*-
#ifndef ThePEG_PartialCollisionHandler_H
#define ThePEG_PartialCollisionHandler_H
//
// This is the declaration of the <!id>PartialCollisionHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>PartialCollisionHandler<!!id> is used to administer all
// steps needed to generate a <!class>Collision<!!class> after the
// hard subprocess has been performed by the
// <!class>CollisionHandler<!!class> derived from
// <!id>PartialCollisionHandler<!!id>. The
// <!id>PartialCollisionHandler<!!id> can also be used from a
// <!class>PartialEventHandler<!!class> to perform specified steps on
// a user-defined initial condition.
//
// The <!id>PartialCollisionHandler<!!id> maintains five groups of of
// <!class>StepHandler<!!class>s implemented as
// <!class>HandlerGroup<!!class>s. Each group have a main step
// handler: <!class>SubProcessHandler<!!class>,
// <!class>CascadeHandler<!!class>,
// <!class>MultipleInteractionHandler<!!class>,
// <!class>HadronizationHandler<!!class> and
// <!class>DecayHandler<!!class> respectively, whereof the first group
// only uses the post-handler part of the group.  as
//
// The <!id>PartialCollisionHandler<!!id> class also inherits from the
// <!id>LastXCombInfo<!!id> class to have easy interface to the
// information in the last selected <!class>XComb<!!class> in case the
// <!id>PartialCollisionHandler<!!id> is used a a sub-class of the
// <!class>CollisionHandler<!!class> class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:PartialEventHandler.html">PartialEventHandler.h</a>
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:HandlerGroup.html">HandlerGroup.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// <a href="http:CascadeHandler.html">CascadeHandler.h</a>
// <a href="http:MultipleInteractionHandler.html">MultipleInteractionHandler.h</a>
// <a href="http:HadronizationHandler.html">HadronizationHandler.h</a>
// <a href="http:DecayHandler.html">DecayHandler.h</a>
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/HandlerGroup.h"
#include "ThePEG/Handlers/StepHandler.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
// #include "PartialCollisionHandler.fh"
#include "PartialCollisionHandler.xh"

namespace ThePEG {

class PartialCollisionHandler: public HandlerBase, public LastXCombInfo<> {

public:

  typedef vector<HandlerGroupBase *> GroupVector;

public:

  PartialCollisionHandler();
  PartialCollisionHandler(const PartialCollisionHandler &);
  virtual ~PartialCollisionHandler();
  // Standard ctors and dtor

public:

  tEventPtr partialCollision(tEventPtr e);
  tEventPtr partialCollision(tStepPtr s);
  // Continue generating a collision, where the event or first step of
  // an event is supplied from the outside.

  tCollPtr continueCollision();
  // Continue generating a collision which was interrupted, or was
  // supplied from outside.

  void clearEvent();
  // Clear all step handlers, making the handler ready for a new event.

  virtual bool empty() const;
  // Returns true if there are no step handlers left to apply to the
  // current event;

  void performStep(tStepHdlPtr handler, tHintPtr hint);
  // Perform a given step using a handler and a hint.

  void addStep(Group::Level, Group::Handler,
	       tStepHdlPtr, tHintPtr);
  // In the curresnt list of step handlers to go through, add another
  // step handler and/or hint.

  inline tStepPtr newStep();
  // Create a new step and make it current.

  inline void popStep();
  // Remove the last step.

  virtual void initGroups();
  // initialize groups of step handlers.

  inline tEventPtr currentEvent() const;
  inline void currentEvent(tEventPtr e);
  // Set/get current event.

  inline tCollPtr currentCollision() const;
  inline void currentCollision(tCollPtr c);
  // Set/get current collision.

  inline tStepPtr currentStep() const;
  inline void currentStep(tStepPtr s);
  // Set/get current step.

  inline tStepHdlPtr currentStepHandler() const;
  inline void currentStepHandler(tStepHdlPtr sh);
  // Set/get current step handler.

  void throwCurrent();
  // Throw away the current event/collision.

  virtual void clean();
  // Throw away the last generated event before generating a new one.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

protected:

  void setupGroups();
  // Setup the step handler groups.

  inline GroupVector & groups();
  inline const GroupVector & groups() const;
  // Access to the step handler groups

private:

  HandlerGroup<SubProcessHandler> theSubprocessGroup;
  HandlerGroup<CascadeHandler> theCascadeGroup;
  HandlerGroup<MultipleInteractionHandler> theMultiGroup;
  HandlerGroup<HadronizationHandler> theHadronizationGroup;
  HandlerGroup<DecayHandler> theDecayGroup;
  GroupVector theGroups;
  // The step handler groups.

  EventPtr theCurrentEvent;
  CollPtr theCurrentCollision;
  StepPtr theCurrentStep;
  StepHdlPtr theCurrentStepHandler;
  // Info about the current event.

protected:

  HandlerGroup<SubProcessHandler> optSubprocessGroup;
  HandlerGroup<CascadeHandler> optCascadeGroup;
  HandlerGroup<MultipleInteractionHandler> optMultiGroup;
  HandlerGroup<HadronizationHandler> optHadronizationGroup;
  HandlerGroup<DecayHandler> optDecayGroup;
  // Utility objects to facilitate default selection of step handlers.

protected:

  GroupVector optGroups;

private:

  ThePEG_DECLARE_PREPOST_GROUP(SubProcessHandler,Post);
  ThePEG_DECLARE_GROUPINTERFACE(CascadeHandler,CascHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(MultipleInteractionHandler,MIHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(HadronizationHandler,HadrHdlPtr);
  ThePEG_DECLARE_GROUPINTERFACE(DecayHandler,DecayHdlPtr);
  // Utility decalarations for interfaces

  //  static ClassDescription<PartialCollisionHandler> initPartialCollisionHandler;
  ThePEG_DECLARE_CLASS_DESCRIPTION(PartialCollisionHandler);

  PartialCollisionHandler & operator=(const PartialCollisionHandler &);
  //  Private and non-existent assignment operator.

};

ThePEG_DECLARE_CLASS_TRAITS(PartialCollisionHandler,HandlerBase);

//  template <>
//  struct BaseClassTrait<PartialCollisionHandler,1> {
//    typedef HandlerBase NthBase;
//  };

//  template <>
//  struct ClassTraits<PartialCollisionHandler>:
//      public ClassTraitsBase<PartialCollisionHandler> {
//    static string className() { return "/ThePEG/PartialCollisionHandler"; }
//  };

}

#include "PartialCollisionHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialCollisionHandler.tcc"
#endif

#endif /* ThePEG_PartialCollisionHandler_H */
