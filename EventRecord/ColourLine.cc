// -*- C++ -*-
//
// ColourLine.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ColourLine class.
//

#include "ColourLine.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

tColinePtr ColourLine::create(tPPtr col, tPPtr anti) {
  if ( col->colourLine() || anti->antiColourLine() ) return tColinePtr();
  ColinePtr l = new_ptr(ColourLine());
  l->addColoured(col);
  l->addAntiColoured(anti);
  return l;
}

tColinePtr ColourLine::create(tPPtr col, bool anti) {
  if ( col->colourLine(anti) ) return tColinePtr();
  ColinePtr l = new_ptr(ColourLine());
  l->addColoured(col, anti);
  return l;
}

ColourLine::~ColourLine() {}

tPPtr ColourLine::startParticle() const {
  return sourceNeighbours().first || antiColoured().empty() ? 
    tPPtr() : antiColoured().back();
}

tPPtr ColourLine::endParticle() const {
  return sinkNeighbours().first || coloured().empty() ? 
    tPPtr() : coloured().back();
}

void ColourLine::addAntiColoured(tPPtr p) {
  theAntiColoured.push_back(p);
  p->colourInfo()->antiColourLine(this);
}

void ColourLine::addColoured(tPPtr p, bool anti) {
  if ( anti ) addAntiColoured(p);
  else {
    theColoured.push_back(p);
    p->colourInfo()->colourLine(this);
  }
}

void ColourLine::removeAntiColoured(tPPtr p) {
  tPVector::iterator cp=find(range(theAntiColoured), p);
  if(cp!=theAntiColoured.end()) theAntiColoured.erase(cp);
  p->colourInfo()->removeAntiColourLine(this);
}

void ColourLine::removeColoured(tPPtr p, bool anti) {
  if ( anti ) removeAntiColoured(p);
  else {
    tPVector::iterator cp=find(range(theColoured), p);
    if(cp!=theColoured.end()) theColoured.erase(cp);
    p->colourInfo()->removeColourLine(this);
  }
}

bool ColourLine::join(ColinePtr line) {
  if ( !startParticle() || startParticle() != line->endParticle() )
    return false;
  while ( line->coloured().size() ) {
    tPPtr p = line->coloured()[0];
    line->removeColoured(p);
    theColoured.insert(theColoured.begin(), p);
    p->colourInfo()->colourLine(this);
  }
  while ( line->antiColoured().size() ) {
    tPPtr p = line->antiColoured()[0];
    line->removeAntiColoured(p);
    theAntiColoured.push_back(p);
    p->colourInfo()->antiColourLine(this);
  }
  return true;
}

void ColourLine::write(ostream & os, tcEventPtr event, bool anti) const {
  os << ( anti? '-': '+' );
  int index = event->colourLineIndex(this);
  if ( sourceNeighbours().first && sourceNeighbours().second )
    os << '(' << event->colourLineIndex(sourceNeighbours().first)
       << '*' << event->colourLineIndex(sourceNeighbours().second) << ')';
  os << index;
  if ( sinkNeighbours().first && sinkNeighbours().second )
    os << '(' << event->colourLineIndex(sinkNeighbours().first)
       << '.' << event->colourLineIndex(sinkNeighbours().second) << ')';
}  

void ColourLine::persistentOutput(PersistentOStream & os) const {
  os << theColoured << theAntiColoured << theSourceNeighbours
     << theSinkNeighbours;
}

void ColourLine::persistentInput(PersistentIStream & is, int) {
  is >> theColoured >> theAntiColoured >> theSourceNeighbours
     >> theSinkNeighbours;
}

ClassDescription<ColourLine> ColourLine::initColourLine;
// Definition of the static class description member.

