// -*- C++ -*-
#ifndef ThePEG_BreitWignerMass_H
#define ThePEG_BreitWignerMass_H
// This is the declaration of the BreitWignerMass class.

#include "ThePEG/PDT/MassGenerator.h"
// #include "BreitWignerMass.fh"
// #include "BreitWignerMass.xh"

namespace ThePEG {

/**
 * BreitWignerMass is derived from MassGenerator and is able to
 * generate the mass for a particle given its nominal mass and its
 * with.
 *
 *
 * @see MassGenerator
 * @see ParticleData
 * 
 */
class BreitWignerMass: public MassGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline BreitWignerMass();

  /**
   * Copy-constructor.
   */
  inline BreitWignerMass(const BreitWignerMass &);

  /**
   * Destructor.
   */
  virtual ~BreitWignerMass();
  //@}

public:

  /** @name Virtual methods required by the MassGenerator base class. */
  //@{
  /**
   * Return true if this mass generator can handle the given particle
   * type.
   */
  inline virtual bool accept(const ParticleData &) const;

  /**
   * Generate a mass for an instance of a given particle type.
   */
  virtual Energy mass(const ParticleData &) const;
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
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
  static NoPIOClassDescription<BreitWignerMass> initBreitWignerMass;

  /**
   *  Private and non-existent assignment operator.
   */
  BreitWignerMass & operator=(const BreitWignerMass &);

};


/** @cond TRAITSPECIALIZATIONS */
ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(BreitWignerMass,MassGenerator,"BreitWignerMass.so");
/** @endcond */

}

#include "BreitWignerMass.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BreitWignerMass.tcc"
#endif

#endif /* ThePEG_BreitWignerMass_H */
