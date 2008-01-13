// -*- C++ -*-
//
// LesHouchesReader.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LesHouchesReader class.
//

#include "LesHouchesReader.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Command.h"
#include "config.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesReader.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/PDF/LHAPDF.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Repository/RandomGenerator.h"
#include "ThePEG/Cuts/Cuts.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/CascadeHandler.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/StringUtils.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "LesHouchesEventHandler.h"
#include "ThePEG/Utilities/Throw.h"
#include "ThePEG/Utilities/HoldFlag.h"

using namespace ThePEG;

LesHouchesReader::LesHouchesReader(bool active)
  : theNEvents(0), position(0), reopened(0), theMaxScan(-1),
    isActive(active), isWeighted(false), hasNegativeWeights(false),
    theCacheFileName(""), theCacheFile(NULL), preweight(1.0),
    reweightPDF(false), doInitPDFs(false),
    theMaxMultCKKW(0), theMinMultCKKW(0), lastweight(1.0), maxFactor(1.0),
    skipping(false) {}

LesHouchesReader::LesHouchesReader(const LesHouchesReader & x)
  : HandlerBase(x), LastXCombInfo<>(x), heprup(x.heprup), hepeup(x.hepeup),
    inData(x.inData), inPDF(x.inPDF), outPDF(x.outPDF),
    thePartonExtractor(x.thePartonExtractor), thePartonBins(x.thePartonBins),
    theXCombs(x.theXCombs), theCuts(x.theCuts),
    theNEvents(x.theNEvents), position(x.position), reopened(x.reopened),
    theMaxScan(x.theMaxScan), isActive(x.isActive), isWeighted(x.isWeighted),
    hasNegativeWeights(x.hasNegativeWeights),
    theCacheFileName(x.theCacheFileName),
    stats(x.stats), statmap(x.statmap),
    thePartonBinInstances(x.thePartonBinInstances),
    theCacheFile(NULL), reweights(x.reweights), preweights(x.preweights),
    preweight(x.preweight), reweightPDF(x.reweightPDF),
    doInitPDFs(x.doInitPDFs),
    theMaxMultCKKW(x.theMaxMultCKKW), theMinMultCKKW(x.theMinMultCKKW),
    lastweight(x.lastweight), maxFactor(x.maxFactor), skipping(x.skipping) {}

LesHouchesReader::~LesHouchesReader() {}

void LesHouchesReader::doinitrun() {
  HandlerBase::doinitrun();
  stats.reset();
  for ( StatMap::iterator i = statmap.begin(); i != statmap.end(); ++i )
    i->second.reset();
  open();
  if ( cacheFileName().length() ) openReadCacheFile();
  position = 0;
  reopened = 0;
}

bool LesHouchesReader::preInitialize() const {
  if ( HandlerBase::preInitialize() ) return true;
  if ( doInitPDFs && ! ( inPDF.first && inPDF.second ) ) return true;
  return false;
}

void LesHouchesReader::doinit() throw(InitException) {
  HandlerBase::doinit();
  open();
  close();
  if ( !heprup.IDBMUP.first || !heprup.IDBMUP.second )
    Throw<LesHouchesInitError>()
      << "No information about incoming particles were found in "
      << "LesHouchesReader '" << name() << "'." << Exception::warning;
  inData = make_pair(getParticleData(heprup.IDBMUP.first),
		     getParticleData(heprup.IDBMUP.second));
  if ( heprup.EBMUP.first <= 0.0 || heprup.EBMUP.second <= 0.0 )
    Throw<LesHouchesInitError>()
    << "No information about the energy of incoming particles were found in "
    << "LesHouchesReader '" << name() << "'." << Exception::warning;
  
  if ( doInitPDFs && ! ( inPDF.first && inPDF.second ) ) {
    initPDFs();
    if ( ! ( inPDF.first && inPDF.second ) ) Throw<InitException>()
      << "LesHouchesReader '" << name()
      << "' could not create PDFBase objects in pre-initialization."
      << Exception::warning;
  }
  else if ( !inPDF.first || !inPDF.second ) Throw<LesHouchesInitError>()
    << "No information about the PDFs of incoming particles were found in "
    << "LesHouchesReader '" << name() << "'." << Exception::warning;
}

void LesHouchesReader::initPDFs() {
  if ( inPDF.first && inPDF.second ) return;

  string remhname;
  if ( heprup.PDFSUP.first && !inPDF.first) {
    inPDF.first = dynamic_ptr_cast<PDFPtr>
      (generator()->preinitCreate("ThePEG::LHAPDF", fullName() + "/PDFA"));
    if ( !inPDF.first ) {
      Throw<InitException>()
	<< "LesHouchesReader '" << name() << "' could not use information "
	<< "about the PDFs used because the LHAPDF library was not properly "
	"defined." << Exception::warning;
      return;
    }
    remhname = fullName() + "/DummyRemH";
    generator()->preinitCreate("ThePEG::NoRemnants", remhname);
    generator()->preinitInterface(inPDF.first, "RemnantHandler",
				  "set", remhname);
    if ( heprup.PDFGUP.first > 0 && heprup.PDFGUP.first < 10 ) {
      ostringstream os;
      os << heprup.PDFGUP.first << " " << heprup.PDFSUP.first;
      generator()->preinitInterface(inPDF.first, "PDFLIBNumbers",
				    "set", os.str());
    } else {
      ostringstream os;
      os << heprup.PDFGUP.first*1000 + heprup.PDFSUP.first;
      generator()->preinitInterface(inPDF.first, "PDFNumber",
				    "set", os.str());
    }
    generator()->preinitInterface(inPDF.first, "RangeException",
				    "set", "Freeze");
  }

  if ( heprup.PDFSUP.second && !inPDF.second) {
    inPDF.second = dynamic_ptr_cast<PDFPtr>
      (generator()->preinitCreate("ThePEG::LHAPDF", fullName() + "/PDFB"));
    if ( !inPDF.second ) {
      Throw<InitException>()
	<< "LesHouchesReader '" << name() << "' could not use information "
	<< "about the PDFs used because the LHAPDF library was not properly "
	"defined." << Exception::warning;
      return;
    }
    if ( remhname == "" ) {
      remhname = fullName() + "/DummyRemH";
      generator()->preinitCreate("ThePEG::NoRemnants", remhname);
    }
    generator()->preinitInterface(inPDF.second, "RemnantHandler",
				  "set", remhname);      
    if ( heprup.PDFGUP.second > 0 && heprup.PDFGUP.second < 10 ) {
      ostringstream os;
      os << heprup.PDFGUP.second << " " << heprup.PDFSUP.second;
      generator()->preinitInterface(inPDF.second, "PDFLIBNumbers",
				    "set", os.str());
    } else {
      ostringstream os;
      os << heprup.PDFGUP.second*1000 + heprup.PDFSUP.second;
      generator()->preinitInterface(inPDF.second, "PDFNumber",
				    "set", os.str());
    }
    generator()->preinitInterface(inPDF.second, "RangeException",
				    "set", "Freeze");
  }
  
  if ( ! ( inPDF.first && inPDF.second ) ) Throw<InitException>()
    << "LesHouchesReader '" << name()
    << "' could not find information about the PDFs used."
    << Exception::warning;
}

