// -*- C++ -*-
#ifndef ThePEG_PartonExtractor_H
#define ThePEG_PartonExtractor_H
// This is the declaration of the PartonExtractor class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/PDF/PDFBase.h"
#include "ThePEG/PDT/ParticleData.h"
// #include "PartonExtractor.fh"
#include "PartonExtractor.xh"

namespace ThePEG {

/**
 * The PartonExtractor is a base class defining the interface to
 * objects responsible for extracting partons from particles. It is
 * used by a SubProcessHandler which combines one PartonExtractor with
 * a number of MEBase objects which are the used in an XComb in a
 * CollisionHandler to generate hard sub-processes.
 *
 * PartonExtractor inherits from the general HandlerBase class and
 * from the LastXCombInfo class to have easy acces to information
 * about the currently chosen hard sub-process.
 *
 *
 * @see SubProcessHandler,
 * @see MEBase,
 * @see CollisionHandler,
 * @see XComb,
 * @see HandlerBase.
 * 
 */
class PartonExtractor: public HandlerBase, public LastXCombInfo<> {

  /** CollisionHandler is a friend. */
  friend class CollisionHandler;
  /** XComb is a friend. */
  friend class XComb;

public:

  /** A map of PartonBinInstance objects indexed by the extracted parton. */
  typedef map<cPPtr,PBIPtr> PartonBinInstanceMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  PartonExtractor();

  /**
   * Copy-constructor.
   */
  PartonExtractor(const PartonExtractor &);

  /**
   * Destructor.
   */
  virtual ~PartonExtractor();
  //@}

public:

  /** @name Virtual functions which may be overridden in sub-classes. */
  //@{
  /**
   * Return true if this parton extractor can handle the given types
   * of incoming particles.
   */
  inline virtual bool canHandle(const cPDPair &);

  /**
   * Return a vector of possible pairs of parton bins which can be
   * produced within a given maximum total particle-particle
   * invariant mass squared, \a maxEnergy sBin.
   */
  virtual PartonPairVec getPartons(Energy maxEnergy, const cPDPair &,
				   const KinematicalCuts &) const;

  /**
   * May be overriden by sub-classes which have their own oppinion
   * about what scale to use in a hard subprocess. The default version
   * simply returns the previously selected scale.
   */
  virtual Energy2 newScale();

  /**
   * Connect the remnants with the colour lines of the extracted
   * parton.
   */
  virtual void colourConnect(tPPtr particle, tPPtr parton,
			     const tPVector & remnants) const;

  /**
   * If remnants has already been created for the given parton, remove
   * them from the given step and generate new remnants corresponding
   * to the parton newp and add them to the step. The new parton bins
   * are returned.
   */
  virtual PBIPair newRemnants(tPPair oldp, tPPair newp, tStepPtr step);

  /**
   * Determine the number of random numbers needed to calculate
   * \f$\hat{s}\f$ and the product of all densitiy functions.
   */
  virtual pair<int,int> nDims(const PBPair & pbins);

  /**
   * Prepare the given parton bin instances for generating a new
   * event.
   */
  virtual void prepare(const PBIPair & pbins);

  /**
   * Generate \f$l=\log(1/x)\f$ for all parton extractions.
   */
  virtual bool generateL(const PBIPair & pbins,
			 const double * r1, const double * r2);

  /**
   * Generate the rest of the degrees of freedom to calculate
   * \f$\hat{s}\f$ and the product of all densitiy functions.
   */
  virtual Energy2 generateSHat(Energy2 s, const PBIPair & pbins,
			       const double * r1, const double * r2);

  /**
   * Return the product of all density functions.
   */
  virtual double fullFn(const PBIPair & pbins, Energy2 scale);

  /**
   * Construct remnants and add them to the step.
   */
  virtual void construct(const PBIPair & pbins, tStepPtr step);
  //@}

  /** @name Access information about the current paron extraction. */
  //@{
  /**
   * Return the current parton bin instances.
   */
  inline const PartonBinInstanceMap & partonBinInstances() const;

  /**
   * Return the corresponding parton bin instance for a given
   * extracted parton.
   */
  tPBIPtr partonBinInstance(tcPPtr) const;
  //@}

