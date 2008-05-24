// -*- C++ -*-
//
// MultiEventGenerator.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultiEventGenerator class.
//

#include "MultiEventGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Command.h"
#include "ThePEG/Repository/BaseRepository.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Config/algorithm.h"
#include "ThePEG/Utilities/StringUtils.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/Repository/CurrentGenerator.h"
#include <ctime>


#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultiEventGenerator.tcc"
#endif

using namespace ThePEG;

MultiEventGenerator::~MultiEventGenerator() {}

string MultiEventGenerator::removeInterface(string cmd) {
  string noun = StringUtils::car(cmd);
  IBPtr ip = BaseRepository::getObjectFromNoun(noun);
  const InterfaceBase * ifb = BaseRepository::
    FindInterface(ip, BaseRepository::getInterfaceFromNoun(noun));
  string posarg = BaseRepository::getPosArgFromNoun(noun);

  for ( string::size_type i = 0; i < theObjects.size(); ++i ) {
    if ( theObjects[i] == ip && theInterfaces[i] == ifb->name() &&
	 thePosArgs[i] == posarg ) {
      theObjects.erase(theObjects.begin() + i);
      theInterfaces.erase(theInterfaces.begin() + i);
      thePosArgs.erase(thePosArgs.begin() + i);
      theValues.erase(theValues.begin() + i);
      return "";
    }
  }
  return "No such object/interface defined for this MultiEventGenerator.";
}

string MultiEventGenerator::addInterface(string cmd) {
  breakThePEG();
  string noun = StringUtils::car(cmd);
  IBPtr ip = BaseRepository::getObjectFromNoun(noun);
  const InterfaceBase * ifb = BaseRepository::
    FindInterface(ip, BaseRepository::getInterfaceFromNoun(noun));
  string posarg = BaseRepository::getPosArgFromNoun(noun);
  cmd = StringUtils::cdr(cmd);
  if ( cmd.empty() ) return "Error: empty argument list.";
  StringVector args;
  do {
    args.push_back(StringUtils::car(cmd, ","));
    cmd = StringUtils::cdr(cmd, ",");
  } while ( !cmd.empty() );

  string ret;
  string oldvalue = ifb->exec(*ip, "get", posarg);
  try {
    for ( string::size_type i = 0; i < args.size(); ++i )
      ifb->exec(*ip, "set", args[i]);
  }
  catch (const Exception & e) {
    e.handle();
    ret = "Error: " + e.message();
  }
  ifb->exec(*ip, "set", posarg + " " + oldvalue);
  if ( !ret.empty() ) return ret;

  for ( string::size_type i = 0; i < theObjects.size(); ++i ) {
    if ( theObjects[i] == ip && theInterfaces[i] == ifb->name() &&
	 thePosArgs[i] == posarg ) {
      theValues[i].insert(theValues[i].end(), args.begin(), args.end());
      return "";
    }
  }

  theObjects.push_back(ip);
  theInterfaces.push_back(ifb->name());
  thePosArgs.push_back(posarg);
  theValues.push_back(args);
  return "";
}

void MultiEventGenerator::doGo(long next, long maxevent, bool tics) {

  if ( theObjects.empty() || next < 0 ) {
    EventGenerator::doGo(next, maxevent, tics);
    return;
  }

  if ( maxevent >= 0 ) N(maxevent);

  vector<const InterfaceBase *> interfaces;
  long nargs = 1;
  for ( string::size_type i = 0; i < theObjects.size(); ++i ) {
    nargs *= theValues[i].size();
    interfaces.push_back(BaseRepository::FindInterface(theObjects[i],
						       theInterfaces[i]));
  }

  openOutputFiles();

  string baseName = runName();

  if ( tics ) tic(next - 1, nargs*N());
  for ( long iargs = 0; iargs < nargs; ++iargs ) {

    ostringstream subname;
    subname << baseName << ":" << iargs + 1;
    runName(subname.str());

    long div = 1;
    if ( iargs > 0 ) {
      log() << endl;
      out() << endl;
    }
    log() << baseName << " sub-run number " << iargs + 1 << endl;
    out() << baseName << " sub-run number " << iargs + 1
	  << " using the following interface values:" << endl;

    for ( string::size_type i = 0; i < theObjects.size(); ++i ) {
      long iarg = (iargs/div)%theValues[i].size();
      interfaces[i]->exec(*theObjects[i], "set",
			  thePosArgs[i] + " " + theValues[i][iarg]);
      out() << "   set " << theObjects[i]->name() << ":" << theInterfaces[i];
      if ( !thePosArgs[i].empty() ) out() << "[" << thePosArgs[i] << "]";

      out() << " " << theValues[i][iarg] << endl;
      div *= theValues[i].size();
    }

    reset();
    for_each(objects(), mem_fun(&InterfacedBase::reset));
    
    init();
    initrun();

    ieve = next-1;

    try {
      while ( shoot() ) {
	if ( tics ) tic(ieve + iargs*N(), nargs*N());
      }
    }
    catch ( ... ) {
      finish();
      throw;
    }
   finish();

 }

  runName(baseName);

  finally();

}

void MultiEventGenerator::persistentOutput(PersistentOStream & os) const {
  os << theObjects << theInterfaces << thePosArgs << theValues;
}

void MultiEventGenerator::persistentInput(PersistentIStream & is, int) {
  is >> theObjects >> theInterfaces >> thePosArgs >> theValues;
}

void MultiEventGenerator::rebind(const TranslationMap & trans)
  throw(RebindException) {
  for ( string::size_type i = 0; i < theObjects.size(); ++i )
    theObjects[i] = trans.translate(theObjects[i]);
  EventGenerator::rebind(trans);
}

ClassDescription<MultiEventGenerator>
MultiEventGenerator::initMultiEventGenerator;
// Definition of the static class description member.

void MultiEventGenerator::Init() {

  static ClassDocumentation<MultiEventGenerator> documentation
    ("The ThePEG::MultiEventGenerator class is derived from the "
     "ThePEG::EventGenerator and is capable of making "
     "several runs with a pre-defined set of parameter and switch values.");

  static Command<MultiEventGenerator> interfaceAddInterface
    ("AddInterface",
     "If arguments are given on the form 'object-name:interface-name arg1, "
     "arg2, arg3' or 'object-name:vectorinterface-name[pos] arg1, arg2, arg3' "
     "the generator will be run three times with the corresonding interface of "
     "the given object set to arg1, arg2, arg3 in each run respectively. If "
     "another interface with e.g. 4 different arguments, the generator will "
     "be run 12 times once for each combination of arguments. If called with "
     "an object and interface wich has already been given in a previous call, "
     "the new arguments will be added to the previously specified list without "
     "checking if any argument is doubled.",
     &MultiEventGenerator::addInterface);

  static Command<MultiEventGenerator> interfaceRemoveInterface
    ("RemoveInterface",
     "If arguments are given on the form 'object-name:interface-name' and "
     "the same interface and object was previously with an "
     "\\interface{AddInterface}, the corresponding arguments are removed "
     "and the interfaced will be left unchanged during the generation.",
     &MultiEventGenerator::removeInterface);

  interfaceAddInterface.rank(10.7);
  interfaceRemoveInterface.rank(10.5);

}

