// -*- C++ -*-
#ifndef ThePEG_Collision_H
#define ThePEG_Collision_H
// This is the decalaration of the Collision class. It

#include "ThePEG/EventRecord/EventConfig.h"
#include "ThePEG/EventRecord/Particle.h"
#include "StandardSelectors.h"
#include "ThePEG/CLHEPWrap/LorentzVector.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

/**
 * This is the decalaration of the Collision class. It contains all
 * <code>Particle</code>s produced in the generation of a collision
 * between two particles in an Event. The particles are divided into
 * <code>Step</code>s corresponding to the particles present after a
 * given step in the event generation. The collision also carries
 * information about the <code>SubProcesses</code> in the collision.
 *
 * @see Event
 * @see Step
 * @see SubProcess
 * @see Particle
 */
class Collision: public EventRecordBase {

public:

  /** PartialCollisionHandler is a friend of most Event classes. */
  friend class PartialCollisionHandler;
  /** Most of the Event classes are friends with each other. */
  friend class CollisionHandler;
  /** Most of the Event classes are friends with each other. */
  friend class Event;
  /** Most of the Event classes are friends with each other. */
  friend class Step;

public:

  /**
   * Collision uses the FixedSizeAllocator for (de)allocation.
   */
  inline void * operator new(size_t);

  /**
   * Collision uses the FixedSizeAllocator for (de)allocation.
   */
  inline void operator delete(void *, size_t);

public:

  /**
   * The standard constructor takes a pair of incoming particles as
   * argument. Optionally can be given a pointer to the Event which
   * this Collision belongs, and a pointer to the CollisionHandler
   * which produced this collision.
   * @param newIncoming a pair of incoming particles.
   * @param newEvent the event to which this Collision belongs.
   * @param newHandler the handler object in charge of the generation
   * of this Collision.
   */
  Collision(const PPair & newIncoming, tEventPtr newEvent = tEventPtr(),
	    tcEventBasePtr newHandler = tcEventBasePtr());

  /**
   * The copy constructor.
   */
  Collision(const Collision &);

  /**
   * The destructor
   */
  inline ~Collision();

public:

  /**
   * Create a new step in this collision, which is a copy of
   * the last step (if any) and return a pointer to it.
   * @param newHandler the handler object in charge of generating the
   * new step.
   */
  tStepPtr newStep(tcEventBasePtr newHandler = tcEventBasePtr());

  /**
   * Return a pointer to the CollisionHandler which produced this
   * Collision. May be the null pointer.
   */
  inline tcEventBasePtr handler() const;

  /**
   * Return a pointer to the Event to which this Collision
   * belongs. May be the null pointer.
   */
  inline tEventPtr event() const;

  /** @name Functions for accessing the <code>Particle</code>s, <code>Step</code>s and <code>SubProcess</code>es of a Collision. */
  //@{
  /**
   * Extract particles from this collision which satisfies the
   * requirements given by an object of the SelectorBase class.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   * @param s SelectorBase object defining which particles should be
   * extracted.
   */
  template <class OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;

  /**
   * Extract all final state particles in this Collision.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   */
  template <class OutputIterator>
  inline void selectFinalState(OutputIterator r) const;

  /**
   * Extract all final state particles in this Collision.
   * @return a vector of pointers to the extracted particles.
   */
  inline tPVector getFinalState() const;

  /**
   * Return a pointer to the primary SubProcess in this Collision. May
   * be the null pointer.
   */
  inline tSubProPtr primarySubProcess() const;

  /**
   * Return the possibly empty list of sub processes in this Collision.
   */
  inline const SubProcessVector & subProcesses() const;

  /**
   * Return a const pointer to the last step in this Collission.
   */
  inline tcStepPtr finalStep() const;

  /**
   * Return a pointer to the last step in this Collission.
   */
  inline tStepPtr finalStep();

  /**
   * Return the vector of steps in this Collision. 
   */
  inline const StepVector & steps() const;

  /**
   * Return a pointer to a given Step in this Collision.
   */
  inline tcStepPtr step(unsigned int i) const;

  /**
   * Return a reference to the pair of colliding particles in this
   * Collision.
   */

  inline const PPair & incoming() const;
  /**
   * Return the set of remnants in this collision. Remnants are
   * defined as the daughters of the incoming particles which are not
   * incoming particles to any SubProcess or children thereof which
   * are present in the final state.
   */
  tParticleSet getRemnants() const;

