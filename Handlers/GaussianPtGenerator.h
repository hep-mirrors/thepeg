// -*- C++ -*-
#ifndef THEPEG_GaussianPtGenerator_H
#define THEPEG_GaussianPtGenerator_H
// This is the declaration of the GaussianPtGenerator class.

#include "ThePEG/Handlers/PtGenerator.h"

namespace ThePEG {

/**
 * GaussianPtGenerator inherits from the abstract PtGenerator
 * class. It will generate a transverse momentum distributed according
 * to a gaussian.
 *
 * @see \ref GaussianPtGeneratorInterfaces "The interfaces"
 * defined for GaussianPtGenerator.
 */
class GaussianPtGenerator: public PtGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline GaussianPtGenerator();

  /**
   * Copy-constructor.
   */
  inline GaussianPtGenerator(const GaussianPtGenerator &);

  /**
   * Destructor.
   */
  virtual ~GaussianPtGenerator();
  //@}

public:

  /** @name Virtual functions required by the PtGenerator class. */
  //@{
  /**
   * Generate (\f$k_x, k_y\f$) components of the transverse
   * momentum. They will be distributed as
   * \f$\exp(-k_\perp^2/\sigma^2)k_\perp dk_\perp\f$ with
   * \f$k_\perp^2=k_x^2+k_y^2\f$ and \f$\sigma=\f$ theSigma. The
   * distribution is cutoff at \f$k_\perp=\f$ theUpperCut.
   */
  virtual TransverseMomentum generate() const;
  //@}

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

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

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The width of the Gaussian distribution. The average squared
   * transverse momentum is theSigma squared.
   */
  Energy theSigma;

  /**
   * Upper cutoff for the transverse momentum distribution.
   */
  Energy theUpperCut;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<GaussianPtGenerator> initGaussianPtGenerator;

  /**
   * Private and non-existent assignment operator.
   */
  GaussianPtGenerator & operator=(const GaussianPtGenerator &);

};

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/**
 * This template specialization informs ThePEG about the
 * base class of GaussianPtGenerator.
 */
template <>
struct BaseClassTrait<GaussianPtGenerator,1>: public ClassTraitsType {
  /** Typedef of the base class of GaussianPtGenerator. */
  typedef PtGenerator NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * GaussianPtGenerator class and the shared object where it is
 * defined.
 */
template <>
struct ClassTraits<GaussianPtGenerator>
  : public ClassTraitsBase<GaussianPtGenerator> {
  /** Return the class name. */
  static string className() { return "ThePEG::GaussianPtGenerator"; }
  /** Return the name of the shared library to be loaded to get access
   * to the GaussianPtGenerator class and every other class it uses
   * (except the base class). */
  static string library() { return "GaussianPtGenerator.so"; }

};

}

#include "GaussianPtGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GaussianPtGenerator.tcc"
#endif

#endif /* THEPEG_GaussianPtGenerator_H */
