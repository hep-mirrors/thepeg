// -*- C++ -*-
#ifndef ThePEG_KinematicalCuts_H
#define ThePEG_KinematicalCuts_H
// This is the declaration of the KinematicalCuts class.

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.fh"
#include "ThePEG/Utilities/Triplet.h"
#include "ThePEG/PDT/StandardMatchers.h"
// #include "KinematicalCuts.fh"
// #include "KinematicalCuts.xh"

namespace ThePEG {

/**
 * The KinematicalCuts class is used to make cuts on generated
 * events. A KinematicalCuts object is selected for each generated
 * collision. The CollisionHandler has a default KinematicalCuts
 * object, which may be overridden by the selected SubProcessHandler
 * object, which in turn may be overridden by the selected MEBase
 * object.
 *
 * The KinematicalCuts is used in two different ways. Individual
 * handlers may use the specific member functions which specify cuts
 * on individual variables. In addition the cut() member functions are
 * always called by the CollisionHandler to automatically check that
 * all cuts are passed. It is possible to derive new classes from the
 * KinematicalCuts class, in which case the virtual newcut() methods
 * may be overridden and will be called from the cut() methods.
 *
 * @see CollisionHandler
 * @see SubProcessHandler
 * @see MEBase
 * @see Collision
 * @see SubProcess
 * 
 */
class KinematicalCuts: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  KinematicalCuts();

  /**
   * Copy-constructor.
   */
  KinematicalCuts(const KinematicalCuts &);

  /**
   * Destructor.
   */
  virtual ~KinematicalCuts();
  //@}

public:

  /** @name Functions called by the CollisionHandler to check if
   *  generated SubProcess or Event passes all cuts. */
  //@{
  /**
   * This method is called by the CollisionHandler with the primary
   * SubProcess provided in its cm frame.
   * @throws Veto if the SubProcess did not pass all cuts.
   */
  void cut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));

  /**
   * This method is called by the CollisionHandler with the primary
   * collision after its first step provided in int cm frame. The
   * LorentzRotation provided should give the transformation to the
   * laboratory frame.
   * @throws Veto if the Collision did not pass all cuts.
   */
  void cut(const Collision &, const LorentzRotation &) const
    ThePEG_THROW_SPEC((Veto));
  //@}

