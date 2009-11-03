// -*- C++ -*-
//
// FFVVertex.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FFVVertex class.
//

#include "FFVVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;
using namespace Helicity;

// Definition of the static class description member
AbstractNoPIOClassDescription<FFVVertex> FFVVertex::initFFVVertex;
    
void FFVVertex::Init() {
      
  static ClassDocumentation<FFVVertex> documentation
    ("The FFVVertex class implements the helicity amplitude"
     "calculations for a fermion-fantifermion gauge boson vertex. Any   "
     "implementation of such a vertex should inherit from in and implement"
     " the virtual setCoupling member to calculate the coupling");
}

// evalulate the full vertex
Complex FFVVertex::evaluate(Energy2 q2,
			    const SpinorWaveFunction & sp, 
			    const SpinorBarWaveFunction & sbar,
			    const VectorWaveFunction & vec) {
  // first calculate the couplings
  setCoupling(q2,sp.particle(),sbar.particle(),vec.particle());
  Complex ii(0.,1.);
  // useful combinations of the polarization vector components
  Complex e0p3=vec.t()+vec.z();
  Complex e0m3=vec.t()-vec.z();
  Complex e1p2=vec.x()+ii*vec.y();
  Complex e1m2=vec.x()-ii*vec.y();
  Complex vertex(0.);
  if(_left!=0.) {
    vertex += _left*(+sbar.s3()*(sp.s1()*e0p3+sp.s2()*e1m2)
		     +sbar.s4()*(sp.s1()*e1p2+sp.s2()*e0m3)); 
  }
  // then the right piece (often not needed eg W vertex)
  if(_right!=0.) {
    vertex += _right*(+sbar.s1()*(sp.s3()*e0m3-sp.s4()*e1m2)
		      -sbar.s2()*(sp.s3()*e1p2-sp.s4()*e0p3));
  }
  vertex*=ii;
  return vertex*norm();
}

// evaluate an off-shell spinor
SpinorWaveFunction FFVVertex::evaluate(Energy2 q2, int iopt,tcPDPtr  out,
				       const SpinorWaveFunction & sp,
				       const VectorWaveFunction &vec,
				       Energy mass, Energy width) {
  // extract the pointers to the particle data objects
  tcPDPtr  Psp=sp.particle();
  tcPDPtr  Pvec=vec.particle();
  // first calculate the couplings
  setCoupling(q2,Psp,out,Pvec);
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = sp.momentum()+vec.momentum(); 
  // now evaluate the contribution
  // polarization components
  Complex e0p3 = vec.t() +  vec.z();
  Complex e0m3 = vec.t() -  vec.z();
  Complex e1p2 = vec.x()+ii*vec.y();
  Complex e1m2 = vec.x()-ii*vec.y();
  // overall factor
  Energy2 p2 = pout.m2();
  Complex fact=-normPropagator(iopt,p2,out,mass,width);
  // momentum components
  if(mass < ZERO) mass  = iopt==5 ? ZERO : out->mass();
  complex<Energy> p1p2 = pout.x()+ii*pout.y();
  complex<Energy> p1m2 = pout.x()-ii*pout.y();
  // complex nos for for the spinor
  Complex s1(0.),s2(0.),s3(0.),s4(0.);
  LorentzSpinor<double>    spt  =sp  .wave();
  complex<Energy> p0p3=pout.e() +   pout.z();
  complex<Energy> p0m3=pout.e() -   pout.z();
  // left piece
  if(_left!=0.) {
    Complex a3=_left*fact*( spt.s1()*e0p3+spt.s2()*e1m2);
    Complex a4=_left*fact*( spt.s1()*e1p2+spt.s2()*e0m3);
    s1 +=UnitRemoval::InvE * (p0m3*a3-p1m2*a4);
    s2 +=UnitRemoval::InvE * (-p1p2*a3+p0p3*a4);
    s3 +=UnitRemoval::InvE * a3*mass;
    s4 +=UnitRemoval::InvE * a4*mass;
  }
  // right piece
  if(_right!=0.) {
    Complex a1=_right*fact*( spt.s3()*e0m3-spt.s4()*e1m2);
    Complex a2=_right*fact*(-spt.s3()*e1p2+spt.s4()*e0p3);
    s1 +=UnitRemoval::InvE * a1*mass;
    s2 +=UnitRemoval::InvE * a2*mass;
    s3 +=UnitRemoval::InvE * (p0p3*a1+p1m2*a2);
    s4 +=UnitRemoval::InvE * (p1p2*a1+p0m3*a2);
  }
  // return the wavefunction
  return SpinorWaveFunction(pout,out,s1,s2,s3,s4);
}
  
