// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CommandBase class.
//

#include "InterfacedBase.h"
#include "Command.h"

using namespace ThePEG;

string CommandBase::exec(InterfacedBase & i, string,
			 string arguments) const throw(InterfaceException) {
  return cmd(i, arguments);
}

string CommandBase::type() const {
  return "Cm";
}

string CommandBase::doxygenType() const {
  return "Command";
}

CmdExUnknown::CmdExUnknown(const InterfaceBase & i,
			   const InterfacedBase & o, string c) {
  theMessage << "Could execute the command \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" with argument " << c
	     << "because the command function threw an unknown exception.";
  severity(warning);
}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Command.tcc"
#endif

