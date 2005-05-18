// -*- C++ -*-
#ifndef ThePEG_NoPDF_H
#define ThePEG_NoPDF_H
// This is the declaration of the NoPDF class.

#include "ThePEG/PDF/PDFBase.h"
// #include "NoPDF.fh"
// #include "NoPDF.xh"

namespace ThePEG {

/**
 * NoPDF inherits from PDFBase and represents particles without
 * sub-structure. The only parton which can be extracted is the
 * incoming particle itself with a momentum distribution which is a
 * delta-function at \f$x=1\f$ (\f$l=0\f$).
 *
 * @see PDFBase
 * @see NoRemnants
 * 
 */
class NoPDF: public PDFBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline NoPDF();

  /**
   * Copy-constructor.
   */
  inline NoPDF(const NoPDF &);

  /**
   * Destructor.
   */
  virtual ~NoPDF();
  //@}

public:

  /** @name Virtual functions mandated by the PDFBase base class. */
  //@{
  /**
   * Return true because we can handle any particle.
   */
  virtual bool canHandleParticle(tcPDPtr particle) const;

  /**
   * Return true if canHandleParticle() and if the corresponding
   * method for remnantHandler() returns true.
   */
  virtual bool canHandle(tcPDPtr particle) const;

  /**
   * Simply return the particle.
   */
  virtual cPDVector partons(tcPDPtr p) const;

  /**
   * The delta function.
   */
  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
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
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<NoPDF> initNoPDF;

  /**
   *  Private and non-existent assignment operator.
   */
  NoPDF & operator=(const NoPDF &);

};

/** This template specialization informs ThePEG about the base classes
 *  of NoPDF. */
template <>
struct BaseClassTrait<NoPDF,1>: public ClassTraitsType {
  /** Typedef of the first base class of NoPDF. */
  typedef PDFBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  NoPDF class. */
template <>
struct ClassTraits<NoPDF>: public ClassTraitsBase<NoPDF> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::NoPDF"; }
};

}

#include "NoPDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoPDF.tcc"
#endif

#endif /* ThePEG_NoPDF_H */
