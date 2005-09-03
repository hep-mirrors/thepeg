// -*- C++ -*-
#ifndef THEPEG_PartonBinInstance_H
#define THEPEG_PartonBinInstance_H
// This is the declaration of the PartonBinInstance class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/PDF/PartonBin.h"
// #include "PartonBinInstance.fh"
// #include "PartonBinInstance.xh"

namespace ThePEG {

ThePEG_DECLARE_CLASS_POINTERS(PartonBinInstance,PBIPtr);
/** A pair of pointers to PartonBinInstance objects. */
typedef pair<PBIPtr,PBIPtr> PBIPair;

ThePEG_DECLARE_CLASS_POINTERS(RemInfoBase,RemIPtr);

/**
 * PartonBinInstance is used to store information about the generation
 * of a given parton extraction for a corresponding PartonBin object.
 */
class PartonBinInstance: public PersistentBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PartonBinInstance();

  /**
   * Copy-constructor.
   */
  PartonBinInstance(const PartonBinInstance &);

  /**
   * Destructor.
   */
  virtual ~PartonBinInstance();

  /**
   * Constructor taking a PartonBin as argument. The second argument
   * should be used if the incoming bin is already known and exists.
   */
  PartonBinInstance(tcPBPtr, tPBIPtr = tPBIPtr());

  /**
   * Constructor using an already prepared extracted parton. This will
   * also initialize the x, and scale values. To calculate the
   * momentum fractions, a Direction<0> object must have been properly
   * initialized.
   *
   * @param parton the extracted parton which must have its first
   * parent set to define the particle extracted from.
   *
   * @param pb the PartonBin object corresponding to the extracted \a
   * parton. If the particle extracted from in turn has been
   * extracted, the incoming() member of the PartonBin must point to
   * the corresponding PartonBin.
   *
   * @param scale the resolution scale at which the \a parton was
   * extracted.
   */
  PartonBinInstance(tPPtr parton, tcPBPtr pb, Energy2 scale = 0.0*GeV2);

  //@}

public:

  /** @name Access information about the corresponding PartonBin object. */
  //@{
  /**
   * Return a pointer to the PartonBin this instance refer to.
   */
  inline tcPBPtr bin() const;

  /**
   * Return pointers to the bins this instance refer to in case more
   * than one parton has been extracted.
   */
  inline const PartonVector & bins() const;

  /**
   * Return a pointer to the data object of the incoming particle.
   */
  inline tcPDPtr particleData() const;

  /**
   * Return a pointer to the data object of the extracted parton.
   */
  inline tcPDPtr partonData() const;

  /**
   * In the case the incoming particle in turn is extracted from
   * another particle, return the PartonBinInstance for that
   * extraction.
   */
  inline tPBIPtr incoming() const;

  /**
   * Return the parton bin instance corresponding to the first
   * incoming particle for this bin.
   */
  tPBIPtr getFirst();

  /**
   * The PDFBase object describing the momentum distribution of the
   * parton within the particle in this PartonBin.
   */
  inline tcPDFPtr pdf() const;

  /**
   * The remnant handler associated with the pdf().
   */
  inline tcRemHPtr remnantHandler() const;
  //@}

  /** @name Functions used for the generation. */
  //@{
  /**
   * Reset the current PartonBin, making room for a new event.
   */
  void reset(double lx = 0, Energy2 Q2 = 0.0*GeV2);

  /**
   * Reset last generated l and Q2 values of this and parent bins.
   */
  void prepare();

  /**
   * Generate l and Q2 of this and parent bins.
   */
  void generate(const double * r);

  /**
   * Return the parton density for this and parent particles. If the
   * argument is positive, this scale should be used.
   */
  double fullFn(Energy2 newScale = -GeV2);

  /**
   * Get the jacobian associated with the phase space point generated.
   */
  inline double jacobian() const;

  /**
   * Set the jacobian associated with the phase space point generated.
   */
  inline void jacobian(double);
  //@}

  /** @name Access information about the generated extraction. */
  //@{
  /**
   * Get the current particle instance.
   */
  inline tPPtr particle() const;

  /**
   * Set the current particle instance.
   */
  inline void particle(tPPtr);

  /**
   * Get the current parton instance.
   */
  inline tPPtr parton() const;

  /**
   * Set the current parton instance.
   */
  inline void parton(tPPtr);

  /**
   * The currently extracted partons (in case of multiple
   * interactions.
   */
  inline const PVector & partons() const;

  /**
   * Get the momentum fraction of this parton w.r.t. the incoming
   * particle in this bin.
   */
  inline double xi() const;

  /**
   * Get one minus the momentum fraction of this parton w.r.t. the
   * incoming particle in this bin.
   */
  inline double eps() const;

  /**
   * Get the logarithmic momentum fraction of this parton w.r.t. the
   * incoming particle in this bin.
   */
  inline double li() const;

