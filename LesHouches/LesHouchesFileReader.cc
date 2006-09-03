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

  cfile.readline();
  if ( !cfile.find("<LesHouchesEvents") ) return;
  map<string,string> attributes =
    StringUtils::xmlAttributes("LesHouchesEvents", cfile.getline());
  LHFVersion = attributes["version"];
  if ( LHFVersion.empty() ) return;

  bool readingHeader = false;
  bool readingInit = false;
  headerBlock = "";

  // Loop over all lines until we hit the </init> tag.
  while ( cfile.readline() && !cfile.find("</init>") ) {
    if ( cfile.find("<header") ) {
      // We have hit the header block, so we should dump this and all
      // following lines to headerBlock until we hit the end of it.
      readingHeader = true;
      headerBlock = cfile.getline() + "\n";
    }
    else if ( cfile.find("<init") ) {
      // We have hit the init block, so we should expect to find the
      // standard information in the following. But first check for
      // attributes.
      initAttributes = StringUtils::xmlAttributes("init", cfile.getline());
      readingInit = true;
      cfile.readline();
      if ( !( cfile >> heprup.IDBMUP.first >> heprup.IDBMUP.second
		    >> heprup.EBMUP.first >> heprup.EBMUP.second
	            >> heprup.PDFGUP.first >> heprup.PDFGUP.second
	            >> heprup.PDFSUP.first >> heprup.PDFSUP.second
		    >> heprup.IDWTUP >> heprup.NPRUP ) ) {
	heprup.NPRUP = -42;
	LHFVersion = "";
	return;
      }
      heprup.resize();

      for ( int i = 0; i < heprup.NPRUP; ++i ) {
	cfile.readline();
	if ( !( cfile >> heprup.XSECUP[i] >> heprup.XERRUP[i]
	              >> heprup.XMAXUP[i] >> heprup.LPRUP[i] ) ) {
	  heprup.NPRUP = -42;
	  LHFVersion = "";
	  return;
	}
      }
    }
    else if ( cfile.find("</header") ) {
      readingHeader = false;
      headerBlock += cfile.getline() + "\n";
    }
    else if ( readingHeader ) {
      // We are in the process of reading the header block. Dump the
	// line to haderBlock.
      headerBlock += cfile.getline() + "\n";
    }
    else if ( readingInit ) {
      // Here we found a comment line. Dump it to initComments.
      initComments += cfile.getline() + "\n";
    }
    else {
      // We found some other stuff outside the standard tags.
      outsideBlock += cfile.getline() + "\n";
    }
  }
  if ( !cfile ) {
    heprup.NPRUP = -42;
    LHFVersion = "";
    return;
  }

  weighted( abs(heprup.IDWTUP) <= 2 );
  negativeWeights( heprup.IDWTUP < 0 );

}

bool LesHouchesFileReader::doReadEvent() {
  if ( !cfile ) return false;
  if ( LHFVersion.empty() ) return false;
  if ( heprup.NPRUP < 0 ) return false;
  eventComments = "";
  outsideBlock = "";
  hepeup.NUP = 0;

  // Keep reading lines until we hit the next event or the end of
  // the event block. Save any inbetween lines. Exit if we didn't
  // find an event.
  while ( cfile.readline() && !cfile.find("<event") )
    outsideBlock += cfile.getline() + "\n";

  // We found an event. First scan for attributes.
  eventAttributes = StringUtils::xmlAttributes("event", cfile.getline());
  if ( !cfile.readline()  ) return false;

  // The first line determines how many subsequent particle lines we
  // have.
  if ( !( cfile >> hepeup.NUP >> hepeup.IDPRUP >> hepeup.XWGTUP
	        >> hepeup.SCALUP >> hepeup.AQEDUP >> hepeup.AQCDUP ) )
    return false;
  hepeup.resize();
  // Read all particle lines.
  for ( int i = 0; i < hepeup.NUP; ++i ) {
    if ( !cfile.readline() ) return false;
    if ( !( cfile >> hepeup.IDUP[i] >> hepeup.ISTUP[i]
	          >> hepeup.MOTHUP[i].first >> hepeup.MOTHUP[i].second
         	  >> hepeup.ICOLUP[i].first >> hepeup.ICOLUP[i].second
	          >> hepeup.PUP[i][0] >> hepeup.PUP[i][1] >> hepeup.PUP[i][2]
	          >> hepeup.PUP[i][3] >> hepeup.PUP[i][4]
        	  >> hepeup.VTIMUP[i] >> hepeup.SPINUP[i] ) )
      return false;
  }

  // Now read any additional comments.
  while ( cfile.readline() && !cfile.find("</event>") )
    eventComments += cfile.getline() + "\n";

  if ( !cfile ) return false;
  return true;

}

void LesHouchesFileReader::close() {
  cfile.close();
  theFile = NULL;
}

void LesHouchesFileReader::persistentOutput(PersistentOStream & os) const {
  os << neve << LHFVersion << outsideBlock << headerBlock << initComments
     << initAttributes << eventComments << eventAttributes << theFileName;
}

void LesHouchesFileReader::persistentInput(PersistentIStream & is, int) {
  is >> neve >> LHFVersion >> outsideBlock >> headerBlock >> initComments
     >> initAttributes >> eventComments >> eventAttributes >> theFileName;
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

