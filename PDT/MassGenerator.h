// -*- C++ -*-
#ifndef ThePEG_MassGenerator_H
#define ThePEG_MassGenerator_H
// This is the declaration of the MassGenerator class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Interface/Interfaced.h"
#include "MassGenerator.fh"
// #include "MassGenerator.xh"

namespace ThePEG {

/**
 * MassGenerator is an abstract base class used by the ParticleData
 * class to generate a mass for a Particle instance.
 *
 * @see \ref MassGeneratorInterfaces "The interfaces"
 * defined for MassGenerator.
 * @see ParticleData
 */
class MassGenerator: public Interfaced {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MassGenerator();

  /**
   * Copy-constructor.
   */
  inline MassGenerator(const MassGenerator &);

  /**
   * Destructor.
   */
  virtual ~MassGenerator();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return true if this mass generator can handle the given particle
   * type.
   */
  virtual bool accept(const ParticleData &) const = 0;

  /**
   * Generate a mass for an instance of a given particle type.
   */
  virtual Energy mass(const ParticleData &) const = 0;
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<MassGenerator> initMassGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  MassGenerator & operator=(const MassGenerator &);

};

/** This template specialization informs ThePEG about the base classes
 *  of MassGenerator. */
template <>
struct BaseClassTrait<MassGenerator,1>: public ClassTraitsType {
  /** Typedef of the first base class of MassGenerator. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  MassGenerator class. */
template <>
struct ClassTraits<MassGenerator>: public ClassTraitsBase<MassGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MassGenerator"; }
};

}

#include "MassGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MassGenerator.tcc"
#endif

#endif /* ThePEG_MassGenerator_H */
