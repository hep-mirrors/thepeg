// -*- C++ -*-
#ifndef ThePEG_Debug_H
#define ThePEG_Debug_H
//
// This is the declaration of the <!id>Debug<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Debug<!!id> class defines a number of debug levels and a
// static public member giving the current debug level in a run.
//

#include <vector>

namespace ThePEG {

class Debug {

public:

  enum Levels {
    noDebug = 0,
    printSomeEvents = 1,
    printEveryEvent = 5,
    full = 9 };
  // The different levels.

  static int level;
  // The current level.

  static std::vector<bool> debugItems;

  static void debugItem(int item, bool on);
  static void setDebug(int ilev);

  inline static bool debugItem(int item);

  static void unmaskFpuErrors();
  static void unmaskFpuOverflow();
  static void unmaskFpuUnderflow();
  static void unmaskFpuDivZero();
  static void unmaskFpuDenorm();
  static void unmaskFpuInvalid();
  static void maskFpuErrors();
  static void maskFpuOverflow();
  static void maskFpuUnderflow();
  static void maskFpuDivZero();
  static void maskFpuDenorm();
  static void maskFpuInvalid();
  // Manipulate handling of floating point signals.

};

}

#include "Debug.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Debug.tcc"
#endif

#endif /* ThePEG_Debug_H */
