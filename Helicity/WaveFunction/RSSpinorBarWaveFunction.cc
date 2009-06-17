// -*- C++ -*-
//
// RSSpinorBarWaveFunction.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RSSpinorBarWaveFunction class.
//

#include "RSSpinorBarWaveFunction.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

// calculate the Wavefunction
void RSSpinorBarWaveFunction::calculateWaveFunction(unsigned int ihel,
						    DiracRep dirac) {
  LorentzRSSpinorBar<double> news;
  if(direction()==incoming) news=LorentzRSSpinorBar<double>(u_spinortype,dirac);
  else                      news=LorentzRSSpinorBar<double>(v_spinortype,dirac);
  unsigned int ix,iy;
  static double eps=1E-5;
  assert(direction()!=intermediate);
  assert(ihel<=3);
  // massive
  if(mass() > ZERO) {
    // extract the momentum components
    // compute the normal spinors to construct the RS spinor
    Complex hel_wf[2][2];
    if(direction()==incoming) {
      // the - spinor
      hel_wf[0][0] = 0.;
      hel_wf[1][0] = 1.;
      // the + spinor
      hel_wf[0][1] = 1.;
      hel_wf[1][1] = 0.;
    }
    else {
      // the + spinor
      hel_wf[0][0] = 1.;
      hel_wf[1][0] = 0.;
      // the - spinor
      hel_wf[0][1] = 0.;
      hel_wf[1][1] = 1.;
    }
    // decide which definition of the spinors we are using
    SqrtEnergy eplusm,eplusp,upper[2],lower[2];
    switch(dirac) {
      // Haber lower energy
    case HaberDRep:
      eplusm = sqrt(2.*mass());
      if(direction()==incoming) {
	upper[0] = SqrtEnergy();
	upper[1] = SqrtEnergy();
	lower[0] = eplusm;
	lower[1] =-eplusm;
      }
      else {
	upper[0] = eplusm;
	upper[1] = eplusm;
	lower[0] = SqrtEnergy();
	lower[1] = SqrtEnergy();
      }
      break;
    case HELASDRep:
      // HELAS
      eplusp = sqrt(mass());
      if(direction()==incoming) {
	upper[0] = eplusp;
	lower[0] =-eplusp;
	upper[1] =-eplusp;
	lower[1] = eplusp;
      }
      else {
	upper[0] = eplusp;
	lower[0] = eplusp;
	upper[1] = eplusp;
	lower[1] = eplusp;
      }
      break;
    default:
      assert(false); 
    }
    // now construct the spinors
    complex<SqrtEnergy> spinor[4][2];
    for(ix=0;ix<2;++ix) {
      spinor[0][ix] = upper[ix]*hel_wf[0][ix];
      spinor[1][ix] = upper[ix]*hel_wf[1][ix];
      spinor[2][ix] = lower[ix]*hel_wf[0][ix];
      spinor[3][ix] = lower[ix]*hel_wf[1][ix];
    }
    // compute the polarization vectors to construct the RS spinor
    Complex vec[4][3],ii(0.,1.);
    double ort=1./sqrt(2.);
    if(direction()==incoming) {
      vec[0][0] = ort;
      vec[1][0] = ort*ii;
      vec[2][0] = 0.;
      vec[3][0] = 0.;
      vec[0][1] = 0.;
      vec[1][1] = 0.;
      vec[2][1] =-1.;
      vec[3][1] = 0.;
      vec[0][2] =-ort;
      vec[1][2] = ort*ii;
      vec[2][2] = 0.;
      vec[3][2] = 0.;
    }
    else {
      vec[0][0] =-ort;
      vec[1][0] = ort*ii;
      vec[2][0] = 0.;
      vec[3][0] = 0.;
      vec[0][1] = 0.;
      vec[1][1] = 0.;
      vec[2][1] = 1.;
      vec[3][1] = 0.;
      vec[0][2] = ort;
      vec[1][2] = ort*ii;
      vec[2][2] = 0.;
      vec[3][2] = 0.;
    }
    // now we can put the bits together to compute the RS spinor
    double or3(sqrt(1./3.)),tor3(sqrt(2./3.));
    if(ihel==0) {
      for(ix=0;ix<4;++ix)
	for(iy=0;iy<4;++iy)
	  news(ix,iy)=UnitRemoval::InvSqrtE*vec[ix][0]*spinor[iy][0];
    }
    else if(ihel==1) {
      for(ix=0;ix<4;++ix)
	for(iy=0;iy<4;++iy)
	  news(ix,iy)=UnitRemoval::InvSqrtE*
	    (or3*vec[ix][0]*spinor[iy][1]+tor3*vec[ix][1]*spinor[iy][0]);
    }
    else if(ihel==2) {
      for(ix=0;ix<4;++ix)
	for(iy=0;iy<4;++iy)
	  news(ix,iy)=UnitRemoval::InvSqrtE*
	    (or3*vec[ix][2]*spinor[iy][0]+tor3*vec[ix][1]*spinor[iy][1]);
    }
    else if(ihel==3) {
      for(ix=0;ix<4;++ix)
	for(iy=0;iy<4;++iy)
	  news(ix,iy)=UnitRemoval::InvSqrtE*(vec[ix][2]*spinor[iy][1]);
    }
    // boost the spinor to the lab frame
    Boost boostv = getMomentum().boostVector();
    if(boostv.mag()>eps) _wf=news.boost(boostv);
    else                 _wf=news;
  }
  // special for the massless case in the lab frame rather than the rest frame
  else {
    // only two valid helicities in this case
    assert(ihel==0||ihel==3);
    // extract the momentum components
    double fact=-1.; if(direction()==incoming){fact=1.;}
    Energy ppx=fact*px(),ppy=fact*py(),ppz=fact*pz(),pee=fact*e(),pmm=mass();
    // define and calculate some kinematic quantities
    Energy2 ptran2 = ppx*ppx+ppy*ppy;
    Energy pabs   = sqrt(ptran2+ppz*ppz);
    Energy ptran  = sqrt(ptran2);
    Complex hel_wf[2],vec[4],ii(0.,1.);
    double root = 1./sqrt(2.);
    // positve 3/2 helicity spinor
    if((direction()==incoming && ihel==3)||(direction()==outgoing &&ihel==0)) {
      // the polarization vector
      // first the no pt case
      if(ptran==ZERO) {
	double sgnz;
	if(ppz<ZERO){sgnz=-1.;}
	else{sgnz=1.;}
	vec[0]= root;
	vec[1]= sgnz*root*ii;
	vec[2]=0.;
	vec[3]=0.;
	if(ppz>=ZERO) {
	  hel_wf[0] = 0;
	  hel_wf[1] = 1;
	}
	else {
	  hel_wf[0] =-1;
	  hel_wf[1] = 0;
	}
      }
      else {
	InvEnergy opabs=1./pabs;
	InvEnergy opt  =1./ptran;
	vec[0]=root*Complex(ppz*ppx*opabs*opt,-ppy*opt);
	vec[1]=root*Complex(ppz*ppy*opabs*opt,ppx*opt);
	vec[2]=-ptran*opabs*root;
	vec[3]=0.;
	InvSqrtEnergy denominator = 1.0/sqrt(2.*pabs);
	SqrtEnergy rtppluspz;
	if(ppz>=ZERO) rtppluspz = sqrt(pabs+ppz);
	else              rtppluspz = ptran/sqrt(pabs-ppz);
	hel_wf[0] = denominator/rtppluspz*complex<Energy>(-ppx,-ppy);
	hel_wf[1] = denominator*rtppluspz;
      }
    }
    // negative 3/2 helicity spinor
    else {
      // the polarization vector
      // first the no pt case
      if(ptran==ZERO) {
	double sgnz;
	if(ppz<ZERO){sgnz=-1.;}
	else{sgnz=1.;}
	vec[0]=-root;
	vec[1]= sgnz*root*ii;
	vec[2]=0.;
	vec[3]=0.;
	if(ppz>=ZERO) {
	  hel_wf[0] = 1;
	  hel_wf[1] = 0;
	}
	// transverse momentum 
	else {
	  hel_wf[0] = 0;
	  hel_wf[1] = 1;
	}
      }
      else {
	InvEnergy opabs=1./pabs;
	InvEnergy opt  =1./ptran;
	vec[0]=root*Complex(-ppz*ppx*opabs*opt,-ppy*opt);
	vec[1]=root*Complex(-ppz*ppy*opabs*opt, ppx*opt);
	vec[2]=ptran*opabs*root;
	vec[3]=0.;
	InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
	SqrtEnergy rtppluspz;
	if(ppz>=ZERO) rtppluspz = sqrt(pabs+ppz);
	else              rtppluspz = ptran/sqrt(pabs-ppz); 
	hel_wf[0] = denominator*rtppluspz;
	hel_wf[1] = denominator/rtppluspz*complex<Energy>(ppx,-ppy);
      }
    }
    // decide which definition of the spinors we are using
    SqrtEnergy eplusm,eminusm,eplusp,eminusp,upper,lower;
    switch(dirac) {
      // Haber lower energy
    case HaberDRep:
      eplusm = sqrt(pee+pmm);
      eminusm = pabs/eplusm;
      if(direction()==incoming) {
	upper = eminusm;
	if(ihel==3) lower = eplusm;
	else        lower =-eplusm;
      }
      else {
	upper = eplusm;
	if(ihel==3) lower =-eminusm;
	else        lower = eminusm;
      }
      break;
    case HELASDRep:
      // HELAS
      eplusp = sqrt(pee+pabs);
      if(pmm!=ZERO) eminusp=pmm/eplusp;
      else              eminusp=SqrtEnergy();
      // set up the coefficients for the different cases
      if(direction()==incoming) {
	if(ihel==3) {
	  upper = eminusp;
	  lower =-eplusp;
	}
	else {
	  upper =-eplusp;
	  lower = eminusp;
	}
      }
      else {
	if(ihel==3) {
	  upper = eplusp;
	  lower = eminusp;
	}
	else {
	  upper = eminusp;
	  lower = eplusp;
	}
      }
      break;
      // invalid choice
    default:
      assert(false);
    }
    complex<SqrtEnergy> spinor[4]={upper*hel_wf[0],upper*hel_wf[1],
				   lower*hel_wf[0],lower*hel_wf[1]};
    for(ix=0;ix<4;++ix) 
      for(iy=0;iy<4;++iy)
	news(ix,iy) = UnitRemoval::InvSqrtE*vec[ix]*spinor[iy];
    _wf=news;
  }
}

