// -*- C++ -*-
#ifndef ThePEG_StandardModelBase_H
#define ThePEG_StandardModelBase_H
// This is the declaration of the StandardModelBase class.

#include "ThePEG/Config/ThePEG.h"
#include "AlphaEMBase.h"
#include "CKMBase.h"
#include "AlphaSBase.h"
// #include "StandardModelBase.fh"
// #include "StandardModelBase.xh"

namespace ThePEG {

/**
 * StandardModelBase is used to handle standard model parameters in an
 * EventGenerator. It uses AlphaEMBase, AlphaSBase and CKMBase to help
 * with the implementation of the electro-magnetic and QCD couplings
 * and the flavour mixing matrix. This means that StandardModelBase
 * does not need to be inherited from when it comes to standard model
 * parameters. Beyond the standard model parameters should be
 * implemented as sub-classes.
 *
 * @see \ref StandardModelBaseInterfaces "The interfaces"
 * defined for StandardModelBase.
 * @see EventGenerator
 * @see AlphaEMBase
 * @see AlphaSBase
 * @see CKMBase
 */
class StandardModelBase: public Interfaced {

  /** Declare a pointer to an AlphaEMBase object. */
  typedef Ptr<AlphaEMBase>::pointer AEMPtr;
  /** Declare a pointer to an AlphaSBase object. */
  typedef Ptr<AlphaSBase>::pointer ASPtr;
  /** Declare a pointer to n CKMBase object. */
  typedef Ptr<CKMBase>::pointer CKMPtr;
  /** Declare a transient pointer to an AlphaEMBase object. */
  typedef Ptr<AlphaEMBase>::transient_pointer tAEMPtr;
  /** Declare a transient pointer to an AlphaSBase object. */
  typedef Ptr<AlphaSBase>::transient_pointer tASPtr;
  /** Declare a transient pointer to a CKMBase object. */
  typedef Ptr<CKMBase>::transient_pointer tCKMPtr;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  StandardModelBase();

  /**
   * Copy-constructor.
   */
  StandardModelBase(const StandardModelBase &);

  /**
   * Destructor.
   */
  virtual ~StandardModelBase();
  //@}

public:

  /**
   * Return the number of families assumed in the standard model.
   */
  unsigned int families() const;

public:


  /** @name Functions accessing electro-weak parameters. */
  //@{
  /**
   * Running \f$\alpha_{EM}\f$.
   */
  inline double alphaEM() const;

  /**
   * Constant \f$\alpha_{EM}\f$.
   */
  inline double alphaEM(Energy2 scale) const;

  /**
   * Return a pointer to the object handling \f$\alpha_{EM}\f$.
   */
  inline tAEMPtr alphaEMPtr() const;

  /**
   * Return \f$\sin^2(\theta_W)\f$.
   */
  inline double sin2ThetaW() const;

  /**
   * The neutrino-photon coupling.
   */
  inline double enu() const;

  /**
   * The charged lepton-photon coupling.
   */
  inline double ee() const;

  /**
   * The up-type-photon coupling.
   */
  inline double eu() const;

  /**
   * The down-type-photon coupling.
   */
  inline double ed() const;

  /**
   * The vector neutrino-\f$Z^0\f$ coupling.
   */
  inline double vnu() const;

  /**
   * The vector charged lepton-\f$Z^0\f$ coupling.
   */
  inline double ve() const;

  /**
   * The vector up-type-\f$Z^0\f$ coupling.
   */
  inline double vu() const;

  /**
   * The vector down-type-\f$Z^0\f$ coupling.
   */
  inline double vd() const;

  /**
   * The axial neutrino-\f$Z^0\f$ coupling.
   */
  inline double anu() const;

  /**
   * The axial charged lepton-\f$Z^0\f$ coupling.
   */
  inline double ae() const;

  /**
   * The axial up-type-\f$Z^0\f$ coupling.
   */
  inline double au() const;

  /**
   * The axial down-type-\f$Z^0\f$ coupling.
   */
  inline double ad() const;

  /**
   * Return a pointer to the CKMBase object used.
   */
  inline tCKMPtr CKM() const;

  /**
   * Return a square of the element of the Cabibbo-Kobayashi-Maskawa
   * Matrix. The fatrix element for the \a uf up-type family and \a df
   * down-type family.
   */
  double CKM(unsigned int uf, unsigned int df) const;

