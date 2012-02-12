// -*- C++ -*-
//
// NLOKTJetFinder.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2011 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the NLOKTJetFinder class.
//

#include "NLOKTJetFinder.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/DescribeClass.h"
#include "ThePEG/Cuts/Cuts.h"


#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

NLOKTJetFinder::NLOKTJetFinder() 
  : theDCut(ZERO), theConeRadius(0.7), 
    theVariant(kt), theMode(inclusive), theMeasure(pt),
    theRemoveOutOfRange(false) {}

NLOKTJetFinder::~NLOKTJetFinder() {}

IBPtr NLOKTJetFinder::clone() const {
  return new_ptr(*this);
}

IBPtr NLOKTJetFinder::fullclone() const {
  return new_ptr(*this);
}

bool NLOKTJetFinder::cluster(tcPDVector & ptype, vector<LorentzMomentum> & p,
			     tcCutsPtr parent, tcPDPtr t1, tcPDPtr t2) const {

  if ( ptype.size() < minOutgoing() )
    return true;

  bool is = 
    unresolvedMatcher()->check(*t1) ||
    unresolvedMatcher()->check(*t2);

  double dmin = Constants::MaxDouble;

  tcPDVector::iterator di = ptype.begin();
  tcPDVector::iterator dj;
  tcPDVector::iterator diMin, djMin;
  vector<LorentzMomentum>::iterator pi = p.begin();
  vector<LorentzMomentum>::iterator pj;
  vector<LorentzMomentum>::iterator piMin, pjMin;

  double r2 = theMode == inclusive ? sqr(theConeRadius) : 1.0;

  double dcut = 0.0;
  
  if ( theVariant != antikt ) {
    dcut = theDCut/GeV2;
  } else {
    dcut = GeV2/theDCut;
  }

  for ( ; di != ptype.end(); ++di, ++pi ) {
    if ( !unresolvedMatcher()->check(**di) )
      continue;
    dj = di; ++dj; pj = pi; ++pj;
    for ( ; dj != ptype.end(); ++dj, ++pj ) {
      if ( !unresolvedMatcher()->check(**dj) )
	continue;      
      double d = Constants::MaxDouble;
      if ( theMeasure == pt ) {
	double deta2 = sqr(pi->eta() - pj->eta());
	double dphi = abs(pi->phi() - pj->phi());
	if ( dphi > Constants::pi ) dphi = 2.0*Constants::pi - dphi;
	double dr2 = deta2 + sqr(dphi);
	if ( theVariant == kt ) {
	  d = min(pi->perp2()/GeV2,pj->perp2()/GeV2)*dr2/r2;
	} else if ( theVariant == ca ) {
	  d = dr2/r2;
	} else if ( theVariant == antikt ) {
	  d = min(GeV2/pi->perp2(),GeV2/pj->perp2())*dr2/r2;
	}
      } else if ( theMeasure == e ) {
	double dct = 2.*(1.-pi->vect().cosTheta(pj->vect()));
	if ( theVariant == kt ) {
	  d = min(sqr(pi->t())/GeV2,sqr(pj->t())/GeV2)*dct/r2;
	} else if ( theVariant == ca ) {
	  d = dct/r2;
	} else if ( theVariant == antikt ) {
	  d = min(GeV2/sqr(pi->t()),GeV2/sqr(pj->t()))*dct/r2;
	}
      }
      if ( d < dmin ) {
	dmin = d; 
	diMin = di; djMin = dj;
	piMin = pi; pjMin = pj;
      }
    }
    if ( is ) {
      double d = Constants::MaxDouble;
      if ( theMeasure == pt ) {
	if ( theVariant == kt ) {
	  d = pi->perp2()/GeV2;
	} else if ( theVariant == ca ) {
	  d = 1.0;
	} else if ( theVariant == antikt ) {
	  d = GeV2/pi->perp2();
	}
      } else if ( theMeasure == e ) {
	if ( theVariant == kt ) {
	  d = sqr(pi->t())/GeV2;
	} else if ( theVariant == ca ) {
	  d = 1.0;
	} else if ( theVariant == antikt ) {
	  d = GeV2/sqr(pi->t());
	}
      }
      if ( d < dmin ) {
	dmin = d; 
	diMin = di; djMin = ptype.end();
	piMin = pi; pjMin = p.end();
      }
    }
  }

  if ( djMin != ptype.end() ) {
    if ( ( theMode == exclusive && dmin < dcut ) || theMode == inclusive ) {
      *piMin = recombine(*piMin,*pjMin);
      ptype.erase(djMin); p.erase(pjMin);
      return true;
    }
  } else {
    if ( theMode == exclusive && dmin < dcut ) {
      ptype.erase(diMin); p.erase(piMin);
      return true;
    }
  }

  if ( theRemoveOutOfRange ) {
    tcPDVector::iterator dx = ptype.begin();
    vector<LorentzMomentum>::iterator px = p.begin(); 
    for ( ; dx != ptype.end(); ++dx, ++px ) {
      if ( !unresolvedMatcher()->check(**dx) )
	continue;
      if ( px->perp() < parent->minKT(*dx) ) {
	ptype.erase(dx); 
	p.erase(px);
	return true;
      }
      if ( abs(px->rapidity() + parent->Y() + parent->currentYHat()) 
	   < parent->minRapidityMax(*dx) ) {
	ptype.erase(dx);
	p.erase(px); 
	return true;
      }
      if ( abs(px->rapidity() + parent->Y() + parent->currentYHat()) 
	   > parent->maxRapidityMin(*dx) ) { 
	ptype.erase(dx);
	p.erase(px); 
	return true;
      }
    }
  }
  return false;

}

