// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesReader class.
//

#include "LesHouchesReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/PDF/PDFBase.h"

using namespace ThePEG;

LesHouchesReader::LesHouchesReader()
: IDWTUP(0), NRUP(0), NUP(0), IDPRUP(0), XWGTUP(0.0),
  SCALUP(0.0), AQEDUP(0.0), AQCDUP(0.0), theXSec(0.0*picobarn),
  theMaxXSec(0.0*picobarn), theMaxWeight(0.0), theNEvents(0), theMaxScan(-1),
  isWeighted(false), hasNegativeWeights(false) {}

LesHouchesReader::LesHouchesReader(const LesHouchesReader & x)
  : HandlerBase(x), IDBMUP(x.IDBMUP), EBMUP(x.EBMUP),
    PDFGUP(x.PDFGUP), PDFSUP(x.PDFSUP), thePDFA(x.thePDFA), thePDFB(x.thePDFB),
    IDWTUP(x.IDWTUP),
    NRUP(x.NRUP), XSECUP(x.XSECUP), XERRUP(x.XERRUP),
    XMAXUP(x.XMAXUP), LPRUP(x.LPRUP), NUP(x.NUP),
    IDPRUP(x.IDPRUP), XWGTUP(x.XWGTUP), SCALUP(x.SCALUP),
    AQEDUP(x.AQEDUP), AQCDUP(x.AQCDUP), IDUP(x.IDUP),
    ISTUP(x.ISTUP), MOTHUP(x.MOTHUP), ICOLUP(x.ICOLUP),
    PUP(x.PUP), VTIMUP(x.VTIMUP), SPINUP(x.SPINUP), theXSec(x.theXSec),
    theMaxXSec(x.theMaxXSec), theMaxWeight(x.theMaxWeight),
    theNEvents(x.theNEvents), theMaxScan(x.theMaxScan),
    isWeighted(x.isWeighted), hasNegativeWeights(x.hasNegativeWeights) {}

LesHouchesReader::~LesHouchesReader() {}

void LesHouchesReader::scan() {
  NRUP = 0;
  XSECUP.clear();
  XERRUP.clear();
  XMAXUP.clear();
  LPRUP.clear();
  xSec(0.0*picobarn);
  maxXSec(0.0*picobarn);
  maxWeight(0.0);
  
  open();

  // If the open() has not already gotten information about subprocesses
  // and cross sections we have to scan through the events.
  if ( !NRUP ) {
    vector<long> LPRN;
    double xlast = 0.0;
    long neve = 0;
    weighted(false);
    negativeWeights(false);
    for ( int i = 0; ( maxScan() < 0 || i < maxScan() ) && readEvent(); ++i ) {
      ++neve;
      vector<int>::iterator idit = find(LPRUP.begin(), LPRUP.end(), IDPRUP);
      if ( idit == LPRUP.end() ) {
	LPRUP.push_back(IDPRUP);
	LPRN.push_back(1);
	XSECUP.push_back(XWGTUP);
	XERRUP.push_back(sqr(XWGTUP));
	XMAXUP.push_back(abs(XWGTUP));
      } else {
	int id = idit - LPRUP.begin();
	++LPRN[id];
	XSECUP[id] += XWGTUP;
	XERRUP[id] += sqr(XWGTUP);
	XMAXUP[id] = max(XMAXUP[id], abs(XWGTUP));
      }
      if ( i == 0 ) xlast = abs(XWGTUP);
      if ( !weighted() && xlast != abs(XWGTUP) ) weighted(true);
      if ( !negativeWeights() && XWGTUP < 0.0 ) negativeWeights(true);
    }
    if ( maxScan() < 0 || neve > NEvents() ) NEvents(neve);
    for ( int id = 0, N = LPRUP.size(); id < N; ++id ) {
      if ( !weighted() ) XERRUP[id] = XSECUP[id]/sqrt(double(LPRN[id]));
      else XERRUP[id] = sqrt(max(0.0, XSECUP[id] - sqr(XERRUP[id])/LPRN[id]));
    }
  }

  CrossSection xsec = 0.0*picobarn;
  maxWeight(0.0);
  for ( int ip = 0; ip < NRUP; ++ip ) {
    xsec += XSECUP[ip]*picobarn;
    if ( maxWeight() < XMAXUP[ip] ) maxWeight(XMAXUP[ip]);
  }
  if ( xSec() <= 0.0*picobarn ) xSec(xsec);
  if ( weighted() && maxXSec() <= 0.0*picobarn && NEvents() > 0 )
    maxXSec(NEvents()*maxWeight());
  return;
}

