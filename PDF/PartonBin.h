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

class PartonBinInfo;
class RemnantInfo;

class PartonBin: public Base {

public:

typedef vector<tPBPtr> tPBVector;

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

  inline const tPBVector & outgoing() const;
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

  void reset(double l = 0, Energy2 Q2 = 0.0*GeV2);
  // Reset the current PartonBin, making room for a new event.

  inline tPPtr lastParticle() const;
  // The current particle instance.

  inline tPPtr lastParton() const;
  // The current parton instance.

  inline const ParticleVector & lastRemnants() const;
  // The current remnants.

  inline const TransverseMomentum & kT() const;
  // Return the transverse momentum of the extracted parton.

  inline Energy2 remnantMass2() const;
  // Return the invariant mass squared of the remnants.

  inline const ParticleVector & lastPartons() const;
  // The currently extracted partons (in case of multiple
  // interactions.

  inline double lastPartialL() const;
  inline void lastPartialL(double);
  // Get/set the (log) fraction of the current particle momenta taken
  // by the current parton.

  inline double lastPartialX() const;
  inline double lastPartialEps() const;
  // Get/set the fraction x (eps = 1-x) of the current particle
  // momenta taken by the current parton.

  inline double lastL() const;
  inline void lastL(double);
  // Get/set lastPartialL() plus the momentum fraction of the incoming
  // particle in case it in turn was extracted from another.

  inline void shift(double);
  inline double shift() const;
  // Set/return the current shift in L due to the remnant extraction.

  void setRemnants(Energy2 sMax, const PVector & prev = PVector());
  // Set information about the current (or rather future) remnants.

  void setRemnantMomenta(const LorentzMomentum &,
			 const PVector & prev = PVector());
  // Produce the actual remnants from the pre-remnants and set their
  // momenta.

  void resetRemnantMomenta(const LorentzMomentum &);
  // Change the momenta of the remnants.

  inline Energy2 lastScale() const;
  inline void lastScale(Energy2);
  // Get/set the scale at which the current parton was extracted.

  inline double lastWeight() const;
  // The current weight (true/approximate parton density).

  inline void lastParticle(tPPtr);
  inline void lastParton(tPPtr);
  // Set the current particle/parton instances

  inline PVector & lastRemnants();
  inline void lastRemnants(const PVector &);
  // The current remnants.

  inline PVector & lastPartons();
  // The currently extracted partons (in case of multiple
  // interactions.

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

  inline double lastJacobian() const;
  inline void lastJacobian(double);
  // Get/set the last jacobian associated with the phase space point
  // generated.

  inline double remnantWeight() const;
  inline void remnantWeight(double);
  // Get/set the last weight associated with the remnant generation.

  inline RemnantInfo * remnantInfo() const;
  inline void remnantInfo(RemnantInfo *);
  // Get/set information saved by the remnant handler from the
  // generation, to be used in the construction of the remnants. (In
  // addition the remnantWeight and lastRemnants() may be used for this
  // purpose.)

  PartonBinInfo * createInfo() const;
  void setInfo(PartonBinInfo *, tPPtr inc);
  // Create/set an object where information is stored which may differ
  // between different sub processes in the same bin.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  cPDPtr theParticle;
  // The incoming particle type.

  PBPtr theIncomingBin;
  // In the case the incoming particle in turn is extracted from
  // another particle, return the PartonBin for that extraction.

  tPBVector theOutgoing;
  // The parton bins corresponding to the extracted parton if it can
  // be extracted from.

  cPDPtr theParton;
  // The extracted parton type.

  cPDFPtr thePDF;
  // The PDFBase object describing the momentum distribution of the
  // parton within the particle in this PartonBin.

  cRemHPtr theRemnantHandler;
  // The remnant handler associated with the pdf().

  double theLastPartialL;
  // The (log) fraction of the current particle momenta taken by the
  // current parton.

  mutable double theLastPartialX;
  mutable double theLastPartialEps;
  // The x and 1-x corresponding to the lastPartialL.

  double theLastL;
  // theLastPartialL plus the momentum fraction of the incoming
  // particle in case it in turn was extracted from another.

  Energy2 theLastScale;
  // The scale at which the current parton was extracted.

  int thePDFDim;
  int theRemDim;
  // The number of degrees of freedom needed to generate the phase
  // space for this parton for the parton density and remnant handler
  // respectively.

  double theLastJacobian;
  // The jacobian resulting form the last generation.

  RemnantInfo * theRemnantInfo;
  // Information saved by the remnant handler from the generation, to
  // be used in the construction of the remnants. (In addition the
  // remnantWeight and lastRemnants() may be used for ths purpose.)

  PartonBinInfo * info;
  // Pointer to an object where information is stored which may differ
  // between different sub processes in the same bin.

  PDFCuts theCuts;
  // The cuts specified for this bin.

private:

  static ClassDescription<PartonBin> initPartonBin;

  PartonBin & operator=(const PartonBin &);
  //  Private and non-existent assignment operator.

};

struct RemnantInfo {
  virtual ~RemnantInfo() {}
};

struct PartonBinInfo {

  PartonBinInfo()
    : lastScale(0.0*GeV2), remnantWeight(0.0), remnantInfo(0), incoming(0) {}
  ~PartonBinInfo() {
    if ( incoming ) delete incoming;
    if ( remnantInfo ) delete remnantInfo;
  }

  PPtr lastParticle;
  PPtr lastParton;
  PVector lastRemnants;
  PVector lastPartons;
  Energy2 lastScale;
  double remnantWeight;
  RemnantInfo * remnantInfo;

  PartonBinInfo * incoming;

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
