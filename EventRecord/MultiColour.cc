// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultiColour class.
//

#include "MultiColour.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultiColour.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

MultiColour::~MultiColour() {}

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

