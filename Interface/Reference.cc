// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ReferenceBase class.
//

#include "InterfacedBase.h"
#include "Reference.h"
#include "Reference.xh"
#include "ThePEG/Utilities/HoldFlag.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Repository/BaseRepository.h"

using namespace ThePEG;

ReferenceBase::
ReferenceBase(string newName, string newDescription,
	      string newClassName, const type_info & newTypeInfo,
	      string newRefClassName, const type_info & newRefTypeInfo,
	      bool depSafe, bool readonly, bool norebind, bool nullable,
	      bool defnull)
  : RefInterfaceBase(newName, newDescription, newClassName, newTypeInfo,
		     newRefClassName, newRefTypeInfo, depSafe,
		     readonly, norebind, nullable, defnull) {}

IVector ReferenceBase::getReferences(const InterfacedBase & i) const {
  IVector r;
  r.push_back(get(i));
  return r;
}

string ReferenceBase::exec(InterfacedBase & i, string action,
			   string arguments) const throw(InterfaceException) {
  ostringstream ret;
  istringstream arg(arguments.c_str());
  if ( action == "get" ) {
    cIBPtr ref = get(i);
    if ( ref ) ret << ref->fullName();
    else ret << "*** NULL Reference ***";
  } else if ( action == "set" ) {
    string name;
    arg >> name;
    IBPtr ip;
    if ( name.size() && name != "NULL") ip = BaseRepository::TraceObject(name);
    set(i, ip);
  } else
    throw InterExUnknown(*this, i);
  return ret.str();
}

string ReferenceBase::type() const {
  return string("R<") + refClassName() + ">";
}

string ReferenceBase::doxygenType() const {
  return "Reference to objects of class " + refClassName();
}

void ReferenceBase::
rebind(InterfacedBase & i,  const TranslationMap & trans,
       const IVector & defs) const {
  if ( noRebind() ) return;
  IBPtr oldref = get(i);
  IBPtr newref;
  if ( oldref ) {
    newref = trans.translate(oldref);
    if ( !dependencySafe() && oldref && newref &&
	 newref->fullName() != oldref->fullName() )
      i.touch();
  } else if ( defaultIfNull() ) {
    try {
      for ( IVector::const_iterator p = defs.begin(); p != defs.end(); ++p ) {
	if ( *p && check(i, *p) ) {
	  newref = *p;
	  i.touch();
	  break;
	}
      }
    } catch ( ... ) {}
  }

  HoldFlag<> depflag(isDependencySafe);
  HoldFlag<> roflag(isReadOnly, false);
  set(i, newref, false);
}

RefExSetRefClass::RefExSetRefClass(const RefInterfaceBase & i,
				   const InterfacedBase & o, cIBPtr r) {
  theMessage << "Could not set the reference \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to the object \""
	     << (r? r->name().c_str(): "<NULL>")
	     << "\" because it is not of the required class ("
	     << i.refClassName() << ").";
  severity(maybeabort);
}

RefExSetUnknown::RefExSetUnknown(const InterfaceBase & i,
				 const InterfacedBase & o, cIBPtr r) {
  theMessage << "Could not set the reference \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to the object \""
	     << (r? r->name().c_str(): "<NULL>")
	     << "\" because the set function threw an  unknown exception.";
  severity(maybeabort);
}

RefExGetUnknown::RefExGetUnknown(const InterfaceBase & i,
				 const InterfacedBase & o) {
  theMessage << "Could not get the reference \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the get function threw an  unknown exception.";
  severity(maybeabort);
}

RefExSetNoobj::RefExSetNoobj(const InterfaceBase & i, const InterfacedBase & o,
			     string n) {
  theMessage << "Could not set the reference \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the specified object \""
	     << n << "\" does not exist.";
  severity(warning);
}

RefExSetMessage::
RefExSetMessage(string ref, const InterfacedBase & o,
		const InterfacedBase & o2, string m) {
  theMessage << "Could not set the reference \"" << ref
	     << "\" for the object \"" << o.name()
	     << "\" to \"" << o2.name() << "\"." << m;
  severity(warning);
}

