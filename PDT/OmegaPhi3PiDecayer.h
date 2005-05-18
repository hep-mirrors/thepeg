// -*- C++ -*-
#ifndef THEPEG_OmegaPhi3PiDecayer_H
#define THEPEG_OmegaPhi3PiDecayer_H
// This is the declaration of the OmegaPhi3PiDecayer class.

#include "ThePEG/PDT/FlatDecayer.h"
// #include "OmegaPhi3PiDecayer.fh"
// #include "OmegaPhi3PiDecayer.xh"

namespace ThePEG {

/**
 * The OmegaPhi3PiDecayer class inherits from performs FlatDecayer and
 * will reweight the flat phase space suitable to describe the decay
 * of a \f$\phi\f$ or an \f$\omega\f$ into \f$\pi^+\pi^-\pi^0\f$. It
 * will in fact decay anything into \f$\pi^+\pi^-\pi^0\f$ assuming the
 * same matrix element.
 *
 * @see \ref OmegaPhi3PiDecayerInterfaces "The interfaces"
 * defined for OmegaPhi3PiDecayer.
 * @see FlatDecayer
 * @see ParticleData
 */
class OmegaPhi3PiDecayer: public FlatDecayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline OmegaPhi3PiDecayer();

  /**
   * Copy-constructor.
   */
  inline OmegaPhi3PiDecayer(const OmegaPhi3PiDecayer &);

  /**
   * Destructor.
   */
  virtual ~OmegaPhi3PiDecayer();
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
   * Give a weight to a phase space point. To be overridden by
   * subclasses. For a given decay mode, \a dm, decaying \a parent
   * particle and decayproducts, \a children, distributed according to
   * a flat distribution in phase space, return a weight (less or
   * equal to unity) modifying the flat distribution to the desired
   * one. Note that the chosen phase space point may be rejected, but
   * the chosen decay channel will not. This means that the weight
   * returned by this function does not influence the branching
   * ratios.
   */
  virtual double reweight(const DecayMode & dm, const Particle & parent,
			  const ParticleVector & children) const;
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
   * Used to multiply the bare weight to get something below unity. In
   * the Fortran pythia version it was set to 150 for unknown reasons.
   */
  double margin;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<OmegaPhi3PiDecayer> initOmegaPhi3PiDecayer;

  /**
   * Private and non-existent assignment operator.
   */
  OmegaPhi3PiDecayer & operator=(const OmegaPhi3PiDecayer &);

};

}


namespace ThePEG {

/** This template specialization informs ThePEG about the base classes
 *  of OmegaPhi3PiDecayer. */
template <>
struct BaseClassTrait<OmegaPhi3PiDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of OmegaPhi3PiDecayer. */
  typedef FlatDecayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  OmegaPhi3PiDecayer class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<OmegaPhi3PiDecayer>
  : public ClassTraitsBase<OmegaPhi3PiDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::OmegaPhi3PiDecayer"; }
  /** Return the name of the shared library be loaded to get access to
   *  the OmegaPhi3PiDecayer class and every other class it uses
   *  (except the base class). */
  static string library() { return "OmegaPhi3PiDecayer.so"; }
};

}

#include "OmegaPhi3PiDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "OmegaPhi3PiDecayer.tcc"
#endif

#endif /* THEPEG_OmegaPhi3PiDecayer_H */
