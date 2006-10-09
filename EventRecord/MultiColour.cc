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

