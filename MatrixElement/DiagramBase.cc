// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DiagramBase class.
//

#include "DiagramBase.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/DescriptionList.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DiagramBase.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

DiagramBase::~DiagramBase() {}

struct ParticleOrdering {
  bool operator()(tcPDPtr p1, tcPDPtr p2) {
    return abs(p1->id()) > abs(p2->id()) ||
      ( abs(p1->id()) == abs(p2->id()) && p1->id() > p2->id() ) ||
      ( p1->id() == p2->id() && p1->fullName() > p2->fullName() );
  }
};

string DiagramBase::getTag() const {
  string tag;
  if ( !done() ) throw DiagramBaseSetupException(*this);
  for ( int i = 0; i < nIncoming(); ++i ) {
    if ( i ) tag += ",";
    tag += partons()[i]->PDGName();
  }
  tag += "->";

  multiset<tcPDPtr,ParticleOrdering> out;
  for ( int i = nIncoming(), N = partons().size(); i < N; ++i )
    out.insert(partons()[i]);
  for ( multiset<tcPDPtr,ParticleOrdering>::iterator i = out.begin();
	i != out.end(); ++i ) {
    if ( i != out.begin() ) tag += ",";
    tag += (**i).PDGName();
  }
  return tag;
}

void DiagramBase::persistentOutput(PersistentOStream & os) const {
  os << theNIncoming << thePartons << theId;
}

void DiagramBase::persistentInput(PersistentIStream & is, int) {
  is >> theNIncoming >> thePartons >> theId;
}

AbstractClassDescription<DiagramBase> DiagramBase::initDiagramBase;
// Definition of the static class description member.

void DiagramBase::Init() {}

DiagramBaseSetupException::DiagramBaseSetupException(const DiagramBase & db) {
  const ClassDescriptionBase * cd = DescriptionList::find(typeid(db));
  if ( !cd )
    theMessage << "Tried to use an unknown sub class of DiagramBase.";
  else
    theMessage << "The '" << cd->name()
	       << "' sub class did not setup the DiagramBase class correctly.";
  severity(abortnow);
}
