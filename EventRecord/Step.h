// -*- C++ -*-
#ifndef ThePEG_BasicStep_H
#define ThePEG_BasicStep_H
//
// This is the declaration of the <!id>Step<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Step<!!id> contains informatiop of all particles present
// after certain step in the event generation. There is also
// information about particles which were introduced as intermediate
// ones in the generation of the step. The <!id>Step<!!id> may also
// contain one or more <!class>SubProcesses<!!class> which were
// generated in the step. The <!id>Step<!!id> is linked back to the
// <!class>Collision<!!class> to which it belongs, and there may be a
// pointer to the <!class>StepHandler<!!class> which generated the
// step.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:SubProcess.html">SubProcess.h</a>
// <a href="http:Particle.html">Particle.h</a>
// <a href="http:SelectorBase.html">SelectorBase.h</a>
// <a href="http:SelectorBase.html">Named.h</a>
// 

#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/StandardSelectors.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

class Step: public EventRecordBase {

public:

  friend class PartialCollisionHandler;
  friend class Collision;
  friend class Event;
  //  friend StepPtr;

public:

  inline void * operator new(size_t);
  inline void operator delete(void *, size_t);

public:

  Step(tCollPtr newCollision = tCollPtr(),
       tcEventBasePtr newHandler = tcEventBasePtr());
  // Standard and default constructor.

  Step(const Step &);
  // The copy constructor.

  inline ~Step();
  // The destructor.

  inline tcEventBasePtr handler() const;
  // Return a pointer to the step handler which performed the
  // generation of this step.

  inline tCollPtr collision() const;
  // Return a pointer to the Collision to which this step belongs.

  template <typename OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;
  // Extract particles from this step.

  template <typename OutputIterator>
  inline void selectFinalState(OutputIterator r) const;
  inline tPVector getFinalState() const;
  // Extract all outgoing particles from this step.

  template <typename PIterator>
  inline static vector<tPVector> getSinglets(PIterator first, PIterator last);
  // Return a vector of particle vectors with colour-connected
  // partons, where each particle vector is in a colour singlet state.
  // * OBSOLETE * Use the corresponding functions in ColourLine instead.

  inline const ParticleSet & all() const;
  // A reference to the set of all particles in this step.

  inline const ParticleSet & particles() const;
  // A reference to the set of outgoing particles in this step.

  inline const ParticleSet & intermediates() const;
  // A reference to the set of intermediate particles in this step.

  inline const SubProcessVector & subProcesses() const;
  // A reference to the vector of sub-processes introduced in this
  // step.

  inline const PPair & incoming() const;
  // Returns the colliding particles in the collision to which this
  // step belongs. (If this step does not belon to a collision, this
  // method will probably cause a segmentation fault - This should be
  // fixed. Maybe this method is not needed at all.)

  inline tPPtr find(tcPPtr) const;
  // If the given particle is present in this step, return its
  // pointer otherwise return the null pointer;

  tPPtr copyParticle(tcPPtr p);
  // If the given particle is present in this step, insert a copy and
  // remove the original (or make it intermediate if it was initially
  // added to this step). Returns the new particle if the copy
  // succeeded. If the copy fails, nothing is changed. For a
  // successful call copyParticle(p)->previous() == p is true.

  bool setCopy(tcPPtr pold, tPPtr pnew);
  // Declare that pold and pnew are two instances of the same
  // particle. If pnew is not present in the step it will be
  // afterwars. Afterwards pold == pnew->previous() && pnew ==
  // pold->next() is true. Returns false if something went wrong.

  tPPtr insertCopy(tcPPtr p);
  // If the given particle is present in the current Collision, insert
  // copy of that particle 'before' the particle. If the particle does
  // not belong to the current collision or if the copy failed,
  // nothing is changed and the null pointer is returned. If
  // successful insertCopy(p)->next() == p is true. The parents of the
  // original particle will become the parents of the copy.

  bool addDecayProduct(tcPPtr parent, tPPtr child, bool fixColour = true);
  template <typename CIterator>
  inline bool addDecayProduct(tcPPtr parent,
			      CIterator firstChild, CIterator lastChild,
			      bool fixColour = true);
  // If the parent is present in this step or if it has immediate
  // children in this step, insert the child(children) and fix up
  // references between the two. If the parent is among the current
  // particles, remove it (or make it intermediate if it was initially
  // added to this step). If false is returned nothing is changed. The
  // parent/child pointers of the affected particles will be set
  // accordingly. If both the parent and child/children are coloured,
  // the colour flow will be set. The colour of the parent will then
  // flow to the first added child, while the anti colour will flow to
  // the last added child.

  bool removeDecayProduct(tcPPtr parent, tPPtr child);
  template <typename CIterator>
  inline bool removeDecayProduct(tcPPtr parent,
				 CIterator firstChild, CIterator lastChild);
  // Remove the child(ren) form the given parent. The children are not
  // removed from the decay record.

