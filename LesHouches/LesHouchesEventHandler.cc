// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesEventHandler class.
//

#include "LesHouchesEventHandler.h"
#include "LesHouchesReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Handlers/LuminosityFunction.h"
#include "ThePEG/Utilities/LoopGuard.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesEventHandler.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

LesHouchesEventHandler::~LesHouchesEventHandler() {}

void LesHouchesEventHandler::doinit() throw(InitException) {
  PartialCollisionHandler::doinit();
  for ( int i = 0, N = readers().size(); i < N; ++i )
    readers()[i]->init();
}

void LesHouchesEventHandler::initialize() {

  if ( lumiFnPtr() ) Repository::clog()
    << "The LuminosityFunction '" << lumiFnPtr()->name()
    << "' assigned to the LesHouchesEventHandler '" << name()
    << "' will not be active in this run. Instead the incoming "
    << "particles will be determined by the used LesHouchesReader objects."
    << Exception::warning;

  typedef map<int,tLesHouchesReaderPtr> ProcessMap;
  if ( readers().empty() )
    throw LesHouchesInitError()
      << "No readers were defined for the LesHouchesEventHandler '"
      << name() << "'" << Exception::warning;

  // Go through all the readers and collect information about cross
  // sections and processes.
  CrossSection sum = 0.0*picobarn;
  CrossSection maxxsec = 0.0*picobarn;
  ProcessMap processes;
  PDPair incoming;
  for ( int i = 0, N = readers().size(); i < N; ++i ) {
    LesHouchesReader & reader = *readers()[i];

    // Check that the incoming particles are consistent between the
    // readers.
    if ( !incoming.first )
      incoming.first = getParticleData(reader.IDBMUP.first);
    if ( !incoming.second )
      incoming.second = getParticleData(reader.IDBMUP.second);
    if ( incoming.first->id() != reader.IDBMUP.first ||
	 incoming.second->id() != reader.IDBMUP.second )
      Repository::clog()
	<< "The different LesHouchesReader objects in the "
	<< "LesHouchesEventHandler '" << name() << "' have different "
	<< "types of colliding particles." << Exception::warning;

    // Check that the weighting of the events in the different readers
    // is consistent with the ones requested for this event
    // handler. Also collect the sum of the maximum weights.
    if ( reader.negativeWeights() && weightOption() > 0 )
      throw LesHouchesInitError()
	<< "The reader '" << reader.name()
	<< "' contains negatively weighted events, "
	<< "which is not allowed for the LesHouchesEventHandler '"
	<< name() << "'." << Exception::warning;
    maxxsec += reader.maxXSec();

    // Check that we do not have the same process numbers in different
    // readers.
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

  // Check that we have any cross section at all.
  if ( sum <= 0.0*picobarn )
    throw LesHouchesInitError()
      << "The sum of the cross sections of the readers in the "
      << "LesHouchesEventHandler '" << name()
      << "' was zero." << Exception::warning;

}

void LesHouchesEventHandler::doinitrun() {
  PartialCollisionHandler::doinitrun();
  NAttempted(0);
  selector().clear();

  for ( int i = 0, N = readers().size(); i < N; ++i ) {
    readers()[i]->initrun();
    if ( weightOption() == unitweight || weightOption() == unitnegweight )
      selector().insert(readers()[i]->maxXSec(), i);
    else
      selector().insert(readers()[i]->xSec(), i);
  }
}

EventPtr LesHouchesEventHandler::generateEvent() {

  LoopGuard<EventLoopException,LesHouchesEventHandler>
    loopGuard(*this, maxLoop());

  while ( true ) {
    loopGuard();

    LesHouchesReader & reader = *readers()[selector()[rnd()]];

    reader.getEvent();

  }

}

void LesHouchesEventHandler::persistentOutput(PersistentOStream & os) const {
  os << theReaders << theNAttempted << theSelector
     << theWeightOption;
}

void LesHouchesEventHandler::persistentInput(PersistentIStream & is, int) {
  is >> theReaders >> theNAttempted >> theSelector
     >> theWeightOption;
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


  static Switch<LesHouchesEventHandler,WeightOpt> interfaceWeightOption
    ("WeightOption",
     "The different ways to weight events in the Les Houches event handler. Whether weighted or not and whether or not negative weights are allowed.",
     &LesHouchesEventHandler::theWeightOption, unitweight, true, false);
  static SwitchOption interfaceWeightOptionUnitWeight
    (interfaceWeightOption,
     "UnitWeight",
     "All events have unit weight.",
     unitweight);
  static SwitchOption interfaceWeightOptionNegUnitWeight
    (interfaceWeightOption,
     "NegUnitWeight",
     "All events have weight +1 or maybe -1.",
     unitnegweight);
  static SwitchOption interfaceWeightOptionVarWeight
    (interfaceWeightOption,
     "VarWeight",
     "Events may have varying but positive weights.",
     varweight);
  static SwitchOption interfaceWeightOptionVarNegWeight
    (interfaceWeightOption,
     "VarNegWeight",
     "Events may have varying weights, both positive and negative.",
     varnegweight);

}

