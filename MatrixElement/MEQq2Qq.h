// -*- C++ -*-
#ifndef ThePEG_MEQq2Qq_H
#define ThePEG_MEQq2Qq_H
// This is the declaration of the MEQq2Qq class.

#include "ThePEG/MatrixElement/ME2to2QCD.h"
// #include "MEQq2Qq.fh"
// #include "MEQq2Qq.xh"

namespace ThePEG {

/**
 * MEQq2Qq inherits from ME2to2QCD and implements the standard
 * \f$q_iq_j\rightarrow q_iq_j\f$ mmatrix element.
 *
 *
 * @see ME2to2QCD.
 * 
 */
class MEQq2Qq: public ME2to2QCD {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MEQq2Qq();

  /**
   * Copy-constructor.
   */
  inline MEQq2Qq(const MEQq2Qq &);

  /**
   * Destructor.
   */
  virtual ~MEQq2Qq();
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
  static NoPIOClassDescription<MEQq2Qq> initMEQq2Qq;

  /**
   *  Private and non-existent assignment operator.
   */
  MEQq2Qq & operator=(const MEQq2Qq &);

};

}


namespace ThePEG {

/** This template specialization informs ThePEG about the
 *  base classes of MEQq2Qq. */
template <>
struct BaseClassTrait<MEQq2Qq,1> {
  /** Typedef of the first base class of MEQq2Qq. */
  typedef ME2to2QCD NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the MEQq2Qq class and the shared object where it is defined. */
template <>
struct ClassTraits<MEQq2Qq>: public ClassTraitsBase<MEQq2Qq> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MEQq2Qq"; }
  /** Return the name of the shared library be loaded to get
   *  access to the MEQq2Qq class and every other class it uses
   *  (except the base class). */
  static string library() { return "libThePEGMEQCD.so"; }
};

}

#include "MEQq2Qq.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MEQq2Qq.tcc"
#endif

#endif /* ThePEG_MEQq2Qq_H */
