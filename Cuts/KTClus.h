// -*- C++ -*-
#ifndef THEPEG_KTClus_H
#define THEPEG_KTClus_H
//
// This is the declaration of the KTClus class.
//

#include "ThePEG/Cuts/TwoCutBase.h"

namespace ThePEG {

/**
 * This clas implements the cuts relevant for the \f$\Delta
 * R\f$-measure in the longitudinally invariant kt-algorithm. By
 * default the cut is only applied to coloured particles, but
 * optionally it may be applied to all particle types.
 *
 * @see \ref KTClusInterfaces "The interfaces"
 * defined for KTClus.
 */
class KTClus: public TwoCutBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline KTClus();

  /**
   * The copy constructor.
   */
  inline KTClus(const KTClus &);

  /**
   * The destructor.
   */
  virtual ~KTClus();
  //@}

public:

  /** @name Overridden virtual functions defined in the base class. */
  //@{
  /**
   * Return the minimum allowed value of the longitudinally invariant
   * \f$k_\perp\f$-algorithms distance measure. This is defined as
   * \f$\min(p_{\perp i}, p_{\perp
   * j})\sqrt{\Delta\eta_{ij}^2+\Delta\phi_{ij}^2}\f$ for two outgoing
   * partons, or simply \f$p_{\perp i}\f$ or \f$p_{\perp j}\f$ for a
   * single outgoing parton. Returns 0 if both partons are incoming. A
   * null pointer indicates an incoming parton, hence the type of the
   * incoming parton is irrelevant.
   */
  virtual Energy minKTClus(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return the minimum allowed squared invariant mass of two outgoing
   * partons of type \a pi and \a pj. Returns zero.
   */
  virtual Energy2 minSij(tcPDPtr pi, tcPDPtr pj) const;

  /**
   * Return the minimum allowed value of the negative of the squared
   * invariant mass of an incoming parton of type \a pi and an
   * outgoing parton of type \a po. Returns zero.
   */
  virtual Energy2 minTij(tcPDPtr pi, tcPDPtr po) const;

  /**
   * Return the minimum allowed value of \f$\Delta
   * R_{ij}=\sqrt{\Delta\eta_{ij}^2+\Delta\phi_{ij}^2}\f$ of two
   * outgoing partons of type \a pi and \a pj. Returns zero.
   */
  virtual double minDeltaR(tcPDPtr pi, tcPDPtr pj) const;

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
   * The minimum allowed value of the longitudinally invariant
   * \f$k_\perp\f$-algorithms distance measure.
   */
  Energy theCut;

  /**
   * If true, only apply the cut to pairs of coloured particles.
   */
  bool onlyJets;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<KTClus> initKTClus;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  KTClus & operator=(const KTClus &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of KTClus. */
template <>
struct BaseClassTrait<KTClus,1> {
  /** Typedef of the first base class of KTClus. */
  typedef TwoCutBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the KTClus class and the shared object where it is defined. */
template <>
struct ClassTraits<KTClus>
  : public ClassTraitsBase<KTClus> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::KTClus"; }
  /** Return the name of the shared library be loaded to get
   *  access to the KTClus class and every other class it uses
   *  (except the base class). */
  static string library() { return "KTClus.so"; }
};

/** @endcond */

}

#include "KTClus.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KTClus.tcc"
#endif

#endif /* THEPEG_KTClus_H */
