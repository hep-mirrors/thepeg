// -*- C++ -*-
#ifndef ThePEG_DynamicLoader_H
#define ThePEG_DynamicLoader_H
//
// This is the declaration of the <!id>DynamicLoader<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>DynamicLoader<!!id> is the general interface to the dynamic
// loader functions of the underlying operating system. Currently it
// only works on Linux.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ClassTraits.html">ClassTraits.h</a>,
// <a href="http:ClassDescription.html">ClassDescription.h</a>,
// <a href="http:DescriptionList.html">DescriptionList.h</a>,
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "DynamicLoader.fh"
// #include "DynamicLoader.xh"

namespace ThePEG {

class DynamicLoader {

public:

  static bool loadcmd(string);
  // The actual load command.

  static bool load(string file);
  // Try to load the file given as argument. If the filename does not
  // begin with a '/', try to prepend the paths one at the time until
  // success.  If all fail try without prepending a path. If nothing
  // works, return false.

  static void appendPath(string);
  // Add a path to the list of directories to seach for dynaically
  // linkable libraries.

  static void prependPath(string);
  // Add a path to the list of directories to seach for dynaically
  // linkable libraries.

  static string lastErrorMessage;

private:

  static vector<string> paths;
  // The list of directories to seach for dynaically linkable
  // libraries.

  static vector<string> defaultPaths();
  // Used to initialize the paths vector from the ThePEG_PATH
  // environment.

};

}

#include "DynamicLoader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DynamicLoader.tcc"
#endif

#endif /* ThePEG_DynamicLoader_H */
