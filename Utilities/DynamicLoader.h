// -*- C++ -*-
#ifndef ThePEG_DynamicLoader_H
#define ThePEG_DynamicLoader_H
// This is the declaration of the DynamicLoader class.

#include "ThePEG/Config/ThePEG.h"
// #include "DynamicLoader.fh"
// #include "DynamicLoader.xh"

namespace ThePEG {

/**
 * <code>DynamicLoader</code> is the general interface to the dynamic
 * loader functions of the underlying operating system. Currently it
 * only works on Linux.
 *
 * @see ClassTraits,
 * @see ClassDescription,
 * @see DescriptionList,
 * @see PersistentIStream.
 */
class DynamicLoader {

public:

  /**
   * The actual load command used on the current platform.
   */
  static bool loadcmd(string);

  /**
   * Try to load the file given as argument. If the filename does not
   * begin with a '/', try to prepend the paths one at the time until
   * success.  If all fail try without prepending a path.
   * @return true if the loading succeeded, false otherwise.
   */
  static bool load(string file);

  /**
   * Add a path to the bottom of the list of directories to seach for
   * dynaically linkable libraries.
   */
  static void appendPath(string);

  /**
   * Add a path to the top of the list of directories to seach for
   * dynaically linkable libraries.
   */
  static void prependPath(string);

  /**
   * Return the last error message issued from the platforms loader.
   */
  static string lastErrorMessage;

private:

  /**
   * The list of directories to seach for dynaically linkable
   * libraries.
   */
  static vector<string> paths;

  /**
   * Used to initialize the paths vector from the ThePEG_PATH
   * environment.
   */
  static vector<string> defaultPaths();

};

}

#include "DynamicLoader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DynamicLoader.tcc"
#endif

#endif /* ThePEG_DynamicLoader_H */
