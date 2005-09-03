// -*- C++ -*-
#ifndef ThePEG_BasicStep_H
#define ThePEG_BasicStep_H
// This is the declaration of the Step class.

#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/StandardSelectors.h"
#include "ThePEG/Utilities/FixedSizeAllocator.h"

namespace ThePEG {

/**
 * The Step class contains information of all particles present after
 * certain step in the event generation. There is also information
 * about particles which were introduced as intermediate ones in the
 * generation of the step. The Step may also contain one or more
 * SubProcesses which were generated in the step. The Step is linked
 * back to the Collision to which it belongs, and there may be a
 * pointer to the StepHandler which generated the step.
 *
 * @see Event
 * @see Collision
 * @see SubProcess
 * @see Particle
 * @see SelectorBase
 * @see SelectorBase
 */
class Step: public EventRecordBase {

public:

  /** Most of the Event classes are friends with each other. */
  friend class Collision;
  /** Most of the Event classes are friends with each other. */
  friend class Event;

public:

  /**
   * Step uses the FixedSizeAllocator for (de)allocation.
   */
  inline void * operator new(size_t);

  /**
   * Step uses the FixedSizeAllocator for (de)allocation.
   */
  inline void operator delete(void *, size_t);

public:

  /**
   * Standard constructor.
   * @param newCollision the Collision to which this Step belongs.
   * @param newHandler the handler object in charge of the generation
   * of this Step.
   */
  Step(tCollPtr newCollision = tCollPtr(),
       tcEventBasePtr newHandler = tcEventBasePtr());

  /**
   * The copy constructor.
   */
  Step(const Step &);

  /**
   * The destructor.
   */
  ~Step();

  /**
   * Return a pointer to the step handler which performed the
   * generation of this step.
   */
  inline tcEventBasePtr handler() const;

  /**
   * Return a pointer to the Collision to which this step belongs.
   */
  inline tCollPtr collision() const;

  /**
   * Extract particles from this Step which satisfies the
   * requirements given by an object of the SelectorBase class.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   * @param s SelectorBase object defining which particles should be
   * extracted.
   */
  template <typename OutputIterator>
  void select(OutputIterator r, const SelectorBase & s) const;

  /**
   * Extract all final state particles in this Step.
   * @param r an output iterator specifying where the extracted
   * (pointers to) particles will be appended.
   */
  template <typename OutputIterator>
  inline void selectFinalState(OutputIterator r) const;

  /**
   * Extract all final state particles in this Step.
   * @return a vector of pointers to the extracted particles.
   */
  inline tPVector getFinalState() const;

  /**
   * Return a vector of particle vectors with colour-connected
   * partons, where each particle vector is in a colour singlet state.
   * @deprecated Use the corresponding functions in ColourLine instead.
   */
  template <typename PIterator>
  inline static vector<tPVector> getSinglets(PIterator first, PIterator last);

  /**
   * A reference to the set of all particles in this step.
   */
  inline const ParticleSet & all() const;

  /**
   * A reference to the set of outgoing particles in this step.
   */
  inline const ParticleSet & particles() const;

  /**
   * A reference to the set of intermediate particles in this step.
   */
  inline const ParticleSet & intermediates() const;

  /**
   * A reference to the vector of sub-processes introduced in this
   * step.
   */
  inline const SubProcessVector & subProcesses() const;

  /**
   * Returns the colliding particles in the collision to which this
   * step belongs. (If this step does not belong to a collision, this
   * method will probably cause a segmentation fault - This should be
   * fixed. @deprecated Maybe this method is not needed at all.)
   */
  inline const PPair & incoming() const;

  /**
   * Get mutable particle. If the given particle is present in this
   * step, return its pointer otherwise return the null pointer;
   */
  inline tPPtr find(tcPPtr) const;

  /**
   * Copy a particle. If the given Particle is present in this step,
   * insert a copy and remove the original (or make it intermediate if
   * it was initially added to this step). Returns the new Particle if
   * the copy succeeded. If the copy fails, nothing is changed. For a
   * successful call <code>copyParticle(p)->previous() == p</code> is
   * true.
   */
  tPPtr copyParticle(tcPPtr p);

  /**
   * Make particles copies of eachother. Declare that pold and pnew
   * are two instances of the same particle. If pnew is not present in
   * the step it will be afterwars. Afterwards <code>pold ==
   * pnew->previous() && pnew == pold->next()</code> is true. Returns
   * false if something went wrong.
   */
  bool setCopy(tcPPtr pold, tPPtr pnew);

