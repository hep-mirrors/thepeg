// -*- C++ -*-
#ifndef ThePEG_MEGG2QQ_H
#define ThePEG_MEGG2QQ_H
//
// This is the declaration of the <!id>MEGG2QQ<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEGG2QQ<!!id> inherits from the <!class>ME2to2QCD<!!class>
// and implements the standard <i>gg->qqbar</i> matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2QCD.html">ME2to2QCD.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEGG2QQ.fh"
// #include "MEGG2QQ.xh"

namespace ThePEG {

class MEGG2QQ: public ME2to2QCD {

public:

  inline MEGG2QQ();
  inline MEGG2QQ(const MEGG2QQ &);
  virtual ~MEGG2QQ();
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

  static NoPIOClassDescription<MEGG2QQ> initMEGG2QQ;
  // Describe a concrete class with persistent data.

  MEGG2QQ & operator=(const MEGG2QQ &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEGG2QQ.
template <>
struct BaseClassTrait<MEGG2QQ,1> {
  typedef ME2to2QCD NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEGG2QQ>: public ClassTraitsBase<MEGG2QQ> {
  static string className() { return "/ThePEG/MEGG2QQ"; }
  // Return the class name.
  static string library() { return "libThePEGMEQCD.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MEGG2QQ.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEGG2QQ.tcc"
#endif

#endif /* ThePEG_MEGG2QQ_H */
