// -*- C++ -*-
#ifndef ThePEG_PDFBase_H
#define ThePEG_PDFBase_H
//
// This is the declaration of the <!id>PDFBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>PDFBase<!!id> is the base class for implementing parton
// density functions for particles with sub-structure. A number of of
// virtual methods are defined which should be overridden by
// sub-classes.
//
// A <!id>PDFBase<!!id> object can either be assigned to a
// <!class>BeamParticleData<!!class> object or to a
// <!class>PartonExtractor<!!class> object. A <!id>PDFBase<!!id> has a
// pointer to a <!class>RemnantHandler<!!class> object which should be
// capable of generating remnants for all partons which may be
// extracted by the PDF.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:BeamParticleData.html">BeamParticleData.h</a>,
// <a href="http:PartonExtractor.html">PartonExtractor.h</a>,
// <a href="http:RemnantHandler.html">RemnantHandler.h</a>,
// <a href="http:PDFCuts.html">PDFCuts.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/PDF/PDFCuts.h"
// #include "PDFBase.fh"
#include "PDFBase.xh"

namespace ThePEG {

class PDFBase: public HandlerBase {

public:

  PDFBase();
  PDFBase(const PDFBase &);
  virtual ~PDFBase();
  // Standard ctors and dtor

public:

  virtual bool canHandleParticle(tcPDPtr particle) const = 0;
  // Return true if this PDF can handle the extraction of parton from the
  // given particle.

  virtual bool canHandle(tcPDPtr particle) const;
  // Return true if canHandleParticle() and if the corresponding
  // method for remnantHandler() returns true.

  virtual cPDVector partons(tcPDPtr particle) const = 0;
  // Return the partons which this PDF may extract from the given
  // particle.

  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
  virtual double xfx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double x, double eps = 0.0,
		     Energy2 particleScale = 0.0*GeV2) const;
  // Return the true pdf for the given parameters, with the momentum
  // fraction given as l=log(1/x) and simply x respectively.

  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
  virtual double xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		      double x, double eps = 0.0,
		      Energy2 particleScale = 0.0*GeV2) const;
  // Return the the valens part of the true pdf for the given
  // parameters, with the momentum fraction given as l=log(1/x) and
  // simply x respectively. If not overidden by a sub class this will
  // return zero.

  inline tcRemHPtr remnantHandler() const;
  // Pointer to the remnant handler to handle remnant when extracting
  // partons according to these densities.

  virtual double flattenL(tcPDPtr particle, tcPDPtr parton, const PDFCuts &,
			  double z, double & jacobian) const;
  // If the PDF contains strange peaks which can be difficult to
  // handle, this function may be overwritten to return an appropriate
  // l=log(1/x) for a z given by a flat distribution in ]0,1[. Also
  // the jacobobian of the l -> z variable transformation must
  // multiply the jacobian argument. The default version will simply
  // use the function l(z) = lmin + z*(lmax-lmin).

  virtual Energy2 flattenScale(tcPDPtr particle, tcPDPtr parton,
			       const PDFCuts &, double l, double z,
			       Energy2 & jacobian) const;
  // If the PDF contains strange peaks which can be difficult to
  // handle, this function may be overwritten to return an appropriate
  // scale Q2 for a z given by a flat distribution in ]0,1[. Also the
  // jacobobian of the l -> z variable transformation must multiply
  // the jacobian argument. The default version will simply use the
  // function Q2 = Q2min*(Q2max/Q2min)^z or, if Q2min is zero, Q2 =
  // z*Q2max.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

protected:

  RemHPtr theRemnantHandler;
  // A remnant handler which can generate remnants for the parton
  // extracted withfor this PDF

protected:

  enum RangeException { rangeFreeze, rangeZero, rangeThrow };
  RangeException rangeException;
  // Indicate to subclasses how to deal with x and Q2 which are out of
  // range.
private:

  static AbstractClassDescription<PDFBase> initPDFBase;

  PDFBase & operator=(const PDFBase &);
  //  Private and non-existent assignment operator.

};

ThePEG_DECLARE_CLASS_TRAITS(PDFBase,HandlerBase);

}

#include "PDFBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PDFBase.tcc"
#endif

#endif /* ThePEG_PDFBase_H */
