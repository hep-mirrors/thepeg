// -*- C++ -*-
#ifndef ThePEG_RemnantHandler_H
#define ThePEG_RemnantHandler_H
// This is the declaration of the RemnantHandler class.

#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/CLHEPWrap/Transverse.h"
// #include "RemnantHandler.fh"
#include "RemnantHandler.xh"

namespace ThePEG {

/**
 * RemnantHandler is an abstract base class for implementing classes
 * used to generate remnants when partons are extracted from
 * particles.
 *
 * @see \ref RemnantHandlerInterfaces "The interfaces"
 * defined for RemnantHandler.
 * @see PartonExtractor
 * @see PDFBase
 */
class RemnantHandler: public HandlerBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor. If \a multi is true the derived class can be
   * used to extract more than one parton.
   */
  RemnantHandler(bool multi = false);

  /**
   * Copy-constructor.
   */
  RemnantHandler(const RemnantHandler &);

  /**
   * Destructor.
   */
  virtual ~RemnantHandler();
  //@}

public:

  /** @name Virtual functions to be overridden by sub-classes. */
  //@{
  /**
   * Return true if this remnant handler can handle extracting all
   * specified \a partons from the given \a particle.
   */
  virtual bool canHandle(tcPDPtr particle,
			 const cPDVector & partons) const = 0;

  /**
   * If the generation of remnants is expected to influence the actual
   * cross section of the hard sub process, the degrees of freedom
   * generated by this remnant handler may be included in the general
   * phase space sampling for the subprocess. In this case this
   * function should be overridden to return the number of degrees of
   * freedom used in the generation. If \a doScale is false, it means
   * that the actual virtuality of the extracted parton will be
   * obtained from another source.
   */
  virtual int nDim(const PartonBin & pb, bool doScale) const;

  /**
   * Generate the momentum of the extracted parton with the \a parent
   * momentum given by the last argument. If the \a scale is negative,
   * it means that the doScale in the previous call to nDim() was
   * true, otherwise the given \a scale should be the virtuality of
   * the extracted parton. Generated quantities which are not returned
   * in the momentum may be saved in the PartonBinInstance, \a pb, for
   * later use. In particular, if the nDim() random numbers, \a r, are
   * not enough to generate with weight one, the resulting weight
   * should be stored with the remnantWeight() method of the parton
   * bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & parent) const = 0;

  /**
   * Generate the momentum of the extracted parton with the \a parent
   * momentum given by the last argument. If the \a scale is negative,
   * it means that the doScale in the previous call to nDim() was
   * true, otherwise the given \a scale should be the virtuality of
   * the extracted parton. \a shat is the total invariant mass squared
   * of the hard sub-system produced by the extracted parton and the
   * primary parton entering from the other side. Generated quantities
   * which are not returned in the momentum may be saved in the
   * PartonBinInstance, \a pb, for later use. In particular, if the
   * nDim() random numbers, \a r, are not enough to generate with
   * weight one, the resulting weight should be stored with the
   * remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale, Energy2 shat,
				    const LorentzMomentum & parent) const = 0;

  /**
   * Boost the generated remnants to the proper momentum given the
   * information in the parton bin, \a pb.
   */
  virtual void boostRemnants(PartonBinInstance & pb) const;

  /**
   * Redo the remnant generation for the given particle bin, \a pb. If
   * \a oldp is non-null it corresponds to the previously extracted
   * parton which should be replaced by \a newp. If \a oldp is null it
   * means \a newp should be extracted in addition to the previously
   * extracted ones available in \a prev. 
   * @return false if the generation failed.
   */
  virtual bool recreateRemnants(PartonBinInstance & pb, tPPtr oldp, tPPtr newp,
				double newl, Energy2 scale,
				const LorentzMomentum & p,
				const PVector & prev = PVector()) const;
  /**
   * Redo the remnant generation for the given particle bin, \a pb. If
   * \a oldp is non-null it corresponds to the previously extracted
   * parton which should be replaced by \a newp. If \a oldp is null it
   * means \a newp should be extracted in addition to the previously
   * extracted ones available in \a prev. In either case \a shat is
   * the total invariant mass squared of the hard sub-system produced
   * by the extracted parton and the primary parton entering from the other
   * side. 
   *
   * @return false if the generation failed.
   */
  virtual bool recreateRemnants(PartonBinInstance & pb, tPPtr oldp, tPPtr newp,
				double newl, Energy2 scale,
				Energy2 shat, const LorentzMomentum & p,
				const PVector & prev = PVector()) const;
  //@}

  /**
   * Return true if this remnant handler is able to handle multiple
   * extractions of partons from the same particle.
   */
  inline bool multiCapable() const;

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

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

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
   * True if this handler can generate remnants also if several
   * partons have been extracted.
   */
  bool isMultiCapable;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class with persistent data.
   */
  static AbstractClassDescription<RemnantHandler> initRemnantHandler;

  /**
   *  Private and non-existent assignment operator.
   */
  RemnantHandler & operator=(const RemnantHandler &);

};

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the base classes
 *  of RemnantHandler. */
template <>
struct BaseClassTrait<RemnantHandler,1>: public ClassTraitsType {
  /** Typedef of the first base class of RemnantHandler. */
  typedef HandlerBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  RemnantHandler class. */
template <>
struct ClassTraits<RemnantHandler>: public ClassTraitsBase<RemnantHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::RemnantHandler"; }
};

/** @endcond */

}

#include "RemnantHandler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantHandler.tcc"
#endif

#endif /* ThePEG_RemnantHandler_H */
