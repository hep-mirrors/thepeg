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
#include "ThePEG/Interface/Command.h"
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
    theDidMatch(false), theLastNumber(0) {}

JetRegion::~JetRegion() {}

IBPtr JetRegion::clone() const {
  return new_ptr(*this);
}

IBPtr JetRegion::fullclone() const {
  return new_ptr(*this);
}

string JetRegion::doYRange(string in) {
  istringstream ins(in);
  double first, second;
  ins >> first >> second;
  if ( first > second )
    swap(first,second);
  theYRanges.push_back(make_pair(first,second));
  return "";
}

string JetRegion::doEtaRange(string in) {
  istringstream ins(in);
  double first, second;
  ins >> first >> second;
  if ( first > second )
    swap(first,second);
  theEtaRanges.push_back(make_pair(first,second));
  return "";
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
    << "pt  = " << ptMin()/GeV << " .. " << ptMax()/GeV << " GeV\n";

  for ( vector<pair<double,double> >::const_iterator r = yRanges().begin();
	r != yRanges().end(); ++r ) {
    CurrentGenerator::log() << "y   = " << r->first << " .. " << r->second << "\n";
  }

  for ( vector<pair<double,double> >::const_iterator r = etaRanges().begin();
	r != etaRanges().end(); ++r ) {
    CurrentGenerator::log() << "eta = " << r->first << " .. " << r->second << "\n";
  }

}

bool JetRegion::matches(tcCutsPtr parent, int n, const LorentzMomentum& p) {

  // one jet region can only contain one jet
  if ( didMatch() )
    return false;

  if ( !accepts().empty() && find(accepts().begin(),accepts().end(),n) == accepts().end() )
    return false;

  if ( p.perp() < ptMin() || p.perp() > ptMax() )
    return false;

  bool inRange = false || yRanges().empty();
  for ( vector<pair<double,double> >::const_iterator r = yRanges().begin();
	r != yRanges().end(); ++r ) {
    if ( p.rapidity() + parent->currentYHat() > r->first && p.rapidity() + parent->currentYHat() < r->second ) {
      inRange = true;
      break;
    }
  }
  if ( !inRange )
    return false;

  inRange = false || etaRanges().empty();
  for ( vector<pair<double,double> >::const_iterator r = etaRanges().begin();
	r != etaRanges().end(); ++r ) {
    if ( p.eta() + parent->currentYHat() > r->first && p.eta() + parent->currentYHat() < r->second ) {
      inRange = true;
      break;
    }
  }
  if ( !inRange )
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
     << theYRanges << theEtaRanges
     << theAccepts;
}

void JetRegion::persistentInput(PersistentIStream & is, int) {
  is >> iunit(thePtMin,GeV) >> iunit(thePtMax,GeV)
     >> theYRanges >> theEtaRanges
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

  static Command<JetRegion> interfaceYRange
    ("YRange",
     "Insert a rapidity range.",
     &JetRegion::doYRange, false);

  static Command<JetRegion> interfaceEtaRange
    ("EtaRange",
     "Insert a pseudo-rapidity range.",
     &JetRegion::doEtaRange, false);

  static ParVector<JetRegion,int> interfaceAccepts
    ("Accepts",
     "The jet numbers accepted. If empty, any jets are accepted.",
     &JetRegion::theAccepts, -1, 1, 1, 10,
     false, false, Interface::upperlim);

}

