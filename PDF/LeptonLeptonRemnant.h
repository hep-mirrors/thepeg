// -*- C++ -*-
#ifndef ThePEG_LeptonLeptonRemnant_H
#define ThePEG_LeptonLeptonRemnant_H
//
// This is the declaration of the <!id>LeptonLeptonRemnant<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>LeptonLeptonRemnant<!!id> inherits from the
// <!class>RemnantHandler<!!class> and implements the generation of a
// single collinear photon remnant when a lepton is extracted from a
// lepton.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RemnantHandler.html">RemnantHandler.h</a>.
// 

#include "ThePEG/PDF/RemnantHandler.h"
// #include "LeptonLeptonRemnant.fh"
// #include "LeptonLeptonRemnant.xh"

namespace ThePEG {

class LeptonLeptonRemnant: public RemnantHandler {

public:

  LeptonLeptonRemnant();
  LeptonLeptonRemnant(const LeptonLeptonRemnant &);
  virtual ~LeptonLeptonRemnant();
  // Standard ctors and dtor

public:

  virtual bool canHandle(tcPDPtr particle, const cPDVector & partons) const;
  // Return true if this remnant handler can handle extracting all
  // specified partons.

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

  double minX;
  // The minimum energy fraction allowed for a photon remnant.

  PDPtr photon;
  // Easy access to a proton data object.

private:

  static ClassDescription<LeptonLeptonRemnant> initLeptonLeptonRemnant;

  LeptonLeptonRemnant & operator=(const LeptonLeptonRemnant &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<LeptonLeptonRemnant,1> {
  typedef RemnantHandler NthBase;
};

template <>
struct ClassTraits<LeptonLeptonRemnant>:
    public ClassTraitsBase<LeptonLeptonRemnant> {
  static string className() { return "/ThePEG/LeptonLeptonRemnant"; }
  static string library() { return "LeptonLeptonRemnant.so"; }
};

}

#include "LeptonLeptonRemnant.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LeptonLeptonRemnant.tcc"
#endif

#endif /* ThePEG_LeptonLeptonRemnant_H */
