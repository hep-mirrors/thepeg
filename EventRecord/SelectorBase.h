// -*- C++ -*-
#ifndef ThePEG_SelectorBase_H
#define ThePEG_SelectorBase_H
// This is the declaration of the SelectorBase class.


#include "EventConfig.h"

namespace ThePEG {

/**
 * Classes derived from the <code>SelectorBase</code> class are used
 * to extract particles from an Event with
 * <code>Event::select()</code> method. There are five different kinds
 * of checks done by a selector object in the
 * <code>Event::select</code> method. If the
 * <code>allCollisions()</code> method returns false, only particles
 * which belongs to the primary collision in an event will be
 * considered for extraction. Furthermore if the
 * <code>allSteps()</code> method returns false, only particles
 * present in the final step of each collision will be considered. If
 * <code>finalState()</code> returns false, final state particles will
 * not be considered and if <code>intermediate()</code> returns false,
 * intermediate particles will not be considered. Finally among all
 * considered particles, only the ones for which the <code>check(const
 * Particle &)</code> returns true will be extracted.
 *
 *
 *
 *
 * @see StandardSelectors
 * @see Event
 * @see Collision
 * @see Step
 * @see Particle
 * 
 */
class SelectorBase {

public:

  /**
   * Default constructor.
   */
  inline SelectorBase();

  /**
   * Destructor.
   */
  inline virtual ~SelectorBase();

  /**
   * Static method corresponding to the virtual check() method.
   */
  inline static bool Check(const Particle &);

  /**
   * Static method corresponding to the virtual intermediate() method.
   */
  inline static bool Intermediate();

  /**
   * Static method corresponding to the virtual finalState() method.
   */
  inline static bool FinalState();

  /**
   * Static method corresponding to the virtual allSteps() method.
   */
  inline static bool AllSteps();

  /**
   * Static method corresponding to the virtual allCollisions() method.
   */
  inline static bool AllCollisions();

  /**
   * Return true if the particle should be extracted.
   */
  inline virtual bool check(const Particle &  p) const;

  /**
   * Return true if final state particles are to be considered.
   */
  inline virtual bool finalState() const;

  /**
   * Return true if intermediate particles should be considered.
   */
  inline virtual bool intermediate() const;

  /**
   * Return true if all steps should be considered. Otherwise only the
   * last step in each collision is considered.
   */
  inline virtual bool allSteps() const;

  /**
   * Return ture if all collisions should be considered. Otherwise
   * only the primary collision will be considered.
   */
  inline virtual bool allCollisions() const;

};

/**
 * The templated <code>ParticleSelector</code> class may be used to
 * implement derived classes from the <code>SelectorBase</code>
 * class. The requirement on the template class is that it implements
 * the static <code>AllCollisions()</code>, <code>AllSteps()</code>,
 * <code>FinalState()</code>, <code>Intermediate()</code> and
 * <code>Check(const Particle &)</code> (corresponding to the virtual
 * ones in <code>ParticleSelector</code>).
 */
template <class T>
struct ParticleSelector: public SelectorBase {

  /**
   * Default constructor.
   */
  inline ParticleSelector();

  /**
   * Destructor.
   */
  inline virtual ~ParticleSelector();

  /**
   * Static method corresponding to the virtual check() method.
   */
  inline static bool Check(const Particle &);

  /**
   * Static method corresponding to the virtual intermediate() method.
   */
  inline static bool Intermediate();

  /**
   * Static method corresponding to the virtual finalState() method.
   */
  inline static bool FinalState();

  /**
   * Static method corresponding to the virtual allSteps() method.
   */
  inline static bool AllSteps();

  /**
   * Static method corresponding to the virtual allCollisions() method.
   */
  inline static bool AllCollisions();

  /**
   * Return true if the particle should be extracted.
   */
  inline virtual bool check(const Particle &  p) const;

  /**
   * Return true if final state particles are to be considered.
   */
  inline virtual bool finalState() const;

  /**
   * Return true if intermediate particles should be considered.
   */
  inline virtual bool intermediate() const;

  /**
   * Return true if all steps should be considered. Otherwise only the
   * last step in each collision is considered.
   */
  inline virtual bool allSteps() const;

