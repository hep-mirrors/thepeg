// -*- C++ -*-
#ifndef ThePEG_HadronizationHandler_H
#define ThePEG_HadronizationHandler_H
//
// This is the declaration of the <!id>HadronizationHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>HadronizationHandler<!!id> is the base class of all
// handlers implementing models for hadronization of coloured
// particles. It is derived from the more general
// <!class>StepHandler<!!class> class, and does not introduce more
// functioanality as it stands.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// 

#include "StepHandler.h"
// #include "HadronizationHandler.fh"
// #include "HadronizationHandler.xh"

namespace ThePEG {

class HadronizationHandler: public StepHandler {

public:

  inline HadronizationHandler();
  inline HadronizationHandler(const HadronizationHandler &);
  virtual ~HadronizationHandler();
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

  static AbstractNoPIOClassDescription<HadronizationHandler>
    initHadronizationHandler;

  HadronizationHandler & operator=(const HadronizationHandler &);
  //  Private and non-existent assignment operator.

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
