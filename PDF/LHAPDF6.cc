// -*- C++ -*-
//
// LHAPDF.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the LHAPDF class.
//

#include "LHAPDF6.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Command.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/PDT/EnumParticles.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Utilities/EnumIO.h"
#include "ThePEG/Utilities/Debug.h"
#include "ThePEG/Utilities/Throw.h"
#include "config.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "LHAPDF/LHAPDF.h"

using std::vector;
using std::string;
using std::pair;

using ThePEG::GeV2;
using ThePEG::cPDVector;

#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/EnumParticles.h"

ThePEG::LHAPDF::LHAPDF()
  : thePDF(), thePDFName("cteq6l1"), 
    theMember(0),
    enablePartonicGamma(false),
    theVerboseLevel(0), theMaxFlav(5),
    lastQ2(-1.0*GeV2), lastX(-1.0), lastP2(-1.0*GeV2),
    xMin(0.0), xMax(1.0), Q2Min(ZERO), Q2Max(Constants::MaxEnergy2) {}

ThePEG::LHAPDF::LHAPDF(const LHAPDF & x)
  : PDFBase(x), 
    thePDF(), thePDFName(x.thePDFName), 
    theMember(x.theMember),
    enablePartonicGamma(false),
    theVerboseLevel(x.theVerboseLevel), theMaxFlav(x.theMaxFlav),
    lastQ2(-1.0*GeV2), lastX(-1.0), lastP2(-1.0*GeV2),
    xMin(x.xMin), xMax(x.xMax), Q2Min(x.Q2Min), Q2Max(x.Q2Max) {}

ThePEG::IBPtr ThePEG::LHAPDF::clone() const {
  return new_ptr(*this);
}

ThePEG::IBPtr ThePEG::LHAPDF::fullclone() const {
  return new_ptr(*this);
}

void ThePEG::LHAPDF::doinit() {
  PDFBase::doinit();
  thePDF = ::LHAPDF::mkPDF(thePDFName, theMember);
  xMin = thePDF->xMin();
  xMax = thePDF->xMax();
  Q2Min = thePDF->q2Min() * GeV2;
  Q2Max = thePDF->q2Max() * GeV2;
}

void ThePEG::LHAPDF::dofinish() {
  PDFBase::dofinish();
  delete thePDF;
  thePDF = 0;
}

void ThePEG::LHAPDF::doinitrun() {
  PDFBase::doinitrun();
  thePDF = ::LHAPDF::mkPDF(thePDFName, theMember);
  xMin = thePDF->xMin();
  xMax = thePDF->xMax();
  Q2Min = thePDF->q2Min() * GeV2;
  Q2Max = thePDF->q2Max() * GeV2;
}

void ThePEG::LHAPDF::setPDFName(string name) {
  if ( ::LHAPDF::endswith(name, ".LHgrid") ) {
  	name = name.substr(0, name.size() - 7);
  }
  else if ( ::LHAPDF::endswith(name, ".LHpdf") ) {
  	name = name.substr(0, name.size() - 6);
  }


  if ( ::LHAPDF::contains(::LHAPDF::availablePDFSets(), name) ) {
    thePDFName = name;
    theMember = 0;
  }
  else {
    Throw<ThePEG::LHAPDF::NotInstalled>()
    	<< "'set " << fullName() << ":PDFName "
    	<< name << "': PDF not installed. Try 'lhapdf install'.\n"
    	<< Exception::setuperror;
  }
}

void ThePEG::LHAPDF::setMember(int member) {
  try {
    ::LHAPDF::PDFInfo * test = 
  	::LHAPDF::mkPDFInfo(thePDFName, member);
    if ( test )
      theMember = member;
  }
  catch (::LHAPDF::ReadError & e) {
   Throw<ThePEG::LHAPDF::NotInstalled>()
    	<< e.what() << Exception::setuperror;
  }
}

string ThePEG::LHAPDF::doTest(string input) {
  double x = 0;
  Energy2 Q2 = ZERO;
  Energy2 P2 = ZERO;
  istringstream is(input);
  is >> x >> iunit(Q2, GeV2) >> iunit(P2, GeV2);
  checkUpdate(x, Q2, P2);
  ostringstream os;
  for ( int i = 0; i < 13; ++i ) os << " " << lastXF[i];
  return os.str();
}  