public:

  /** @name Access to cuts on specific variables related to a SubProcess. */
  //@{
  /**
   * The minimum values of the invariant mass of the hard sub-process.
   */
  inline Energy mHatMin() const;

  /**
   * The maximum values of the invariant mass of the hard sub-process.
   */
  inline Energy mHatMax() const;

  /**
   * The minimum values of the squared invariant mass of the hard
   * sub-process.
   */
  inline Energy sHatMin() const;
  /**
   * Themaximum values of the squared invariant mass of the hard
   * sub-process.
   */
  inline Energy sHatMax() const;

  /**
   * Returns true if mHatMin() <= \a mhat < mHatMax().
   */
  inline bool mHat(Energy mhat) const;

  /**
   * Returns true if sHatMin() <= \a shat < sHatMax().
   */
  inline bool sHat(Energy2 shat) const;

  /**
   * The minimum values of the transverse momentum of the outgoing
   * particles in the hard sub-process.
   */
  inline Energy pTHatMin() const;

  /**
   * The maximum values of the transverse momentum of the outgoing
   * particles in the hard sub-process.
   */
  inline Energy pTHatMax() const;

  /**
   * Returns true if pTHatMin() <= \a pt < pTHatMax().
   */
  inline bool pTHat(Energy pt) const;

  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than singularMassMax().
   */
  inline Energy pTHatSingularMin() const;

  /**
   * The maxium mass for outgoing particles used in
   * pTHatSingularMin().
   */
  inline Energy singularMassMax() const;
  //@}

  /** @name Access to cuts on specific variables related to a Collision. */
  //@{
  /**
   * The minimum value of the rapidity of the hard scattering
   * sub-system.
   */
  inline double yStarMin() const;

  /**
   * The maximum value of the rapidity of the hard scattering
   * sub-system.
   */
  inline double yStarMax() const;

  /**
   * Returns true if yStarMin() <= \a y <= yStarMax().
   */
  inline bool yStar(double y) const;

  /**
   * The minimum value of the maximum rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double maxYMin() const;

  /**
   * The maximum value of the maximum rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double maxYMax() const;

  /**
   * Returns true if maxYMin() <= \a y <= maxYMax().
   */
  inline bool maxY(double y) const;

  /**
   * The minimum value of the minimum rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double minYMin() const;

  /**
   * The maximum value of the minimum rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double minYMax() const;

  /**
   * Returns true if minYMin() <= \a y <= minYMax().
   */
  inline bool minY(double y) const;

  /**
   * The minimum value of the maximum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double maxEtaMin() const;

  /**
   * The maximum value of the maximum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double maxEtaMax() const;

  /**
   * Returns true if maxEtaMin() <= \a eta <= maxEtaMax().
   */
  inline bool maxEta(double eta) const;

  /**
   * The minimum value of the minimum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double minEtaMin() const;

  /**
   * The maximum value of the minimum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  inline double minEtaMax() const;

  /**
   * Returns true if minEtaMin() <= \a eta <= minEtaMax().
   */
  inline bool minEta(double eta) const;

  /**
   * The minimumvalue of the maximum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  inline double maxCTMin() const;

  /**
   * The maximum value of the maximum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  inline double maxCTMax() const;

  /**
   * Returns true if maxCTMin() <= \a ct <= maxCTMax().
   */
  inline bool maxCT(double ct) const;

  /**
   * The minimum value of the minimum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  inline double minCTMin() const;

  /**
   * The maximum value of the minimum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  inline double minCTMax() const;

  /**
   * Returns true if minCTMin() <= \a ct <= minCTMax().
   */
  inline bool minCT(double ct) const;

  /**
   * The minimum value of the Bjorken-x of the particle comin into the
   * hard scattering along the positive z-axis.
   */
  inline double x1Min() const;

  /**
   * The maximum value of the Bjorken-x of the particle comin into the
   * hard scattering along the positive z-axis.
   */
  inline double x1Max() const;

  /**
   * Returns true if x1Min() < \a x <= x1Max().
   */
  inline bool x1(double x) const;

  /**
   * The minimum value of the Bjorken-x of the particle comin into the
   * hard scattering along the negative z-axis.
   */
  inline double x2Min() const;

  /**
   * The maximum value of the Bjorken-x of the particle comin into the
   * hard scattering along the negative z-axis.
   */
  inline double x2Max() const;

  /**
   * Returns true if x2Min() < \a x <= x2Max().
   */
  inline bool x2(double x) const;

  /**
   * The minimum value of the Feynman-x of the hard scattering.
   */
  inline double xFMin() const;

  /**
   * The maximum value of the Feynman-x of the hard scattering.
   */
  inline double xFMax() const;

  /**
   * Returns true if xFMin() <= \a x <= xFMax().
   */
  inline bool xF(double x) const;

  /**
   * The minimum value of cosine of the scattering angle in the
   * restframe of a hard \f$2\rightarrow 2\f$ scattering.
   */
  inline double cTHMin() const;

  /**
   * The maximum value of cosine of the scattering angle in the
   * restframe of a hard \f$2\rightarrow 2\f$ scattering.
   */
  inline double cTHMax() const;

  /**
   * Returns true if cTHMin() <= \a cth <= cTHMax().
   */
  inline bool cTH(double cth) const;

  /**
   * The minimum value of \f$|\hat{t}|\f$ of a hard \f$2\rightarrow
   * 2\f$ scattering.
   */
  inline Energy2 tHatMin() const;

  /**
   * The maximum value of \f$|\hat{t}|\f$ of a hard \f$2\rightarrow
   * 2\f$ scattering.
   */
  inline Energy2 tHatMax() const;

  /**
   * Returns true if tHatMin() <= \a th < tHatMax().
   */
  inline bool tHat(Energy2 that) const;

  /**
   * The minimum value of \f$|\hat{u}|\f$ of a hard \f$2\rightarrow
   * 2\f$ scattering.
   */
  inline Energy2 uHatMin() const;

  /**
   * The maximum value of \f$|\hat{u}|\f$ of a hard \f$2\rightarrow
   * 2\f$ scattering.
   */
  inline Energy2 uHatMax() const;

  /**
   * Returns true if uHatMin() <= \a uh < uHatMax().
   */
  inline bool uHat(Energy2 uhat) const;

  /**
   * The minimum value of the scale in a hard scattering as defined by
   * the Handlers which performed the hard scattering.
   */
  inline Energy2 scaleMin() const;

  /**
   * The maximum value of the scale in a hard scattering as defined by
   * the Handlers which performed the hard scattering.
   */
  inline Energy2 scaleMax() const;

  /**
   * Returns true if scaleMin() <= \a sc < scaleMax().
   */
  inline bool scale(Energy2 sc) const;
  //@}

  /** @name Access to cuts on specific variables related to a
   *  lepto-production <code>Collision</code>. */
  //@{
  /**
   * For lepton-particle scattering, the minimum energy of the
   * scattered lepton.
   */
  inline Energy DISLepton1EnergyMin() const;

  /**
   * For lepton-particle scattering, the maximum energy of the
   * scattered lepton.
   */
  inline Energy DISLepton1EnergyMax() const;

  /**
   * For lepton-particle scattering, the minimum scattering angle of
   * the lepton.
   */
  inline double DISLepton1AngleMin() const;

  /**
   * For lepton-particle scattering, the maximum scattering angle of
   * the lepton.
   */
  inline double DISLepton1AngleMax() const;

  /**
   * Minimum \f$Q^2\f$. For lepton-particle scattering, the minimum
   * \f$Q^2\f$ as calculated from the scattered lepton.
   */
  inline Energy2 DISQ21Min() const;
  /**
   * Maximum \f$Q^2\f$. For lepton-particle scattering, the maximum
   * \f$Q^2\f$ as calculated from the scattered lepton.
   */
  inline Energy2 DISQ21Max() const;

  /**
   * For particle-lepton scattering, the minimum
   * energy of the scattered lepton.
   */
  inline Energy DISLepton2EnergyMin() const;

  /**
   * For particle-lepton scattering, the maximum
   * energy of the scattered lepton.
   */
  inline Energy DISLepton2EnergyMax() const;

  /**
   * For particle-lepton scattering, the minimum scattering angle of
   * the lepton.
   */
  inline double DISLepton2AngleMin() const;

  /**
   * For particle-lepton scattering, the maximum scattering angle of
   * the lepton.
   */
  inline double DISLepton2AngleMax() const;

  /**
   * Minimum \f$Q^2\f$. For particle-lepton scattering, the minimum
   * \f$Q^2\f$ as calculated from the scattered lepton.
   */
  inline Energy2 DISQ22Min() const;

  /**
   * Maximum \f$Q^2\f$. For particle-lepton scattering, the maximum
   * \f$Q^2\f$ as calculated from the scattered lepton.
   */
  inline Energy2 DISQ22Max() const;

  /**
   * Minimum \f$W^2\f$. For lepton-particle, particle-lepton and
   * lepton-lepton scattering, the minimum value of the invariant mass
   * squared of the outgoing particles when removing the scattered
   * lepton(s).
   */
  inline Energy2 DISW2Min() const;

  /**
   * Maximum \f$W^2\f$. For lepton-particle, particle-lepton and
   * lepton-lepton scattering, the maximum value of the invariant mass
   * squared of the outgoing particles when removing the scattered
   * lepton(s).
   */
  inline Energy2 DISW2Max() const;

  /**
   * These functions return true if the given variable passes the
   * cuts.
   */
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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /** @name Cut functions to be overridden by sub-classes. */
  //@{
  /**
   * This method is called by the cut(const SubProcess &) method with
   * the primary SubProcess provided in its cm frame. This base-class
   * method does nothing.
   */
  virtual void newcut(const SubProcess &) const ThePEG_THROW_SPEC((Veto));

  /**
   * This method is called by the cut(const Collision &, const
   * LorentzRotation &) method with the primary collision after its
   * first step provided in int cm frame. The LorentzRotation provided
   * should give the transformation to the laboratory frame. This
   * base-class method does nothing.
   */
  virtual void newcut(const Collision &, const LorentzRotation &) const
    ThePEG_THROW_SPEC((Veto));
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  virtual void doupdate() throw(UpdateException);

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

  //@}

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
   * Return true if \a p is a lepton.
   */
  bool isLepton(const Particle & p) const;

  /**
   * Utility function for the interface.
   */
  double maxYMinMax() const;

  /**
   * Utility function for the interface.
   */
  double minYMaxMin() const;

  /**
   * Utility function for the interface.
   */
  double maxEtaMinMax() const;

  /**
   * Utility function for the interface.
   */
  double minEtaMaxMin() const;

  /**
   * Utility function for the interface.
   */
  double maxCTMinMax() const;

  /**
   * Utility function for the interface.
   */
  double minCTMaxMin() const;

