// -*- C++ -*-
//
// VectorWaveFunction.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the VectorWaveFunction class.
//
// Author: Peter Richardson
//

#include "VectorWaveFunction.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

// calculate the Wavefunction
void VectorWaveFunction::calculateWaveFunction(unsigned int ihel,VectorPhase vphase) {
  Direction dir=direction();
  if(dir==intermediate)
    throw ThePEG::Helicity::HelicityConsistencyError() 
      << "In VectorWaveFunction::calcluateWaveFunction "
      << "particle must be incoming or outgoing not intermediate" 
      << Exception::abortnow;
  // check a valid helicity combination
  if(ihel==0 || ihel==2||(ihel==1&&mass()>Energy())) {
    int jhel=ihel-1;
    // extract the momentum components
    double fact=-1.; if(dir==incoming){fact=1.;}
    Energy ppx=fact*px(),ppy=fact*py(),ppz=fact*pz(),pee=fact*e(),pmm=mass();
    // calculate some kinematic quantites;
    Energy2 pt2 = ppx*ppx+ppy*ppy;
    Energy pabs = sqrt(pt2+ppz*ppz);
    Energy pt = sqrt(pt2);
    // overall phase of the vector
    Complex phase;
    if(vphase==vector_phase) {
      if(pt==Energy() || ihel==1) phase = 1.;
      else if(ihel==0)            phase = Complex(ppx/pt,-fact*ppy/pt);
      else                        phase = Complex(ppx/pt, fact*ppy/pt);
    }
    else                          phase = 1.;
    if(ihel!=1) phase = phase/sqrt(2.);
    // first the +/-1 helicity states
    if(ihel!=1) {
      // first the no pt case
      if(pt==Energy()) {
	double sgnz;
	sgnz = ppz<Energy() ? -1. : 1.;
	_wf.setX(-complex<double>(jhel)*phase);
	_wf.setY(sgnz*phase*complex<double>(0,-fact));
	_wf.setZ(0.);
	_wf.setT(0.);
      }
      else {
	InvEnergy opabs=1./pabs;
	InvEnergy opt  =1./pt;
	_wf.setX(phase*complex<double>(-jhel*ppz*ppx*opabs*opt, fact*ppy*opt));
	_wf.setY(phase*complex<double>(-jhel*ppz*ppy*opabs*opt,-fact*ppx*opt));
	_wf.setZ(double(jhel*pt*opabs)*phase);
	_wf.setT(0.);
      }
    }
    // 0 component for massive vectors
    else {
      if(pabs==Energy()) {
	_wf.setX(0.);
	_wf.setY(0.);
	_wf.setZ(1.);
	_wf.setT(0.);
      }
      else {
	InvEnergy empabs=pee/pmm/pabs;
	_wf.setX(double(empabs*ppx));
	_wf.setY(double(empabs*ppy));
	_wf.setZ(double(empabs*ppz));
	_wf.setT(double(pabs/pmm));
      }
    }
  }
  // special return the momentum as a check of gauge invariance
  else if(ihel==10) {
    _wf.setX(double(px()/MeV));
    _wf.setY(double(py()/MeV));
    _wf.setZ(double(pz()/MeV));
    _wf.setT(double(e()/MeV));
  }
  // issue warning and return zero
  else {
    ThePEG::Helicity::HelicityConsistencyError() 
      << "Invalid Helicity = " << ihel << " requested for Vector " 
      << getParticle()->PDGName() << Exception::abortnow;
    _wf.setX(0.);_wf.setY(0.);_wf.setZ(0.);_wf.setT(0.);
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<LorentzPolarizationVector>& wave,
					   tVectorSpinPtr spin,bool massless,
					   VectorPhase phase,bool vertex) {
  wave.resize(3);
  for(unsigned int ix=0;ix<3;++ix) {
    // calculate the wavefunction for the first helicity
    if(massless&&ix==1) _wf=LorentzPolarizationVector();
    else reset(ix,phase);
    // add to output array
    wave[ix] = _wf;
    // setup the spininfo object
    if(vertex) {
      if(direction()==outgoing) spin->setBasisState(ix,_wf);
      else                      spin->setDecayState(ix,_wf.conjugate());
    }
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<LorentzPolarizationVector>& wave,
					   tPPtr part,bool time,
					   bool massless,VectorPhase phase,
					   bool vertex) {
  tVectorSpinPtr inspin;
  if(part->spinInfo()) inspin=dynamic_ptr_cast<tVectorSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix)
	wave[ix]=inspin->getProductionBasisState(ix);
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tVectorSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
  else {
    if(inspin) {
      inspin->decay();
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix)
	wave[ix]=inspin->getDecayBasisState(ix);
    }
    else {
      if(part->spinInfo())
	throw ThePEG::Helicity::HelicityConsistencyError() 
	  << "Wrong type of SpinInfo for the incoming particle in "
	  << "VectorWaveFunction::constructSpinInfo() "
	  << Exception::warning;
      if(vertex) {
	SpinPtr newspin=new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tVectorSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<LorentzPolarizationVector>& wave,
					   RhoDMatrix& rho,tPPtr part,bool time,
					   bool massless,VectorPhase phase,
					   bool vertex) {
  tVectorSpinPtr inspin;
  if(part->spinInfo()) inspin=dynamic_ptr_cast<tVectorSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix)
	wave[ix]=inspin->getProductionBasisState(ix);
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tVectorSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
    rho = RhoDMatrix(PDT::Spin1);
  }
  else {
    if(inspin) {
      inspin->decay();
      rho = inspin->rhoMatrix();
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix) 
	wave[ix]=inspin->getDecayBasisState(ix);
    }
    else {
      if(part->spinInfo())
	throw ThePEG::Helicity::HelicityConsistencyError() 
	  << "Wrong type of SpinInfo for the incoming particle in "
	  << "VectorWaveFunction::constructSpinInfo() "
	  << Exception::warning;
      if(vertex) {
	SpinPtr newspin=new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tVectorSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      rho = RhoDMatrix(PDT::Spin1);
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<VectorWaveFunction>& wave,
						  tVectorSpinPtr spin,bool massless,
						  VectorPhase phase,bool vertex) {
  wave.resize(3);
  for(unsigned int ix=0;ix<3;++ix) {
    // calculate the wavefunction for the first helicity
    if(massless&&ix==1) _wf=LorentzPolarizationVector();
    else                reset(ix,phase);
    // add to output array
    wave[ix] = VectorWaveFunction(*this);
    // setup the spininfo object
    if(vertex) {
      if(direction()==outgoing) spin->setBasisState(ix,_wf);
      else                      spin->setDecayState(ix,_wf.conjugate());
    }
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<VectorWaveFunction>& wave,
					   tPPtr part,bool time,
					   bool massless,VectorPhase phase,
					   bool vertex) {
  tVectorSpinPtr inspin;
  if(part->spinInfo()) inspin=dynamic_ptr_cast<tVectorSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
    if(inspin) {
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix)
	wave[ix]=VectorWaveFunction(getMomentum(),getParticle(),
				    inspin->getProductionBasisState(ix),direction());
    }
    else {
      if(vertex) {
	SpinPtr temp = new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin=dynamic_ptr_cast<tVectorSpinPtr>(temp);
	part->spinInfo(temp);
      }
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
  else {
    if(inspin) {
      inspin->decay();
      wave.resize(3);
      for(unsigned int ix=0;ix<3;++ix)
	wave[ix]=VectorWaveFunction(getMomentum(),getParticle(),
				     inspin->getDecayBasisState(ix),direction());
    }
    else {
      if(part->spinInfo())
	throw ThePEG::Helicity::HelicityConsistencyError() 
	  << "Wrong type of SpinInfo for the incoming particle in "
	  << "VectorWaveFunction::constructSpinInfo() "
	  << Exception::warning;
      if(vertex) {
	SpinPtr newspin=new_ptr(VectorSpinInfo(part->momentum(),time));
	inspin= dynamic_ptr_cast<tVectorSpinPtr>(newspin);
	if(time) inspin->decayed(true);
	part->spinInfo(newspin);
      }
      constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
}

// construct the spininfo object
void VectorWaveFunction::constructSpinInfo(vector<VectorWaveFunction>& wave,
						  RhoDMatrix& rho,tPPtr part,bool time,
						  bool massless,VectorPhase phase,
						  bool vertex) {
  tVectorSpinPtr inspin;
  if(part->spinInfo()) inspin=dynamic_ptr_cast<tVectorSpinPtr>(part->spinInfo());
  if(direction()==outgoing) {
      if(inspin) {
	wave.resize(3);
	for(unsigned int ix=0;ix<3;++ix)
	  wave[ix]=VectorWaveFunction(getMomentum(),getParticle(),
				      inspin->getProductionBasisState(ix),direction());
      }
      else {
	if(vertex) {
	  SpinPtr temp = new_ptr(VectorSpinInfo(part->momentum(),time));
	  inspin=dynamic_ptr_cast<tVectorSpinPtr>(temp);
	  part->spinInfo(temp);
	}
	constructSpinInfo(wave,inspin,massless,phase,vertex);
      }
      rho = RhoDMatrix(PDT::Spin1);
  }
  else {
    if(inspin)
      {
	inspin->decay();
	rho = inspin->rhoMatrix();
	wave.resize(3);
	for(unsigned int ix=0;ix<3;++ix)
	  wave[ix]=VectorWaveFunction(getMomentum(),getParticle(),
				      inspin->getDecayBasisState(ix),direction());
      }
    else {
      if(part->spinInfo())
	throw ThePEG::Helicity::HelicityConsistencyError() 
	  << "Wrong type of SpinInfo for the incoming particle in "
	  << "VectorWaveFunction::constructSpinInfo() "
	  << Exception::warning;
    if(vertex) {
      SpinPtr newspin=new_ptr(VectorSpinInfo(part->momentum(),time));
      inspin= dynamic_ptr_cast<tVectorSpinPtr>(newspin);
      if(time) inspin->decayed(true);
      part->spinInfo(newspin);
    }
    rho = RhoDMatrix(PDT::Spin1);
    constructSpinInfo(wave,inspin,massless,phase,vertex);
    }
  }
}
