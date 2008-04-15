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

int main(int argc, char * argv[]) {
  using namespace ThePEG;

  Debug::level = 1;
  string repo =
    SystemUtils::getenv("ThePEG_INSTALL_PATH") + "/ThePEGDefaults.rpo";
  string repout;
  string file;
  bool init = false;

  Repository repository;

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
    else if ( arg == "--exitonerror" ) repository.exitOnError() = 1;
    else if ( arg == "-s" ) {
      DynamicLoader::load(argv[++iarg]);
      repository.globalLibraries().push_back(argv[iarg]);
    }
    else if ( arg.substr(0,2) == "-s" ) {
      DynamicLoader::load(arg.substr(2));
      repository.globalLibraries().push_back(arg.substr(2));
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
      else repository.load(repo);
      {
	HoldFlag<> setup(InterfaceBase::NoReadOnly);
	if ( file.empty() ) file = "ThePEGDefaults.in";
	repository.read(file, cout);
	repository.update();
      }
      repository.save(repout);
    } else {
      repository.load(repo);
      breakThePEG();
      if ( file.size() && file != "-" ) {
	if ( file == "--java" || file == "-java" )
	  repository.read(cin, cout, "-*-ready-*-\n");
	else {
	  repository.read(file, cout);
	}
      } else {
	repository.read(cin, cout, "ThePEG> ");
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