void ThePEG::LHAPDF::checkUpdate(double x, Energy2 Q2, Energy2 P2) const {
  if ( x == lastX && Q2 == lastQ2 && P2 == lastP2 ) return;
  lastX = x;
  lastQ2 = Q2;
  lastP2 = P2;

  assert ( thePDF );

  if ( ! thePDF->inRangeXQ2(x, Q2/GeV2) ) {
      switch ( rangeException ) {
      case rangeThrow: Throw<Exception>()
	<< "Momentum fraction (x=" << x << ") or scale (Q2=" << double(Q2/GeV2)
	<< " GeV^2) was outside of limits in PDF " << name() << "."
	<< Exception::eventerror;
	break;
      case rangeZero:
	lastXF = vector<double>(13, 0.0);
	return;
      case rangeFreeze:
	lastX = x = min(max(x, xMin), xMax);
	lastQ2 = Q2 = min(max(Q2, Q2Min), Q2Max);
      }
  } 

  thePDF->xfxQ2(x, Q2/GeV2, lastXF);

}

bool ThePEG::LHAPDF::canHandleParticle(tcPDPtr particle) const {
  using namespace ParticleID;
//  switch ( ptype() ) {
//  case nucleonType:
    return abs(particle->id()) == pplus || abs(particle->id()) == n0;
//  case pionType:
//    return particle->id() == pi0 || particle->id() == ParticleID::gamma;
//  case photonType:
//    return particle->id() == ParticleID::gamma;
//  default:
//    return false;
// }
}

cPDVector ThePEG::LHAPDF::partons(tcPDPtr particle) const {
  // We assume that all standard partons can be extracted.
  const ::LHAPDF::PDFSet & pdfset = ::LHAPDF::getPDFSet(thePDFName);
  const vector<int> & flavs = 
    pdfset.get_entry_as< vector<int> >("Flavors");

  assert( !flavs.empty() );

  cPDVector ret;
  ret.reserve( flavs.size() );
  if ( canHandleParticle(particle) ) {
    for ( size_t i=0; i < flavs.size(); ++i ) {
      ret.push_back(getParticleData(flavs[i]));
    }
    // special if needed add photon
    if(enablePartonicGamma) 
      ret.push_back(getParticleData(ParticleID::gamma));
  }
  assert( ret.size() == flavs.size() );
  return ret;
}

namespace LHAPDFIndex {
enum VectorIndices {
  topb = 0, botb = 1, chab = 2, strb = 3, upb = 4, dowb = 5, glu = 6, dow = 7,
  up = 8, str = 9, cha = 10, bot = 11, top = 12, photon = 13 };
}

double ThePEG::LHAPDF::xfx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
                      double x, double, Energy2 particleScale) const {
  // Here we should return the actual density.
  using namespace ThePEG::ParticleID;
  using namespace LHAPDFIndex;
  checkUpdate(x, partonScale, particleScale);
  switch ( parton->id() ) {
  case t:
    return maxFlav() < 6? 0.0: lastXF[top];
  case tbar:
    return maxFlav() < 6? 0.0: lastXF[topb];
  case b:
    return maxFlav() < 5? 0.0: lastXF[bot];
  case bbar:
    return maxFlav() < 5? 0.0: lastXF[botb];
  case c:
    return maxFlav() < 4? 0.0: lastXF[cha];
  case cbar:
    return maxFlav() < 4? 0.0: lastXF[chab];
  case ParticleID::s:
    return lastXF[str];
  case sbar:
    return lastXF[strb];
  case u:
    switch ( particle->id() ) {
    case n0: return lastXF[dow];
    case pbarminus: return lastXF[upb];
    case nbar0: return lastXF[dowb];
    case pplus:
    default: return lastXF[up];
    }
  case ubar:
    switch ( particle->id() ) {
    case n0: return lastXF[dowb];
    case pbarminus: return lastXF[up];
    case nbar0: return lastXF[dow];
    case pplus:
    default: return lastXF[upb];
    }
  case d:
    switch ( particle->id() ) {
    case n0: return lastXF[up];
    case pbarminus: return lastXF[dowb];
    case nbar0: return lastXF[upb];
    case pplus:
    default: return lastXF[dow];
    }
  case dbar:
    switch ( particle->id() ) {
    case n0: return lastXF[upb];
    case pbarminus: return lastXF[dow];
    case nbar0: return lastXF[up];
    case pplus:
    default: return lastXF[dowb];
    }
  case ParticleID::g:
    return lastXF[glu];
  case ParticleID::gamma:
    return enablePartonicGamma ? lastXF[photon] : 0.;
  }
  return 0.0;
}

