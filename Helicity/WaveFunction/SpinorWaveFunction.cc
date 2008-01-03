// -*- C++ -*-
//
// SpinorWaveFunction.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinorWaveFunction class.
//
// Author: Peter Richardson
//

#include "SpinorWaveFunction.h"
#include "SpinorBarWaveFunction.h"

using namespace ThePEG;
using namespace Helicity;

// calculate the Wavefunction
void SpinorWaveFunction::calculateWaveFunction(unsigned int ihel,DiracRep dirac) {
  // check helicity is O.K.
  Direction dir = direction();
  if(dir==intermediate) throw ThePEG::Helicity::HelicityConsistencyError() 
    << "In SpinorWaveFunction::calcluateWaveFunction "
    << "particle must be incoming or outgoing not intermediate" 
    << Exception::abortnow;
  if(ihel>1) throw ThePEG::Helicity::HelicityConsistencyError() 
    << "Invalid Helicity = " << ihel << " requested for Spinor" 
    << Exception::abortnow;
  // extract the momentum components
  double fact=-1.; if(dir==incoming){fact=1.;}
  Energy ppx=fact*px(),ppy=fact*py(),ppz=fact*pz(),pee=fact*e(),pmm=mass();
  // define and calculate some kinematic quantities
  Energy2 ptran2  = ppx*ppx+ppy*ppy;
  Energy pabs   = sqrt(ptran2+ppz*ppz);
  Energy ptran  = sqrt(ptran2);
  // first need to evalulate the 2-component helicity spinors 
  // this is the same regardless of which definition of the spinors
  // we are using
  complex <double> hel_wf[2];
  // compute the + spinor for + helicty particles and - helicity antiparticles
  if((dir==incoming && ihel== 1) || (dir==outgoing && ihel==0)) {
    // no transverse momentum 
    if(ptran==Energy()) {
      if(ppz>=Energy()) {
	hel_wf[0] = 1;
	hel_wf[1] = 0;
      }
      else {
	hel_wf[0] = 0;
	hel_wf[1] = 1;
      }
    }
    else {
      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
      SqrtEnergy rtppluspz = (ppz>=Energy()) ? sqrt(pabs+ppz) : ptran/sqrt(pabs-ppz); 
      hel_wf[0] = denominator*rtppluspz;
      hel_wf[1] = denominator/rtppluspz*complex<Energy>(ppx,ppy);
    }
  }
  // compute the - spinor for - helicty particles and + helicity antiparticles
  else {
    // no transverse momentum
    if(ptran==Energy()) {
      if(ppz>=Energy()) {
	hel_wf[0] = 0;
	hel_wf[1] = 1;
      }
      // transverse momentum 
      else {
	hel_wf[0] = -1;
	hel_wf[1] =  0;
      }
    }
    else {
      InvSqrtEnergy denominator = 1./sqrt(2.*pabs);
      SqrtEnergy rtppluspz = (ppz>=Energy()) ? sqrt(pabs+ppz) : ptran/sqrt(pabs-ppz);
      hel_wf[0] = denominator/rtppluspz*complex<Energy>(-ppx,ppy);
      hel_wf[1] = denominator*rtppluspz;
    }
  }
  // decide which definition of the spinors we are using
  SqrtEnergy eplusm,eminusm,eplusp,eminusp,upper,lower;
  switch(dirac) {
    // Haber lower energy
  case HaberDRep:
    eplusm = sqrt(pee+pmm);
    eminusm = pabs/eplusm;
    if(dir==incoming) {
      upper = eplusm;
      lower = (ihel==1) ? eminusm : -eminusm;
    }
    else {
      upper = eminusm;
      lower = (ihel==1) ? -eplusm : eplusm;
    }
    break;
  case HELASDRep:
    // HELAS
    eplusp = sqrt(pee+pabs);
    eminusp = (pmm!=Energy()) ? pmm/eplusp : SqrtEnergy();
    // set up the coefficients for the different cases
    if(dir==incoming) {
      if(ihel==1) {
	upper = eminusp;
	lower = eplusp;
      }
      else {
	upper = eplusp;
	lower = eminusp;
      }
    }
    else {
      if(ihel==1) {
	upper = -eplusp;
	lower = eminusp;
      }
      else {
	upper = eminusp;
	lower =-eplusp;
      }
    }
    break;
    // invalid choice
  default:
    ThePEG::Helicity::HelicityConsistencyError() 
      << "Invalid choice of Dirac representation in "
      << "SpinorWaveFunction::calculateWaveFunction() " << Exception::abortnow; 
    break;
  }
  // now finally we can construct the spinors
  _wf = LorentzSpinor<double>( (dir==incoming) ? u_spinortype : v_spinortype , dirac);
  _wf[0]=upper*hel_wf[0]*UnitRemoval::InvSqrtE;
  _wf[1]=upper*hel_wf[1]*UnitRemoval::InvSqrtE;
  _wf[2]=lower*hel_wf[0]*UnitRemoval::InvSqrtE;
  _wf[3]=lower*hel_wf[1]*UnitRemoval::InvSqrtE;
}