// evaluate an off-shell SpinorBar
SpinorBarWaveFunction FFVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr  out,
					  const SpinorBarWaveFunction & sbar,
					  const VectorWaveFunction & vec,
					  Energy mass, Energy width) {
  // first calculate the couplings
  setCoupling(q2,out,sbar.particle(),vec.particle());
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = sbar.momentum()+vec.momentum();
  // now evaluate the contribution
  // polarization components
  Complex e0p3=vec.t() +  vec.z();
  Complex e0m3=vec.t() -  vec.z();
  Complex e1p2=vec.x()+ii*vec.y();
  Complex e1m2=vec.x()-ii*vec.y();
  // overall factor
  Energy2 p2 = pout.m2();
  Complex fact=-normPropagator(iopt,p2,out,mass,width);
  // momentum components
  if(mass < ZERO) mass  = (iopt==5) ? ZERO : out->mass();
  complex<Energy> p1p2=pout.x()+ii*pout.y();
  complex<Energy> p1m2=pout.x()-ii*pout.y();
  // complex numbers for the spinor
  Complex s1(0.),s2(0.),s3(0.),s4(0.);
  LorentzSpinorBar<double> sbart=sbar.wave();
  Energy p0p3=pout.e() +   pout.z();
  Energy p0m3=pout.e() -   pout.z();
  // left piece
  if(_left!=0.) {
    Complex a1 =  _left*fact*( sbart.s3()*e0p3+sbart.s4()*e1p2);
    Complex a2 =  _left*fact*( sbart.s3()*e1m2+sbart.s4()*e0m3);
    s1 += UnitRemoval::InvE*a1*mass;
    s2 += UnitRemoval::InvE*a2*mass;
    s3 += UnitRemoval::InvE*(-p0m3*a1+p1p2*a2);
    s4 += UnitRemoval::InvE*(+p1m2*a1-p0p3*a2);
  }
  // right piece
  if(_right!=0.) {
    Complex a3 = _right*fact*( sbart.s1()*e0m3-sbart.s2()*e1p2);
    Complex a4 = _right*fact*(-sbart.s1()*e1m2+sbart.s2()*e0p3);
    s1 += UnitRemoval::InvE*(-p0p3*a3-p1p2*a4);
    s2 += UnitRemoval::InvE*(-p1m2*a3-p0m3*a4);
    s3 += UnitRemoval::InvE*a3*mass;
    s4 += UnitRemoval::InvE*a4*mass;
  }
  return SpinorBarWaveFunction(pout,out,s1,s2,s3,s4);
}

// off-shell vector
VectorWaveFunction FFVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr  out,
				       const SpinorWaveFunction & sp,
				       const SpinorBarWaveFunction & sbar,
				       Energy mass, Energy width) {
  // first calculate the couplings
  setCoupling(q2,sp.particle(),sbar.particle(),out);
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = sbar.momentum()+sp.momentum();
  // overall factor
  Energy2 p2 = pout.m2();
  Complex fact = normPropagator(iopt,p2,out,mass,width);
  // momentum components
  if(mass < ZERO) mass  = (iopt==5) ? ZERO : out->mass();
  Energy2 mass2 = sqr(mass);
  // the vector for the fermion-antifermion
  Complex vec[4];
  // left coupling
  if(_left!=0.) {
    vec[0] =   -_left*(sbar.s3()*sp.s2()+sbar.s4()*sp.s1());
    vec[1] = ii*_left*(sbar.s3()*sp.s2()-sbar.s4()*sp.s1());
    vec[2] =   -_left*(sbar.s3()*sp.s1()-sbar.s4()*sp.s2());
    vec[3] =    _left*(sbar.s3()*sp.s1()+sbar.s4()*sp.s2());
  }
  // right coupling
  if(_right!=0.) {
    vec[0] +=    +_right*(sbar.s1()*sp.s4()+sbar.s2()*sp.s3());
    vec[1] += -ii*_right*(sbar.s1()*sp.s4()-sbar.s2()*sp.s3());
    vec[2] +=    +_right*(sbar.s1()*sp.s3()-sbar.s2()*sp.s4());
    vec[3] +=    +_right*(sbar.s1()*sp.s3()+sbar.s2()*sp.s4());
  }
  // massless boson
  if(mass==ZERO) {
    for(int ix=0;ix<4;++ix){vec[ix]*=fact;}
  }
  // massive boson
  else {
    complex<InvEnergy> dot = ( pout.e() *vec[3]
			       -pout.x()*vec[0]
			       -pout.y()*vec[1]
			       -pout.z()*vec[2])/mass2;
    vec[0]=fact*(vec[0]-dot*pout.x());
    vec[1]=fact*(vec[1]-dot*pout.y());
    vec[2]=fact*(vec[2]-dot*pout.z());
    vec[3]=fact*(vec[3]-dot*pout.e());
  }
  return VectorWaveFunction(pout,out,vec[0],vec[1],vec[2],vec[3]);
}
