// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MatcherBase class.
//

#include "MatcherBase.h"
#include "DecayMode.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Repository/Repository.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/EnumIO.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MatcherBase.tcc"
#endif

using namespace ThePEG;

MatcherBase::MatcherBase()
  : theMaxMass(0.0*GeV), theMinMass(0.0*GeV), commonMass(-1.0*GeV),
    commonWidth(-1.0*GeV), commonCTau(-1.0*mm),
    commonCharge(PDT::ChargeUndefined), commonSpin(PDT::SpinUndefined),
    commonColor(PDT::ColourUndefined), commonStable(-1) {}

MatcherBase::MatcherBase(const MatcherBase & m)
  : Interfaced(m), theMaxMass(m.theMaxMass), theMinMass(m.theMinMass),
    commonMass(m.commonMass), commonWidth(m.commonWidth),
    commonCTau(m.commonCTau), commonCharge(m.commonCharge),
    commonSpin(m.commonSpin), commonColor(m.commonColor),
    commonStable(m.commonStable), theAntiPartner(m.theAntiPartner) {}

void MatcherBase::doupdate() throw(UpdateException) {
  Interfaced::doupdate();
  ParticleDataSet oldParticles;
  MatcherSet oldMatchers;
  Energy oldMass = commonMass;
  Energy oldWidth = commonWidth;
  Length oldCTau = commonCTau;
  PDT::Spin  oldSpin = commonSpin;
  PDT::Charge oldCharge = commonCharge;
  PDT::Color oldColor = commonColor;
  int oldStable = commonStable;
  matchingParticles.swap(oldParticles);
  matchingMatchers.swap(oldMatchers);
  if ( generator() ) {
    for ( ParticleMap::const_iterator it = generator()->particles().begin();
	  it != generator()->particles().end(); ++it ) addPIfMatch(it->second);
    addMIfMatchFrom(generator()->matchers());
  } else {
    addPIfMatchFrom(Repository::allParticles());
    addMIfMatchFrom(Repository::allMatchers());
  }
  if ( matchingParticles != oldParticles || matchingMatchers != oldMatchers ||
    oldMass != commonMass || oldWidth != commonWidth || oldCTau != commonCTau ||
    oldSpin != commonSpin || oldCharge != commonCharge ||
       oldColor != commonColor || oldStable != commonStable ) touch();
}

void MatcherBase::clear() {
  matchingParticles.clear();
  matchingMatchers.clear();
  theMaxMass = 0.0*GeV;
  theMinMass = 0.0*GeV;
  commonMass = -1.0*GeV;
  commonWidth = -1.0*GeV;
  commonCTau = -1.0*mm;
  commonSpin = PDT::SpinUndefined;
  commonCharge = PDT::ChargeUndefined;
  commonColor = PDT::ColourUndefined;
  commonStable = -1;
}

void MatcherBase::addMIfMatch(tPMPtr pm) {
  if ( member(matchingMatchers, pm) ) return;
  ParticleDataSet::const_iterator i = pm->matchingParticles.begin();
  while ( i != pm->matchingParticles.end() )
    if ( !member(matchingParticles, *i++) ) return;
  matchingMatchers.insert(pm);
}


