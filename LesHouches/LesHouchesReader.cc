// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesReader class.
//

#include "LesHouchesReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Event.h"

using namespace ThePEG;

LesHouchesReader::LesHouchesReader()
: IDWTUP(0), NRUP(0), NUP(0), IDPRUP(0), XWGTUP(0.0),
  SCALUP(0.0), AQEDUP(0.0), AQCDUP(0.0) {}

LesHouchesReader::LesHouchesReader(const LesHouchesReader & x)
  : HandlerBase(x), IDBMUP(x.IDBMUP), EBMUP(x.EBMUP),
    PDFGUP(x.PDFGUP), PDFSUP(x.PDFSUP), IDWTUP(x.IDWTUP),
    NRUP(x.NRUP), XSECUP(x.XSECUP), XERRUP(x.XERRUP),
    XMAXUP(x.XMAXUP), LPRUP(x.LPRUP), NUP(x.NUP),
    IDPRUP(x.IDPRUP), XWGTUP(x.XWGTUP), SCALUP(x.SCALUP),
    AQEDUP(x.AQEDUP), AQCDUP(x.AQCDUP), IDUP(x.IDUP),
    ISTUP(x.ISTUP), MOTHUP(x.MOTHUP), ICOLUP(x.ICOLUP),
    PUP(x.PUP), VTIMUP(x.VTIMUP), SPINUP(x.SPINUP) {}

LesHouchesReader::~LesHouchesReader() {}

EventPtr LesHouchesReader::getEvent() {

  particleIndex.clear();
  colourIndex.clear();
  colourIndex(0, tColinePtr());
  readEvent();

  return EventPtr();
}

void LesHouchesReader::createParticles() {
  PPair beams;
  PPair incoming;
  PVector outgoing;
  PVector spaceintermediate;
  PVector timeintermediate;
  for ( int i = 0, N = IDUP.size(); i < N; ++i ) {
    if ( !IDUP[i] ) continue;
    Lorentz5Momentum mom(PUP[i][1]*GeV, PUP[i][2]*GeV, PUP[i][3]*GeV,
			 PUP[i][4]*GeV, PUP[i][5]*GeV);
    PPtr p = getParticleData(IDUP[i])->produceParticle(mom);
    tColinePtr c = colourIndex(ICOLUP[i].first);
    if ( c ) c->addColoured(p);
    c = colourIndex(ICOLUP[i].second);
    if ( c ) c->addAntiColoured(p);
    particleIndex(i, p);
    switch ( ISTUP[i] ) {
    case -9:
      if ( !beams.first ) beams.first = p;
      else if ( !beams.second ) beams.second = p;
      else throw LesHouchesInconsistencyError()
	<< "To many incoming beam particles in the LesHouchesReader '"
	<< name() << "'." << Exception::runerror;
      break;
    case -2:
      spaceintermediate.push_back(p);
      break;
    case -1:
      if ( !incoming.first ) incoming.first = p;
      else if ( !incoming.second ) incoming.second = p;
      else throw LesHouchesInconsistencyError()
	<< "To many incoming particles to hard subprocess in the "
	<< "LesHouchesReader '"	<< name() << "'." << Exception::runerror;
      break;
    case 1:
      outgoing.push_back(p);
      break;
    case 2:
    case 3:
      timeintermediate.push_back(p);
      break;
    default:
      throw LesHouchesInconsistencyError()
	<< "Unknown status code (" << ISTUP[i] << ") in the LesHouchesReader '"
	<< name() << "'." << Exception::runerror;
    }
  }
}

void LesHouchesReader::persistentOutput(PersistentOStream & os) const {
  os << IDBMUP << EBMUP << PDFGUP << PDFSUP << IDWTUP << NRUP
     << XSECUP << XERRUP << XMAXUP << LPRUP << NUP << IDPRUP
     << XWGTUP << SCALUP << AQEDUP << AQCDUP << IDUP << ISTUP
     << MOTHUP << ICOLUP << PUP << VTIMUP << SPINUP;
}

void LesHouchesReader::persistentInput(PersistentIStream & is, int) {
  is >> IDBMUP >> EBMUP >> PDFGUP >> PDFSUP >> IDWTUP >> NRUP
     >> XSECUP >> XERRUP >> XMAXUP >> LPRUP >> NUP >> IDPRUP
     >> XWGTUP >> SCALUP >> AQEDUP >> AQCDUP >> IDUP >> ISTUP
     >> MOTHUP >> ICOLUP >> PUP >> VTIMUP >> SPINUP;
}

AbstractClassDescription<LesHouchesReader> LesHouchesReader::initLesHouchesReader;
// Definition of the static class description member.

void LesHouchesReader::Init() {

  static ClassDocumentation<LesHouchesReader> documentation
    ("There is no documentation for the \\classname{LesHouchesReader} class");

}

