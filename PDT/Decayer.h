// -*- C++ -*-
#ifndef ThePEG_Decayer_H
#define ThePEG_Decayer_H
//
// This is the declaration of the <!id>Decayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Decayer<!!id> is an abstract base class to specify the
// interface between <!class>ParticleData<!!class> objects an objects
// modelling the decay of a particle.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "Decayer.fh"
// #include "Decayer.xh"
#include "ThePEG/Handlers/HandlerBase.h"
#include "ThePEG/MatrixElement/Amplitude.h"

namespace ThePEG {

class Decayer: public HandlerBase {

public:

  inline Decayer();
  inline Decayer(const Decayer &);
  virtual ~Decayer();
  // Standard ctors and dtor

public:

  virtual bool accept(const DecayMode &) const = 0;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const = 0;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  virtual double brat(const DecayMode &, const ParticleData &,
		      double oldbrat) const;
  // If this model has any oppinions on the decay rate for a given
  // decay mode for a given particle type, this method may be
  // overriden to return this oppinion.

  virtual double brat(const DecayMode &, const Particle &,
		      double oldbrat) const;
  // If this model has any oppinions on the decay rate for a given
  // decay mode for a given particle instance, this method may be
  // overriden to return this oppinion.

  inline Ptr<Amplitude>::pointer amplitude() const;
  // Return the eventual amplitude associated with this decay matrix element.

  virtual ParticleVector getChildren(const DecayMode & dm,
				     const Particle & parent) const;
  // Can be used by sub-class decay() functions to produce instances
  // of the children. This default implementation just calls the
  // produceProducts() of the DecayMode object.

  virtual void finalBoost(const Particle & parent,
			  const ParticleVector & children) const;
  // Can be used by sub-classes to perform the final boost back from
  // the parents cms. This default version does just that.

  virtual void setScales(const Particle & parent,
			 const ParticleVector & children) const;
  // Can be used by sub classes to set the production scale of the
  // children. This default version sets the scale to the parents
  // mass.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

private:

  static AbstractNoPIOClassDescription<Decayer> initDecayer;

  Decayer & operator=(const Decayer &);
  //  Private and non-existent assignment operator.

  Ptr<Amplitude>::pointer theAmplitude;
  // The eventual amplitude associated with this matrix element.

};

template <>
struct BaseClassTrait<Decayer,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<Decayer>: public ClassTraitsBase<Decayer> {
  static string className() { return "/ThePEG/Decayer"; }
};

}

#include "Decayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Decayer.tcc"
#endif

#endif /* ThePEG_Decayer_H */
