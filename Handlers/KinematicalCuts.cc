// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the KinematicalCuts class.
//

#include "KinematicalCuts.h"
#include "KinematicalCuts.xh"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/EventRecord/Collision.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/PDT/StandardMatchers.h"
// #include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "KinematicalCuts.tcc"
#endif

using namespace ThePEG;

KinematicalCuts::KinematicalCuts()
  : theMHatMin(2.0*GeV), theMHatMax(-1.0*GeV), thePTHatMin(0.0*GeV),
    thePTHatMax(-1.0*GeV), thePTHatSingularMin(1.0*GeV),
    theSingularMassMax(1.0*GeV), theYStarMin(-10.0), theYStarMax(10.0),
    theMaxYMin(-10.0), theMaxYMax(10.0), theMinYMin(-10.0), theMinYMax(10.0),
    theMaxEtaMin(-10.0), theMaxEtaMax(10.0), theMinEtaMin(-10.0),
    theMinEtaMax(10.0), theMaxCTMin(-1.0), theMaxCTMax(1.0), theMinCTMin(-1.0),
    theMinCTMax(1.0), theX1Min(0.0), theX1Max(1.0), theX2Min(0.0),
    theX2Max(1.0), theXFMin(-1.0), theXFMax(1.0), theCTHMin(-1.0),
    theCTHMax(1.0), theTHatMin(0.0*GeV2), theTHatMax(-1.0*GeV2),
    theUHatMin(0.0*GeV2), theUHatMax(-1.0*GeV2),
    theScaleMin(0.0*GeV2), theScaleMax(-1.0*GeV2), useLeptoCuts(false),
    theDISLepton1EnergyMin(0.0*GeV), theDISLepton1EnergyMax(-1.0*GeV),
    theDISLepton1AngleMin(0.0), theDISLepton1AngleMax(Constants::pi),
    theDISQ21Min(0.0*GeV2), theDISQ21Max(-1.0*GeV2),
    theDISLepton2EnergyMin(0.0*GeV), theDISLepton2EnergyMax(-1.0*GeV),
    theDISLepton2AngleMin(0.0), theDISLepton2AngleMax(Constants::pi),
    theDISQ22Min(0.0*GeV2), theDISQ22Max(-1.0*GeV2),
    theDISW2Min(0.0*GeV2), theDISW2Max(-1.0*GeV2) {}

KinematicalCuts::KinematicalCuts(const KinematicalCuts & kc)
  : Interfaced(kc), theMHatMin(kc.theMHatMin), theMHatMax(kc.theMHatMax),
    thePTHatMin(kc.thePTHatMin), thePTHatMax(kc.thePTHatMax),
    thePTHatSingularMin(kc.thePTHatSingularMin),
    theSingularMassMax(kc.theSingularMassMax), theYStarMin(kc.theYStarMin),
    theYStarMax(kc.theYStarMax), theMaxYMin(kc.theMaxYMin),
    theMaxYMax(kc.theMaxYMax), theMinYMin(kc.theMinYMin),
    theMinYMax(kc.theMinYMax), theMaxEtaMin(kc.theMaxEtaMin),
    theMaxEtaMax(kc.theMaxEtaMax), theMinEtaMin(kc.theMinEtaMin),
    theMinEtaMax(kc.theMinEtaMax), theMaxCTMin(kc.theMaxCTMin),
    theMaxCTMax(kc.theMaxCTMax), theMinCTMin(kc.theMinCTMin),
    theMinCTMax(kc.theMinCTMax), theX1Min(kc.theX1Min), theX1Max(kc.theX1Max),
    theX2Min(kc.theX2Min),  theX2Max(kc.theX2Max), theXFMin(kc.theXFMin),
    theXFMax(kc.theXFMax), theCTHMin(kc.theCTHMin), theCTHMax(kc.theCTHMax),
    theTHatMin(kc.theTHatMin), theTHatMax(kc.theTHatMax),
    theUHatMin(kc.theUHatMin), theUHatMax(kc.theUHatMax),
    theScaleMin(kc.theScaleMin), theScaleMax(kc.theScaleMax),
    useLeptoCuts(kc.useLeptoCuts),
    theDISLepton1EnergyMin(kc.theDISLepton1EnergyMin),
    theDISLepton1EnergyMax(kc.theDISLepton1EnergyMax),
    theDISLepton1AngleMin(kc.theDISLepton1AngleMin),
    theDISLepton1AngleMax(kc.theDISLepton1AngleMax),
    theDISQ21Min(kc.theDISQ21Min), theDISQ21Max(kc.theDISQ21Max),
    theDISLepton2EnergyMin(kc.theDISLepton2EnergyMin),
    theDISLepton2EnergyMax(kc.theDISLepton2EnergyMax),
    theDISLepton2AngleMin(kc.theDISLepton2AngleMin),
    theDISLepton2AngleMax(kc.theDISLepton2AngleMax),
    theDISQ22Min(kc.theDISQ22Min), theDISQ22Max(kc.theDISQ22Max),
    theDISW2Min(kc.theDISW2Min), theDISW2Max(kc.theDISW2Max),
    theLeptonMatcher(kc.theLeptonMatcher) {}

