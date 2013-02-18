// -*- C++ -*-
//
// MultiJetRegion.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2012 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MultiJetRegion class.
//

#include "MultiJetRegion.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Repository/CurrentGenerator.h"

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

MultiJetRegion::MultiJetRegion()
  : theMassMin(0.*GeV), theMassMax(Constants::MaxEnergy),
    theDeltaRMin(0.0), theDeltaRMax(Constants::MaxRapidity),
    theDeltaYMin(0.0), theDeltaYMax(Constants::MaxRapidity), 
    theDeltaEtaMin(0.0), theDeltaEtaMax(Constants::MaxRapidity) {}

MultiJetRegion::~MultiJetRegion() {}

IBPtr MultiJetRegion::clone() const {
  return new_ptr(*this);
}

IBPtr MultiJetRegion::fullclone() const {
  return new_ptr(*this);
}

void MultiJetRegion::describe() const {

  CurrentGenerator::log()
    << "MultiJetRegion '" << name() << "' matching JetRegions:\n";

  for ( vector<Ptr<JetRegion>::ptr>::const_iterator r = regions().begin();
	r != regions().end(); ++r ) {
    CurrentGenerator::log()
      << "'" << (**r).name() << "'\n";
  }

  CurrentGenerator::log() << "with\n";

  CurrentGenerator::log()
    << "m    = " << massMin()/GeV << " .. " << massMax()/GeV << " GeV\n"
    << "dR   = " << deltaRMin() << " .. " << deltaRMax() << "\n"
    << "dy   = " << deltaYMin() << " .. " << deltaYMax() << "\n"
    << "deta = " << deltaEtaMin() << " .. " << deltaEtaMax() << "\n";

}

bool MultiJetRegion::matches() const {

  int n = regions().size();

  for ( int i = 0; i < n; ++i )
    for ( int j = i+1; j < n; ++j )
      if ( !matches(i,j) )
	return false;

  return true;

}

bool MultiJetRegion::matches(int i, int j) const {
  
  if ( !regions()[i]->didMatch() ||
       !regions()[j]->didMatch() )
    return false;

  const LorentzMomentum& pi = regions()[i]->lastMomentum();
  const LorentzMomentum& pj = regions()[j]->lastMomentum();

  Energy m = (pi+pj).m();
  if ( m < massMin() || m > massMax() )
    return false;

  double deta = abs(pi.eta()-pj.eta());
  if ( deta < deltaEtaMin() || deta > deltaEtaMax() )
    return false;

  double dphi = abs(pi.phi() - pj.phi());
  if ( dphi > Constants::pi ) dphi = 2.0*Constants::pi - dphi;
  double dR = sqrt(sqr(deta)+sqr(dphi));
  if ( dR < deltaRMin() || dR > deltaRMax() )
    return false;

  double dy = abs(pi.rapidity() - pj.rapidity());
  if ( dy < deltaYMin() || dy > deltaYMax() )
    return false;

  return true;

}

// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void MultiJetRegion::persistentOutput(PersistentOStream & os) const {
  os << theRegions
     << ounit(theMassMin,GeV) << ounit(theMassMax,GeV)
     << theDeltaRMin << theDeltaRMax 
     << theDeltaYMin << theDeltaYMax 
     << theDeltaEtaMin << theDeltaEtaMax;
}

void MultiJetRegion::persistentInput(PersistentIStream & is, int) {
  is >> theRegions
     >> iunit(theMassMin,GeV) >> iunit(theMassMax,GeV)
     >> theDeltaRMin >> theDeltaRMax 
     >> theDeltaYMin >> theDeltaYMax 
     >> theDeltaEtaMin >> theDeltaEtaMax;
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<MultiJetRegion,HandlerBase>
  describeThePEGMultiJetRegion("ThePEG::MultiJetRegion", "JetCuts.so");

void MultiJetRegion::Init() {

  static ClassDocumentation<MultiJetRegion> documentation
    ("MultiJetRegion implements pairwise constraints on jets matching several jet regions.");


  static RefVector<MultiJetRegion,JetRegion> interfaceRegions
    ("Regions",
     "The jet regions to act on.",
     &MultiJetRegion::theRegions, -1, false, false, true, false, false);

  static Parameter<MultiJetRegion,Energy> interfaceMassMin
    ("MassMin",
     "The minimum jet-jet invariant mass.",
     &MultiJetRegion::theMassMin, GeV, 0.0*GeV, 0.0*GeV, 0*GeV,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,Energy> interfaceMassMax
    ("MassMax",
     "The maximum jet-jet invariant mass.",
     &MultiJetRegion::theMassMax, GeV, Constants::MaxEnergy, 0.0*GeV, 0*GeV,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaRMin
    ("DeltaRMin",
     "The minimum jet-jet lego-plot separation.",
     &MultiJetRegion::theDeltaRMin, 0.0, 0.0, 0,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaRMax
    ("DeltaRMax",
     "The maximum jet-jet lego-plot separation.",
     &MultiJetRegion::theDeltaRMax, Constants::MaxRapidity, 0, 0,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaYMin
    ("DeltaYMin",
     "The minimum jet-jet rapidity separation.",
     &MultiJetRegion::theDeltaYMin, 0.0, 0.0, 0,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaYMax
    ("DeltaYMax",
     "The maximum jet-jet rapidity separation.",
     &MultiJetRegion::theDeltaYMax, Constants::MaxRapidity, 0, 0,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaEtaMin
    ("DeltaEtaMin",
     "The minimum jet-jet pseudo-rapidity separation.",
     &MultiJetRegion::theDeltaEtaMin, 0.0, 0.0, 0,
     false, false, Interface::lowerlim);

  static Parameter<MultiJetRegion,double> interfaceDeltaEtaMax
    ("DeltaEtaMax",
     "The maximum jet-jet pseudo-rapidity separation.",
     &MultiJetRegion::theDeltaEtaMax, Constants::MaxRapidity, 0, 0,
     false, false, Interface::lowerlim);

}

