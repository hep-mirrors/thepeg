// -*- C++ -*-
#ifndef ThePEG_GRV94L_H
#define ThePEG_GRV94L_H
// This is the declaration of the GRV94L class.

#include "ThePEG/PDF/GRVBase.h"
// #include "GRV94L.fh"
// #include "GRV94L.xh"

namespace ThePEG {

/**
 * GRV94L inherits from PDFBase via the GRVBase class and implements
 * the GRV94L parton densities for (anti) protons and neutrons.
 *
 * @see \ref GRV94LInterfaces "The interfaces"
 * defined for GRV94L.
 */
class GRV94L: public GRVBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline GRV94L();

  /**
   * Copy-constructor.
   */
  inline GRV94L(const GRV94L &);

  /**
   * Destructor.
   */
  virtual ~GRV94L();
  //@}

  /**
   * Return the cutoff scale.
   */
  inline Energy2 mu2() const;

  /**
   * Return the square of \f$\Lambda_{QCD}\f$ used.
   */
  inline Energy2 lam2() const;

protected:

  /**
   * Setup the \a l\f$=\log{1/x}\f$ and \a scale \f$Q^2\f$ to be used
   * in the following call to uv(), dv)=, etc.
   */
  virtual void setup(double l, Energy2 scale) const;

  /**
   * Return the value of the u valens density for the values previously given
   * by setup().
   */
  virtual double uv() const;

  /**
   * Return the value of the d valens density for the values previously given
   * by setup().
   */
  virtual double dv() const;

  /**
   * Return the value of the difference between the u and d sea
   * densities for the values previously given by setup().
   */
  virtual double del() const;

  /**
   * Return the value of the average u and d sea densities for the
   * values previously given by setup().
   */
  virtual double udb() const;

  /**
   * Return the value of the s density for the values previously given by
   * setup().
   */
  virtual double sb() const;

  /**
   * Return the value of the c density for the values previously given by
   * setup().
   */
  virtual double cb() const;

  /**
   * Return the value of the b density for the values previously given by
   * setup().
   */
  virtual double bb() const;

  /**
   * Return the value of the gluon densities for the values previously
   * given by setup().
   */
  virtual double gl() const;

public:

  /**
   * Standard Init function used to initialize the interface.
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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

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
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<GRV94L> initGRV94L;

  /**
   *  Private and non-existent assignment operator.
   */
  GRV94L & operator=(const GRV94L &);

};

/** This template specialization informs ThePEG about the
 *  base classes of GRV94L. */
template <>
struct BaseClassTrait<GRV94L,1>: public ClassTraitsType {
  /** Typedef of the first base class of GRV94L. */
  typedef GRVBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  GRV94L class and the shared object where it is defined. */
template <>
struct ClassTraits<GRV94L>: public ClassTraitsBase<GRV94L> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::GRV94L"; }
  /** Return the name of the shared library be loaded to get access to
   *  the GRV94L class and every other class it uses (except
   *  the base class). */
  static string library() { return "GRV94L.so"; }
};

}

#include "GRV94L.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GRV94L.tcc"
#endif

#endif /* ThePEG_GRV94L_H */
