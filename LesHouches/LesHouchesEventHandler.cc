// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesEventHandler class.
//

#include "LesHouchesEventHandler.h"
#include "LesHouchesReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Repository/Repository.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesEventHandler.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

LesHouchesEventHandler::~LesHouchesEventHandler() {}

void LesHouchesEventHandler::doinit() throw(InitException) {
  typedef map<int,tLesHouchesReaderPtr> ProcessMap;
  PartialCollisionHandler::doinit();
  if ( readers().empty() )
    throw LesHouchesInitError()
      << "No readers were defined for the LesHouchesEventHandler '"
      << name() << "'" << Exception::warning;

  // Go through all the readers and collect information about cross
  // sections and processes.
  CrossSection sum = 0.0*picobarn;
  ProcessMap processes;
  for ( int i = 0, N = readers().size(); i < N; ++i ) {
    LesHouchesReader & reader = *readers()[i];
    reader.scan();
    for ( int ip = 0; ip < reader.NRUP; ++ip ) {
      sum += reader.XSECUP[ip]*picobarn;
      if ( reader.LPRUP[ip] ) {
	ProcessMap::iterator pit = processes.find(reader.LPRUP[ip]);
	if ( pit == processes.end() )
	  processes[reader.LPRUP[ip]] = readers()[i];
	else
	  Repository::clog()
	    << "Warning: In the LesHouchesEventHandler '"
	    << name() << "', both the '" << pit->second->name() << "' and '"
	    << reader.name() << "' contains sub-process number " << pit->first
	    << ". This process may be double-counted in this run." << endl;
      }
    }
  }
  if ( sum <= 0.0*picobarn )
    throw LesHouchesInitError()
      << "The sum of the cross sections of the readers in the "
      << "LesHouchesEventHandler '" << name()
      << "' was zero." << Exception::warning;
}

void LesHouchesEventHandler::initialize() {
}

void LesHouchesEventHandler::persistentOutput(PersistentOStream & os) const {
  os << theReaders;
}

void LesHouchesEventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theReaders;
}

ClassDescription<LesHouchesEventHandler>
LesHouchesEventHandler::initLesHouchesEventHandler;
// Definition of the static class description member.

void LesHouchesEventHandler::Init() {

  static ClassDocumentation<LesHouchesEventHandler> documentation
    ("There is no documentation for the LesHouchesEventHandler class");


  static RefVector<LesHouchesEventHandler,LesHouchesReader>
    interfaceLesHoushesReaders
    ("LesHoushesReaders",
     "Objects capable of reading events from an event file or an "
     "external matrix element generator.",
     &LesHouchesEventHandler::theReaders, -1, false, false, true, false, false);

}

