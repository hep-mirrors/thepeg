// -*- C++ -*-
#ifndef ThePEG_ME2to2QCD_H
#define ThePEG_ME2to2QCD_H
//
// This is the declaration of the <!id>ME2to2QCD<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ME2to2QCD<!!id> class inherits from the
// <!class>ME2to2Base<!!class> class and can be used as a sub class
// for all QCD <i>2->2</i> processes. It implements some common
// functions such as common pre-factors, maximum number of flavours,
// treatment of interference terms and possibility to enhance certain
// terms.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ME2to2Base.html">ME2to2Base.h</a>.
// 

#include "ThePEG/MatrixElement/ME2to2Base.h"
// #include "ME2to2QCD.fh"
// #include "ME2to2QCD.xh"

namespace ThePEG {

class ME2to2QCD: public ME2to2Base {

public:

  inline ME2to2QCD();
  inline ME2to2QCD(const ME2to2QCD &);
  virtual ~ME2to2QCD();
  // Standard ctors and dtor.

public:

  virtual unsigned int orderInAlphaS() const;
  virtual unsigned int orderInAlphaEW() const;
  // Return the order in respective couplings in which this matrix
  // element is given. Returns 2 and 0 respectively.

  double comfac() const;
  // The common prefactor for all 2->2 QCD sub-processes
  // ie. alpha_s^2.

  inline int maxFlavour() const;
  // Return the heaviest flavour allowed for this matrix element.

  inline double Kfac() const;
  // K-factor for artificially boosting the cross-section.

  inline double KfacA() const;
  // K-factor for artificially boosting colour-annihilation diagrams.

  inline bool interference() const;
  // Return true if interference terms should be used.

  inline bool isQuark(const ParticleData &) const;
  // Return true id argument is a quark.

  inline tcPDPtr quark(int i) const;
  // Return the quark with flavour i (or gluon if i = 0);

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

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

  int theMaxFlavour;
  // The heaviest flavour allowed for incoming and outgoing partons.

  double theKfac;
  double theKfacA;
  // Overall K-factors used to boost this cross-section.

  bool useInterference;
  // Flag so tell whether interference should be used or not.

private:

  static AbstractClassDescription<ME2to2QCD> initME2to2QCD;
  // Describe an abstract base class with persistent data.

  ME2to2QCD & operator=(const ME2to2QCD &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ME2to2QCD.
template <>
struct BaseClassTrait<ME2to2QCD,1> {
  typedef ME2to2Base NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ME2to2QCD>: public ClassTraitsBase<ME2to2QCD> {
  static string className() { return "/ThePEG/ME2to2QCD"; }
  // Return the class name.
};

}

#include "ME2to2QCD.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ME2to2QCD.tcc"
#endif

#endif /* ThePEG_ME2to2QCD_H */
