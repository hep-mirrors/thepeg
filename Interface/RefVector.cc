// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RefVector class.
//

#include "InterfacedBase.h"
#include "RefVector.h"
#include "RefVector.xh"
#include "ThePEG/Utilities/HoldFlag.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Repository/BaseRepository.h"

using namespace ThePEG;

RefVectorBase::
RefVectorBase(string newName, string newDescription,
	      string newClassName, const type_info & newTypeInfo,
	      string newRefClassName, const type_info & newRefTypeInfo,
	      int newSize, bool depSafe, bool readonly,
	      bool norebind, bool nullable, bool defnull)
  : RefInterfaceBase(newName, newDescription, newClassName, newTypeInfo,
		     newRefClassName, newRefTypeInfo, depSafe,
		     readonly, norebind, nullable, defnull),
    theSize(newSize) {}

IVector RefVectorBase::getReferences(const InterfacedBase & i) const {
  return get(i);
}

string RefVectorBase::exec(InterfacedBase & i, string action,
			   string arguments) const throw(InterfaceException) {
  istringstream arg(arguments.c_str());
  int place = -1;
  if ( !( arg >> place ) ) place = -1;
  ostringstream ret;
  if ( action == "get" ) {
    IVector refvec = get(i);
    if ( place >= 0 ) {
      if ( refvec[place] ) return refvec[place]->fullName();
      else return "*** NULL Reference ***";
    }
    for ( IVector::size_type j = 0; j < refvec.size(); ++j ) {
      if ( j != 0 ) ret << ", ";
      if ( refvec[j] ) ret << refvec[j]->fullName();
      else ret << "*** NULL Reference ***";
    }
  } else if ( action == "erase" ) {
    erase(i, place);
  } else if ( action == "set" || action == "insert" ) {
    string name;
    arg >> name;
    IBPtr ip;
    if ( name.size() && name != "NULL") ip = BaseRepository::TraceObject(name);
    if ( action == "set" ) set(i, ip, place);
    else insert(i, ip, place);
  } else
    throw InterExUnknown(*this, i);
  return ret.str();
}

string RefVectorBase::type() const {
  return string("V<") + refClassName() + ">";
}

void RefVectorBase::
rebind(InterfacedBase & i, const TranslationMap & trans,
       const IVector & defs) const {
  if ( noRebind() ) return;
  IVector oldrefs =  get(i);
  IVector newRefs;
  for ( unsigned int ir = 0; ir < oldrefs.size(); ++ir ) {
    IBPtr oldref = oldrefs[ir];;
    IBPtr newref;
    if ( oldref ) {
      newref = trans.translate(oldref);
      if ( !dependencySafe() && newref->fullName() != oldref->fullName() )
	i.touch();
    }
    else if ( defaultIfNull() ) {
      for ( IVector::const_iterator p = defs.begin(); p != defs.end(); ++p ) {
	try {
	  if ( *p && check(i, *p, ir) ) {
	    newref = *p;
	    i.touch();
	    break;
	  }
	} catch ( ... ) {}
      }
    }
    newRefs.push_back(newref);
  }

  HoldFlag<> depflag(isDependencySafe);
  HoldFlag<> roflag(isReadOnly, false);

  if ( size() <= 0 )
    for ( IVector::size_type j = oldrefs.size(); j > 0; --j )
      erase(i, j - 1);

  for ( IVector::size_type j = 0; j < oldrefs.size(); ++j )
    if ( size() > 0 )
      set(i, newRefs[j], j, false);
    else
      insert(i, newRefs[j], j, false);
}

RefVExRefClass::RefVExRefClass(const RefInterfaceBase & i,
			       const InterfacedBase & o,
			       cIBPtr r, const char * s) {
  theMessage << "Could not " << s << " the object \""
	     << (r? r->name().c_str(): "<NULL>")
	     << "\" in the reference vector \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because it is not of the required class ("
	     << i.refClassName() << ").";
  severity(maybeabort);
}

RefVExSetUnknown::RefVExSetUnknown(const RefInterfaceBase & i,
				   const InterfacedBase & o,
				   cIBPtr r, int j, const char * s) {
  theMessage << "Could not " << s
	     << " the object \"" << (r? r->name().c_str(): "<NULL>")
	     << " at position " << j << " in the reference vector \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because the " << s
	     << " function threw an unknown exception.";
  severity(maybeabort);
}

RefVExSetUnfound::RefVExSetUnfound(const InterfaceBase & i,
				   const InterfacedBase & o,
				   string n) {
  theMessage << "Could not set the object named \""
	     <<  n
	     << " in the reference vector \""
	     << i.name() << "\" of \"" << o.name()
	     << "\"because the object was not found.";
  severity(maybeabort);
}

RefVExIndex::RefVExIndex(const InterfaceBase & i,
			 const InterfacedBase & o, int j) {
  theMessage << "Could not access element " << j
	     << " of the reference vector \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the index was outside of the allowed range.";
  severity(maybeabort);
}

RefVExFixed::RefVExFixed(const InterfaceBase & i, const InterfacedBase & o) {
  theMessage << "Cannot insert or delete in the reference vector \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" since the vector is of fixed size.";
  severity(maybeabort);
}

RefVExDelUnknown::RefVExDelUnknown(const InterfaceBase & i,
				   const InterfacedBase & o, int j) {
  theMessage << "Could not delete the value at position " << j
	     << " from the reference vector \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the delete function threw an unknown exception.";
  severity(maybeabort);
}

RefVExGetUnknown::RefVExGetUnknown(const InterfaceBase & i,
				   const InterfacedBase & o) {
  theMessage << "Could not get the reference vector \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the get function threw an  unknown exception.";
  severity(maybeabort);
}

RefVExNoSet::RefVExNoSet(const InterfaceBase & i,  const InterfacedBase & o) {
  theMessage << "Could not set an object in the reference vector \"" << i.name()
	     << "\" for the object \"" << o.name() 
	     << "\" because no set function has been specified.";
  severity(warning);
}


RefVExNoIns::RefVExNoIns(const InterfaceBase & i,  const InterfacedBase & o) {
  theMessage << "Could not insert an object in the reference vector \""
	     << i.name() << "\" for the object \"" << o.name() 
	     << "\" because no insert function has been specified.";
  severity(warning);
}


RefVExNoDel::RefVExNoDel(const InterfaceBase & i,  const InterfacedBase & o) {
  theMessage << "Could not erase an object in the reference vector \""
	     << i.name() << "\" for the object \"" << o.name() 
	     << "\" because no erase function has been specified.";
  severity(warning);
}