KinematicalCuts::~KinematicalCuts() {}

void KinematicalCuts::newcut(const SubProcess &) const
  ThePEG_THROW_SPEC((Veto)) {}

void KinematicalCuts::cut(const SubProcess & sp) const
  ThePEG_THROW_SPEC((Veto)) {
  //  Timer<34> timer("KinematicalCuts::cut(SubProcess)");
  newcut(sp);
  const ParticleVector & out = sp.outgoing();
  int N = out.size();
  if ( N < 1 ) throw KinCutSetup();
  if ( !sp.incoming().first || !sp.incoming().second ) throw KinCutSetup();

  // General cuts:
  if ( sp.shat() < sHatMin() || sp.shat() >= sHatMax() ) throw Veto();

  // Now check 2->2 proceses:
  if ( N != 2 ) return;

  if ( -sp.that() < tHatMin() || -sp.that() >= tHatMax() ) throw Veto();

  if ( -sp.uhat() < uHatMin() || -sp.uhat() >= uHatMax() ) throw Veto();

  double cth = out[0]->momentum().cosTheta();
  if ( cth < cTHMin() || cth >= cTHMax() ) throw Veto();

  Energy pt = out[0]->momentum().perp();
  if ( pt < pTHatMin() || pt >= pTHatMax() ) throw Veto();

}

void KinematicalCuts::
newcut(const Collision &, const LorentzRotation &) const
  ThePEG_THROW_SPEC((Veto)) {}

