// -*- C++ -*-
#ifndef ThePEG_CKMBase_H
#define ThePEG_CKMBase_H
// This is the declaration of the CKMBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"
// #include "CKMBase.fh"
// #include "CKMBase.xh"

namespace ThePEG {

/**
 * CKMBase is an abstract base classused by the StandardModelBase to
 * implement the Cabibbo-Kobayashi-Mascawa mixing matrix. Concrete
 * sub-classes must implement the getMatrix(unsigned int) function.
 *
 * @see StandardModelBase.
 */
class CKMBase: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline CKMBase();

  /**
   * Copy-constructor.
   */
  inline CKMBase(const CKMBase &);

  /**
   * Destructor.
   */
  virtual ~CKMBase();
  //@}

public:

  /**
   * Return the matrix of squared CKM matrix elements. The returned
   * matrix should be for \a nf families. This function must be
   * overridden by sub-classes.
   */
  virtual vector< vector<double> >  getMatrix(unsigned int nf) const = 0;

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<CKMBase> initCKMBase;

  /**
   *  Private and non-existent assignment operator.
   */
  CKMBase & operator=(const CKMBase &);

};

/** This template specialization informs ThePEG about the base classes
 *  of CKMBase. */
template <>
struct BaseClassTrait<CKMBase,1> {
  /** Typedef of the first base class of CKMBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  CKMBase class. */
template <>
struct ClassTraits<CKMBase>: public ClassTraitsBase<CKMBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::CKMBase"; }
};

}

#include "CKMBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CKMBase.tcc"
#endif

#endif /* ThePEG_CKMBase_H */
