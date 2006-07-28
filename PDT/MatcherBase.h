// -*- C++ -*-
#ifndef ThePEG_MatcherBase_H
#define ThePEG_MatcherBase_H
// This is the declaration of the MatcherBase class.


#include "ParticleData.h"
#include "ThePEG/EventRecord/Particle.h"

namespace ThePEG {

/**
 * MatcherBase is an abstract base class to be used for objects
 * representing groups of ParticleData objects. Concrete
 * implementations will typically use the templated Matcher class for
 * easy building of a full sub-class.
 *
 * @see ParticleData
 * @see Matcher
 * 
 */
class MatcherBase: public Interfaced {

public:

  /** Repository needs to be a friend. */
  friend class Repository;

  /**
   * Convenient typedef.
   */
  typedef set<tPDPtr> tPDSet;

  /**
   * Convenient typedef.
   */
  typedef set<tPMPtr> tPMSet;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  MatcherBase();

  /**
   * Copy-constructor.
   */
  MatcherBase(const MatcherBase &);

  /**
   * Destructor.
   */
  virtual ~MatcherBase();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Check if a particle type meets the criteria.
   */
  virtual bool check(const ParticleData &) const = 0;

  /**
   * Specialized clone method for MatcherBase used by the
   * Repository. A sub class must make sure that also the MatcherBase
   * object corresponding to the complex conjugate of this is cloned.
   */
  virtual PMPtr pmclone() const = 0;
  //@}

  /** @name Check if something is matched. */
  //@{
  /**
   * Check if a Particle meets the criteria.
   */
  inline bool checkp(const Particle &) const;

  /**
   * Check if a given particle type belongs to the set of
   * matches. This function looks for the same ParticleData object in
   * the set of all particles matched by this matcher. May be quicker
   * than to go through the check proceedure.
   */
  inline bool matches(const ParticleData &) const;

  /**
   * Check if a given particle belongs to the set of matches. This
   * function looks for the corresponding ParticleData object in the
   * set of all particles matched by this matcher. May be quicker than
   * to go through the check proceedure.
   */
  inline bool matches(const Particle &) const;
  
  /**
   * Check if a given particle matcher belongs to the set of
   * matches. This function looks for the same MatcherBase object in
   * the set of all matchers matched by this matcher.
   */
  inline bool matches(const MatcherBase &) const;
  //@}

  /** @name Access the sets of matching particles and matchers. */
  //@{
  /**
   * Access to the set of matching particles.
   */
  inline const tPDSet & particles() const;
  /**
   * Access to the set of matching matchers.
   */
  inline const tPMSet & matchers() const;
  //@}

  /** @name Access common properties of all matched particles. */
  //@{
  /**
   * Returns the minimum mass of the matching particles.
   */
  inline Energy minMass() const;

  /**
   * Returns the maximum mass of the matching particles.
   */
  inline Energy maxMass() const;

  /**
   * Returns the common mass of the matching particles. If all matching
   * particles do not have exactly the same mass, -1.0 GeV is returned.
   */
  inline Energy mass() const;

  /**
   * Returns the common width of the matching particles. If all matching
   * particles do not have exactly the same width, -1.0 GeV is returned.
   */
  inline Energy width() const;

  /**
   * Returns the common decay length of the matching particles. If all
   * matching particles do not have exactly the same decay length -1.0
   * mm is returned.
   */
  inline Length cTau() const;

  /**
   * Return common charge. If all matching particles have the same
   * charge the common charge is returned. Otherwise if all are
   * positive (negative), PDT::Positive (PDT::Negative) is
   * returned. Otherwise if all are charged, PDT::Charged is
   * returned. Otherwise PDT::ChargeUndefined is returned.
   */
  inline PDT::Charge iCharge() const;

  /**
   * Are the particles charged? If all matching particles are charged, return
   * true, otherwise false.
   */
  inline bool charged() const;

  /**
   * Are the particles positively charged? If all matching particles
   * are positively charged, return true, otherwise false.
   */
  inline bool positive() const;

