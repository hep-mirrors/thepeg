// -*- C++ -*-
#ifndef ThePEG_PartialEventGenerator_H
#define ThePEG_PartialEventGenerator_H
// This is the declaration of the PartialEventGenerator class.

#include "ThePEG/Repository/EventGenerator.h"
// #include "PartialEventGenerator.fh"
// #include "PartialEventGenerator.xh"

namespace ThePEG {

/**
 * PartialEventGenerator inherits from the EventGenerator class and
 * has a pointer to a PartialCollisionHandler which is not able to
 * generate full event, hence EventGenerator::go() and hence
 * EventGenerator::shoot() are inactive and only the hence
 * EventGenerator::partialEvent() function should be used with a
 * previously partially event is specified..
 *
 * @see EventGenerator,
 * @see PartialCollisionHandler.
 * 
 */
class PartialEventGenerator: public EventGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PartialEventGenerator();

  /**
   * Copy-constructor.
   */
  PartialEventGenerator(const PartialEventGenerator &);

  /**
   * Destructor.
   */
  virtual ~PartialEventGenerator();
  //@}

public:

  /**
   * Return a pointer to the PatrialCollisionHandler.
   */
  inline tPartCollHdlPtr handler() const;
  
  /**
   * Return the event being generated.
   */
  virtual tcEventPtr currentEvent() const;

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

  /**
   * Generate one event. Does nothing.
   */
  virtual EventPtr doShoot();

  /**
   * Finish generating an event constructed from the outside. 
   */
  virtual EventPtr doPartialEvent(tEventPtr);


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
   * Pointer to the PatrialCollisionHandler.
   */
  PartCollHdlPtr theHandler;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<PartialEventGenerator> initPartialEventGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  PartialEventGenerator & operator=(const PartialEventGenerator &);

};

/** This template specialization informs ThePEG about the base classes
 *  of PartialEventGenerator. */
template <>
struct BaseClassTrait<PartialEventGenerator,1> {
  /** Typedef of the first base class of PartialEventGenerator. */
  typedef EventGenerator NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  PartialEventGenerator class. */
template <>
struct ClassTraits<PartialEventGenerator>:
    public ClassTraitsBase<PartialEventGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::PartialEventGenerator"; }
};

}

#include "PartialEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartialEventGenerator.tcc"
#endif

#endif /* ThePEG_PartialEventGenerator_H */
