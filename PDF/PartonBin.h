// -*- C++ -*-
#ifndef ThePEG_PartonBin_H
#define ThePEG_PartonBin_H
//
// This is the declaration of the <!id>PartonBin<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>PartonBin<!!id> class is used py the
// <!class>PartonExtractor<!!class> class to store information about
// the extraction of a prton from a particle.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PartonExtractor.html">PartonExtractor.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/PDF/PDFBase.h"
#include "ThePEG/PDF/PDFCuts.h"
#include "ThePEG/CLHEPWrap/Transverse.h"
#include "ThePEG/EventRecord/Particle.h"
// #include "PartonBin.fh"
// #include "PartonBin.xh"

namespace ThePEG {

class PartonBin: public Base {

public:

typedef vector<PBPtr> PBVector;

public:

  PartonBin(tcPDPtr p, tPBPtr prev, tcPDPtr pi, tcPDFPtr pdf,
	    const PDFCuts & newCuts);
  // Standard ctors and dtor.

  PartonBin();
  PartonBin(const PartonBin &);
  virtual ~PartonBin();
  // Default ctors and dtor.

public:

  inline tcPDPtr particle() const;
  // The incoming particle type.

  inline tPBPtr incoming() const;
  // In the case the incoming particle in turn is extracted from
  // another particle, return the PartonBin for that extraction.

  inline const PBVector & outgoing() const;
  // The parton bins corresponding to the extracted parton if it can
  // be extracted from.

  inline void addOutgoing(tPBPtr);
  // Add a parton bin corresponding to the extracted parton if it can
  // be extracted from.

  inline tcPDPtr parton() const;
  // The extracted parton type.

  inline tcPDFPtr pdf() const;
  // The PDFBase object describing the momentum distribution of the
  // parton within the particle in this PartonBin.

  inline tcRemHPtr remnantHandler() const;
  // The remnant handler associated with the pdf().

  int nDim(bool doscale);
  // Detemine the number of degrees of freedom needed to generate the
  // phase space of this and parent partons. If doscale is true this
  // bin is expected to generate the scale in addition to l.

  inline int pdfDim() const;
  inline int remDim() const;
  // Return the number of degrees of freedom used by the parton
  // density and remnant handler.

  void prepare();
  // Reset last generated l and Q2 values of this and parent bins.

  void generate(const double * r);
  // Generate l and Q2 of this and parent bins.

  inline const PDFCuts & cuts() const;
  // Return the cuts specified for this bin.

  double fullFn(Energy2 newScale = -GeV2);
  // Return the parton density for this and parent particles. If the
  // argument is positive, this scale should be used.

  tPBPtr getFirst();
  // Return the parton bin corresponding to the first incoming particle.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  cPDPtr theParticle;
  // The incoming particle type.

  tPBPtr theIncomingBin;
  // In the case the incoming particle in turn is extracted from
  // another particle, return the PartonBin for that extraction.

  PBVector theOutgoing;
  // The parton bins corresponding to the extracted parton if it can
  // be extracted from.

  cPDPtr theParton;
  // The extracted parton type.

  cPDFPtr thePDF;
  // The PDFBase object describing the momentum distribution of the
  // parton within the particle in this PartonBin.

  cRemHPtr theRemnantHandler;
  // The remnant handler associated with the pdf().

  int thePDFDim;
  int theRemDim;
  // The number of degrees of freedom needed to generate the phase
  // space for this parton for the parton density and remnant handler
  // respectively.

  PDFCuts theCuts;
  // The cuts specified for this bin.

private:

  static ClassDescription<PartonBin> initPartonBin;

  PartonBin & operator=(const PartonBin &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<PartonBin,1> {
  typedef Base NthBase;
};

template <>
struct ClassTraits<PartonBin>: public ClassTraitsBase<PartonBin> {
  static string className() { return "/ThePEG/PartonBin"; }
};

}

#include "PartonBin.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBin.tcc"
#endif

#endif /* ThePEG_PartonBin_H */
