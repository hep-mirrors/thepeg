// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesFileReader class.
//

#include "LesHouchesFileReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesFileReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

LesHouchesFileReader::~LesHouchesFileReader() {}

void LesHouchesFileReader::open() {
  if ( theFile != NULL ) close();
  if ( isGZipped || theFileName.substr(theFileName.length()-3,3) == ".gz" ) {
    string cmd = string(ThePEG_GZREAD_FILE) + " " + theFileName;
    theFile = popen(cmd.c_str(), "r");
    isPipe = true;
  } else {
    theFile = std::fopen(theFileName.c_str(), "r");
    isPipe = false;
  }
  if ( theFile == NULL )
    throw LesHouchesFileError()
      << "The LesHouchesFileReader '" << name() << "' could not open the "
      << "event file called '" << theFileName << "'."
      << Exception::runerror;
}

void LesHouchesFileReader::close() {
  if ( theFile == NULL ) return;
  if ( isPipe ) pclose(theFile);
  else fclose(theFile);
  theFile = NULL;
}

void LesHouchesFileReader::persistentOutput(PersistentOStream & os) const {
  os << theFileName << isGZipped;
}

void LesHouchesFileReader::persistentInput(PersistentIStream & is, int) {
  is >> theFileName >> isGZipped;
  isPipe = false;
}

AbstractClassDescription<LesHouchesFileReader>
LesHouchesFileReader::initLesHouchesFileReader;
// Definition of the static class description member.

void LesHouchesFileReader::Init() {

  static ClassDocumentation<LesHouchesFileReader> documentation
    ("\\classname{LesHouchesFileReader} is an abstract base class to be "
      "used for objects which reads event files from matrix element "
     "generators.");

  static Parameter<LesHouchesFileReader,string> interfaceFileName
    ("FileName",
     "The name of a file containing events to be read into ThePEG",
     &LesHouchesFileReader::theFileName, "", "", "", false, false, false);

}

