// -*- C++ -*-
#ifndef ThePEG_MEqq2qq_H
#define ThePEG_MEqq2qq_H
//
// This is the declaration of the <!id>MEqq2qq<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEqq2qq<!!id> inherits from the <!class>ME2to2QCD<!!class>
// and implements the standard <i>qqbar->qqbar</i> matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2QCD.html">ME2to2QCD.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEqq2qq.fh"
// #include "MEqq2qq.xh"

namespace ThePEG {

class MEqq2qq: public ME2to2QCD {

public:

  inline MEqq2qq();
  inline MEqq2qq(const MEqq2qq &);
  virtual ~MEqq2qq();
  // Standard ctors and dtor.

public:

  virtual double me2() const;
  // Return the matrix element for the kinematical configuation
  // previously provided by the last call to setKinematics().

  virtual void getDiagrams() const;
  // Add all possible diagrams with the add() function.

  virtual Selector<const ColourLines *>
  colourGeometries(tcDiagPtr diag) const;
  // Return a Selector with possible colour geometries for the selected
  // diagram weighted by their relative probabilities.

  virtual Selector<DiagramIndex> diagrams(const DiagramVector &) const;
  // Weight the given diagrams with their relative probabilities.

protected:

  inline double colA() const;
  inline double colB() const;
  // Return the matrix element squared (without common pre-factors)
  // for different colour configurations.

public:

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

private:

  static NoPIOClassDescription<MEqq2qq> initMEqq2qq;
  // Describe a concrete class with persistent data.

  MEqq2qq & operator=(const MEqq2qq &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEqq2qq.
template <>
struct BaseClassTrait<MEqq2qq,1> {
  typedef ME2to2QCD NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEqq2qq>: public ClassTraitsBase<MEqq2qq> {
  static string className() { return "/ThePEG/MEqq2qq"; }
  // Return the class name.
  static string library() { return "libThePEGMEQCD.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MEqq2qq.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEqq2qq.tcc"
#endif

#endif /* ThePEG_MEqq2qq_H */
