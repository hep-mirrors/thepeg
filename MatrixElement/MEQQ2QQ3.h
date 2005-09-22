// -*- C++ -*-
#ifndef ThePEG_MEQQ2QQ_H
#define ThePEG_MEQQ2QQ_H
// This is the declaration of the MEQQ2QQ class.

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEQQ2QQ.fh"
// #include "MEQQ2QQ.xh"

namespace ThePEG {

/**
 * MEQQ2QQ inherits from ME2to2QCD and implements the standard
 * \f$q_iq_i\rightarrow q_iq_i\f$ matrix element.
 *
 * @see \ref MEQQ2QQInterfaces "The interfaces"
 * defined for MEQQ2QQ.
 * @see ME2to2QCD
 */
class MEQQ2QQ: public ME2to2QCD {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MEQQ2QQ();

  /**
   * Copy-constructor.
   */
  inline MEQQ2QQ(const MEQQ2QQ &);

  /**
   * Destructor.
   */
  virtual ~MEQQ2QQ();
  //@}

public:

  /** @name Virtual functions required by the MEBase class. */
  //@{
  /**
   * The matrix element for the kinematical configuration
   * previously provided by the last call to setKinematics(), suitably
   * scaled by sHat() to give a dimension-less number.
   * @return the matrix element scaled with sHat() to give a
   * dimensionless number.
   */
  virtual double me2() const;

  /**
   * Add all possible diagrams with the add() function.
   */
  virtual void getDiagrams() const;

  /**
   * Return a Selector with possible colour geometries for the selected
   * diagram weighted by their relative probabilities.
   * @param diag the diagram chosen.
   * @return the possible colour geometries weighted by their
   * relative probabilities.
   */
  virtual Selector<const ColourLines *>
  colourGeometries(tcDiagPtr diag) const;

  /**
   * Get diagram selector. With the information previously supplied with the
   * setKinematics method, a derived class may optionally
   * override this method to weight the given diagrams with their
   * (although certainly not physical) relative probabilities.
   * @param dv the diagrams to be weighted.
   * @return a Selector relating the given diagrams to their weights.
   */
  virtual Selector<DiagramIndex> diagrams(const DiagramVector & dv) const;
  //@}

protected:

  /** @name Internal functions returning the matrix element squared
   *  for different colour configurations. */
  //@{
  /**
   * Return the matrix element squared (without common pre-factors)
   * for the specific colour configuration.
   */
  inline double colA() const;

  /**
   * Return the matrix element squared (without common pre-factors)
   * for the specific colour configuration.
   */
  inline double colB() const;
  //@}

public:

  /**
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<MEQQ2QQ> initMEQQ2QQ;

  /**
   *  Private and non-existent assignment operator.
   */
  MEQQ2QQ & operator=(const MEQQ2QQ &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of MEQQ2QQ. */
template <>
struct BaseClassTrait<MEQQ2QQ,1>: public ClassTraitsType {
  /** Typedef of the first base class of MEQQ2QQ. */
  typedef ME2to2QCD NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the MEQQ2QQ class and the shared object where it is defined. */
template <>
struct ClassTraits<MEQQ2QQ>: public ClassTraitsBase<MEQQ2QQ> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MEQQ2QQ"; }
  /** Return the name of the shared library be loaded to get
   *  access to the MEQQ2QQ class and every other class it uses
   *  (except the base class). */
  static string library() { return "MEQCD.so"; }
};

/** @endcond */

}

#include "MEQQ2QQ3.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQQ2QQ.tcc"
#endif

#endif /* ThePEG_MEQQ2QQ_H */
