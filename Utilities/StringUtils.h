// -*- C++ -*-
#ifndef ThePEG_StringUtils_H
#define ThePEG_StringUtils_H
//
// This is the declaration of the <!id>StringUtils<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The id>StringUtils<!!id> class contains a few static utility
// functions for basic strings.
//
// 

#include "ThePEG/Config/ThePEG.h"
// #include "StringUtils.fh"
// #include "StringUtils.xh"

namespace ThePEG {

class StringUtils {

public:

  typedef vector<string> StringVector;

  static StringVector split(string s, string ws = " \t\n");
  // Return a vector of string containing the substrings of 's'
  // defined by the separating characters in 'ws'.

  static string car(string s, string ws = " \t\n");
  // Return the first substring of 's'.

  static string cdr(string s, string ws = " \t\n");
  // Return 's' after removing the first substring (and possible 'ws'
  // characters').

};

}

#include "StringUtils.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StringUtils.tcc"
#endif

#endif /* ThePEG_StringUtils_H */
