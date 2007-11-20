// -*- C++ -*-
//
// runThePEG.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/Exception.h"
#include "ThePEG/Repository/Main.h"

int main(int argc, char * argv[]) {
  using namespace ThePEG;

  string run;
  long N = -1;
  long seed = 0;
  string mainclass;
  bool tics = false;

  for ( int iarg = 1; iarg < argc; ++iarg ) {
    string arg = argv[iarg];
    if ( arg == "-r" ) run = argv[++iarg];
    else if ( arg == "-x" ) mainclass = argv[++iarg];
    else if ( arg == "-s" ) DynamicLoader::load(argv[++iarg]);
    else if ( arg.substr(0,2) == "-s" )
      DynamicLoader::load(arg.substr(2));
    else if ( arg == "-l" ) DynamicLoader::appendPath(argv[++iarg]);
    else if ( arg.substr(0,2) == "-l" )
      DynamicLoader::appendPath(arg.substr(2));
    else if ( arg == "-L" ) DynamicLoader::prependPath(argv[++iarg]);
    else if ( arg.substr(0,2) == "-L" )
      DynamicLoader::prependPath(arg.substr(2));
    else if ( arg == "-d" ) Debug::setDebug(atoi(argv[++iarg]));
    else if ( arg.substr(0,2) == "-d" )
      Debug::setDebug(atoi(arg.substr(2).c_str()));
    else if ( arg == "-N" ) N = atoi(argv[++iarg]);
    else if ( arg.substr(0,2) == "-N" ) N = atoi(arg.substr(2).c_str());
    else if ( arg == "--seed" || arg == "-seed" ) seed = atoi(argv[++iarg]);
    else if ( arg == "--tics" || arg == "-tics" ) tics = true;
    else if ( arg == "--help" || arg == "-h" ) {
    cerr << "Usage: " << argv[0] << " [-d {debuglevel|-debugitem}] "
	 << "[-l load-path] [-L first-load-path] run-file" << endl;
      return 3;
    }
    else
      run = arg;
  }

  if ( Debug::level ) Debug::unmaskFpuErrors();

  if ( run.empty() ) {
    cerr << "No run-file specified." << endl;
    return 1;
  }

  try {

    EGPtr eg;
    if ( run == "-" ) {
      PersistentIStream is(cin);
      is >> eg;
    } else {
      PersistentIStream is(run);
      is >> eg;
    }

    breakThePEG();

    if ( !eg ) {
      std::cout << "eg = nil" << endl;
      return 1;
    }

    if ( seed > 0 ) eg->setSeed(seed);
    if ( !mainclass.empty() ) {
      Main::arguments(vector<string>(argv + 1, argv + argc));
      Main::N(N);
      if ( !eg->loadMain(mainclass) )
	std::cout << "Main class file '" << mainclass << "' not found." << endl;
    } else {
      eg->go(1, N, tics);
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
    breakThePEG();
    cerr << "Unknown Exception\n";
    return 2;
  }

  return 0;
}