  /**
   * Set the logarithmic momentum fraction of this parton w.r.t. the
   * incoming particle in this bin.
   */
  inline void li(double);

  /**
   * Get the momentum fraction of this parton w.r.t. the collidig
   * particles.
   */
  inline double x() const;

  /**
   * Get the logarithmic momentum fraction of this parton w.r.t. the
   * collidig particles.
   */
  inline double l() const;

  /**
   * Set the logarithmic momentum fraction of this parton w.r.t. the
   * collidig particles.
   */
  inline void l(double);

  /**
   * Get the scale at which the current parton was extracted.
   */
  inline Energy2 scale() const;

  /**
   * Set the scale at which the current parton was extracted.
   */
  inline void scale(Energy2);

  /**
   * Return the transverse momentum of the extracted parton.
   */
  inline const TransverseMomentum & kT() const;

  /**
   * Get the weight associated with the remnant generation.
   */
  inline double remnantWeight() const;

  /**
   * Set the weight associated with the remnant generation.
   */
  inline void remnantWeight(double);

  /**
   * Get the current remnants.
   */
  inline const PVector & remnants() const;

  /**
   * Set the current remnants.
   */
  inline void remnants(const PVector &);

  /**
   * Get information saved by the remnant handler from the generation,
   * to be used in the construction of the remnants. (In addition the
   * remnantWeight and remnants() may be used for this purpose.)
   */
  inline tRemIPtr remnantInfo() const;

  /**
   * Set information saved by the remnant handler from the generation,
   * to be used in the construction of the remnants. (In addition the
   * remnantWeight and remnants() may be used for this purpose.)
   */
  inline void remnantInfo(tRemIPtr);
  //@}

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

private:

  /**
   * Pointer to the main bin this instance refer to.
   */
  cPBPtr theBin;

  /**
   * Pointer to the main bin (and secondary in case several partons
   * have been extracted this instance refer to.
   */
  PartonVector theBins;

  /**
   * In the case the incoming particle in turn is extracted from
   * another particle, this is the PartonBinInstance for that
   * extraction.
   */
  PBIPtr theIncoming;

  /**
   * The jacobian associated with the phase space point generated.
   */
  double theJacobian;

  /**
   * The current particle instance.
   */
  PPtr theParticle;

  /**
   * The current parton instance.
   */
  PPtr theParton;

  /**
   * The currently extracted partons (in case of multiple
   * interactions.
   */
  PVector thePartons;

  /**
   * The momentum fraction (xi, li=log(xi), eps=1-xi), of this
   * parton w.r.t. the incoming particle in this
   * bin.
   */
  mutable double theXi;
  /**
   * The momentum fraction (xi, li=log(xi), eps=1-xi), of this
   * parton w.r.t. the incoming particle in this
   * bin.
   */
  mutable double theEps;
  /**
   * The momentum fraction (xi, li=log(xi), eps=1-xi), of this
   * parton w.r.t. the incoming particle in this
   * bin.
   */
  double theLi;

  /**
   * The momentum fraction (x, l=log(x)) of this parton
   * w.r.t. the collidig particles.
   */
  mutable double theX;
  /**
   * The momentum fraction (x, l=log(x)) of this parton
   * w.r.t. the collidig particles.
   */
  double theL;

  /**
   * The scale at which the current parton was extracted.
   */
  Energy2 theScale;

  /**
   * The transverse momentum of the extracted parton.
   */
  TransverseMomentum theKT;

  /**
   * The weight associated with the remnant generation.
   */
  double theRemnantWeight;

  /**
   * The current remnants.
   */
  PVector theRemnants;

  /**
   * The information saved by the remnant handler from the generation,
   * to be used in the construction of the remnants. (In addition the
   * remnantWeight and lastRemnants() may be used for this purpose.)
   */
  RemIPtr theRemInfo;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<PartonBinInstance> initPartonBinInstance;

  /**
   * Private and non-existent assignment operator.
   */
  PartonBinInstance & operator=(const PartonBinInstance &);

};

/** Empty base class. A RemnantHandler may use sub-classes to store
    information about the generation of remnants. */
struct RemInfoBase: public Base {
  /** The descructor. */
  virtual ~RemInfoBase() {}
};

}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of PartonBinInstance. */
template <>
struct BaseClassTrait<PartonBinInstance,1>: public ClassTraitsType {
  /** Typedef of the first base class of PartonBinInstance. */
  typedef Base NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  PartonBinInstance class. */
template <>
struct ClassTraits<PartonBinInstance>:
    public ClassTraitsBase<PartonBinInstance> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::PartonBinInstance"; }
};

/** @endcond */

}

#include "PartonBinInstance.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBinInstance.tcc"
#endif

#endif /* THEPEG_PartonBinInstance_H */
