// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Step class.
//

#include "Step.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Config/algorithm.h"
#include <iostream>
#include <iomanip>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Step.tcc"
#endif

using namespace ThePEG;

Step::
Step(tCollPtr newCollision, tcEventBasePtr newHandler)
  : theCollision(newCollision), theHandler(newHandler) {}

Step::Step(const Step & s)
  : theParticles(s.theParticles), theIntermediates(s.theIntermediates),
    allParticles(s.allParticles), theCollision(s.theCollision),
    theHandler(s.theHandler) {}

StepPtr Step::clone() const {
  return ptr_new<StepPtr>(*this);
}

void Step::rebind(const EventTranslationMap & trans) {
  ParticleSet::const_iterator pit;
  allParticles.clear();
  for ( pit = theParticles.begin(); pit != theParticles.end(); ++pit )
    allParticles.insert(trans.translate(*pit));
  theParticles.swap(allParticles);
  allParticles.clear();
  for ( pit = theIntermediates.begin();	pit != theIntermediates.end(); ++pit )
    allParticles.insert(trans.translate(*pit));
  theIntermediates = allParticles;
  allParticles.insert(theParticles.begin(), theParticles.end());
  for ( pit = allParticles.begin(); pit != allParticles.end(); ++pit )
    (**pit).rebind(trans);
}

void Step::addParticle(tPPtr p) {
  if ( !p->birthStep() ) p->rep().theBirthStep = this;
  theParticles.insert(p);
  allParticles.insert(p);
  if ( collision() ) collision()->addParticle(p);
}

void Step::addSubProcess(tSubProPtr sp) {
  if ( !member(allParticles, sp->incoming().first) && collision() &&
       sp->incoming().first != collision()->incoming().first ) {
    collision()->incoming().first->
      rep().theChildren.push_back(sp->incoming().first);
    sp->incoming().first->rep().theParents.push_back(collision()->incoming().first);
  }
  if ( !member(allParticles, sp->incoming().second) && collision() &&
       sp->incoming().second != collision()->incoming().second ) {
    collision()->incoming().second->
      rep().theChildren.push_back(sp->incoming().second);
    sp->incoming().second->rep().theParents.push_back(collision()->incoming().second);
  }
  if ( !sp->incoming().first->birthStep() )
    sp->incoming().first->rep().theBirthStep = this;
  if ( !sp->incoming().second->birthStep() )
    sp->incoming().second->rep().theBirthStep = this;
  addIntermediate(sp->incoming().first);
  addIntermediate(sp->incoming().second);
  addIntermediates(sp->intermediates().begin(), sp->intermediates().end());
  addParticles(sp->outgoing().begin(), sp->outgoing().end());
  theSubProcesses.push_back(sp);
  if ( collision() ) collision()->addSubProcess(sp);
}

void Step::addIntermediate(tPPtr p) {
  if ( !p->birthStep() ) p->rep().theBirthStep = this;
  theIntermediates.insert(p);
  allParticles.insert(p);
  if ( collision() ) collision()->addParticle(p);
}

void Step::
insertIntermediate(tPPtr p, tPPtr parent, tPPtr child) {
  if ( !p->birthStep() ) p->rep().theBirthStep = this;
  addIntermediate(p);
  parent->removeChild(child);
  child->removeParent(parent);
  if ( parent ) {
    parent->rep().theChildren.push_back(p);
    p->rep().theParents.push_back(parent);
  }
  if ( child ) {
    p->rep().theChildren.push_back(child);
    child->rep().theParents.push_back(p);
  }
}

