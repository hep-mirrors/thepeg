// -*- C++ -*-
#ifndef THEPEG_DummyDecayer_H
#define THEPEG_DummyDecayer_H
//
// This is the declaration of the <!id>DummyDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This is a dummy decayer class to be used for symbolic decay
// channels. If it for some reason is called to perform a decay, it
// will throw a std::logic_error.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Decayer.html">.h</a>.
// 

#include "ThePEG/PDT/Decayer.h"
// #include "DummyDecayer.fh"
// #include "DummyDecayer.xh"

namespace ThePEG {

class DummyDecayer: public Decayer {

public:

  inline DummyDecayer();
  inline DummyDecayer(const DummyDecayer &);
  virtual ~DummyDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  virtual double brat(const DecayMode &,
		      const ParticleData &, double) const;
  virtual double brat(const DecayMode &, const Particle &, double) const;
  // Will always return zero, since no decay can ever be performed
  // with this decayer.

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

  static NoPIOClassDescription<DummyDecayer> initDummyDecayer;
  // Describe a concrete class without persistent data.

  DummyDecayer & operator=(const DummyDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of DummyDecayer.
template <>
struct BaseClassTrait<DummyDecayer,1> {
  typedef Decayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<DummyDecayer>
  : public ClassTraitsBase<DummyDecayer> {
  static string className() { return "/ThePEG/DummyDecayer"; }
  // Return the class name.
};

}

#include "DummyDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DummyDecayer.tcc"
#endif

#endif /* THEPEG_DummyDecayer_H */
