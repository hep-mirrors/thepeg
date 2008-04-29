// -*- C++ -*-
//
// Strategy.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Strategy class.
//

#include "Strategy.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Utilities/Throw.h"

using namespace ThePEG;

string Strategy::localParticlesDir() const {
  return theLocalParticlesDir;
}

void Strategy::setLocalParticlesDir(string x) {
  if ( x == "" ) {
    theLocalParticlesDir = x;
    return;
  }
  if ( x[0] != '/' )
    Throw<InterfaceException>()
      << "LocalParticlesDir directory name must start with a '/'."
      << Exception::setuperror;
  if ( x[x.length() - 1] != '/' ) x += '/';
  try {
    Repository::CheckObjectDirectory(x);
  }
  catch ( Exception & e ) {
    e.handle();
    Throw<InterfaceException>()
      << "No directory named " << x << " in the repository."
      << Exception::setuperror;
  }
  theLocalParticlesDir = x;
}

IBPtr Strategy::clone() const {
  return new_ptr(*this);
}

IBPtr Strategy::fullclone() const {
  return new_ptr(*this);
}

void Strategy::persistentOutput(PersistentOStream & os) const {
  os << theParticles << theLocalParticlesDir << theDefaultObjects;
}

void Strategy::persistentInput(PersistentIStream & is, int) {
  is >> theParticles >> theLocalParticlesDir >> theDefaultObjects;
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
    ("Represents a general strategy to be assigned to an EventGenerator. "
     "It contains a set of default ParticleData objects which takes "
     "presedence over the ones in the Repository (although not over "
     "the ones in the EventGenerator). It also contains a set of other "
     "default objects which are automatically assigned to all Reference "
     "and RefVector interfaces which have the "
     "InterfaceBase::defaultIfNull() flag set.");

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
     "ThePEG::EventGenerator are gone through first and are given precedence.",
     &Strategy::theDefaultObjects, 0, true, false, true, false, false);

  static Parameter<Strategy,string> interfaceLocalParticlesDir
    ("LocalParticlesDir",
     "A directory in the repository which will be scanned for particles "
     "which will be included as default particles in a run. These particles "
     "will be overridden by particles specified in "
     "<interface>LocalParticles</interface> and default particles "
     "specified directly in the EventGenerator.",
     &Strategy::theLocalParticlesDir, "",
     true, false,
     &Strategy::setLocalParticlesDir, (string(Strategy::*)()const)(0),
     (string(Strategy::*)()const)(0));

  interfaceLocalParticles.rank(10);
  interfaceLocalParticlesDir.rank(11);
  interfaceDefaultObjects.rank(9);

}