void LesHouchesReader::initialize(LesHouchesEventHandler & eh) {
  Energy2 Smax = 0.0*GeV2;
  double Y = 0.0;
  if ( !theCuts ) {
    theCuts = eh.cuts();
    if ( !theCuts ) throw LesHouchesInitError()
      << "No Cuts object was assigned to the LesHouchesReader '"
      << name() << "' nor was one assigned to the controlling "
      << "LesHouchesEventHandler '" << eh.name() << "'. At least one of them "
      << "needs to have a Cuts object." << Exception::warning;

    Smax = cuts().SMax();
    Y = cuts().Y();
  }

  theCKKW = eh.CKKWHandler();

  if ( !partonExtractor() ) thePartonExtractor = eh.partonExtractor();
  if ( !partonExtractor() )  throw LesHouchesInitError()
    << "No PartonExtractor object was assigned to the LesHouchesReader '"
    << name() << "' nor was one assigned to the controlling "
    << "LesHouchesEventHandler '" << eh.name() << "'. At least one of them "
    << "needs to have a PartonExtractor object." << Exception::warning;

  open();

  Energy emax = 2.0*sqrt(heprup.EBMUP.first*heprup.EBMUP.second)*GeV;
  theCuts->initialize(sqr(emax),
		      0.5*log(heprup.EBMUP.first/heprup.EBMUP.second));
  if ( Smax > 0.0*GeV2 && ( Smax != cuts().SMax() || Y != cuts().Y() ) )
    throw LesHouchesInitError()
      << "The LesHouchesReader '" << name() << "' uses the same Cuts object "
      << "as another LesHouchesReader which has not got the same energies of "
      << "the colliding particles. For the generation to work properly "
      << "different LesHouchesReader object with different colliding particles "
      << "must be assigned different (although possibly identical) Cuts "
      << "objects." << Exception::warning;

  thePartonBins = partonExtractor()->getPartons(emax, inData, cuts());
  for ( int i = 0, N = partonBins().size(); i < N; ++i ) {
    theXCombs[partonBins()[i]] =
      new_ptr(XComb(emax, inData, &eh, partonExtractor(), CKKWHandler(),
		    partonBins()[i], theCuts));
    partonExtractor()->nDims(partonBins()[i]);
  }
  outPDF = make_pair(partonExtractor()->getPDF(inData.first),
		     partonExtractor()->getPDF(inData.second));
  close();
  scan();
  initStat();
}


long LesHouchesReader::scan() {
  heprup.NPRUP = 0;
  heprup.XSECUP.clear();
  heprup.XERRUP.clear();
  heprup.XMAXUP.clear();
  heprup.LPRUP.clear();
  
  open();

  // Shall we write the events to a cache file for fast reading? If so
  // we write to a temporary file if the caches events should be
  // randomized.
  if ( cacheFileName().length() ) openWriteCacheFile();

  // Use posi to remember the positions of the cached events on the
  // temporary stream (if present).
  vector<long> posi;

  // Keep track of the number of events scanned.
  long neve = 0;

  // If the open() has not already gotten information about subprocesses
  // and cross sections we have to scan through the events.
  if ( !heprup.NPRUP || cacheFile() != NULL ) {
    double xlast = 0.0;
    weighted(false);
    negativeWeights(false);
    for ( int i = 0; ( maxScan() < 0 || i < maxScan() ) && readEvent(); ++i ) {
      if ( !checkPartonBin() ) throw LesHouchesInitError()
	<< "Found event in LesHouchesReader '" << name()
	<< "' which cannot be handeled by the assigned PartonExtractor '"
	<< partonExtractor()->name() << "'." << Exception::runerror;
      if ( cacheFile() != NULL ) {
	// We are caching events. Remember where they were written in
	// case we want to randomize
	cacheEvent();
      }
      ++neve;
      vector<int>::iterator idit =
	find(heprup.LPRUP.begin(), heprup.LPRUP.end(), hepeup.IDPRUP);
      if ( idit == heprup.LPRUP.end() ) {
	++heprup.NPRUP;
	heprup.LPRUP.push_back(hepeup.IDPRUP);
	heprup.XSECUP.push_back(hepeup.XWGTUP);
	heprup.XERRUP.push_back(sqr(hepeup.XWGTUP));
	heprup.XMAXUP.push_back(abs(hepeup.XWGTUP));
      } else {
	int id = idit - heprup.LPRUP.begin();
	heprup.XSECUP[id] += hepeup.XWGTUP;
	heprup.XERRUP[id] += sqr(hepeup.XWGTUP);
	heprup.XMAXUP[id] = max(heprup.XMAXUP[id], abs(hepeup.XWGTUP));
      }
      if ( i == 0 ) xlast = hepeup.XWGTUP;
      if ( xlast != hepeup.XWGTUP ) weighted(true);
      if ( hepeup.XWGTUP < 0.0 ) negativeWeights(true);
    }
    if ( maxScan() < 0 || neve > NEvents() ) NEvents(neve);
    for ( int id = 0, N = heprup.LPRUP.size(); id < N; ++id ) {
      heprup.XSECUP[id] /= neve;
      heprup.XERRUP[id] = weighted()? sqrt(heprup.XERRUP[id])/neve: 0.0;
    }
  }

  if ( cacheFile() != NULL ) closeCacheFile();

  return neve;

}

