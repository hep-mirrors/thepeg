// -*- C++ -*-
#ifndef ThePEG_SelectorBase_H
#define ThePEG_SelectorBase_H
//
// This is the declaration of the <!id>SelectorBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// Classes derived from the <!id>SelectorBase<!!id> class are used to
// extract particles from an <!class>Event<!!class> with
// <!id>Event::select<!!id> method. There are five different kinds of
// checks done by a selector object in the <!id>Event::select<!!id>
// method. If the <!id>allCollisions()<!!id> method returns false,
// only particles which belongs to the primary collision in an event
// will be considered for extraction. Furthermore if the
// <!id>allSteps()<!!id> method returns false, only particles present
// in the final step of each collision wikk be considered. If
// <!id>finalState()<!!id> returns false, final state particles will
// not be considered and if <!id>intermediate()<!!id> returns false,
// intermediate particles will not be considered. Finally among all
// considered particles, only the ones for which the <!id>check(const
// Particle &)<!!id> returns true will be extracted.
//
// The templated <!id>SelectParticle<!!id> class may be used to
// implement derived classes from the <!id>SelectorBase<!!id>
// class. The requirement on the template class is that it implements
// the static <!id>AllCollisions()<!!id>, <!id>AllSteps()<!!id>,
// <!id>FinalState()<!!id>, <!id>Intermediate()<!!id> and
// <!id>Check(const Particle &)<!!id> (corresponding to the virtual
// ones in <!id>SelectParticle<!!id>).
//
// The <!id>SelectIfNot<!!id>, <!id>SelectIfEither<!!id>,
// <!id>SelectIfBoth<!!id> classes can be used to combine other
// selector classes.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StandardSelectors.html">StandardSelectors.h</a>
// <a href="http:Event.html">Event.h</a>
// <a href="http:Collision.html">Collision.h</a>
// <a href="http:Step.html">Step.h</a>
// <a href="http:Particle.html">Collision.h</a>
// 


#include "EventConfig.h"

namespace ThePEG {

class SelectorBase {

public:

  inline SelectorBase();
  // Default constructor

  inline virtual ~SelectorBase();
  // Destructor

  inline static bool Check(const Particle &);
  // Static method corresponding to the virtual check() method.

  inline static bool Intermediate();
  // Static method corresponding to the virtual intermediate() method.

  inline static bool FinalState();
  // Static method corresponding to the virtual finalState() method.

  inline static bool AllSteps();
  // Static method corresponding to the virtual allSteps() method.

  inline static bool AllCollisions();
  // Static method corresponding to the virtual allCollisions() method.

  inline virtual bool check(const Particle &  p) const;
  // Return true if the particle should be extracted.

  inline virtual bool finalState() const;
  // Return true if final state particles are to be considered.

  inline virtual bool intermediate() const;
  // Return true if intermediate particles should be considered.

  inline virtual bool allSteps() const;
  // Return true if all steps should be considered. Otherwise only the
  // last step in each collision is considered.

  inline virtual bool allCollisions() const;
  // Return ture if all collisions should be considered. Otherwise
  // only the primary collision will be considered.

};

template <class T>
struct ParticleSelector: public SelectorBase {

  inline ParticleSelector();

  inline virtual ~ParticleSelector();

  inline static bool Check(const Particle &);

  inline static bool Intermediate();

  inline static bool FinalState();

  inline static bool AllSteps();

  inline static bool AllCollisions();

  inline virtual bool check(const Particle &  p) const;

  inline virtual bool finalState() const;

  inline virtual bool intermediate() const;

  inline virtual bool allSteps() const;

  inline virtual bool allCollisions() const;

};  

class SelectIfNot: public SelectorBase {

public:

  inline SelectIfNot(const SelectorBase &);

  inline SelectIfNot(const SelectIfNot &);

  inline virtual bool check(const Particle &  p) const;

  inline virtual bool finalState() const;

  inline virtual bool intermediate() const;

  inline virtual bool allSteps() const;

  inline virtual bool allCollisions() const;

private:

  inline SelectIfNot();

  const SelectorBase & s;

};

class SelectIfBoth: public SelectorBase {

public:

  inline SelectIfBoth(const SelectorBase &, const SelectorBase &);

  inline SelectIfBoth(const SelectIfBoth &);

  inline virtual bool check(const Particle &  p) const;

  inline virtual bool finalState() const;

  inline virtual bool intermediate() const;

  inline virtual bool allSteps() const;

  inline virtual bool allCollisions() const;

private:

  inline SelectIfBoth();

  const SelectorBase & s1;
  const SelectorBase & s2;

};

class SelectIfEither: public SelectorBase {

public:

  inline SelectIfEither(const SelectorBase &, const SelectorBase &);

  inline SelectIfEither(const SelectIfEither &);

  inline virtual bool check(const Particle &  p) const;

  inline virtual bool finalState() const;

  inline virtual bool intermediate() const;

  inline virtual bool allSteps() const;

  inline virtual bool allCollisions() const;

private:

  inline SelectIfEither();

  const SelectorBase & s1;
  const SelectorBase & s2;

};

template <typename OutputIterator, typename Container>
inline void copyIfCheck(OutputIterator r, const Container & c,
			const SelectorBase & s);

}

#include "SelectorBase.icc"

#endif /* ThePEG_SelectorBase_H */
