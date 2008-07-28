// -*- C++ -*-
//
// DecayHandler.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_DecayHandler_H
#define ThePEG_DecayHandler_H
// This is the declaration of the DecayHandler class.

#include "StepHandler.h"

namespace ThePEG {

/**
 * The DecayHandler is the base class of all handlers implementing the
 * administration of decays of unstable particles. It is derived from
 * the more general StepHandler class, and overrides the handle()
 * method. This base class simply decays all unstable particle in the
 * current step.
 *
 * @see \ref DecayHandlerInterfaces "The interfaces"
 * defined for DecayHandler.
 * @see StepHandler
 * @see EventHandler
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
   * Destructor.
   */
  virtual ~DecayHandler();
  //@}

public:

  /** @name Virtual functions required by the StepHandler class. */
  //@{
  /**
   * Look through all \a tagged particled and decay all unstable ones.
   * @param eh the EventHandler in charge of the generation.
   * @param tagged the vector of particles to consider. If empty, all
   * final state particles in the current Step is considered.
   * @param hint a possible Hint which is ignored in this implementation.
   */
  virtual void handle(EventHandler & eh, const tPVector & tagged,
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

  /**
   * Get the maximum lifetime above which a particle is not decayed.
   */
  inline Length maxLifeTime() const;

  /**
   * Option for whether the maximum lifetime should be applied to the
   * mean lifetime of the particle species or the lifetime of the particle
   * instance
   */
  inline bool lifeTimeOption() const;

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
   * The maximum number of failed decay attempts allowed for each
   * particle.
   */
  long theMaxLoop;

  /**
   * The maximum lifetime above which a particle is not decayed.
   */
  Length theMaxLifeTime;

  /**
   *   Option for how theMaxLifeTime should be interpreted
   */
  bool theLifeTimeOption;

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

/** @cond TRAITSPECIALIZATIONS */

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

/** @endcond */

}

#include "DecayHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DecayHandler.tcc"
#endif

#endif /* ThePEG_DecayHandler_H */