void Step::removeEntry(tPPtr p) {
  ParticleSet::iterator it = allParticles.find(p);
  if ( it == allParticles.end() ) return;
  allParticles.erase(it);
  it = theParticles.find(p);
  theParticles.erase(it);
  if ( p->previous() ) {
    it = theIntermediates.find(p->previous());
    if ( it != theIntermediates.end() ) theIntermediates.erase(it);
    theParticles.insert(p->previous());
    allParticles.insert(p->previous());
  }
  while ( !p->parents().empty() ) {
    PPtr parent = p->parents().back();
    p->removeParent(parent);
    parent->removeChild(p);
    if ( !parent->children().empty() ) continue;
    it = theIntermediates.find(parent);
    if ( it != theIntermediates.end() ) theIntermediates.erase(it);
    theParticles.insert(parent);
    allParticles.insert(parent);
  }
  if ( !p->hasColourInfo() ) return;
  if ( p->colourNeighbour() )
    p->colourNeighbour()->antiColourNeighbour(p->antiColourNeighbour());
  if ( p->antiColourNeighbour() )
    p->antiColourNeighbour()->colourNeighbour(p->colourNeighbour());
  if ( p->incomingColour() ) p->outgoingColour(tPPtr());
  if ( p->incomingAntiColour() ) p->outgoingAntiColour(tPPtr());
}

void Step::removeParticle(tPPtr p) {
  if ( p->next() ) removeParticle(p->next());
  while ( !p->children().empty() ) removeParticle(p->children().back());
  removeEntry(p);
}

bool Step::nullStep() const {
  for ( ParticleSet::const_iterator it = allParticles.begin();
	it != allParticles.end(); ++it )
    if ( (**it).birthStep() == this ) return false;
  return true;
}

tPPtr Step::copyParticle(tcPPtr pin) {
  PPtr cp;
  tPPtr p = const_ptr_cast<tPPtr>(pin);
  if ( !collision() ) return cp;
  ParticleSet::iterator pit = theParticles.find(p);
  if ( collision()->finalStep() != this || p->next() ||
       ! p->children().empty() ||  pit == theParticles.end() ) return cp;
  cp = p->clone();
  cp->rep().thePrevious = p;
  p->rep().theNext = cp;
  if ( p->hasColour() ) p->colourFlow(cp);
  if ( p->hasAntiColour() ) p->antiColourFlow(cp);
  cp->rep().theBirthStep = this;
  theParticles.erase(pit);
  if ( p->birthStep() == this ) theIntermediates.insert(p);
  addParticle(cp);
  return cp;
}

bool Step::setCopy(tcPPtr poldin, tPPtr pnew) {
  if ( poldin->id() != pnew->id() ) return false;
  tPPtr pold = const_ptr_cast<tPPtr>(poldin);
  pold->rep().theNext = pnew;
  pnew->rep().thePrevious = pold;
  theParticles.erase(pold);
  if ( pold->birthStep() == this ) theIntermediates.insert(pold);
  pnew->rep().theBirthStep = this;
  addParticle(pnew);
  return true;
}

tPPtr Step::insertCopy(tcPPtr pin) {
  PPtr cp;
  tPPtr p = const_ptr_cast<tPPtr>(pin);
  if ( !collision() ) return cp;
  if ( collision()->all().find(p) == collision()->all().end() ) return cp;
  cp = p->clone();
  cp->rep().theNext = p;
  cp->rep().theChildren.clear();
  if ( p->previous() ) {
    p->previous()->rep().theNext = cp;
    cp->rep().thePrevious = p->previous();
  } else {
    for ( int i = 0, N = p->parents().size(); i < N; ++i ) {
      tPPtr parent = p->parents()[i];
      for ( int j = 0, M = parent->children().size(); j < M; ++j )
	if ( parent->children()[j] == p ) parent->rep().theChildren[j] = cp;
    }
  }
  p->rep().theParents.clear();
  p->rep().thePrevious = cp;
  if ( p->hasColour() ) cp->colourFlow(p);
  if ( p->hasAntiColour() ) cp->antiColourFlow(p);
  cp->rep().theBirthStep = this;
  theIntermediates.insert(cp);
  return cp;
}