void LesHouchesReader::initStat() {

  stats.reset();
  statmap.clear();
  if ( heprup.NPRUP <= 0 ) return;

  if ( !weighted() ) {
    double xsec = 0.0;
    for ( int ip = 0; ip < heprup.NPRUP; ++ip ) {
      xsec += heprup.XSECUP[ip];
      statmap[heprup.LPRUP[ip]] = XSecStat(heprup.XSECUP[ip]*picobarn);
    }
    stats.maxXSec(xsec*picobarn);
  } else {
    //     heprup.XSECUP.clear();
    //     heprup.XERRUP.clear();
    double sumx = 0.0;
    for ( int ip = 0; ip < heprup.NPRUP; ++ip ) {
      sumx += heprup.XMAXUP[ip];
      statmap[heprup.LPRUP[ip]] = XSecStat(heprup.XMAXUP[ip]*picobarn);
    }
    stats.maxXSec(sumx*picobarn);
  }
  maxFactor = 1.0;
}

void LesHouchesReader::increaseMaxXSec(CrossSection maxxsec) {
  for ( int i = 0; i < heprup.NPRUP; ++i )
    statmap[heprup.LPRUP[i]].maxXSec(statmap[heprup.LPRUP[i]].maxXSec()*
      maxxsec/stats.maxXSec());
  maxFactor *= maxxsec/stats.maxXSec();
  stats.maxXSec(maxxsec);
}

tXCombPtr LesHouchesReader::getXComb() {
  if ( lastXCombPtr() ) return lastXCombPtr();
  fillEvent();
  connectMothers();
  tcPBPair sel = createPartonBinInstances();
  theLastXComb = xCombs()[sel];
  lastXCombPtr()->subProcess(SubProPtr());
  lastXCombPtr()->setPartonBinInstances(partonBinInstances(),
					sqr(hepeup.SCALUP)*GeV2);
  lastXCombPtr()->lastAlphaS(hepeup.AQCDUP);
  lastXCombPtr()->lastAlphaEM(hepeup.AQEDUP);
  return lastXCombPtr();
}

tSubProPtr LesHouchesReader::getSubProcess() {
  getXComb();
  if ( subProcess() ) return subProcess();
  lastXCombPtr()->subProcess(new_ptr(SubProcess(lastPartons(), tCollPtr(), this)));
  subProcess()->setOutgoing(outgoing().begin(), outgoing().end());
  subProcess()->setIntermediates(intermediates().begin(),
				 intermediates().end());
  return subProcess();
}

void LesHouchesReader::fillEvent() {
  if ( !particleIndex.empty() ) return;
  particleIndex.clear();
  colourIndex.clear();
  colourIndex(0, tColinePtr());
  createParticles();
  createBeams();
}

void LesHouchesReader::reopen() {
  // If we didn't know how many events there were, we know now.
  if ( NEvents() <= 0 ) NEvents(position);
  ++reopened;
  // How large fraction of the events have we actually used? And how
  // large will we have used if we go through the file again?
  double frac = double(stats.attempts())/double(NEvents());
  if ( frac*double(reopened + 1)/double(reopened) > 1.0 &&
    NEvents() - stats.attempts() <
       generator()->N() - generator()->currentEventNumber() )
    generator()->logWarning(
      LesHouchesReopenWarning()
      << "Reopening LesHouchesReader '" << name()
      << "' after accessing " << stats.attempts() << " events out of "
      << NEvents() << Exception::warning);
  if ( cacheFile() != NULL ) {
    closeCacheFile();
    openReadCacheFile();
    if ( !uncacheEvent() ) throw LesHouchesReopenError()
      << "Could not reopen LesHouchesReader '" << name()
      << "'." << Exception::runerror;
  } else {  
    close();
    open();
    if ( !readEvent() ) throw LesHouchesReopenError()
      << "Could not reopen LesHouchesReader '" << name()
      << "'." << Exception::runerror;
  }
}

void LesHouchesReader::reset() {
  particleIndex.clear();
  colourIndex.clear();
  theLastXComb = tXCombPtr();
}

