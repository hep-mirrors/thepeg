// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MadGraphReader class.
//

#include "MadGraphReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDF/PDFBase.h"

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
  heprup.NRUP = 1;
  heprup.LPRUP.push_back(0);
  heprup.XSECUP.push_back(xsec);
  heprup.XERRUP.push_back(0.0);
  heprup.XMAXUP.push_back(maxw);
  weighted(true);
  NEvents(neve);
  negativeWeights(false);

  if ( !heprup.IDBMUP.first ) {
    if ( lpp1 == 1 ) heprup.IDBMUP.first = ParticleID::pplus;
    else if ( lpp1 == -1 ) heprup.IDBMUP.first = ParticleID::pbarminus;
  }
  if ( !heprup.IDBMUP.second ) {
    if ( lpp2 == 1 ) heprup.IDBMUP.second = ParticleID::pplus;
    else if ( lpp2 == -1 ) heprup.IDBMUP.second = ParticleID::pbarminus;
  }

  if ( heprup.EBMUP.first <= 0.0*GeV ) heprup.EBMUP.first = ebeam1;
  if ( heprup.EBMUP.second <= 0.0*GeV ) heprup.EBMUP.second = ebeam2;

  // Translation into PDFLib codes is not perfect.
  if ( pdftag.substr(0, 3) == "mrs" )
    heprup.PDFGUP.first = heprup.PDFGUP.second = 3;
  else if ( pdftag.substr(0, 4) == "cteq" )
    heprup.PDFGUP.first = heprup.PDFGUP.second = 4;
  else heprup.PDFGUP.first = heprup.PDFGUP.second = 0;
  if ( pdftag == "cteq3_m" ) heprup.PDFSUP.first = heprup.PDFSUP.second = 30;
  else if ( pdftag == "cteq3_l" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 29;
  else if ( pdftag == "cteq3_d" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 32;
  else if ( pdftag == "cteq4_m" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 34;
  else if ( pdftag == "cteq4_d" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 33;
  else if ( pdftag == "cteq4_l" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 32;
  else if ( pdftag == "cteq4a1" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 35;
  else if ( pdftag == "cteq4a2" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 36;
  else if ( pdftag == "cteq4a3" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 37;
  else if ( pdftag == "cteq4a4" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 38;
  else if ( pdftag == "cteq4a5" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 39;
  else if ( pdftag == "cteq4hj" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 40;
  else if ( pdftag == "cteq4lq" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 41;
  else if ( pdftag == "cteq5l1" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 46;
  else if ( pdftag.substr(0, 5) == "cteq5" )
    heprup.PDFSUP.first = heprup.PDFSUP.second = 48;
  else heprup.PDFSUP.first = heprup.PDFSUP.second = 0;

  if ( !cfile )
    throw LesHouchesFileError()
      << "An error occurred while '" << name() << "' was reading the file '"
      << filename() << "'." << Exception::runerror;
}


long MadGraphReader::scan() {
  long neve = LesHouchesFileReader::scan();
  for ( int ip = 0; ip < heprup.NRUP; ++ip ) {
    heprup.XSECUP[ip] *= neve;
    heprup.XERRUP[ip] *= neve;
  }
  return neve;
}

bool MadGraphReader::readEvent() {
  if ( !cfile ) return false;

  hepeup.NUP = 0;
  ieve = 0;
  long evno = 0;
  hepeup.XWGTUP = 0.0;
  double scale = 0.0;
  double aEM = 0.0;
  double aS = 0.0;
  bool oldformat = false;

  cfile >> hepeup.NUP >> evno >> hepeup.XWGTUP >> scale >> aEM >> aS;
  if ( !cfile ) {
    hepeup.IDPRUP = evno;
    hepeup.SCALUP = fixedScale;
    hepeup.AQEDUP = fixedAEM;
    hepeup.AQCDUP = fixedAS;
    ++ieve;
    oldformat = true;
  } else {
    hepeup.IDPRUP = 0;
    ieve = evno;
    hepeup.SCALUP = scale;
    hepeup.AQEDUP = aEM;
    hepeup.AQCDUP = aS;
  }

  hepeup.IDUP.resize(hepeup.NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.IDUP[i];

  hepeup.MOTHUP.resize(hepeup.NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.MOTHUP[i].first;
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.MOTHUP[i].second;

  hepeup.ICOLUP.resize(hepeup.NUP);
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.ICOLUP[i].first;
  if ( !cfile.readline() ) return false;
  for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.ICOLUP[i].second;

  if ( oldformat ) {
    hepeup.ISTUP.assign(hepeup.NUP, 1);
    hepeup.ISTUP[0] = hepeup.ISTUP[1] = -1;
    hepeup.SPINUP.assign(hepeup.NUP, 9);
  } else {
    hepeup.ISTUP.resize(hepeup.NUP);
    if ( !cfile.readline() ) return false;
    for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.ISTUP[i];
    hepeup.SPINUP.resize(hepeup.NUP, 9);
    if ( !cfile.readline() ) return false;
    for ( int i = 0; i < hepeup.NUP; ++i ) cfile >> hepeup.SPINUP[i];
  }

  hepeup.PUP.resize(hepeup.NUP, vector<double>(5));
  for ( int i = 0; i < hepeup.NUP; ++i ) {
    if ( !cfile.readline() ) return false;
    int dummy = 0;
    cfile  >> dummy >> hepeup.PUP[i][3]
	   >> hepeup.PUP[i][0] >> hepeup.PUP[i][1] >> hepeup.PUP[i][2];
    hepeup.PUP[i][4] =
      sqrt(max(sqr(hepeup.PUP[i][3]) - sqr(hepeup.PUP[i][0]) -
	       sqr(hepeup.PUP[i][1]) - sqr(hepeup.PUP[i][2]), 0.0));
  }

  if ( !cfile ) return false;

  // Set info not obtained from MadGraph.
  hepeup.VTIMUP = vector<double>(hepeup.NUP, -1.0);

  // Deduce positions of incoming beams and corresponding partons.
  pair<int,int> beampos(-1, -1);
  for ( int i = 0; i < hepeup.NUP; ++i ) {
    if ( hepeup.ISTUP[i] != -9 ) continue;
    if ( beampos.first < 0 ) beampos.first = i;
    else if ( beampos.second < 0 ) beampos.second = i;
  }
  pair<int,int> partpos(-1, -1);
  for ( int i = hepeup.NUP - 1; i >= 0; --i ) {
    if ( hepeup.ISTUP[i] != -1 ) continue;
    if ( hepeup.MOTHUP[i].first > 0 &&
	 hepeup.MOTHUP[i].first == beampos.first )
      partpos.first = i;
    else if ( hepeup.MOTHUP[i].first > 0 &&
	      hepeup.MOTHUP[i].first == beampos.second )
      partpos.second = i;
    else if ( partpos.second < 0 ) partpos.second = i;
    else if ( partpos.first < 0 ) partpos.first = i;
  }

  // Now determine the corresponding PDF weights.
  if ( partpos.first < 0 || partpos.second < 0 )
    throw LesHouchesInconsistencyError()
      << "No incoming partons were found in event number " << ieve
      << " in MadGraphReader '" << name() << "'." << Exception::runerror;
  tcPDPtr particle =
    getParticleData(beampos.first > 0?
		    hepeup.IDUP[beampos.first]: heprup.IDBMUP.first);
  tcPDPtr parton = getParticleData(hepeup.IDUP[partpos.first]);
  double totp = beampos.first > 0?
    hepeup.PUP[beampos.first][3] + hepeup.PUP[beampos.first][2]:
    2.0*heprup.EBMUP.first;
  double x = (hepeup.PUP[partpos.first][3] + hepeup.PUP[partpos.first][2])/totp;
  hepeup.XPDWUP.first =
    thePDFA->xfx(particle, parton, sqr(hepeup.SCALUP*GeV), x);
  particle =
    getParticleData(beampos.second > 0?
		    hepeup.IDUP[beampos.second]: heprup.IDBMUP.second);
  parton = getParticleData(hepeup.IDUP[partpos.second]);
  totp = beampos.second > 0?
    hepeup.PUP[beampos.second][3] - hepeup.PUP[beampos.second][2]:
    2.0*heprup.EBMUP.second;
  x = (hepeup.PUP[partpos.second][3] - hepeup.PUP[partpos.second][2])/totp;
  hepeup.XPDWUP.second =
    thePDFB->xfx(particle, parton, sqr(hepeup.SCALUP*GeV), x);

  cfile.readline();

  // Reweight according to the re- and pre-weights objects in the
  // LesHouchesReader base class.
  hepeup.XWGTUP *= reweight();

  // Return true even if last read failed.
  return true;

}

MadGraphReader::~MadGraphReader() {}

void MadGraphReader::persistentOutput(PersistentOStream & os) const {
  os << ounit(fixedScale, GeV) << fixedAEM << fixedAS;
}

void MadGraphReader::persistentInput(PersistentIStream & is, int) {
  is >> iunit(fixedScale, GeV) >> fixedAEM >> fixedAS;
}

ClassDescription<MadGraphReader> MadGraphReader::initMadGraphReader;
// Definition of the static class description member.

void MadGraphReader::Init() {

  static ClassDocumentation<MadGraphReader> documentation
    ("ThePEG::MadGraphReader is used together with the LesHouchesEventHandler "
     "to read event files generated with the MadGraph/MadEvent program.",
     "Events were read from event files generated "
     "with the MadGraph/MadEvent\\cite{ThePEG::MadGraph} program.",
     "\\bibitem{ThePEG::MadGraph} F. Maltoni and T. Stelzer, hep-ph/0208156;\\\\"
     "T. Stelzer and W.F. Long, \\textit{Comput.~Phys.~Commun.} "
     "\\textbf{81} (1994) 357-371.");

  static Parameter<MadGraphReader,Energy> interfaceFixedScale
    ("FixedScale",
     "Old MadGraph files do not necessarily contain information about "
     "the factorization (or renormalization) scale. In this case this "
     "is used instead.",
     &MadGraphReader::fixedScale, GeV, 91.188*GeV, 0.0*GeV, 1000.0*GeV,
     true, false, true);

  static Parameter<MadGraphReader,double> interfaceFixedAlphaEM
    ("FixedAlphaEM",
     "Old MadGraph files do not necessarily contain information about "
     "the value of \f$\alpha_{EM}\f$. In this case this is used instead.",
     &MadGraphReader::fixedAEM, 0.007546772, 0.0, 1.0,
     true, false, true);

  static Parameter<MadGraphReader,double> interfaceFixedAlphaS
    ("FixedAlphaS",
     "Old MadGraph files do not necessarily contain information about "
     "the value of \f$\alpha_S\f$. In this case this is used instead.",
     &MadGraphReader::fixedAS, 0.12, 0.0, 1.0,
     true, false, true);

}

