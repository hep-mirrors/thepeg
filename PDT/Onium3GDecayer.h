// -*- C++ -*-
#ifndef THEPEG_Onium3GDecayer_H
#define THEPEG_Onium3GDecayer_H
//
// This is the declaration of the <!id>Onium3GDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs the decay of a spin-1 onium resonance into
// three gluons or two gluons and a photon. After the decay the
// collision handler is instructed to restart the generation from the
// hadronization (or optionally the parton cascade) stage.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FlatDecayer.html">FlatDecayer.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/PDT/FlatDecayer.h"
// #include "Onium3GDecayer.fh"
// #include "Onium3GDecayer.xh"

namespace ThePEG {

class Onium3GDecayer: public FlatDecayer {

public:

  inline Onium3GDecayer();
  inline Onium3GDecayer(const Onium3GDecayer &);
  virtual ~Onium3GDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  virtual double reweight(const DecayMode &, const Particle & parent,
				 const ParticleVector & children) const;
  // For a given decay mode, decaying particle and decayproducts
  // distributed according to a flat distribution in phase space,
  // return a weight (less or equal to unity) modifying the flat
  // distribution to the desired one. Note that the chosen phase space
  // point may be rejected, but the chosen decay channel will
  // not. This means that the weight returned by this function does
  // not influence the branching ratios.

  inline bool shower() const;
  // Return true if the produced gluons should be showered.

  inline Energy minGGMass() const;
  // Return the minimum invariant mass between two gluons in gamma-g-g
  // decays.

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

  bool doShower;
  // If true the produced gluons should be showered.

  Energy theMinGGMass;
  // The minimum invariant mass between two gluons in gamma-g-g
  // decays.

private:

  static ClassDescription<Onium3GDecayer> initOnium3GDecayer;
  // Describe a concrete class with persistent data.

  Onium3GDecayer & operator=(const Onium3GDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of Onium3GDecayer.
template <>
struct BaseClassTrait<Onium3GDecayer,1> {
  typedef FlatDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<Onium3GDecayer>
  : public ClassTraitsBase<Onium3GDecayer> {
  static string className() { return "ThePEG::Onium3GDecayer"; }
  // Return the class name.
  static string library() { return "Onium3GDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "Onium3GDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Onium3GDecayer.tcc"
#endif

#endif /* THEPEG_Onium3GDecayer_H */
