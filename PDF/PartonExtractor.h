// -*- C++ -*-
#ifndef ThePEG_PartonExtractor_H
#define ThePEG_PartonExtractor_H
//
// This is the declaration of the <!id>PartonExtractor<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>PartonExtractor<!!id> is an abstract base class defining
// the interface to objects responsible for extracting partons from
// particles. It is used by a <!class>SubProcessHandler<!!class> which
// combines one <!id>PartonExtractor<!!id> with a number of
// <!class>PartonXSecFn<!!class>s which are the used by an
// <!class>XComb<!!class> in a <!class>CollisionHandler<!!class> to
// generate hard sub-processes.
//
// <!id>PartonExtractor<!!id> inherits from the general
// <!class>HandlerBase<!!class> class and from the LastXCombInfo class
// to have easy acces to information about the currently chosen hars
// sub-process.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>,
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>,
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>,
// <a href="http:XComb.html">XComb.h</a>,
// <a href="http:HandlerBase.html">HandlerBase.h</a>.
// 

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/Handlers/LastXCombInfo.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/PDF/PDFBase.h"
#include "ThePEG/PDT/ParticleData.h"
// #include "PartonExtractor.fh"
#include "PartonExtractor.xh"

namespace ThePEG {

class PartonExtractor: public HandlerBase, public LastXCombInfo<> {

  friend class CollisionHandler;
  friend class XComb;

public:

  typedef map<cPPtr,PBPtr, less<cPPtr>, Allocator<PBPtr> > PartonBinMap;
  typedef map<cPPtr,PBIPtr> PartonBinInstanceMap;

public:

  PartonExtractor();
  PartonExtractor(const PartonExtractor &);
  virtual ~PartonExtractor();
  // Standard ctors and dtor

public:

  inline virtual bool canHandle(const cPDPair &);
  // Return true if this parton extractor can handle the given types
  // of incoming particles.

  virtual PartonPairVec getPartons(Energy maxEnergy, const cPDPair &,
				   const KinematicalCuts &) const;
  // Return a vector of possible pairs of parton bins which can be
  // produced within a given interval in total particle-particle
  // invariant mass squared sBin, a given interval in total
  // parton-parton invariant mass squared sHatBin, for a given pair of
  // incoming particles.

  virtual Energy2 newScale();
  // May be overriden by sub-classes which have their own oppinion
  // about what scale to use in a hard subprocess. The default version
  // simply returns the previously selected scale.

  virtual void colourConnect(tPPtr particle, tPPtr parton,
			     const tPVector & remnants) const;
  // Connect the remnants with the colour lines of the extracted
  // parton. This default version does not accept that the incoming
  // particle is coloured.

  PBIPair newRemnants(tPPair oldp, tPPair newp, tStepPtr step);
  // If remnants has already been created for the given parton, remove
  // them from the given step and generate new remnants corresponding
  // to the parton newp and add them to the step. The new parton bins
  // are returned.

  inline const PartonBinMap & lastPartonBins() const;
  // Return info about the current selection.

  inline const PartonBinInstanceMap & partonBinInstances() const;
  // Return the current parton bin instances.

  tPBPtr partonBin(tcPPtr) const;
  // Return the corresponding parton bin for a given extracted parton.

  tPBIPtr partonBinInstance(tcPPtr) const;
  // Return the corresponding parton bin instance for a given
  // extracted parton.

  inline int maxTries() const;
  // The maximum number of attempts allowed when trying to generate
  // remnants.

  virtual pair<int,int> nDims(const PBPair & pbins);
  // Determine the number of random numbers needed to calculate sHat
  // and the product of all densitiy functions.

  virtual void prepare(const PBPair & pbins);
  // Prepare the given parton bins for generating a new event.

  virtual void prepare(const PBIPair & pbins);
  // Prepare the given parton bin instances for generating a new
  // event.

  virtual bool generateL(const PBPair & pbins,
			 const double * r1, const double * r2);
  // Generate log(1/x) for all parton extractions.

  virtual bool generateL(const PBIPair & pbins,
			 const double * r1, const double * r2);
  // Generate log(1/x) for all parton extractions.

  virtual Energy2 generateSHat(Energy2 s, const PBPair & pbins,
			       const double * r1, const double * r2);
  // Generate the rest of the degrees of freedom to calculate sHat and
  // the product of all densitiy functions.

