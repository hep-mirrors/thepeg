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
  cfile.open(filename());
  theFile = cfile.cfile();
  if ( ( theFile = cfile.cfile() ) == NULL )
    throw LesHouchesFileError()
      << "The LesHouchesFileReader '" << name() << "' could not open the "
      << "event file called '" << theFileName << "'."
      << Exception::runerror;
}

void LesHouchesFileReader::close() {
  cfile.close();
  theFile = NULL;
}

void LesHouchesFileReader::persistentOutput(PersistentOStream & os) const {
  os << neve << theFileName;
}

void LesHouchesFileReader::persistentInput(PersistentIStream & is, int) {
  is >> neve >> theFileName;
  ieve = 0;
}

AbstractClassDescription<LesHouchesFileReader>
LesHouchesFileReader::initLesHouchesFileReader;
// Definition of the static class description member.

void LesHouchesFileReader::Init() {

  static ClassDocumentation<LesHouchesFileReader> documentation
    ("ThePEG::LesHouchesFileReader is an abstract base class to be "
      "used for objects which reads event files from matrix element "
     "generators.");

  static Parameter<LesHouchesFileReader,string> interfaceFileName
    ("FileName",
     "The name of a file containing events conforming to the Les Houches "
     "protocol to be read into ThePEG. A file name ending in "
     "<code>.gz</code> will be read from a pipe which uses "
     "<code>zcat</code>. If a file name ends in <code>|</code> the "
     "preceeding string is interpreted as a command, the output of which "
     "will be read through a pipe.",
     &LesHouchesFileReader::theFileName, "", false, false);

  interfaceFileName.fileType();
  interfaceFileName.rank(11);

}

