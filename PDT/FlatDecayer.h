// -*- C++ -*-
#ifndef ThePEG_FlatDecayer_H
#define ThePEG_FlatDecayer_H
//
// This is the declaration of the <!id>FlatDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>FlatDecayer<!!id> class inrerits from the abstract
// <!class>Decayer<!!class> and implements the decay of a given
// <!class>Particle<!!class> to a given set of children according to a
// flat phase space distribution.
//
// It is possible to implement a more complicated decay distribution
// by inheriting from the <!id>FlatDecayer<!!id> class and only
// override the virtual function <!id>reweight<!!id> to return a
// weight of a given phase space point relative to the flat
// distribution.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Decayer.html">Decayer.h</a>,
// <a href="http:Particle.html">Particle.h</a>.
// 

#include "ThePEG/PDT/Decayer.h"
// #include "FlatDecayer.fh"
// #include "FlatDecayer.xh"

namespace ThePEG {

class FlatDecayer: public Decayer {

public:

  inline FlatDecayer();
  inline FlatDecayer(const FlatDecayer &);
  virtual ~FlatDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode. Will return <!id>true<!!id> if all decay
  // products are completely specified and there are more than one of
  // them.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  inline virtual double reweight(const DecayMode &, const Particle & parent,
				 const ParticleVector & children) const;
  // To be overridden by subclasses. For a given decay mode, decaying
  // particle and decayproducts distributed according to a flat
  // distribution in phase space, return a weight (less or equal to
  // unity) modifying the flat distribution to the desired one. Note
  // that the chosen phase space point may be rejected, but the chosen
  // decay channel will not. This means that the weight returned by
  // this function does not influence the branching ratios. For the
  // FlatDecayer class this function simply returns 1.

public:

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

  static NoPIOClassDescription<FlatDecayer> initFlatDecayer;
  // Describe a concrete class without persistent data.

  FlatDecayer & operator=(const FlatDecayer &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of FlatDecayer.
template <>
struct BaseClassTrait<FlatDecayer,1> {
  typedef Decayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<FlatDecayer>: public ClassTraitsBase<FlatDecayer> {
  static string className() { return "/ThePEG/FlatDecayer"; }
  // Return the class name.
};

}

#include "FlatDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlatDecayer.tcc"
#endif

#endif /* ThePEG_FlatDecayer_H */
