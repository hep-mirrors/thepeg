// -*- C++ -*-
#ifndef ThePEG_NoRemnants_H
#define ThePEG_NoRemnants_H
//
// This is the declaration of the <!id>NoRemnants<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>NoRemnants<!!id> inherits from <!class>RemnantHandler<!!class>
// but can only handle particles without sub-structure with the parton
// density given by a <!class>NoPDF<!!class> object. No , and will
// never give any remnants.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RemnantHandler.html">RemnantHandler.h</a>,
// <a href="http:NoPDF.html">NoPDF.h</a>.
// 

#include "ThePEG/PDF/RemnantHandler.h"
// #include "NoRemnants.fh"
// #include "NoRemnants.xh"

namespace ThePEG {

class NoRemnants: public RemnantHandler {

public:

  inline NoRemnants();
  inline NoRemnants(const NoRemnants &);
  virtual ~NoRemnants();
  // Standard ctors and dtor

public:

  inline virtual bool canHandle(tcPDPtr particle,
				const cPDVector & partons) const;
  // Return true if this remnant handler can handle extracting all
  // specified partons. The NoRemnants will return false if any
  // partons are given.

  virtual PVector getRemnants(const PartonBin &,
			      Energy2 sMax, TransverseMomentum & kt,
			      const PVector & prev = PVector()) const;
  // For a given parton extracted from a particle return the remnants,
  // in their cm system, assumong the particle is comin in along the
  // positive z-axis. Also return the generated intrisic transverse
  // momentum of the extracted parton. If the prev vector of particles
  // is not empty it meens that we are dealing with multiple
  // interactions and prev contains the previously extracted partons.

  virtual Lorentz5Momentum generate(PartonBin & pb, const double * r,
				    Energy2 scale,
				    const LorentzMomentum & p) const;
  virtual Lorentz5Momentum generate(PartonBinInstance & pb, const double * r,
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

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

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

  static NoPIOClassDescription<NoRemnants> initNoRemnants;

  NoRemnants & operator=(const NoRemnants &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<NoRemnants,1> {
  typedef RemnantHandler NthBase;
};

template <>
struct ClassTraits<NoRemnants>: public ClassTraitsBase<NoRemnants> {
  static string className() { return "/ThePEG/NoRemnants"; }
};

}

#include "NoRemnants.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "NoRemnants.tcc"
#endif

#endif /* ThePEG_NoRemnants_H */
