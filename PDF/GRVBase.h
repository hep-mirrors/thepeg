// -*- C++ -*-
#ifndef ThePEG_GRVBase_H
#define ThePEG_GRVBase_H
// This is the declaration of the GRVBase class.

#include "ThePEG/PDF/PDFBase.h"
// #include "GRVBase.fh"
// #include "GRVBase.xh"

namespace ThePEG {

/**
 * GRVBase inherits from PDFBase and is used as a base class for all
 * GRV parton densities.
 *
 * @see \ref GRVBaseInterfaces "The interfaces"
 * defined for GRVBase.
 */
class GRVBase: public PDFBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  GRVBase();

  /**
   * Copy-constructor.
   */
  GRVBase(const GRVBase &);

  /**
   * Destructor.
   */
  virtual ~GRVBase();
  //@}

public:

  /** @name Virtual functions required by the PDFBase class. */
  //@{
  /**
   * Return true if this PDF can handle the extraction of parton from the
   * given particle, ie. if the particle is a proton or neutron.
   */
  virtual bool canHandleParticle(tcPDPtr particle) const;

  /**
   * Return the parton types which are described by these parton
   * densities.
   */
  virtual cPDVector partons(tcPDPtr p) const;

  /**
   * Return the value of the density of parton at the given a scale
   * and log fractional momentum l (the optional virtuality of the
   * incoming particle is not used).
   */
  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale) const;

  /**
   * Return the valaens partof the density of parton at the given a
   * scale and log fractional momentum l (the optional virtuality of
   * the incoming particle is not used).
   */
  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale) const;
  //@}

public:

  /** @name Access derived kinematical quantities. */
  //@{
  /**
   * Return last selected
   * \f$S\f$. \f$S=\log(\log(Q^2/\mu^2)/\log(Q^2/\Lambda_{QCD}^2))\f$
   */
  inline double S() const;

  /**
   * Return last selected
   * \f$S^2\f$. \f$S=\log(\log(Q^2/\mu^2)/\log(Q^2/\Lambda_{QCD}^2))\f$
   */
  inline double S2() const;

  /**
   * Return last selected
   * \f$S^3\f$. \f$S=\log(\log(Q^2/\mu^2)/\log(Q^2/\Lambda_{QCD}^2))\f$
   */
  inline double S3() const;

  /**
   * Return last selected
   * \f$\sqrt{S}\f$. \f$S=\log(\log(Q^2/\mu^2)/\log(Q^2/\Lambda_{QCD}^2))\f$
   */
  inline double rootS() const;

  /**
   * Return last selected momentum fraction, \f$x\f$.
   */
  inline double x() const;

  /**
   * Return last selected logarithmic momentum fraction
   * \f$l=\log(1/x)\f$.
   */
  inline double lx() const;

  /**
   * Return one minus the last selected momentum fraction, eps\f$=1-x\f$.
   */
  inline double eps() const;

  /**
   * Return the square root of the last selected momentum fraction,
   * \f$x\f$.
   */
  inline double rootx() const;
  //@}

