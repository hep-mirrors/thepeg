// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StringUtils class.
//

#include "StringUtils.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StringUtils.tcc"
#endif


using namespace ThePEG;


StringUtils::StringVector StringUtils::split(string s, string ws) {
  StringVector r;
  string::size_type i = s.find_first_not_of(ws);
  while ( i != string::npos ) {
    s = s.substr(i);
    i = s.find_first_of(ws);
    r.push_back(s.substr(0, i));
    if ( i == string::npos ) return r;
    s = s.substr(i);
    i = s.find_first_not_of(ws);
  }
  return r;
}

string StringUtils::car(string s, string ws) {
  string::size_type p = s.find_first_not_of(ws);
  if ( p == string::npos ) return "";
  s = s.substr(p);
  return s.substr(0, s.find_first_of(ws));
}

string StringUtils::cdr(string s, string ws) {
  string::size_type p = s.find_first_not_of(ws);
  if ( p == string::npos ) return "";
  s = s.substr(p);
  p = s.find_first_of(ws);
  if ( p == string::npos ) return "";
  s = s.substr(p);
  p = s.find_first_not_of(ws);
  if ( p == string::npos ) return "";
  return s.substr(p);
}