// construct the spininfo object
void SpinorWaveFunction::
constructSpinInfo(vector<LorentzSpinor<SqrtEnergy> >& wave,tPPtr part,
		  bool time, bool vertex) {
  tFermionSpinPtr inspin = !part->spinInfo() ? tFermionSpinPtr() :
    dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(2);
      wave[0]=inspin->getProductionBasisState(0);
      wave[1]=inspin->getProductionBasisState(1);
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,vertex);
    }
  }
  else {
    if(inspin) {
      inspin->decay();
      // rho matrix should be here
      wave.resize(2);
      wave[0]=inspin->getDecayBasisState(0);
      wave[1]=inspin->getDecayBasisState(1);
    }
    else {
      if(part->spinInfo()) throw ThePEG::Helicity::HelicityConsistencyError() 
	<< "Wrong type of SpinInfo for the incoming particle in "
	<< "SpinorWaveFunction::constructSpinInfo() "
	<< Exception::runerror;
      if(vertex) {
	SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      constructSpinInfo(wave,inspin,vertex);
    }
  }
}

// construct the spininfo object
void SpinorWaveFunction::
constructSpinInfo(vector<LorentzSpinor<SqrtEnergy> >& wave,RhoDMatrix& rho,
		  tPPtr part,bool time,bool vertex) {
  tFermionSpinPtr inspin = !part->spinInfo() ? tFermionSpinPtr() :
    dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(2);
      wave[0]=inspin->getProductionBasisState(0);
      wave[1]=inspin->getProductionBasisState(1);
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,vertex);
    }
    rho = RhoDMatrix(PDT::Spin1Half);rho.average();
  }
  else {
    if(inspin) {
      inspin->decay();
      rho = inspin->rhoMatrix();
      wave.resize(2);
      wave[0]=inspin->getDecayBasisState(0);
      wave[1]=inspin->getDecayBasisState(1);
    }
    else {
      if(part->spinInfo()) throw ThePEG::Helicity::HelicityConsistencyError() 
	<< "Wrong type of SpinInfo for the incoming particle in "
	<< "SpinorWaveFunction::constructSpinInfo() "
	<< Exception::runerror;
      if(vertex) {
	SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      rho = RhoDMatrix(PDT::Spin1Half);rho.average();
      constructSpinInfo(wave,inspin,vertex);
    }
  }
}

// construct the spininfo object
void SpinorWaveFunction::constructSpinInfo(vector<SpinorWaveFunction>& wave,
					   tPPtr part,bool time, bool vertex) {
  tFermionSpinPtr inspin = !part->spinInfo() ? tFermionSpinPtr() :
    dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(2);
      wave[0]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getProductionBasisState(0),
				 DummyType(),direction());
      wave[1]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getProductionBasisState(1),
				 DummyType(),direction());
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,vertex);
    }
  }
  else {
    if(inspin) {
      inspin->decay();
      // rho matrix should be here
      wave.resize(2);
      wave[0]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getDecayBasisState(0),
				 DummyType(),direction());
      wave[1]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getDecayBasisState(1),
				 DummyType(),direction());
    }
    else {
      if(part->spinInfo()) throw ThePEG::Helicity::HelicityConsistencyError() 
	<< "Wrong type of SpinInfo for the incoming particle in "
	<< "SpinorWaveFunction::constructSpinInfo() "
	<< Exception::runerror;
    if(vertex) {
      SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
      inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
      if(time) inspin->decayed(true);
      part->spinInfo(newspin);
    }
    constructSpinInfo(wave,inspin,vertex);
    }
  }
}

// construct the spininfo object
void SpinorWaveFunction::constructSpinInfo(vector<SpinorWaveFunction>& wave,
					   RhoDMatrix& rho,tPPtr part,bool time,
					   bool vertex) {
  tFermionSpinPtr inspin = !part->spinInfo() ? tFermionSpinPtr() :
    dynamic_ptr_cast<tFermionSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(2);
      wave[0]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getProductionBasisState(0),
				 DummyType(),direction());
      wave[1]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getProductionBasisState(1),
				 DummyType(),direction());
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tFermionSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,vertex);
    }
    rho = RhoDMatrix(PDT::Spin1Half);rho.average();
  }
  else {
    if(inspin) {
      inspin->decay();
      rho = inspin->rhoMatrix();
      wave.resize(2);
      wave[0]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getDecayBasisState(0),
				 DummyType(),direction());
      wave[1]=SpinorWaveFunction(getMomentum(),getParticle(),
				 inspin->getDecayBasisState(1),
				 DummyType(),direction());
    }
    else {
      if(part->spinInfo()) throw ThePEG::Helicity::HelicityConsistencyError() 
	<< "Wrong type of SpinInfo for the incoming particle in "
	<< "SpinorWaveFunction::constructSpinInfo() "
	<< Exception::runerror;
      if(vertex) {
	SpinPtr newspin=new_ptr(FermionSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tFermionSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      rho = RhoDMatrix(PDT::Spin1Half);rho.average();
      constructSpinInfo(wave,inspin,vertex);
    }
  }
}

  
void SpinorWaveFunction::conjugate() {
  _wf=_wf.conjugate();
}

SpinorBarWaveFunction SpinorWaveFunction::bar() {
  Lorentz5Momentum p = getMomentum();
  if(direction()==outgoing) p *= -1.;
  return SpinorBarWaveFunction(p,getParticle(),_wf.bar(),direction());
}	  
