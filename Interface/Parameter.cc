// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ParameterBase class.
//

#include "InterfacedBase.h"
#include "Parameter.h"
#include "Parameter.xh"

namespace ThePEG {

string ParameterBase::exec(InterfacedBase & i, string action,
			   string arguments) const  throw(InterfaceException) {
  ostringstream ret;
  istringstream arg(arguments.c_str());
  if ( action == "get" ) {
    return get(i);
  } else if ( action == "min" ) {
    return minimum(i);
  } else if ( action == "max" ) {
    return maximum(i);
  } else if ( action == "def" ) {
    return def(i);
  } else if ( action == "setdef" ) {
    setDef(i);
  } else if ( action == "set" ) {
    set(i, arguments);
  } else
    throw InterExUnknown(*this, i);
  return "";
}

string ParameterBase::fullDescription(const InterfacedBase & ib) const {
  string min = minimum(ib);
  if ( min.empty() ) min = "-inf";
  string max = maximum(ib);
  if ( max.empty() ) max = "inf";
  
  return InterfaceBase::fullDescription(ib) + get(ib) + '\n' +
    min + '\n' + def(ib) + '\n' + max + '\n';
}

ParExGetUnknown::ParExGetUnknown(const InterfaceBase & i,
				 const InterfacedBase & o, const char * s) {
  theMessage << "Could not get the " << s << " value of parameter \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" because the get function threw an unknown exception.";
  severity(maybeabort);
}

}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Parameter.tcc"
#endif
