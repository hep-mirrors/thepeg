// -*- C++ -*-
//
// This is the implementation of the non-inlined member functions of
// the Collision class.
//
#include "Collision.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/DIterator.h"
#include <iostream>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Collision.tcc"
#endif

using namespace ThePEG;

Collision::Collision(const PPair & newIncoming, tEventPtr newEvent,
		     tcEventBasePtr newHandler)
  : theIncoming(newIncoming), theEvent(newEvent), theHandler(newHandler) {
  addParticle(incoming().first);
  addParticle(incoming().second);
}

Collision::Collision(const Collision & c)
  : theIncoming(c.theIncoming), theSteps(c.theSteps),
    theSubProcesses(c.theSubProcesses),
    allParticles(c.allParticles), theEvent(c.theEvent),
    theHandler(c.theHandler), theVertex(c.theVertex) {}

CollPtr Collision::clone() const {
  return ptr_new<CollPtr>(*this);
}

tStepPtr Collision::newStep(tcEventBasePtr newHandler) {
  if ( theSteps.empty() ) theSteps.push_back(new_ptr(Step(this)));
  else theSteps.push_back(new_ptr(Step(*finalStep())));
  tStepPtr s = finalStep();
  s->handler(newHandler);
  s->theIntermediates.clear();
  s->theSubProcesses.clear();
  s->allParticles = s->theParticles;
  return s;
}

void Collision::rebind(const EventTranslationMap & trans) {
  theIncoming.first = trans.translate(theIncoming.first);
  theIncoming.second = trans.translate(theIncoming.second);
  theEvent = trans.translate(theEvent);
  for ( StepVector::iterator sit = theSteps.begin();
	sit != theSteps.end(); ++sit )
    (*sit = trans.translate(*sit))->rebind(trans);
  for ( SubProcessVector::iterator spit = theSubProcesses.begin();
	spit != theSubProcesses.end(); ++spit )
    (*spit = trans.translate(*spit))->rebind(trans);
  ParticleSet newParticles;
  for ( ParticleSet::const_iterator pit = allParticles.begin();
	pit != allParticles.end(); ++pit )
    newParticles.insert(trans.translate(*pit));
  allParticles.swap(newParticles);
}

void Collision::transform(const LorentzRotation & r) {
  for_each(allParticles, Transformer(r));
}

void Collision::addStep(tStepPtr s) {
  theSteps.push_back(s);
  s->collision(this);
  addParticles(s->all().begin(), s->all().end());
  if ( event() ) event()->addStep(s);
}

void Collision::addSubProcess(tSubProPtr p) {
  theSubProcesses.push_back(p);
  if ( event() ) event()->addSubProcess(p);
}

void Collision::addParticle(tPPtr p) {
  allParticles.insert(p);
  if ( event() ) event()->addParticle(p);
}

void Collision::removeEntry(tPPtr p) {
  ParticleSet::iterator it = allParticles.find(p);
  if ( it == allParticles.end() ) return;
  for ( DIterator<StepVector::iterator> sit = theSteps.begin();
	sit != theSteps.end(); ++sit ) sit->removeEntry(p);
  allParticles.erase(it);
}

void Collision::removeParticle(tPPtr p) {
  if ( p->next() ) removeParticle(p->next());
  while ( !p->children().empty() ) removeParticle(p->children().back());
  if ( p->hasRep() ) p->rep().theBirthStep = tStepPtr();
  removeEntry(p);
}

void Collision::removeDecay(tPPtr p) {
  while ( !p->children().empty() ) removeParticle(p->children().back());
}

void Collision::cleanSteps() {
  for ( StepVector::size_type i = 0; i < theSteps.size(); ++i ) {
    if ( theSteps[i]->nullStep() ) theSteps.erase(theSteps.begin() + i--);
  }
}

void Collision::popStep() {
  StepPtr last = finalStep();
  ParticleVector pv(last->all().begin(), last->all().end());
  for ( ParticleVector::iterator pit = pv.begin();pit != pv.end(); ++pit )
    if ( (**pit).birthStep() == last ) removeParticle(*pit);
  theSteps.pop_back();
}

tParticleSet Collision::getRemnants() const {
  tParticleSet ret;
  tPVector partons;
  for ( DIterator<SubProcessVector::const_iterator> i = subProcesses().begin();
	i != subProcesses().end(); ++i ) {
    partons.push_back(i->incoming().first->original());
    partons.push_back(i->incoming().second->original());
  }
  for ( tPVector::size_type i = 0; i < partons.size(); ++i ) {
    partons.insert(partons.end(), partons[i]->parents().begin(),
		   partons[i]->parents().end());
    tParticleSet siblings = partons[i]->siblings();
    ret.insert(siblings.begin(), siblings.end());
  }
  for ( int i = 0, N = partons.size(); i < N; ++i ) ret.erase(partons[i]);
  return ret;
}
  

ostream & ThePEG::operator<<(ostream & os, const Collision & c) {
  int isub = 0;
  if ( c.incoming().first || c.incoming().second ) {
    os << "--- Colliding particles:" << endl;
    if ( c.incoming().first ) os << *c.incoming().first;
    if ( c.incoming().second ) os << *c.incoming().second;
  }
  for ( unsigned int i = 0; i < c.steps().size(); ++i ) {
    const Step & s = *c.steps()[i];
    for ( SubProcessVector::const_iterator it = s.subProcesses().begin();
	  it != s.subProcesses().end(); ++it ) {
      os << "---------------------------------------"
	 << "---------------------------------------" << endl;
      if ( !isub ) {
	os << "Primary sub-process";
	++isub;
      } else
	os << "Secondary sub-process " << isub++;
      if ( (**it).handler() )
	os << " performed by " << EventConfig::nameHandler((**it).handler())
	   << endl;
      os << **it;
    }
    os << "---------------------------------------"
       << "---------------------------------------" << endl
       << "Step " << i+1;
    if ( s.handler() )
      os << " performed by " << EventConfig::nameHandler(s.handler());
    os << endl << s;
  }
  if ( ThePEG_DEBUG_ITEM(9) ) {
    for ( ParticleSet::const_iterator p = c.all().begin();
	  p != c.all().end(); ++p )
      if ( c.isRemnant(*p) ) os << setw(5) << (**p).number();
    os << endl;
  }
  return os;
}

void Collision::persistentOutput(PersistentOStream & os) const {
  os << theIncoming << theSteps << theSubProcesses << theEvent;
  EventConfig::putHandler(os, theHandler);
  os << ounit(theVertex, mm);
}

void Collision::persistentInput(PersistentIStream & is, int) {
  is >> theIncoming >> theSteps >> theSubProcesses >> theEvent;
  EventConfig::getHandler(is, theHandler);
  is >> iunit(theVertex, mm);
}

ClassDescription<Collision> Collision::initCollision;

void Collision::Init() {}

