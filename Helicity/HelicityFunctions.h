// -*- C++ -*-
//
// HelicityFunctions.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2017 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 3 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_HelicityFunctions_H
#define ThePEG_HelicityFunctions_H
//
// This is the declaration of the HelicityFunctions header for common functions
// used in helicity calculations to avoid duplication of code

#include "ThePEG/Vectors/LorentzVector.h"

namespace ThePEG {
namespace Helicity {
namespace HelicityFunctions {

inline LorentzPolarizationVector polarizationVector(const Lorentz5Momentum & p,
						    unsigned int ihel,
						    Direction dir,
						    VectorPhase vphase=default_vector_phase) {
  // check the direction
  assert(dir!=intermediate);
  // special helicity combination for guge invariance tests
  if(ihel==10) return p*UnitRemoval::InvE;
  // check a valid helicity combination
  assert(ihel==0 || ihel == 2 || (ihel==1 && p.mass()>ZERO));
  // convert the helicitty from 0,1,2 to -1,0,1
  int jhel=ihel-1;
  // extract the momentum components
  double fact = dir==outgoing ? -1 : 1;
  Energy ppx=fact*p.x(),ppy=fact*p.y(),ppz=fact*p.z(),pee=fact*p.e(),pmm=p.mass();
  // calculate some kinematic quantites
  Energy2 pt2 = ppx*ppx+ppy*ppy;
  Energy pabs = sqrt(pt2+ppz*ppz);
  Energy pt = sqrt(pt2);
  // overall phase of the vector
  Complex phase(1.);
  if(vphase==vector_phase) {
    if(pt==ZERO || ihel==1) phase = 1.;
    else if(ihel==0)            phase = Complex(ppx/pt,-fact*ppy/pt);
    else                        phase = Complex(ppx/pt, fact*ppy/pt);
  }
  if(ihel!=1) phase = phase/sqrt(2.);
  // first the +/-1 helicity states
  if(ihel!=1) {
    // first the zero pt case
    if(pt==ZERO) {
      double sgnz = ppz<ZERO ? -1. : 1.;
      return LorentzPolarizationVector(-complex<double>(jhel)*phase,
				       sgnz*phase*complex<double>(0,-fact),
				       0.,0.);
    }
    else {
      InvEnergy opabs=1./pabs;
      InvEnergy opt  =1./pt;
      return LorentzPolarizationVector(phase*complex<double>(-jhel*ppz*ppx*opabs*opt, fact*ppy*opt),
				       phase*complex<double>(-jhel*ppz*ppy*opabs*opt,-fact*ppx*opt),
				       double(jhel*pt*opabs)*phase,0.);
    }
  }
  // 0 component for massive vectors
  else {
    if(pabs==ZERO) {
      return LorentzPolarizationVector(0.,0.,1.,0.);
    }
    else {
      InvEnergy empabs=pee/pmm/pabs;
      return LorentzPolarizationVector(double(empabs*ppx),double(empabs*ppy),
				       double(empabs*ppz),double(pabs/pmm));
    }
  }
}
 
}
}
}
  
#endif /* ThePEG_HelicityFunctions_H */
