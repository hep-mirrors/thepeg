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
  // The following is for backward compatibility and will eventually
  // be removed.
  string name = pb.name();
  if ( name.find('/') == string::npos ) {
    if ( name.substr(0, 2) == "::" ) name = name.substr(2);
    if ( name.find("::") == string::npos ) return;
    while ( name.find("::") != string::npos )
      name.replace(name.find("::"), 2, "/");
    name = "/" + name;
    stringMap()[name] = &pb;
  } else {
    if ( name[0] == '/' ) name = name.substr(1);
    while ( name.find('/') != string::npos )
      name.replace(name.find('/'), 1, "::");
    stringMap()[name] = &pb;
  }
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
