// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ParVectorBase class.
//

#include "InterfacedBase.h"
#include "ParVector.h"
#include "ParVector.xh"

namespace ThePEG {

string ParVectorBase::
exec(InterfacedBase & i, string action, string arguments) const
  throw(InterfaceException) {
  istringstream arg(arguments.c_str());
  int place = 0;
  if ( !(arg >> place) ) place = -1;
  ostringstream ret;
  if ( action == "get" ) {
    StringVector v = get(i);
    if ( place >= 0 ) return v[place];
    for ( StringVector::const_iterator it = v.begin(); it != v.end(); ++it ) {
      if ( it != v.begin() ) ret << ", ";
      ret << *it;
    }
  } else if ( action == "erase" ) {
    erase(i, place);
  } else if ( action == "min" ) {
    return minimum(i, place);
  } else if ( action == "max" ) {
    return maximum(i, place);
  } else if ( action == "def" ) {
    return def(i, place);
  } else if ( action == "setdef" ) {
    setDef(i, place);
  } else if ( action == "set" || action == "insert" ) {
    string val;
    arg >> val;
    if ( action == "set" ) set(i, val, place);
    else insert(i, val, place);
  } else
    throw InterExUnknown(*this, i);
  return ret.str();
}

string ParVectorBase::fullDescription(const InterfacedBase & ib) const {
  ostringstream os;
  StringVector vals = get(ib);
  os << InterfaceBase::fullDescription(ib)
     << size() << "\n" << vals.size() << "\n";
  for ( int i = 0, N = vals.size(); i < N; ++i ) {
    string min = minimum(ib, i);
    if ( min.empty() ) min = "-inf";
    string max = maximum(ib, i);
    if ( max.empty() ) max = "inf";
    os << vals[i] << "\n"
       << min << "\n"
       << def(ib, i) << "\n"
       << max << "\n";
  }
  return os.str();
}


ParVExIndex::ParVExIndex(const InterfaceBase & i, const InterfacedBase & o,
			 int j) {
  theMessage << "Could not access element " << j
	     << " of the parameter vector \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the index was outside of the allowed range.";
  severity(maybeabort);
}

ParVExFixed::ParVExFixed(const InterfaceBase & i, const InterfacedBase & o) {
  theMessage << "Cannot insert or delete in the parameter vector \""
	     << i.name() << "\" for the object \"" << o.name()
	     << "\" since the vector is of fixed size.";
  severity(maybeabort);
}

ParVExDelUnknown::ParVExDelUnknown(const InterfaceBase & i,
				   const InterfacedBase & o, int j) {
  theMessage << "Could not delete the value at position " << j
	     << " from the parameter vector \"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the delete function threw an unknown exception.";
  severity(maybeabort);
}

ParVExGetUnknown::ParVExGetUnknown(const InterfaceBase & i,
				   const InterfacedBase & o, const char * s) {
  theMessage << "Could not get the " << s
	     << " values from the parameter vector\"" << i.name()
	     << "\" for the object \"" << o.name()
	     << "\" because the get function threw an unknown exception.";
  severity(maybeabort);
}

}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "ParVector.tcc"
#endif