void LesHouchesReader::convertEvent() {
  particleIndex.clear();
  colourIndex.clear();
  colourIndex(0, tColinePtr());
  readEvent();
  createParticles();
  createBeams();
  connectMothers();
}

void LesHouchesReader::createParticles() {
  theBeams = PPair();
  theIncoming = PPair();
  theOutgoing = PVector();
  theIntermediates = PVector();
  for ( int i = 0, N = IDUP.size(); i < N; ++i ) {
    if ( !IDUP[i] ) continue;
    Lorentz5Momentum mom(PUP[i][1]*GeV, PUP[i][2]*GeV, PUP[i][3]*GeV,
			 PUP[i][4]*GeV, PUP[i][5]*GeV);
    PPtr p = getParticleData(IDUP[i])->produceParticle(mom);
    tColinePtr c = colourIndex(ICOLUP[i].first);
    if ( c ) c->addColoured(p);
    c = colourIndex(ICOLUP[i].second);
    if ( c ) c->addAntiColoured(p);
    particleIndex(i + 1, p);
    switch ( ISTUP[i] ) {
    case -9:
      if ( !theBeams.first ) theBeams.first = p;
      else if ( !theBeams.second ) theBeams.second = p;
      else throw LesHouchesInconsistencyError()
	<< "To many incoming beam particles in the LesHouchesReader '"
	<< name() << "'." << Exception::runerror;
      break;
    case -1:
      if ( !theIncoming.first ) theIncoming.first = p;
      else if ( !theIncoming.second ) theIncoming.second = p;
      else throw LesHouchesInconsistencyError()
	<< "To many incoming particles to hard subprocess in the "
	<< "LesHouchesReader '"	<< name() << "'." << Exception::runerror;
      break;
    case 1:
      theOutgoing.push_back(p);
      break;
    case -2:
    case 2:
    case 3:
      theIntermediates.push_back(p);
      break;
    default:
      throw LesHouchesInconsistencyError()
	<< "Unknown status code (" << ISTUP[i] << ") in the LesHouchesReader '"
	<< name() << "'." << Exception::runerror;
    }
  }
}

void LesHouchesReader::createBeams() {

  if ( !theBeams.first ) {
    theBeams.first = getParticleData(IDBMUP.first)->produceParticle();
    double m = theBeams.first->mass()/GeV;
    theBeams.first->set5Momentum
      (Lorentz5Momentum(0.0*GeV, 0.0*GeV, sqrt(sqr(EBMUP.first) - sqr(m))*GeV,
			EBMUP.first*GeV, m*GeV));
    IDUP.push_back(IDBMUP.first);
    ISTUP.push_back(-9);
    MOTHUP.push_back(make_pair(0, 0));
    ICOLUP.push_back(make_pair(0, 0));
    VTIMUP.push_back(0.0);
    SPINUP.push_back(0.0);
    MOTHUP[particleIndex(theIncoming.first)].first = IDUP.size();
  }
  if ( !theBeams.second ) {
    theBeams.second = getParticleData(IDBMUP.second)->produceParticle();
    double m = theBeams.second->mass()/GeV;
    theBeams.second->set5Momentum
      (Lorentz5Momentum(0.0*GeV, 0.0*GeV, -sqrt(sqr(EBMUP.second) - sqr(m))*GeV,
			EBMUP.second*GeV, m*GeV));
    IDUP.push_back(IDBMUP.second);
    ISTUP.push_back(-9);
    MOTHUP.push_back(make_pair(0, 0));
    ICOLUP.push_back(make_pair(0, 0));
    VTIMUP.push_back(0.0);
    SPINUP.push_back(0.0);
    MOTHUP[particleIndex(theIncoming.second)].first = IDUP.size();
  }
}

void LesHouchesReader::connectMothers() {
  const ObjectIndexer<long,Particle> & pi = particleIndex;
  for ( int i = 0, N = IDUP.size(); i < N; ++i ) {
    if ( pi(MOTHUP[i].first) )
      pi(MOTHUP[i].first)->addChild(pi(i + 1));
    if ( pi(MOTHUP[i].second) )
      pi(MOTHUP[i].second)->addChild(pi(i + 1));
  }
}

void LesHouchesReader::persistentOutput(PersistentOStream & os) const {
  os << IDBMUP << EBMUP << PDFGUP << PDFSUP << thePDFA << thePDFB
     << IDWTUP << NRUP
     << XSECUP << XERRUP << XMAXUP << LPRUP << NUP << IDPRUP
     << XWGTUP << SCALUP << AQEDUP << AQCDUP << IDUP << ISTUP
     << MOTHUP << ICOLUP << PUP << VTIMUP << SPINUP
     << ounit(theXSec, picobarn) << ounit(theMaxXSec, picobarn)
     << theMaxWeight << theNEvents << theMaxScan << isWeighted
     << hasNegativeWeights;
}

