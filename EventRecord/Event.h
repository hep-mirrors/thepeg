// -*- C++ -*-
#ifndef ThePEG_Event_H
#define ThePEG_Event_H
//
// This is the decalaration of the <!id>Event<!!id> class. It contains
// all <!class>Particle<!!class>s produced in the generation of an
// event. The particles are divided into <!class>Collision<!!class>s
// corresponding to the actiual collisions between incoming particles
// in a bunch crossing.
//
// <!id>Event<!!id> inherits from the <!class>Named<!!class> which holds
// the name of an event.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:Step.html">Step.h</a>
// <a href="http:SubProcess.html">SubProcess.h</a>
// <a href="http:Particle.html">Particle.h</a>
// <a href="http:SelectorBase.html">SelectorBase.h</a>
// <a href="http:Named.html">Named.h</a>
//
#include "Particle.h"
#include "StandardSelectors.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

class Event : public EventRecordBase, public Named {

public:

  friend class Collision;
  friend class PartialCollisionHandler;
  friend class CollisionHandler;

  typedef map<tcColinePtr, int> ColourLineMap;

public:

  inline void * operator new(size_t);
  inline void operator delete(void *, size_t);

public:

  Event(const PPair & newIncoming, tcEventBasePtr newHandler = tcEventBasePtr(),
	string newName = "", long newNumber = -1, double weight = 1.0);
  // The standard constructor for an Event takes as arguments a pair
  // of colliding particles (corresponding to the primary collision in
  // case of multiple collisions in an event). Optionally a pointer to
  // the EventHandler which performed the generation, an event name
  // and event number can be given.

  Event(const Event&);
  // The copy constructur

  inline ~Event();
  // The destructor.

  EventPtr clone() const;
  // Returns a full clone of this Event. All collisions, particles
  // etc. in this Event are also cloned.

public:

  inline tcEventBasePtr handler() const;
  // Return a pointer to the EventHandler which produced this
  // Event. May be the null pointer.

  template <class OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;
  // Extract particles from this event which satisfies the
  // requirements given by an object of the SelectorBase class.

  template <class OutputIterator>
  inline void selectFinalState(OutputIterator r) const;
  template <class Container>
  inline void getFinalState(Container c) const;
  inline tPVector getFinalState() const;
  // Extract all final state particles in this Event.

  tCollPtr newCollision();
  // Create a new collision in this event and return a pointer to it.

  tStepPtr newStep();
  // Create a new step in the current collision, which is a copy of
  // the last step (if any) and return a pointer to it. If no
  // collision exists, one will be added.

  inline tCollPtr primaryCollision() const;
  // Return a pointer to the primary Collision in this Event. May
  // be the null pointer.

  inline const CollisionVector & collisions() const;
  // Return a possibly empty list of collisions in this Event.

  inline tSubProPtr primarySubProcess() const;
  // Return a pointer to the primary SubProcess in the prinmary
  // Collision in this Event. May be the null pointer.

  inline const PPair & incoming() const;
  // Return a reference to the pair of colliding particles in the
  // primary Collision of this Event.

  void transform(const LorentzRotation &);
  // Transform all particles in this Event.

  inline long number() const;
  // Return the number assigned to this Event. The name is accessed
  // with the name() method of the Named base class.

  int colourLineIndex(tcColinePtr) const;
  // Return the index of the given colour line.

  void removeDecay(tPPtr);
  // Remove (recursively) the decay products from a given Particle and
  // add the particle to the list of final state particles.

  void removeParticle(tPPtr);
  // Remove the given Particle from the Collision. If this was the
  // last daughter of the mother Particle, the latter is added to the
  // list of final state particles.

  void cleanSteps();
  // Remove all steps which have no new particles introduced in them.

  inline double weight() const;
  inline void weight(double);
  // Return the weight associated with this event.

protected:

  void setInfo(tcEventBasePtr newHandler, string newName,
	       long newNumber, double weight);
  // Set event info.

  void addCollision(tCollPtr c);
  // Add a collision to this Event.

  void primaryCollision(tCollPtr c);
  // Set the primary collision in this Event.

  template <class Iterator>
  inline void addParticles(Iterator first, Iterator last);
  void addParticle(tPPtr p);
  // Add particles to this Collision.

  inline void addSubProcess(tSubProPtr p);
  // Add a new SubProcess to this Event. For book keeping purposes
  // only. The sub-processes are accessed from the differenc
  // collisions in this Event.

  void addStep(tStepPtr);
  // Add a new Step to this Collision. For book keeping purposes
  // only. The steps are accessed from the differenc
  // collisions in this Event.

  void removeEntry(tPPtr p);
  // Remove a given Particle entry.

  void rebind(const EventTranslationMap & trans);
  // When an event is clone, a shallow copy is done first, then all
  // particles etc, are cloned, and finally this method is used to see
  // to that the pointers in the cloned Event points to the cloned
  // particles etc.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  PPair theIncoming;
  // The pair of colliding particles.

  CollisionVector theCollisions;
  // A vector of collisions in this Event.

  StepSet allSteps;
  // A set of all particles in this Event.

  SubProcessSet allSubProcesses;
  // A set of all sub-processes in this Event.

  ParticleSet allParticles;
  // A set of all particles in this Event.

  tcEventBasePtr theHandler;
  // A pointer to the EventHandler which performed the generation
  // of this Event.

  mutable ColourLineMap theColourLines;
  // Map of all registered colour lines to their index numbers.

  long theNumber;
  // The number assigned to this Event.

  double theWeight;
  // The weight associated with this event.

private:

  static ClassDescription<Event> initEvent;
  // Describe concrete class with persistent data.

  inline Event();
  friend class ClassTraits<Event>;
  // Private default constructor must only be used by the
  // PersistentIStream class via the ClassTraits<Event> class .

  inline Event & operator=(const Event&);
  // The default constructor is private. So is the assignment operator.

};

ostream & operator<<(ostream &, const Event &);
// Write an Event object to a stream.

// CLASSDOC OFF

template <>
struct BaseClassTrait<Event,1> {
  typedef EventRecordBase NthBase;
};

template <>
struct ClassTraits<Event>: public ClassTraitsBase<Event> {
  static string className() { return "/ThePEG/Event"; }
  static TPtr create() { return TPtr::Create(Event()); }
};

}

#include "Event.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Event.tcc"
#endif

#endif /* ThePEG_Event_H */
