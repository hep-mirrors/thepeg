// -*- C++ -*-
#ifndef ThePEG_CKMBase_H
#define ThePEG_CKMBase_H
//
// This is the declaration of the <!id>CKMBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>CKMBase<!!id> is used by the
// <!class>StandardModelBase<!!class> to implement the
// Cabibbo-Kobayashi-Mascawa mixing matrix.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StandardModelBase.html">StandardModelBase.h</a>.
// 

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"
// #include "CKMBase.fh"
// #include "CKMBase.xh"

namespace ThePEG {

class CKMBase: public Interfaced {

public:

  inline CKMBase();
  inline CKMBase(const CKMBase &);
  virtual ~CKMBase();
  // Standard ctors and dtor

public:

  virtual vector< vector<double> >  getMatrix(unsigned int nFamilies) const = 0;
  // Return the matrix of squared matrix elements.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  static AbstractNoPIOClassDescription<CKMBase> initCKMBase;

  CKMBase & operator=(const CKMBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<CKMBase,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<CKMBase>: public ClassTraitsBase<CKMBase> {
  static string className() { return "/ThePEG/CKMBase"; }
};

}

#include "CKMBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CKMBase.tcc"
#endif

#endif /* ThePEG_CKMBase_H */
