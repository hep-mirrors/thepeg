// -*- C++ -*-
#ifndef ThePEG_SystemUtils_H
#define ThePEG_SystemUtils_H
// This is the declaration of the SystemUtils class.

#include "ThePEG/Config/ThePEG.h"
// #include "SystemUtils.fh"
// #include "SystemUtils.xh"

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
  inline static string getenv(string);

};

}

#include "SystemUtils.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SystemUtils.tcc"
#endif

#endif /* ThePEG_SystemUtils_H */
