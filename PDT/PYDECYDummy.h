// -*- C++ -*-
#ifndef ThePEG_PYDECYDummy_H
#define ThePEG_PYDECYDummy_H
// This is the declaration of the PYDECYDummy class.

#include "Decayer.h"
// #include "PYDECYDummy.fh"
// #include "PYDECYDummy.xh"

namespace ThePEG {

/**
 * PYDECYDummy inherits from the Decayer class, and is used to
 * represent pythia-6 decay matrix element codes. It is a true dummy
 * class and cannot actually perform any decays.
 *
 * @see Decayer
 */
class PYDECYDummy: public Decayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline PYDECYDummy();

  /**
   * Stadard constructor giving the pythia-6 decay ME code.
   */
  inline PYDECYDummy(int);

  /**
   * Copy-constructor.
   */
  inline PYDECYDummy(const PYDECYDummy &);


  /**
   * Destructor.
   */
  inline virtual ~PYDECYDummy();
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

  /** @name Virtual functions required by the Decayer class.
   */
  //@{
  /**
   * Check if this decayer can perfom the decay specified by the
   * given decay mode.
   * @param dm the DecayMode describing the decay.
   * @return true.
   */
  virtual bool accept(const DecayMode & dm) const;

  /**
   * Perform a decay for a given DecayMode and a given Particle instance.
   * Will throw a std::logic_error if called.
   */
  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  //@}

  /**
   * Calculate branching ratio. In this case return 0.
   */
  virtual double brat(const DecayMode &,
		      const ParticleData &, double) const;

  /**
   * Calculate branching ratio. In this case return 0.
   */
  virtual double brat(const DecayMode &, const Particle &, double) const;



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

  /**
   * Read setup info from a standard stream.
   */
  virtual void readSetup(istream & is) throw(SetupException);


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
   * The pythia-6 ME code.
   */
  int theME;

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<PYDECYDummy> initPYDECYDummy;

  /**
   *  Private and non-existent assignment operator.
   */
  PYDECYDummy & operator=(const PYDECYDummy &);

};

/** This template specialization informs ThePEG about the base classes
 *  of PYDECYDummy. */
template <>
struct BaseClassTrait<PYDECYDummy,1>: public ClassTraitsType {
  /** Typedef of the first base class of PYDECYDummy. */
  typedef Decayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  PYDECYDummy class. */
template <>
struct ClassTraits<PYDECYDummy>: public ClassTraitsBase<PYDECYDummy> {
  /** Return a platform-independent class name */
  static string className() {
    return "ThePEG::PYDECYDummy";
  }
};

}

#include "PYDECYDummy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PYDECYDummy.tcc"
#endif

#endif /* ThePEG_PYDECYDummy_H */