  /**
   * Return true if the given particle is a remnant of the colliding
   * particles. Calls the getRemnants method, so to check several
   * particles it is better to call getRemnants directly and check if
   * the particles are members of the resulting set by hand.
   */
  inline bool isRemnant(tPPtr) const;

  //@}

  /**
   * Return the vertex position of this Collision.
   */
  inline const LorentzPoint & vertex() const;

  /**
   * Set the vertex position of this Collision.
   */
  inline void vertex(const LorentzPoint &);

  /**
   * Transform all particles in this Collision.
   */
  void transform(const LorentzRotation &);

  /**
   * Return the total invariant mass squared of the final-state
   * particles in this Collision.
   */
  inline Energy2 m2() const;

  /** @name Functions for removing entires from a Collision. */
  //@{
  /**
   * Remove (recursively) the decay products from a given Particle and
   * add the particle to the list of final state particles.
   */
  void removeDecay(tPPtr);

  /**
   * Remove (recursively) the given Particle from the Collision. If
   * this was the last daughter of the mother Particle, the latter is
   * added to the list of final state particles.
   */
  void removeParticle(tPPtr);

  /**
   * Remove all steps which have no new particles introduced in them.
   */
  void cleanSteps();

  /**
   * Remove the last Step in this Collision.
   */
  void popStep();

  //@}

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

protected:

  /** @name Internal functions for adding and removing entires in a Collision. */
  //@{
  /**
   * Add a new Step to this Collision.
   */
  void addStep(tStepPtr s);

  /**
   * Add a new SubProcess to this Collision.
   */
  void addSubProcess(tSubProPtr p);

  /**
   * Add a range of particles to this Collision.
   */
  template <class Iterator>
  void addParticles(Iterator first, Iterator last);

  /**
   * Add a particle to this Collision.
   */
  void addParticle(tPPtr p);

  /**
   * Remove a given Particle entry.
   */
  void removeEntry(tPPtr p);

  //@}

  /**
   * Return a reference to the list of all particles in this Collision.
   */
  inline const ParticleSet & all() const;

  /**
   * Clone this Collision. This also makes clones of all steps, sub
   * processes and particles in this Collision.
   */
  CollPtr clone() const;

  /**
   * Rebind to cloned objects. When a Collision is cloned, a shallow
   * copy is done first, then all <code>Particle</code>s etc, are
   * cloned, and finally this method is used to see to that the
   * pointers in the cloned Collision points to the cloned
   * <code>particles</code> etc.
   */
  void rebind(const EventTranslationMap & trans);

private:

  /**
   * The pair of colliding particles.
   */
  PPair theIncoming;

  /**
   * A vector of all steps in this Collision.
   */
  StepVector theSteps;

  /**
   * A vector of all sub-processes in this Collision. The front
   * element points to the primary sub-process.
   */
  SubProcessVector theSubProcesses;

  /**
   * A set of all particles in this Collision.
   */
  ParticleSet allParticles;

  /**
   * A pointer to the Event to which this Collision belongs.
   */
  tEventPtr theEvent;

  /**
   * A pointer to the CollisionHandler which performed the generation
   * of this Collision.
   */
  tcEventBasePtr theHandler;

  /**
   * The vertex position of this Collision
   */
  LorentzPoint theVertex;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<Collision> initCollision;

  /**
   * Private default constructor must only be used by the
   * PersistentIStream class via the ClassTraits<Collision> class .
   */
  inline Collision();

  /**
   * The ClassTraits<Collision> class must be a friend to be able to
   * use the private default constructor.
   */
  friend class ClassTraits<Collision>;

  /**
   * The assignment operator is private and not implemented.
   */
  inline Collision & operator=(const Collision &);

  /** Output to a standard ostream. */
  friend ostream & operator<<(ostream & os, const Collision & c);

};

  /** Output a Collision to a standard ostream. */
ostream & operator<<(ostream &, const Collision &);


/** This template specialization informs ThePEG about the
 *  base class of Collision. */
template <>
struct BaseClassTrait<Collision,1> {
  /** Typedef of the first base class of THECLASS. */
  typedef EventRecordBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the Collision class and how to create it. */
template <>
struct ClassTraits<Collision>: public ClassTraitsBase<Collision> {
  /** Return a platform-independent class name */
  static string className() { return "/ThePEG/Collision"; }
  /** Create a Collision object. */
  static TPtr create() { return TPtr::Create(Collision()); }
};

}

#include "Collision.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Collision.tcc"
#endif

#endif /* ThePEG_Collision_H */
