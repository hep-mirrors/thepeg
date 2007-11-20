// -*- C++ -*-
//
// InterfaceBase.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the InterfaceBase class.
//

#include "InterfaceBase.h"
#include "InterfacedBase.h"
#include "ThePEG/Repository/BaseRepository.h"

namespace ThePEG {

InterfaceBase::InterfaceBase(string newName,
			     string newDescription,
			     string newClassName,
			     const type_info & newTypeInfo, bool depSafe,
			     bool readonly)
  : Named(newName), theDescription(newDescription),
    theClassName(newClassName), theRank(-1.0), isDependencySafe(depSafe),
    isReadOnly(readonly) {
  BaseRepository::Register(*this, newTypeInfo);
}

string InterfaceBase::fullDescription(const InterfacedBase &) const {
  return type() + '\n' + name() + '\n' + description() +
    ( readOnly()? "\n-*-readonly-*-\n": "\n-*-mutable-*-\n" );
}

void InterfaceBase::doxygenDescription(ostream & os) const {
  os << "\n<hr><b>Name: <a name=\"" << name() << "\"><code>"
     << name() << "</code></a></b><br>\n"
     << "<b>Type:</b> " << doxygenType();
  if ( readOnly() ) os << " (read-only)";
  os << " <br>\n"
     << "\\par Description:\n"
     << description() << "<br>\n";
}

IVector InterfaceBase::getReferences(const InterfacedBase &) const {
  return IVector();
}

bool InterfaceBase::NoReadOnly = false;

InterExClass::InterExClass(const InterfaceBase & i, const InterfacedBase & o) {
  theMessage << "Could not access the interface \"" << i.name()
	     << "\" of the object \"" << o.name() << "\" because the object "
	     << "is not of the required class (" << i.className() << ").";
  severity(abortnow);
}

InterExSetup::InterExSetup(const InterfaceBase & i, const InterfacedBase & o) {
  theMessage << "Could not access the interface \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" since no get/set member function or variable was found.";
  severity(abortnow);
}

InterExUnknown::InterExUnknown(const InterfaceBase & i,
			       const InterfacedBase & o) {
  theMessage << "Could not perform action on the interface  \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because the requested action was not recognized";
  severity(maybeabort);
}

InterExReadOnly::InterExReadOnly(const InterfaceBase & i,
				 const InterfacedBase & o) {
  theMessage << "Could not perform action on the interface  \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because this interface is read-only.";
  severity(maybeabort);
}

InterExNoNull::InterExNoNull(const InterfaceBase & i,
			     const InterfacedBase & o) {
  theMessage << "Could not set reference \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" to <Null> because null pointers are explicitly "
	     << "disallowed.";
  severity(warning);
}


}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InterfaceBase.tcc"
#endif

