// -*- C++ -*-
#ifndef ThePEG_ThePEGStrategy_H
#define ThePEG_ThePEGStrategy_H
// This is the declaration of the ThePEGStrategy class.

#include "ThePEG/Repository/Strategy.h"
// #include "ThePEGStrategy.fh"
// #include "ThePEGStrategy.xh"

namespace ThePEG {

/**
 * The ThePEGStrategy class is a sub-class of the Strategy class,
 * simply implementing the correct citation for ThePEG in the
 * modelReferences() method.
 *
 * @see Strategy
 * 
 */
class ThePEGStrategy: public Strategy {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ThePEGStrategy();

  /**
   * Copy-constructor.
   */
  inline ThePEGStrategy(const ThePEGStrategy &);

  /**
   * Destructor.
   */
  virtual ~ThePEGStrategy();
  //@}

public:

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
   * Describe concrete class without persistent data.
   */
  static NoPIOClassDescription<ThePEGStrategy> initThePEGStrategy;

  /**
   *  Private and non-existent assignment operator.
   */
  ThePEGStrategy & operator=(const ThePEGStrategy &);

};


/** This template specialization informs ThePEG about the base classes
 *  of ThePEGStrategy. */
template <>
struct BaseClassTrait<ThePEGStrategy,1> {
  /** Typedef of the first base class of ThePEGStrategy. */
  typedef Strategy NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  ThePEGStrategy class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<ThePEGStrategy>: public ClassTraitsBase<ThePEGStrategy> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::ThePEGStrategy"; }
  /** Return the name of the shared library be loaded to get access to
   *  the ThePEGStrategy class and every other class it uses
   *  (except the base class). */
  static string library() { return "ThePEGStrategy.so"; }
};

}

#include "ThePEGStrategy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ThePEGStrategy.tcc"
#endif

#endif /* ThePEG_ThePEGStrategy_H */
