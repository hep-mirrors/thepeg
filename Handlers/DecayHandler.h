// -*- C++ -*-
#ifndef ThePEG_DecayHandler_H
#define ThePEG_DecayHandler_H
//
// This is the declaration of the <!id>DecayHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>DecayHandler<!!id> is the base class of all handlers
// implementing the administration of decays of unstable particles. It
// is derived from the more general <!class>StepHandler<!!class>
// class, and overrides the <!id>handle<!!id> method, simply decays
// all unstable particle in the current step.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// 

#include "StepHandler.h"
// #include "DecayHandler.fh"
#include "DecayHandler.xh"

namespace ThePEG {

class DecayHandler: public StepHandler {

public:

  inline DecayHandler();
  inline DecayHandler(const DecayHandler &);
  virtual ~DecayHandler();
  // Standard ctors and dtor

public:

  virtual void handle(PartialCollisionHandler & ch, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception));
  // Look through all tagged particled and decay all unstable ones.

  void performDecay(tPPtr parent, Step & s) const
    ThePEG_THROW_SPEC((Veto, Exception));
  // Perform the decay of one unstable particle.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

  inline long maxLoop() const;
  // The maximum number of failed decay attempts allowed for each
  // particle.

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

private:

  long theMaxLoop;
  // The maximum number of failed decay attempts allowed for each
  // particle.

private:

  static ClassDescription<DecayHandler> initDecayHandler;

  DecayHandler & operator=(const DecayHandler &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<DecayHandler,1> {
  typedef StepHandler NthBase;
};

template <>
struct ClassTraits<DecayHandler>: public ClassTraitsBase<DecayHandler> {
  static string className() { return "/ThePEG/DecayHandler"; }
};

}

#include "DecayHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DecayHandler.tcc"
#endif

#endif /* ThePEG_DecayHandler_H */