void RSSpinorBarWaveFunction::
calculateWaveFunctions(vector<LorentzRSSpinorBar<SqrtEnergy> > & waves,
		       tPPtr particle,Direction dir) {
  tRSFermionSpinPtr inspin = !particle->spinInfo() ? tRSFermionSpinPtr() :
    dynamic_ptr_cast<tRSFermionSpinPtr>(particle->spinInfo());
  waves.resize(4);
  // spin info object exists
  if(inspin) {
    if(dir==outgoing) {
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = inspin->getProductionBasisState(ix).bar();
    }
    else {
      inspin->decay();
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = inspin->getDecayBasisState(ix).bar();
    }
  }
  // do the calculation
  else {
    assert(!particle->spinInfo());
    RSSpinorBarWaveFunction wave(particle->momentum(),particle->dataPtr(),dir);
    for(unsigned int ix=0;ix<4;++ix) {
      wave.reset(ix);
      waves[ix] = wave.dimensionedWf();
    }
  }
}

void RSSpinorBarWaveFunction::
calculateWaveFunctions(vector<RSSpinorBarWaveFunction> & waves,
		       tPPtr particle,Direction dir) {
  tRSFermionSpinPtr inspin = !particle->spinInfo() ? tRSFermionSpinPtr() :
    dynamic_ptr_cast<tRSFermionSpinPtr>(particle->spinInfo());
  waves.resize(4);
  // spin info object exists
  if(inspin) {
    if(dir==outgoing) {
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = RSSpinorBarWaveFunction(particle,
					    inspin->getProductionBasisState(ix).bar(),
					    dir);
    }
    else {
      inspin->decay();
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = RSSpinorBarWaveFunction(particle,
					    inspin->getDecayBasisState(ix).bar(),
					    dir);
    }
  }
  // do the calculation
  else {
    assert(!particle->spinInfo());
    RSSpinorBarWaveFunction wave(particle->momentum(),particle->dataPtr(),dir);
    for(unsigned int ix=0;ix<4;++ix) {
      wave.reset(ix);
      waves[ix] = wave;
    }
  }
}

