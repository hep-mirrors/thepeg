// -*- C++ -*-
//
// JetRegion.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2012 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the JetRegion class.
//

#include "JetRegion.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/ParVector.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Repository/CurrentGenerator.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

JetRegion::JetRegion()
  : thePtMin(0.*GeV), thePtMax(Constants::MaxEnergy),
    theYMin(-Constants::MaxRapidity), theYMax(Constants::MaxRapidity),
    theEtaMin(-Constants::MaxRapidity), theEtaMax(Constants::MaxRapidity),
    theDidMatch(false), theLastNumber(0) {}

JetRegion::~JetRegion() {}

IBPtr JetRegion::clone() const {
  return new_ptr(*this);
}

IBPtr JetRegion::fullclone() const {
  return new_ptr(*this);
}

void JetRegion::describe() const {

  CurrentGenerator::log()
    << "JetRegion '" << name() << "' matching ";
  if ( accepts().empty() )
    CurrentGenerator::log() << "any jets ";
  else {
    CurrentGenerator::log() << "jets ";
    for ( vector<int>::const_iterator k = accepts().begin();
	  k != accepts().end(); ++k ) {
      CurrentGenerator::log() << "#" << *k;
      if ( k != --accepts().end() )
	CurrentGenerator::log() << ", ";
      else
	CurrentGenerator::log() << " ";
    }
  }
  CurrentGenerator::log() << " within:\n";

  CurrentGenerator::log() 
    << "pt  = " << ptMin()/GeV << " .. " << ptMax()/GeV << " GeV\n"
    << "y   = " << yMin() << " .. " << yMax() << "\n"
    << "eta   = " << etaMin() << " .. " << etaMax() << "\n";

}

bool JetRegion::matches(int n, const LorentzMomentum& p) {

  // one jet region can only contain one jet
  if ( didMatch() )
    return false;

  if ( find(accepts().begin(),accepts().end(),n) == accepts().end() )
    return false;

  if ( p.perp() < ptMin() || p.perp() > ptMax() ||
       p.rapidity() < yMin() || p.rapidity() > yMax() ||
       p.eta() < etaMin() || p.eta() > etaMax() )
    return false;

  theDidMatch = true;
  theLastNumber = n;
  theLastMomentum = p;

  return true;

}

// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void JetRegion::persistentOutput(PersistentOStream & os) const {
  os << ounit(thePtMin,GeV) << ounit(thePtMax,GeV)
     << theYMin << theYMax 
     << theEtaMin << theEtaMax 
     << theAccepts;
}

void JetRegion::persistentInput(PersistentIStream & is, int) {
  is >> iunit(thePtMin,GeV) >> iunit(thePtMax,GeV)
     >> theYMin >> theYMax 
     >> theEtaMin >> theEtaMax 
     >> theAccepts;
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<JetRegion,HandlerBase>
  describeThePEGJetRegion("ThePEG::JetRegion", "JetCuts.so");

void JetRegion::Init() {

  static ClassDocumentation<JetRegion> documentation
    ("JetRegion implements the requirement of finding a jet inside a "
     "given range of transverse momenta, and (pseudo-)rapidity.");

  static Parameter<JetRegion,Energy> interfacePtMin
    ("PtMin",
     "The minimum pt required.",
     &JetRegion::thePtMin, GeV, 0.0*GeV, 0.0*GeV, 0*GeV,
     false, false, Interface::lowerlim);

  static Parameter<JetRegion,Energy> interfacePtMax
    ("PtMax",
     "The maximum pt allowed.",
     &JetRegion::thePtMax, GeV, Constants::MaxEnergy, 0.0*GeV, 0*GeV,
     false, false, Interface::lowerlim);

  static Parameter<JetRegion,double> interfaceYMin
    ("YMin",
     "The minimum rapidity required.",
     &JetRegion::theYMin, -Constants::MaxRapidity, 0, 0,
     false, false, Interface::nolimits);
 
  static Parameter<JetRegion,double> interfaceYMax
    ("YMax",
     "The maximum rapidity required.",
     &JetRegion::theYMax, Constants::MaxRapidity, 0, 0,
     false, false, Interface::nolimits);

  static Parameter<JetRegion,double> interfaceEtaMin
    ("EtaMin",
     "The minimum pseudo-rapidity required.",
     &JetRegion::theEtaMin, -Constants::MaxRapidity, 0, 0,
     false, false, Interface::nolimits);
 
  static Parameter<JetRegion,double> interfaceEtaMax
    ("EtaMax",
     "The maximum pseudo-rapidity required.",
     &JetRegion::theEtaMax, Constants::MaxRapidity, 0, 0,
     false, false, Interface::nolimits);

  static ParVector<JetRegion,int> interfaceAccepts
    ("Accepts",
     "The jet numbers accepted.",
     &JetRegion::theAccepts, -1, 1, 1, 0,
     false, false, Interface::upperlim);

}

