// -*- C++ -*-
#ifndef THEPEG_WeakToHadronsDecayer_H
#define THEPEG_WeakToHadronsDecayer_H
//
// This is the declaration of the <!id>WeakToHadronsDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class performs weak decays of taus and charmed and bottom
// hadrons. The intermediate W can either decay leptonically in which
// case standard V-A matrix element is used, or it can decay into
// quarks in which case the conversion into quarks is performed as for
// the QuarkToHadronsDecayer base class. In both cases the W decay
// products should be specified first. The spectator system can either
// be specified in terms of hadrons or in terms of quarks which will
// be collapsed into a single hadron.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:QuarkToHadronsDecayer.html">QuarkToHadronsDecayer.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/PDT/QuarksToHadronsDecayer.h"
// #include "WeakToHadronsDecayer.fh"
// #include "WeakToHadronsDecayer.xh"

namespace ThePEG {

class WeakToHadronsDecayer: public QuarksToHadronsDecayer {

public:

  inline WeakToHadronsDecayer();
  inline WeakToHadronsDecayer(const WeakToHadronsDecayer &);
  virtual ~WeakToHadronsDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual PVector getHadrons(int Nh, tcPDVector quarks) const;
  // Produce the specified number of hadrons from the specified
  // quarks. The last quark is considered to be a spectator quark.

  virtual double reweight(const Particle & parent,
			  const PVector & children) const;
  // Called by base class distribute() to reweight the default flat
  // phase spece.

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

  static ClassDescription<WeakToHadronsDecayer> initWeakToHadronsDecayer;
  // Describe a concrete class with persistent data.

  WeakToHadronsDecayer & operator=(const WeakToHadronsDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of WeakToHadronsDecayer.
template <>
struct BaseClassTrait<WeakToHadronsDecayer,1> {
  typedef QuarksToHadronsDecayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<WeakToHadronsDecayer>
  : public ClassTraitsBase<WeakToHadronsDecayer> {
  static string className() { return "ThePEG::WeakToHadronsDecayer"; }
  // Return the class name.
  static string library() { return "WeakToHadronsDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "WeakToHadronsDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "WeakToHadronsDecayer.tcc"
#endif

#endif /* THEPEG_WeakToHadronsDecayer_H */
