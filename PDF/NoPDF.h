// -*- C++ -*-
#ifndef ThePEG_NoPDF_H
#define ThePEG_NoPDF_H
//
// This is the declaration of the <!id>NoPDF<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>NoPDF<!!id> inherits from <!class>PDFBase<!!class> and
// represents particles without sub-structure. Theonly parton which
// can be extracted is the incoming particle itself with a momentum
// distribution which is a delta-function at x=1 (l=0).
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PDFBase.html">PDFBase.h</a>
// 

#include "ThePEG/PDF/PDFBase.h"
// #include "NoPDF.fh"
// #include "NoPDF.xh"

namespace ThePEG {

class NoPDF: public PDFBase {

public:

  inline NoPDF();
  inline NoPDF(const NoPDF &);
  virtual ~NoPDF();
  // Standard ctors and dtor

public:

  virtual bool canHandleParticle(tcPDPtr particle) const;
  // Return true because we can handle any particle.

  virtual bool canHandle(tcPDPtr particle) const;
  // Return true if canHandleParticle() and if the corresponding
  // method for remnantHandler() returns true.

  virtual cPDVector partons(tcPDPtr p) const;
  // Simply return the particle.

  virtual double xfl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale = 0.0*GeV2) const;
  // The delta function.

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

  static NoPIOClassDescription<NoPDF> initNoPDF;

  NoPDF & operator=(const NoPDF &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<NoPDF,1> {
  typedef PDFBase NthBase;
};

template <>
struct ClassTraits<NoPDF>: public ClassTraitsBase<NoPDF> {
  static string className() { return "/ThePEG/NoPDF"; }
};

}

#include "NoPDF.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoPDF.tcc"
#endif

#endif /* ThePEG_NoPDF_H */
