// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Interfaced class.
//

#include "Interfaced.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Particle.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Interfaced.tcc"
#endif

using namespace ThePEG;

void Interfaced::registerRepository(IBPtr i) {
  Repository::Register(i);
}

void Interfaced::registerRepository(IBPtr i, string newName) {
  Repository::Register(i, newName);
}

void Interfaced::setUsed() const {
  theUseFlag = true;
  if ( generator() ) generator()->use(*this);
}

PPtr Interfaced::getParticle(long newId) const {
  PPtr p(generator()? generator()->getParticle(newId): PPtr());
  return p;
}

PDPtr Interfaced::getParticleData(long newId) const {
  PDPtr p(generator()? generator()->getParticleData(newId):
	  Repository::defaultParticle(newId));
  return p;
}

void Interfaced::persistentOutput(PersistentOStream & os) const {
  os << theGenerator << theUseFlag;
}

void Interfaced::persistentInput(PersistentIStream & is , int) {
  is >> theGenerator >> theUseFlag;
}

AbstractClassDescription<Interfaced> Interfaced::initInterfaced;

void Interfaced::Init() {}

void Interfaced::debug() const {
  cerr << "Object name: " << name() << " Class name: "
       << DescriptionList::find(typeid(*this))->name() << endl;
}

