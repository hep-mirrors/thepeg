// -*- C++ -*-
#ifndef ThePEG_Interfaced_H
#define ThePEG_Interfaced_H
// This is the declaration of the Interfaced class.

#include "ThePEG/Config/ThePEG.h"
#include "InterfacedBase.h"

namespace ThePEG {

/**
 * The Interfaced class is derived from the InterfacedBase class
 * adding a couple of things particular to ThePEG, in an attempt to
 * keep the InterfacedBase class as generic as possible.
 *
 * The main addition is that the Interfaced class has a pointer to an
 * EventGenerator object. During the run-phase this points to the
 * EventGenerator controlling the run in which the Interfaced object
 * is used. Through this EventGenerator there is quick access to
 * eg. the set of ParticleData objects used, and the default
 * RandomGenerator for the run. Note that no EventGenerator object is
 * available to the Interfaced object during the setup
 * phase.
 *
 * @see InterfacedBase,
 * @see EventGenerator,
 * @see ParticleData,
 * @see RandomGenerator,
 */
class Interfaced: public InterfacedBase {

  /** Repository is a friend. */
  friend class Repository;

public:

  /**
   * Empty virtual destructor
   */
  inline virtual ~Interfaced();

  /**
   * Functions which are to be used during the actual event
   * generation, after the setup is complete.
   */
public:


  /** @name Functions used during the actual event generation, after
      the setup is complete. */
  //@{
  /**
   * Create a new Particle instance given a id number.
   */
  PPtr getParticle(long) const;

  /**
   * Return a pointer to the ParticleData object corresponding to the
   * given id number.
   */
  PDPtr getParticleData(long) const;

  /**
   * Returns true if this object has actally been used.
   */
  inline bool used() const;

  /**
   * Should be called to indicate that this object has actually been
   * used.
   */
  inline void useMe() const;
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
   * Standard Init function.
   */
  static void Init();

protected:

  /**
   * Register an Interfaced object with the Repository.
   */
  static void registerRepository(IBPtr);

  /**
   * Register an Interfaced object with the Repository, giving it a
   * name.
   */
  static void registerRepository(IBPtr, string newName);

  /**
   * Protected default constructor.
   */
  inline Interfaced();

  /**
   * Protected constructor taking a name as argument.
   */
  inline Interfaced(string newName);

  /**
   * Protected copy-constructor.
   */
  inline Interfaced(const Interfaced &);

  /**
   * Return a pointer to the EventGenerator controlling the run.
   * During the setup phase this returns a null pointer.
   */
  inline tEGPtr generator() const;

  /** @name Standard Interfaced virtual functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase. This function
   * is called everytime the object is changed through an interface
   * during the setup phase. Also if the setup is changed for an
   * object on which this is dependent. Note that the generator() is
   * not available when this method is called.
   * @throws UpdateException if the setup is such that the object
   * would not work properly.
   */
  inline virtual void doupdate() throw(UpdateException) = 0;

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk. Nothing should have changed since the
   * last update() call.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw (InitException) = 0;

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish() = 0;
  //@}

private:

  /**
   * Used internally by 'useMe'
   */
  void setUsed() const;

  /**
   * A pointer to the EventGenerator controlling the run.
   */
  tEGPtr theGenerator;

  /**
   * Flag to tell whether this object has been used or not.
   */
  mutable bool theUseFlag;

private:

  /**
   * Standard Initialization object.
   */
  static AbstractClassDescription<Interfaced> initInterfaced;

  /**
   *  Private and non-existent assignment operator.
   */
  Interfaced & operator=(const Interfaced &);

public:

  /**
   * This method may be implemented by derived classes to facilitate
   * debugging.
   */
  virtual void debug() const;

};

/**
 * This template specialization informs ThePEG about the
 * base class of Interfaced.
 */
template <>
struct BaseClassTrait<Interfaced,1> {
  /** Typedef of the base class of Interfaced. */
  typedef InterfacedBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * Interfaced class.
 */
template <>
struct ClassTraits<Interfaced>: public ClassTraitsBase<Interfaced> {
  /** Return the class name. */
  static string className() { return "ThePEG::Interfaced"; }
};

}

#include "Interfaced.icc"

#endif /* ThePEG_Interfaced_H */
