// -*- C++ -*-
#ifndef ThePEG_Collision_H
#define ThePEG_Collision_H
// This is the decalaration of the <!id>Collision<!!> class. It
// contains all <!class>Particle<!!class>s produced in the generation
// of a collision between two particles in an
// <!class>Event<!!class>. The particles are divided into
// <!class>Step<!!class>s corresponding to the particles present after
// a given step in the event generation. The collision also carries
// information about the <!class>SubProcesse<!!class>s in the
// collision.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>
// <a href="http:Step.html">Step.h</a>
// <a href="http:SubProcess.html">SubProcess.h</a>
// <a href="http:Particle.html">Particle.h</a>
// 

#include "ThePEG/EventRecord/EventConfig.h"
#include "ThePEG/EventRecord/Particle.h"
#include "StandardSelectors.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

class Collision: public EventRecordBase {

public:

  friend class PartialCollisionHandler;
  friend class CollisionHandler;
  friend class Event;
  friend class Step;

public:

  inline void * operator new(size_t);
  inline void operator delete(void *, size_t);

public:

  Collision(const PPair & newIncoming, tEventPtr newEvent = tEventPtr(),
	    tcEventBasePtr newHandler = tcEventBasePtr());
  // The standard constructor takes a pair of incoming particles as
  // argument. Optionally can be given a pointer to the Event which
  // this Collision belongs, and a pointer to the CollisionHandler
  // which produced this collision.

  Collision(const Collision &);
  // The copy constructor.

  inline ~Collision();
  // The destructor

public:

  inline tcEventBasePtr handler() const;
  // Return a pointer to the CollisionHandler which produced this
  // Collision. May be the null pointer.

  tStepPtr newStep(tcEventBasePtr newHandler = tcEventBasePtr());
  // Create a new step in this collision, which is a copy of
  // the last step (if any) and return a pointer to it.

  inline tEventPtr event() const;
  // Return a pointer to the Event to which this Collision
  // belongs. May be the null pointer.

  template <class OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;
  // Extract particles from this collision which satisfies the
  // requirements given by an object of the SelectorBase class.

  template <class OutputIterator>
  inline void selectFinalState(OutputIterator r) const;
  inline tPVector getFinalState() const;
  // Extract all final state particles in this Collision.

  inline tSubProPtr primarySubProcess() const;
  // Return a pointer to the primary SubProcess in this Collision. May
  // be the null pointer.

  inline const SubProcessVector & subProcesses() const;
  // Return a possibly empty list of sub process in this Collision.

  inline tcStepPtr finalStep() const;
  inline tStepPtr finalStep();
  // Return a pointer to the last step in this Collission.

  inline const StepVector & steps() const;
  // Return the vector of steps in this Collision. 

  inline tcStepPtr step(unsigned int i) const;
  // Return a pointer to a given Step in this Collision.

  inline const PPair & incoming() const;
  // Return a reference to the pair of colliding particles in this
  // Collision.

  inline const LorentzPoint & vertex() const;
  // Return the vertex position of this Collision.

  inline void vertex(const LorentzPoint &);
  // Set the vertex position of this Collision.

  void transform(const LorentzRotation &);
  // Transform all particles in this Collision.

  inline Energy2 m2() const;
  // Return the total invariant mass squared of the particles in this
  // Collision.

  void removeDecay(tPPtr);
  // Remove (recursively) the decay products from a given Particle and
  // add the particle to the list of final state particles.

  void removeParticle(tPPtr);
  // Remove (recursively) the given Particle from the Collision. If
  // this was the last daughter of the mother Particle, the latter is
  // added to the list of final state particles.

  void cleanSteps();
  // Remove all steps which have no new particles introduced in them.

  void popStep();
  // Remove the last Step in this Collision.

  tParticleSet getRemnants() const;
  // Retrun the set of remnants in this collision.

  inline bool isRemnant(tPPtr) const;
  // Return true if the given particle is a remnant of the colliding
  // particles. Calls the getRemnants method, so to check several
  // particles it is better to call getRemnants directly and check if
  // the particles are members of the resulting set by hand.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  void addStep(tStepPtr s);
  // Add a new Step to this Collision.

  void addSubProcess(tSubProPtr p);
  // Add a new SubProcess to this Collision.

  template <class Iterator>
  void addParticles(Iterator first, Iterator last);
  void addParticle(tPPtr p);
  // Add particles to this Collision.

  void removeEntry(tPPtr p);
  // Remove a given Particle entry.

  inline const ParticleSet & all() const;
  // Return a reference to the list of all particles in this Collision.

  CollPtr clone() const;
  // Clone this Collision. This also makes clones of all steps, sub
  // processes and particles in this Collision.

  void rebind(const EventTranslationMap & trans);
  // When a collision is cloned, a shallow copy is done first, then all
  // particles etc, are cloned, and finally this method is used to see
  // to that the pointers in the cloned Collision points to the cloned
  // particles etc.

private:

  PPair theIncoming;
  // The pair of colliding particles.

  StepVector theSteps;
  // A vector of all steps in this Collision.

  SubProcessVector theSubProcesses;
  // A vector of all sub-processes in this Collision. The front
  // element points to the primary sub-process.

  ParticleSet allParticles;
  // A set of all particles in this Collision.

  tEventPtr theEvent;
  // A pointer to the Event to which this Collision belongs.

  tcEventBasePtr theHandler;
  // A pointer to the CollisionHandler which performed the generation
  // of this Collision.

  LorentzPoint theVertex;
  // The vertex position of this Collision

private:

  static ClassDescription<Collision> initCollision;
  // Describe concrete class with persistent data.

  inline Collision();
  friend class ClassTraits<Collision>;
  // Private default constructor must only be used by the
  // PersistentIStream class via the ClassTraits<Collision> class .

  inline Collision & operator=(const Collision &);
  // The assignment operator is private.

  friend ostream & operator<<(ostream & os, const Collision & c);

};

ostream & operator<<(ostream &, const Collision &);
// Write a Collision object to a stream.

// CLASSDOC OFF

template <>
struct BaseClassTrait<Collision,1> {
  typedef EventRecordBase NthBase;
};

template <>
struct ClassTraits<Collision>: public ClassTraitsBase<Collision> {
  static string className() { return "/ThePEG/Collision"; }
  static TPtr create() { return TPtr::Create(Collision()); }
};

}

#include "Collision.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Collision.tcc"
#endif

#endif /* ThePEG_Collision_H */