void KinematicalCuts::
cut(const Collision & c, const LorentzRotation & r) const
  ThePEG_THROW_SPEC((Veto)) {
  //  Timer<35> timer("KinematicalCuts::cut(Collision)");
  newcut(c, r);
  if ( !c.primarySubProcess() ) throw KinCutSetup();
  if ( !c.incoming().first || !c.incoming().second ) throw KinCutSetup();
  if ( !c.step(0) ) throw KinCutSetup();
  const SubProcess & sp = *c.primarySubProcess();
  const ParticleVector & out = sp.outgoing();
  int N = out.size();
  if ( N < 1 ) throw KinCutSetup();
  if ( !sp.incoming().first || !sp.incoming().second ) throw KinCutSetup();
  Lorentz5Momentum p1 = c.incoming().first->momentum();
  Lorentz5Momentum p2 = c.incoming().second->momentum();
  Lorentz5Momentum q1 = sp.incoming().first->momentum();
  Lorentz5Momentum q2 = sp.incoming().second->momentum();

  if ( p1.plus() <= 0.0*GeV ) throw KinCutSetup();
  if ( p2.minus() <= 0.0*GeV ) throw KinCutSetup();

  double x1 = q1.plus()/p1.plus();
  if ( x1 <= x1Min() || x1 > x1Max() ) throw Veto();

  double x2 = q2.minus()/p2.minus();
  if ( x2 <= x2Min() || x2 > x2Max() ) throw Veto();

  if ( x1 - x2 < xFMin() || x1 - x2 > xFMax() ) throw Veto();

  if ( x1/x2 < exp(2.0*yStarMin()) || x1/x2 >= exp(2.0*yStarMax()) )
    throw Veto();

  ParticleVector::const_iterator it = sp.outgoing().begin();
  LorentzMomentum ymax = (**it).momentum();
  LorentzMomentum ymin = (**it).momentum();
  LorentzMomentum etamax = (**it).momentum();
  LorentzMomentum etamin = (**it).momentum();
  LorentzMomentum ctmax = (**it).momentum();
  LorentzMomentum ctmin = (**it).momentum();
  while ( ++it != sp.outgoing().end() ) {
    LorentzMomentum cur = (**it).momentum();
    if ( cur.plus()*ymax.minus() > ymax.plus()*cur.minus() ) ymax = cur;
    if ( cur.plus()*ymin.minus() < ymin.plus()*cur.minus() ) ymin = cur;
    if ( (cur.rho()+cur.z())*(etamax.rho()-etamax.z()) >
	 (cur.rho()-cur.z())*(etamax.rho()+etamax.z()) ) etamax = cur;
    if ( (cur.rho()+cur.z())*(etamin.rho()-etamin.z()) >
	 (cur.rho()-cur.z())*(etamin.rho()+etamin.z()) ) etamin = cur;
    if ( cur.cosTheta() > ctmax.cosTheta() ) ctmax = cur;
    if ( cur.cosTheta() < ctmin.cosTheta() ) ctmin = cur;
  }

  if ( ymax.plus() < exp(2.0*maxYMin())*ymax.minus() ||
       ymax.plus() > exp(2.0*maxYMax())*ymax.minus() ) throw Veto();
  if ( ymin.plus() < exp(2.0*minYMin())*ymin.minus() ||
       ymin.plus() > exp(2.0*minYMax())*ymin.minus() ) throw Veto();
  if ( (etamax.rho()+etamax.z()) <
       exp(2.0*maxEtaMin())*(etamax.rho()-etamax.z()) ||
       (etamax.rho()+etamax.z()) >
       exp(2.0*maxEtaMax())*(etamax.rho()-etamax.z()) ) throw Veto();
  if ( (etamin.rho()+etamin.z()) <
       exp(2.0*minEtaMin())*(etamin.rho()-etamin.z()) ||
       (etamin.rho()+etamin.z()) >
       exp(2.0*minEtaMax())*(etamin.rho()-etamin.z()) ) throw Veto();
  if ( ctmax.cosTheta() < maxCTMin() ||
       ctmax.cosTheta() > maxCTMax() ) throw Veto();
  if ( ctmin.cosTheta() < minCTMin() ||
       ctmin.cosTheta() > minCTMax() ) throw Veto();

  if ( !useLeptoCuts ) return;

  const ParticleSet & particles = c.step(0)->particles();
  tcPPtr l1;
  Energy2 Q21 = 0.0*GeV;
  if ( isLepton(*c.incoming().first) ) {
    for ( ParticleSet::const_iterator it = particles.begin();
	  it != particles.end(); ++it )
      if ( (**it).parents()[0] == c.incoming().first && isLepton(**it) &&
	-(p1 - (**it).momentum()).m2() > Q21 ) {
	l1 = *it;
	Q21 = -(p1 - l1->momentum()).m2();
	break;
      }
  }
  tcPPtr l2;
  Energy2 Q22 = 0.0*GeV;
  if ( isLepton(*c.incoming().second) ) {
    for ( ParticleSet::const_iterator it = particles.begin();
	  it != particles.end(); ++it )
      if ( (**it).parents()[0] == c.incoming().second && isLepton(**it) &&
	-(p2 - (**it).momentum()).m2() > Q22 ) {
	l2 = *it;
	Q22 = -(p2 - l2->momentum()).m2();
	break;
      }
  }

  p1 *= r;
  p2 *= r;
  if ( l1 ) {
    if ( Q21 < DISQ21Min() || Q21 >= DISQ21Max() ) throw Veto();
    LorentzMomentum q = l1->momentum();
    q *= r;
    if ( q.e() < DISLepton1EnergyMin() ||
	 q.e() >= DISLepton1EnergyMax() ) throw Veto();
    double the = q.angle((const LorentzMomentum &)p1);
    if ( the < DISLepton1AngleMin() ||
	 the > DISLepton1AngleMax() ) throw Veto();
    p1 -= q;
  }
  if ( l2 ) {
    if ( Q22 < DISQ22Min() || Q22 >= DISQ22Max() ) throw Veto();
    LorentzMomentum q = l2->momentum();
    q *= r;
    if ( q.e() < DISLepton2EnergyMin() ||
	 q.e() >= DISLepton2EnergyMax() ) throw Veto();
    double the = q.angle((const LorentzMomentum &)p2);
    if ( the < DISLepton2AngleMin() ||
	 the > DISLepton2AngleMax() ) throw Veto();
    p1 -= q;
  }
  if ( l1 || l2 ) {
    Energy2 W2 = (p1+p2).m2();
    if ( W2 < DISW2Min() || W2 >= DISW2Max() ) throw Veto();
  }
}

