// -*- C++ -*-
#ifndef ThePEG_RemnantHandler_H
#define ThePEG_RemnantHandler_H
//
// This is the declaration of the <!id>RemnantHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>RemnantHandler<!!id> is an abstract base class for
// implementing classes for generating remnants when partons are
// extracted particles.
//

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/CLHEPWrap/Transverse.h"
// #include "RemnantHandler.fh"
#include "RemnantHandler.xh"

namespace ThePEG {

class RemnantHandler: public HandlerBase {

public:

  RemnantHandler(bool multi = false);
  RemnantHandler(const RemnantHandler &);
  virtual ~RemnantHandler();
  // Standard ctors and dtor

public:

  virtual bool canHandle(tcPDPtr particle,
			 const cPDVector & partons) const = 0;
  // Return true if this remnant handler can handle extracting all
  // specified partons from the given particle.

  virtual int nDim(const PartonBin & pb, bool doScale) const;
  // If the generation of remnants is expected to influence the actual
  // cross section of the hard sub process, the degrees of freedom
  // generated by this remnant handler may be included int the general
  // phase space sampling for the subprocess. In this case this
  // function should be overridden to return the number of degrees of
  // freedom used in the generation. If doScale is false, it means
  // that the actual virtuality of the extracted parton will be
  // obtained from another source.

  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & parent) const = 0;
  // Generate the momentum of the extracted parton with the parent
  // momentum given by the last argument. If the scale is negative, it
  // means that the doScale in the previous call to nDim() was true,
  // otherwise the given scale should be the virtuality of the
  // extracted parton. Generated quantities which are not returned in
  // the momentum may be saved in the PartonBin for later use. In
  // particular, if the nDim() random numbers are not enough to
  // generate with weight one, the resulting weight should be stored
  // with the remnantWeight() method of the parton bin.

  virtual void createRemnants(PartonBinInstance & pb) const;
  // If the actual remnants were not fully generated in the previous
  // call to generate(), do that now and store them in the parton bin.

  virtual bool recreateRemnants(PartonBinInstance & pb, tPPtr oldp, tPPtr newp,
				double newl, Energy2 scale,
				const LorentzMomentum & p,
				const PVector & prev = PVector()) const;
  // Redo the remnant generation for the given particle bin. If oldp
  // is non-null it corresponds to the previously extracted parton
  // which should be replaced by newp. If oldp is null it means newp
  // should be extracted in addition to the previously extracted ones
  // available in prev. Return false if the generation failed.

  inline bool multiCapable() const;
  // Return true if this remnant handler is able to handle multiple
  // extractions of partons from the same particle.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

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

  bool isMultiCapable;
  // True if this handler can generate remnants also if several
  // partons have been extracted.

private:

  static AbstractClassDescription<RemnantHandler> initRemnantHandler;

  RemnantHandler & operator=(const RemnantHandler &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<RemnantHandler,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<RemnantHandler>: public ClassTraitsBase<RemnantHandler> {
  static string className() { return "/ThePEG/RemnantHandler"; }
};

}

#include "RemnantHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantHandler.tcc"
#endif

#endif /* ThePEG_RemnantHandler_H */
