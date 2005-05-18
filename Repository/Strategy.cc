// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Strategy class.
//

#include "Strategy.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Strategy.tcc"
#endif

using namespace ThePEG;

Strategy::Strategy() {}

Strategy::Strategy(const Strategy & s)
  : Interfaced(s), theParticles(s.theParticles),
    theDefaultObjects(s.theDefaultObjects) {}

Strategy::~Strategy() {}

IBPtr Strategy::clone() const {
  return new_ptr(*this);
}

void Strategy::persistentOutput(PersistentOStream & os) const {
  os << theParticles << theDefaultObjects;
}

void Strategy::persistentInput(PersistentIStream & is, int) {
  is >> theParticles >> theDefaultObjects;
}

ClassDescription<Strategy> Strategy::initStrategy;

void Strategy::setLocalParticles(PDPtr pd, int) {
  particles()[pd->id()] = pd;
}
  
void Strategy::insLocalParticles(PDPtr pd, int) {
  particles()[pd->id()] = pd;
}
  
void Strategy::delLocalParticles(int place) {
  ParticleMap::iterator it = particles().begin();
  while ( place-- && it != particles().end() ) ++it;
  if ( it != particles().end() ) particles().erase(it);
}

vector<PDPtr> Strategy::getLocalParticles() const {
  vector<PDPtr> ret;
  for ( ParticleMap::const_iterator it = particles().begin();
	it != particles().end(); ++it ) ret.push_back(it->second);
  return ret;
}

void Strategy::Init() {
  
  static ClassDocumentation<Strategy> documentation
    ("There is no documentation for the ThePEG::Strategy class");

  static RefVector<Strategy,ParticleData> interfaceLocalParticles
    ("LocalParticles",
     "Special versions of ThePEG::ParticleData objects to be used. Note "
     "that to delete an object, its number in the list "
     "should be given, rather than its id number.",
     0, 0, false, false, true, false,
     &Strategy::setLocalParticles, &Strategy::insLocalParticles,
     &Strategy::delLocalParticles, &Strategy::getLocalParticles);

  static RefVector<Strategy,Interfaced> interfaceDefaultObjects
    ("DefaultObjects",
     "A vector of pointers to default objects. In a ThePEG::Reference or "
     "ThePEG::RefVector interface with the defaultIfNull() flag set, if a "
     "null pointer is encountered this vector is gone through until an "
     "acceptable object is found in which case the null pointer is replaced "
     "by a pointer to this object. Note that the default objects given in the "
     "ThePEG::OldEventGenerator are gone through first and are given precedence.",
     &Strategy::theDefaultObjects, 0, true, false, true, false, false);

}

