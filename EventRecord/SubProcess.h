// -*- C++ -*-
#ifndef ThePEG_SubProcess_H
#define ThePEG_SubProcess_H
// This is the declaration of the SubProcess class.


#include <vector>
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

/**
 * A SubProcess object represents a hard \f$2\rightarrow n\f$
 * sub-process in a collision. It carries information about the
 * incoming and outgoing particles, as well as possible intermediate
 * ones. It also has a pointer to the MEBase object which generated
 * the sub-process.
 *
 * @see Event
 * @see Particle
 */
class SubProcess: public EventRecordBase {

public:

  /** Most of the Event classes are friends with each other. */
  friend class Step;
  /** Most of the Event classes are friends with each other. */
  friend class Collision;
 
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
   * Standard constructor.
   * @param newIncoming the two incoming partons.
   * @param newCollision the Collision to which this SubProcess belongs.
   * @param newHandler the MEBase object which generated this SubProcess.
   */
  SubProcess(const PPair & newIncoming,
	     tCollPtr newCollision = tCollPtr(),
	     tcEventBasePtr newHandler = tcEventBasePtr());

  /**
   * Copy constructor.
   */
  SubProcess(const SubProcess &);

  /**
   * Destructor.
   */
  inline ~SubProcess();

  /**
   * A pointer to the MEBase object which generated this SubProcess.
   */
  inline tcEventBasePtr handler() const;

  /**
   * A pointer to the collision to which this sub-process belongs.
   */
  inline tCollPtr collision() const;

  /**
   * The pair of incoming partons.
   */
  inline const PPair & incoming() const;

  /**
   * A reference to the vector of intermediate partons.
   */
  inline const ParticleVector & intermediates() const;

  /**
   * A reference to the vector of outgoing particles.
   */
  inline const ParticleVector & outgoing() const;

  /**
   * Set the vector of outgoing particles.
   */
  template <class InputIterator>
  void setOutgoing(InputIterator, InputIterator);

  /**
   * Add a particle to the list of outgoing ones. If \a fixrelations
   * is true the mother daughter pointers will be set to/from the
   * incoming partons.
   */
  void addOutgoing(tPPtr p, bool fixrelations = true);

  /**
   * Set the vector of intermediate particles.
   */
  template <class InputIterator>
  void setIntermediates(InputIterator, InputIterator);

  /**
   * Add a particle to the list of intermediate ones. If \a fixrelations
   * is true the mother daughter pointers will be set to/from the
   * incoming partons.
   */
  void addIntermediate(tPPtr p, bool fixrelations = true);

  /**
   * Remove a particle entry from this sub-process.
   */
  void removeEntry(tPPtr p);

  /**
   * Return a clone of this sub process.
   */
  SubProPtr clone() const;

protected:

  /**
   * Rebind to cloned objects. When a SubProcess is cloned, a shallow
   * copy is done first, then all <code>Particle</code>s etc, are
   * cloned, and finally this method is used to see to that the
   * pointers in the cloned SubProcess points to the cloned
   * <code>Particle</code>s etc.
   */
  void rebind(const EventTranslationMap & trans);


public:

  /**
   * Perform a LorentzTransformation of all particles in the sub
   * process.
   */
  void transform(const LorentzRotation &);

  /**
   * Return the value of the Mandelstam variable \f$\hat{s}\f$ in this
   * SubProcess. It is calculated using the incoming particles.
   */
  inline Energy2 shat() const;

  /**
   * Return the value of the Mandelstam variable \f$\hat{t}\f$ in this
   * SubProcess. It is calculated using the first incoming and first outgoing
   * particle.
   */
  inline Energy2 that() const;

  /**
   * Return the value of the Mandelstam variable \f$\hat{u}\f$ in this
   * SubProcess. It is calculated using the first incoming and last outgoing
   * particle.
   */
  inline Energy2 uhat() const;

public:

  /**
   * Standard function for writing to a persistent stream.
   */
  void persistentOutput(PersistentOStream &) const;

  /**
   * Standard function for reading from a persistent stream.
   */
  void persistentInput(PersistentIStream &, int);

  /**
   * Standard Init function. @see Base::Init().
   */
  static void Init();

private:

  /**
   * A pointer to the MEBase object which generated this sub-process.
   */
  tcEventBasePtr theHandler;

  /**
   * A pointer to the collision to which this sub-process belongs.
   */
  tCollPtr theCollision;

  /**
   * The pair of incoming particles.
   */
  PPair theIncoming;

  /**
   * The vector of intermediate particles,
   */
  ParticleVector theIntermediates;

  /**
   * The vector of outgoing particles.
   */
  ParticleVector theOutgoing;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<SubProcess> initSubProcess;

  /**
   * Private default constructor must only be used by the
   * PersistentIStream class via the ClassTraits<SubProcess> class .
   */
  inline SubProcess();

  /**
   * The ClassTraits<SubProcess> class must be a friend to be able to
   * use the private default constructor.
   */
  friend class ClassTraits<SubProcess>;

  /**
   * Assignment is forbidden.
   */
  inline SubProcess & operator=(const SubProcess &);

};

/** Output a SubProcess to an ostream. */
ostream & operator<<(ostream &, const SubProcess &);


/** This template specialization informs ThePEG about the
 *  base class of Collision. */
template <>
struct BaseClassTrait<SubProcess,1> {
  /** Typedef of the first base class of SubProcess. */
  typedef EventRecordBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the SubProcess class and how to create it. */
template <>
struct ClassTraits<SubProcess>: public ClassTraitsBase<SubProcess> {
  /** Return a platform-independent class name */
  static string className() { return "/ThePEG/SubProcess"; }
  /** Create a SubProcess object. */
  static TPtr create() { return TPtr::Create(SubProcess()); }
};

}

#include "SubProcess.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "SubProcess.tcc"
#endif

#endif /* ThePEG_SubProcess_H */
