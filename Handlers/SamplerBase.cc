// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SamplerBase class.
//

#include "SamplerBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Handlers/StandardEventHandler.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SamplerBase.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SamplerBase::~SamplerBase() {}

int SamplerBase::lastBin() const {
  return 0;
}

void SamplerBase::persistentOutput(PersistentOStream & os) const {
  os << theEventHandler << theLastPoint;
  // Add all member variable which should be written persistently here.
}

void SamplerBase::persistentInput(PersistentIStream & is, int) {
  is >> theEventHandler >> theLastPoint;
  // Add all member variable which should be read persistently here.
}

AbstractClassDescription<SamplerBase> SamplerBase::initSamplerBase;
// Definition of the static class description member.

void SamplerBase::Init() {

  static ClassDocumentation<SamplerBase> documentation
    ("This is the base class for all phase space sampler classes to be"
     "used by the ThePEG::EventHandler class to sample the phase"
     "space according to the cross sections for the proceses in the"
     "ThePEG::EventHandler.");

}