bool KinematicalCuts::isLepton(const Particle & p) const {
  return theLeptonMatcher->checkp(p);
}

double KinematicalCuts::maxYMinMax() const {
  return max(maxYMin(), minYMin());
}

double KinematicalCuts::minYMaxMin() const {
  return min(minYMax(), maxYMax());
}

double KinematicalCuts::maxEtaMinMax() const {
  return max(maxEtaMin(), minEtaMin());
}

double KinematicalCuts::minEtaMaxMin() const {
  return min(minEtaMax(), maxEtaMax());
}

double KinematicalCuts::maxCTMinMax() const {
  return max(maxCTMin(), minCTMin());
}

double KinematicalCuts::minCTMaxMin() const {
  return min(minCTMax(), minCTMin());
}

IBPtr KinematicalCuts::clone() const {
  return new_ptr(*this);
}

void KinematicalCuts::doupdate() throw(UpdateException) {
  Interfaced::doupdate();
  if ( yStarMax() <= yStarMin() )
    throw KinCutZeroInterval(*this, "YStarMax <= YStarMin");
  if ( maxYMax() <= maxYMin() )
    throw KinCutZeroInterval(*this, "MaxYMax <= MaxYMin");
  if ( minYMax() <= minYMin() )
    throw KinCutZeroInterval(*this, "MaxYMin <= MinYMin");
  if ( maxYMax() <= minYMin() )
    throw KinCutZeroInterval(*this, "MaxYMax <= MinYMin");
  if ( maxEtaMax() <= maxEtaMin() )
    throw KinCutZeroInterval(*this, "MaxEtaMax <= MaxEtaMin");
  if ( minEtaMax() <= minEtaMin() )
    throw KinCutZeroInterval(*this, "MaxEtaMin <= MinEtaMin");
  if ( maxEtaMax() <= minEtaMin() )
    throw KinCutZeroInterval(*this, "MaxEtaMax <= MinEtaMin");
  if ( maxCTMax() <= maxCTMin() )
    throw KinCutZeroInterval(*this, "MaxCTMax <= MaxCTMin");
  if ( minCTMax() <= minCTMin() )
    throw KinCutZeroInterval(*this, "MaxCTMin <= MinCTMin");
  if ( maxCTMax() <= minCTMin() )
    throw KinCutZeroInterval(*this, "MaxCTMax <= MinCTMin");
  if ( x1Max() <= x1Min() )
    throw KinCutZeroInterval(*this, "X1Max <= X1Min");
  if ( x2Max() <= x2Min() )
    throw KinCutZeroInterval(*this, "X2Max <= X2Min");
  if ( xFMax() <= xFMin() )
    throw KinCutZeroInterval(*this, "XFMax <= XFMin");
  if ( cTHMax() <= cTHMin() )
    throw KinCutZeroInterval(*this, "CTHMax <= CTHMin");
  if ( DISLepton1AngleMax() <= DISLepton1AngleMin() )
    throw KinCutZeroInterval(*this, "Lepton1AngleMax <= DISLepton1AngleMin");
  if ( DISLepton2AngleMax() <= DISLepton2AngleMin() )
    throw KinCutZeroInterval(*this, "Lepton1AngleMax <= DISLepton1AngleMin");
}

