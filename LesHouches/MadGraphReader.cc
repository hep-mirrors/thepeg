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

  double xsec = -1.0;
  double maxw = -1.0;
  ieve = neve = 0;
  double ebeam1 = -1.0;
  double ebeam2 = -1.0;
  int lpp1 = 0;
  int lpp2 = 0;
  string pdftag;
  // First scan banner to extract some information
  while ( cfile.readline() ) {
    if ( !cfile || cfile.getc() != '#' ) break;
    if ( cfile.find("Number of events") ) {
      cfile.skip(':');
      cfile >> neve;
    } else if ( cfile.find("Integrated weight") ) {
      cfile.skip(':');
      cfile >> xsec;
    } else if ( cfile.find("Max wgt") ) {
      cfile.skip(':');
      cfile >> maxw;
    } else if ( cfile.find("ebeam(1)") ) {
      cfile >> ebeam1;
    } else if ( cfile.find("ebeam(2)") ) {
      cfile >> ebeam2;
    } else if ( cfile.find("lpp(1)") ) {
      cfile >> lpp1;
    } else if ( cfile.find("lpp(2)") ) {
      cfile >> lpp2;
    } else if ( cfile.find("PDF set") ) {
      cfile.skip('\'');
      cfile >> pdftag;
      pdftag = pdftag.substr(0, 7);
    }
  }

  // Return here if no comment block was found.
  if ( neve <= 0 ) return;

  // Convert the extracted information to LesHouches format.
  NRUP = 1;
  LPRUP.push_back(0);
  XSECUP.push_back(xsec);
  XERRUP.push_back(0.0);
  XMAXUP.push_back(maxw);
  weighted(true);
  NEvents(neve);
  maxXSec(NEvents()*xSec());
  negativeWeights(false);

  if ( !IDBMUP.first ) {
    if ( lpp1 == 1 ) IDBMUP.first = ParticleID::pplus;
    else if ( lpp1 == -1 ) IDBMUP.first = ParticleID::pbarminus;
  }
  if ( !IDBMUP.second ) {
    if ( lpp2 == 1 ) IDBMUP.second = ParticleID::pplus;
    else if ( lpp2 == -1 ) IDBMUP.second = ParticleID::pbarminus;
  }

  if ( EBMUP.first <= 0.0*GeV ) EBMUP.first = ebeam1;
  if ( EBMUP.second <= 0.0*GeV ) EBMUP.second = ebeam2;

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

  if ( !cfile )
    throw LesHouchesFileError()
      << "An error occurred while '" << name() << "' was reading the file '"
      << filename() << "'." << Exception::runerror;
}

void MadGraphReader::scan() {
  LesHouchesFileReader::scan();
}

bool MadGraphReader::readEvent() {
  if ( !cfile ) return false;

  NUP = 0;
  ieve = 0;
  long evno = 0;
  XWGTUP = 0.0;
  double scale = 0.0;
  double aEM = 0.0;
  double aS = 0.0;
  bool oldformat = false;

  cfile >> NUP >> evno >> XWGTUP >> scale >> aEM >> aS;
  if ( !cfile ) {
    IDPRUP = evno;
    ++ieve;
    oldformat = true;
  } else {
    IDPRUP = 0;
    ieve = evno;
    SCALUP = scale;
    AQEDUP = aEM;
    AQCDUP = aS;
  }

  IDUP.resize(NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < NUP; ++i ) cfile >> IDUP[i];

  MOTHUP.resize(NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < NUP; ++i ) cfile >> MOTHUP[i].first;
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < NUP; ++i ) cfile >> MOTHUP[i].second;

  ICOLUP.resize(NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < NUP; ++i ) cfile >> ICOLUP[i].first;
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < NUP; ++i ) cfile >> ICOLUP[i].second;

  if ( oldformat ) {
    ISTUP.assign(NUP, 1);
    ISTUP[0] = ISTUP[1] = -1;
    SPINUP.assign(NUP, 9);
  } else {
    ISTUP.resize(NUP);
    if ( !cfile.readline() ) return false;
    for ( int i = 0; i < NUP; ++i ) cfile >> ISTUP[i];
    SPINUP.resize(NUP, 9);
    if ( !cfile.readline() ) return false;
    for ( int i = 0; i < NUP; ++i ) cfile >> SPINUP[i];
  }

  PUP.resize(NUP, vector<double>(5));
  for ( int i = 0; i < NUP; ++i ) {
    if ( !cfile.readline() ) return false;
    int dummy = 0;
    cfile  >> dummy >> PUP[i][3] >> PUP[i][0] >> PUP[i][1] >> PUP[i][2];
    PUP[i][4] = sqrt(max(sqr(PUP[i][3]) - sqr(PUP[i][0]) -
			 sqr(PUP[i][1]) - sqr(PUP[i][2]), 0.0));
  }

  if ( !cfile ) return false;

  // Set info not obtained from MadGraph.
  VTIMUP = vector<double>(NUP, -1.0);

  cfile.readline();

  // Return true even if last read failed.
  return true;

}

MadGraphReader::~MadGraphReader() {}

void MadGraphReader::persistentOutput(PersistentOStream & os) const {
  os << neve;
}

void MadGraphReader::persistentInput(PersistentIStream & is, int) {
  is >> neve;
  ieve = 0;
}

ClassDescription<MadGraphReader> MadGraphReader::initMadGraphReader;
// Definition of the static class description member.

void MadGraphReader::Init() {

  static ClassDocumentation<MadGraphReader> documentation
    ("There is no documentation for the ThePEG::MadGraphReader class");

}

