// -*- C++ -*-
#ifndef ThePEG_FixedCMSLuminosity_H
#define ThePEG_FixedCMSLuminosity_H
// This is the declaration of the FixedCMSLuminosity class.

#include "LuminosityFunction.h"
// #include "FixedCMSLuminosity.fh"
// #include "FixedCMSLuminosity.xh"

namespace ThePEG {

/**
 * The FixedCMSLuminosity class describes an experiment with incoming
 * particles colliding with precicely defined and opposite momenta. It
 * is derived from the LuminosityFunction base class.
 *
 * @see \ref FixedCMSLuminosityInterfaces "The interfaces"
 * defined for FixedCMSLuminosity.
 */
class FixedCMSLuminosity: public LuminosityFunction {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline FixedCMSLuminosity();

  /**
   * Copy-constructor.
   */
  inline FixedCMSLuminosity(const FixedCMSLuminosity &);

  /**
   * Destructor.
   */
  virtual ~FixedCMSLuminosity();
  //@}

public:

  /** @name Virtual functions required by the LuminosityFunction class. */
  //@{
  /**
   * Return true if this luminosity function can actually handle a
   * given pair of incoming particles.
   */
  inline virtual bool canHandle(const cPDPair &) const;

  /**
   * Return the maximum center of mass energy.
   */
  inline virtual Energy maximumCMEnergy() const;
  //@}

  /**
   * The average total energy in the cms of the incoming particles.
   */
  inline Energy energy() const;

public:

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
   * The total energy in the collisons.
   */
  Energy theEnergy;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<FixedCMSLuminosity> initFixedCMSLuminosity;

  /**
   *  Private and non-existent assignment operator.
   */
  FixedCMSLuminosity & operator=(const FixedCMSLuminosity &);

};

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of FixedCMSLuminosity.
 */
template <>
struct BaseClassTrait<FixedCMSLuminosity,1>: public ClassTraitsType {
  /** Typedef of the base class of FixedCMSLuminosity. */
  typedef LuminosityFunction NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * FixedCMSLuminosity class and the shared object where it is defined.
 */
template <>
struct ClassTraits<FixedCMSLuminosity>:
    public ClassTraitsBase<FixedCMSLuminosity> {
  /** Return the class name. */
  static string className() { return "ThePEG::FixedCMSLuminosity"; }
  /** Return the name of the shared library be loaded to get access to
   *  the FixedCMSLuminosity class and every other class it uses
   *  (except the base class). */
  static string library() { return "FixedCMSLuminosity.so"; }
};

/** @endcond */

}

#include "FixedCMSLuminosity.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FixedCMSLuminosity.tcc"
#endif

#endif /* ThePEG_FixedCMSLuminosity_H */
