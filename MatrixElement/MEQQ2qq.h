// -*- C++ -*-
#ifndef ThePEG_MEQQ2qq_H
#define ThePEG_MEQQ2qq_H
//
// This is the declaration of the <!id>MEQQ2qq<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEQQ2qq<!!id> inherits from the <!class>ME2to2QCD<!!class>
// and implements the standard <i>qqbar->q'qbar'</i> matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2QCD.html">ME2to2QCD.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEQQ2qq.fh"
// #include "MEQQ2qq.xh"

namespace ThePEG {

class MEQQ2qq: public ME2to2QCD {

public:

  inline MEQQ2qq();
  inline MEQQ2qq(const MEQQ2qq &);
  virtual ~MEQQ2qq();
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

  static NoPIOClassDescription<MEQQ2qq> initMEQQ2qq;
  // Describe a concrete class with persistent data.

  MEQQ2qq & operator=(const MEQQ2qq &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEQQ2qq.
template <>
struct BaseClassTrait<MEQQ2qq,1> {
  typedef ME2to2QCD NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEQQ2qq>: public ClassTraitsBase<MEQQ2qq> {
  static string className() { return "/ThePEG/MEQQ2qq"; }
  // Return the class name.
  static string library() { return "libThePEGMEQCD.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MEQQ2qq.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQQ2qq.tcc"
#endif

#endif /* ThePEG_MEQQ2qq_H */
