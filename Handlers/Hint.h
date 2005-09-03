// -*- C++ -*-
#ifndef ThePEG_Hint_H
#define ThePEG_Hint_H
// This is the declaration of the Hint class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"

namespace ThePEG {

/**
 * Hint is a base class to be used to pass information
 * between <code>StepHandler</code> s, which cannot be convayed
 * through the Event record. The base class contains a vector of of
 * tagged particles. A StepHandler is always given a hint, and is only
 * allowed to treat Particles from the current Step which are listed
 * in the vector of tagged particles in the hint (if this vector is
 * empty the StepHandler may treat all particles in the Step.
 *
 * A Hint may have the stop flag set. In this case
 * the StepHandler to which the hint is assigned is
 * not called, and the event generation is stopped.
 *
 * A Hint may be given a scale, but what a StepHandler does with this
 * and other pieces of information possibly supplied by subclasses of
 * Hint, is not defined.
 *
 * There is a special Hint which is kept as the static member called
 * Hint::theDefaultHint. Although any default constructed Hint object
 * would work as a default hint, only pointers to this static object
 * should be used where a default hint is needed.
 *
 *
 * @see StepHandler
 * @see EventHandler
 * @see Particle
 * @see Event
 * @see Step
 * 
 */
class Hint: public Base {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline Hint();

  /**
   * Copy-constructor.
   */
  inline Hint(const Hint &);

  /**
   * Destructor.
   */
  inline virtual ~Hint();
  //@}

public:

  /**
   * Return true if there are tagged particles in the hint.
   */
  inline bool tagged() const;

  /**
   * Return a list of pointers to particles to be handled. A handler
   * is not allowed to touch other particles in the event record. If a
   * particle which has been flagged by the hint is no longer present
   * in the current Step, a null pointer is inserted in its place.
   */
  tPVector tagged(const Step & s) const;

  /**
   * Add a range of particles to the list of tagged particles.
   */
  template <typename InputIterator>
  inline void tag(InputIterator first, InputIterator last);

  /**
   * Add a particle to the list of tagged particles.
   */
  inline void tag(tPPtr);

  /**
   * Set the stop hint.
   */
  inline void stop(bool);

  /**
   * Get the stop hint.
   */
  inline bool stop() const;

  /**
   * Set the scale.
   */
  inline void scale(const Scale &);
  /**
   * Get the scale.
   */
  inline const Scale & scale() const;

  /**
   * Return a pointer to the default hint.
   */
  inline static tHintPtr Default();

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

private:

  /**
   * The vector of tagged particles.
   */
  tPVector theTagged;

  /**
   * The scale.
   */
  Scale theScale;

  /**
   * The stop hint.
   */
  bool theStopFlag;

  /**
   * The default hint.
   */
  static Hint theDefaultHint;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<Hint> initHint;

  /**
   * Assignment is private and non-existing.
   */
  inline const Hint & operator=(const Hint & h);

};


/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of Hint.
 */
template <>
struct BaseClassTrait<Hint,1>: public ClassTraitsType {
  /** Typedef of the base class of Hint. */
  typedef Base NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * Hint class.
 */
template <>
struct ClassTraits<Hint>:
    public ClassTraitsBase<Hint> {
  /** Return the class name. */
  static string className() { return "ThePEG::Hint"; }
};

/** @endcond */

}

#include "Hint.icc"

#endif /* ThePEG_Hint_H */
