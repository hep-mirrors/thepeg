// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the StandardModelBase class.
//

#include "StandardModelBase.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/PDT/ParticleData.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "StandardModelBase.tcc"
#endif

using namespace ThePEG;

StandardModelBase::StandardModelBase()
  : theFamilies(3), theAlphaEM(1.0/137.04), theSin2ThetaW(0.232),
    theEnu(0.0), theEe(-1.0), theEu(2.0/3.0), theEd(-1.0/3.0),
    theVnu(1.0), theVe(-0.072), theVu(0.3813), theVd(-0.6907),
    theAnu(1.0), theAe(-1.0), theAu(1.0), theAd(-1.0), recalculateEW(1),
    theNc(3), theAlphaS(0.3) {}

StandardModelBase::StandardModelBase(const StandardModelBase & x)
  : Interfaced(x), theFamilies(x.theFamilies), theAlphaEM(x.theAlphaEM),
    theRunningAlphaEM(x.theRunningAlphaEM), theSin2ThetaW(x.theSin2ThetaW),
    theEnu(x.theEnu), theEe(x.theEe), theEu(x.theEu), theEd(x.theEd),
    theVnu(x.theVnu), theVe(x.theVe), theVu(x.theVu), theVd(x.theVd),
    theAnu(x.theAnu), theAe(x.theAe), theAu(x.theAu), theAd(x.theAd),
    recalculateEW(x.recalculateEW), theCKM(x.theCKM),
    theCKM2Matrix(x.theCKM2Matrix), theNc(x.theNc), theAlphaS(x.theAlphaS),
    theRunningAlphaS(x.theRunningAlphaS) {}

StandardModelBase::~StandardModelBase() {}

IBPtr StandardModelBase::clone() const {
  return new_ptr(*this);
}

IBPtr StandardModelBase::fullclone() const {
  return new_ptr(*this);
}

void StandardModelBase::doinit() throw(InitException) {
  if ( recalculateEW ) {
    theAnu = theEnu < 0? -1.0: 1.0;
    theAe = theEe < 0? -1.0: 1.0;
    theAd = theEd < 0? -1.0: 1.0;
    theAu = theEu < 0? -1.0: 1.0;
    theVnu = theAnu - 4.0*theEnu*sin2ThetaW();
    theVe = theAe - 4.0*theEe*sin2ThetaW();;
    theVd = theAd - 4.0*theEd*sin2ThetaW();;
    theVu = theAu - 4.0*theEu*sin2ThetaW();
  }
  theRunningAlphaEM->init();
  theCKM->init();
  theRunningAlphaS->init();
  theCKM2Matrix = theCKM->getMatrix(families());
  Interfaced::doinit();
}

double StandardModelBase::CKM(const ParticleData & uType,
			      const ParticleData & dType) const {
  int uFamily = abs(uType.id())/2;
  int dFamily = abs(dType.id())/2+1;
  return CKM(uFamily, dFamily);
}

void StandardModelBase::persistentOutput(PersistentOStream & os) const {
  os << theFamilies << theAlphaEM << theRunningAlphaEM << theSin2ThetaW
     << theEnu << theEe << theEu << theEd << theVnu << theVe << theVu << theVd
     << theAnu << theAe << theAu << theAd << recalculateEW << theCKM
     << theNc << theAlphaS << theRunningAlphaS;
}

void StandardModelBase::persistentInput(PersistentIStream & is, int) {
  is >> theFamilies >> theAlphaEM >> theRunningAlphaEM >> theSin2ThetaW
     >> theEnu >> theEe >> theEu >> theEd >> theVnu >> theVe >> theVu >> theVd
     >> theAnu >> theAe >> theAu >> theAd >> recalculateEW >> theCKM
     >> theNc >> theAlphaS >> theRunningAlphaS;
}

ClassDescription<StandardModelBase> StandardModelBase::initStandardModelBase;

