// -*- C++ -*-
#ifndef THEPEG_DummyDecayer_H
#define THEPEG_DummyDecayer_H
// This is the declaration of the DummyDecayer class.

#include "ThePEG/PDT/Decayer.h"
// #include "DummyDecayer.fh"
// #include "DummyDecayer.xh"

namespace ThePEG {

/**
 * DummyDecayer inherits from Decayer and is a dummy decayer class to
 * be used for symbolic decay channels. If it for some reason is
 * called to perform a decay, it will throw a std::logic_error.
 *
 * @see Decayer.
 * 
 */
class DummyDecayer: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline DummyDecayer();

  /**
   * Copy-constructor.
   */
  inline DummyDecayer(const DummyDecayer &);

  /**
   * Destructor.
   */
  virtual ~DummyDecayer();
  //@}

public:

  /** @name Virtual functions required by the Decayer class.
   */
  //@{
  /**
   * Check if this decayer can perfom the decay specified by the
   * given decay mode.
   * @param dm the DecayMode describing the decay.
   * @return true always.
   */
  virtual bool accept(const DecayMode & dm) const;

  /**
   * Perform a decay for a given DecayMode and a given Particle
   * instance. Will throw std::logic_error if called.
   * @param dm the DecayMode describing the decay.
   * @param p the Particle instance to be decayed.
   * @return a ParticleVector containing the decay products.
   */
  virtual ParticleVector decay(const DecayMode & dm, const Particle & p) const;
 
  /**
   * Will always return zero, since no decay can ever be performed
   * with this decayer.
   */
  virtual double brat(const DecayMode &,
		      const ParticleData &, double) const;
  /**
   * Will always return zero, since no decay can ever be performed
   * with this decayer.
   */
  virtual double brat(const DecayMode &, const Particle &, double) const;
  //@}

public:

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
  static NoPIOClassDescription<DummyDecayer> initDummyDecayer;

  /**
   * Private and non-existent assignment operator.
   */
  DummyDecayer & operator=(const DummyDecayer &);

};

}


namespace ThePEG {

/** This template specialization informs ThePEG about the base classes
 *  of DummyDecayer. */
template <>
struct BaseClassTrait<DummyDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of DummyDecayer. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  DummyDecayer class. */
template <>
struct ClassTraits<DummyDecayer>
  : public ClassTraitsBase<DummyDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::DummyDecayer"; }

};

}

#include "DummyDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DummyDecayer.tcc"
#endif

#endif /* THEPEG_DummyDecayer_H */
