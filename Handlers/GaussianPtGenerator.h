// -*- C++ -*-
#ifndef THEPEG_GaussianPtGenerator_H
#define THEPEG_GaussianPtGenerator_H
//
// This is the declaration of the <!id>GaussianPtGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Handlers/PtGenerator.h"

namespace ThePEG {

class GaussianPtGenerator: public PtGenerator {

public:

  inline GaussianPtGenerator();
  inline GaussianPtGenerator(const GaussianPtGenerator &);
  virtual ~GaussianPtGenerator();
  // Standard ctors and dtor.

public:
  virtual pair<Energy,Energy> generate() const;
  // Return (px, py) components of the transverse momentum.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  Energy theSigma;
  // The width of the Gaussian distribution. The average squared
  // transverse momentum is theSigma squared.

  Energy theUpperCut;
  // Upper cutoff for the transverse momentum distribution.

private:

  static ClassDescription<GaussianPtGenerator> initGaussianPtGenerator;
  // Describe a concrete class with persistent data.

  GaussianPtGenerator & operator=(const GaussianPtGenerator &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of GaussianPtGenerator.
template <>
struct BaseClassTrait<GaussianPtGenerator,1> {
  typedef PtGenerator NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<GaussianPtGenerator>
  : public ClassTraitsBase<GaussianPtGenerator> {
  static string className() { return "ThePEG::GaussianPtGenerator"; }
  // Return the class name.
  static string library() { return "GaussianPtGenerator.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "GaussianPtGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GaussianPtGenerator.tcc"
#endif

#endif /* THEPEG_GaussianPtGenerator_H */
