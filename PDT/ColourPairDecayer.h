// -*- C++ -*-
#ifndef THEPEG_ColourPairDecayer_H
#define THEPEG_ColourPairDecayer_H
//
// This is the declaration of the <!id>ColourPairDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs decays according to phase space into two or
// more particles, some of which may be coloured. The coloured
// particles must come in pairs and will be colour connected
// pair-wise.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FlatDecayer.html">FlatDecayer.h</a>,
// <a href="http:Particle.html">Particle.h</a>.
// 

#include "ThePEG/PDT/FlatDecayer.h"
// #include "ColourPairDecayer.fh"
// #include "ColourPairDecayer.xh"

namespace ThePEG {

class ColourPairDecayer: public FlatDecayer {

public:

  inline ColourPairDecayer();
  inline ColourPairDecayer(const ColourPairDecayer &);
  virtual ~ColourPairDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector getChildren(const DecayMode & dm,
				     const Particle & parent) const;
  // Used by the base class' decay() to produce instances of the children.

  inline bool shower() const;
  // Return true if the produced gluons should be showered.

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

  bool doShower;
  // If true the produced gluons should be showered.

private:

  static ClassDescription<ColourPairDecayer> initColourPairDecayer;
  // Describe a concrete class with persistent data.

  ColourPairDecayer & operator=(const ColourPairDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ColourPairDecayer.
template <>
struct BaseClassTrait<ColourPairDecayer,1> {
  typedef FlatDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ColourPairDecayer>
  : public ClassTraitsBase<ColourPairDecayer> {
  static string className() { return "ThePEG::ColourPairDecayer"; }
  // Return the class name.
  static string library() { return "ColourPairDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "ColourPairDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ColourPairDecayer.tcc"
#endif

#endif /* THEPEG_ColourPairDecayer_H */
