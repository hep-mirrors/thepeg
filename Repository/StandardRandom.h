// -*- C++ -*-
#ifndef ThePEG_StandardRandom_H
#define ThePEG_StandardRandom_H
// This is the declaration of the StandardRandom class.

#include "RandomGenerator.h"
#include "ThePEG/CLHEPWrap/JamesRandom.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
// #include "StandardRandom.fh"
// #include "StandardRandom.xh"

namespace ThePEG {

/**
 * StandardRandom inherits from the RandomGenerator class and is an
 * interface to the CLHEP::JamesRandom engine class.
 *
 * @see \ref StandardRandomInterfaces "The interfaces"
 * defined for StandardRandom.
 */
class StandardRandom: public RandomGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline StandardRandom();

  /**
   * Copy-constructor.
   */
  inline StandardRandom(const StandardRandom &);

  /**
   * Destructor.
   */
  virtual ~StandardRandom();
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

public:

  /**
   * return a reference to the HepJamesRandom engine.
   */
  virtual RandomEngine & randomGenerator();

  /**
   * Reset the underlying CLHEP random engine with the given seed.
   */
  virtual void setSeed(long seed);

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
   * Standard Init function used to initialize the interface.
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
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

private:

  /**
   * The underlying random engine..
   */
  JamesRandom theRandomGenerator;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<StandardRandom> initStandardRandom;

  /**
   *  Private and non-existent assignment operator.
   */
  StandardRandom & operator=(const StandardRandom &);

};

/** This template specialization informs ThePEG about the base classes
 *  of StandardRandom. */
template <>
struct BaseClassTrait<StandardRandom,1>: public ClassTraitsType {
  /** Typedef of the first base class of StandardRandom. */
  typedef RandomGenerator NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  StandardRandom class. */
template <>
struct ClassTraits<StandardRandom>: public ClassTraitsBase<StandardRandom> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::StandardRandom"; }
};

}

#include "StandardRandom.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardRandom.tcc"
#endif

#endif /* ThePEG_StandardRandom_H */
