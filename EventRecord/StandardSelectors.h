// -*- C++ -*-
#ifndef ThePEG_StandardSelectors_H
#define ThePEG_StandardSelectors_H
//
// This file contains declarations of standard selector classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>SelectFinalState<!!id> class selects all final state
// particles in an event (and is used internally by the
// <!id>Event::selectFinalState()<!!id> method.
//
// The <!id>SelectFinalState<!!id> class selects all
// intermediateparticles in an event.
// 
// The <!id>SelectAllSteps<!!id> class seraches all steps in an event.
// 
// The <!id>SelectPrimaryCollision<!!id> class seraches only the
// primary collision in an event.
// 
// The <!id>SelectCharged<!!id> class extracts only charged particles
// in the event..
// 
// CLASSDOC SUBSECTION See also:
//
// <a href="http:SelectorBase.html">SelectorBase.h</a>
// 


#include "SelectorBase.h"
#include "ParticleTraits.h"

namespace ThePEG {

struct AllSelector: public SelectorBase {

  static bool Check(const Particle &) { return true; }

  static bool Intermediate() { return true; }

  static bool FinalState() { return true; }

  static bool AllSteps() { return true; }

  static bool AllCollisions() { return true; }

};

typedef ParticleSelector<AllSelector> SelectAll;


struct FinalStateSelector: public SelectorBase {

  static bool Intermediate() { return false; }

  static bool AllSteps() { return false; }

};

typedef ParticleSelector<FinalStateSelector> SelectFinalState;


struct IntermediateSelector: public SelectorBase {

  static bool Check(const Particle &) { return true; }

  static bool Intermediate() { return true; }

  static bool FinalState() { return false; }

  static bool AllSteps() { return true; }

  static bool AllCollisions() { return true; }

};

struct PrimaryCollisionSelector: public SelectorBase {

  static bool Check(const Particle &) { return true; }

  static bool Intermediate() { return true; }

  static bool FinalState() { return true; }

  static bool AllSteps() { return true; }

  static bool AllCollisions() { return false; }

};

typedef ParticleSelector<PrimaryCollisionSelector> SelectPrimaryCollision;


struct ChargedSelector: public SelectorBase {

  static bool Check(const Particle & p) {
    return ParticleTraits<Particle>::iCharge(p);
  }

};

typedef ParticleSelector<ChargedSelector> SelectCharged;

}

#endif /* ThePEG_StandardSelectors_H */
