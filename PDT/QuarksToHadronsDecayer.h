// -*- C++ -*-
#ifndef THEPEG_QuarksToHadronsDecayer_H
#define THEPEG_QuarksToHadronsDecayer_H
// This is the declaration of the QuarksToHadronsDecayer class.

#include "ThePEG/PDT/Decayer.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
// #include "QuarksToHadronsDecayer.fh"
// #include "QuarksToHadronsDecayer.xh"

namespace ThePEG {

ThePEG_DECLARE_CLASS_POINTERS(FlavourGenerator, FlavGenPtr);

/**
 * The QuarksToHadronsDecayer class inherits from Decayer and is able
 * to decay particles to \f$n_q\f$ (2 or 4) quarks which then are
 * decayed to hadrons according to phase space. The number of final
 * hadrons can either be given by a fixed number or as a Gaussian
 * multiplicity distribution centered around \f$c+n_q/4+c_3\f$ and a
 * width \f$\sqrt{c}\f$, where \f$c = c_1 \log((m - \sum m)/c_2)\f$,
 * \f$m\f$ is the mass of the decaying particle, \f$\sum m\f$ the sum
 * of the quark masses and \f$c_i\f$ real parameters.
 *
 * @see \ref QuarksToHadronsDecayerInterfaces "The interfaces"
 * defined for QuarksToHadronsDecayer.
 * @see ParticleData
 * 
 */
class QuarksToHadronsDecayer: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline QuarksToHadronsDecayer();

  /**
   * Copy-constructor.
   */
  inline QuarksToHadronsDecayer(const QuarksToHadronsDecayer &);

  /**
   * Destructor.
   */
  virtual ~QuarksToHadronsDecayer();
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
  //@}

  /**
   * Get the number of hadrons to be produced, given the mass of the
   * decaying particle, \a m0, and the number, \a Nq and summed masses
   * of the quarks, \a summq.
   */
  virtual int getN(Energy m0, Energy summq, int Nq) const;

  /**
   * Produce \a Nh hadrons from the specified \a quarks. The last
   * quark is considered to be a spectator quark.
   */
  virtual PVector getHadrons(int Nh, tcPDVector quarks) const;

  /**
   * Distribute the produced children in phase space. This default
   * version uses a flat phase space which can be reweighted by
   * overriding the reweight() function.
   */
  virtual void distribute(const Particle & parent, PVector & children) const;

  /**
   * Called by distribute() to reweight the default flat phase
   * spece. Can be overridden by sub-classes and should return a
   * number between 0 and 1. This version returns 1.
   */
  virtual double reweight(const Particle & parent,
			  const PVector & children) const;

public:

  /**
   * Return the fixed number of hadrons to be produced. If less than
   * 2, the number is instead given by a gaussian multiplicity
   * distribution.
   */
  inline int fixedN() const;

  /**
   * Return the minimum number of hadrons to be produced.
   */
  inline int minN() const;

  /**
   * Return the parameter \f$c_1\f$ used for the multiplicity
   * distriution.
   */
  inline double c1() const;

  /**
   * Return the parameter \f$c_2\f$ used for the multiplicity
   * distriution.
   */
  inline Energy c2() const;

  /**
   * Return the parameter \f$c_3\f$ used for the multiplicity
   * distriution.
   */
  inline double c3() const;

  /**
   * Return a pointer to the flavour generator to be used.
   */
  inline tcFlavGenPtr flavourGenerator() const;

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:


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
   * The fixed number of hadrons to be produced. If less than 2, the
   * number is instead given by a gaussian multiplicity distribution.
   */
  int theFixedN;

  /**
   * The minimum hadrons to be produced.
   */
  int theMinN;

  /**
   * The parameter \f$c_1\f$ of the multiplicity distribution.
   */
  double theC1;
  /**
   * The parameter \f$c_2\f$ of the multiplicity distribution.
   */
  Energy theC2;

  /**
   * The parameter \f$c_3\f$ of the multiplicity distribution.
   */
  double theC3;

  /**
   * The object in charge of generating hadrons spieces from given
   * quark flavours.
   */
  FlavGenPtr theFlavourGenerator;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<QuarksToHadronsDecayer> initQuarksToHadronsDecayer;

  /**
   * Private and non-existent assignment operator.
   */
  QuarksToHadronsDecayer & operator=(const QuarksToHadronsDecayer &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of QuarksToHadronsDecayer. */
template <>
struct BaseClassTrait<QuarksToHadronsDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of QuarksToHadronsDecayer. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  QuarksToHadronsDecayer class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<QuarksToHadronsDecayer>
  : public ClassTraitsBase<QuarksToHadronsDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::QuarksToHadronsDecayer"; }
  /** Return the name of the shared library be loaded to get access to
   *  the QuarksToHadronsDecayer class and every other class it uses
   *  (except the base class). */
  static string library() { return "QuarksToHadronsDecayer.so"; }
};

/** @endcond */

}

#include "QuarksToHadronsDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "QuarksToHadronsDecayer.tcc"
#endif

#endif /* THEPEG_QuarksToHadronsDecayer_H */
