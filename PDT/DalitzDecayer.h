// -*- C++ -*-
#ifndef THEPEG_DalitzDecayer_H
#define THEPEG_DalitzDecayer_H
//
// This is the declaration of the <!id>DalitzDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs Dalitz decays into gamma e+ e-.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/PDT/Decayer.h"
// #include "DalitzDecayer.fh"
// #include "DalitzDecayer.xh"

namespace ThePEG {

class DalitzDecayer: public Decayer {

public:

  inline DalitzDecayer();
  inline DalitzDecayer(const DalitzDecayer &);
  virtual ~DalitzDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.


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
  virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  PDPtr rho;
  // Quick access to the rho particle data.

private:

  static ClassDescription<DalitzDecayer> initDalitzDecayer;
  // Describe a concrete class with persistent data.

  DalitzDecayer & operator=(const DalitzDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of DalitzDecayer.
template <>
struct BaseClassTrait<DalitzDecayer,1> {
  typedef Decayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<DalitzDecayer>
  : public ClassTraitsBase<DalitzDecayer> {
  static string className() { return "/ThePEG/DalitzDecayer"; }
  // Return the class name.
  static string library() { return "DalitzDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "DalitzDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DalitzDecayer.tcc"
#endif

#endif /* THEPEG_DalitzDecayer_H */
