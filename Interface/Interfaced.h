// -*- C++ -*-
#ifndef ThePEG_Interfaced_H
#define ThePEG_Interfaced_H
//
// This is the declaration of the <!id>Interfaced<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Interfaced<!!id> class is derived from the
// <!class>InterfacedBase<!!class> class adding a couple of things
// particular to ThePEG, in an attempt to keep the
// <!class>InterfacedBase<!!class> class as generic as possible.
//
// The main addition is that the <!id>Interfaced<!!id> class has a
// pointer to an <!class>EventGenerator<!!class> object. During the
// run-phase this point to the EventGenerator controlling the run in
// which the <!id>Interfaced<!!id> object is used. Through this
// EventGenerator there is quick access to eg. the set of
// <!class>ParticleData<!!class> objects used, and the default
// <!class>RandomGenerator<!!class> for the run. Note that no
// <!class>EventGenerator<!!class> object is available to the
// <!id>Interfaced<!!id> object during the setup phase.
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>,
// <a href="http:RandomGenerator.html">RandomGenerator.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfacedBase.h"

namespace ThePEG {

class Interfaced: public InterfacedBase {

  friend class Repository;

public:

  inline virtual ~Interfaced();
  // Empty virtual destructor

public:
  // Functions which are to be used during the actual event
  // generation, after the setup is complete.

  PPtr getParticle(long) const;
  // Create a new particle instance given a id number.

  PDPtr getParticleData(long) const;
  // Return a pointer to the particle data object corresponding to the
  // given id number.

  inline bool used() const;
  // Returns true if this object has actally been used.

  inline void useMe() const;
  // Should be called to indicate that this object has actually been
  // used.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  static void registerRepository(IBPtr);
  static void registerRepository(IBPtr, string newName);
  // Avoid other classes including the Repository class just to use
  // the Register function.

  inline Interfaced();
  inline Interfaced(string newName);
  inline Interfaced(const Interfaced &);
  // Protected constructors.

  inline tEGPtr generator() const;
  // Return a pointer to the EventGenerator controlling the run.
  // During the setup phase this returns a null pointer.

  inline virtual void doupdate() throw(UpdateException) = 0;
  // This function is called everytime the object setup is
  // changed. Also if the setup is changed for an object on which this
  // is dependent. It should throw an UpdateException if the setup is
  // such that the object would not work properly. Note that the
  // 'generator()' is not available when this method is called.

  inline virtual void doinit() throw (InitException) = 0;
  // This is called before the start of an event generation
  // run. Nothing should have changed since the last 'update' call.
  // If the setup is not sane, an InitException should be thrown.

  inline virtual void dofinish() = 0;
  // This is called after the event generation run is done. It can
  // e.g. be used to write out statistics on the output file.

private:

  void setUsed() const;
  // Used internally by 'useMe'

  tEGPtr theGenerator;
  // A pointer to the EventGenerator controlling the run.

  mutable bool theUseFlag;
  // Flag to tell whether this object has been used or not.

private:

  static AbstractClassDescription<Interfaced> initInterfaced;
  // Standard Initialization object.

  Interfaced & operator=(const Interfaced &);
  //  Private and non-existent assignment operator.

public:

  virtual void debug() const;
  // This method may be implemented by derived classes to facilitate
  // debugging.

};

template <>
struct BaseClassTrait<Interfaced,1> {
  typedef InterfacedBase NthBase;
};

template <>
struct ClassTraits<Interfaced>: public ClassTraitsBase<Interfaced> {
  static string className() { return "/ThePEG/Interfaced"; }
};

}

#include "Interfaced.icc"

#endif /* ThePEG_Interfaced_H */
