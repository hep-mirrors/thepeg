// -*- C++ -*-
#ifndef ThePEG_PDFBase_H
#define ThePEG_PDFBase_H
// This is the declaration of the PDFBase class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/PDF/PDFCuts.h"
// #include "PDFBase.fh"
#include "PDFBase.xh"

namespace ThePEG {

/**
 * PDFBase is the base class for implementing parton density functions
 * for particles with sub-structure. A number of of virtual methods
 * are defined which should be overridden by sub-classes.
 *
 * A PDFBase object can be assigned to a BeamParticleData object
 * and/or to a PartonExtractor object. A PDFBase has a pointer to a
 * RemnantHandler object which should be capable of generating
 * remnants for all partons which may be extracted by the PDF.
 *
 * @see \ref PDFBaseInterfaces "The interfaces"
 * defined for PDFBase.
 * @see BeamParticleData
 * @see PartonExtractor
 * @see RemnantHandler
 * @see PDFCuts
 */
class PDFBase: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PDFBase();

  /**
   * Copy-constructor.
   */
  PDFBase(const PDFBase &);

  /**
   * Destructor.
   */
  virtual ~PDFBase();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return true if this PDF can handle the extraction of partons from
   * the given \a particle.
   */
  virtual bool canHandleParticle(tcPDPtr particle) const = 0;

  /**
   * Return true if canHandleParticle() and if the corresponding
   * method for remnantHandler() returns true for the given \a
   * particle.
   */
  virtual bool canHandle(tcPDPtr particle) const;

  /**
   * Return the partons which this PDF may extract from the given
   * \a particle.
   */
  virtual cPDVector partons(tcPDPtr particle) const = 0;

  /**
   * The density. Return the pdf for the given \a parton inside the
   * given \a particle for the virtuality \a partonScale and
   * logarithmic momentum fraction \a l \f$(l=\log(1/x)\f$. The \a
   * particle is assumed to have a virtuality \a particleScale.
   */
  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * The density. Return the pdf for the given \a parton inside the
   * given \a particle for the virtuality \a partonScale and momentum
   * fraction \a x. The \a particle is assumed to have a virtuality \a
   * particleScale.
   */
  virtual double xfx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double x, double eps = 0.0,
		     Energy2 particleScale = 0.0*GeV2) const;

  /**
   * The valence density. Return the pdf for the given cvalence \a
   * parton inside the given \a particle for the virtuality \a
   * partonScale and logarithmic momentum fraction \a l
   * \f$(l=\log(1/x)\f$. The \a particle is assumed to have a
   * virtuality \a particleScale. If not overidden by a sub class this
   * will return zero.
   */
  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;

  /**
   * The valence density. Return the pdf for the given cvalence \a
   * parton inside the given \a particle for the virtuality \a
   * partonScale and momentum fraction \a x. The \a particle is
   * assumed to have a virtuality \a particleScale. If not overidden
   * by a sub class this will return zero.
   */
  virtual double xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		      double x, double eps = 0.0,
		      Energy2 particleScale = 0.0*GeV2) const;

  /**
   * Generate a momentum fraction. If the PDF contains strange peaks
   * which can be difficult to handle, this function may be
   * overwritten to return an appropriate \f$l=\log(1/x)\f$ for a \a z
   * uniformly distributed in ]0,1[. Also the jacobobian of the
   * \f$l\rightarrow z\f$ variable transformation must in the function
   * multiply the \a jacobian argument. The default version will
   * simply use the function \f$l(z) = l_{\min} +
   * z*(l_{\max}-l_{\min})\f$ (where the limits are set by \a cut).
   */
  virtual double flattenL(tcPDPtr particle, tcPDPtr parton, const PDFCuts &cut,
			  double z, double & jacobian) const;

  /**
   * Generate scale. If the PDF contains strange peaks which can be
   * difficult to handle, this function may be overwritten to return
   * an appropriate scale \f$Q^2\f$ for a \a z uniformly distributed
   * in ]0,1[. Also the jacobobian of the \f$Q^2\rightarrow z\f$
   * variable transformation must multiply the \a jacobian
   * argument. The default version will simply use the function \f$Q^2
   * = Q^2_{\min}(Q^2_{\max}/Q^2_{\min})^z\f$ or, if \f$Q^2_{\min}\f$
   * is zero, \f$Q^2 = z Q^2_{\max}\f$ (where the limits are set by \a
   * cut).
   */
  virtual Energy2 flattenScale(tcPDPtr particle, tcPDPtr parton,
			       const PDFCuts & cut, double l, double z,
			       Energy2 & jacobian) const;
  //@}

  /**
   * Pointer to the remnant handler to handle remnant when extracting
   * partons according to these densities.
   */
  inline tcRemHPtr remnantHandler() const;


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
  virtual void doinit() throw(InitException);

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

protected:

  /**
   * A remnant handler which can generate remnants for the parton
   * extracted withfor this PDF
   */
  RemHPtr theRemnantHandler;

protected:

  /**
   * Indicate how to deal with x and Q2 which are out of range.
   */
  enum RangeException {
    rangeFreeze, /**> Freeze the value of the PDF outside the limits. */
    rangeZero,   /**> Set the PDF to zero outside the limits. */
    rangeThrow   /**> THrow an exception if outside the limits. */
  };

  /**
   * Indicate to subclasses how to deal with x and Q2 which are out of
   * range.
   */
  RangeException rangeException;

private:


  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class with persistent data.
   */
  static AbstractClassDescription<PDFBase> initPDFBase;

  /**
   *  Private and non-existent assignment operator.
   */
  PDFBase & operator=(const PDFBase &);

};

ThePEG_DECLARE_CLASS_TRAITS(PDFBase,HandlerBase);

}

#include "PDFBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDFBase.tcc"
#endif

#endif /* ThePEG_PDFBase_H */