bool Step::removeDecayProduct(tcPPtr par, tPPtr child) {
  if ( !collision() ) return false;
  tPPtr parent = const_ptr_cast<tPPtr>(par->final());
  if ( collision()->all().find(parent) == collision()->all().end() )
    return false;
  if ( !par->hasRep() ) return false;
  PVector::iterator it = ThePEG::find(parent->rep().theChildren, child);
  if ( it == parent->rep().theChildren.end() ) return false;
  parent->rep().theChildren.erase(it);
  ParticleSet::iterator cit = theParticles.find(child);
  if ( cit != theParticles.end() ) {
    theParticles.erase(cit);
    if ( child->birthStep() == this ) theIntermediates.insert(child);
  }
  return true;
}
  
bool Step::addDecayProduct(tcPPtr par, tPPtr child, bool fixColour) {
  if ( !collision() ) return false;
  tPPtr parent = const_ptr_cast<tPPtr>(par->final());
  if ( collision()->finalStep() != this || parent->next() ) return false;
  ParticleSet::iterator pit = theParticles.find(parent);
  if ( pit != theParticles.end() ) {
    theParticles.erase(pit);
    if ( parent->birthStep() == this ) theIntermediates.insert(parent);
  } else {
    if ( parent != collision()->incoming().first &&
	 parent != collision()->incoming().second &&
	 parent->children().empty() ) return false;
  }
  parent->rep().theChildren.push_back(child);
  child->rep().theParents.push_back(parent);
  child->rep().theBirthStep = this;
  addParticle(child);
  if ( !fixColour || !parent->hasColourInfo() || !parent->coloured() ||
       !child->coloured() ) return true;
  if ( parent->hasColour() && child->hasColour() &&
       !parent->outgoingColour() && !child->colourLine() )
    parent->colourFlow(child);
  if ( parent->hasAntiColour() && child->hasAntiColour() &&
       !child->antiColourLine() ) {
    if ( parent->outgoingAntiColour() )
      parent->antiColourLine()->
	removeAntiColoured(parent->outgoingAntiColour());
    parent->antiColourFlow(child);
  }
  return true;
}

void Step::addDecayNoCheck(tPPtr parent, tPPtr child) {
  ParticleSet::iterator pit = theParticles.find(parent);
  if ( pit != theParticles.end() ) {
    theParticles.erase(pit);
    if ( parent->birthStep() == this ) theIntermediates.insert(parent);
  }
  child->rep().theBirthStep = this;
  addParticle(child);
}

void Step::addDecayProduct(tPPtr child) {
  for ( int i = 0, N = child->parents().size(); i < N; ++i ) {
    ParticleSet::iterator pit = theParticles.find(child->parents()[i]);
    if ( pit != theParticles.end() ) {
      theParticles.erase(pit);
      if ( child->parents()[i]->birthStep() == this )
	theIntermediates.insert(child->parents()[i]);
    }
  }
  child->rep().theBirthStep = this;
  addParticle(child);
}

void Step::fixColourFlow() {
  tParticleVector news;
  for ( ParticleSet::iterator pi = theParticles.begin();
	pi != theParticles.end(); ++pi )
    if ( (**pi).birthStep() == this ) news.push_back(*pi);
  for ( int i = 0, N = news.size(); i < N; ++i ) {
    tPPtr p = news[i];
    if ( p->hasColour() && !p->antiColourNeighbour() ) {
      tPPtr ng = p;
      while ( ( ng = ng->incomingColour() ) && !ng->antiColourNeighbour() );
      if ( ng ) {
	ng = ng->antiColourNeighbour();
	if ( !ng->outgoingColour() ) ng = copyParticle(ng);
	while ( ng->outgoingColour() ) ng = ng->outgoingColour();
	p->antiColourConnect(ng);
      }
    }
    if ( p->hasAntiColour() && !p->colourNeighbour() ) {
      tPPtr ng = p;
      while ( ( ng = ng->incomingAntiColour() ) && !ng->colourNeighbour() );
      if ( ng ) {
	ng = ng->colourNeighbour();
	if ( !ng->outgoingAntiColour() ) ng = copyParticle(ng);
	while ( ng->outgoingAntiColour() ) ng = ng->outgoingAntiColour();
	p->colourConnect(ng);
      }
    }
  }
}

