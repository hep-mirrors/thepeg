// -*- C++ -*-
#ifndef THEPEG_ColourPairDecayer_H
#define THEPEG_ColourPairDecayer_H
// This is the declaration of the ColourPairDecayer class.

#include "ThePEG/PDT/FlatDecayer.h"
// #include "ColourPairDecayer.fh"
// #include "ColourPairDecayer.xh"

namespace ThePEG {

/**
 * ColourPairDecayer inherits from the FlatDecayer class and performs
 * decays according to phase space into two or more particles, some of
 * which may be coloured. The coloured particles must come in pairs
 * and will be colour connected pair-wise.
 *
 * @see \ref ColourPairDecayerInterfaces "The interfaces"
 * defined for ColourPairDecayer.
 */
class ColourPairDecayer: public FlatDecayer {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ColourPairDecayer();

  /**
   * Copy-constructor.
   */
  inline ColourPairDecayer(const ColourPairDecayer &);

  /**
   * Destructor.
   */
  virtual ~ColourPairDecayer();
  //@}

public:

  /** @name Virtual functions required by the Decayer and FlatDecayer classes.
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
   * Produce children. Used by the FlatDecayer::decay() to produce
   * instances of the children given a DecayMode \a dm and the
   * decaying particle \a parent..
   */
  virtual ParticleVector getChildren(const DecayMode & dm,
				     const Particle & parent) const;
  //@}

  /**
   * Return true if the produced gluons and quarks should be
   * showered. The corresponding flag is set though the interface.
   */
  inline bool shower() const;

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
   * If true the produced gluons and quarks should be showered.
   */
  bool doShower;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<ColourPairDecayer> initColourPairDecayer;

  /**
   * Private and non-existent assignment operator.
   */
  ColourPairDecayer & operator=(const ColourPairDecayer &);

};

}


namespace ThePEG {

/** This template specialization informs ThePEG about the base classes
 *  of ColourPairDecayer. */
template <>
struct BaseClassTrait<ColourPairDecayer,1>: public ClassTraitsType {
  /** Typedef of the first base class of ColourPairDecayer. */
  typedef FlatDecayer NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  ColourPairDecayer class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<ColourPairDecayer>
  : public ClassTraitsBase<ColourPairDecayer> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::ColourPairDecayer"; }
  /** Return the name of the shared library be loaded to get access to
   *  the ColourPairDecayer class and every other class it uses
   *  (except the base class). */
  static string library() { return "ColourPairDecayer.so"; }

};

}

#include "ColourPairDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourPairDecayer.tcc"
#endif

#endif /* THEPEG_ColourPairDecayer_H */
