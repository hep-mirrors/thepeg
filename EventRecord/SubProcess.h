// -*- C++ -*-
#ifndef ThePEG_SubProcess_H
#define ThePEG_SubProcess_H
//
// This is the declaration of the <!id>SubProcess<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// A <!id>SubProcess<!!id> object represents a hard <i>2-&gt;n</i>
// sub-process in a collision. It carries information about the
// incoming and outgoing particles, as well as possible intermediate
// ones. It also has a pointer to the <!class>PartonXSecFn<!!class>
// object which generated the sub-process.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>
// <a href="http:Particle.html">Particle.h</a>
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>
// 


#include <vector>
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

class SubProcess: public EventRecordBase {

public:

  friend class Step;
  friend class Collision;
  //  friend SubProPtr;
 
public:

  inline void * operator new(size_t);
  inline void operator delete(void *, size_t);

public:

  SubProcess(const PPair & newIncoming,
	     tCollPtr newCollision = tCollPtr(),
	     tcEventBasePtr newHandler = tcEventBasePtr());
  // Standard constructor (default constructor is private).

  SubProcess(const SubProcess &);
  // Copy constructor.

  inline ~SubProcess();
  // Destructor.

  inline tcEventBasePtr handler() const;
  // A pointer to the PartonXSecFn object which generatoed this
  // sub-process.

  inline tCollPtr collision() const;
  // A pointer to the collision to which this sub-process belongs.

  inline const PPair & incoming() const;
  // The pair of colliding particles.

  inline const ParticleVector & intermediates() const;
  // A reference to the vector of intermediate particles.

  inline const ParticleVector & outgoing() const;
  // A reference to the vector of outgoing particles.

  template <class InputIterator>
  void setOutgoing(InputIterator, InputIterator);
  // Set the vector of outgoing particles.

  void addOutgoing(tPPtr p, bool fixrelations = true);
  // Add a particle to the list of outgoing ones.

  template <class InputIterator>
  void setIntermediates(InputIterator, InputIterator);
  // Set the vector of intermediate particles.

  void addIntermediate(tPPtr p, bool fixrelations = true);
  // Add a particle to the list of intermediate ones.

  void removeEntry(tPPtr p);
  // Remove a particle entry from this sub-process.

  SubProPtr clone() const;
  // Return a clone of this sub process.

protected:

  void rebind(const EventTranslationMap & trans);
  // When a sub-process is cloned, a shallow copy is done first, then
  // all particles are cloned, and finally this method is used to
  // see to that the pointers in the cloned SubProcess points to the
  // cloned particles.


public:

  void transform(const LorentzRotation &);
  // Perform a LorentzTransformation of all particles in the sub
  // process.

  inline Energy2 shat() const;
  inline Energy2 that() const;
  inline Energy2 uhat() const;
  // Return the value of the Mandelstam variables in this
  // sub-process. shat is calculated using the incoming particles,
  // that is calculated using the first incoming and first outgoing
  // particle and uhat is calculated using the second incoming and the
  // first outgoing particle.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  tcEventBasePtr theHandler;
  // A pointer to the PartonXSecFn object which generated this sub-process.

  tCollPtr theCollision;
  // A pointer to the collision to which this sub-process belongs.

  PPair theIncoming;
  // The pair of incoming particles.

  ParticleVector theIntermediates;
  // The vector of intermediate particles,

  ParticleVector theOutgoing;
  // The vector of outgoing particles.

private:

  static ClassDescription<SubProcess> initSubProcess;
  // Describe concrete class with persistent data.

  inline SubProcess();
  friend class ClassTraits<SubProcess>;
  // Private default constructor must only be used by the
  // PersistentIStream class via the ClassTraits<SubProcess> class .

  inline SubProcess & operator=(const SubProcess &);
  // Assignment is forbidden.

};

ostream & operator<<(ostream &, const SubProcess &);
// Write a SubProcess object to a stream.

// CLASSDOC OFF

template <>
struct BaseClassTrait<SubProcess,1> {
  typedef EventRecordBase NthBase;
};

template <>
struct ClassTraits<SubProcess>: public ClassTraitsBase<SubProcess> {
  static string className() { return "/ThePEG/SubProcess"; }
  static TPtr create() { return TPtr::Create(SubProcess()); }
};

}

#include "SubProcess.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "SubProcess.tcc"
#endif

#endif /* ThePEG_SubProcess_H */
