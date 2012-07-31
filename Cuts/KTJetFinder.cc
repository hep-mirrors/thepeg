// -*- C++ -*-
//
// KTJetFinder.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2012 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the KTJetFinder class.
//

#include "KTJetFinder.h"
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

KTJetFinder::KTJetFinder() 
  : theDCut(ZERO), theConeRadius(0.7), 
    theVariant(kt), theMode(inclusive), theMeasure(pt),
    theRecombination(recoDefault) {}

KTJetFinder::~KTJetFinder() {}

IBPtr KTJetFinder::clone() const {
  return new_ptr(*this);
}

IBPtr KTJetFinder::fullclone() const {
  return new_ptr(*this);
}

bool KTJetFinder::cluster(tcPDVector & ptype, vector<LorentzMomentum> & p,
			  tcCutsPtr parent, tcPDPtr t1, tcPDPtr t2) const {

  if ( ptype.size() <= minOutgoing() )
    return false;

  if ( !oneCluster(ptype,p,parent,t1,t2) )
    return false;

  while ( ptype.size() > minOutgoing() )
    if ( !oneCluster(ptype,p,parent,t1,t2) )
      break;

  return true;

}

bool KTJetFinder::oneCluster(tcPDVector & ptype, vector<LorentzMomentum> & p,
			     tcCutsPtr parent, tcPDPtr t1, tcPDPtr t2) const {

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

  return false;

}

LorentzMomentum KTJetFinder::recombine(const LorentzMomentum& pi,
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


void KTJetFinder::persistentOutput(PersistentOStream & os) const {
  os << ounit(theDCut,GeV2) << theConeRadius << theVariant << theMode << theMeasure 
     << theRecombination;
}

void KTJetFinder::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theDCut,GeV2) >> theConeRadius >> theVariant >> theMode >> theMeasure 
     >> theRecombination;
}


// *** Attention *** The following static variable is needed for the type
// description system in ThePEG. Please check that the template arguments
// are correct (the class and its base class), and that the constructor
// arguments are correct (the class name and the name of the dynamically
// loadable library where the class implementation can be found).
DescribeClass<KTJetFinder,JetFinder>
  describeKTJetFinder("ThePEG::KTJetFinder", "KTJetFinder.so");

void KTJetFinder::Init() {

  static ClassDocumentation<KTJetFinder> documentation
    ("KTJetFinder implements the class of longitudinally invariant kt "
     "jet clustering algorithms, as relevant for cuts on the real "
     "emission contribution to a NLO calculation. Recombination is "
     "exclusively performed using the pt scheme.");


  static Parameter<KTJetFinder,Energy2> interfaceDCut
    ("DCut",
     "The distance cut, when acting exclusively. "
     "The inverse is taken for the anti-kt algorithm, "
     "while for the Cambridge/Aachen variant dCut/GeV2 is used.",
     &KTJetFinder::theDCut, GeV2, 0.0*GeV2, 0.0*GeV2, 0*GeV2,
     false, false, Interface::lowerlim);


  static Parameter<KTJetFinder,double> interfaceConeRadius
    ("ConeRadius",
     "The cone radius R used in inclusive mode.",
     &KTJetFinder::theConeRadius, 0.7, 0.0, 1.0,
     false, false, Interface::limited);


  static Switch<KTJetFinder,int> interfaceVariant
    ("Variant",
     "The variant to use.",
     &KTJetFinder::theVariant, kt, false, false);
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


  static Switch<KTJetFinder,int> interfaceMode
    ("Mode",
     "The mode to use.",
     &KTJetFinder::theMode, inclusive, false, false);
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

  static Switch<KTJetFinder,int> interfaceMeasure
    ("Measure",
     "The measure and recombination scheme to use.",
     &KTJetFinder::theMeasure, pt, false, false);
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

  static Switch<KTJetFinder,int> interfaceRecombination
    ("RecombinationScheme",
     "The recombination scheme to use.",
     &KTJetFinder::theRecombination, recoDefault, false, false);
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

}

