// -*- C++ -*-
#ifndef ThePEG_FlatDecayer_H
#define ThePEG_FlatDecayer_H
// This is the declaration of the FlatDecayer class.

#include "ThePEG/PDT/Decayer.h"
// #include "FlatDecayer.fh"
// #include "FlatDecayer.xh"

namespace ThePEG {

/**
 * The FlatDecayer class inrerits from the abstract Decayer class and
 * implements the decay of a given Particle to a given set of children
 * according to a flat phase space distribution.
 *
 * It is possible to implement a more complicated decay distribution
 * by inheriting from the FlatDecayer class and only override the
 * virtual function reweight() to return a weight (between zero and
 * one) of a given phase space point relative to the flat
 * distribution.
 *
 * @see \ref FlatDecayerInterfaces "The interfaces"
 * defined for FlatDecayer.
 * @see Decayer
 * @see Particle
 */
class FlatDecayer: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline FlatDecayer();

  /**
   * Copy-constructor.
   */
  inline FlatDecayer(const FlatDecayer &);

  /**
   * Destructor.
   */
  virtual ~FlatDecayer();
  //@}

public:

  /** @name Virtual functions required by the Decayer class.
   */
  //@{
  /**
   * Check if this decayer can perfom the decay specified by the
   * given decay mode.
   * @param dm the DecayMode describing the decay.
   * @return true if this decayer can handle the given mode, otherwise false.
   */
  virtual bool accept(const DecayMode & dm) const;

  /**
   * Perform a decay for a given DecayMode and a given Particle instance.
   * @param dm the DecayMode describing the decay.
   * @param p the Particle instance to be decayed.
   * @return a ParticleVector containing the decay products.
   */
  virtual ParticleVector decay(const DecayMode & dm, const Particle & p) const;

  /**
   * Give a weight to a phase space point. To be overridden by
   * subclasses. For a given decay mode, \a dm, decaying \a parent
   * particle and decayproducts, \a children, distributed according to
   * a flat distribution in phase space, return a weight (less or
   * equal to unity) modifying the flat distribution to the desired
   * one. Note that the chosen phase space point may be rejected, but
   * the chosen decay channel will not. This means that the weight
   * returned by this function does not influence the branching
   * ratios. For the FlatDecayer class this function simply returns 1.
   */
  inline virtual double reweight(const DecayMode &dm, const Particle & parent,
				 const ParticleVector & children) const;
  //@}

public:

  /**
   * Standard Init function used to initialize the interfaces.
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
   * Initialize this object after the setup phase before saving and
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
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<FlatDecayer> initFlatDecayer;

  /**
   *  Private and non-existent assignment operator.
   */
  FlatDecayer & operator=(const FlatDecayer &);

};

}


namespace ThePEG {

/** This template specialization informs ThePEG about the base classes
 *  of FlatDecayer. */
template <>
struct BaseClassTrait<FlatDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of FlatDecayer. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  FlatDecayer class. */
template <>
struct ClassTraits<FlatDecayer>: public ClassTraitsBase<FlatDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::FlatDecayer"; }
};

}

#include "FlatDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlatDecayer.tcc"
#endif

#endif /* ThePEG_FlatDecayer_H */
