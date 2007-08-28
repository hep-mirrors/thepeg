// -*- C++ -*-
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
