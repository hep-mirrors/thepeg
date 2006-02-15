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
#include "ThePEG/Cuts/Cuts.h"

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
  double ctmin = -1.0;
  double ctmax = 1.0;

  Energy q = 0.0*GeV;
  try {
    q = SimplePhaseSpace::
      getMagnitude(sHat(), meMomenta()[2].mass(), meMomenta()[3].mass());
  } catch ( ImpossibleKinematics ) {
    return false;
  }

  Energy e = sqrt(sHat())/2.0;
		    
  Energy2 m22 = meMomenta()[2].mass2();
  Energy2 m32 = meMomenta()[3].mass2();
  Energy2 e0e2 = 2.0*e*sqrt(sqr(q) + m22);
  Energy2 e1e2 = 2.0*e*sqrt(sqr(q) + m22);
  Energy2 e0e3 = 2.0*e*sqrt(sqr(q) + m32);
  Energy2 e1e3 = 2.0*e*sqrt(sqr(q) + m32);
  Energy2 pq = 2.0*e*q;

  Energy2 thmin = lastCuts().minTij(mePartonData()[0], mePartonData()[2]);
  if ( thmin > 0.0*GeV2 ) ctmax = min(ctmax, (e0e2 - m22 - thmin)/pq);

  thmin = lastCuts().minTij(mePartonData()[1], mePartonData()[2]);
  if ( thmin > 0.0*GeV2 ) ctmin = max(ctmin, (thmin + m22 - e1e2)/pq);

  thmin = lastCuts().minTij(mePartonData()[1], mePartonData()[3]);
  if ( thmin > 0.0*GeV2 ) ctmax = min(ctmax, (e1e3 - m32 - thmin)/pq);

  thmin = lastCuts().minTij(mePartonData()[0], mePartonData()[3]);
  if ( thmin > 0.0*GeV2 ) ctmin = max(ctmin, (thmin + m32 - e0e3)/pq);

  Energy ptmin = max(lastCuts().minKT(mePartonData()[2]),
   		     lastCuts().minKT(mePartonData()[3]));
  if ( ptmin > 0.0*GeV ) {
    double ctm = 1.0 - sqr(ptmin/q);
    if ( ctm <= 0.0 ) return false;
    ctmin = max(ctmin, -sqrt(ctm));
    ctmax = min(ctmax, sqrt(ctm));
  }

  if ( ctmin >= ctmax ) return false;
    
  double cth = getCosTheta(ctmin, ctmax, r);

  Energy pt = q*sqrt(1.0-sqr(cth));
  theLastPhi = rnd(2.0*Constants::pi);
  meMomenta()[2].setV(Momentum3(pt*sin(phi()), pt*cos(phi()), q*cth));

  meMomenta()[3].setV(Momentum3(-pt*sin(phi()),	-pt*cos(phi()), -q*cth));

  meMomenta()[2].rescaleEnergy();
  meMomenta()[3].rescaleEnergy();

  vector<LorentzMomentum> out(2);
  out[0] = meMomenta()[2];
  out[1] = meMomenta()[3];
  tcPDVector tout(2);
  tout[0] = mePartonData()[2];
  tout[1] = mePartonData()[3];
  if ( !lastCuts().passCuts(tout, out, mePartonData()[0], mePartonData()[1]) )
    return false;

  theLastTHat = pq*cth + m22 - e0e2;
  theLastUHat = m22 + m32 - sHat() - theLastTHat;
  jacobian((pq/sHat())*Constants::pi*jacobian());
  return true;
}

double ME2to2Base::getCosTheta(double ctmin, double ctmax, const double * r) {
  double cth = 0.0;
  double zmin = 0.5*(1.0 - ctmax);
  double zmax = 0.5*(1.0 - ctmin);
  if ( zmin <= 0.0 || zmax >= 1.0 ) {
    jacobian(ctmax - ctmin);
    cth = ctmin + (*r)*jacobian();
  } else {
    double A1 = (2.0*zmax - 1.0)/(zmax*(1.0-zmax));
    double A0 = (2.0*zmin - 1.0)/(zmin*(1.0-zmin));
    double A = *r*(A1 - A0) + A0;
    double z = A < 2.0? 2.0/(sqrt(sqr(A) + 4.0) + 2 - A):
      0.5*(A - 2.0 + sqrt(sqr(A) + 4.0))/A;
    cth = 1.0 - 2.0*z;
    jacobian(2.0*(A1 - A0)*sqr(z)*sqr(1.0 - z)/(sqr(z) + sqr(1.0 - z)));
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

