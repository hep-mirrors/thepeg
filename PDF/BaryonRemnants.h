// -*- C++ -*-
#ifndef ThePEG_BaryonRemnants_H
#define ThePEG_BaryonRemnants_H
// This is the declaration of the BaryonRemnants class.

#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/Handlers/PtGenerator.h"
#include "ThePEG/Handlers/ZGenerator.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
#include "ThePEG/Utilities/VSelector.h"
// #include "BaryonRemnants.fh"
// #include "BaryonRemnants.xh"

namespace ThePEG {

/**
 * BaryonRemnants inherits from RemnantHandler and implements a simple
 * model for generation of remnants when a parton is extracted from a
 * baryon.
 *
 * @see \ref BaryonRemnantsInterfaces "The interfaces"
 * defined for BaryonRemnants.
 */
class BaryonRemnants: public RemnantHandler {

public:

  /** A pointer to a PtGenerator object. */
  typedef Ptr<PtGenerator>::pointer PtGPtr;
  /** A pointer to a ZGenerator object. */
  typedef Ptr<ZGenerator>::pointer ZGPtr;
  /** A pointer to a FlavourGenerator object. */
  typedef Ptr<FlavourGenerator>::pointer FlGPtr;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  BaryonRemnants();

  /**
   * Copy-constructor.
   */
  BaryonRemnants(const BaryonRemnants &);

  /**
   * Destructor.
   */
  virtual ~BaryonRemnants();
  //@}

public:

  /** @name Virtual functions mandated by the RemnantHandler base class. */
  //@{
  /**
   * Return true if this remnant handler can handle extracting all
   * specified \a partons form the given \a particle.
   */
  virtual bool canHandle(tcPDPtr particle, const cPDVector & partons) const;

  /**
   * Generate momenta. Generates the momenta of the extracted parton
   * in the particle cms (but with the parton \f$x\f$ still the
   * positive light-cone fraction) as given by the last argument, \a
   * p. If the particle is space-like the positive and negative
   * light-cone momenta are \f$\sqrt{-m^2}\f$ and \f$-sqrt{-m^2}\f$
   * respectively. If the \a scale is negative, it means that the \a
   * doScale in the previous call to nDim() was true, otherwise the
   * given scale should be the virtuality of the extracted
   * parton. Generated quantities which are not returned in the
   * momentum may be saved in the PartonBin, \a pb, for later use. In
   * particular, if the nDim() random numbers, \a r, are not enough to
   * generate with weight one, the resulting weight should be stored
   * with the remnantWeight() method of the parton bin.
   */
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;

  /**
   * If the actual remnants were not fully generated in the previous
   * call to generate(), do that now and store them in the parton bin,
   * \a pb.
   */
  virtual void createRemnants(PartonBinInstance & pb) const;
  //@}

  /**
   * Return the energy margin to be added to the sum of the parent and
   * parton masses to determine if it is possible to construct the
   * remnants with the given (upper limit of the) virtuality of the
   * extracted parton.
   */
  inline Energy margin() const;

protected:

  /**
   * Return a reference to the object responsible for generating
   * momentum fractions in case of more than one remnant.
   */
  inline ZGenerator & zGenerator() const;

  /**
   * Return a reference to the object responsible for generating
   * primordial pt of the struck quark.
   */
  inline PtGenerator & ptGeneratorQ() const;

  /**
   * Return a reference to the object responsible for generating
   * primordial pt among the remnants.
   */
  inline PtGenerator & ptGeneratorR() const;

  /**
   * Return a reference to the object responsible for handling the
   * flavour contents of a baryon.
   */
  inline FlavourGenerator & flavourGenerator() const;

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
   * The object responsible for generating primordial pt for the struck
   * quark.
   */
  Ptr<PtGenerator>::pointer thePtGeneratorQ;

  /**
   * The object responsible for generating primordial pt within the remnants.
   */
  Ptr<PtGenerator>::pointer thePtGeneratorR;

  /**
   * The object responsible for generating momentum fractions in case
   * of more than one remnant.
   */
  Ptr<ZGenerator>::pointer theZGenerator;

  /**
   * The object responsible for handling the flavour contents of a
   * baryon.
   */
  Ptr<FlavourGenerator>::pointer theFlavourGenerator;

  /**
   * The energy margin to be added to the sum of the parent and parton
   * masses to determine if it is possible to construct the remnants
   * with the given (upper limit of the) virtuality of the extracted
   * parton.
   */
  Energy theMargin;


private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<BaryonRemnants> initBaryonRemnants;

  /**
   *  Private and non-existent assignment operator.
   */
  BaryonRemnants & operator=(const BaryonRemnants &);

};

/** Simple struct used by BaryonRemnants to store generated values. */
struct BaryonRemInfo: public RemInfoBase {
  /** The extracted flavour. */
  int iq;
  /** -1 if the particle is an anti-particle. +1 otherwise. */
  int sign;
  /** The valens flavours of the particle. */
  vector<int> flav;
  /** The flavours left in the remnant. */
  vector<int> vflav;
  /** Different divisions into quark-diquark weighted by their
      respective probabilities. */
  VSelector< pair<int,int> > flavsel;
  /** True if the extracted parton may be a valens quark. */
  bool mayval;
};

/** This template specialization informs ThePEG about the
 *  base classes of BaryonRemnants. */
template <>
struct BaseClassTrait<BaryonRemnants,1>: public ClassTraitsType {
  /** Typedef of the first base class of BaryonRemnants. */
  typedef RemnantHandler NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  BaryonRemnants class and the shared object where it is defined. */
template <>
struct ClassTraits<BaryonRemnants>: public ClassTraitsBase<BaryonRemnants> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::BaryonRemnants"; }
  /** Return the name of the shared library be loaded to get access to
   *  the BaryonRemnants class and every other class it uses (except
   *  the base class). */
  static string library() { return "BaryonRemnants.so"; }
};

}

#include "BaryonRemnants.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BaryonRemnants.tcc"
#endif

#endif /* ThePEG_BaryonRemnants_H */
