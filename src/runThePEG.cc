#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/PDT/PYDECYDummy.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Timer.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/Exception.h"
#include "ThePEG/Repository/Main.h"

int main(int argc, char * argv[]) {
  using namespace ThePEG;

  string run;
  long N = -1;
  long seed = 0;
  string mainclass;

  for ( int iarg = 1; iarg < argc; ++iarg ) {
    string arg = argv[iarg];
    if ( arg == "-r" ) run = argv[++iarg];
    else if ( arg == "-x" ) mainclass = argv[++iarg];
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
    else if ( arg == "-seed" ) seed = atoi(argv[++iarg]);
    else if ( arg == "-h" ) {
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

    PersistentIStream is(run);
    EGPtr eg;
    is >> eg;

    MainTimer timer(".runThePEG.timer." + run);

    breakThePEG();

    if ( !mainclass.empty() ) {
      if ( eg ) eg->initialize();
      Main::eventGenerator(eg);
      vector<string> args;
      for ( int iarg = 1; iarg < argc; ++iarg ) args.push_back(argv[iarg]);
      Main::arguments(args);
      Main::N(N);
      if ( !DynamicLoader::load(mainclass) )
	std::cout << "Main class file '" << mainclass << "' not found." << endl;
      else if ( eg ) eg->finish();
    } else if ( eg ) {
      if ( seed > 0 ) eg->setSeed(seed);
      eg->go(1, N);
    } else std::cout << "eg = nil" << endl;

  }
  catch ( std::exception & e ) {
    cerr << e.what() << endl;
    return 1;
  }
  catch ( ... ) {
    breakThePEG();
    cerr << "Unknown Exception\n";
    return 2;
  }

  return 0;
}

