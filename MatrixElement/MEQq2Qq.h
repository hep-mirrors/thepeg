// -*- C++ -*-
#ifndef ThePEG_MEQq2Qq_H
#define ThePEG_MEQq2Qq_H
//
// This is the declaration of the <!id>MEQq2Qq<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>MEQq2Qq<!!id> inherits from the <!class>ME2to2QCD<!!class>
// and implements the standard <i>qq'->qq'</i> matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2QCD.html">ME2to2QCD.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEQq2Qq.fh"
// #include "MEQq2Qq.xh"

namespace ThePEG {

class MEQq2Qq: public ME2to2QCD {

public:

  inline MEQq2Qq();
  inline MEQq2Qq(const MEQq2Qq &);
  virtual ~MEQq2Qq();
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

  static NoPIOClassDescription<MEQq2Qq> initMEQq2Qq;
  // Describe a concrete class with persistent data.

  MEQq2Qq & operator=(const MEQq2Qq &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MEQq2Qq.
template <>
struct BaseClassTrait<MEQq2Qq,1> {
  typedef ME2to2QCD NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MEQq2Qq>: public ClassTraitsBase<MEQq2Qq> {
  static string className() { return "/ThePEG/MEQq2Qq"; }
  // Return the class name.
  static string library() { return "libThePEGMEQCD.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MEQq2Qq.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQq2Qq.tcc"
#endif

#endif /* ThePEG_MEQq2Qq_H */
