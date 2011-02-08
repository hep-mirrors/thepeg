// -*- C++ -*-
//
// MultiColour.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultiColour class.
//

#include "MultiColour.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

vector<tcColinePtr> MultiColour::antiColourLines() const {
  return vector<tcColinePtr>(theAntiColourLines.begin(),
			    theAntiColourLines.end());
}

vector<tcColinePtr> MultiColour::colourLines() const {
  return vector<tcColinePtr>(theColourLines.begin(),
			    theColourLines.end());
}

bool MultiColour::hasColourLine(tcColinePtr line, bool anti) const {
  return ( anti? ( theAntiColourLines.find(line) != theAntiColourLines.end() ):
	   ( theColourLines.find(line) != theColourLines.end() ) );
}

void MultiColour::colourLine(tColinePtr line, bool anti) {
  if ( anti ) antiColourLine(line);
  else {
    if ( !colourLine() ) ColourBase::colourLine(line);
    theColourLines.insert(line);
  }
}

void MultiColour::antiColourLine(tColinePtr line) {
  if ( !antiColourLine() ) ColourBase::antiColourLine(line);
  theAntiColourLines.insert(line);
}

void MultiColour::removeColourLine(tcColinePtr line, bool anti) {
  if ( anti ) removeAntiColourLine(line);
  else {
    ColourBase::removeColourLine(line);
    theColourLines.erase(line);
  }
}

void MultiColour::removeAntiColourLine(tcColinePtr line) {
  ColourBase::removeAntiColourLine(line);
  theAntiColourLines.erase(line);
}

void MultiColour::persistentOutput(PersistentOStream & os) const {
  os << theColourLines << theColourLines;
}

void MultiColour::persistentInput(PersistentIStream & is, int) {
  is >> theColourLines >> theAntiColourLines;
}

ClassDescription<MultiColour> MultiColour::initMultiColour;
// Definition of the static class description member.

void MultiColour::Init() {

  static ClassDocumentation<MultiColour> documentation
    ("There is no documentation for the MultiColour class");

}

