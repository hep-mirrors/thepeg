// -*- C++ -*-
#ifndef ThePEG_SystemUtils_H
#define ThePEG_SystemUtils_H
//
// This is the declaration of the <!id>SystemUtils<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The id>SystemUtils<!!id> class contains a few static utility
// functions for system calls.
//
//

#include "ThePEG/Config/ThePEG.h"
// #include "SystemUtils.fh"
// #include "SystemUtils.xh"

namespace ThePEG {

class SystemUtils {

public:

  inline static string getenv(string);
  // Simply interface to std::getenv with string argument. Also
  // non-existent environment variables will result in a zero-length
  // string.

};

}

#include "SystemUtils.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SystemUtils.tcc"
#endif

#endif /* ThePEG_SystemUtils_H */
