// -*- C++ -*-
#ifndef ThePEG_CascadeHandler_H
#define ThePEG_CascadeHandler_H
//
// This is the declaration of the <!id>CascadeHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>CascadeHandler<!!id> is the base class of all handlers
// implementing perturbative partonic cascade models. It is derived
// from the more general <!class>StepHandler<!!class> class, and does
// not introduce more functioanality as it stands.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// 

#include "StepHandler.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/PDF/PDF.h"
// #include "CascadeHandler.fh"
// #include "CascadeHandler.xh"

namespace ThePEG {


class CascadeHandler: public StepHandler, public LastXCombInfo<> {

public:

  inline CascadeHandler();
  inline CascadeHandler(const CascadeHandler &);
  virtual ~CascadeHandler();
  // Standard ctors and dtor

public:

  virtual void handle(PartialCollisionHandler & ch, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception));
  // The default version stores important information and calls cascade().

  virtual void cascade() = 0;
  // The main function to be overwritten by sub-classes.

public:

  inline const tPVector & tagged() const;
  // Return the vector of tagged particles which should be
  // showered. It the vector is empty, the patons from the current
  // sub-process is supposed to be showered.

  inline const Hint & hint() const;
  // Return the int provided in the current call to handle().

  inline const PDF & firstPDF() const;
  inline const PDF & secondPDF() const;
  inline const pair<PDF,PDF> & pdfs() const;
  // Return references to the currently used PDF's.

  inline tPartCollHdlPtr collisionHandler() const;
  // Return a pointer to the current collision handler.

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

  const tPVector * theTagged;
  const Hint * theHint;
  // Store the arguments given to handle().

  pair<PDF,PDF> thePDFs;
  // The pdfs used to extract the incoming partons.

  tPartCollHdlPtr theCollisionHandler;
  // The current collision handler.

private:

  static AbstractNoPIOClassDescription<CascadeHandler> initCascadeHandler;

  CascadeHandler & operator=(const CascadeHandler &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<CascadeHandler,1> {
  typedef StepHandler NthBase;
};

template <>
struct ClassTraits<CascadeHandler>: public ClassTraitsBase<CascadeHandler> {
  static string className() { return "/ThePEG/CascadeHandler"; }
};

}

#include "CascadeHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CascadeHandler.tcc"
#endif

#endif /* ThePEG_CascadeHandler_H */