void LesHouchesReader::persistentInput(PersistentIStream & is, int) {
  is >> IDBMUP >> EBMUP >> PDFGUP >> PDFSUP >> thePDFA >> thePDFB
     >> IDWTUP >> NRUP
     >> XSECUP >> XERRUP >> XMAXUP >> LPRUP >> NUP >> IDPRUP
     >> XWGTUP >> SCALUP >> AQEDUP >> AQCDUP >> IDUP >> ISTUP
     >> MOTHUP >> ICOLUP >> PUP >> VTIMUP >> SPINUP
     >> iunit(theXSec, picobarn) >> iunit(theMaxXSec, picobarn)
     >> theMaxWeight >> theNEvents >> theMaxScan >> isWeighted
     >> hasNegativeWeights;
}

AbstractClassDescription<LesHouchesReader>
LesHouchesReader::initLesHouchesReader;
// Definition of the static class description member.

void LesHouchesReader::setBeamA(long id) { IDBMUP.first = id; }
long LesHouchesReader::getBeamA() const { return IDBMUP.first; }
void LesHouchesReader::setBeamB(long id) { IDBMUP.second = id; }
long LesHouchesReader::getBeamB() const { return IDBMUP.second; }
void LesHouchesReader::setEBeamA(Energy e) { EBMUP.first = e; }
Energy LesHouchesReader::getEBeamA() const { return EBMUP.first; }
void LesHouchesReader::setEBeamB(Energy e) { EBMUP.second = e; }
Energy LesHouchesReader::getEBeamB() const { return EBMUP.second; }

void LesHouchesReader::Init() {

  static ClassDocumentation<LesHouchesReader> documentation
    ("ThePEG::LesHouchesReader is an abstract base class to be used "
     "for objects which reads event files or streams from matrix element "
     "generators.");

  static Parameter<LesHouchesReader,long> interfaceBeamA
    ("BeamA",
     "The PDG id of the incoming particle along the positive z-axis. "
     "If zero the corresponding information is to be deduced from the "
     "event stream/file.",
     0, 0, 0, 0,
     true, false, false,
     &LesHouchesReader::setBeamA,
     &LesHouchesReader::getBeamA, 0, 0, 0);

  static Parameter<LesHouchesReader,long> interfaceBeamB
    ("BeamB",
     "The PDG id of the incoming particle along the negative z-axis. "
     "If zero the corresponding information is to be deduced from the "
     "event stream/file.",
     0, 0, 0, 0,
     true, false, false,
     &LesHouchesReader::setBeamB,
     &LesHouchesReader::getBeamB, 0, 0, 0);

  static Parameter<LesHouchesReader,Energy> interfaceEBeamA
    ("EBeamA",
     "The energy of the incoming particle along the positive z-axis. "
     "If zero the corresponding information is to be deduced from the "
     "event stream/file.",
     0, GeV, 0.0*GeV, 0.0*GeV, 1000000000.0*GeV,
     true, false, true,
     &LesHouchesReader::setEBeamA, &LesHouchesReader::getEBeamA, 0, 0, 0);

  static Parameter<LesHouchesReader,Energy> interfaceEBeamB
    ("EBeamB",
     "The energy of the incoming particle along the negative z-axis. "
     "If zero the corresponding information is to be deduced from the "
     "event stream/file.",
     0, GeV, 0.0*GeV, 0.0*GeV, 1000000000.0*GeV,
     true, false, true,
     &LesHouchesReader::setEBeamB, &LesHouchesReader::getEBeamB, 0, 0, 0);

  static Reference<LesHouchesReader,PDFBase> interfacePDFA
    ("PDFA",
     "The PDF used for incoming particle along the positive z-axis. "
     "If null the corresponding information is to be deduced from the "
     "event stream/file.",
     &LesHouchesReader::thePDFA, true, false, true, true, false);

  static Reference<LesHouchesReader,PDFBase> interfacePDFB
    ("PDFB",
     "The PDF used for incoming particle along the negative z-axis. "
     "If null the corresponding information is to be deduced from the "
     "event stream/file.",
     &LesHouchesReader::thePDFB, true, false, true, true, false);


  static Parameter<LesHouchesReader,long> interfaceMaxScan
    ("MaxScan",
     "The maximum number of events to scan to obtain information about "
     "processes and cross section in the intialization.",
     &LesHouchesReader::theMaxScan, -1, 0, 0,
     true, false, false);


}

