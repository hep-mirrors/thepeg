// -*- C++ -*-
#ifndef ThePEG_Hint_H
#define ThePEG_Hint_H
//
// This is the declaration of the <!id>Hint<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Hint<!!id> is a base class to be used to pass information
// between <!class>StepHandler<!!class>s, which cannot be convayed
// through the <!class>Event<!!class> record. The base class contains
// a vector of of tagged particles. A <!class>StepHandler<!!class> is
// always given a hint, and is only allowed to treat
// <!class>Particle<!!class>s from the current <!class>Step<!!class>
// which are listed in the vector of tagged particles in the hint (if
// this vector is empty the <!class>StepHandler<!!class> may treat all
// particles in the <!class>Step<!!class>.
//
// A <!id>Hint<!!id> may have the stop flag set. In this case
// the <!class>StepHandler<!!class> to which the hint is assigned is
// not called, and the event generation is stopped.
//
// A <!id>Hint<!!id> may be given a scale, but what a
// <!class>StepHandler<!!class> does with this and other pieces of
// information possibly supplied by subclasses of <!id>Hint<!!id>, is
// not defined.
//
// There is a special <!id>Hint<!!id> which is kept as the static
// member called <!id>Hint::theDefaultHint<!!id>. Although any default
// constructed Hint object would work as a default hint, only pointers
// to this static object should be used where a default hint is
// needed.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StepHandler.html">StepHandler.h</a>
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:Particle.html">Particle.h</a>
// <a href="http:Event.html">Event.h</a>
// <a href="http:Step.html">Step.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"

namespace ThePEG {

class Hint: public Base {

public:

  inline Hint();
  inline Hint(const Hint &);
  inline ~Hint();
  // Default ctors and dtor.

public:

  inline bool tagged() const;
  // Return true if there are tagged particles in the hint.

  tPVector tagged(const Step & s) const;
  // Return a list of pointers to particles to be handled. A handler
  // is not allowed to touch other particles in the event record. If a
  // particle which has been flagged by the hint is no longer present
  // in the current Step, a null pointer is inserted in its place.

  template <typename InputIterator>
  inline void tag(InputIterator first, InputIterator last);
  inline void tag(tPPtr);
  // Add particles to the list of tagged particles.

  inline void stop(bool);
  inline bool stop() const;
  // Set/get the stop hint.

  inline void scale(const Scale &);
  inline const Scale & scale() const;
  // Set/get the scale.

  inline static tHintPtr Default();
  // Return a pointer to the default hint.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  tPVector theTagged;
  // The vector of tagged particles.

  Scale theScale;
  // The scale.

  bool theStopFlag;
  // The stop hint.

  static Hint theDefaultHint;
  // The default hint.

private:

  static ClassDescription<Hint> initHint;

  inline const Hint & operator=(const Hint & h);
  // Assignment is private and non-existing.

};

// CLASSDOC OFF

template <>
struct BaseClassTrait<Hint,1> {
  typedef Base NthBase;
};

template <>
struct ClassTraits<Hint>:
    public ClassTraitsBase<Hint> {
  static string className() {
    return "/ThePEG/Hint";
  }
};

}

#include "Hint.icc"

#endif /* ThePEG_Hint_H */
