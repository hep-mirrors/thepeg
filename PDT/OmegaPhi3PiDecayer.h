// -*- C++ -*-
#ifndef THEPEG_OmegaPhi3PiDecayer_H
#define THEPEG_OmegaPhi3PiDecayer_H
//
// This is the declaration of the <!id>OmegaPhi3PiDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs the decay of a phi or an omega into pi+ pi-
// p0. It will in fact decay anything into pi+ pi- p0 assuming the
// same matrix element.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FlatDecayer.html">.h</a>,
// <a href="http:ParticleData.html">.h</a>.
// 

#include "ThePEG/PDT/FlatDecayer.h"
// #include "OmegaPhi3PiDecayer.fh"
// #include "OmegaPhi3PiDecayer.xh"

namespace ThePEG {

class OmegaPhi3PiDecayer: public FlatDecayer {

public:

  inline OmegaPhi3PiDecayer();
  inline OmegaPhi3PiDecayer(const OmegaPhi3PiDecayer &);
  virtual ~OmegaPhi3PiDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual double reweight(const DecayMode &, const Particle & parent,
				 const ParticleVector & children) const;
  // For a given decay mode, decaying particle and decayproducts
  // distributed according to a flat distribution in phase space,
  // return a weight (less or equal to unity) modifying the flat
  // distribution to the desired one. Note that the chosen phase space
  // point may be rejected, but the chosen decay channel will
  // not. This means that the weight returned by this function does
  // not influence the branching ratios.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  double margin;
  // Used to multiply the bare weight to get something below unity. In
  // the Fortran pythia version it was set to 150 for unknown reasons.

private:

  static ClassDescription<OmegaPhi3PiDecayer> initOmegaPhi3PiDecayer;
  // Describe a concrete class with persistent data.

  OmegaPhi3PiDecayer & operator=(const OmegaPhi3PiDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of OmegaPhi3PiDecayer.
template <>
struct BaseClassTrait<OmegaPhi3PiDecayer,1> {
  typedef FlatDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<OmegaPhi3PiDecayer>
  : public ClassTraitsBase<OmegaPhi3PiDecayer> {
  static string className() { return "ThePEG::OmegaPhi3PiDecayer"; }
  // Return the class name.
  static string library() { return "OmegaPhi3PiDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "OmegaPhi3PiDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "OmegaPhi3PiDecayer.tcc"
#endif

#endif /* THEPEG_OmegaPhi3PiDecayer_H */
