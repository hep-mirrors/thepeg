// -*- C++ -*-
#ifndef ThePEG_AlphaEMBase_H
#define ThePEG_AlphaEMBase_H
//
// This is the declaration of the <!id>AlphaEMBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>AlphaEMBase<!!id> is used by the
// <!class>StandardModelBase<!!class> to implement the
// electro-magnetic coupling.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StandardModelBase.html">StandardModelBase.h</a>.
// 

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"
// #include "AlphaEMBase.fh"
// #include "AlphaEMBase.xh"

namespace ThePEG {

class AlphaEMBase: public Interfaced {

public:

  inline AlphaEMBase();
  inline AlphaEMBase(const AlphaEMBase &);
  virtual ~AlphaEMBase();
  // Standard ctors and dtor

public:

  virtual double value(Energy2 scale, const StandardModelBase &) const = 0;
  // Return the value of the coupling at a given scale using the given
  // standard model object.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  static AbstractNoPIOClassDescription<AlphaEMBase> initAlphaEMBase;

  AlphaEMBase & operator=(const AlphaEMBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<AlphaEMBase,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<AlphaEMBase>: public ClassTraitsBase<AlphaEMBase> {
  static string className() { return "/ThePEG/AlphaEMBase"; }
};

}

#include "AlphaEMBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AlphaEMBase.tcc"
#endif

#endif /* ThePEG_AlphaEMBase_H */
