// -*- C++ -*-
#ifndef ThePEG_Strategy_H
#define ThePEG_Strategy_H
//
// This is the declaration of the <!id>Strategy<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Strategy<!!id> class represents a general strategy to be
// assigned to an <!class>EventGenerator<!!class>. It contains a set
// of default <!class>ParticleData<!!class> objects which takes
// presedence over the ones in the <!class>Repository<!!class>. It
// also contains a set of other default objects which are
// automatically assigned to all <!class>Reference<!!class> interfaces
// which have the <!id>defaultIfNull<!!id> flag set.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:Repository.html">Repository.h</a>,
// <a href="http:Reference.html">Reference.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "Strategy.fh"
// #include "Strategy.xh"
#include "ThePEG/Interface/Interfaced.h"

namespace ThePEG {

class Strategy: public Interfaced {

public:

  Strategy();
  Strategy(const Strategy &);
  virtual ~Strategy();
  // Standard ctors and dtor

public:

  inline const ParticleMap & particles() const;
  // Return the map of local particles.

  inline const vector<IPtr> & defaultObjects() const;
  // Return the vector of default objects.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

private:

  inline ParticleMap & particles();
  // Return the map of local particles.

private:

  ParticleMap theParticles;
  // the map of default particles.

  vector<IPtr> theDefaultObjects;
  // A vector of default objects.

private:

  void setLocalParticles(PDPtr pd, int);
  void insLocalParticles(PDPtr pd, int);
  void delLocalParticles(int place);
  vector<PDPtr> getLocalParticles() const;
  // Utility functions used by the interface.

private:

  static ClassDescription<Strategy> initStrategy;

  Strategy & operator=(const Strategy &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<Strategy,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<Strategy>:
    public ClassTraitsBase<Strategy> {
  static string className() {
    return "/ThePEG/Strategy";
  }
};

}

#include "Strategy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Strategy.tcc"
#endif

#endif /* ThePEG_Strategy_H */