protected:

  /**
   * Setup the \a l\f$=\log{1/x}\f$ and \a scale \f$Q^2\f$ to be used
   * in the following call to uv(), dv)=, etc.
   */
  virtual void setup(double l, Energy2 scale) const = 0;

  /**
   * Setup the \a l\f$=\log{1/x}\f$ and \a scale \f$Q^2\f$ to be used
   * in the following call to uv(), dv)=, etc.
   */
  void setup(double l, Energy2 scale, Energy2 mu2, Energy2 lam2) const;

  /**
   * The form of the valens density functions.
   */
  double valens(double N, double ak, double bk,
		double a, double b, double c, double d) const;

  /**
   * The form of the light sea and gluon density
   * functions.
   */
  double lightsea(double al, double be, double ak, double bk, double a,
		  double b, double c, double d, double e, double es) const;

  /**
   * The form of the heavy sea density functions.
   */
  double heavysea(double sth, double al, double be, double ak, double ag,
		  double b, double d, double e, double es) const;

  /**
   * Return the value of the u valens density for the values previously given
   * by setup().
   */
  virtual double uv() const = 0;

  /**
   * Return the value of the d valens density for the values previously given
   * by setup().
   */
  virtual double dv() const = 0;

  /**
   * Return the value of the difference between the u and d sea
   * densities for the values previously given by setup().
   */
  virtual double del() const = 0;

  /**
   * Return the value of the average u and d sea densities for the
   * values previously given by setup().
   */
  virtual double udb() const = 0;

  /**
   * Return the value of the s density for the values previously given by
   * setup().
   */
  virtual double sb() const = 0;

  /**
   * Return the value of the c density for the values previously given by
   * setup().
   */
  virtual double cb() const = 0;

  /**
   * Return the value of the b density for the values previously given by
   * setup().
   */
  virtual double bb() const = 0;

  /**
   * Return the value of the gluon densities for the values previously
   * given by setup().
   */
  virtual double gl() const = 0;

  /**
   * fuv() returns the saved values from the quv() functions if
   * present. Otherwise uv() is called, saved and returned.
   */
  inline double fuv() const;

  /**
   * fdv() returns the saved values from the dv() functions if
   * present. Otherwise dv() is called, saved and returned.
   */
  inline double fdv() const;

  /**
   * fdel() returns the saved values from the del() functions if
   * present. Otherwise del() is called, saved and returned.
   */
  inline double fdel() const;

  /**
   * fudb() returns the saved values from the udb() functions if
   * present. Otherwise udb() is called, saved and returned.
   */
  inline double fudb() const;

  /**
   * fsb() returns the saved values from the sb() functions if
   * present. Otherwise sb() is called, saved and returned.
   */
  inline double fsb() const;

  /**
   * fcb() returns the saved values from the cb() functions if
   * present. Otherwise cb() is called, saved and returned.
   */
  inline double fcb() const;

  /**
   * fbb() returns the saved values from the bb() functions if
   * present. Otherwise bb() is called, saved and returned.
   */
  inline double fbb() const;

  /**
   * fgl() returns the saved values from the gl() functions if
   * present. Otherwise gl() is called, saved and returned.
   */
  inline double fgl() const;

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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
  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  virtual IVector getReferences();
  //@}

private:

  /**
   * The last selected logarithmic momentum fraction
   * \f$l=\log(1/x)\f$.
   */
  mutable double theLx;

  /**
   * THe last selected momentum fraction, \f$x\f$.
   */
  mutable double thex;

  /**
   * One minus the last selected momentum fraction, eps\f$=1-x\f$.
   */
  mutable double theEps;

  /**
   * The square root of the last selected momentum fraction, \f$x\f$.
   */
  mutable double theRootx;

  /**
   * The last selected scale.
   */
  mutable Energy2 Q2;

  /**
   * The last used \f$\Lambda_{QCD}^2\f$.
   */
  mutable Energy2 theLam2;

  /**
   * The last used \f$\mu^2\f$.
   */
  mutable Energy2 theMu2;

  /**
   * The last selected
   * \f$S\f$. \f$S=\log(\log(Q^2/\mu^2)/\log(Q^2/\Lambda_{QCD}^2))\f$
   */
  mutable double theS;

  /**
   * Return last selected \f$S^2\f$.
   */
  mutable double theS2;

  /**
   * Return last selected \f$S^3\f$.
   */
  mutable double theS3;

  /**
   * Return last selected \f$\sqrt{S}\f$.
   */
  mutable double theRootS;

  /**
   * Saved values from the different functions.
   */
  mutable double uvSave;

  /**
   * Saved values from the different functions.
   */
  mutable double dvSave;

  /**
   * Saved values from the different functions.
   */
  mutable double delSave;

  /**
   * Saved values from the different functions.
   */
  mutable double udbSave;

  /**
   * Saved values from the different functions.
   */
  mutable double sbSave;

  /**
   * Saved values from the different functions.
   */
  mutable double cbSave;

  /**
   * Saved values from the different functions.
   */
  mutable double bbSave;

  /**
   * Saved values from the different functions.
   */
  mutable double glSave;

private:

  /**
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<GRVBase> initGRVBase;

  /**
   *  Private and non-existent assignment operator.
   */
  GRVBase & operator=(const GRVBase &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of GRVBase. */
template <>
struct BaseClassTrait<GRVBase,1>: public ClassTraitsType {
  /** Typedef of the first base class of GRVBase. */
  typedef PDFBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  GRVBase class and the shared object where it is defined. */
template <>
struct ClassTraits<GRVBase>: public ClassTraitsBase<GRVBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::GRVBase"; }
  /** Return the name of the shared library be loaded to get access to
   *  the GRVBase class and every other class it uses (except
   *  the base class). */
  static string library() { return "GRVBase.so"; }
};

/** @endcond */

}

#include "GRVBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GRVBase.tcc"
#endif

#endif /* ThePEG_GRVBase_H */
