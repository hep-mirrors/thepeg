// -*- C++ -*-
#ifndef ThePEG_BreitWignerMass_H
#define ThePEG_BreitWignerMass_H
//
// This is the declaration of the <!id>BreitWignerMass<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>BreitWignerMass<!!id> is derived from
// <!class>MassGenerator<!!class> and is able to generate the mass for
// a particle given its nominal mass and its with.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:MassGenerator.html">MassGenerator.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/PDT/MassGenerator.h"
// #include "BreitWignerMass.fh"
// #include "BreitWignerMass.xh"

namespace ThePEG {

class BreitWignerMass: public MassGenerator {

public:

  inline BreitWignerMass();
  inline BreitWignerMass(const BreitWignerMass &);
  virtual ~BreitWignerMass();
  // Standard ctors and dtor.

public:

  inline virtual bool accept(const ParticleData &) const;
  // Return true if this mass generator can handle the given particle
  // type.

  virtual Energy mass(const ParticleData &) const;
  // Generate a mass for an instance of a given particle type.

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

  static NoPIOClassDescription<BreitWignerMass> initBreitWignerMass;
  // Describe concrete class without persistent data.

  BreitWignerMass & operator=(const BreitWignerMass &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_DYNAMIC_CLASS_TRAITS(BreitWignerMass,MassGenerator,"BreitWignerMass.so");

}

#include "BreitWignerMass.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BreitWignerMass.tcc"
#endif

#endif /* ThePEG_BreitWignerMass_H */