double ThePEG::LHAPDF::xfvl(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double l, Energy2 particleScale) const {
  using Math::exp1m;
  return xfvx(particle, parton, partonScale, exp(-l), exp1m(-l), particleScale);
}

double ThePEG::LHAPDF::xfvx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		     double x, double, Energy2 particleScale) const {
  // Here we should return the actual valence density. This will only
  // work properly for nucleons
  using namespace ThePEG::ParticleID;
  using namespace LHAPDFIndex;
  checkUpdate(x, partonScale, particleScale);

  switch ( parton->id() ) {
  case t:
  case tbar:
  case b:
  case bbar:
  case c:
  case cbar:
  case ParticleID::s:
  case sbar:
  case ParticleID::gamma:
    return 0.0;
  case u:
    switch ( particle->id() ) {
    case n0: return lastXF[dow] - lastXF[dowb];
    case pbarminus: return 0.0;
    case nbar0: return 0.0;
    case pplus: return lastXF[up] - lastXF[upb];
    default: return 0.0;
    }
  case ubar:
    switch ( particle->id() ) {
    case n0: return 0.0;
    case pbarminus: return lastXF[up] - lastXF[upb];
    case nbar0: return lastXF[dow] - lastXF[dowb];
    case pplus:
    default: return 0.0;
    }
  case d:
    switch ( particle->id() ) {
    case n0: return lastXF[up] - lastXF[upb];
    case pbarminus: return 0.0;
    case nbar0: return 0.0;
    case pplus: return lastXF[dow] - lastXF[dowb];
    default: return 0.0;
    }
  case dbar:
    switch ( particle->id() ) {
    case n0: return 0.0;
    case pbarminus: return lastXF[dow] - lastXF[dowb];
    case nbar0: return lastXF[up] - lastXF[upb];
    case pplus:
    default: return 0.0;
    }
  case ParticleID::g:
    return 0.0;
  }
  return 0.0;
}

double ThePEG::LHAPDF::xfsx(tcPDPtr particle, tcPDPtr parton, Energy2 partonScale,
		    double x, double, Energy2 particleScale) const {
  // Here we should return the actual density.
  using namespace ThePEG::ParticleID;
  using namespace LHAPDFIndex;
  checkUpdate(x, partonScale, particleScale);

  switch ( parton->id() ) {
  case t:
    return maxFlav() < 6? 0.0: lastXF[top];
  case tbar:
    return maxFlav() < 6? 0.0: lastXF[topb];
  case b:
    return maxFlav() < 5? 0.0: lastXF[bot];
  case bbar:
    return maxFlav() < 5? 0.0: lastXF[botb];
  case c:
    return maxFlav() < 4? 0.0: lastXF[cha];
  case cbar:
    return maxFlav() < 4? 0.0: lastXF[chab];
  case ParticleID::s:
    return lastXF[str];
  case sbar:
    return lastXF[strb];
  case u:
    switch ( particle->id() ) {
    case n0: return lastXF[dowb];
    case pbarminus: return lastXF[upb];
    case nbar0: return lastXF[dowb];
    case pplus: return lastXF[upb];
    default: return lastXF[up];
    }
  case ubar:
    switch ( particle->id() ) {
    case n0: return lastXF[dowb];
    case pbarminus: return lastXF[upb];
    case nbar0: return lastXF[dowb];
    case pplus: return lastXF[upb];
    default: return lastXF[upb];
    }
  case d:
    switch ( particle->id() ) {
    case n0: return lastXF[upb];
    case pbarminus: return lastXF[dowb];
    case nbar0: return lastXF[upb];
    case pplus: return lastXF[dowb];
    default: return lastXF[dow];
    }
  case dbar:
    switch ( particle->id() ) {
    case n0: return lastXF[upb];
    case pbarminus: return lastXF[dowb];
    case nbar0: return lastXF[upb];
    case pplus: return lastXF[dowb];
    default: return lastXF[dowb];
    }
  case ParticleID::g:
    return lastXF[glu];
  case ParticleID::gamma:
    return enablePartonicGamma ? lastXF[photon] : 0.;
  }
  return 0.0;
}

