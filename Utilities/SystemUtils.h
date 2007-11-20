// -*- C++ -*-
//
// SystemUtils.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_SystemUtils_H
#define ThePEG_SystemUtils_H
// This is the declaration of the SystemUtils class.

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

/**
 * The SystemUtils class contains a few static utility functions for
 * system calls.
 */
class SystemUtils {

public:

  /**
   * Simple interface to std::getenv with string argument.
   * Non-existent environment variables will result in a zero-length
   * string.
   */
  static string getenv(string e)
  {
    const char * cp = std::getenv(e.c_str());
    return cp? cp: "";
  }

};

}

#endif /* ThePEG_SystemUtils_H */