void MatcherBase::addPIfMatch(tPDPtr pd) {
  if ( !pd || !check(*pd) || member(matchingParticles, pd) ) return;
  if ( matchingParticles.empty() ) {
    commonMass = pd->mass();
    theMinMass = pd->mass();
    theMaxMass = pd->mass();
    commonWidth = pd->width();
    commonCTau = pd->cTau();
    commonCharge = pd->iCharge();
    commonSpin = pd->iSpin();
    commonColor = pd->iColor();
    commonStable = pd->stable();
  } else {
    if ( commonMass != pd->mass() ) commonMass = -1.0*GeV;
    theMinMass = min(theMinMass, pd->mass());
    theMaxMass = min(theMaxMass, pd->mass());
    if ( commonWidth != pd->width() ) commonWidth = -1.0*GeV;
    if ( commonCTau != pd->cTau() ) commonCTau = -1.0*mm;
    if ( commonCharge != pd->iCharge() ) {
      switch ( commonCharge ) {
      case PDT::ChargeUndefined:
	break;
      case PDT::Positive:
	if ( PDT::negative(pd->iCharge()) ) commonCharge = PDT::Charged;
	else if ( !PDT::positive(pd->iCharge()) )
	  commonCharge = PDT::ChargeUndefined;
	break;
      case PDT::Negative:
	if ( PDT::positive(pd->iCharge()) ) commonCharge = PDT::Charged;
	else if ( !PDT::negative(pd->iCharge()) )
	  commonCharge = PDT::ChargeUndefined;
	break;
      case PDT::Charged:
	if ( !PDT::charged(pd->iCharge()) )
	  commonCharge = PDT::ChargeUndefined;
	break;
      default:
	if ( PDT::positive(commonCharge) ) {
	  if ( PDT::positive(pd->iCharge()) )
	    commonCharge = PDT::Positive;
	  else if ( PDT::negative(pd->iCharge()) )
	    commonCharge = PDT::Charged;
	  else commonCharge = PDT::ChargeUndefined;
	}
	else if ( PDT::negative(commonCharge) ) {
	  if ( PDT::negative(pd->iCharge()) )
	    commonCharge = PDT::Negative;
	  else if ( PDT::positive(pd->iCharge()) )
	    commonCharge = PDT::Charged;
	  else commonCharge = PDT::ChargeUndefined;
	}
	else commonCharge = PDT::ChargeUndefined;
      }
    }
    if ( commonSpin != pd->iSpin() ) commonSpin = PDT::SpinUndefined;
    if ( commonColor != pd->iColor() ) {
      if ( PDT::colored(commonColor) && PDT::colored(pd->iColor()) )
	commonColor = PDT::Coloured;
      else
	commonColor = PDT::ColorUndefined;
      if ( commonStable != pd->stable() ) commonStable = -1;
    }
  }
  matchingParticles.insert(pd);
}

struct ParticleOrdering {
  bool operator()(tcPDPtr p1, tcPDPtr p2) {
    return abs(p1->id()) > abs(p2->id()) ||
      ( abs(p1->id()) == abs(p2->id()) && p1->id() > p2->id() ) ||
      ( p1->id() == p2->id() && p1->fullName() > p2->fullName() );
  }
};

struct MatcherOrdering {
  bool operator()(tcPMPtr m1, tcPMPtr m2) {
    return m1->name() < m2->name() ||
      ( m1->name() == m2->name() && m1->fullName() < m2->fullName() );
  }
};

void MatcherBase::persistentOutput(PersistentOStream & os ) const {
  multiset<tcPDPtr,ParticleOrdering>
    parts(particles().begin(), particles().end());
  multiset<tcPMPtr,MatcherOrdering>
    match(matchers().begin(), matchers().end());

  os << parts << match << ounit(theMaxMass, GeV) << ounit(theMinMass, GeV)
     << ounit(commonMass, GeV) << ounit(commonWidth, GeV)
     << ounit(commonCTau, mm) << oenum(commonCharge) << oenum(commonSpin)
     << oenum(commonColor) << commonStable << theAntiPartner;
}

void MatcherBase::persistentInput(PersistentIStream & is, int) {
  is >> matchingParticles >> matchingMatchers >> iunit(theMaxMass, GeV)
     >> iunit(theMinMass, GeV) >> iunit(commonMass, GeV)
     >> iunit(commonWidth, GeV) >> iunit(commonCTau, mm) >> ienum(commonCharge)
     >> ienum(commonSpin) >> ienum(commonColor) >> commonStable
     >> theAntiPartner;
}

void MatcherBase::rebind(const TranslationMap & trans) throw(RebindException) {
  Interfaced::rebind(trans);
}

AbstractClassDescription<MatcherBase> MatcherBase::initMatcherBase;

void MatcherBase::Init() {}

