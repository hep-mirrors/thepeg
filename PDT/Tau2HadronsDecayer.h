// -*- C++ -*-
#ifndef THEPEG_Tau2HadronsDecayer_H
#define THEPEG_Tau2HadronsDecayer_H
//
// This is the declaration of the <!id>Tau2HadronsDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class will perform the decays of tau to neutrimo + hadrons
// according to phase space, with an extra weight xnu(3-nxu).
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/PDT/FlatDecayer.h"
// #include "Tau2HadronsDecayer.fh"
// #include "Tau2HadronsDecayer.xh"

namespace ThePEG {

class Tau2HadronsDecayer: public FlatDecayer {

public:

  inline Tau2HadronsDecayer();
  inline Tau2HadronsDecayer(const Tau2HadronsDecayer &);
  virtual ~Tau2HadronsDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual double reweight(const DecayMode &, const Particle & parent,
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

  static ClassDescription<Tau2HadronsDecayer> initTau2HadronsDecayer;
  // Describe a concrete class with persistent data.

  Tau2HadronsDecayer & operator=(const Tau2HadronsDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of Tau2HadronsDecayer.
template <>
struct BaseClassTrait<Tau2HadronsDecayer,1> {
  typedef FlatDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<Tau2HadronsDecayer>
  : public ClassTraitsBase<Tau2HadronsDecayer> {
  static string className() { return "/ThePEG/Tau2HadronsDecayer"; }
  // Return the class name.
  static string library() { return "Tau2HadronsDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "Tau2HadronsDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Tau2HadronsDecayer.tcc"
#endif

#endif /* THEPEG_Tau2HadronsDecayer_H */
