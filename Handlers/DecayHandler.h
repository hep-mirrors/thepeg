// -*- C++ -*-
#ifndef ThePEG_DecayHandler_H
#define ThePEG_DecayHandler_H
// This is the declaration of the DecayHandler class.

#include "StepHandler.h"
// #include "DecayHandler.fh"
#include "DecayHandler.xh"

namespace ThePEG {

/**
 * The DecayHandler is the base class of all handlers implementing the
 * administration of decays of unstable particles. It is derived from
 * the more general StepHandler class, and overrides the handle()
 * method. This base class simply decays all unstable particle in the
 * current step.
 *
 * @see StepHandler
 * @see CollisionHandler
 * @see SubProcessHandler
 * 
 */
class DecayHandler: public StepHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline DecayHandler();

  /**
   * Copy-constructor.
   */
  inline DecayHandler(const DecayHandler &);

  /**
   * Destructor.
   */
  virtual ~DecayHandler();
  //@}

public:

  /** @name Virtual functions required by the StepHandler class. */
  //@{
  /**
   * Look through all \a tagged particled and decay all unstable ones.
   * @param ch the PartialCollisionHandler in charge of the generation.
   * @param tagged the vector of particles to consider. If empty, all
   * final state particles in the current Step is considered.
   * @param hint a possible Hint which is ignored in this implementation.
   */
  virtual void handle(PartialCollisionHandler & ch, const tPVector & tagged,
		      const Hint & hint)
    ThePEG_THROW_SPEC((Veto, Stop, Exception));
  //@}

  /**
   * Perform the decay of one unstable particle.
   * @param parent the particle to be decayed.
   * @param s the Step where decay products are inserted.
   */
  void performDecay(tPPtr parent, Step & s) const throw(Veto, Exception);

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

  /**
   * The maximum number of failed decay attempts allowed for each
   * particle.
   */
  inline long maxLoop() const;

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
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The maximum number of failed decay attempts allowed for each
   * particle.
   */
  long theMaxLoop;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<DecayHandler> initDecayHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  DecayHandler & operator=(const DecayHandler &);

};

/**
 * This template specialization informs ThePEG about the
 * base class of DecayHandler.
 */
template <>
struct BaseClassTrait<DecayHandler,1>: public ClassTraitsType {
  /** Typedef of the base class of DecayHandler. */
  typedef StepHandler NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * DecayHandler class.
 */
template <>
struct ClassTraits<DecayHandler>: public ClassTraitsBase<DecayHandler> {
  /** Return the class name. */
  static string className() { return "ThePEG::DecayHandler"; }
};

}

#include "DecayHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DecayHandler.tcc"
#endif

#endif /* ThePEG_DecayHandler_H */
