// -*- C++ -*-
#ifndef ThePEG_Event_H
#define ThePEG_Event_H
// This is the decalaration of the Event class.

#include "Particle.h"
#include "StandardSelectors.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

/**
 * The Event class contains all Particles produced in the generation
 * of an event. The particles are divided into Collisions
 * corresponding to the actiual collisions between incoming particles
 * in a bunch crossing.
 *
 * Event inherits from the Named which holds the name of an event.
 *
 * @see Collision
 * @see Step
 * @see SubProcess
 * @see Particle
 * @see SelectorBase
 * @see Named
 *
 */
class Event : public EventRecordBase, public Named {

public:

  /** PartialCollisionHandler is a friend of most Event classes. */
  friend class PartialCollisionHandler;
  /** CollisionHandler is a friend. */
  friend class CollisionHandler;
  /** Most of the Event classes are friends with each other. */
  friend class Collision;

  /** Map colour lines to indices. */
  typedef map<tcColinePtr, int> ColourLineMap;

public:

  /**
   * Event uses the FixedSizeAllocator for (de)allocation.
   */
  inline void * operator new(size_t);

  /**
   * Event uses the FixedSizeAllocator for (de)allocation.
   */
  inline void operator delete(void *, size_t);

public:

  /**
   * The standard constructor for an Event takes as arguments a pair
   * of colliding particles (corresponding to the primary collision in
   * case of multiple collisions in an event). Optionally a pointer to
   * the EventHandler which performed the generation, an event name
   * and event number can be given.
   * @param newIncoming a pair of incoming particles to the prinary Collision.
   * @param newHandler the handler object in charge of the generation
   * of this Event.
   * @param newName the name of this event.
   * @param newNumber the number of this event.
   * @param weight the weight of this event
   */
  Event(const PPair & newIncoming, tcEventBasePtr newHandler = tcEventBasePtr(),
	string newName = "", long newNumber = -1, double weight = 1.0);

  /**
   * The copy constructor.
   */
  Event(const Event&);

  /**
   * The destructor.
   */
  ~Event();

  /**
   * Returns a full clone of this Event. All collisions,
   * <code>Particle</code>s etc. in this Event are cloned.
   */
  EventPtr clone() const;

public:

  /**
   * Return a pointer to the EventHandler which produced this
   * Event. May be the null pointer.
   */
  inline tcEventBasePtr handler() const;

  /** @name Functions for accessing particles etc. */
  //@{
  /**
   * Extract particles from this event which satisfies the
   * requirements given by an object of the SelectorBase class.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   * @param s SelectorBase object defining which particles should be
   * extracted.
    */
  template <class OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;

  /**
   * Extract all final state particles in this Event.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   */
  template <class OutputIterator>
  inline void selectFinalState(OutputIterator r) const;

  /**
   * Extract all final state particles in this Event.
   * @param c a container where the extracted (pointers to) particles
   * will be appended.
   */
  template <class Container>
  inline void getFinalState(Container c) const;

  /**
   * Extract all final state particles in this Event.
   * @return a vector of pointers to the extracted particles.
   */
  inline tPVector getFinalState() const;

  /**
   * Return a pointer to the primary Collision in this Event. May
   * be the null pointer.
   */
  inline tCollPtr primaryCollision() const;

  /**
   * Return a possibly empty list of collisions in this Event.
   */
  inline const CollisionVector & collisions() const;

  /**
   * Return a pointer to the primary SubProcess in the prinmary
   * Collision in this Event. May be the null pointer.
   */
  inline tSubProPtr primarySubProcess() const;

  /**
   * Return a reference to the pair of colliding particles in the
   * primary Collision of this Event.
   */
  inline const PPair & incoming() const;

  //@}

  /**
   * Create a new Collision in this event and return a pointer to it.
   */
  tCollPtr newCollision();

  /**
   * Create a new Step in the current Collision, which is a copy of
   * the last Step (if any) and return a pointer to it. If no
   * collision exists, one will be added.
   */
  tStepPtr newStep();

  /**
   * Transform all particles in this Event.
   */
  void transform(const LorentzRotation &);

  /**
   * Return the number assigned to this Event. The name is accessed
   * with the name() method of the Named base class.
   */
  inline long number() const;

