// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DynamicLoader class.
//

#include "DynamicLoader.h"
#include "ThePEG/Utilities/StringUtils.h"
#include "ThePEG/Utilities/SystemUtils.h"
#include "ThePEG/Config/algorithm.h"

#ifdef ThePEG_HAS_DLOPEN
#include <dlfcn.h>
#endif

#include <cstdlib>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DynamicLoader.tcc"
#endif

using namespace ThePEG;

bool DynamicLoader::loadcmd(string file) {
#ifdef ThePEG_HAS_DLOPEN
  bool ret = dlopen(file.c_str(), RTLD_LAZY|RTLD_GLOBAL) != 0;
  if ( !ret ) lastErrorMessage += string(dlerror()) + string("\n");
  return ret;
#else
#error ThePEG can only be run on platforms which supports
#error dynamic loading.
  return false;
#endif
}

void DynamicLoader::appendPath(string path) {
  if ( path[path.size()-1] != '/' ) path += '/';
  paths.push_back(path);
}

void DynamicLoader::prependPath(string path) {
  if ( path[path.size()-1] != '/' ) path += '/';
  paths.insert(paths.begin(), path);
}

bool DynamicLoader::load(string name) {
  lastErrorMessage = "";
  static set<string> loaded;
  if ( loaded.find(name) != loaded.end() ) return true;
  loaded.insert(name);
  bool success = false;
  if ( name[0] == '/' ) success = loadcmd(name);
  else {
    for ( unsigned i = 0; i < paths.size(); ++i )
      if ( loadcmd(paths[i] + name) ) {
	success = true;
	break;
      }
  }
  if ( success || loadcmd(name) ) return true;
  loaded.erase(name);
  return false;
}

vector<string> DynamicLoader::paths = DynamicLoader::defaultPaths();

string DynamicLoader::lastErrorMessage;

vector<string> DynamicLoader::defaultPaths() {
  string spaths = SystemUtils::getenv("ThePEG_PATH");
  vector<string> vpaths = StringUtils::split(spaths, ":");
  string instpath = SystemUtils::getenv("ThePEG_INSTALL_PATH");
  if ( instpath.empty() ) instpath = "../lib";
  if ( vpaths.empty() ) vpaths.push_back(instpath);
  else replace(vpaths, string("+"), instpath);
  return vpaths;
}
