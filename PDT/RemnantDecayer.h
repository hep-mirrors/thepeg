// -*- C++ -*-
#ifndef THEPEG_RemnantDecayer_H
#define THEPEG_RemnantDecayer_H
//
// This is the declaration of the RemnantDecayer class.
//

#include "ThePEG/PDT/Decayer.h"
#include "RemnantDecayer.fh"
#include "ThePEG/PDT/RemnantData.fh"
#include "ThePEG/EventRecord/RemnantParticle.h"

namespace ThePEG {

/**
 * Here is the documentation of the RemnantDecayer class.
 *
 * @see \ref RemnantDecayerInterfaces "The interfaces"
 * defined for RemnantDecayer.
 */
class RemnantDecayer: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline RemnantDecayer();

  /**
   * The copy constructor.
   */
  inline RemnantDecayer(const RemnantDecayer &);

  /**
   * The destructor.
   */
  virtual ~RemnantDecayer();
  //@}

public:

  /** @name Virtual functions required by the Decayer class. */
  //@{
  /**
   * Check if this decayer can perfom the decay specified by the
   * given decay mode.
   * @param dm the DecayMode describing the decay.
   * @return true if this decayer can handle the given mode, otherwise false.
   */
  virtual bool accept(const DecayMode & dm) const;

  /**
   * Return true if this Decayer need to access the full current step
   * when a particle is decayed. If true is returned the standard
   * Decay Handler will call the decay(const DecayMode&,const
   * Particle&,Step&) function rather than the decay(const
   * DecayMode&,const Particle&) function.
   */
  virtual bool needsFullStep() const;

  /**
   * Perform a decay for a given DecayMode and a given Particle
   * instance. This version allows the decaying particle to borrow
   * energy/momentum from its sublings in the current step. This will
   * be called by the standard DecayHandler if the needsFullStep()
   * function returns true.
   *
   * @param dm   the DecayMode describing the decay.
   * @param p    the Particle instance to be decayed.
   * @param step the current step in which to find possible siblings to
   *             shuffle energy with.
   * @return a ParticleVector containing the decay products.
   */
  virtual ParticleVector decay(const DecayMode & dm, const Particle & p,
			       Step & step) const;

  /**
   * Perform a decay for a given DecayMode and a given Particle instance.
   * @param dm the DecayMode describing the decay.
   * @param p the Particle instance to be decayed.
   * @return a ParticleVector containing the decay products.
   */
  virtual ParticleVector decay(const DecayMode & dm, const Particle & p) const;
  //@}

  /**
   * Return true if this decayer can handle the extraction of the \a
   * extracted partons from the given \a particle.
   */
  virtual bool canHandle(tcPDPtr parent,
			 const multiset<tcPDPtr> & extracted) const;

protected:

  /**
   * Access the RemnantData object of a \a remnant.
   */
  inline tRemPDPtr data(tcRemPPtr remnant) const;

  /**
   * Access the parent  of a \a remnant.
   */
  inline tPPtr parent(tcRemPPtr remnant) const;

  /**
   * Access the vector of extracted particles of a \a remnant.
   */
  inline const PVector & extracted(tcRemPPtr remnant) const;

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


// If needed, insert declarations of virtual function defined in the
// InterfacedBase class here (using ThePEG-interfaced-decl in Emacs).


private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<RemnantDecayer> initRemnantDecayer;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  RemnantDecayer & operator=(const RemnantDecayer &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of RemnantDecayer. */
template <>
struct BaseClassTrait<RemnantDecayer,1> {
  /** Typedef of the first base class of RemnantDecayer. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the RemnantDecayer class and the shared object where it is defined. */
template <>
struct ClassTraits<RemnantDecayer>
  : public ClassTraitsBase<RemnantDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::RemnantDecayer"; }
};

/** @endcond */

}

#include "RemnantDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantDecayer.tcc"
#endif

#endif /* THEPEG_RemnantDecayer_H */
