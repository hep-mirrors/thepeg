// -*- C++ -*-
//
// DynamicLoader.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the DynamicLoader class.
//

#include "DynamicLoader.h"
#include "ThePEG/Utilities/StringUtils.h"
#include "ThePEG/Utilities/SystemUtils.h"
#include "ThePEG/Config/algorithm.h"
#include "config.h"

#ifdef ThePEG_HAS_DLOPEN
#include <dlfcn.h>
#endif

#include <cstdlib>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "DynamicLoader.tcc"
#endif

using namespace ThePEG;

void DynamicLoader::dlname(string sofile) {
  if ( StringUtils::suffix(sofile) == "so" ) {
    string lafile = StringUtils::remsuf(sofile) + ".la";
    ifstream is(lafile.c_str());
    string line;
    while ( getline(is, line) ) {
      if ( line.find("dlname='") != string::npos ) {
	int pos = line.find('\'') + 1;
	int l = line.rfind('\'') - pos;
	sofile = StringUtils::basename(sofile);
	versionMap[sofile] = line.substr(pos, l);
      }
    }
  } else if ( StringUtils::suffix(StringUtils::remsuf(sofile)) == "so" ) {
    versionMap[StringUtils::basename(StringUtils::remsuf(sofile))] =
      StringUtils::basename(sofile);
  }

}

string DynamicLoader::dlnameversion(string libs) {
  string ret;
  do {
    string soname = StringUtils::car(libs);
    string dir = StringUtils::dirname(soname);
    if ( dir.length() ) dir += '/';
    libs = StringUtils::cdr(libs);
    if ( versionMap.find(StringUtils::basename(soname)) != versionMap.end() )
      ret += dir + versionMap[StringUtils::basename(soname)] + " ";
    else
      ret += soname + " ";
  } while ( libs.length() );
  return StringUtils::stripws(ret);
}

bool DynamicLoader::loadcmd(string file) {
#ifdef ThePEG_HAS_DLOPEN
  dlname(file);
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
  apppaths.push_back(path);
}

void DynamicLoader::prependPath(string path) {
  if ( path[path.size()-1] != '/' ) path += '/';
  paths.insert(paths.begin(), path);
  prepaths.push_back(path);
}

bool DynamicLoader::load(string name) {
  lastErrorMessage = "";
  static set<string> loaded;
  if ( loaded.find(name) != loaded.end() ) return true;
  loaded.insert(name);
  bool success = false;
  if ( name[0] == '/' ) success = loadcmd(name);
  else {
    for ( unsigned i = 0; i < paths.size(); ++i ) {
      string path = paths[i];
      if ( path[path.size() - 1] != '/' ) path += '/';
      if ( loadcmd(path + name) ) {
	success = true;
	break;
      }
    }
  }
  if ( success || loadcmd(name) ) {
    lastErrorMessage = "";
    return true;
  }
  loaded.erase(name);
  return false;
}

const vector<string> & DynamicLoader::appendedPaths() {
  return apppaths;
}

const vector<string> & DynamicLoader::prependedPaths() {
  return prepaths;
}

const vector<string> & DynamicLoader::allPaths() {
  return paths;
}

vector<string> DynamicLoader::paths = DynamicLoader::defaultPaths();

vector<string> DynamicLoader::prepaths = vector<string>();

vector<string> DynamicLoader::apppaths = vector<string>();

string DynamicLoader::lastErrorMessage;

map<string,string> DynamicLoader::versionMap;

vector<string> DynamicLoader::defaultPaths() {
  string spaths = SystemUtils::getenv("ThePEG_PATH");
  vector<string> vpaths = StringUtils::split(spaths, ":");
  string instpath = SystemUtils::getenv("ThePEG_INSTALL_PATH");
  if ( vpaths.empty() ) {
    if ( !instpath.empty() ) vpaths.push_back(instpath);
  } else
    replace(vpaths, string("+"), instpath);
  vpaths.push_back(".");
  return vpaths;
}