private:

  /**
   * The minimum value of the invariant mass of the hard sub-process.
   */
  Energy theMHatMin;

  /**
   * The maximum value of the invariant mass of the hard sub-process.
   */
  Energy theMHatMax;

  /**
   * The minimum value of the transverse momentum of the outgoing
   * particles in the hard sub-process.
   */
  Energy thePTHatMin;
  /**
   * The maximum value of the transverse momentum of the outgoing
   * particles in the hard sub-process.
   */
  Energy thePTHatMax;

  /**
   * Additional cut on the transverse momenta of the hard sub-process
   * for s-channel hard sub-processes for outgoing particles of mass
   * less than theSingularMassMax.
   */
  Energy thePTHatSingularMin;

  /**
   * The maximum particle mass for the additional thePTHatSingularMin
   * cut.
   */
  Energy theSingularMassMax;

  /**
   * The minimum value of the rapidity of the hard scattering
   * sub-system.
   */
  double theYStarMin;

  /**
   * The maximum value of the rapidity of the hard scattering
   * sub-system.
   */
  double theYStarMax;

  /**
   * The minimum value of the maximum rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMaxYMin;

  /**
   * The maximum value of the maximum rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMaxYMax;

  /**
   * The minimum value of the minimum rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMinYMin;

  /**
   * The maximum value of the minimum rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMinYMax;

  /**
   * The minimum value of the maximum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMaxEtaMin;

  /**
   * The maximum value of the maximum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMaxEtaMax;

  /**
   * The minimum value of the minimum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMinEtaMin;

  /**
   * The maximum value of the minimum pseudo rapidity of the outgoing
   * particles in the hard scattering.
   */
  double theMinEtaMax;

  /**
   * The minimum value of the maximum cos(theta) of
   * the outgoing particles in the hard scattering.
   */
  double theMaxCTMin;

  /**
   * The maximum value of the maximum cos(theta) of
   * the outgoing particles in the hard scattering.
   */
  double theMaxCTMax;

  /**
   * The minimum value of the minimum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  double theMinCTMin;

  /**
   * The maximum value of the minimum cos(theta) of the outgoing
   * particles in the hard scattering.
   */
  double theMinCTMax;

  /**
   * The minimum value of the Bjorken-x of the particle comin into the
   * hard scattering along the positive z-axis.
   */
  double theX1Min;

  /**
   * The maximum value of the Bjorken-x of the particle comin into the
   * hard scattering along the positive z-axis.
   */
  double theX1Max;

  /**
   * The minimum value of the Bjorken-x of the particle
   * comin into the hard scattering along the negative z-axis.
   */
  double theX2Min;

  /**
   * The maximum value of the Bjorken-x of the particle
   * comin into the hard scattering along the negative z-axis.
   */
  double theX2Max;

  /**
   * The minimum value of the Feynman-x of the hard scattering.
   */
  double theXFMin;

  /**
   * The maximum value of the Feynman-x of the hard scattering.
   */
  double theXFMax;

  /**
   * The minimum value of cosine of the scattering angle in the
   * restframe of a hard \f$2\rightarrow 2\f$ scattering.
   */
  double theCTHMin;

  /**
   * The maximum value of cosine of the scattering angle in the
   * restframe of a hard \f$2\rightarrow 2\f$ scattering.
   */
  double theCTHMax;

  /**
   * The minimum value of \f$\hat{t}\f$ of a hard \f$2\rightarrow 2\f$
   * scattering.
   */
  Energy2 theTHatMin;

  /**
   * The maximum value of \f$\hat{t}\f$ of a hard \f$2\rightarrow 2\f$
   * scattering.
   */
  Energy2 theTHatMax;

  /**
   * The minimum value of \f$|\hat{u}|\f$ of a hard \f$2\rightarrow 2\f$
   * scattering.
   */
  Energy2 theUHatMin;

  /**
   * The maximum value of \f$|\hat{u}|\f$ of a hard \f$2\rightarrow 2\f$
   * scattering.
   */
  Energy2 theUHatMax;

  /**
   * The minimum value of the scale in a hard scattering as defined by
   * the Handlers which performed the hard scattering.
   */
  Energy2 theScaleMin;

  /**
   * The maximum value of the scale in a hard scattering as defined by
   * the Handlers which performed the hard scattering.
   */
  Energy2 theScaleMax;

  /**
   * Internal flag to indicate if we should use cuts on scattered
   * leptons.
   */
  bool useLeptoCuts;

  /**
   * For lepton-particle scattering, the minimum energy of the
   * scattered lepton.
   */
  Energy theDISLepton1EnergyMin;

  /**
   * For lepton-particle scattering, the maximum energy of the
   * scattered lepton.
   */
  Energy theDISLepton1EnergyMax;

  /**
   * For lepton-particle scattering, the minimum scattering angle of
   * the lepton.
   */
  double theDISLepton1AngleMin;

  /**
   * For lepton-particle scattering, the maximum scattering angle of
   * the lepton.
   */
  double theDISLepton1AngleMax;

  /**
   * For lepton-particle scattering, the minimum \f$Q^2\f$ as calculated
   * from the scattered lepton.
   */
  Energy2 theDISQ21Min;

  /**
   * For lepton-particle scattering, the maximum \f$Q^2\f$ as calculated
   * from the scattered lepton.
   */
  Energy2 theDISQ21Max;

  /**
   * For particle-lepton scattering, the minimum energy of the
   * scattered lepton.
   */
  Energy theDISLepton2EnergyMin;

  /**
   * For particle-lepton scattering, the maximum energy of the
   * scattered lepton.
   */
  Energy theDISLepton2EnergyMax;

  /**
   * For particle-lepton scattering, the minimum scattering angle of
   * the lepton.
   */
  double theDISLepton2AngleMin;

  /**
   * For particle-lepton scattering, the maximum scattering angle of
   * the lepton.
   */
  double theDISLepton2AngleMax;

  /**
   * For particle-lepton scattering, the minimum \f$Q^2\f$ as
   * calculated from the scattered lepton.
   */
  Energy2 theDISQ22Min;

  /**
   * For particle-lepton scattering, the maximum \f$Q^2\f$ as
   * calculated from the scattered lepton.
   */
  Energy2 theDISQ22Max;

  /**
   * For lepton-particle, particle-lepton and lepton-lepton
   * scattering, the minimumvalue of the invariant mass squared of the
   * outgoing particles when removing the scattered lepton(s).
   */
  Energy2 theDISW2Min;

  /**
   * For lepton-particle, particle-lepton and lepton-lepton
   * scattering, the maximum value of the invariant mass squared of
   * the outgoing particles when removing the scattered lepton(s).
   */
  Energy2 theDISW2Max;

  /**
   * A matcher object used to identify leptons.
   */
  Ptr<MatchLepton>::pointer theLeptonMatcher;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<KinematicalCuts> initKinematicalCuts;

  /**
   *  Private and non-existent assignment operator.
   */
  KinematicalCuts & operator=(const KinematicalCuts &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of KinematicalCuts.
 */
template <>
struct BaseClassTrait<KinematicalCuts,1>: public ClassTraitsType {
  /** Typedef of the base class of KinematicalCuts. */
  typedef Interfaced NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * KinematicalCuts class.
 */
template <>
struct ClassTraits<KinematicalCuts>:
    public ClassTraitsBase<KinematicalCuts> {
  /** Return the class name. */
  static string className() { return "ThePEG::KinematicalCuts"; }
};

}

#include "KinematicalCuts.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KinematicalCuts.tcc"
#endif

#endif /* ThePEG_KinematicalCuts_H */
