// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleKTCut class.
//

#include "SimpleKTCut.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/PDT/MatcherBase.h"
#include "ThePEG/Cuts/Cuts.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleKTCut.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleKTCut::~SimpleKTCut() {}

Energy SimpleKTCut::minKT(tcPDPtr p) const {
  if ( theMatcher && !theMatcher->matches(*p) ) return 0.0*GeV;
  return theMinKT;
}

double SimpleKTCut::minEta(tcPDPtr p) const {
  if ( theMatcher && !theMatcher->matches(*p) )
    return -Constants::MaxRapidity;
  return theMinEta;
}

double SimpleKTCut::maxEta(tcPDPtr p) const {
  if ( theMatcher && !theMatcher->matches(*p) )
    return Constants::MaxRapidity;
  return theMaxEta;
}

bool SimpleKTCut::passCuts(tcCutsPtr parent,
			   tcPDPtr ptype, LorentzMomentum p) const {
  if ( theMatcher && !theMatcher->matches(*ptype) ) return true;
  if ( p.perp() <= theMinKT ) return false;
  double y = p.rapidity() + parent->Y() + parent->currentYHat();
  if ( p.mt()*sinh(y) <= p.perp()*sinh(theMinEta) ) return false;
  if ( p.mt()*sinh(y) >= p.perp()*sinh(theMaxEta) ) return false;
  return true;
}

void SimpleKTCut::persistentOutput(PersistentOStream & os) const {
  os << ounit(theMinKT, GeV) << theMinEta << theMaxEta << theMatcher;
}

void SimpleKTCut::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theMinKT, GeV) >> theMinEta >> theMaxEta >> theMatcher;
}

ClassDescription<SimpleKTCut> SimpleKTCut::initSimpleKTCut;
// Definition of the static class description member.

double SimpleKTCut::maxEtaMin() const {
  return theMaxEta;
}

double SimpleKTCut::minEtaMax() const {
  return theMinEta;
}

void SimpleKTCut::Init() {

  typedef double (ThePEG::SimpleKTCut::*IGFN)() const;
  typedef void (ThePEG::SimpleKTCut::*ISFN)(double);

  static ClassDocumentation<SimpleKTCut> documentation
    ("This is a very simple concrete sub-class of OneCutbase simply "
     "requiring a minimum transverse momentum of any outgoing particle. "
     "It is also possible to require a minimum and maximum pseudorapidity. "
     "Optionally the restrictions only apply to particles matching a "
     "specific matcher object.");

  static Parameter<SimpleKTCut,Energy> interfaceMinKT
    ("MinKT",
     "The minimum allowed value of the transverse momentum of an outgoing "
     "parton.",
     &SimpleKTCut::theMinKT, GeV, 10.0*GeV, 0.0*GeV, 0*GeV,
     true, false, Interface::lowerlim);


  static Parameter<SimpleKTCut,double> interfaceMinEta
    ("MinEta",
     "The minimum allowed pseudo-rapidity of an outgoing parton. "
     "The pseudo-rapidity is measured in the lab system.",
     &SimpleKTCut::theMinEta,
     -Constants::MaxRapidity, 0, Constants::MaxRapidity,
     true, false, Interface::upperlim,
     (ISFN)0, (IGFN)0, (IGFN)0, &SimpleKTCut::maxEtaMin, (IGFN)0);

  static Parameter<SimpleKTCut,double> interfaceMaxEta
    ("MaxEta",
     "The maximum allowed pseudo-rapidity of an outgoing parton. "
     "The pseudo-rapidity is measured in the lab system.",
     &SimpleKTCut::theMaxEta,
     Constants::MaxRapidity, -Constants::MaxRapidity, 0,
     true, false, Interface::lowerlim,
     (ISFN)0, (IGFN)0,  &SimpleKTCut::minEtaMax, (IGFN)0, (IGFN)0);

  static Reference<SimpleKTCut,MatcherBase> interfaceMatcher
    ("Matcher",
     "If non-null only particles matching this object will be affected "
     "by the cut.",
     &SimpleKTCut::theMatcher, true, false, true, true, false);
}
