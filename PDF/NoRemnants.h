// -*- C++ -*-
#ifndef ThePEG_NoRemnants_H
#define ThePEG_NoRemnants_H
// This is the declaration of the NoRemnants class.

#include "ThePEG/PDF/RemnantHandler.h"
// #include "NoRemnants.fh"
// #include "NoRemnants.xh"

namespace ThePEG {

/**
 * NoRemnants inherits from RemnantHandler but can only handle
 * particles without sub-structure with the parton density given by a
 * NoPDF object and will never give any remnants.
 *
 *
 * @see RemnantHandler,
 * @see NoPDF.
 * 
 */
class NoRemnants: public RemnantHandler {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline NoRemnants();

  /**
   * Copy-constructor.
   */
  inline NoRemnants(const NoRemnants &);

  /**
   * Destructor.
   */
  virtual ~NoRemnants();
  //@}

public:

  /** @name Virtual functions mandated by the RemnantHandler base class. */
  //@{
  /**
   * Return true if this remnant handler can handle extracting all
   * specified partons. The NoRemnants will return false if any
   * partons are given.
   */
  inline virtual bool canHandle(tcPDPtr particle,
				const cPDVector & partons) const;

  /**
   * Generate Remnants. Will not generate remnants and will throw a
   * RemnantHandlerException if the extracted parton is not the
   * incomining particle with x=1.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;
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
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<NoRemnants> initNoRemnants;

  /**
   *  Private and non-existent assignment operator.
   */
  NoRemnants & operator=(const NoRemnants &);

};

/** This template specialization informs ThePEG about the
 *  base classes of NoRemnants. */
template <>
struct BaseClassTrait<NoRemnants,1> {
  /** Typedef of the first base class of NoRemnants. */
  typedef RemnantHandler NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  NoRemnants class. */
template <>
struct ClassTraits<NoRemnants>: public ClassTraitsBase<NoRemnants> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::NoRemnants"; }
};

}

#include "NoRemnants.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoRemnants.tcc"
#endif

#endif /* ThePEG_NoRemnants_H */
