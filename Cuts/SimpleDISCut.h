// -*- C++ -*-
#ifndef THEPEG_SimpleDISCut_H
#define THEPEG_SimpleDISCut_H
//
// This is the declaration of the SimpleDISCut class.
//

#include "ThePEG/Cuts/TwoCutBase.h"

namespace ThePEG {

/**
 * SimpleDISCut inherits from TwoCutBase and omplements a simple
 * \f$Q^2\f$ cut on the a scattered lepton, either neutral or charged
 * current.
 *
 * @see \ref SimpleDISCutInterfaces "The interfaces"
 * defined for SimpleDISCut.
 */
class SimpleDISCut: public TwoCutBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline SimpleDISCut();

  /**
   * The copy constructor.
   */
  inline SimpleDISCut(const SimpleDISCut &);

  /**
   * The destructor.
   */
  virtual ~SimpleDISCut();
  //@}

public:

  /** @name Overridden virtual functions defined in the base class. */
  //@{
  /**
   * Return the minimum allowed squared invariant mass of two outgoing
   * partons of type \a pi and \a pj. Returns zero.
   */
  virtual Energy2 minSij(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return the minimum allowed value of the negative of the squared
   * invariant mass of an incoming parton of type \a pi and an
   * outgoing parton of type \a po. Return the minimum \f$Q^2\f$ if
   * the incoming and outgoing particles are matching leptons.
   */
  virtual Energy2 minTij(tcPDPtr pi, tcPDPtr po) const;

  /**
   * Return the minimum allowed value of \f$\Delta
   * R_{ij}=\sqrt{\Delta\eta_{ij}^2+\Delta\phi_{ij}^2}\f$ of two
   * outgoing partons of type \a pi and \a pj. Returns zero.
   */
  virtual double minDeltaR(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return the minimum allowed value of the longitudinally invariant
   * \f$k_\perp\f$-algorithms distance measure. This is defined as
   * \f$\min(p_{\perp i}, p_{\perp
   * j})\sqrt{\Delta\eta_{ij}^2+\Delta\phi_{ij}^2}\f$ for two outgoing
   * partons, or simply \f$p_{\perp i}\f$ or \f$p_{\perp j}\f$ for a
   * single outgoing parton. Returns 0 if both partons are incoming. A
   * null pointer indicates an incoming parton, hence the type of the
   * incoming parton is irrelevant. Returns zero.
   */
  virtual Energy minKTClus(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return the minimum allowed value of the Durham
   * \f$k_\perp\f$-algorithms distance measure. This is defined as
   * \f$2\min(E_j^2, E_j^2)(1-\cos\theta_{ij})/\hat{s}\f$ for two
   * outgoing partons. Returns zero.
   */
  virtual double minDurham(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return true if a pair of particles with type \a pitype and \a
   * pjtype and momenta \a pi and \a pj respectively passes the
   * cuts. \a inci and \a inj indicates if the corresponding particles
   * are incoming.
   */
  virtual bool passCuts(tcCutsPtr parent, tcPDPtr pitype, tcPDPtr pjtype,
			LorentzMomentum pi, LorentzMomentum pj,
			bool inci = false, bool incj = false) const;
  //@}

protected:

  /**
   * Check that the types of the incoming and outgoing particle types
   * matches a DIS event.
   */
  bool check(long idi, long ido) const;

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
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
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
   * Helper function used by the interface.
   */
  Energy maxMinQ2() const;

  /**
   * Helper function used by the interface.
   */
  Energy minMaxQ2() const;

private:

  /**
   * The minimum \f$Q^2\f$.
   */
  Energy2 theMinQ2;

  /**
   * The maximum \f$Q^2\f$. This is only applied as a post-cut.
   */
  Energy2 theMaxQ2;

  /**
   * If true the cut is applied to charged current events, otherwise
   * it is applied to neutral current events.
   */
  bool chargedCurrent;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<SimpleDISCut> initSimpleDISCut;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  SimpleDISCut & operator=(const SimpleDISCut &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of SimpleDISCut. */
template <>
struct BaseClassTrait<SimpleDISCut,1> {
  /** Typedef of the first base class of SimpleDISCut. */
  typedef TwoCutBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the SimpleDISCut class and the shared object where it is defined. */
template <>
struct ClassTraits<SimpleDISCut>
  : public ClassTraitsBase<SimpleDISCut> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::SimpleDISCut"; }
  /** Return the name of the shared library be loaded to get
   *  access to the SimpleDISCut class and every other class it uses
   *  (except the base class). */
  static string library() { return "SimpleDISCut.so"; }
};

/** @endcond */

}

#include "SimpleDISCut.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleDISCut.tcc"
#endif

#endif /* THEPEG_SimpleDISCut_H */