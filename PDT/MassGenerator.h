// -*- C++ -*-
#ifndef ThePEG_MassGenerator_H
#define ThePEG_MassGenerator_H
//
// This is the declaration of the <!id>MassGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>MassGenerator<!!id> is an abstract base class used by the
// <!class>ParticleData<!!class> to generate a mass for a particle
// instance.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Interface/Interfaced.h"
#include "MassGenerator.fh"
// #include "MassGenerator.xh"

namespace ThePEG {

class MassGenerator: public Interfaced {

public:

  inline MassGenerator();
  inline MassGenerator(const MassGenerator &);
  virtual ~MassGenerator();
  // Standard ctors and dtor

public:

  virtual bool accept(const ParticleData &) const = 0;
  // Return true if this mass generator can handle the given particle
  // type.

  virtual Energy mass(const ParticleData &) const = 0;
  // Generate a mass for an instance of a given particle type.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

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

  static AbstractNoPIOClassDescription<MassGenerator> initMassGenerator;

  MassGenerator & operator=(const MassGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<MassGenerator,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<MassGenerator>: public ClassTraitsBase<MassGenerator> {
  static string className() {
    return "/ThePEG/MassGenerator";
  }
};

}

#include "MassGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MassGenerator.tcc"
#endif

#endif /* ThePEG_MassGenerator_H */
