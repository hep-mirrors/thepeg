// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ConstituentParticleData class.
//

#include "ConstituentParticleData.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Parameter.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ConstituentParticleData.tcc"
#endif

using namespace ThePEG;

ConstituentParticleData::ConstituentParticleData(long newId, string newPDGName)
  : ParticleData(newId, newPDGName), theConstituentMass(0.0*GeV),
    theDefaultConstituentMass(0.0*GeV) {}


PDPtr ConstituentParticleData::
Create(long newId, string newPDGName) {
  return new_ptr(ConstituentParticleData(newId, newPDGName));
}

PDPair ConstituentParticleData::
Create(long newId, string newPDGName, string newAntiPDGName) {
  PDPair pap;
  pap.first = new_ptr(ConstituentParticleData(newId, newPDGName));
  pap.second = new_ptr(ConstituentParticleData(-newId, newAntiPDGName));
  antiSetup(pap);
  return pap;
}

ConstituentParticleData::~ConstituentParticleData() {}

void ConstituentParticleData::readSetup(istream & is) throw(SetupException) {
  ParticleData::readSetup(is);
  is >> iunit(theDefaultConstituentMass, GeV);
  theConstituentMass = theDefaultConstituentMass;
}

PDPtr ConstituentParticleData::pdclone() const {
  return new_ptr(*this);
}

void ConstituentParticleData::persistentOutput(PersistentOStream & os) const {
  os << ounit(theConstituentMass, GeV) << ounit(theDefaultConstituentMass, GeV);
}

void ConstituentParticleData::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theConstituentMass, GeV) >> iunit(theDefaultConstituentMass, GeV);
}

void ConstituentParticleData::setConstituentMass(Energy m) {
  theConstituentMass = m;
  ConstituentParticleData * apd =
    dynamic_cast<ConstituentParticleData*>(CC().operator->());
  if ( synchronized() && apd ) apd->theConstituentMass = m;
}

Energy ConstituentParticleData::defConstituentMass() const {
  return theDefaultConstituentMass;
}

Energy ConstituentParticleData::maxConstituentMass() const {
  return 10.0*max(constituentMass(),defConstituentMass());
}

ClassDescription<ConstituentParticleData>
ConstituentParticleData::initConstituentParticleData;

void ConstituentParticleData::Init() {

  static Parameter<ConstituentParticleData,Energy> interfaceMass
    ("ConstituentMass",
     "The constituent mass of the particle in GeV.",
     &ConstituentParticleData::theConstituentMass,
     GeV, 0.0*GeV, 0.0*GeV,
     Constants::MaxEnergy, false, false, true,
     &ConstituentParticleData::setConstituentMass, 0, 0,
     &ConstituentParticleData::maxConstituentMass,
     &ConstituentParticleData::defConstituentMass);

}

