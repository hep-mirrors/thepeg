// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MadGraphReader class.
//

#include "MadGraphReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MadGraphReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

void MadGraphReader::open() {
  LesHouchesFileReader::open();

  char cline[1024];
  double xsec = -1.0;
  double maxw = -1.0;
  long neve = 0;
  double ebeam1 = -1.0;
  double ebeam2 = -1.0;
  int lpp1 = 0;
  int lpp2 = 0;
  string pdftag;

  while ( fgetc(theFile) == '#' ) {
    if ( fgets(cline, 1024, theFile) == NULL )
      throw LesHouchesFileError()
	<< "An error occurred while '" << name() << "' was reading the file '"
	<< filename() << "'." << Exception::runerror;
    string line(cline);
    line = line.substr(0, line.find('\n'));
    istringstream is(line);
    if ( line.find("Number of events") != string::npos ) {
      neve = atol(line.substr(line.find(':')+1, string::npos).c_str());
    } else if ( line.find("Integrated weight") != string::npos ) {
      xsec = atof(line.substr(line.find(':')+1, string::npos).c_str());
    } else if ( line.find("Max wgt") != string::npos ) {
      maxw = atof(line.substr(line.find(':')+1, string::npos).c_str());
    } else if ( line.find("ebeam(1)") != string::npos ) {
      ebeam1 = atof(line.c_str());
    } else if ( line.find("ebeam(2)") != string::npos ) {
      ebeam2 = atof(line.c_str());
    } else if ( line.find("lpp(1)") != string::npos ) {
      lpp1 = atoi(line.c_str());
    } else if ( line.find("lpp(2)") != string::npos ) {
      lpp2 = atoi(line.c_str());
    } else if ( line.find("PDF set") != string::npos ) {
      pdftag = line.substr(2, 7);
    }
  }
  

}


bool MadGraphReader::readEvent() {
  return false;
}

void MadGraphReader::scan() {}

MadGraphReader::~MadGraphReader() {}

void MadGraphReader::persistentOutput(PersistentOStream & os) const {
  // *** ATTENTION *** os << ; // Add all member variable which should be written persistently here.
}

void MadGraphReader::persistentInput(PersistentIStream & is, int) {
  // *** ATTENTION *** is >> ; // Add all member variable which should be read persistently here.
}

ClassDescription<MadGraphReader> MadGraphReader::initMadGraphReader;
// Definition of the static class description member.

void MadGraphReader::Init() {

  static ClassDocumentation<MadGraphReader> documentation
    ("There is no documentation for the \\classname{MadGraphReader} class");

}

