// -*- C++ -*-
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
    theClassName(newClassName), isDependencySafe(depSafe),
    isReadOnly(readonly) {
  BaseRepository::Register(*this, newTypeInfo);
}

string InterfaceBase::fullDescription(const InterfacedBase & ib) const {
  return type() + '\n' + name() + '\n' + description() +
    ( readOnly()? "\n-*-readonly-*-\n": "\n-*-mutable-*-\n" );
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

