// -*- C++ -*-
#ifndef ThePEG_StringUtils_H
#define ThePEG_StringUtils_H
// This is the declaration of the StringUtils class.

#include "ThePEG/Config/ThePEG.h"
// #include "StringUtils.fh"
// #include "StringUtils.xh"

namespace ThePEG {

/**
 * The StringUtils class contains a few static utility functions for
 * basic strings.
 */
class StringUtils {

public:

  /**
   * A vector of strings.
   */
  typedef vector<string> StringVector;

  /**
   * Return a vector of string containing the substrings of s, defined
   * by the separating characters in ws (the ws characters are not
   * included in the substrings.
   */
  static StringVector split(string s, string ws = " \t\n");

  /**
   * Return the first substring of s, defined by the separating
   * characters in ws (the ws characters are not included in the
   * substrings.
   */
  static string car(string s, string ws = " \t\n");

  /**
   * Return s after removing the first substring, defined by the
   * separating characters in ws (the ws characters are not included
   * in the substrings.
   */
  static string cdr(string s, string ws = " \t\n");

  /**
   * Return the string \a str stripped from leading and trailing white
   * space.
   */
  static string stripws(string str);

};

}

#include "StringUtils.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StringUtils.tcc"
#endif

#endif /* ThePEG_StringUtils_H */