  template <typename Iterator>
  bool addDecayProduct(Iterator firstParent, Iterator lastParent, tPPtr child);
  template <typename PIterator, typename CIterator>
  bool addDecayProduct(PIterator firstParent, PIterator lastParent,
		       CIterator firstChild, CIterator lastChild);
  // Add the child (children) as a decay product of all the listed
  // particles. The parents must satisfy the same requirements as in
  // the single parent method. If any of the parents fail false is
  // returned and nothing has changed. The parent/child pointers of
  // the affected particles will be set accordingly.

  void fixColourFlow();
  // Fix the colour flow of particles which have been added to this
  // step and which have not already had their colour neighbours set.
  // If a neighbor is found which has not been added in this step, it
  // is first cloned in order not to compromise the colour flow of
  // previous steps.

  tPPtr colourNeighbour(tcPPtr, bool anti = false) const;
  tPPtr antiColourNeighbour(tcPPtr) const;
  // Return the (anti) colour neighbour of the given particle if one
  // exists in the final state.

  template <typename Iterator>
  void addParticles(Iterator first, Iterator last);
  void addParticle(tPPtr p);
  // Add a (range of) particle(s) to this step. If this step belongs
  // to a collision, the paticle will also be added to the
  // collision. If this particle has not previously been in a step,
  // the birthStep pointer of the particle will be set.

  template <typename Iterator>
  void addIntermediates(Iterator first, Iterator last);
  void addIntermediate(tPPtr p);
  // Add an (range of) intermediate particle(s) in this step. If this
  // step belongs to a collision, the paticle will also be added to
  // the collision. If this particle has not previously been in a
  // step, the birthStep pointer of the particle will be set.

  void insertIntermediate(tPPtr p, tPPtr parent, tPPtr child);
  // Add an intermediate particle 'p' so that if 'child' previously
  // was the child of 'parent', afterwards 'p' will be the child of
  // 'parent' and 'child' will be the child of 'p'.

  void addSubProcess(tSubProPtr);
  // Add a sub-process. All outgoing particles are added to the list
  // of outgoing particles in the step. All other particles in the
  // sub-process will be added to the list of intermediates.

  void removeParticle(tPPtr p);
  // Remove (recursively) the given Particle from the Collision. If
  // this was the last daughter of the mother Particle, the latter is
  // added to the list of final state particles.  

  bool nullStep() const;
  // Return true if no new particles were introduced in this step.

  template <typename Cont>
  inline tParticleSet getCurrent(const Cont & c) const;
  template <typename Iterator>
  tParticleSet getCurrent(Iterator first, Iterator last) const;
  // Given a container or a range of particles, return the ones which
  // belongs to the final state of this step. If a particle does not
  // belong to these, it's children (or next instance) will be checked
  // and possibly added instead (recursively)

  StepPtr clone() const;
  // Return a clone of this step.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  static vector<tPVector> getSinglets(tParticleSet &);
  // Used internally by the public getSinglets(...);
  // * OBSOLETE * Use the corresponding functions in ColourLine instead.

  void removeEntry(tPPtr p);
  // Remove a particle entry from the step. Make its ancesters (if
  // any) present in this step.

  void rebind(const EventTranslationMap & trans);
  // When a step is cloned, a shallow copy is done first, then all
  // particles etc, are cloned, and finally this method is used to see
  // to that the pointers in the cloned Step points to the cloned
  // particles etc.

  template <typename Inserter, typename PPointer>
  void addIfFinal(Inserter o, PPointer p);
  // Insert p into with the Inserter o if p is a member of the final
  // state of this Step. Otherwise call the method for the children if
  // any.


private:

  inline Step & operator=(const Step &);
  // Assignement is not allowed.

  inline void collision(tCollPtr);
  inline void handler(tcEventBasePtr);
  // Setup pointers to the collision and to the step handler.

private:

  ParticleSet theParticles;
  // The set of all outgoing particle in this step.

  ParticleSet theIntermediates;
  // The set of all intermediate particle in this step.

  SubProcessVector theSubProcesses;
  // The vector of all sub-processes introduced in this step.

  ParticleSet allParticles;
  // The set of all particles available in this step.

  tCollPtr theCollision;
  // Pointer to the collision to which this step belongs.

  tcEventBasePtr theHandler;
  // Pointer ot the step handler which performed this step.

private:

  static ClassDescription<Step> initStep;
  // Describe concrete class with persistent data.

};

ostream & operator<<(ostream &, const Step &);
// Write a Step object to a stream

ThePEG_DECLARE_CLASS_TRAITS(Step,EventRecordBase);

}

#include "Step.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Step.tcc"
#endif

#endif /* ThePEG_BasicStep_H */
