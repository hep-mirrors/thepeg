// -*- C++ -*-
#ifndef ThePEG_StandardRandom_H
#define ThePEG_StandardRandom_H
//
// This is the declaration of the <!id>StandardRandom<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>StandardRandom<!!id> inherits from the
// <!class>RandomGenerator<!!class> class and implements the
// <!class>JamesRandom<!!class> engine from CLHEP.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RandomGenerator.html">RandomGenerator.h</a>,
// <a href="http:.JamesRandomhtml">JamesRandom.h</a>.
// 

#include "RandomGenerator.h"
#include "ThePEG/CLHEPWrap/JamesRandom.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
// #include "StandardRandom.fh"
// #include "StandardRandom.xh"

namespace ThePEG {

class StandardRandom: public RandomGenerator {

public:

  inline StandardRandom();
  inline StandardRandom(const StandardRandom &);
  virtual ~StandardRandom();
  // Standard ctors and dtor

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

public:

  virtual RandomEngine & randomGenerator();
  // return a reference to the HepJamesRandom engine.

  virtual void setSeed(long seed);
  // Reset the underlying CLHEP random engine with the given seed.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

  virtual void rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  JamesRandom theRandomGenerator;
  // The random generator.

private:

  static ClassDescription<StandardRandom> initStandardRandom;

  StandardRandom & operator=(const StandardRandom &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<StandardRandom,1> {
  typedef RandomGenerator NthBase;
};

template <>
struct ClassTraits<StandardRandom>: public ClassTraitsBase<StandardRandom> {
  static string className() { return "/ThePEG/StandardRandom"; }
};

}

#include "StandardRandom.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardRandom.tcc"
#endif

#endif /* ThePEG_StandardRandom_H */
