// -*- C++ -*-
#ifndef ThePEG_PYDECYDummy_H
#define ThePEG_PYDECYDummy_H
//
// This is the declaration of the <!id>PYDECYDummy<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>PYDECYDummy<!!id> inherits from the <!class>Decayer<!!class>
// class, and is used to represent pythia-6 decay matrix elements. It
// is a true dummy class and cannot actually perform any decays.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Decayer.html">Decayer.h</a>
// 

#include "Decayer.h"
// #include "PYDECYDummy.fh"
// #include "PYDECYDummy.xh"

namespace ThePEG {

class PYDECYDummy: public Decayer {

public:

  inline PYDECYDummy();
  inline PYDECYDummy(int);
  inline PYDECYDummy(const PYDECYDummy &);
  inline virtual ~PYDECYDummy();
  // Standard ctors and dtor

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual bool accept(const DecayMode &) const;

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;

  virtual double brat(const DecayMode &,
		      const ParticleData &, double) const;

  virtual double brat(const DecayMode &, const Particle &, double) const;


  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual void readSetup(istream & is) throw(SetupException);
  // Read setup info from a standard stream.

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void
  rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  int theME;

  static ClassDescription<PYDECYDummy> initPYDECYDummy;

  PYDECYDummy & operator=(const PYDECYDummy &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<PYDECYDummy,1> {
  typedef Decayer NthBase;
};

template <>
struct ClassTraits<PYDECYDummy>:
    public ClassTraitsBase<PYDECYDummy> {
  static string className() {
    return "/ThePEG/PYDECYDummy";
  }
};

}

#include "PYDECYDummy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "PYDECYDummy.tcc"
#endif

#endif /* ThePEG_PYDECYDummy_H */
