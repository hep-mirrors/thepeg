// -*- C++ -*-
#ifndef THEPEG_PartonBinInstance_H
#define THEPEG_PartonBinInstance_H
//
// This is the declaration of the <!id>PartonBinInstance<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/PDF/PartonBin.h"
// #include "PartonBinInstance.fh"
// #include "PartonBinInstance.xh"

namespace ThePEG {

ThePEG_DECLARE_CLASS_POINTERS(PartonBinInstance,PBIPtr);
typedef pair<PBIPtr,PBIPtr> PBIPair;

ThePEG_DECLARE_CLASS_POINTERS(RemInfoBase,RemIPtr);

class PartonBinInstance: public PersistentBase {

public:

  PartonBinInstance();
  PartonBinInstance(const PartonBinInstance &);
  virtual ~PartonBinInstance();
  // Standard ctors and dtor.

  PartonBinInstance(tcPBPtr, tPBIPtr = tPBIPtr());
  // Constructor taking a parton bin as argument. The second argument
  // should be used if the incoming bin is already known and exists.

public:

  inline tcPBPtr bin() const;
  // Return a pointer to the bin this instance refer to.

  inline const PartonVector & bins() const;
  // Return a pointer to the bin this instance refer to.

  inline tcPDPtr particleData() const;
  // Return a pointer to the data object of the incoming particle.

  inline tcPDPtr partonData() const;
  // Return a pointer to the data object of the extracted parton.

  inline tPBIPtr incoming() const;
  // In the case the incoming particle in turn is extracted from
  // another particle, return the PartonBinInstance for that
  // extraction.

  tPBIPtr getFirst();
  // Return the parton bin instance corresponding to the first
  // incoming particle for this bin.

  inline tcPDFPtr pdf() const;
  // The PDFBase object describing the momentum distribution of the
  // parton within the particle in this PartonBin.

  inline tcRemHPtr remnantHandler() const;
  // The remnant handler associated with the pdf().

  void reset(double lx = 0, Energy2 Q2 = 0.0*GeV2);
  // Reset the current PartonBin, making room for a new event.

  void prepare();
  // Reset last generated l and Q2 values of this and parent bins.

  void generate(const double * r);
  // Generate l and Q2 of this and parent bins.

  double fullFn(Energy2 newScale = -GeV2);
  // Return the parton density for this and parent particles. If the
  // argument is positive, this scale should be used.

  inline double jacobian() const;
  inline void jacobian(double);
  // Get/set the jacobian associated with the phase space point
  // generated.

  inline tPPtr particle() const;
  inline void particle(tPPtr);
  // Get/set the current particle instance.

  inline tPPtr parton() const;
  inline void parton(tPPtr);
  // Get/set the current parton instance.

  inline const PVector & partons() const;
  // The currently extracted partons (in case of multiple
  // interactions.

  inline double xi() const;
  inline double eps() const;
  inline double li() const;
  inline void li(double);
  // Get/set the momentum fraction (xi, li=log(xi), eps=1-xi), of this
  // parton w.r.t. the incoming particle in this
  // bin.

  inline double x() const;
  inline double l() const;
  inline void l(double);
  // Get/set the momentum fraction (x, l=log(x)) of this parton
  // w.r.t. the collidig particles.

  inline Energy2 scale() const;
  inline void scale(Energy2);
  // Get/set the scale at which the current parton was extracted.

  inline const TransverseMomentum & kT() const;
  // Return the transverse momentum of the extracted parton.

  inline double remnantWeight() const;
  inline void remnantWeight(double);
  // Get/set the weight associated with the remnant generation.

  inline const PVector & remnants() const;
  inline void remnants(const PVector &);
  // The current remnants.

  inline tRemIPtr remnantInfo() const;
  inline void remnantInfo(tRemIPtr);
  // Get/set information saved by the remnant handler from the
  // generation, to be used in the construction of the remnants. (In
  // addition the remnantWeight and remnants() may be used for this
  // purpose.)

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

private:

  cPBPtr theBin;
  // Pointer to the main bin this instance refer to.

  PartonVector theBins;
  // Pointer to the main bin (and secondary in case several partons
  // have been extracted this instance refer to.

  PBIPtr theIncoming;
  // In the case the incoming particle in turn is extracted from
  // another particle, this is the PartonBinInstance for that
  // extraction.

  double theJacobian;
  // The jacobian associated with the phase space point generated.

  PPtr theParticle;
  // The current particle instance.

  PPtr theParton;
  // The current parton instance.

  PVector thePartons;
  // The currently extracted partons (in case of multiple
  // interactions.

  mutable double theXi;
  mutable double theEps;
  double theLi;
  // The momentum fraction (xi, li=log(xi), eps=1-xi), of this
  // parton w.r.t. the incoming particle in this
  // bin.

  mutable double theX;
  double theL;
  // The momentum fraction (x, l=log(x)) of this parton
  // w.r.t. the collidig particles.

  Energy2 theScale;
  // The scale at which the current parton was extracted.

  TransverseMomentum theKT;
  // The transverse momentum of the extracted parton.

  double theRemnantWeight;
  // The weight associated with the remnant generation.

  PVector theRemnants;
  // The current remnants.

  RemIPtr theRemInfo;
  // The information saved by the remnant handler from the generation,
  // to be used in the construction of the remnants. (In addition the
  // remnantWeight and lastRemnants() may be used for this purpose.)

private:

  static ClassDescription<PartonBinInstance> initPartonBinInstance;
  // Describe a concrete class with persistent data.

  PartonBinInstance & operator=(const PartonBinInstance &);
  // Private and non-existent assignment operator.

};

struct RemInfoBase: public Base {
  virtual ~RemInfoBase() {}
};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of PartonBinInstance.
template <>
struct BaseClassTrait<PartonBinInstance,1> {
  typedef Base NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<PartonBinInstance>: public ClassTraitsBase<PartonBinInstance> {
  static string className() { return "/ThePEG/PartonBinInstance"; }
  // Return the class name.
};

}

#include "PartonBinInstance.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBinInstance.tcc"
#endif

#endif /* THEPEG_PartonBinInstance_H */
