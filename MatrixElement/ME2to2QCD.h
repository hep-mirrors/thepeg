// -*- C++ -*-
#ifndef ThePEG_ME2to2QCD_H
#define ThePEG_ME2to2QCD_H
// This is the declaration of the ME2to2QCD class.

#include "ThePEG/MatrixElement/ME2to2Base.h"
// #include "ME2to2QCD.fh"
// #include "ME2to2QCD.xh"

namespace ThePEG {

/**
 * The ME2to2QCD class inherits from the ME2to2Base class and can be
 * used as a sub class for all QCD 2\f$\rightarrow\f$2 processes. It
 * implements some common functions such as common pre-factors,
 * maximum number of flavours, treatment of interference terms and
 * possibility to enhance certain terms.
 *
 * @see \ref ME2to2QCDInterfaces "The interfaces"
 * defined for ME2to2QCD.
 * @see ME2to2Base
 */
class ME2to2QCD: public ME2to2Base {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ME2to2QCD();

  /**
   * Copy-constructor.
   */
  inline ME2to2QCD(const ME2to2QCD &);

  /**
   * Destructor.
   */
  virtual ~ME2to2QCD();
  //@}

public:

  /** @name Virtual functions required by the MEBase class. */
  //@{
  /**
   * Return the order in \f$\alpha_S\f$ in which this matrix element
   * is given. Returns 2.
   */
  virtual unsigned int orderInAlphaS() const;

  /**
   * Return the order in \f$\alpha_{EM}\f$ in which this matrix
   * element is given. Returns 0.
   */
  virtual unsigned int orderInAlphaEW() const;

  /**
   * The common prefactor for all 2\f$\rightarrow\f$2 QCD sub-processes
   * ie. \f$\alpha_S^2\f$.
   */
  double comfac() const;

  /**
   * Return the heaviest flavour allowed for this matrix element.
   */
  inline int maxFlavour() const;

  /**
   * K-factor for artificially boosting the cross-section.
   */
  inline double Kfac() const;

  /**
   * K-factor for artificially boosting colour-annihilation diagrams.
   */
  inline double KfacA() const;

  /**
   * Return true if interference terms should be used.
   */
  inline bool interference() const;

  /**
   * Return true if argument is a quark.
   */
  inline bool isQuark(const ParticleData &) const;

  /**
   * Return the quark with flavour i (or gluon if i = 0);
   */
  inline tcPDPtr quark(int i) const;
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
   * The heaviest flavour allowed for incoming and outgoing partons.
   */
  int theMaxFlavour;

  /**
   * Overall K-factor used to boost this cross-section.
   */
  double theKfac;

  /**
   * Overall K-factors used to boost the colour annihilation diagram
   * in the cross-section.
   */
  double theKfacA;

  /**
   * Flag so tell whether interference should be used or not.
   */
  bool useInterference;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractClassDescription<ME2to2QCD> initME2to2QCD;

  /**
   *  Private and non-existent assignment operator.
   */
  ME2to2QCD & operator=(const ME2to2QCD &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of ME2to2QCD.
 */
template <>
struct BaseClassTrait<ME2to2QCD,1>: public ClassTraitsType {
  /** Typedef of the base class of ME2to2QCD. */
  typedef ME2to2Base NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * ME2to2QCD class.
 */
template <>
struct ClassTraits<ME2to2QCD>: public ClassTraitsBase<ME2to2QCD> {
  /** Return the class name. */
  static string className() { return "ThePEG::ME2to2QCD"; }
};

/** @endcond */

}

#include "ME2to2QCD.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ME2to2QCD.tcc"
#endif

#endif /* ThePEG_ME2to2QCD_H */
