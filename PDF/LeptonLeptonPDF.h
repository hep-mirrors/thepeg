// -*- C++ -*-
#ifndef ThePEG_LeptonLeptonPDF_H
#define ThePEG_LeptonLeptonPDF_H
//
// This is the declaration of the <!id>LeptonLeptonPDF<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>LeptonLeptonPDF<!!id> inherits from <!class>PDFBase<!!class>
// and encodes the distribution of leptons within leptons, ie. the
// energy loss of leptons due to radiation of soft photons..
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PDFBase.html">PDFBase.h</a>.
// 

#include "ThePEG/PDF/PDFBase.h"
// #include "LeptonLeptonPDF.fh"
// #include "LeptonLeptonPDF.xh"

namespace ThePEG {

class LeptonLeptonPDF: public PDFBase {

public:

  inline LeptonLeptonPDF();
  inline LeptonLeptonPDF(const LeptonLeptonPDF &);
  virtual ~LeptonLeptonPDF();
  // Standard ctors and dtor

public:

  virtual bool canHandleParticle(tcPDPtr particle) const;
  // Return true if this PDF can handle the extraction of parton from the
  // given particle ie. if the particle is a lepton.

  virtual cPDVector partons(tcPDPtr p) const;
  // Return a vector of partons handled by this PDF (always the same
  // lepton as the incoming particle).

  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
  // Return the value of the density function at a given l=log(1/x)
  // and scale for the given parton.

  virtual double xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
  // Return the the valens part of the true pdf for the given
  // parameters, with the momentum fraction given as l=log(1/x). This
  // version simply returns the full pdf.

  virtual double xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		      double x, double eps, Energy2 particleScale) const;
  // Return the the valens part of the true pdf for the given
  // parameters, with the momentum fraction given as x. This
  // version simply returns the full pdf.

  virtual double flattenL(tcPDPtr particle, tcPDPtr parton, const PDFCuts &,
			  double z, double & jacobian) const;
  // If the PDF contains strange peaks which can be difficult to
  // handle, this function may be overwritten to return an appropriate
  // l=log(1/x) for a z given by a flat distribution in ]0,1[. Also
  // the jacobobian of the l(z) function must be returned. The default
  // version will simly use the function l(z) = lmin + z*(lmax-lmin).

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static NoPIOClassDescription<LeptonLeptonPDF> initLeptonLeptonPDF;

  LeptonLeptonPDF & operator=(const LeptonLeptonPDF &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<LeptonLeptonPDF,1> {
  typedef PDFBase NthBase;
};

template <>
struct ClassTraits<LeptonLeptonPDF>: public ClassTraitsBase<LeptonLeptonPDF> {
  static string className() { return "/ThePEG/LeptonLeptonPDF"; }
  static string library() { return "LeptonLeptonPDF.so"; }
};

}

#include "LeptonLeptonPDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LeptonLeptonPDF.tcc"
#endif

#endif /* ThePEG_LeptonLeptonPDF_H */