  /**
   * Are the particles negatively charged? If all matching particles
   * are negatively charged, return true, otherwise false.
   */
  inline bool negative() const;

  /**
   * Return common spin. If all matching particles have the same spin,
   * the common spin is returned. Otherwise PDT::SpinUndefined is
   * returned.
   */
  inline PDT::Spin iSpin() const;

  /**
   * If all matching particles have the same color, the common color
   * is returned. Otherwise if all are colored, PDT::Coloured is
   * returned. Otherwise PDT::ColourUndefined is returned.
   */
  inline PDT::Color iColor() const;

  /**
   * Are the particles coloured? If all matching particles are
   * coloured, return true, otherwise false.
   */
  inline bool colored() const;

  /**
   * Are the particles stable? Returns (0)1 if all matching particles
   * are (un)stable. Otherwise -1 is returned.
   */
  inline int stable() const;
  //@}

  /**
   * Get the matcher object matching the antiparticles of this. If
   * no-one exists null is returned.
   */
  inline tPMPtr CC() const;

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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  virtual void doupdate() throw(UpdateException);

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

  //@}

protected:

  /**
   * Add a particle to the set of matching particles if it meets the
   * criteria.
   */
  void addPIfMatch(tPDPtr);

  /**
   * Add a particle matcher to the set of matching matchers if it
   * meets the criteria.
   */
  void addMIfMatch(tPMPtr);

  /**
   * Add a number of particles to the set of matching particles if
   * they meets the criteria.
   */
  template <typename Iterator>
  inline void addPIfMatch(Iterator, Iterator);

  /**
   * Add a number of particles to the set of matching particles if
   * they meets the criteria.
   */
  template <typename Cont>
  inline void addPIfMatchFrom(const Cont &);

  /**
   * Add a number of particle matchers to the set of matching
   * matchers if they meets the criteria.
   */
  template <typename Iterator>
  inline void addMIfMatch(Iterator, Iterator);

  /**
   * Add a number of particle matchers to the set of matching
   * matchers if they meets the criteria.
   */
  template <typename Cont>
  inline void addMIfMatchFrom(const Cont &);

  /**
   * Clear information about matching particles and matchers.
   */
  void clear();

  /**
   * Set antipartner.
   */
  inline void setCC(tPMPtr, tPMPtr) const;

private:

  /**
   * The set of particle data objects matched by this matcher.
   */
  tPDSet matchingParticles;

  /**
   * A set of matchers which matches a subset of this matcher.
   */
  tPMSet matchingMatchers;

  /**
   * The maximum mass of all matching particles.
   */
  Energy theMaxMass;

  /**
   * The minimum mass of all matching particles.
   */
  Energy theMinMass;

  /**
   * The common mass of all matching particles.
   */
  Energy commonMass;

  /**
   * The common width of all matching particles.
   */
  Energy commonWidth;

  /**
   * The common decay length of all matching particles.
   */
  Length commonCTau;

  /**
   * The common charge of all matching particles.
   */
  PDT::Charge commonCharge;

  /**
   * The common spin of all matching particles.
   */
  PDT::Spin commonSpin;

  /**
   * The common colour of all matching particles.
   */
  PDT::Color commonColor;

  /**
   * The common stability of all matching particles.
   */
  int commonStable;

  /**
   * Pointer to a matcher object which matches all anti particles
   * which are matched by this matcher.
   */
  tPMPtr theAntiPartner;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class with persistent data.
   */
  static AbstractClassDescription<MatcherBase> initMatcherBase;

  /**
   *  Private and non-existent assignment operator.
   */
  MatcherBase & operator=(const MatcherBase &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of MatcherBase. */
template <>
struct BaseClassTrait<MatcherBase,1>: public ClassTraitsType {
  /** Typedef of the first base class of MatcherBase. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  MatcherBase class. */
template <>
struct ClassTraits<MatcherBase>:
    public ClassTraitsBase<MatcherBase> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MatcherBase"; }
};

/** @endcond */

}

#include "MatcherBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MatcherBase.tcc"
#endif

#endif /* ThePEG_MatcherBase_H */