  /**
   * Return the square of the elements of the Cabibbo-Kobayashi-Maskawa
   * Matrix.
   */
  double CKM(const ParticleData & uType,
		    const ParticleData & dType) const;
  //@}

public:

  /** @name Functions accessing QCD parameters. */
  //@{
  /**
   * Return the number of colours.
   */
  inline unsigned int Nc() const;

  /**
   * Return the number of avtive quark flavours for a given \a scale.
   */
  inline unsigned int Nf(Energy2 scale) const;

  /**
   * Return the constant strong coupling constant.
   */
  inline double alphaS() const;

  /**
   * Return the running strong coupling for a given \a scale
   */
  inline double alphaS(Energy2 scale) const;

  /**
   * Return a pointer to the object handling \f$\alpha_S\f$.
   */
  inline tASPtr alphaSPtr() const;

  /**
   * Return the \f$\Lambda_{QCD}\f$ for \a nflav active flavours.
   */
  inline Energy LambdaQCD(unsigned int nflav) const;

  /**
   * Return the \f$\Lambda_{QCD}\f$ for the given \a scale.
   */
  inline Energy LambdaQCD(Energy2 scale) const;
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

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
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
  virtual void doinit() throw(InitException);

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
   * The number of families.
   */
  unsigned int theFamilies;

  /**
   * The constant \f$\alpha_{EM}\f$.
   */
  double theAlphaEM;

  /**
   * Pointer to an object capable of calculating the running
   * \f$\alpha_{EM}\f$.
   */
  AEMPtr theRunningAlphaEM;

  /**
   * The \f$\sin^2(\theta_W)\f$
   */
  double theSin2ThetaW;

  /**
   * Coupling between a fundamental fermion and the photon.
   */
  double theEnu;

  /**
   * Coupling between a fundamental fermion and the photon.
   */
  double theEe;

  /**
   * Coupling between a fundamental fermion and the photon.
   */
  double theEu;

  /**
   * Coupling between a fundamental fermion and the photon.
   */
  double theEd;

  /**
   * Vector coupling between a fundamental fermion and Z^0.
   */
  double theVnu;

  /**
   * Vector coupling between a fundamental fermion and Z^0.
   */
  double theVe;

  /**
   * Vector coupling between a fundamental fermion and Z^0.
   */
  double theVu;

  /**
   * Vector coupling between a fundamental fermion and Z^0.
   */
  double theVd;

  /**
   * Axial coupling between a fundamental fermions and Z^0.
   */
  double theAnu;

  /**
   * Axial coupling between a fundamental fermions and Z^0.
   */
  double theAe;

  /**
   * Axial coupling between a fundamental fermions and Z^0.
   */
  double theAu;

  /**
   * Axial coupling between a fundamental fermions and Z^0.
   */
  double theAd;

  /**
   * If true, the electro-weak couplings are derived from
   * \f$\theta_W\f$ in the initialization.
   */
  long recalculateEW;

  /**
   * A pointer to an object representing the Cabibbo-Kobayashi-Maskawa
   * matrix.
   */
  CKMPtr theCKM;

  /**
   * The matrix of squared CKM elements set from theCKM at initialization.
   */
  mutable vector< vector<double> > theCKM2Matrix;

  /**
   * The number of colours;
   */
  unsigned int theNc;

  /**
   * The fixed strong coupling.
   */
  double theAlphaS;

  /**
   * Pointer to an object capable of calculating the running
   * \f$\alpha_{S}\f$.
   */
  ASPtr theRunningAlphaS;


private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<StandardModelBase> initStandardModelBase;

  /**
   *  Private and non-existent assignment operator.
   */
  StandardModelBase & operator=(const StandardModelBase &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of StandardModelBase. */
template <>
struct BaseClassTrait<StandardModelBase,1>: public ClassTraitsType {
  /** Typedef of the first base class of StandardModelBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  StandardModelBase class. */
template <>
struct ClassTraits<StandardModelBase>:
    public ClassTraitsBase<StandardModelBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::StandardModelBase"; }
};

/** @endcond */

}

#include "StandardModelBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardModelBase.tcc"
#endif

#endif /* ThePEG_StandardModelBase_H */
