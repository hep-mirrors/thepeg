// -*- C++ -*-
#ifndef THEPEG_DalitzDecayer_H
#define THEPEG_DalitzDecayer_H
// This is the declaration of the DalitzDecayer class.

#include "ThePEG/PDT/Decayer.h"
// #include "DalitzDecayer.fh"
// #include "DalitzDecayer.xh"

namespace ThePEG {

/**
 * The DalitzDecayer inherits from the Decayer class and performs
 * Dalitz decays into \f$\gamma e^+ e^-\f$.
 *
 * @see \ref DalitzDecayerInterfaces "The interfaces"
 * defined for DalitzDecayer.
 */
class DalitzDecayer: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline DalitzDecayer();

  /**
   * Copy-constructor.
   */
  inline DalitzDecayer(const DalitzDecayer &);

  /**
   * Destructor.
   */
  virtual ~DalitzDecayer();
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
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

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
  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  virtual IVector getReferences();
  //@}

private:

  /**
   * Quick access to the rho particle data.
   */
  PDPtr rho;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<DalitzDecayer> initDalitzDecayer;

  /**
   * Private and non-existent assignment operator.
   */
  DalitzDecayer & operator=(const DalitzDecayer &);

};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of DalitzDecayer. */
template <>
struct BaseClassTrait<DalitzDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of DalitzDecayer. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  DalitzDecayer class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<DalitzDecayer>
  : public ClassTraitsBase<DalitzDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::DalitzDecayer"; }
  /** Return the name of the shared library be loaded to get access to
   *  the DalitzDecayer class and every other class it uses
   *  (except the base class). */
  static string library() { return "DalitzDecayer.so"; }

};

/** @endcond */

}

#include "DalitzDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DalitzDecayer.tcc"
#endif

#endif /* THEPEG_DalitzDecayer_H */
