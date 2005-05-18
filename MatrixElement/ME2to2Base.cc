// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ME2to2Base class.
//

#include "ME2to2Base.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Switch.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ME2to2Base.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/Handlers/KinematicalCuts.h"

using namespace ThePEG;

ME2to2Base::~ME2to2Base() {}

Energy2 ME2to2Base::scale() const {
  switch ( scaleChoice() ) {
  case 1:
    return -tHat()*uHat()/(tHat() + uHat());
  default:
    return tHat()*uHat()/sHat();
  }
  
}

int ME2to2Base::nDim() const {
  return 1;
}

void ME2to2Base::setKinematics() {
  MEBase::setKinematics();
  theLastTHat = (meMomenta()[0] - meMomenta()[2]).m2();
  theLastUHat = (meMomenta()[1] - meMomenta()[2]).m2();
  theLastPhi = meMomenta()[2].phi();
}

bool ME2to2Base::generateKinematics(const double * r) {
  double ctmin = lastCuts().cTHMin();
  double ctmax = lastCuts().cTHMax();

  Energy q = 0.0*GeV;
  try {
    q = SimplePhaseSpace::
      getMagnitude(sHat(), meMomenta()[2].mass(), meMomenta()[3].mass());
  } catch ( ImpossibleKinematics ) {
    return false;
  }
					    
  Energy2 e1e3 = 2.0*meMomenta()[0].e()*sqrt(q*q + meMomenta()[2].mass2());
  Energy2 pq = 2.0*meMomenta()[0].z()*q;
  Energy2 m132 = meMomenta()[0].mass2() + meMomenta()[2].mass2();
  Energy2 m242 = meMomenta()[1].mass2() + meMomenta()[3].mass2();
  if ( lastCuts().tHatMin() > 0.0*GeV2 )
    ctmax = min(ctmax, (e1e3 - lastCuts().tHatMin() - m132)/pq);
  if ( lastCuts().tHatMax() > 0.0*GeV2 )
    ctmin = max(ctmin, (e1e3 - lastCuts().tHatMax() - m132)/pq);
  if ( lastCuts().uHatMin() > 0.0*GeV2 )
    ctmin = max(ctmin, (e1e3 - sHat() + lastCuts().uHatMin() - m242)/pq);
  if ( lastCuts().uHatMax() > 0.0*GeV2 )
    ctmax = min(ctmax, (e1e3 - sHat() + lastCuts().uHatMax() - m242)/pq);
  if ( lastCuts().pTHatMin() > 0.0*GeV ) {
    double ctm = 1.0 - sqr(lastCuts().pTHatMin()/q);
    if ( ctm <= 0.0 ) return false;
    ctmin = max(ctmin, -sqrt(ctm));
    ctmax = min(ctmax, sqrt(ctm));
  }
  if ( ctmin >= ctmax ) return false;
    
  double cth = getCosTheta(ctmin, ctmax, r);

  theLastPhi = rnd(2.0*Constants::pi);
  meMomenta()[2].setV(Momentum3(q*sqrt(1.0-sqr(cth))*sin(phi()),
				q*sqrt(1.0-sqr(cth))*cos(phi()), q*cth));

  meMomenta()[3].setV(Momentum3(-q*sqrt(1.0-sqr(cth))*sin(phi()),
				-q*sqrt(1.0-sqr(cth))*cos(phi()), -q*cth));
  meMomenta()[2].rescaleEnergy();
  meMomenta()[3].rescaleEnergy();
  theLastTHat = (meMomenta()[0] - meMomenta()[2]).m2();
  theLastUHat = (meMomenta()[1] - meMomenta()[2]).m2();
  jacobian((pq/sHat())*Constants::pi*jacobian());
  return true;
}

double ME2to2Base::getCosTheta(double ctmin, double ctmax, const double * r) {
  double cth = 0.0;
  if ( ctmin <= -1.0 || ctmax >= 1.0 ) {
    jacobian(ctmax - ctmin);
    cth = ctmin + (*r)*jacobian();
  } else {
    double zmin = 0.5*(1.0 - ctmax);
    double zmax = 0.5*(1.0 - ctmin);
    double A1 = (2.0*zmax - 1.0)/(zmax*(1.0-zmax));
    double A0 = (2.0*zmin - 1.0)/(zmin*(1.0-zmin));
    double A = *r*(A1 - A0) + A0;
    double z = 0.5*(A - 2.0 + sqrt(sqr(A) + 4.0))/A;
    cth = 2.0*z-1;
    jacobian(2.0*(A1 - A0)/(1.0/sqr(z) + 1.0/sqr(1.0 - z)));
  }
  return cth;
}  

CrossSection ME2to2Base::dSigHatDR() const {
  return me2()*jacobian()/(16.0*sqr(Constants::pi)*sHat());
}

void ME2to2Base::persistentOutput(PersistentOStream & os) const {
  os << theScaleChoice << ounit(theLastTHat, GeV2) << ounit(theLastUHat, GeV2)
     << theLastPhi;
}

void ME2to2Base::persistentInput(PersistentIStream & is, int) {
  is >> theScaleChoice >> iunit(theLastTHat, GeV2) >> iunit(theLastUHat, GeV2)
     >> theLastPhi;
}

AbstractClassDescription<ME2to2Base> ME2to2Base::initME2to2Base;
// Definition of the static class description member.

Switch<ME2to2Base,int> & ME2to2Base::interfaceScaleChoice() {
  static Switch<ME2to2Base,int> dummy
    ("ScaleChoice",
     "Different options for calculating the scale of the generated "
     "hard sub-process.",
     &ME2to2Base::theScaleChoice, 0, false, false);
  return dummy;
}

void ME2to2Base::Init() {

  static ClassDocumentation<ME2to2Base> documentation
    ("The ThePEG::ME2to2Base class may be used as a base class "
     "for all \\f$2\\rightarrow 2\\f$ matrix elements.");

  static SwitchOption interfaceScaleChoice0
    (interfaceScaleChoice(),
     "that.uhat/shat", "\\f$\\hat{t}\\hat{u}/\\hat{s}\\f$", 0);

  static SwitchOption interfaceScaleChoice1
    (interfaceScaleChoice(),
     "that.uhat/(that+uhat)",
     "\\f$-\\hat{t}\\hat{u}/(\\hat{t}+\\hat{u})\\f$", 1);

}