bool LesHouchesReader::readEvent() {

  reset();

  if ( !doReadEvent() ) return false;

  // If we are just skipping event we do not need to reweight or do
  // anything fancy.
  if ( skipping ) return true;

  // Reweight according to the re- and pre-weights objects in the
  // LesHouchesReader base class.
  hepeup.XWGTUP *= ( lastweight = reweight() );

  if ( !reweightPDF ) return true;
  // We should try to reweight the PDFs here.

  fillEvent();

  double x1 = incoming().first->momentum().plus()/
    beams().first->momentum().plus();

  if ( inPDF.first && outPDF.first && inPDF.first != outPDF.first ) {
    if ( hepeup.XPDWUP.first <= 0.0 )
      hepeup.XPDWUP.first =
	inPDF.first->xfx(inData.first, incoming().first->dataPtr(),
			 sqr(hepeup.SCALUP*GeV), x1);
    double xf = outPDF.first->xfx(inData.first, incoming().first->dataPtr(),
				  sqr(hepeup.SCALUP*GeV), x1);
    hepeup.XWGTUP *= xf/hepeup.XPDWUP.first;
    lastweight *= xf/hepeup.XPDWUP.first;
    hepeup.XPDWUP.first = xf;
  }

  double x2 = incoming().second->momentum().minus()/
    beams().second->momentum().minus();

  if ( inPDF.second && outPDF.second && inPDF.second != outPDF.second ) {
    if ( hepeup.XPDWUP.second <= 0.0 )
      hepeup.XPDWUP.second =
	inPDF.second->xfx(inData.second, incoming().second->dataPtr(),
			 sqr(hepeup.SCALUP*GeV), x2);
    double xf =
      outPDF.second->xfx(inData.second, incoming().second->dataPtr(),
			 sqr(hepeup.SCALUP*GeV), x2);
    hepeup.XWGTUP *= xf/hepeup.XPDWUP.second;
    lastweight *= xf/hepeup.XPDWUP.second;
    hepeup.XPDWUP.second = xf;
  }

  if ( !cuts().initSubProcess((incoming().first->momentum() +
			       incoming().second->momentum()).m2(),
			      0.5*log(x1/x2)) ) return false;

  return true;
}

double LesHouchesReader::getEvent() {
  if ( cacheFile() != NULL ) {
    if ( !uncacheEvent() ) reopen();
  } else {
    if ( !readEvent() ) reopen();
  }
  ++position;

  return weighted()?
    double(hepeup.XWGTUP*picobarn/statmap[hepeup.IDPRUP].maxXSec()):
    lastweight/maxFactor;
}

void LesHouchesReader::skip(long n) {
  HoldFlag<> skipflag(skipping);
  while ( n-- ) getEvent();
}

double LesHouchesReader::reweight() {
  preweight = 1.0;
  if ( reweights.empty() && preweights.empty() &&
       !( CKKWHandler() && maxMultCKKW() > 0 && maxMultCKKW() > minMultCKKW() ) )
    return 1.0;
  fillEvent();
  getSubProcess();
  for ( int i = 0, N = preweights.size(); i < N; ++i ) {
    preweights[i]->setXComb(lastXCombPtr());
    preweight *= preweights[i]->weight();
  }
  double weight = preweight;
  for ( int i = 0, N = reweights.size(); i < N; ++i ) {
    reweights[i]->setXComb(lastXCombPtr());
    weight *= reweights[i]->weight();
  }

  // If we are caching events we do not want to do CKKW reweighting.
  if ( cacheFile() != NULL ) return weight;

  if ( CKKWHandler() && maxMultCKKW() > 0 && maxMultCKKW() > minMultCKKW() ) {
    CKKWHandler()->setXComb(lastXCombPtr());
    weight *= CKKWHandler()->reweightCKKW(minMultCKKW(), maxMultCKKW());
  }
  return weight;
}

bool LesHouchesReader::checkPartonBin() {

  // First find the positions of the incoming partons.
  pair< vector<int>, vector<int> > inc;
  for ( int i = 0; i < hepeup.NUP; ++i ) {
    if ( hepeup.ISTUP[i] == -9 ) {
      if ( inc.first.empty() ) inc.first.push_back(i);
      else if ( inc.second.empty() ) inc.second.push_back(i);
    }
    else if ( hepeup.ISTUP[i] == -1 ) {
      if ( inc.first.size() &&
	   hepeup.MOTHUP[i].first == inc.first.back() + 1 )
	inc.first.push_back(i);
      else if ( inc.second.size() &&
		hepeup.MOTHUP[i].first == inc.second.back() + 1 )
	inc.second.push_back(i);
      else if ( inc.first.empty() ) {
	inc.first.push_back(-1);
	inc.first.push_back(i);
      }
      else if ( inc.second.empty() ) {
	inc.second.push_back(-1);
	inc.second.push_back(i);
      }
      else if ( inc.first.size() <= inc.second.size() )
	inc.first.push_back(i);
      else
	inc.second.push_back(i);
    }
  }

  // Now store the corresponding id numbers
  pair< vector<long>, vector<long> > ids;
  ids.first.push_back(inc.first[0] < 0? heprup.IDBMUP.first:
		      hepeup.IDUP[inc.first[0]]);
  for ( int i = 1, N = inc.first.size(); i < N; ++i )
    ids.first.push_back(hepeup.IDUP[inc.first[i]]);
  ids.second.push_back(inc.second[0] < 0? heprup.IDBMUP.second:
		       hepeup.IDUP[inc.second[0]]);
  for ( int i = 1, N = inc.second.size(); i < N; ++i )
    ids.second.push_back(hepeup.IDUP[inc.second[i]]);

  // Find the correct pair of parton bins.
  PBPair pbp;
  for ( int i = 0, N = partonBins().size(); i < N; ++i ) {
    tcPBPtr curr = partonBins()[i].first;
    int icurr = inc.first.size() - 1;
    while ( curr && icurr >= 0 ) {
      if ( curr->parton()->id () != ids.first[icurr] ) break;
      curr = curr->incoming();
      --icurr;
    }
    if ( curr || icurr >= 0 ) continue;

    curr = partonBins()[i].second;
    icurr = inc.second.size() - 1;
    while ( curr && icurr >= 0 ) {
      if ( curr->parton()->id () != ids.second[icurr] ) break;
      curr = curr->incoming();
      --icurr;
    }
    if ( curr || icurr >= 0 ) continue;

    pbp = partonBins()[i];
  }

  // If we are only checking we return here.
  return ( pbp.first && pbp.second );

}

