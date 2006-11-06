// -*- C++ -*-
#ifndef ThePEG_SoftRemnantHandler_H
#define ThePEG_SoftRemnantHandler_H
// This is the declaration of the SoftRemnantHandler class.

#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/PDT/RemnantDecayer.fh"

namespace ThePEG {

/**
 * SoftRemnantHandler inherits from the RemnantHandler and implements
 * the generation of a single collinear RemnantParticle when anything
 * is extracted from anything else. Such a RemnantParticle needs to be
 * decayed by a special RemnantDecayer and the SoftRemnantHandler
 * needs to be assign such a decayer to work properly.
 *
 * @see \ref SoftRemnantHandlerInterfaces "The interfaces"
 * defined for SoftRemnantHandler.
 */
class SoftRemnantHandler: public RemnantHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  SoftRemnantHandler();

  /**
   * Copy-constructor.
   */
  SoftRemnantHandler(const SoftRemnantHandler &);

  /**
   * Destructor.
   */
  virtual ~SoftRemnantHandler();
  //@}

public:

  /** @name Virtual functions mandated by the RemnantHandler base class. */
  //@{
  /**
   * Return true if this remnant handler can handle extracting all
   * specified \a partons form the given \a particle.
   */
  virtual bool canHandle(tcPDPtr particle, const cPDVector & partons) const;

  /**
   * Generate momenta. Generates the momenta of the extracted parton
   * in the particle cms (but with the parton \f$x\f$ still the
   * positive light-cone fraction) as given by the last argument, \a
   * p. If the particle is space-like the positive and negative
   * light-cone momenta are \f$\sqrt{-m^2}\f$ and \f$-sqrt{-m^2}\f$
   * respectively. If the \a scale is negative, it means that the \a
   * doScale in the previous call to nDim() was true, otherwise the
   * given scale should be the virtuality of the extracted
   * parton. Generated quantities which are not returned in the
   * momentum may be saved in the PartonBin, \a pb, for later use. In
   * particular, if the nDim() random numbers, \a r, are not enough to
   * generate with weight one, the resulting weight should be stored
   * with the remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;

  /**
   * Generate the momentum of the extracted parton with the \a parent
   * momentum given by the last argument. If the \a scale is negative,
   * it means that the doScale in the previous call to nDim() was
   * true, otherwise the given \a scale should be the virtuality of
   * the extracted parton. \a shat is the total invariant mass squared
   * of the hard sub-system produced by the extracted parton and the
   * primary parton entering from the other side. Generated quantities
   * which are not returned in the momentum may be saved in the
   * PartonBinInstance, \a pb, for later use. In particular, if the
   * nDim() random numbers, \a r, are not enough to generate with
   * weight one, the resulting weight should be stored with the
   * remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale, Energy2 shat,
				    const LorentzMomentum & parent) const;
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
   * A pointer to a RemnantDecayer object which is able to decay the
   * produced RemnantParticle objects.
   */
  RemDecPtr remdec;

  /**
   * Utility function for the interface.
   */
  void setDecayer(RemDecPtr rd);


private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<SoftRemnantHandler> initSoftRemnantHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  SoftRemnantHandler & operator=(const SoftRemnantHandler &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of SoftRemnantHandler. */
template <>
struct BaseClassTrait<SoftRemnantHandler,1>: public ClassTraitsType {
  /** Typedef of the first base class of SoftRemnantHandler. */
  typedef RemnantHandler NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  SoftRemnantHandler class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<SoftRemnantHandler>:
    public ClassTraitsBase<SoftRemnantHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::SoftRemnantHandler"; }
};

/** @endcond */

}

#include "SoftRemnantHandler.icc"

#endif /* ThePEG_SoftRemnantHandler_H */
