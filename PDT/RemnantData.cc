// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantData class.
//

#include "RemnantData.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantData.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantData::~RemnantData() {}

void RemnantData::persistentOutput(PersistentOStream &) const {
  // *** ATTENTION *** os << ; // Add all member variable which should be written persistently here.
}

void RemnantData::persistentInput(PersistentIStream &, int) {
  // *** ATTENTION *** is >> ; // Add all member variable which should be read persistently here.
}

ClassDescription<RemnantData> RemnantData::initRemnantData;
// Definition of the static class description member.

void RemnantData::Init() {

  static ClassDocumentation<RemnantData> documentation
    ("There is no documentation for the RemnantData class");

}

