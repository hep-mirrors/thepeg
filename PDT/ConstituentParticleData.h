// -*- C++ -*-
#ifndef ThePEG_ConstituentParticleData_H
#define ThePEG_ConstituentParticleData_H
//
// This is the declaration of the <!id>ConstituentParticleData<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ConstituentParticleData<!!id> inherits from the
// <!class>ParticleData<!!class> class and is used for quarks,
// diquarks and gluons to store information about their constituent
// mass..
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/PDT/ParticleData.h"

// #include "ConstituentParticleData.fh"
// #include "ConstituentParticleData.xh"

namespace ThePEG {

class ConstituentParticleData: public virtual ParticleData {

public:

  inline ConstituentParticleData();
  inline ConstituentParticleData(const ConstituentParticleData &);
  virtual ~ConstituentParticleData();
  // Standard ctors and dtor

  static PDPtr Create(long newId, string newPDGName);
  // Create a Particle which is its own anti-particle.

  static PDPair Create(long newId, string newPDGName, string newAntiPDGName);
  // Create a particle - anti particle pair.

public:

  inline virtual Energy constituentMass() const;
  // Return the constituent mass of this parton.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  ConstituentParticleData(long newId, string newPDGName);
  // Protected constructor only to be used by subclasses or by the
  // Create method.

  virtual void readSetup(istream & is) throw(SetupException);
  // Read setup info from a standard stream.

  virtual PDPtr pdclone() const;
  // ParticleData clone method

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

  void setConstituentMass(Energy m);
  Energy defConstituentMass() const;
  Energy maxConstituentMass() const;
  // Utility functions for the interface.

private:

  Energy theConstituentMass;
  // The constituent mass of this parton.

  Energy theDefaultConstituentMass;
  // The default constituent mass of this parton.

private:

  static ClassDescription<ConstituentParticleData> initConstituentParticleData;

  ConstituentParticleData & operator=(const ConstituentParticleData &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<ConstituentParticleData,1> {
  typedef ParticleData NthBase;
};

template <>
struct ClassTraits<ConstituentParticleData>: public ClassTraitsBase<ConstituentParticleData> {
  static string className() { return "/ThePEG/ConstituentParticleData"; }
};

}

#include "ConstituentParticleData.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ConstituentParticleData.tcc"
#endif

#endif /* ThePEG_ConstituentParticleData_H */