tcPBPair LesHouchesReader::createPartonBinInstances() {
  tcPBPair sel;
  for ( int i = 0, N = partonBins().size(); i < N; ++i ) {
    tcPBPtr bin = partonBins()[i].first;
    tPPtr p = incoming().first;
    while ( bin && p ) {
      if ( p->dataPtr() != bin->parton() ) break;
      bin = bin->incoming();
      p = p->parents().size()? p->parents()[0]: tPPtr();
    }
    if ( bin || p ) continue;
    bin = partonBins()[i].second;
    p = incoming().second;
    while ( bin && p ) {
      if ( p->dataPtr() != bin->parton() ) break;
      bin = bin->incoming();
      p = p->parents().size()? p->parents()[0]: tPPtr();
    }
    if ( bin || p ) continue;
    sel = partonBins()[i];
    break;
  }
  if ( !sel.first || !sel.second ) throw LesHouchesInconsistencyError()
    << "Could not find appropriate PartonBin objects for event produced by "
    << "LesHouchesReader '" << name() << "'." << Exception::runerror;

  Direction<0> dir(true);
  thePartonBinInstances.first =
    new_ptr(PartonBinInstance(incoming().first, sel.first,
			      -sqr(hepeup.SCALUP*GeV)));
  if ( thePartonBinInstances.first->xi() > 1.00001 ) {
    Throw<LesHouchesInconsistencyError>()
      << "Found an event with momentum fraction larger than unity (x1="
      << thePartonBinInstances.first->xi()
      << "). The event will be skipped." << Exception::warning;
    throw Veto();
  }
  dir.reverse();
  thePartonBinInstances.second =
    new_ptr(PartonBinInstance(incoming().second, sel.second,
			      -sqr(hepeup.SCALUP*GeV)));

  if ( thePartonBinInstances.second->xi() > 1.00001 ) {
    Throw<LesHouchesInconsistencyError>()
      << "Found an event with momentum fraction larger than unity (x2="
      << thePartonBinInstances.second->xi()
      << "). The event will be skipped." << Exception::warning;
    throw Veto();
  }
  return sel;

}
		     

void LesHouchesReader::createParticles() {
  theBeams = PPair();
  theIncoming = PPair();
  theOutgoing = PVector();
  theIntermediates = PVector();
  set<int> oklines;
  oklines.insert(0);
  for ( int i = 0, N = hepeup.IDUP.size(); i < N; ++i ) {
    if ( !hepeup.IDUP[i] ) continue;
    Lorentz5Momentum mom(hepeup.PUP[i][0]*GeV, hepeup.PUP[i][1]*GeV,
			 hepeup.PUP[i][2]*GeV, hepeup.PUP[i][3]*GeV,
			 hepeup.PUP[i][4]*GeV);
    PPtr p = getParticleData(hepeup.IDUP[i])->produceParticle(mom);
    tColinePtr c = colourIndex(hepeup.ICOLUP[i].first);
    if ( c ) c->addColoured(p);
    c = colourIndex(hepeup.ICOLUP[i].second);
    if ( c ) c->addAntiColoured(p);

    // Check colour-line consistency.
    if ( ThePEG_DEBUG_LEVEL && abs(hepeup.ISTUP[i]) == 1 &&
	 oklines.find(hepeup.ICOLUP[i].first) == oklines.end() ) {
      bool ends = 0;
      for ( int j = i + 1; j < N; ++j ) {
	if ( abs(hepeup.ISTUP[j]) == 1 ) {
	  if ( hepeup.ICOLUP[j].first == hepeup.ICOLUP[i].first ) ++ends;
	  if ( hepeup.ICOLUP[j].second == hepeup.ICOLUP[i].first ) ends = -N;
	}
      }
      if ( ends != 1 ) Throw<LesHouchesInconsistencyError>()
	<< "LesHouchesReader '" << name() << "' found inconsistent colour "
	<< "flow in Les Houches common block structure. See colour line "
	<< hepeup.ICOLUP[i].first << " in event looking like:\n"
	<< hepeup << Exception::runerror;
      oklines.insert(hepeup.ICOLUP[i].first);
    }
    if ( ThePEG_DEBUG_LEVEL && abs(hepeup.ISTUP[i]) == 1 &&
	 oklines.find(hepeup.ICOLUP[i].second) == oklines.end() ) {
      bool ends = 0;
      for ( int j = i + 1; j < N; ++j ) {
	if ( abs(hepeup.ISTUP[j]) == 1 ) {
	  if ( hepeup.ICOLUP[j].second == hepeup.ICOLUP[i].second ) ++ends;
	  if ( hepeup.ICOLUP[j].first == hepeup.ICOLUP[i].second ) ends = -N;
	}
      }
      if ( ends != 1 ) Throw<LesHouchesInconsistencyError>()
	<< "LesHouchesReader '" << name() << "' found inconsistent colour "
	<< "flow in Les Houches common block structure. See colour line "
	<< hepeup.ICOLUP[i].second << " in event looking like:\n"
	<< hepeup << Exception::runerror;
      oklines.insert(hepeup.ICOLUP[i].second);
    }

    particleIndex(i + 1, p);
    switch ( hepeup.ISTUP[i] ) {
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
      else if ( particleIndex(theIncoming.first) == hepeup.MOTHUP[i].first )
	theIncoming.first = p;
      else if ( particleIndex(theIncoming.second) == hepeup.MOTHUP[i].first )
	theIncoming.second = p;
      else throw LesHouchesInconsistencyError()
	<< "To many incoming particles to hard subprocess in the "
	<< "LesHouchesReader '"	<< name() << "'." << Exception::runerror;
      p->scale(sqr(hepeup.SCALUP*GeV));
      break;
    case 1:
      theOutgoing.push_back(p);
      p->scale(sqr(hepeup.SCALUP*GeV));
      break;
    case -2:
    case 2:
    case 3:
      theIntermediates.push_back(p);
      break;
    default:
      throw LesHouchesInconsistencyError()
	<< "Unknown status code (" << hepeup.ISTUP[i]
	<< ") in the LesHouchesReader '" << name() << "'."
	<< Exception::runerror;
    }
  }
}

