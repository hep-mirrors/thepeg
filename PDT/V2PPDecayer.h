// -*- C++ -*-
#ifndef THEPEG_V2PPDecayer_H
#define THEPEG_V2PPDecayer_H
//
// This is the declaration of the <!id>V2PPDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs the decay of a vector meson into two
// pseudo-scalars according to a flat phase space. If, however the
// decaying particle comes from a pseudo-scalar and has only one
// sibling which is a pseudo-scalar (or a photon) the decay is
// reweighted with cos^2 (sin^2 for photon) of the angle between one
// of the decay products and its grand parent.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FlatDecayer.html">.h</a>,
// <a href="http:ParticleData.html">.h</a>.
// 

#include "ThePEG/PDT/FlatDecayer.h"
// #include "V2PPDecayer.fh"
// #include "V2PPDecayer.xh"

namespace ThePEG {

class V2PPDecayer: public FlatDecayer {

public:

  inline V2PPDecayer();
  inline V2PPDecayer(const V2PPDecayer &);
  virtual ~V2PPDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  inline virtual double reweight(const DecayMode &, const Particle & parent,
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

  mutable tPPtr grandParent;
  // The grand parent in case reweighting should be done.

  mutable tPPtr sibling;
  // The decaying particles sibling in case reweighting should be done.

private:

  static ClassDescription<V2PPDecayer> initV2PPDecayer;
  // Describe a concrete class with persistent data.

  V2PPDecayer & operator=(const V2PPDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of V2PPDecayer.
template <>
struct BaseClassTrait<V2PPDecayer,1> {
  typedef FlatDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<V2PPDecayer>
  : public ClassTraitsBase<V2PPDecayer> {
  static string className() { return "/ThePEG/V2PPDecayer"; }
  // Return the class name.
  static string library() { return "V2PPDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "V2PPDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "V2PPDecayer.tcc"
#endif

#endif /* THEPEG_V2PPDecayer_H */