  /**
   * The maximum number of attempts allowed when trying to generate
   * remnants.
   */
  inline int maxTries() const;

protected:

  /**
   * Used by generateL() for each of the final parton
   * bins. Direction<0> is set to positive(negative) for the
   * first(second) final bin.
   */
  virtual void generateL(PartonBinInstance & pb, const double * r);

  /**
   * Used by generateSHat() for each of the final parton
   * bins. Direction<0> is set to positive(negative) for the
   * first(second) final bin. Should ask the remnant handler to
   * generate what is needed to construct the extracted parton
   * momentum. Returns false if no remnants could be generated.
   */
  virtual bool generate(PartonBinInstance & pb, const double * r,
			const Lorentz5Momentum & first);

  /**
   * Used by the public fullFn() for each of the final parton bins.
   */
  virtual double fullFn(const PartonBinInstance & pb);

  /**
   * Used by the public construct() for each of the final parton bins.
   */
  virtual void construct(PartonBinInstance & pb, tStepPtr step);

  /**
   * Used by the public newRemnants() for each of the parton bins.
   */
  PBIPtr newRemnants(tPBIPtr oldpb, tPPtr newp);

  /**
   * Used by the public newRemnants() for each 0f the parton bins.
   */
  void addNewRemnants(tPBIPtr oldpb, tPBIPtr newpb, tStepPtr step);

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

  /**
   * Add parton bins to pbins for the given incoming particle and the
   * specified cuts.
   */
  virtual void addPartons(tPBPtr incoming ,const PDFCuts & cuts,
		  PartonVector & pbins) const;
  
  /**
   * Return the PDFBase object to be used for the incoming particle
   * type. If one of theSpecialDensities matches the particle type it
   * is returned, otherwise if particle is a BeamParticleData use the
   * PDFBase object specified there. If also this fails, return a
   * NoPDF object.
   */
  tcPDFPtr getPDF(tcPDPtr particle) const;

  /**
   * The NoPDF object.
   */
  inline tcPDFPtr noPDF() const;

  /**
   * The PartonBinInstance's used mapped to the respective partons.
   */
  inline PartonBinInstanceMap & partonBinInstances();

  /**
   * Connect the first (\a anti) coloured particle in the given range
   * (not equal to \a parton) and connect it to the colour \a line.
   */
  template <typename Iterator>
  inline void findConnect(tColinePtr line, tPPtr parton, bool anti,
			  Iterator first, Iterator last) const;

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
  //@}

private:

  /**
   * Set the XComb object describing the current hard sub-process.
   */
  void select(tXCombPtr newXComb);

private:

  /**
   * The PartonBinInstance's used mapped to the respective partons.
   */
  PartonBinInstanceMap thePartonBinInstances;

  /**
   * A list of special PDFBase objects to be used.
   */
  vector<PDFPtr> theSpecialDensities;

  /**
   * The NoPDF object.
   */
  PDFPtr theNoPDF;

  /**
   * The maximum number of tries allowed when trying to produce
   * remnants.
   */
  int theMaxTries;

  /**
   * True if this extractor should override the \f$l\f$-generation in
   * the PDFs and generate a flat distribution in \f$\log(\hat{s})\f$
   * and y.
   */
  bool flatSHatY;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<PartonExtractor> initPartonExtractor;

  /**
   *  Private and non-existent assignment operator.
   */
  PartonExtractor & operator=(const PartonExtractor &);

};

/** This template specialization informs ThePEG about the base classes
 *  of PartonExtractor. */
template <>
struct BaseClassTrait<PartonExtractor,1> {
  /** Typedef of the first base class of PartonExtractor. */
  typedef HandlerBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  PartonExtractor class. */
template <>
  /** Return a platform-independent class name */
struct ClassTraits<PartonExtractor>: public ClassTraitsBase<PartonExtractor> {
  static string className() { return "ThePEG::PartonExtractor"; }
};

}

#include "PartonExtractor.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonExtractor.tcc"
#endif

#endif /* ThePEG_PartonExtractor_H */
