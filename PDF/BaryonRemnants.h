// -*- C++ -*-
#ifndef ThePEG_BaryonRemnants_H
#define ThePEG_BaryonRemnants_H
//
// This is the declaration of the <!id>BaryonRemnants<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>BaryonRemnants<!!id> inherits from the
// <!class>RemnantHandler<!!class> and implements the generation of a
// remnants when a partons are extracted from a baryon.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RemnantHandler.html">RemnantHandler.h</a>.
// 

#include "ThePEG/PDF/RemnantHandler.h"
#include "ThePEG/Handlers/PtGenerator.h"
#include "ThePEG/Handlers/ZGenerator.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
#include "ThePEG/Utilities/VSelector.h"
// #include "BaryonRemnants.fh"
// #include "BaryonRemnants.xh"

namespace ThePEG {

class BaryonRemnants: public RemnantHandler {

public:

  typedef Ptr<PtGenerator>::pointer PtGPtr;;
  typedef Ptr<ZGenerator>::pointer ZGPtr;
  typedef Ptr<FlavourGenerator>::pointer FlGPtr;

public:

  BaryonRemnants();
  BaryonRemnants(const BaryonRemnants &);
  virtual ~BaryonRemnants();
  // Standard ctors and dtor

public:

  virtual bool canHandle(tcPDPtr particle, const cPDVector & partons) const;
  // Return true if this remnant handler can handle extracting all
  // specified partons.

  virtual Lorentz5Momentum generate(PartonBin & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;
  // Generate the momentum of the extracted parton in the particle cms
  // (but with x still the positive light-cone fraction) as given by
  // the last argument. If the particle is space-like the positive and
  // negative light-cone momenta are sqrt(-m2) and -sqrt(-m2)
  // respectively. If the scale is negative, it means that the doScale
  // in the previous call to nDim() was true, otherwise the given
  // scale should be the virtuality of the extracted parton. Generated
  // quantities which are not returned in the momentum may be saved in
  // the PartonBin for later use. In particular, if the nDim() random
  // numbers are not enough to generate with weight one, the resulting
  // weight should be stored with the remnantWeight() method of the
  // parton bin.

  virtual void createRemnants(PartonBin & pb) const;
  // If the actual remnants were not fully generated in the previous
  // call to generate(), do that now and store them in the parton bin.

  inline Energy margin() const;
  // Return the energy margin to be added to the sum of the parent and
  // parton masses to determine if it is possible to construct the
  // remnants with the given (upper limit of the) virtuality of the
  // extracted parton.

protected:

  inline ZGenerator & zGenerator() const;
  // Return a reference to the object responsible for generating
  // momentum fractions in case of more than one remnant.

  inline PtGenerator & ptGeneratorQ() const;
  // Return a reference to the object responsible for generating
  // primordial pt of the struck quark.

  inline PtGenerator & ptGeneratorR() const;
  // Return a reference to the object responsible for generating
  // primordial pt among the remnants.

  inline FlavourGenerator & flavourGenerator() const;
  // Return a reference to the object responsible for handling the
  // flavour contents of a baryon.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

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

  Ptr<PtGenerator>::pointer thePtGeneratorQ;
  Ptr<PtGenerator>::pointer thePtGeneratorR;
  // The object responsible for generating primordial pt for the struck
  // quark (Q) and within the remnants (R)..

  Ptr<ZGenerator>::pointer theZGenerator;
  // The object responsible for generating momentum fractions in case
  // of more than one remnant.

  Ptr<FlavourGenerator>::pointer theFlavourGenerator;
  // The object responsible for handling the flavour contents of a
  // baryon.

  Energy theMargin;
  // The energy margin to be added to the sum of the parent and parton
  // masses to determine if it is possible to construct the remnants
  // with the given (upper limit of the) virtuality of the extracted
  // parton.


private:

  static ClassDescription<BaryonRemnants> initBaryonRemnants;

  BaryonRemnants & operator=(const BaryonRemnants &);
  //  Private and non-existent assignment operator.

};

struct BaryonRemnantsInfo: public RemnantInfo {
  int iq;
  int sign;
  vector<int> flav;
  vector<int> vflav;
  VSelector< pair<int,int> > flavsel;
  bool mayval;
};

template <>
struct BaseClassTrait<BaryonRemnants,1> {
  typedef RemnantHandler NthBase;
};

template <>
struct ClassTraits<BaryonRemnants>: public ClassTraitsBase<BaryonRemnants> {
  static string className() { return "/ThePEG/BaryonRemnants"; }
  static string library() { return "libThePEGString.so BaryonRemnants.so"; }
};

}

#include "BaryonRemnants.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BaryonRemnants.tcc"
#endif

#endif /* ThePEG_BaryonRemnants_H */