void LesHouchesReader::createBeams() {

  if ( !theBeams.first ) {
    theBeams.first = getParticleData(heprup.IDBMUP.first)->produceParticle();
    double m = theBeams.first->mass()/GeV;
    theBeams.first->set5Momentum
      (Lorentz5Momentum(0.0*GeV, 0.0*GeV,
			sqrt(sqr(heprup.EBMUP.first) - sqr(m))*GeV,
			heprup.EBMUP.first*GeV, m*GeV));
    hepeup.IDUP.push_back(heprup.IDBMUP.first);
    hepeup.ISTUP.push_back(-9);
    hepeup.MOTHUP.push_back(make_pair(0, 0));
    hepeup.ICOLUP.push_back(make_pair(0, 0));
    hepeup.VTIMUP.push_back(0.0);
    hepeup.SPINUP.push_back(0.0);
    particleIndex(hepeup.IDUP.size(), theBeams.first);
    hepeup.MOTHUP[particleIndex(theIncoming.first) - 1].first =
      hepeup.IDUP.size();
  }
  if ( !theBeams.second ) {
    theBeams.second = getParticleData(heprup.IDBMUP.second)->produceParticle();
    double m = theBeams.second->mass()/GeV;
    theBeams.second->set5Momentum
      (Lorentz5Momentum(0.0*GeV, 0.0*GeV,
			-sqrt(sqr(heprup.EBMUP.second) - sqr(m))*GeV,
			heprup.EBMUP.second*GeV, m*GeV));
    hepeup.IDUP.push_back(heprup.IDBMUP.second);
    hepeup.ISTUP.push_back(-9);
    hepeup.MOTHUP.push_back(make_pair(0, 0));
    hepeup.ICOLUP.push_back(make_pair(0, 0));
    hepeup.VTIMUP.push_back(0.0);
    hepeup.SPINUP.push_back(0.0);
    particleIndex(hepeup.IDUP.size(), theBeams.second);
    hepeup.MOTHUP[particleIndex(theIncoming.second) - 1].first =
      hepeup.IDUP.size();
  }
}

void LesHouchesReader::connectMothers() {
  const ObjectIndexer<long,Particle> & pi = particleIndex;
  for ( int i = 0, N = hepeup.IDUP.size(); i < N; ++i ) {
    if ( pi(hepeup.MOTHUP[i].first) ) 
      pi(hepeup.MOTHUP[i].first)->addChild(pi(i + 1));
    if ( pi(hepeup.MOTHUP[i].second) && hepeup.MOTHUP[i].second != hepeup.MOTHUP[i].first) 
      pi(hepeup.MOTHUP[i].second)->addChild(pi(i + 1));
  }
}

bool LesHouchesReader::compressedCache() const {
#ifdef ThePEG_GZREAD_FILE
#ifdef ThePEG_GZWRITE_FILE
  return cacheFileName().length() > 3 &&
    cacheFileName().substr(cacheFileName().length()-3,3) == ".gz";
#else
  return false;
#endif
#else
  return false;
#endif
}

void LesHouchesReader::openReadCacheFile() {
  if ( cacheFile() != NULL ) closeCacheFile();
  if ( compressedCache() ) {
    string cmd = ThePEG_GZREAD_FILE " " + cacheFileName();
    theCacheFile = popen(cmd.c_str(), "r");
  } else {
    theCacheFile = fopen(cacheFileName().c_str(), "r");
  }
  position = 0;
}

void LesHouchesReader::openWriteCacheFile() {
  if ( cacheFile() != NULL ) closeCacheFile();
  if ( compressedCache() ) {
    string cmd = ThePEG_GZWRITE_FILE " " + cacheFileName();
    theCacheFile = popen(cmd.c_str(), "w");
  } else {
    theCacheFile = fopen(cacheFileName().c_str(), "w");
  }
}

void LesHouchesReader::closeCacheFile() {
  if ( compressedCache() ) pclose(cacheFile());
  else fclose(cacheFile());
  theCacheFile = NULL;
}

void LesHouchesReader::cacheEvent() const {
  static vector<char> buff;
  fwrite(&hepeup.NUP, sizeof(hepeup.NUP), 1, cacheFile());
  buff.resize(eventSize(hepeup.NUP));
  char * pos = &buff[0];
  pos = mwrite(pos, hepeup.IDPRUP);
  pos = mwrite(pos, hepeup.XWGTUP);
  pos = mwrite(pos, hepeup.XPDWUP);
  pos = mwrite(pos, hepeup.SCALUP);
  pos = mwrite(pos, hepeup.AQEDUP);
  pos = mwrite(pos, hepeup.AQCDUP);
  pos = mwrite(pos, hepeup.IDUP[0], hepeup.NUP);
  pos = mwrite(pos, hepeup.ISTUP[0], hepeup.NUP);
  pos = mwrite(pos, hepeup.MOTHUP[0], hepeup.NUP);
  pos = mwrite(pos, hepeup.ICOLUP[0], hepeup.NUP);
  for ( int i = 0; i < hepeup.NUP; ++i )
    pos = mwrite(pos, hepeup.PUP[i][0], 5);
  pos = mwrite(pos, hepeup.VTIMUP[0], hepeup.NUP);
  pos = mwrite(pos, hepeup.SPINUP[0], hepeup.NUP);
  pos = mwrite(pos, lastweight);
  fwrite(&buff[0], buff.size(), 1, cacheFile());
}