LorentzMomentum NLOKTJetFinder::recombine(const LorentzMomentum& pi,
					  const LorentzMomentum& pj) const {

  if ( ( theRecombination == recoDefault && theMeasure == e ) 
       || theRecombination == recoE ) {
    return pi + pj;
  }

  Energy ptij = pi.perp() + pj.perp();
  double phiij = (pi.perp()*pi.phi()+pj.perp()*pj.phi())/ptij;
  double yij = (pi.perp()*pi.rapidity()+pj.perp()*pj.rapidity())/ptij;

  return LorentzMomentum(ptij*cos(phiij),ptij*sin(phiij),ptij*sinh(yij),ptij*cosh(yij));

}

// If needed, insert default implementations of virtual function defined
// in the InterfacedBase class here (using ThePEG-interfaced-impl in Emacs).


void NLOKTJetFinder::persistentOutput(PersistentOStream & os) const {
  os << ounit(theDCut,GeV2) << theConeRadius << theVariant << theMode << theMeasure 
     << theRemoveOutOfRange << theRecombination;
}

void NLOKTJetFinder::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theDCut,GeV2) >> theConeRadius >> theVariant >> theMode >> theMeasure 
     >> theRemoveOutOfRange >> theRecombination;
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<NLOKTJetFinder,JetFinder>
  describeNLOKTJetFinder("ThePEG::NLOKTJetFinder", "NLOKTJetFinder.so");

void NLOKTJetFinder::Init() {

  static ClassDocumentation<NLOKTJetFinder> documentation
    ("NLOKTJetFinder implements the class of longitudinally invariant kt "
     "jet clustering algorithms, as relevant for cuts on the real "
     "emission contribution to a NLO calculation. Recombination is "
     "exclusively performed using the pt scheme.");


  static Parameter<NLOKTJetFinder,Energy2> interfaceDCut
    ("DCut",
     "The distance cut, when acting exclusively. "
     "The inverse is taken for the anti-kt algorithm, "
     "while for the Cambridge/Aachen variant dCut/GeV2 is used.",
     &NLOKTJetFinder::theDCut, GeV2, 0.0*GeV2, 0.0*GeV2, 0*GeV2,
     false, false, Interface::lowerlim);


  static Parameter<NLOKTJetFinder,double> interfaceConeRadius
    ("ConeRadius",
     "The cone radius R used in inclusive mode.",
     &NLOKTJetFinder::theConeRadius, 0.7, 0.0, 1.0,
     false, false, Interface::limited);


  static Switch<NLOKTJetFinder,int> interfaceVariant
    ("Variant",
     "The variant to use.",
     &NLOKTJetFinder::theVariant, kt, false, false);
  static SwitchOption interfaceVariantKt
    (interfaceVariant,
     "Kt",
     "Kt algorithm.",
     kt);
  static SwitchOption interfaceVariantCA
    (interfaceVariant,
     "CA",
     "Cambridge/Aachen algorithm.",
     ca);
  static SwitchOption interfaceVariantAntiKt
    (interfaceVariant,
     "AntiKt",
     "Anti kt algorithm.",
     antikt);


  static Switch<NLOKTJetFinder,int> interfaceMode
    ("Mode",
     "The mode to use.",
     &NLOKTJetFinder::theMode, inclusive, false, false);
  static SwitchOption interfaceModeInclusive
    (interfaceMode,
     "Inclusive",
     "Find inclusive jets.",
     inclusive);
  static SwitchOption interfaceModeExclusive
    (interfaceMode,
     "Exclusive",
     "Find exclusive jets.",
     exclusive);

  static Switch<NLOKTJetFinder,int> interfaceMeasure
    ("Measure",
     "The measure and recombination scheme to use.",
     &NLOKTJetFinder::theMeasure, pt, false, false);
  static SwitchOption interfaceMeasurePt
    (interfaceMeasure,
     "Pt",
     "Use the pt variant.",
     pt);
  static SwitchOption interfaceMeasureE
    (interfaceMeasure,
     "E",
     "Use the Durham variant.",
     e);  

  static Switch<NLOKTJetFinder,int> interfaceRecombination
    ("RecombinationScheme",
     "The recombination scheme to use.",
     &NLOKTJetFinder::theRecombination, recoDefault, false, false);
  static SwitchOption interfaceRecombinationdefault
    (interfaceRecombination,
     "Default",
     "Use the scheme according to the defined measure",
     recoDefault);
  static SwitchOption interfaceRecombinationPt
    (interfaceRecombination,
     "Pt",
     "Add transverse momenta",
     recoPt);
  static SwitchOption interfaceRecombinationE
    (interfaceRecombination,
     "E",
     "Add the four-momenta",
     recoE);  


  static Switch<NLOKTJetFinder,bool> interfaceRemoveOutOfRange
    ("RemoveOutOfRange",
     "Set to true to remove partons from cuts which are out of"
     "rapidity or pT range and not consider them as jets",
     &NLOKTJetFinder::theRemoveOutOfRange, false, false, false);
  static SwitchOption interfaceRemoveOutOfRangeTrue
    (interfaceRemoveOutOfRange,
     "True",
     "Remove",
     true);
  static SwitchOption interfaceRemoveOutOfRangeFalse
    (interfaceRemoveOutOfRange,
     "False",
     "Keep",
     false);

}

