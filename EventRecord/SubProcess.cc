// -*- C++ -*-
//
// SubProcess.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SubProcess class.
//
#include "SubProcess.h"
#include "ThePEG/EventRecord/Collision.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/EventRecord/ParticleTraits.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include <iostream>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "SubProcess.tcc"
#endif

using namespace ThePEG;

SubProcess::
SubProcess(const PPair & newIncoming,
 	   tCollPtr newCollision, tcEventBasePtr newHandler)
  : theHandler(newHandler), theCollision(newCollision),
    theIncoming(newIncoming), isDecayed(false) {}

SubProcess::~SubProcess() {}

SubProPtr SubProcess::clone() const {
  return ptr_new<SubProPtr>(*this);
}

void SubProcess::addIntermediate(tPPtr p, bool fixrelations) {
  if ( fixrelations ) {
    incoming().first->rep().theChildren.push_back(p);
    incoming().second->rep().theChildren.push_back(p);
    p->rep().theParents.push_back(incoming().first);
    p->rep().theParents.push_back(incoming().second);
  }
  theIntermediates.push_back(p);
}

void SubProcess::addOutgoing(tPPtr p, bool fixrelations) {
  if ( fixrelations ) {
    if ( intermediates().empty() ) {
      incoming().first->rep().theChildren.push_back(p);
      incoming().second->rep().theChildren.push_back(p);
      p->rep().theParents.push_back(incoming().first);
      p->rep().theParents.push_back(incoming().second);
    } else {
      for (ParticleVector::iterator it = theIntermediates.begin();
	   it != theIntermediates.end(); ++it ) {
	(**it).rep().theChildren.push_back(p);
	p->rep().theParents.push_back(*it);
      }
    }
  }
  theOutgoing.push_back(p);
}

void SubProcess::rebind(const EventTranslationMap & trans) {
  theIncoming.first = trans.translate(theIncoming.first);
  theIncoming.second = trans.translate(theIncoming.second);
  theCollision = trans.translate(theCollision);
  for ( ParticleVector::iterator pit = theOutgoing.begin();
	pit != theOutgoing.end(); ++pit )
    *pit = trans.translate(*pit);
  for ( ParticleVector::iterator pit = theIntermediates.begin();
	pit != theIntermediates.end(); ++pit )
    *pit = trans.translate(*pit);
}

void SubProcess::removeEntry(tPPtr p) {
  if ( p == theIncoming.first ) theIncoming.first = PPtr();
  if ( p == theIncoming.second ) theIncoming.second = PPtr();
  ParticleVector::iterator pit = theOutgoing.begin();
  while ( pit != theOutgoing.end() ) {
    if ( *pit == p ) pit = theOutgoing.erase(pit);
    else ++pit;
  }
  pit = theIntermediates.begin();
  while ( pit != theIntermediates.end() ) {
    if ( *pit == p ) pit = theIntermediates.erase(pit);
    else ++pit;
  }
}

void SubProcess::transform(const LorentzRotation & r) {
  incoming().first->transform(r);
  incoming().second->transform(r);
  for_each(intermediates(), Transformer(r));
  for_each(outgoing(), Transformer(r));
}

ostream & ThePEG::operator<<(ostream & os, const SubProcess & sp) {
  os << "--- incoming:" << endl
     << *sp.incoming().first << *sp.incoming().second;
  if ( !sp.intermediates().empty() ) os << "--- intermediates:" << endl;
  Particle::PrintParticles(os, sp.intermediates().begin(),
			   sp.intermediates().end());
  os << "--- outgoing:" << endl;
  Particle::PrintParticles(os, sp.outgoing().begin(), sp.outgoing().end());
  return os;
}

void SubProcess::debugme() const {
  cerr << *this;
  EventRecordBase::debugme();
}

void SubProcess::persistentOutput(PersistentOStream & os) const {
  EventConfig::putHandler(os, theHandler);
  os << theCollision << theIncoming << theIntermediates << theOutgoing
     << isDecayed;
}

void SubProcess::persistentInput(PersistentIStream & is, int) {
  EventConfig::getHandler(is, theHandler);
  is >> theCollision >> theIncoming >> theIntermediates >> theOutgoing
     >> isDecayed;
}

ClassDescription<SubProcess> SubProcess::initSubProcess;

void SubProcess::Init() {}

ThePEG_IMPLEMENT_SET(SubProPtr,SubProcessSet)
