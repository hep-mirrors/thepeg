// -*- C++ -*-
#ifndef ThePEG_WidthGenerator_H
#define ThePEG_WidthGenerator_H
//
// This is the declaration of the <!id>WidthGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>WidthGenerator<!!id> is an abstract base class to be used to
// encapsulate models for giving the partial decay width of a
// <!class>ParticleData<!!class> given the specified
// <!class>DecayMode<!!class>s.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:DecayMode.html">DecayMode.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "WidthGenerator.fh"
#include "ThePEG/Interface/Interfaced.h"
// #include "WidthGenerator.xh"
#include "ThePEG/Utilities/Selector.h"
#include "ThePEG/PDT/DecayMode.fh"

namespace ThePEG {

class WidthGenerator: public Interfaced {

public:

  typedef Selector<tDMPtr> DecayMap;

public:

  inline WidthGenerator();
  inline WidthGenerator(const WidthGenerator &);
  virtual ~WidthGenerator();
  // Standard ctors and dtor

public:

  virtual bool accept(const ParticleData &) const = 0;
  // Return true if this rater can be used for the given particle with
  // the given decay map.

  Energy width(const Particle &) const;
  virtual Energy width(const ParticleData &, Energy m) const = 0;
  // Given a particle type and a mass of an instance of that particle
  // type, calculate a width.

  virtual Length lifeTime(const ParticleData &, Energy m, Energy w) const;
  // Given a particle type and a mass and a width of an instance of
  // that particle type, generate a life time.

  virtual DecayMap rate(const ParticleData &) const = 0;
  // Initialize the given decay map for the given particle type.

  virtual DecayMap rate(const Particle &);
  // Return a decay map for a given particleinstance.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  static AbstractNoPIOClassDescription<WidthGenerator> initWidthGenerator;

  WidthGenerator & operator=(const WidthGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<WidthGenerator,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<WidthGenerator>: public ClassTraitsBase<WidthGenerator> {
  static string className() { return "/ThePEG/WidthGenerator"; }
};

}

#include "WidthGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "WidthGenerator.tcc"
#endif

#endif /* ThePEG_WidthGenerator_H */
