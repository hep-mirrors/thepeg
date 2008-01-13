// -*- C++ -*-
//
// setupThePEG.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Exception.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/SystemUtils.h"
#include <fstream>

int main(int argc, char * argv[]) {
  using namespace ThePEG;

  Debug::level = 1;
  string repo =
    SystemUtils::getenv("ThePEG_INSTALL_PATH") + "/ThePEGDefaults.rpo";
  string repout;
  string file;
  bool init = false;

  for ( int iarg = 1; iarg < argc; ++iarg ) {
    string arg = argv[iarg];
    if ( arg == "-d" ) Debug::setDebug(atoi(argv[++iarg]));
    else if ( arg.substr(0,2) == "-d" )
      Debug::setDebug(atoi(arg.substr(2).c_str()));
    else if ( arg == "-r" ) repo = argv[++iarg];
    else if ( arg == "-o" ) repout = argv[++iarg];
    else if ( arg == "--init" || arg == "-init" ) {
      init = true;
      Debug::level = 0;
    }
    else if ( arg == "--exitonerror" ) Repository::exitOnError() = 1;
    else if ( arg == "-s" ) {
      DynamicLoader::load(argv[++iarg]);
      Repository::globalLibraries().push_back(argv[iarg]);
    }
    else if ( arg.substr(0,2) == "-s" ) {
      DynamicLoader::load(arg.substr(2));
      Repository::globalLibraries().push_back(arg.substr(2));
    }
    else if ( arg == "-l" ) DynamicLoader::appendPath(argv[++iarg]);
    else if ( arg.substr(0,2) == "-l" )
      DynamicLoader::appendPath(arg.substr(2));
    else if ( arg == "-L" ) DynamicLoader::prependPath(argv[++iarg]);
    else if ( arg.substr(0,2) == "-L" )
      DynamicLoader::prependPath(arg.substr(2));
    else if ( arg == "-h" || arg == "--help" ) {
      cerr << "Usage: " << argv[0]
	 << " {cmdfile} [-d {debuglevel|-debugitem}] [-r input-repository-file]"
	 << " [-l load-path] [-L first-load-path]" << endl;
      return 3;
    }
    else
      file = arg;
  }

  if ( Debug::level ) Debug::unmaskFpuErrors();

  try {

    if ( init ) {
      breakThePEG();
      if ( repout.empty() ) repout = repo;
      else Repository::load(repo);
      {
	HoldFlag<> setup(InterfaceBase::NoReadOnly);
	if ( file.empty() ) file = "ThePEGDefaults.in";
	ifstream is(file.c_str());
	Repository::read(is, cout);
	Repository::update();
      }
      Repository::save(repout);
    } else {
      Repository::load(repo);
      breakThePEG();
      if ( file.size() && file != "-" ) {
	if ( file == "--java" || file == "-java" )
	  Repository::read(cin, cout, "-*-ready-*-\n");
	else {
	  ifstream is(file.c_str());
	  Repository::read(is, cout);
	}
      } else {
	Repository::read(cin, cout, "ThePEG> ");
      }
    }
  }
  catch ( Exception & e ) {
    cerr << "Unexpected exception caught: " << e.what() << endl;
    e.handle();
    return 1;
  }
  catch ( std::exception & e ) {
    cerr << "Unexpected exception caught: " << e.what() << endl;
    return 1;
  }
  catch ( ... ) {
    cerr << "Unknown Exception\n";
    return 2;
  }

  return 0;
}

