// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Exception class.
//

#include "Exception.h"
#include <iostream>
#include <cstdlib>
#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/Repository/CurrentGenerator.h"
#include "ThePEG/EventRecord/Event.h"

void breakThePEG() {
  return;
}

extern "C" {
  void debugThePEG(const ThePEG::Interfaced * i) {
    i->debug();
  }

  void debugEvent() {
    using namespace ThePEG;
    if ( !CurrentGenerator::isVoid() &&
	 CurrentGenerator::current().currentEvent() )
      cerr << *CurrentGenerator::current().currentEvent();
  }

}

namespace ThePEG {

Veto::Veto() {
  if ( ThePEG_DEBUG_LEVEL ) breakThePEG();
}

Exception::Exception(const string & newMessage, Severity newSeverity)
  : theMessage(newMessage), handled(false), theSeverity(newSeverity) {
  breakThePEG();
  if ( theSeverity == abortnow ) {
    writeMessage();
    abort();
  }
}

Exception::~Exception() throw() {
  if ( !handled ) {
    writeMessage();
    if ( theSeverity == maybeabort ) abort();
  }
}

void Exception::severity(Severity newSeverity) {
  theSeverity = newSeverity;
  if ( theSeverity == abortnow ) {
    writeMessage(cerr);
    abort();
  }
}

void Exception::writeMessage(ostream & os) const {
  switch ( severity() ) {
  case unknown:
    os << "unknown error type: ";
    break;
  case info:
    os << "Informational exception: ";
    break;
  case warning:
    os << "Warning: ";
    break;
  case eventerror:
  case runerror:
  case maybeabort:
  case abortnow:
    os << "Error: ";
    break;
  }
  os << message() << endl;
  switch ( severity() ) {
  case eventerror:
    os << "The generated event will be discarded." << endl;
    break;
  case runerror:
    os << "This run will be aborted." << endl;
    break;
  case maybeabort:
  case abortnow:
    os << "The program will now abort and dump core." << endl;
    break;
  case unknown:
  case info:
  case warning:
    break;
  }
}

ostream * Exception::errstream = &cerr;

}

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Exception.tcc"
#endif