void RSSpinorBarWaveFunction::
calculateWaveFunctions(vector<LorentzRSSpinorBar<SqrtEnergy> > & waves,
		       RhoDMatrix & rho,
		       tPPtr particle,Direction dir) {
  tRSFermionSpinPtr inspin = !particle->spinInfo() ? tRSFermionSpinPtr() :
    dynamic_ptr_cast<tRSFermionSpinPtr>(particle->spinInfo());
  waves.resize(4);
  // spin info object exists
  if(inspin) {
    if(dir==outgoing) {
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = inspin->getProductionBasisState(ix).bar();
      rho = RhoDMatrix(PDT::Spin3Half);
    }
    else {
      inspin->decay();
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = inspin->getDecayBasisState(ix).bar();
      rho = inspin->rhoMatrix();
    }
  }
  // do the calculation
  else {
    assert(!particle->spinInfo());
    RSSpinorBarWaveFunction wave(particle->momentum(),particle->dataPtr(),dir);
    for(unsigned int ix=0;ix<4;++ix) {
      wave.reset(ix);
      waves[ix] = wave.dimensionedWf();
    }
    rho = RhoDMatrix(PDT::Spin3Half);
  }
}

void RSSpinorBarWaveFunction::
calculateWaveFunctions(vector<RSSpinorBarWaveFunction> & waves,
		       RhoDMatrix & rho,
		       tPPtr particle,Direction dir) {
  tRSFermionSpinPtr inspin = !particle->spinInfo() ? tRSFermionSpinPtr() :
    dynamic_ptr_cast<tRSFermionSpinPtr>(particle->spinInfo());
  waves.resize(4);
  // spin info object exists
  if(inspin) {
    if(dir==outgoing) {
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = RSSpinorBarWaveFunction(particle,
					    inspin->getProductionBasisState(ix).bar(),
					    dir);
      rho = RhoDMatrix(PDT::Spin3Half);
    }
    else {
      inspin->decay();
      for(unsigned int ix=0;ix<4;++ix)
	waves[ix] = RSSpinorBarWaveFunction(particle,
					    inspin->getDecayBasisState(ix).bar(),
					    dir);
      rho = inspin->rhoMatrix();
    }
  }
  // do the calculation
  else {
    assert(!particle->spinInfo());
    RSSpinorBarWaveFunction wave(particle->momentum(),particle->dataPtr(),dir);
    for(unsigned int ix=0;ix<4;++ix) {
      wave.reset(ix);
      waves[ix] = wave;
    }
    rho = RhoDMatrix(PDT::Spin3Half);
  }
}

void RSSpinorBarWaveFunction::
constructSpinInfo(const vector<LorentzRSSpinorBar<SqrtEnergy> > & waves,
		  tPPtr particle,Direction dir, bool time) {
  assert(waves.size()==4);
  tRSFermionSpinPtr inspin = !particle->spinInfo() ? tRSFermionSpinPtr() :
    dynamic_ptr_cast<tRSFermionSpinPtr>(particle->spinInfo());
  if(inspin) {
    for(unsigned int ix=0;ix<4;++ix)
      if(dir==outgoing) inspin->setBasisState(ix,waves[ix].bar());
      else              inspin->setDecayState(ix,waves[ix].bar());
  }
  else {
    RSFermionSpinPtr temp = new_ptr(RSFermionSpinInfo(particle->momentum(),time));
    particle->spinInfo(temp);
    for(unsigned int ix=0;ix<4;++ix)
      if(dir==outgoing) temp->setBasisState(ix,waves[ix].bar());
      else              temp->setDecayState(ix,waves[ix].bar());
  }
}
