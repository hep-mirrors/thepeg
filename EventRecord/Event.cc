// -*- C++ -*-
//
// This is the implementation of the non-inlined member functions of
// the Event class.
//
#include "Event.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/DIterator.h"
#include <iostream>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Event.tcc"
#endif

using namespace ThePEG;

Event::Event(const PPair & newIncoming, tcEventBasePtr newHandler,
	     string newName, long newNumber, double newWeight)
  : Named(newName), theIncoming(newIncoming), theHandler(newHandler),
    theNumber(newNumber), theWeight(newWeight) {
  addParticle(incoming().first);
  addParticle(incoming().second);
}

Event::Event(const Event & e)
  : Base(e), Named(e), 
    theIncoming(e.theIncoming), theCollisions(e.theCollisions),
    allSteps(e.allSteps), allSubProcesses(e.allSubProcesses),
    allParticles(e.allParticles), theHandler(e.theHandler),
    theNumber(e.theNumber), theWeight(e.theWeight) {}

Event::~Event() {
  for ( int i = 0, N = theCollisions.size(); i < N; ++i )
    if ( theCollisions[i]->event() == this )
      theCollisions[i]->theEvent = tEventPtr();
  theIncoming = PPair();
  theCollisions.clear();
  allSteps.clear();
  allSubProcesses.clear();
  allParticles.clear();
  theHandler = tcEventBasePtr();
  theColourLines.clear();
  theNumber = -1;
  theWeight = 0.0;
}

void Event::setInfo(tcEventBasePtr newHandler, string newName,
		    long newNumber, double weight) {
  theHandler = newHandler;
  name(newName);
  theNumber = newNumber;
  theWeight = weight;
}

tCollPtr Event::newCollision() {
  theCollisions.push_back(new_ptr(Collision(incoming(), this)));
  return theCollisions.back();
}

tStepPtr Event::newStep() {
  if ( theCollisions.empty() ) newCollision();
  return theCollisions.back()->newStep();
}


void Event::addCollision(tCollPtr c) {
  if ( !c ) return;
  theCollisions.push_back(c);
  addParticles(c->all().begin(), c->all().end());
  allSubProcesses.insert(c->subProcesses().begin(), c->subProcesses().end()); 
}

void Event::addParticle(tPPtr p) {
  if ( !p ) return;
  if ( member(allParticles, p) ) return;
  allParticles.insert(p);
  p->number(allParticles.size());
}

void Event::transform(const LorentzRotation & r) {
  for_each(allParticles, Transformer(r));
}

int Event::colourLineIndex(tcColinePtr line) const {
  ColourLineMap::const_iterator found = theColourLines.find(line);
  if ( found != theColourLines.end() ) return found->second;
  int index = theColourLines.size() + 1;
  theColourLines[line] = index;
  return index;
}

void Event::primaryCollision(tCollPtr c) {
  if ( !c ) return;
  if ( theCollisions.empty() ) theCollisions.push_back(c);
  else {
    if ( theCollisions[0] )
      for ( ParticleSet::const_iterator it = theCollisions[0]->all().begin();
	    it != theCollisions[0]->all().end(); ++it ) 
	allParticles.erase(*it);
    theCollisions[0] = c;
  }
  addParticles(c->all().begin(), c->all().end());
}

void Event::removeDecay(tPPtr p) {
  while ( !p->children().empty() ) removeParticle(p->children().back());
}

void Event::removeEntry(tPPtr p) {
  ParticleSet::iterator it = allParticles.find(p);
  if ( it == allParticles.end() ) return;
  for ( DIterator<CollisionVector::iterator> cit = theCollisions.begin();
	cit != theCollisions.end(); ++cit ) cit->removeEntry(p);
  allParticles.erase(it);
}

void Event::removeParticle(tPPtr p) {
  if ( p->next() ) removeParticle(p->next());
  while ( !p->children().empty() ) removeParticle(p->children().back());
  removeEntry(p);
}

void Event::cleanSteps() {
  for ( DIterator<CollisionVector::iterator> cit = theCollisions.begin();
	cit != theCollisions.end(); ++cit ) cit->cleanSteps();
}

EventPtr Event::clone() const {
  EventPtr newEvent = ptr_new<EventPtr>(*this);
  EventTranslationMap trans;
  trans[this] = newEvent;
  for ( CollisionVector::const_iterator cit = theCollisions.begin();
	cit != theCollisions.end(); ++cit ) trans[*cit] = (**cit).clone();
  for ( SubProcessSet::const_iterator spit = allSubProcesses.begin();
	spit != allSubProcesses.end(); ++spit ) trans[*spit] = (**spit).clone();
  for ( StepSet::const_iterator sit = allSteps.begin();
        sit != allSteps.end(); ++sit ) trans[*sit] = (**sit).clone();
  for ( ParticleSet::const_iterator pit = allParticles.begin();
	pit != allParticles.end(); ++pit )
    trans[*pit] = (**pit).clone();
  newEvent->rebind(trans);
  return newEvent;
}

void Event::rebind(const EventTranslationMap & trans) {
  theIncoming.first = trans.translate(theIncoming.first);
  theIncoming.second = trans.translate(theIncoming.second);
  for ( CollisionVector::iterator cit = theCollisions.begin();
	cit != theCollisions.end(); ++cit )
    (*cit = trans.translate(*cit))->rebind(trans);
  SubProcessSet newSubProcesses;
  for ( SubProcessSet::const_iterator spit = allSubProcesses.begin();
	spit != allSubProcesses.end(); ++spit )
    newSubProcesses.insert(trans.translate(*spit));
  allSubProcesses.swap(newSubProcesses);
  StepSet newSteps;
  for ( StepSet::const_iterator sit = allSteps.begin();
	sit != allSteps.end(); ++sit )
    newSteps.insert(trans.translate(*sit));
  allSteps.swap(newSteps);
  ParticleSet newParticles;
  for ( ParticleSet::const_iterator pit = allParticles.begin();
	pit != allParticles.end(); ++pit )
    newParticles.insert(trans.translate(*pit));
  allParticles.swap(newParticles);
}
  
ostream & ThePEG::operator<<(ostream & os, const Event & e) {
  os << "***************************************"
     << "***************************************" << endl
     << "Event number " << e.number() << " (id: " << e.name() << ") ";
  if ( e.handler() ) os << "performed by "
			<<  EventConfig::nameHandler(e.handler());
  os << endl;
  for ( unsigned int i = 0; i < e.collisions().size(); ++i ) {
    os << "======================================="
       << "=======================================" << endl;
    if ( e.collisions().size() != 1 ) {
      if ( i ) {
	os << "Secondary Collision " << i;
	if ( e.collisions()[i]->handler() )
	  os << " performed by "
	     << EventConfig::nameHandler(e.collisions()[i]->handler());
      } else
	os << "Primary Collision";
    }
    os << endl << *e.collisions()[i];
  }
  return os;
}

void Event::debugme() const {
  cerr << *this;
  EventRecordBase::debugme();
}

void Event::persistentOutput(PersistentOStream & os) const {
  os << theIncoming << theCollisions << allSteps << allSubProcesses
     << allParticles << theNumber;
  EventConfig::putHandler(os, theHandler);
}

void Event::persistentInput(PersistentIStream & is, int) {
  is >> theIncoming >> theCollisions >> allSteps >> allSubProcesses
     >> allParticles >> theNumber;
  EventConfig::getHandler(is, theHandler);
}

ClassDescription<Event> Event::initEvent;

void Event::Init() {}

