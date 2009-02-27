// -*- C++ -*-
//
// StandardModelBase.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/ParticleData.h"

using namespace ThePEG;

StandardModelBase::StandardModelBase()
  : theFamilies(3), theAlphaEM(1.0/137.04), theSin2ThetaW(0.232),
    theEnu(0.0), theEe(-1.0), theEu(2.0/3.0), theEd(-1.0/3.0),
    theVnu(1.0), theVe(-0.072), theVu(0.3813), theVd(-0.6907),
    theAnu(1.0), theAe(-1.0), theAu(1.0), theAd(-1.0), recalculateEW(1),
    theNc(3), theAlphaS(0.3) {}

StandardModelBase::~StandardModelBase() {}

IBPtr StandardModelBase::clone() const {
  return new_ptr(*this);
}

IBPtr StandardModelBase::fullclone() const {
  return new_ptr(*this);
}

void StandardModelBase::doinit() {
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

double StandardModelBase::CKM(unsigned int uFamily,
				     unsigned int dFamily) const {
  if ( theCKM2Matrix.empty() ) theCKM2Matrix = theCKM->getMatrix(families());
  if ( uFamily >= theCKM2Matrix.size() ) return 0.0;
  const vector<double> & row = theCKM2Matrix[uFamily];
  if ( dFamily >= row.size() ) return 0.0;
  return row[dFamily];
}

double StandardModelBase::CKM(const ParticleData & uType,
			      const ParticleData & dType) const {
  int uFamily = abs(uType.id() - 1)/2;
  int dFamily = abs(dType.id())/2;
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

  static ClassDocumentation<StandardModelBase> documentation
    ("There is no documentation for the ThePEG::StandardModelBase class");

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
     &StandardModelBase::theEe, -1.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceEu
    ("EW/e_u",
     "The coupling between an up-type quark and a photon.",
     &StandardModelBase::theEu, 2.0/3.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceEd
    ("EW/e_d",
     "The coupling between a down-type quark and a photon.",
     &StandardModelBase::theEd, -1.0/3.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVnu
    ("EW/v_nu",
     "The vector coupling between a neutrino and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theVnu, 1.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVe
    ("EW/v_e",
     "The vector coupling between a charged lepton and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theVe, -0.072, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVu
    ("EW/v_u",
     "The vector coupling between an up-type quark and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theVu, 0.3813, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceVd
    ("EW/v_d",
     "The vector coupling between a down-type quark and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theVd, -0.6907, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAnu
    ("EW/a_nu",
     "The axial coupling between a neutrino and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theAnu, 1.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAe
    ("EW/a_e",
     "The axial coupling between a charged lepton and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theAe, -1.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAu
    ("EW/a_u",
     "The axial coupling between an up-type quark and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theAu, 1.0, 0.0, 0.0, false, false, false);
  static Parameter<StandardModelBase,double> interfaceAd
    ("EW/a_d",
     "The axial coupling between a down-type quark and a Z^0. "
     "See also command interface <interface>EW/RecalculateEW</interface>",
     &StandardModelBase::theAd, -1.0, 0.0, 0.0, false, false, false);
  static Switch<StandardModelBase> interfaceRecalculateEW
    ("EW/RecalculateEW",
     "Recalculate all parameters which depend directly on "
     "\\f$\\sin^2\\theta_W\\f$ "
     "in the initialization disregarding the values previously set. "
     "This affects only "
     "<interface>EW/v_nu</interface>, "
     "<interface>EW/v_e</interface>, "
     "<interface>EW/v_u</interface>, "
     "<interface>EW/v_d</interface>, "
     "<interface>EW/a_nu</interface>, "
     "<interface>EW/a_e</interface>, "
     "<interface>EW/a_u</interface> and "
     "<interface>EW/a_d</interface>.",
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

  interfaceRunningAlphaEM.rank(10);
  interfaceRunningAlphaS.rank(9);
  interfaceSin2ThetaW.rank(8);
  interfaceCKM.rank(7);

}

