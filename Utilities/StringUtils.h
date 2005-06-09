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

  /**
   * Return the directory path part (excluding the trailing slash) of
   * the given filename, or an empty string if no directory path is
   * included
   */
  inline static string dirname(string file);

  /**
   * Return the base name of the given filename, removing the
   * directory path if present.
   */
  inline static string basename(string file);

  /**
   * Remove the trailing suffix from the given filename.
   */
  inline static string remsuf(string file);

  /**
   * Return the trailing suffix (without the dot) of the given
   * filename.
   */
  inline static string suffix(string file);

};

}

#include "StringUtils.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StringUtils.tcc"
#endif

#endif /* ThePEG_StringUtils_H */
