// -*- C++ -*-
#ifndef ThePEG_MultipleInteractionHandler_H
#define ThePEG_MultipleInteractionHandler_H
//
// This is the declaration of the <!id>MultipleInteractionHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MultipleInteractionHandler<!!id> is the base class of all
// handlers implementing models for multiple interactions. It is
// derived from the more general <!class>StepHandler<!!class> class,
// and does not introduce more functioanality as it stands.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// 


#include "StepHandler.h"
// #include "MultipleInteractionHandler.fh"
// #include "MultipleInteractionHandler.xh"

namespace ThePEG {

class MultipleInteractionHandler: public StepHandler {

public:

  inline MultipleInteractionHandler();
  inline MultipleInteractionHandler(const MultipleInteractionHandler &);
  virtual ~MultipleInteractionHandler();
  // Standard ctors and dtor

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

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

  static AbstractNoPIOClassDescription<MultipleInteractionHandler>
    initMultipleInteractionHandler;

  MultipleInteractionHandler & operator=(const MultipleInteractionHandler &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<MultipleInteractionHandler,1> {
  typedef StepHandler NthBase;
};

template <>
struct ClassTraits<MultipleInteractionHandler>:
    public ClassTraitsBase<MultipleInteractionHandler> {
  static string className() { return "/ThePEG/MultipleInteractionHandler"; }
};

}

#include "MultipleInteractionHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultipleInteractionHandler.tcc"
#endif

#endif /* ThePEG_MultipleInteractionHandler_H */
