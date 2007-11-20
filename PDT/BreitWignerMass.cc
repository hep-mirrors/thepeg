// -*- C++ -*-
//
// BreitWignerMass.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BreitWignerMass class.
//

#include "BreitWignerMass.h"
#include "ThePEG/PDT/ParticleData.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Repository/UseRandom.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "BreitWignerMass.tcc"
#endif

using namespace ThePEG;

BreitWignerMass::~BreitWignerMass() {}

Energy BreitWignerMass::mass(const ParticleData & pd) const {
  Energy ret = 0.0*GeV;
  do {
    ret = UseRandom::rndRelBW(pd.mass(), pd.width(), pd.widthCut());
//     ret = RandBreitWigner::shootM2(UseRandom::currentEngine(),
// 				   pd.mass()/GeV, pd.width()/GeV,
// 				   pd.widthCut()/GeV)*GeV;
  } while ( ret > pd.massMax() || ret < pd.massMin() );
  return ret;
}

NoPIOClassDescription<BreitWignerMass> BreitWignerMass::initBreitWignerMass;

void BreitWignerMass::Init() {

  static ClassDocumentation<BreitWignerMass> documentation
    ("Generates masses of particle instances according to a Breit-Wigner "
     "distribution.");

}