tPPtr Step::antiColourNeighbour(tcPPtr p) const {
  return colourNeighbour(p, true);
}

tPPtr Step::colourNeighbour(tcPPtr p, bool anti) const {
  if ( !member(particles(), const_ptr_cast<tPPtr>(p)) ) return tPPtr();
  tColinePtr line = p->colourLine(!anti);
  if ( !line ) return tPPtr();
  for ( ParticleSet::const_iterator it = particles().begin();
	it != particles().end(); ++it )
    if ( (**it).colourLine(anti) == line ) return *it;
  return tPPtr();
}

vector<tPVector> Step::getSinglets(tParticleSet & left) {
  vector<tPVector> ret;
  while ( !left.empty() ) {
    tPPtr first = *left.begin();
    left.erase(first);
    if ( !first->hasColourInfo() || !first->coloured() ) continue;
    tPPtr last = first;
    while ( last->antiColourNeighbour() &&
	    last->antiColourNeighbour() != first )
      last = last->antiColourNeighbour();
    while ( first->colourNeighbour() && first->colourNeighbour() != last )
      first = first->colourNeighbour();
    ret.push_back(tPVector());
    for ( ; first != last; first = first->antiColourNeighbour() ) {
      left.erase(first);
      ret.back().push_back(first);
    }
    left.erase(first);
    ret.back().push_back(first);
  }
  return ret;
}

ostream & ThePEG::operator<<(ostream & os, const Step & s) {
  if ( !s.intermediates().empty() ) os << "--- intermediates:" << endl;
  Particle::PrintParticles(os, s.intermediates().begin(),
			   s.intermediates().end());
  os << "--- final:" << endl;
  LorentzMomentum sum;
  Energy sumx = Energy();
  Energy sumy = Energy();
  Energy sumz = Energy();
  Particle::PrintParticles(os, s.particles().begin(), s.particles().end());
  for ( ParticleSet::const_iterator it = s.particles().begin();
	it != s.particles().end(); ++it ) {
    sum += (**it).momentum();
    sumx += sqr((**it).momentum().x());
    sumy += sqr((**it).momentum().y());
    sumz += sqr((**it).momentum().z());
  }
  os << "---------------------------------------"
     << "---------------------------------------" << endl
     << "     Sum of momenta:        ";
  int oldprecision = os.precision();
  sumx = ( abs(sum.x()) > sqrt(Constants::epsilon*sumx) ? sum.x(): Energy() );
  sumy = ( abs(sum.y()) > sqrt(Constants::epsilon*sumy) ? sum.y(): Energy() );
  sumz = ( abs(sum.z()) > sqrt(Constants::epsilon*sumz) ? sum.z(): Energy() );
  os << setprecision(3) << setw(10) << sumx/GeV << setw(10) << sumy/GeV
     << setw(10) << sumz/GeV << setw(10) << sum.e()/GeV
     << setw(10) << sum.m()/GeV << endl << setprecision(oldprecision);
  return os;
}

void Step::persistentOutput(PersistentOStream & os) const {
  os << theParticles << theIntermediates << theSubProcesses << allParticles
     << theCollision;
  EventConfig::putHandler(os, theHandler);
}

void Step::persistentInput(PersistentIStream & is, int) {
  is >> theParticles >> theIntermediates >> theSubProcesses >> allParticles
     >> theCollision;
  EventConfig::getHandler(is, theHandler);
}

ClassDescription<Step> Step::initStep;

void Step::Init() {}

ThePEG_IMPLEMENT_SET(StepPtr,StepSet)