   /**
   * Return ture if all collisions should be considered. Otherwise
   * only the primary collision will be considered.
   */
 inline virtual bool allCollisions() const;

};  

/**
 * The SelectIfNot classes can be used to negate the meaning of
 * another SelectorBase object.
 */
class SelectIfNot: public SelectorBase {

public:

  /** Constructor taking the SelectorBase object to be negated. */
  inline SelectIfNot(const SelectorBase &);

  /**
   * Copy constructor.
   */
  inline SelectIfNot(const SelectIfNot &);

  /**
   * Return true if the particle should be extracted.
   */
  inline virtual bool check(const Particle &  p) const;

  /**
   * Return true if final state particles are to be considered.
   */
  inline virtual bool finalState() const;

  /**
   * Return true if intermediate particles should be considered.
   */
  inline virtual bool intermediate() const;

  /**
   * Return true if all steps should be considered. Otherwise only the
   * last step in each collision is considered.
   */
  inline virtual bool allSteps() const;

  /**
   * Return ture if all collisions should be considered. Otherwise
   * only the primary collision will be considered.
   */
  inline virtual bool allCollisions() const;

private:

  /**
   * Default constructor is private.
   */
  inline SelectIfNot();

  /**
   * The selector to be negated.
   */
  const SelectorBase & s;

};

/**
 * The SelectIfBoth class can be used to combine other selector
 * objects. Particles which would be extracted with either selectors
 * will be extractor.
 */
class SelectIfBoth: public SelectorBase {

public:

  /**
   * Constructor taking two SelectorBase object to be combiden.
   */
  inline SelectIfBoth(const SelectorBase &, const SelectorBase &);

  /**
   * Copy constructor.
   */
  inline SelectIfBoth(const SelectIfBoth &);

  /**
   * Return true if the particle should be extracted.
   */
  inline virtual bool check(const Particle &  p) const;

  /**
   * Return true if final state particles are to be considered.
   */
  inline virtual bool finalState() const;

  /**
   * Return true if intermediate particles should be considered.
   */
  inline virtual bool intermediate() const;

  /**
   * Return true if all steps should be considered. Otherwise only the
   * last step in each collision is considered.
   */
  inline virtual bool allSteps() const;

  /**
   * Return ture if all collisions should be considered. Otherwise
   * only the primary collision will be considered.
   */
  inline virtual bool allCollisions() const;

private:

  /**
   * Default constructor is private.
   */
  inline SelectIfBoth();

  /**
   * One selector to be combined.
   */
  const SelectorBase & s1;

  /**
   * The other selector to be combined.
   */
  const SelectorBase & s2;

};

/**
 * The SelectIfEither class can be used to combine other selector
 * objects. Only particles which would be extracted with both selectors
 * will be extractor.
 */
class SelectIfEither: public SelectorBase {

public:

  /**
   * Constructor taking two SelectorBase object to be combiden.
   */
  inline SelectIfEither(const SelectorBase &, const SelectorBase &);

  /**
   * Copy constructor.
   */
  inline SelectIfEither(const SelectIfEither &);

  /**
   * Return true if the particle should be extracted.
   */
  inline virtual bool check(const Particle &  p) const;

  /**
   * Return true if final state particles are to be considered.
   */
  inline virtual bool finalState() const;

  /**
   * Return true if intermediate particles should be considered.
   */
  inline virtual bool intermediate() const;

  /**
   * Return true if all steps should be considered. Otherwise only the
   * last step in each collision is considered.
   */
  inline virtual bool allSteps() const;

  /**
   * Return ture if all collisions should be considered. Otherwise
   * only the primary collision will be considered.
   */
  inline virtual bool allCollisions() const;

private:

  /**
   * Default constructor is private.
   */
  inline SelectIfEither();

  /**
   * One selector to be combined.
   */
  const SelectorBase & s1;

  /**
   * The other selector to be combined.
   */
  const SelectorBase & s2;

};

/** Helper function to be used together with SelectorBase objects. */
template <typename OutputIterator, typename Container>
inline void copyIfCheck(OutputIterator r, const Container & c,
			const SelectorBase & s);

}

#include "SelectorBase.icc"

#endif /* ThePEG_SelectorBase_H */
