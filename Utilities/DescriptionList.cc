// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DescriptionList class.
//

#include "DescriptionList.h"
#include "ClassDescription.h"

using namespace ThePEG;

void DescriptionList::hookup() {
  for ( DescriptionMap::iterator it = descriptionMap().begin();
	it != descriptionMap().end(); ++it ) it->second->setup();
}

void DescriptionList::Register(ClassDescriptionBase & pd) {
  if ( find(pd.info()) ) return;
  insert(pd);
  hookup();
}

DescriptionList::DescriptionMap & DescriptionList::descriptionMap() {
  static DescriptionMap theDescriptionMap;
  return theDescriptionMap;
}

DescriptionList::StringMap & DescriptionList::stringMap() {
  static StringMap theStringMap;
  return theStringMap;
}

void DescriptionList::insert(ClassDescriptionBase & pb) {
  descriptionMap()[&(pb.info())] = &pb;
  stringMap()[pb.name()] = &pb;
}

void DescriptionList::printHierarchies(ostream & os) {
  typedef ClassDescriptionBase::DescriptionVector DescVec;
  for ( DescriptionMap::iterator it = descriptionMap().begin();
	it != descriptionMap().end(); ++it ) {
    os << "Class Name '" << it->second->name() << "'\n (" << it->first->name()
       << "," <<  it->second << ") version " << it->second->version()
       << endl << "  Base classes:" << endl;
    for ( unsigned int i = 0; i < it->second->descriptions().size(); ++i )
      os << "   " << i << " '" << it->second->descriptions()[i]->name()
	 << "' (" << it->second->descriptions()[i] << ")" << endl;
  }
}