  /**
   * Insert a copy. If the given particle is present in the current
   * Collision, insert copy of that particle 'before' the particle. If
   * the particle does not belong to the current collision or if the
   * copy failed, nothing is changed and the null pointer is
   * returned. If successful <code>insertCopy(p)->next() == p</code>
   * is true. The parents of the original particle will become the
   * parents of the copy.
   */
  tPPtr insertCopy(tcPPtr p);

  /**
   * Add decay product. If the \a parent is present in this step or if
   * it has immediate children in this step, insert the \a child and
   * fix up references between the two. If the parent is among the
   * final state particles, remove it (or make it intermediate if it
   * was initially added to this step). The parent/child pointers of
   * the affected particles will be set accordingly. If both the
   * parent and child/children are coloured and \a fixColour is true,
   * the colour flow will be set.
   * @return true iff the addition succeeded.
   */
  bool addDecayProduct(tcPPtr parent, tPPtr child, bool fixColour = true);

  /**
   * Add decay products. If the \a parent is present in this step or if
   * it has immediate children in this step, insert the range of
   * children and fix up references between the two. If the parent is
   * among the final state particles, remove it (or make it
   * intermediate if it was initially added to this step). The
   * parent/child pointers of the affected particles will be set
   * accordingly. If both the parent and children are coloured and \a
   * fixColour is true, the colour flow will be set. The colour of the
   * parent will then flow to the first added child, while the anti
   * colour will flow to the last added child.
   * @return true iff the addition succeeded.
   */
  template <typename CIterator>
  inline bool addDecayProduct(tcPPtr parent,
			      CIterator firstChild, CIterator lastChild,
			      bool fixColour = true);

  /**
   * Add a particle to this Step. It is assumed to be already setup as
   * a child to a parent particle. The parent is removed from the list
   * of final state particles in this step. No consistency checks are
   * performed. @deprecated Use addDecayProduct(tPPtr child) instead.
   */
  void addDecayNoCheck(tPPtr parent, tPPtr child);

  /**
   * Add a particle to this Step. It is assumed to be already setup as
   * a child to parent particles. The parents are removed from the
   * list of final state particles in this step. No consistency checks
   * are performed.
   */
  void addDecayProduct(tPPtr child);

  /**
   * Remove the \a child form the given \a parent. The \a child is not
   * removed from the decay record.
   */
  bool removeDecayProduct(tcPPtr parent, tPPtr child);

  /**
   * Remove children form the given \a parent. The children are not
   * removed from the decay record.
   */
  template <typename CIterator>
  inline bool removeDecayProduct(tcPPtr parent,
				 CIterator firstChild, CIterator lastChild);

  /**
   * Add decay product. Add the \a child as a decay product of all the
   * listed parents. The parents must satisfy the same requirements as
   * in the addDecayProduct(tcPPtr,tPPtr,bool) function. If any of the
   * parents fail false is returned and nothing is changed. The
   * parent/child pointers of the affected particles will be set
   * accordingly, but no colour flow wll be set.
   */
  template <typename Iterator>
  bool addDecayProduct(Iterator firstParent, Iterator lastParent, tPPtr child);

  /**
   * Add the children as a decay products of all the listed
   * particles. The parents must satisfy the same requirements as in
   * the addDecayProduct(tcPPtr,tPPtr,bool) function. If any of the
   * parents fail false is returned and nothing is changed. The
   * parent/child pointers of the affected particles will be set
   * accordingly, but no colour flow wll be set.
   */
  template <typename PIterator, typename CIterator>
  bool addDecayProduct(PIterator firstParent, PIterator lastParent,
		       CIterator firstChild, CIterator lastChild);

  /**
   * Fix the colour flow of particles which have been added to this
   * step and which have not already had their colour neighbours set.
   * If a neighbor is found which has not been added in this step, it
   * is first cloned in order not to compromise the colour flow of
   * previous steps. @deprecated This method should not be needed with
   * the current ColourLine representation of colour.
   */
  void fixColourFlow();

  /**
   * Return the (\a anti-)colour neighbour of the given \a particle if
   * one exists in the final state of this Step. Will return null if
   * the given \a particle is not in the final state of this Step.
   */
  tPPtr colourNeighbour(tcPPtr particle, bool anti = false) const;

  /**
   * Return the anti-colour neighbour of the given \a particle if one
   * exists in the final state of this Step. Will return null if the
   * given \a particle is not in the final state of this Step.
   */
  tPPtr antiColourNeighbour(tcPPtr particle) const;

  /**
   * Add a range of particles to this Step. If this step belongs
   * to a Collision, the paticle will also be added to the
   * Collision. If this particle has not previously been in a Step,
   * the birthStep pointer of the particle will be set.
   */
  template <typename Iterator>
  void addParticles(Iterator first, Iterator last);

