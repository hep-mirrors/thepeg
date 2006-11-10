// -*- C++ -*-
#ifndef THEPEG_SimpleBaryonRemnantDecayer_H
#define THEPEG_SimpleBaryonRemnantDecayer_H
//
// This is the declaration of the SimpleBaryonRemnantDecayer class.
//

#include "ThePEG/PDT/RemnantDecayer.h"

namespace ThePEG {

/**
 * The SimpleBaryonRemnantDecayer class inherits from the
 * RemnantDecayer class and is able to decay RemnantParticles produced
 * by the SoftRemnantHandler class for the cases when a single parton
 * has been extracted from a baryon.
 *
 * @see \ref SimpleBaryonRemnantDecayerInterfaces "The interfaces"
 * defined for SimpleBaryonRemnantDecayer.
 */
class SimpleBaryonRemnantDecayer: public RemnantDecayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline SimpleBaryonRemnantDecayer();

  /**
   * The copy constructor.
   */
  inline SimpleBaryonRemnantDecayer(const SimpleBaryonRemnantDecayer &);

  /**
   * The destructor.
   */
  virtual ~SimpleBaryonRemnantDecayer();
  //@}

public:

  /** @name Virtual functions required by the RemnantDecayer class. */
  //@{
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
   * Return true if this decayer can handle the extraction of the \a
   * extracted parton from the given \a particle.
   */
  virtual bool canHandle(tcPDPtr parent, tcPDPtr extracted) const;
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


private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<SimpleBaryonRemnantDecayer>
  initSimpleBaryonRemnantDecayer;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  SimpleBaryonRemnantDecayer & operator=(const SimpleBaryonRemnantDecayer &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of SimpleBaryonRemnantDecayer. */
template <>
struct BaseClassTrait<SimpleBaryonRemnantDecayer,1> {
  /** Typedef of the first base class of SimpleBaryonRemnantDecayer. */
  typedef RemnantDecayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  SimpleBaryonRemnantDecayer class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<SimpleBaryonRemnantDecayer>
  : public ClassTraitsBase<SimpleBaryonRemnantDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::SimpleBaryonRemnantDecayer"; }
};

/** @endcond */

}

#include "SimpleBaryonRemnantDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleBaryonRemnantDecayer.tcc"
#endif

#endif /* THEPEG_SimpleBaryonRemnantDecayer_H */
