// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MadGraphReader class.
//

#include "MadGraphReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/EnumParticles.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MadGraphReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;
using std::fgetc;
using std::fgets;

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
  // First scan banner to extract some information
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

  // Convert the extracted information to LesHouches format.
  if ( lpp1 == 1 ) IDBMUP.first = ParticleID::pplus;
  else if ( lpp1 == -1 ) IDBMUP.first = ParticleID::pbarminus;
  if ( lpp2 == 1 ) IDBMUP.second = ParticleID::pplus;
  else if ( lpp2 == -1 ) IDBMUP.second = ParticleID::pbarminus;
  if ( !lpp1 || !lpp2 ) {
    // Madgraph doesn't specify beams if they are not protons. If they
    // are electrons we have tolook at the first event to check.
    fgets(cline, 1024, theFile);
    istringstream is(fgets(cline, 1024, theFile));
    int idum1 = 0, idum2 = 0;
    is >> idum1 >> idum2;
    if ( !lpp1 ) IDBMUP.first = idum1;
    if ( !lpp2 ) IDBMUP.second = idum2;
    // Reopen the file to return to the correct position.
    close();
    open();
    while ( fgetc(theFile) == '#' ) fgets(cline, 1024, theFile);
  }
  EBMUP.first = ebeam1;
  EBMUP.second = ebeam2;

  // Translation into PDFLib codes is not perfect.
  if ( pdftag.substr(0, 3) == "mrs" ) PDFGUP.first = PDFGUP.second = 3;
  else if ( pdftag.substr(0, 4) == "cteq" ) PDFGUP.first = PDFGUP.second = 4;
  else PDFGUP.first = PDFGUP.second = 0;
  if ( pdftag == "cteq3_m" ) PDFSUP.first = PDFSUP.second = 30;
  else if ( pdftag == "cteq3_l" ) PDFSUP.first = PDFSUP.second = 29;
  else if ( pdftag == "cteq3_d" ) PDFSUP.first = PDFSUP.second = 32;
  else if ( pdftag == "cteq4_m" ) PDFSUP.first = PDFSUP.second = 34;
  else if ( pdftag == "cteq4_d" ) PDFSUP.first = PDFSUP.second = 33;
  else if ( pdftag == "cteq4_l" ) PDFSUP.first = PDFSUP.second = 32;
  else if ( pdftag == "cteq4a1" ) PDFSUP.first = PDFSUP.second = 35;
  else if ( pdftag == "cteq4a2" ) PDFSUP.first = PDFSUP.second = 36;
  else if ( pdftag == "cteq4a3" ) PDFSUP.first = PDFSUP.second = 37;
  else if ( pdftag == "cteq4a4" ) PDFSUP.first = PDFSUP.second = 38;
  else if ( pdftag == "cteq4a5" ) PDFSUP.first = PDFSUP.second = 39;
  else if ( pdftag == "cteq4hj" ) PDFSUP.first = PDFSUP.second = 40;
  else if ( pdftag == "cteq4lq" ) PDFSUP.first = PDFSUP.second = 41;
  else if ( pdftag == "cteq5l1" ) PDFSUP.first = PDFSUP.second = 46;
  else if ( pdftag.substr(0, 5) == "cteq5" ) PDFSUP.first = PDFSUP.second = 48;
  else PDFSUP.first = PDFSUP.second = 0;
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