void KinematicalCuts::persistentOutput(PersistentOStream & os) const {
  os << ounit(theMHatMin, GeV) << ounit(theMHatMax, GeV)
     << ounit(thePTHatMin, GeV) << ounit(thePTHatMax, GeV)
     << ounit(thePTHatSingularMin, GeV) << ounit(theSingularMassMax, GeV)
     << theYStarMin << theYStarMax
     << theMaxYMin << theMaxYMax << theMinYMin << theMinYMax
     << theMaxEtaMin << theMaxEtaMax << theMinEtaMin << theMinEtaMax
     << theMaxCTMin << theMaxCTMax << theMinCTMin << theMinCTMax << theX1Min
     << theX1Max << theX2Min << theX2Max << theXFMin << theXFMax << theCTHMin
     << theCTHMax << ounit(theTHatMin, GeV2) << ounit(theTHatMax, GeV2)
     << ounit(theUHatMin, GeV2) << ounit(theUHatMax, GeV2)
     << ounit(theScaleMin, GeV2) << ounit(theScaleMax, GeV2)
     << useLeptoCuts << ounit(theDISLepton1EnergyMin, GeV)
     << ounit(theDISLepton1EnergyMax, GeV)
     << theDISLepton1AngleMin << theDISLepton1AngleMax
     << ounit(theDISLepton2EnergyMin, GeV) << ounit(theDISLepton2EnergyMax, GeV)
     << theDISLepton2AngleMin << theDISLepton2AngleMax
     << ounit(theDISW2Min, GeV2) << ounit(theDISW2Max, GeV2)
     << ounit(theDISQ21Min, GeV2) << ounit(theDISQ21Max, GeV2)
     << ounit(theDISQ22Min, GeV2) << ounit(theDISQ22Max, GeV2)
     << theLeptonMatcher;
}

void KinematicalCuts::persistentInput(PersistentIStream & is, int) {
  is >> iunit(theMHatMin, GeV) >> iunit(theMHatMax, GeV)
     >> iunit(thePTHatMin, GeV) >> iunit(thePTHatMax, GeV)
     >> iunit(thePTHatSingularMin, GeV) >> iunit(theSingularMassMax, GeV)
     >> theYStarMin >> theYStarMax
     >> theMaxYMin >> theMaxYMax >> theMinYMin >> theMinYMax
     >> theMaxEtaMin >> theMaxEtaMax >> theMinEtaMin >> theMinEtaMax
     >> theMaxCTMin >> theMaxCTMax >> theMinCTMin >> theMinCTMax >> theX1Min
     >> theX1Max >> theX2Min >> theX2Max >> theXFMin >> theXFMax >> theCTHMin
     >> theCTHMax >> iunit(theTHatMin, GeV2) >> iunit(theTHatMax, GeV2)
     >> iunit(theUHatMin, GeV2) >> iunit(theUHatMax, GeV2)
     >> iunit(theScaleMin, GeV2) >> iunit(theScaleMax, GeV2)
     >> useLeptoCuts >> iunit(theDISLepton1EnergyMin, GeV)
     >> iunit(theDISLepton1EnergyMax, GeV)
     >> theDISLepton1AngleMin >> theDISLepton1AngleMax
     >> iunit(theDISLepton2EnergyMin, GeV) >> iunit(theDISLepton2EnergyMax, GeV)
     >> theDISLepton2AngleMin >> theDISLepton2AngleMax
     >> iunit(theDISW2Min, GeV2) >> iunit(theDISW2Max, GeV2)
     >> iunit(theDISQ21Min, GeV2) >> iunit(theDISQ21Max, GeV2)
     >> iunit(theDISQ22Min, GeV2) >> iunit(theDISQ22Max, GeV2)
     >> theLeptonMatcher;
}

ClassDescription<KinematicalCuts> KinematicalCuts::initKinematicalCuts;

KinCutSetup::KinCutSetup() {
  theMessage << "KinematicalCuts was asked to check an icomplete "
	     << "SubProcess/Collision/Event. This should never happen."
	     << " the run will be aborted immediately.";
  severity(abortnow);
}

KinCutZeroInterval::KinCutZeroInterval(const KinematicalCuts & i, string s) {
  theMessage << "The KinematicalCuts object '" << i.name() << "' is not "
	     << "Properly set up since an interval was non-existent :"
	     << s << ".";
  severity(warning);
}