  /**
   * Return the index of the given colour line.
   */
  int colourLineIndex(tcColinePtr) const;

  /** @name Functions for removing entires from an Event. */
  //@{
  /**
   * Remove (recursively) the decay products from a given Particle and
   * add the particle to the list of final state particles.
   */
  void removeDecay(tPPtr);

  /**
   * Remove the given Particle from the Collision. If this was the
   * last daughter of the mother Particle, the latter is added to the
   * list of final state particles.
   */
  void removeParticle(tPPtr);

  /**
   * Remove all steps which have no new particles introduced in them.
   */
  void cleanSteps();

  //@}

  /**
   * Return the weight associated with this event.
   */
  inline double weight() const;

  /**
   * Set the weight associated with this event.
   */
  inline void weight(double);

protected:

  /**
   * Set event info.
   */
  void setInfo(tcEventBasePtr newHandler, string newName,
	       long newNumber, double weight);

  /**
   * Add a collision to this Event.
   */
  void addCollision(tCollPtr c);

  /**
   * Set the primary collision in this Event.
   */
  void primaryCollision(tCollPtr c);

  /**
   * Add a range of particles to this Collision.
   */
  template <class Iterator>
  inline void addParticles(Iterator first, Iterator last);

  /**
   * Add a particle to this Collision.
   */
  void addParticle(tPPtr p);

  /**
   * Add a new SubProcess to this Event. For book keeping purposes
   * only. The sub-processes are accessed from the different
   * Collisions in this Event.
   */
  inline void addSubProcess(tSubProPtr p);

  /**
   * Add a new Step to this Collision. For book keeping purposes
   * only. The steps are accessed from the different Collisions in
   * this Event.
   */
  void addStep(tStepPtr);

  /**
   * Remove a given Particle entry.
   */
  void removeEntry(tPPtr p);

  /**
   * Rebind to cloned objects. When an Event is cloned, a shallow
   * copy is done first, then all <code>Particle</code>s etc, are
   * cloned, and finally this method is used to see to that the
   * pointers in the cloned Event points to the cloned
   * <code>Particle</code>s etc.
   */
  void rebind(const EventTranslationMap & trans);

public:

  /**
   * Standard function for writing to a persistent stream.
   */
  void persistentOutput(PersistentOStream &) const;

  /**
   * Standard functions for reading from a persistent stream.
   */
  void persistentInput(PersistentIStream &, int);

  /**
   * Standard Init function. @see Base::Init().
   */
  static void Init();

private:

  /**
   * The pair of colliding particles.
   */
  PPair theIncoming;

  /**
   * A vector of collisions in this Event.
   */
  CollisionVector theCollisions;

  /**
   * A set of all particles in this Event.
   */
  StepSet allSteps;

  /**
   * A set of all sub-processes in this Event.
   */
  SubProcessSet allSubProcesses;

  /**
   * A set of all particles in this Event.
   */
  ParticleSet allParticles;

  /**
   * A pointer to the EventHandler which performed the generation
   * of this Event.
   */
  tcEventBasePtr theHandler;

  /**
   * Map of all registered colour lines to their index numbers.
   */
  mutable ColourLineMap theColourLines;

  /**
   * The number assigned to this Event.
   */
  long theNumber;

  /**
   * The weight associated with this event.
   */
  double theWeight;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<Event> initEvent;

  /**
   * Private default constructor must only be used by the
   * PersistentIStream class via the ClassTraits<Event> class .
   */
  inline Event();

  /**
   * The ClassTraits<Event> class must be a friend to be able to
   * use the private default constructor.
   */
  friend class ClassTraits<Event>;

  /**
   * The assignment operator is private and not implemented.
   */
  inline Event & operator=(const Event&);

};

/** Output a Event to a standard ostream. */
ostream & operator<<(ostream &, const Event &);


/** This template specialization informs ThePEG about the
 *  base class of Event. */
template <>
struct BaseClassTrait<Event,1> {
  /** Typedef of the first base class of Collision. */
  typedef EventRecordBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the Event class and how to create it. */
template <>
struct ClassTraits<Event>: public ClassTraitsBase<Event> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::Event"; }
  /** Create a Event object. */
  static TPtr create() { return TPtr::Create(Event()); }
};

}

#include "Event.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Event.tcc"
#endif

#endif /* ThePEG_Event_H */