bool LesHouchesReader::uncacheEvent() {
  static vector<char> buff;
  if ( fread(&hepeup.NUP, sizeof(hepeup.NUP), 1, cacheFile()) != 1 )
    return false;
  buff.resize(eventSize(hepeup.NUP));
  if ( fread(&buff[0], buff.size(), 1, cacheFile()) != 1 ) return false;
  const char * pos = &buff[0];
  pos = mread(pos, hepeup.IDPRUP);
  pos = mread(pos, hepeup.XWGTUP);
  pos = mread(pos, hepeup.XPDWUP);
  pos = mread(pos, hepeup.SCALUP);
  pos = mread(pos, hepeup.AQEDUP);
  pos = mread(pos, hepeup.AQCDUP);
  hepeup.IDUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.IDUP[0], hepeup.NUP);
  hepeup.ISTUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.ISTUP[0], hepeup.NUP);
  hepeup.MOTHUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.MOTHUP[0], hepeup.NUP);
  hepeup.ICOLUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.ICOLUP[0], hepeup.NUP);
  hepeup.PUP.resize(hepeup.NUP, vector<double>(5));
  for ( int i = 0; i < hepeup.NUP; ++i ) 
    pos = mread(pos, hepeup.PUP[i][0], 5);
  hepeup.VTIMUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.VTIMUP[0], hepeup.NUP);
  hepeup.SPINUP.resize(hepeup.NUP);
  pos = mread(pos, hepeup.SPINUP[0], hepeup.NUP);
  pos = mread(pos, lastweight);

  // If we are skipping, we do not have to do anything else.
  if ( skipping ) return true;

  if ( CKKWHandler() && maxMultCKKW() > 0 && maxMultCKKW() > minMultCKKW() ) {
    // The cached event has not been submitted to CKKW reweighting, so
    // we do that now.
    fillEvent();
    getSubProcess();
    CKKWHandler()->setXComb(lastXCombPtr());
    double weight = CKKWHandler()->reweightCKKW(minMultCKKW(), maxMultCKKW());
    hepeup.XWGTUP *= weight;
    lastweight *= weight;
  }
  return true;
}

void LesHouchesReader::persistentOutput(PersistentOStream & os) const {
  os << heprup.IDBMUP << heprup.EBMUP << heprup.PDFGUP << heprup.PDFSUP
     << heprup.IDWTUP << heprup.NPRUP << heprup.XSECUP << heprup.XERRUP
     << heprup.XMAXUP << heprup.LPRUP << hepeup.NUP << hepeup.IDPRUP
     << hepeup.XWGTUP << hepeup.XPDWUP << hepeup.SCALUP << hepeup.AQEDUP
     << hepeup.AQCDUP << hepeup.IDUP << hepeup.ISTUP << hepeup.MOTHUP
     << hepeup.ICOLUP << hepeup.PUP << hepeup.VTIMUP << hepeup.SPINUP
     << inData << inPDF << outPDF << thePartonExtractor << theCKKW
     << thePartonBins << theXCombs << theCuts << theNEvents << position
     << reopened << theMaxScan << isActive << isWeighted << hasNegativeWeights
     << theCacheFileName << stats << statmap << thePartonBinInstances
     << theBeams << theIncoming << theOutgoing << theIntermediates
     << reweights << preweights << preweight << reweightPDF << doInitPDFs
     << theLastXComb << theMaxMultCKKW << theMinMultCKKW << lastweight
     << maxFactor;
}

void LesHouchesReader::persistentInput(PersistentIStream & is, int) {
  if ( cacheFile() ) closeCacheFile();
  is >> heprup.IDBMUP >> heprup.EBMUP >> heprup.PDFGUP >> heprup.PDFSUP
     >> heprup.IDWTUP >> heprup.NPRUP >> heprup.XSECUP >> heprup.XERRUP
     >> heprup.XMAXUP >> heprup.LPRUP >> hepeup.NUP >> hepeup.IDPRUP
     >> hepeup.XWGTUP >> hepeup.XPDWUP >> hepeup.SCALUP >> hepeup.AQEDUP
     >> hepeup.AQCDUP >> hepeup.IDUP >> hepeup.ISTUP >> hepeup.MOTHUP
     >> hepeup.ICOLUP >> hepeup.PUP >> hepeup.VTIMUP >> hepeup.SPINUP
     >> inData >> inPDF >> outPDF >> thePartonExtractor >> theCKKW
     >> thePartonBins >> theXCombs >> theCuts >> theNEvents >> position
     >> reopened >> theMaxScan >> isActive >> isWeighted >> hasNegativeWeights
     >> theCacheFileName >> stats >> statmap >> thePartonBinInstances
     >> theBeams >> theIncoming >> theOutgoing >> theIntermediates
     >> reweights >> preweights >> preweight >> reweightPDF >> doInitPDFs
     >> theLastXComb >> theMaxMultCKKW >> theMinMultCKKW >> lastweight
     >> maxFactor;
}

AbstractClassDescription<LesHouchesReader>
LesHouchesReader::initLesHouchesReader;
// Definition of the static class description member.