void ThePEG::LHAPDF::persistentOutput(PersistentOStream & os) const {
  os << thePDFName << theMember 
     << theVerboseLevel << theMaxFlav
     << xMin << xMax << ounit(Q2Min, GeV2) << ounit(Q2Max, GeV2);
}

void ThePEG::LHAPDF::persistentInput(PersistentIStream & is, int) {
  is >> thePDFName >> theMember
     >> theVerboseLevel >> theMaxFlav
     >> xMin >> xMax >> iunit(Q2Min, GeV2) >> iunit(Q2Max, GeV2);
  lastQ2 = -1.0*GeV2;
  lastX = -1.0;
  lastP2 = -1.0*GeV2;
}

ThePEG::ClassDescription<ThePEG::LHAPDF> ThePEG::LHAPDF::initLHAPDF;
// Definition of the static class description member.

void ThePEG::LHAPDF::Init() {

  static ClassDocumentation<LHAPDF> documentation
    ("The LHAPDF class inherits from PDFBase and implements an interface "
     "to the LHAPDF library of parton density function parameterizations. "
     "This class is available even if LHAPDF was not properly installed "
     "when ThePEG was installed, but will then produce an error in the "
     "initialization. Note that the valence densities from the xfvx() and "
     "xfvl() function will only work properly for nucleons. All other "
     "particles will have zero valence densities.");

  static Parameter<LHAPDF,string> interfacePDFName
    ("PDFName",
     "The name of the PDF set to be used. Should correspond to "
     "the LHAPDF v6 name.",
     &ThePEG::LHAPDF::thePDFName, "cteq6l1", true, false,
     &ThePEG::LHAPDF::setPDFName);

  static Parameter<LHAPDF,int> interfaceMember
    ("Member",
     "The chosen member of the selected PDF set.",
     &ThePEG::LHAPDF::theMember, 0, 0, 0, 
     true, false, Interface::lowerlim,
     &ThePEG::LHAPDF::setMember);

  static Command<LHAPDF> interfaceTest
    ("Test",
     "Write out the values of the chosen PDF set using the x, Q2 and P2 "
     "parameters supplied.",
     &ThePEG::LHAPDF::doTest, true);


  static Switch<LHAPDF,int> interfaceVerboseLevel
    ("VerboseLevel",
     "The verbosity of the output from the LHAPDF library.",
     &ThePEG::LHAPDF::theVerboseLevel, 0, true, false);
  static SwitchOption interfaceVerboseLevelSilent
    (interfaceVerboseLevel,
     "Silent",
     "Trying to inhibit all output from the LHAPDF library "
     "(unfortunately not always possible).",
     0);
  static SwitchOption interfaceVerboseLevelNormal
    (interfaceVerboseLevel,
     "Normal",
     "Normal output from the LHAPDF library "
     "(unfortunately to the standard output).",
     1);
  interfaceVerboseLevel.setHasDefault(false);

  static Parameter<LHAPDF,int> interfaceMaxFlav
    ("MaxFlav",
     "The maximum number of flavours for which non-zero densities are "
     "reported. The actual number of flavours may be less depending on "
     "the chosen PDF set.",
     &ThePEG::LHAPDF::theMaxFlav, 5, 3, 0,
     true, false, Interface::lowerlim);

  interfacePDFName.rank(9);
  interfaceMember.rank(8);

}