  virtual Energy2 generateSHat(Energy2 s, const PBIPair & pbins,
			       const double * r1, const double * r2);
  // Generate the rest of the degrees of freedom to calculate sHat and
  // the product of all densitiy functions.

  virtual double fullFn(const PBPair & pbins, Energy2 scale);
  // Return the product of all density functions.

  virtual double fullFn(const PBIPair & pbins, Energy2 scale);
  // Return the product of all density functions.

  virtual void construct(const PBPair & pbins, tStepPtr step);
  virtual void construct(const PBIPair & pbins, tStepPtr step);
  // Construct remnants and add them to the step.

protected:

  virtual void generateL(PartonBin & pb, const double * r);
  virtual void generateL(PartonBinInstance & pb, const double * r);
  // Used by generateL() for each of the final parton
  // bins. Direction<0> is set to positive(negative) for the
  // first(second) final bin.

  virtual bool generate(PartonBin & pb, const double * r,
			const Lorentz5Momentum & first);
  virtual bool generate(PartonBinInstance & pb, const double * r,
			const Lorentz5Momentum & first);
  // Used by generateSHat() for each of the final parton
  // bins. Direction<0> is set to positive(negative) for the
  // first(second) final bin. Should ask the remnant handler to
  // generate what is needed to construct the extracted parton
  // momentum. Returns false if no remnants could be generated.

  virtual double fullFn(const PartonBin & pb);
  virtual double fullFn(const PartonBinInstance & pb);
  // Used by the public fullFn() for each of the final parton bins.

  virtual void construct(PartonBin & pb, tStepPtr step);
  virtual void construct(PartonBinInstance & pb, tStepPtr step);
  // Used by the public construct() for each of the final parton bins.

  PBIPtr newRemnants(tPBIPtr oldpb, tPPtr newp);
  void addNewRemnants(tPBIPtr oldpb, tPBIPtr newpb, tStepPtr step);
  // Used by the public newRemnants() for each f the parton bins.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual void addPartons(tPBPtr incoming ,const PDFCuts & cuts,
		  PartonVector & pbins) const;
  // Add parton bins to pbins for the given incoming particle and the
  // specified cuts.
  
  tcPDFPtr getPDF(tcPDPtr particle) const;
  // Return the PDFBase object to be used for the incoming particle
  // type. If one of theSpecialDensities matches the particle type it
  // is returned, otherwise if particle is a BeamParticleData use the
  // PDFBase object specified there. If also this fails, return a
  // NoPDF object.

  inline tcPDFPtr noPDF() const;
  // The NoPDF object.

  inline PartonBinMap & lastPartonBins();
  // The PartonBin's used mapped to the respective partons.

  inline PartonBinInstanceMap & partonBinInstances();
  // The PartonBinInstance's used mapped to the respective partons.

  template <typename Iterator>
  inline void findConnect(tColinePtr line, tPPtr parton, bool anti,
			  Iterator first, Iterator last) const;
  // connect the first (anti) coloured particle in the given range
  // (not equal to parton) and connect it to the colour line.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  void select(tXCombPtr newXComb);

private:

  PartonBinMap theLastPartonBins;
  // The PartonBin's used mapped to the respective partons.

  PartonBinInstanceMap thePartonBinInstances;
  // The PartonBinInstance's used mapped to the respective partons.

  vector<PDFPtr> theSpecialDensities;
  // A list of special PDFBase objects to be used.

  PDFPtr theNoPDF;
  // The NoPDF object.

  int theMaxTries;
  // THe maximum number of tries allowed when trying to produce
  // remnants.

  bool flatSHatY;
  // True if this extractor should override the l-generation in the
  // PDFs and generate a flat distribution in log(sHat) and y.

private:

  static ClassDescription<PartonExtractor> initPartonExtractor;

  PartonExtractor & operator=(const PartonExtractor &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<PartonExtractor,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<PartonExtractor>: public ClassTraitsBase<PartonExtractor> {
  static string className() { return "/ThePEG/PartonExtractor"; }
};

}

#include "PartonExtractor.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PartonExtractor.tcc"
#endif

#endif /* ThePEG_PartonExtractor_H */