void LesHouchesReader::setBeamA(long id) { heprup.IDBMUP.first = id; }
long LesHouchesReader::getBeamA() const { return heprup.IDBMUP.first; }
void LesHouchesReader::setBeamB(long id) { heprup.IDBMUP.second = id; }
long LesHouchesReader::getBeamB() const { return heprup.IDBMUP.second; }
void LesHouchesReader::setEBeamA(Energy e) { heprup.EBMUP.first = e/GeV; }
Energy LesHouchesReader::getEBeamA() const { return heprup.EBMUP.first*GeV; }
void LesHouchesReader::setEBeamB(Energy e) { heprup.EBMUP.second = e/GeV; }
Energy LesHouchesReader::getEBeamB() const { return heprup.EBMUP.second*GeV; }
void LesHouchesReader::setPDFA(PDFPtr pdf) { inPDF.first = pdf; }
PDFPtr LesHouchesReader::getPDFA() const { return inPDF.first; }
void LesHouchesReader::setPDFB(PDFPtr pdf) { inPDF.second = pdf; }
PDFPtr LesHouchesReader::getPDFB() const { return inPDF.second; }

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
     0, true, false, true, true, false,
     &LesHouchesReader::setPDFA, &LesHouchesReader::getPDFA, 0);

  static Reference<LesHouchesReader,PDFBase> interfacePDFB
    ("PDFB",
     "The PDF used for incoming particle along the negative z-axis. "
     "If null the corresponding information is to be deduced from the "
     "event stream/file.",
     0, true, false, true, true, false,
     &LesHouchesReader::setPDFB, &LesHouchesReader::getPDFB, 0);

  static Parameter<LesHouchesReader,long> interfaceMaxScan
    ("MaxScan",
     "The maximum number of events to scan to obtain information about "
     "processes and cross section in the intialization.",
     &LesHouchesReader::theMaxScan, -1, 0, 0,
     true, false, false);


  static Parameter<LesHouchesReader,string> interfaceCacheFileName
    ("CacheFileName",
     "Name of file used to cache the events form the reader in a fast-readable "
     "form. If empty, no cache file will be generated.",
     &LesHouchesReader::theCacheFileName, "",
     true, false);
  interfaceCacheFileName.fileType();

  static Reference<LesHouchesReader,PartonExtractor> interfacePartonExtractor
    ("PartonExtractor",
     "The PartonExtractor object used to construct remnants. If no object is "
     "provided the LesHouchesEventHandler object must provide one instead.",
     &LesHouchesReader::thePartonExtractor, true, false, true, true, false);


  static Reference<LesHouchesReader,Cuts> interfaceCuts
    ("Cuts",
     "The Cuts object to be used for this reader. Note that these "
     "must not be looser cuts than those used in the actual generation. "
     "If no object is provided the LesHouchesEventHandler object must "
     "provide one instead.",
     &LesHouchesReader::theCuts, true, false, true, true, false);

  static RefVector<LesHouchesReader,ReweightBase> interfaceReweights
    ("Reweights",
     "A list of ThePEG::ReweightBase objects to modify this the weight of "
     "this reader.",
     &LesHouchesReader::reweights, 0, false, false, true, false);

  static RefVector<LesHouchesReader,ReweightBase> interfacePreweights
    ("Preweights",
     "A list of ThePEG::ReweightBase objects to bias the phase space for this "
     "reader without influencing the actual cross section.",
     &LesHouchesReader::preweights, 0, false, false, true, false);

  static Switch<LesHouchesReader,bool> interfaceReweightPDF
    ("ReweightPDF",
     "If the PDFs used in the generation for this reader is different "
     "from the ones assumed by the associated PartonExtractor object, "
     "should the events be reweighted to fit the latter?",
     &LesHouchesReader::reweightPDF, false, true, false);
  static SwitchOption interfaceReweightPDFNo
    (interfaceReweightPDF, "No", "The event weights are kept as they are.",
     false);
  static SwitchOption interfaceReweightPDFYes
    (interfaceReweightPDF,
     "Yes", "The events are reweighted.", true);

  static Switch<LesHouchesReader,bool> interfaceInitPDFs
    ("InitPDFs",
     "If no PDFs were specified in <interface>PDFA</interface> or "
     "<interface>PDFB</interface>for this reader, try to extract the "
     "information from the event file and assign the relevant PDFBase"
     "objects when the reader is initialized.",
     &LesHouchesReader::doInitPDFs, false, true, false);
  static SwitchOption interfaceInitPDFsYes
    (interfaceInitPDFs,
     "Yes",
     "Extract PDFs during initialization.",
     true);
  static SwitchOption interfaceInitPDFsNo
    (interfaceInitPDFs,
     "No",
     "Do not extract PDFs during initialization.",
     false);

  static Parameter<LesHouchesReader,int> interfaceMaxMultCKKW
    ("MaxMultCKKW",
     "If this reader is to be used (possibly together with others) for CKKW-"
     "reweighting and veto, this should give the multiplicity of outgoing "
     "particles in the highest multiplicity matrix element in the group. "
     "If set to zero, no CKKW procedure should be applied.",
     &LesHouchesReader::theMaxMultCKKW, 0, 0, 0,
     true, false, Interface::lowerlim);

  static Parameter<LesHouchesReader,int> interfaceMinMultCKKW
    ("MinMultCKKW",
     "If this reader is to be used (possibly together with others) for CKKW-"
     "reweighting and veto, this should give the multiplicity of outgoing "
     "particles in the lowest multiplicity matrix element in the group. If "
     "larger or equal to <interface>MaxMultCKKW</interface>, no CKKW "
     "procedure should be applied.",
     &LesHouchesReader::theMinMultCKKW, 0, 0, 0,
     true, false, Interface::lowerlim);

  interfaceCuts.rank(8);
  interfacePartonExtractor.rank(7);
  interfaceBeamA.rank(5);
  interfaceBeamB.rank(4);
  interfaceEBeamA.rank(3);
  interfaceEBeamB.rank(2);
  interfaceMaxMultCKKW.rank(1.5);
  interfaceMinMultCKKW.rank(1.0);

}

namespace ThePEG {

ostream & operator<<(ostream & os, const HEPEUP & h) {
  os << "<event>\n"
     << " " << setw(4) << h.NUP
     << " " << setw(6) << h.IDPRUP
     << " " << setw(14) << h.XWGTUP
     << " " << setw(14) << h.SCALUP
     << " " << setw(14) << h.AQEDUP
     << " " << setw(14) << h.AQCDUP << "\n";

  for ( int i = 0; i < h.NUP; ++i )
    os << " " << setw(8) << h.IDUP[i]
       << " " << setw(2) << h.ISTUP[i]
       << " " << setw(4) << h.MOTHUP[i].first
       << " " << setw(4) << h.MOTHUP[i].second
       << " " << setw(4) << h.ICOLUP[i].first
       << " " << setw(4) << h.ICOLUP[i].second
       << " " << setw(14) << h.PUP[i][0]
       << " " << setw(14) << h.PUP[i][1]
       << " " << setw(14) << h.PUP[i][2]
       << " " << setw(14) << h.PUP[i][3]
       << " " << setw(14) << h.PUP[i][4]
       << " " << setw(1) << h.VTIMUP[i]
       << " " << setw(1) << h.SPINUP[i] << std::endl;
  os << "</event>" << std::endl;
  return os;
}

}

