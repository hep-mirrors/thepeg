// -*- C++ -*-
#ifndef ThePEG_SimpleAlphaEM_H
#define ThePEG_SimpleAlphaEM_H
//
// This is the declaration of the <!id>SimpleAlphaEM<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>SimpleAlphaEM<!!id> inherits from <!class>AlphaEMBase<!!class>
// and implements a simple running of the electromagnetic coupling as
// parameterized by H.~Buckhardt et al.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:AlphaEMBase.html">AlphaEMBase.h</a>.
// 

#include "AlphaEMBase.h"
// #include "SimpleAlphaEM.fh"
// #include "SimpleAlphaEM.xh"

namespace ThePEG {

class SimpleAlphaEM: public AlphaEMBase {

public:

  inline SimpleAlphaEM();
  inline SimpleAlphaEM(const SimpleAlphaEM &);
  virtual ~SimpleAlphaEM();
  // Standard ctors and dtor

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

public:

  virtual double value(Energy2 scale, const StandardModelBase &) const;
  // Return the value of the coupling at a given scale using the given
  // standard model object.

public:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  static NoPIOClassDescription<SimpleAlphaEM> initSimpleAlphaEM;

  SimpleAlphaEM & operator=(const SimpleAlphaEM &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<SimpleAlphaEM,1> {
  typedef AlphaEMBase NthBase;
};

template <>
struct ClassTraits<SimpleAlphaEM>: public ClassTraitsBase<SimpleAlphaEM> {
  static string className() { return "/ThePEG/SimpleAlphaEM"; }
  static string library() { return "SimpleAlphaEM.so"; }
};

}

#include "SimpleAlphaEM.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleAlphaEM.tcc"
#endif

#endif /* ThePEG_SimpleAlphaEM_H */
