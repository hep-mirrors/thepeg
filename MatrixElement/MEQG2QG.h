// -*- C++ -*-
#ifndef ThePEG_MEQG2QG_H
#define ThePEG_MEQG2QG_H
//
// This is the declaration of the <!id>MEQG2QG<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEQG2QG<!!id> inherits from the <!class>ME2to2QCD<!!class>
// and implements the standard <i>qg->qg</i> matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2QCD.html">ME2to2QCD.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEQG2QG.fh"
// #include "MEQG2QG.xh"

namespace ThePEG {

class MEQG2QG: public ME2to2QCD {

public:

  inline MEQG2QG();
  inline MEQG2QG(const MEQG2QG &);
  virtual ~MEQG2QG();
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

  inline double colA1() const;
  inline double colB1() const;
  inline double colA2() const;
  inline double colB2() const;
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

  static NoPIOClassDescription<MEQG2QG> initMEQG2QG;
  // Describe a concrete class with persistent data.

  MEQG2QG & operator=(const MEQG2QG &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEQG2QG.
template <>
struct BaseClassTrait<MEQG2QG,1> {
  typedef ME2to2QCD NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEQG2QG>: public ClassTraitsBase<MEQG2QG> {
  static string className() { return "/ThePEG/MEQG2QG"; }
  // Return the class name.
  static string library() { return "libThePEGMEQCD.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MEQG2QG.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQG2QG.tcc"
#endif

#endif /* ThePEG_MEQG2QG_H */
