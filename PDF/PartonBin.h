// -*- C++ -*-
#ifndef ThePEG_PartonBin_H
#define ThePEG_PartonBin_H
// This is the declaration of the PartonBin class.

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

/**
 * The PartonBin class is used py the PartonExtractor class to store
 * information about the extraction of a parton from a
 * particle. Several PartonBin objects can be used to specify a whole
 * chain of partons extracted from particles extracted from other
 * particles. A PartonBin without an incoming() PartonBin represents
 * the incoming particle itself and is used to stop recursion.
 *
 * After the extraction of a parton, the kinematical variables of that
 * extraction is stored in a orresponding PartonBinInfo object.
 *
 * @see PartonExtractor.
 * 
 */
class PartonBin: public Base {

public:

typedef vector<PBPtr> PBVector;

public:

  /** @name Standard constructors, assignment and destructors. */
  //@{
  /**
   * Standard constructor.

   * @param p the incoming particle type. Possibly null if this bin
   * represents the incoming particle itself.
   * @param prev the PartonBin of the incoming particle. Possibly null
   * if this bin represents the incoming particle itself.
   * @param pi the parton to be extracted.
   * @param pdf the density function to be used. Possibly null if this
   * bin represents the incoming particle itself.
   * @param newCuts the kinematical cuts on the extraction.
   */
  PartonBin(tcPDPtr p, tPBPtr prev, tcPDPtr pi, tcPDFPtr pdf,
	    const PDFCuts & newCuts);

  /**
   * Default constructor.
   */
  PartonBin();

  /**
   * Copy-constructor.
   */
  PartonBin(const PartonBin &);

  /**
   * Destructor.
   */
  virtual ~PartonBin();
  //@}

public:

  /** @name Access the information in this ParticleBin. */
  //@{
  /**
   * The incoming particle type.
   */
  inline tcPDPtr particle() const;

  /**
   * In the case the incoming particle in turn is extracted from
   * another particle, return the PartonBin for that extraction.
   */
  inline tPBPtr incoming() const;

  /**
   * The parton bins corresponding to the extracted parton if it in
   * turn can be extracted from.
   */
  inline const PBVector & outgoing() const;

  /**
   * Add a parton bin corresponding to the extracted parton if it in
   * turn can be extracted from.
   */
  inline void addOutgoing(tPBPtr);

  /**
   * The extracted parton type.
   */
  inline tcPDPtr parton() const;

  /**
   * The PDFBase object describing the momentum distribution of the
   * parton within the particle in this PartonBin.
   */
  inline tcPDFPtr pdf() const;

  /**
   * The remnant handler associated with the pdf().
   */
  inline tcRemHPtr remnantHandler() const;

  /**
   * Detemine the number of degrees of freedom needed to generate the
   * phase space of this and parent partons. If doscale is true this
   * bin is expected to generate the scale in addition to the momentum
   * fraction.
   */
  int nDim(bool doscale);

  /**
   * Return the number of degrees of freedom used by the parton
   * density and remnant handler.
   */
  inline int pdfDim() const;

  /**
   * Return the number of degrees of freedom used by the parton
   * density and remnant handler.
   */
  inline int remDim() const;
  //@}

  /** @name Functions used in the generation. */
  //@{
  /**
   * Reset last generated l and Q2 values of this and parent bins.
   */
  void prepare();

  /**
   * Generate l and Q2 of this and parent bins.
   */
  void generate(const double * r);

  /**
   * Return the cuts specified for this bin.
   */
  inline const PDFCuts & cuts() const;

  /**
   * Return the parton density for this and parent particles. If the
   * argument is positive, this scale should be used.
   */
  double fullFn(Energy2 newScale = -1.0*GeV2);

  /**
   * Return the parton bin corresponding to the first incoming particle.
   */
  tPBPtr getFirst();
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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * The incoming particle type.
   */
  cPDPtr theParticle;

  /**
   * In the case the incoming particle in turn is extracted from
   * another particle, return the PartonBin for that extraction.
   */
  tPBPtr theIncomingBin;

  /**
   * The parton bins corresponding to the extracted parton if it
   * itself can be extracted from.
   */
  PBVector theOutgoing;

  /**
   * The extracted parton type.
   */
  cPDPtr theParton;

  /**
   * The PDFBase object describing the momentum distribution of the
   * parton within the particle in this PartonBin.
   */
  cPDFPtr thePDF;

  /**
   * The remnant handler associated with the pdf().
   */
  cRemHPtr theRemnantHandler;

  /**
   * The number of degrees of freedom needed to generate the phase
   * space for this parton for the parton density.
   */
  int thePDFDim;

  /**
   * The number of degrees of freedom needed to generate the phase
   * space for this parton for the remnant handler.
   */
  int theRemDim;

  /**
   * The cuts specified for this bin.
   */
  PDFCuts theCuts;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<PartonBin> initPartonBin;

  /**
   *  Private and non-existent assignment operator.
   */
  PartonBin & operator=(const PartonBin &);

};

/** This template specialization informs ThePEG about the base classes
 *  of PartonBin. */
template <>
struct BaseClassTrait<PartonBin,1> {
  /** Typedef of the first base class of PartonBin. */
  typedef Base NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  PartonBin class. */
template <>
struct ClassTraits<PartonBin>: public ClassTraitsBase<PartonBin> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::PartonBin"; }
};

}

#include "PartonBin.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonBin.tcc"
#endif

#endif /* ThePEG_PartonBin_H */
