// -*- C++ -*-
//
#ifndef ThePEG_DecayMode_H
#define ThePEG_DecayMode_H
//
// This is the declaration of the <!id>DecayMode<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>DecayMode<!!id> describes a decay channel of a
// particle. In its simplest form it contains simply a parent
// <!class>ParticleData<!!class> object and a list of decay products,
// but it can also specify a set of <!class>MatcherBase<!!class>
// objects each representing one of a set of possible decay
// products. A matcher can also be specified to represents an
// unlimited set of decay products. Decay chains can be represented by
// specifying other decay channels where the parents are taken to be
// intermediate resonances. It is also possible to specify the absence
// of intermediate resonances.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:MatcherBase.html">MatcherBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Interface/Interfaced.h"
#include "DecayMode.fh"
#include "MatcherBase.h"
#include "Decayer.h"

namespace ThePEG {

ThePEG_DECLARE_MULTISET(tPDPtr,ParticleMSet);
ThePEG_DECLARE_MULTISET(tPMPtr,MatcherMSet);
ThePEG_DECLARE_MULTISET(tDMPtr,ModeMSet);

class DecayMode: public Interfaced {

public:

  friend class ParticleData;

public:

  typedef vector<tcDMPtr> ModeVector;

public:

  static DMPtr constructDecayMode(string & tag);
  // Create a decay mode from a given tag.

  DecayMode();
  DecayMode(const DecayMode &);
  inline ~DecayMode();
  // Standard ctors and dtor

  virtual DMPtr clone(tPDPtr pd) const;
  // Return a clone of this decay mode with *pd as decaying particle.

public:

  inline string tag() const;
  // Return the tag for this decay mode.

  inline tcPDPtr parent() const;
  // Get a pointer to the particle data object corresponding to
  // the decaying particle.

  inline const ParticleMSet & products() const;
  // The set of identified decay products.

  inline const ModeMSet & cascadeProducts() const;
  // The set of identified resonant products with specified decay
  // modes

  inline const MatcherMSet & productMatchers() const;
  // The set of matchers each corresponding to one decay product.

  inline tPMPtr wildProductMatcher() const;
  // The pointer to a matcher corresponding to any number of decay
  // products

  inline const ParticleMSet & excluded() const;
  // The set particles corresponding to excluded intermediate
  // resonances.

  double brat() const;
  // Return the bRatio branching ratio to be used.

  double brat(const Particle &) const;
  // Calculate the branching ratio for a particular particle instance.

  inline tDecayerPtr decayer() const;
  // Get the decayer. The set method returns false if the decayer
  // does not claim to be able to handle the decay.

  bool includes(const DecayMode &) const;
  // Check if another decay mode is included in this one.

  inline tDMPtr CC() const;
  // Return a pointer to the corresponding decaymode for the
  // antiparticle decay.

  inline bool operator == (const DecayMode &) const;
  // Check if another decay mode has the same final state as this
  // one.

  inline const ModeVector & overlap() const;
  // Return the list of overlapping decay modes.

  void synchronize();
  // Modify this mode to have properties corresponding to its anti-partner.

public:

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

  inline void parent(tPDPtr);
  // Set a pointer to the particle data object corresponding to
  // the decaying particle.

  void brat(double);
  // Set the bRatio branching ratio to be used.

  void switchOn();
  void switchOff();
  // Switch on/off this decay mode.

  void decayer(tDecayerPtr);
  // Set the decayer. The set method returns false if the decayer
  // does not claim to be able to handle the decay.

  void addProduct(tPDPtr);
  // Add identified decay products.

  void addCascadeProduct(tDMPtr);
  // Add identified resonant product with specified decay mode.

  void addProductMatcher(tPMPtr);
  // Add a mathcer corresponding to one decay product.

  void setWildMatcher(tPMPtr);
  // Add a matcher corresponding to any number of decay products.

  void addExcluded(tPDPtr);
  // Add a particle corresponding to an excluded intermediate
  // resonance.

  static DMPtr Create(tPDPtr newParent, double newBrat = 0.0,
		      bool newOn = false);
  DecayMode(tPDPtr newParticle, double newBrat, bool newOn);
  virtual IBPtr fullclone() const;
  virtual IBPtr clone() const;
  DMPtr dmclone() const;
  // Protected creation and clone methods.

  virtual void readSetup(istream & is) throw(SetupException);
  // Read setup info from a standard stream.

  virtual void rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

  inline ParticleMSet & products();
  // The set of identified decay products.

  inline ModeMSet & cascadeProducts();
  // The set of identified resonant products with specified decay
  // modes

  inline MatcherMSet & productMatchers();
  // The set of matchers each corresponding to one decay product.

  inline tPMPtr & wildProductMatcher();
  // The pointer to a matcher corresponding to any number of decay
  // products

  inline ParticleMSet & excluded();
  // The set particles corresponding to excluded intermediate
  // resonances.

private:

  bool addOverlap(tcDMPtr);
  // Add a decay mode to the list of overlapping modes if included.

  void resetOverlap();
  // Remove all decay modes from the list of overlapping modes.

  bool compareId(const ParticleMSet &, const ParticleMSet &) const;
  // Check if two sets of particles have equivalent types.

  ParticleMSet::const_iterator findId(const ParticleMSet &,
				      const ParticleData &) const;
  // Check if a particle set contains a given particle ID.
  
  string makeTag() const;
  // Use the members in this decay channel and generate the
  // corresponding tag.

  void resetTag();
  // Delete the tag (it will be regenerated later if asked for).

private:

  void setOn(long);
  long getOn() const;
  void setDecayer(DecayerPtr);
  // Utility functions for the interface.

private:

  mutable string theTag;
  // The tag.

  double theBrat;
  // The branching ratio.

  bool isOn;
  // True if this mode is switched on.

  tPDPtr theParent;
  // Pointer to a particle data object corresponding to the decaying
  // particle.

  ParticleMSet theProducts;
  // The set of specified decay particles.

  ModeMSet theCascadeProducts;
  // The set of matching decay channels corresponding to a specified
  // with a specified subsequent decay mode.

  MatcherMSet theMatchers;
  // The set of matching decay products. Each of the matchers
  // correspond to one particle.

  tPMPtr theWildMatcher;
  // A particle matcher which corresponds to zero or more particles.

  ParticleMSet theExcluded;
  // A set of particles which are not allowed as intermediate
  // resonances.

  ModeVector theOverlap;
  // A list of decay modes which are included in this one.

  DecayerPtr theDecayer;
  // The decayer object responsible for performing the decay.

  tDMPtr theAntiPartner;

private:

  static ClassDescription<DecayMode> initDecayMode;

  DecayMode & operator=(const DecayMode &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<DecayMode,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<DecayMode>:
    public ClassTraitsBase<DecayMode> {
  static string className() { return "/ThePEG/DecayMode"; }
};

}

#include "DecayMode.icc"

#endif /* ThePEG_DecayMode_H */