void StandardModelBase::Init() {

  static Parameter<StandardModelBase,unsigned int> interfaceFamilies
    ("NumberOfFamilies",
     "The number of families assumed in the Standard model.",
     &StandardModelBase::theFamilies, 0, 3, 5,
     false, false, true);

  static Parameter<StandardModelBase,double> interfaceAlphaEM
    ("EW/AlphaEM",
     "The electro-magnetic coupling constant at zero momentum transfer.",
     &StandardModelBase::theAlphaEM, 1.0/137.04, 0.0, 100.0,
     false, false, true);

  static Reference<StandardModelBase,AlphaEMBase> interfaceRunningAlphaEM
    ("EW/RunningAlphaEM",
     "Reference to an object capable of calculating the running "
     "electro-magnetic coupling at a given scale",
     &StandardModelBase::theRunningAlphaEM, false, false, true, false);

  static Parameter<StandardModelBase,double> interfaceSin2ThetaW
    ("EW/Sin2ThetaW",
     "The square of the sine of the weak mixing angel",
     &StandardModelBase::theSin2ThetaW, 0.232, 0.0, 1.0, false, false, true);

  static Parameter<StandardModelBase,double> interfaceEnu
    ("EW/e_nu",
     "The coupling between a neutrino and a photon.",
     &StandardModelBase::theEnu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceEe
    ("EW/e_e",
     "The coupling between a charged lepton and a photon.",
     &StandardModelBase::theEe, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceEu
    ("EW/e_u",
     "The coupling between an up-type quark and a photon.",
     &StandardModelBase::theEu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceEd
    ("EW/e_d",
     "The coupling between a down-type quark and a photon.",
     &StandardModelBase::theEd, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVnu
    ("EW/v_nu",
     "The vector coupling between a neutrino and a Z^0.",
     &StandardModelBase::theVnu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVe
    ("EW/v_e",
     "The vector coupling between a charged lepton and a Z^0.",
     &StandardModelBase::theVe, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVu
    ("EW/v_u",
     "The vector coupling between an up-type quark and a Z^0.",
     &StandardModelBase::theVu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVd
    ("EW/v_d",
     "The vector coupling between a down-type quark and a Z^0.",
     &StandardModelBase::theVd, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAnu
    ("EW/a_nu",
     "The axial coupling between a neutrino and a Z^0.",
     &StandardModelBase::theAnu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAe
    ("EW/a_e",
     "The axial coupling between a charged lepton and a Z^0.",
     &StandardModelBase::theAe, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAu
    ("EW/a_u",
     "The axial coupling between an up-type quark and a Z^0.",
     &StandardModelBase::theAu, 0.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAd
    ("EW/a_d",
     "The axial coupling between a down-type quark and a Z^0.",
     &StandardModelBase::theAd, 0.0, 0.0, 0.0, false, false, false);
  static Switch<StandardModelBase> interfaceRecalculateEW
    ("EW/RecalculateEW",
     "Recalculate all parameters which depend directly on $\\sin^2\\theta_W$ "
     "in the initialization disregarding the values previously set. "
     "This affects only \\parameter{EW/v_nu}, "
     "\\parameter{EW/v_e}, \\parameter{EW/v_u}, "
     "\\parameter{EW/v_d}, \\parameter{EW/a_nu}, "
     "\\parameter{EW/a_e}, \\parameter{EW/a_u} and "
     "\\parameter{EW/a_d}.",
     &StandardModelBase::recalculateEW, 1, false, false);
  static SwitchOption interfaceRecalculateEWOn
    (interfaceRecalculateEW, "On", "On", 1);
  static SwitchOption interfaceRecalculateEWOff
    (interfaceRecalculateEW, "Off", "Off", 0);

  static Reference<StandardModelBase,CKMBase> interfaceCKM
    ("EW/CKM",
     "Reference to an object capable of calculating the square of the "
     "elements of the Cabibbo-Kobayashi-Maskawa flavour mixing matrix",
     &StandardModelBase::theCKM, false, false, true, false);

  static Parameter<StandardModelBase,unsigned int> interfaceNc
    ("QCD/Nc",
     "The number of colours assumed in the Standard model.",
     &StandardModelBase::theNc, 0, 3, 10,
     false, false, true);

  static Parameter<StandardModelBase,double> interfaceAlphaS
    ("QCD/AlphaS",
     "The (fixed) strong coupling constant.",
     &StandardModelBase::theAlphaS, 0.2, 0.0, 100.0,
     false, false, true);

  static Reference<StandardModelBase,AlphaSBase> interfaceRunningAlphaS
    ("QCD/RunningAlphaS",
     "Reference to an object capable of calculating the running "
     "stron coupling at a given scale",
     &StandardModelBase::theRunningAlphaS, false, false, true, false);

}

