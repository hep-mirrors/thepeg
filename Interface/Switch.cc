// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SwitchBase class.
//

#include "InterfacedBase.h"
#include "Switch.h"

namespace ThePEG {

string SwitchBase::exec(InterfacedBase & i, string action,
		    string arguments) const throw(InterfaceException) {
  ostringstream ret;
  istringstream arg(arguments.c_str());
  if ( action == "get" ) {
    long opt = get(i);
    ret << opt;
    OptionMap::const_iterator oit = theOptions.find(opt);
    if ( oit ==  theOptions.end() )
      ret << " (Not a registered option) ";
    else
      ret << " (" << (oit->second).name() << ")";
  } else if ( action == "def" ) {
    long opt = def(i);
    ret << opt;
    OptionMap::const_iterator oit = theOptions.find(opt);
    if ( oit ==  theOptions.end() )
      ret << " (Not a registered option) ";
    else
      ret << " (" << (oit->second).name() << ")";
  } else if ( action == "setdef" ) {
    setDef(i);
  } else if ( action == "set" ) {
    long val;
    arg >> val;
    try {
      set(i, val);
      return ret.str();
    }
    catch ( Exception & ex ) {
      ex.handle();
    }
    istringstream arg2(arguments.c_str());
    string sval;
    arg2 >> sval;
    StringMap::const_iterator optit = theOptionNames.find(sval);
    if ( optit != theOptionNames.end() ) val = optit->second.value();
    set(i, val);
  } else
    throw InterExUnknown(*this, i);
  return ret.str();
}

string SwitchBase::type() const {
  return "Sw";
}

string SwitchBase::doxygenType() const {
  return "Switch";
}

SwExSetOpt::SwExSetOpt(const InterfaceBase & i,
		       const InterfacedBase & o, long v) {
  theMessage << "Could not set the switch \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to " << v
	     << "because it is not a registered option.";
  severity(warning);
}

SwExSetUnknown::SwExSetUnknown(const InterfaceBase & i,
			       const InterfacedBase & o, long v) {
  theMessage << "Could not set the switch \"" << i.name()
	     << "\" for the object \"" << o.name() << "\" to " << v
	     << " because the set function threw an unknown exception.";
  severity(maybeabort);
}

SwExGetUnknown::SwExGetUnknown(const InterfaceBase & i,
			       const InterfacedBase & o, const char * s) {
  theMessage << "Could not get the " << s << " value of switch \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the get function threw an unknown exception.";
  severity(maybeabort);
}

}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Switch.tcc"
#endif
