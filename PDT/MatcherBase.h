// -*- C++ -*-
#ifndef ThePEG_MatcherBase_H
#define ThePEG_MatcherBase_H
//
// This is the declaration of the <!id>MatcherBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>MatcherBase<!!id> is an abstract base class to be used for
// objects representing groups of <!class>ParticleData<!!class>
// objects. Concrete implementations will typically use the templated
// <!class>Matcher<!!class> class for easy building of a full
// sub-class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:Matcher.html">Matcher.h</a>.
// 


#include "ParticleData.h"
#include "ThePEG/EventRecord/Particle.h"

namespace ThePEG {

class MatcherBase: public Interfaced {

public:

  friend class Repository;

public:

  MatcherBase();
  MatcherBase(const MatcherBase &);
  inline virtual ~MatcherBase();
  // Standard ctors and dtor

public:

  virtual bool check(const ParticleData &) const = 0;
  inline bool checkp(const Particle &) const;
  // Check if a particle meets the criteria.

  inline bool matches(const ParticleData &) const;
  inline bool matches(const Particle &) const;
  // Check if a given particle belongs to the set of matches
  
  inline bool matches(const MatcherBase &) const;
  // Check if a particle matcher belongs to the set of matches.

  inline const ParticleDataSet & particles() const;
  inline const MatcherSet & matchers() const;
  // Access to the sets of matching particle and matchers.

  inline double minMass() const;
  inline double maxMass() const;
  // Returns the minimum and maximum mass of the matching
  // particles.

  inline double mass() const;
  // Returns the common mass of the matching particles. If all matching
  // particles do not have exactly the same mass -1.0 is returned.

  inline double width() const;
  // Returns the common width of the matching particles. If all matching
  // particles do not have exactly the same width -1.0 is returned.

  inline double cTau() const;
  // Returns the common decay length of the matching particles. If all
  // matching particles do not have exactly the same decay length -1.0
  // is returned.

  inline PDT::Charge iCharge() const;
  inline bool charged() const;
  inline bool positive() const;
  inline bool negative() const;
  // If all matching particles have the same charge the common charge
  // is returned. Otherwise if all are positive (negative),
  // PDT::Cpositive (PDT::Cnegative) is returned. Otherwise if
  // all are charged, PDT::Ccharged is returned. Otherwise
  // PDT::Cundefined is returned.

  inline PDT::Spin iSpin() const;
  // If all matching particles have the same spin the common spin is
  // returned. Otherwise HepPDT::Sundefined is returned.

  inline PDT::Color iColor() const;
  inline bool colored() const;
  // If all matching particles have the same color the common color is
  // returned. Otherwise if all are colored, PDT::colcolored is
  // returned. Otherwise HepPDT::colundefined is returned.

  inline int stable() const;
  // Returns (0)1 if all matching particles are (un)stable. Otherwise
  // -1 is returned.

  inline tPMPtr CC() const;
  // Get the matcher object matching the antiparticles of this. If
  // no-one exists 0 is returned.

  void rebind(TranslationMap & trans) throw(RebindException);

public:

  virtual PMPtr pmclone() const = 0;
  // Specialized clone method for matcher.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

protected:

  void addPIfMatch(tPDPtr);
  void addMIfMatch(tPMPtr);
  template <typename Iterator>
  inline void addPIfMatch(Iterator, Iterator);
  template <typename Cont>
  inline void addPIfMatchFrom(const Cont &);
  template <typename Iterator>
  inline void addMIfMatch(Iterator, Iterator);
  template <typename Cont>
  inline void addMIfMatchFrom(const Cont &);
  // Add a (number of) particle or a particle matcher id to the set of matching
  // particles if it meets the criteria.

  void clear();
  // Clear information about matching particles and matchers.

  inline void setCC(tPMPtr, tPMPtr) const;
  // Set antipartner.

private:

  ParticleDataSet matchingParticles;
  // The set of particle data objects matched by this matcher.

  MatcherSet matchingMatchers;
  // A set of matchers which matches a subset of this matcher.

  Energy theMaxMass;
  Energy theMinMass;
  Energy commonMass;
  Energy commonWidth;
  Length commonCTau;
  PDT::Charge commonCharge;
  PDT::Spin commonSpin;
  PDT::Color commonColor;
  int commonStable;
  // Variables containing common properties of all matched
  // particles. All are set to a sensible 'undefined' value if the
  // properties differs between the matched particles.

  tPMPtr theAntiPartner;
  // Pointer to a matcher object which matches all anti particles
  // which are matched by this matcher.

private:

  static AbstractClassDescription<MatcherBase> initMatcherBase;

  MatcherBase & operator=(const MatcherBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<MatcherBase,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<MatcherBase>:
    public ClassTraitsBase<MatcherBase> {
  static string className() { return "/ThePEG/MatcherBase"; }
};

}

#include "MatcherBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MatcherBase.tcc"
#endif

#endif /* ThePEG_MatcherBase_H */
