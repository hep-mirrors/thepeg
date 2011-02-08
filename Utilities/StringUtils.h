// -*- C++ -*-
//
// StringUtils.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_StringUtils_H
#define ThePEG_StringUtils_H
// This is the declaration of the StringUtils class.

#include "ThePEG/Config/ThePEG.h"

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
  static StringVector split(string s, string ws = " \t\r\n");

  /**
   * Return the first substring of s, defined by the separating
   * characters in ws (the ws characters are not included in the
   * substrings.
   */
  static string car(string s, string ws = " \t\r\n");

  /**
   * Return s after removing the first substring, defined by the
   * separating characters in ws (the ws characters are not included
   * in the substrings.
   */
  static string cdr(string s, string ws = " \t\r\n");

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
  static string dirname(string file);

  /**
   * Return the base name of the given filename, removing the
   * directory path if present.
   */
  static string basename(string file);

  /**
   * Remove the trailing suffix from the given filename.
   */
  static string remsuf(string file);

  /**
   * Return the trailing suffix (without the dot) of the given
   * filename.
   */
  static string suffix(string file);

  /**
   * Assuming the \a line contains a valid XML \a tag, scan the \a
   * line for attributes belonging to this \a tag and return a map of
   * name-value pairs. Oprionally only look from position \a curr in
   * the \a line.
   */
  static map<string,string> xmlAttributes(string tag, string line,
				       string::size_type curr = 0);

  /**
   * Convenient typdef.
   */
  typedef string::size_type pos_t;

  /**
   * Convenient alias for npos.
   */
  static const pos_t end = string::npos;
  

};

}

#endif /* ThePEG_StringUtils_H */