  /**
   * Add a particle to this step. If this step belongs to a Collision,
   * the paticle will also be added to the Collision. If this particle
   * has not previously been in a Step, the birthStep pointer of the
   * particle will be set.
   */
  void addParticle(tPPtr p);

  /**
   * Add a range of intermediate particles in this step. If this
   * step belongs to a Collision, the particles will also be added to
   * the Collision. If this particle has not previously been in a
   * Step, the birthStep pointer of the particle will be set.
   */
  template <typename Iterator>
  void addIntermediates(Iterator first, Iterator last);

  /**
   * Add an intermediate particle in this Step. If this
   * Step belongs to a Collision, the particle will also be added to
   * the Collision. If this particle has not previously been in a
   * step, the birthStep pointer of the particle will be set.
   */
  void addIntermediate(tPPtr p);

  /**
   * Add an intermediate particle. Particle \a p is added so that if
   * \a child previously was the child of \a parent, afterwards \a p
   * will be the child of \a parent and \a child will be the child of
   * \a p.
   */
  void insertIntermediate(tPPtr p, tPPtr parent, tPPtr child);

  /**
   * Add a sub-process. All outgoing particles are added to the list
   * of outgoing particles in the step. All other particles in the
   * sub-process will be added to the list of intermediates.
   */
  void addSubProcess(tSubProPtr);

  /**
   * Remove (recursively) the given Particle from the Step. If
   * this was the last daughter of the mother Particle, the latter is
   * added to the list of final state particles.  
   */
  void removeParticle(tPPtr p);

  /**
   * Return true if no new particles were introduced in this step.
   */
  bool nullStep() const;

  /**
   * Get final state particles. Given a container, return the ones
   * which belongs to the final state of this step. If a particle does
   * not belong to these, it's children (or next instance) will be
   * checked and possibly added instead (recursively).
   */
  template <typename Cont>
  inline tParticleSet getCurrent(const Cont & c) const;

  /**
   * Get final state particles. Given a range of particles, return the
   * ones which belongs to the final state of this step. If a particle
   * does not belong to these, it's children (or next instance) will
   * be checked and possibly added instead (recursively)
   */
  template <typename Iterator>
  tParticleSet getCurrent(Iterator first, Iterator last) const;

  /**
   * Return a clone of this step.
   */
  StepPtr clone() const;

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

protected:

  /**
   * Used internally by the public getSinglets(...); @deprecated Use
   * the corresponding functions in ColourLine instead.
   */
  static vector<tPVector> getSinglets(tParticleSet &);

  /**
   * Remove a particle entry from the step. Make its ancesters (if
   * any) present in this step.
   */
  void removeEntry(tPPtr p);

  /**
   * Rebind to cloned objects. When a Step is cloned, a shallow copy
   * is done first, then all <code>Particle</code>s etc, are cloned,
   * and finally this method is used to see to that the pointers in
   * the cloned Step points to the cloned <code>Particle</code>s etc.
   */
  void rebind(const EventTranslationMap & trans);

  /**
   * Get final state particles. Insert particle \a p into with the
   * Inserter \a o if \a p is a member of the final state of this
   * Step. Otherwise call the method for the children of \a p if any.
   */
  template <typename Inserter, typename PPointer>
  void addIfFinal(Inserter o, PPointer p);

private:

  /**
   * Assignement is not allowed.
   */
  inline Step & operator=(const Step &);

  /**
   * Setup pointer to the Collision.
   */
  inline void collision(tCollPtr);
  /**
   * Setup pointer to the step handler.
   */
  inline void handler(tcEventBasePtr);

private:

  /**
   * The set of all outgoing particle in this step.
   */
  ParticleSet theParticles;

  /**
   * The set of all intermediate particle in this step.
   */
  ParticleSet theIntermediates;

  /**
   * The vector of all sub-processes introduced in this step.
   */
  SubProcessVector theSubProcesses;

  /**
   * The set of all particles available in this step.
   */
  ParticleSet allParticles;

  /**
   * Pointer to the collision to which this step belongs.
   */
  tCollPtr theCollision;

  /**
   * Pointer ot the step handler which performed this step.
   */
  tcEventBasePtr theHandler;

private:

  /**
   * Describe concrete class with persistent data.
   */
  static ClassDescription<Step> initStep;

};

/** Output a Step to an ostream */
ostream & operator<<(ostream &, const Step &);

/** @cond TRAITSPECIALIZATIONS */
ThePEG_DECLARE_CLASS_TRAITS(Step,EventRecordBase);
/** @endcond */

}

#include "Step.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Step.tcc"
#endif

#endif /* ThePEG_BasicStep_H */
/**
 * Write a Step object to a stream
 */
