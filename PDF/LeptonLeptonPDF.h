// -*- C++ -*-
#ifndef ThePEG_LeptonLeptonPDF_H
#define ThePEG_LeptonLeptonPDF_H
// This is the declaration of the LeptonLeptonPDF class.

#include "ThePEG/PDF/PDFBase.h"
// #include "LeptonLeptonPDF.fh"
// #include "LeptonLeptonPDF.xh"

namespace ThePEG {

/**
 * LeptonLeptonPDF inherits from PDFBase and encodes the distribution
 * of leptons within leptons, ie. the energy loss of leptons due to
 * radiation of soft photons.
 *
 * @see \ref LeptonLeptonPDFInterfaces "The interfaces"
 * defined for LeptonLeptonPDF.
 */
class LeptonLeptonPDF: public PDFBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline LeptonLeptonPDF();

  /**
   * Copy-constructor.
   */
  inline LeptonLeptonPDF(const LeptonLeptonPDF &);

  /**
   * Destructor.
   */
  virtual ~LeptonLeptonPDF();
  //@}

public:

  /** @name Virtual functions required by the PDFBase class. */
  //@{
  /**
   * Return true if this PDF can handle the extraction of parton from the
   * given particle ie. if the particle is a lepton.
   */
  virtual bool canHandleParticle(tcPDPtr particle) const;

  /**
   * Return a vector of partons handled by this PDF (always the same
   * lepton as the incoming particle).
   */
  virtual cPDVector partons(tcPDPtr p) const;

  /**
   * Return the value of the density function at a given
   * l\f$=\log(1/x)\f$ and scale for the given parton.
   */
  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the the valens part of the true pdf for the given
   * parameters, with the momentum fraction given as
   * l\f$=\log(1/x)\f$. This version simply returns the full pdf.
   */
  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Return the the valens part of the true pdf for the given
   * parameters, with the momentum fraction given as x. This version
   * simply returns the full pdf.
   */
  virtual double xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		      double x, double eps, Energy2 particleScale) const;

  /**
   * If the PDF contains strange peaks which can be difficult to
   * handle, this function may be overwritten to return an appropriate
   * l\f$=\log(1/x)\f$ for a z given by a flat distribution in
   * ]0,1[. Also the jacobobian of the l(z) function must be
   * returned. The default version will simly use the function l(z) =
   * lmin + z*(lmax-lmin).
   */
  virtual double flattenL(tcPDPtr particle, tcPDPtr parton, const PDFCuts &,
			  double z, double & jacobian) const;
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
  static NoPIOClassDescription<LeptonLeptonPDF> initLeptonLeptonPDF;

  /**
   *  Private and non-existent assignment operator.
   */
  LeptonLeptonPDF & operator=(const LeptonLeptonPDF &);

};

/** This template specialization informs ThePEG about the base classes
 *  of LeptonLeptonPDF. */
template <>
struct BaseClassTrait<LeptonLeptonPDF,1>: public ClassTraitsType {
  /** Typedef of the first base class of LeptonLeptonPDF. */
  typedef PDFBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  LeptonLeptonPDF class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<LeptonLeptonPDF>: public ClassTraitsBase<LeptonLeptonPDF> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::LeptonLeptonPDF"; }
  /** Return the name of the shared library be loaded to get access to
   *  the LeptonLeptonPDF class and every other class it uses (except
   *  the base class). */
  static string library() { return "LeptonLeptonPDF.so"; }
};

}

#include "LeptonLeptonPDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LeptonLeptonPDF.tcc"
#endif

#endif /* ThePEG_LeptonLeptonPDF_H */
