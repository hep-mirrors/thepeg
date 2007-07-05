// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FFVVertex class.
//

#include "FFVVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

namespace ThePEG {
namespace Helicity{
   
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
			    const VectorWaveFunction & vec)
{
  // extract the pointers to the particle data objects
  tcPDPtr  Psp=sp.getParticle();
  tcPDPtr  Pvec=vec.getParticle();
  tcPDPtr  Psbar=sbar.getParticle();
  // first calculate the couplings
  setCoupling(q2,Psp,Psbar,Pvec);
  Complex ii(0.,1.);
  Complex vertex(0.);
  // useful combinations of the polarization vector components
  Complex e0p3=vec.t()+vec.z();
  Complex e0m3=vec.t()-vec.z();
  Complex e1p2=vec.x()+ii*vec.y();
  Complex e1m2=vec.x()-ii*vec.y();
  // work out which convention to use 
  // low energy convention
  if(sp.wave().Rep()==HaberDRep&&sbar.wave().Rep()==HaberDRep) {      
    Complex st[4]={0.,0.,0.,0.};
    // first the left piece as this is virtually always needed
    if(_left!=0.) {
      Complex s1m3=sp.s1()-sp.s3();
      Complex s2m4=sp.s2()-sp.s4();
      st[0] = _left*(e0p3*s1m3+e1m2*s2m4);
      st[1] = _left*(e1p2*s1m3+e0m3*s2m4);
    }
    // then the right piece (often not needed eg W vertex)
    if(_right!=0.) {
      Complex s1p3=sp.s1()+sp.s3();
      Complex s2p4=sp.s2()+sp.s4();
      st[2] = _right*( e0m3*s1p3-e1m2*s2p4);
      st[3] = _right*(-e1p2*s1p3+e0p3*s2p4);
    }
    vertex = ii*0.5*
      (  sbar.s1()*(st[0]+st[2])+sbar.s2()*(st[1]+st[3])
        +sbar.s3()*(st[0]-st[2])+sbar.s4()*(st[1]-st[3]));
  }
  // high energy convention
  else if(sp.wave().Rep()==HELASDRep&&sbar.wave().Rep()==HELASDRep) {
    // first the left piece as this is virtually always needed
    if(_left!=0.) {
      vertex = _left*(+sbar.s3()*(sp.s1()*e0p3+sp.s2()*e1m2)
		      +sbar.s4()*(sp.s1()*e1p2+sp.s2()*e0m3)); 
    }
    // then the right piece (often not needed eg W vertex)
    if(_right!=0.) {
      vertex += _right*(+sbar.s1()*(sp.s3()*e0m3-sp.s4()*e1m2)
			-sbar.s2()*(sp.s3()*e1p2-sp.s4()*e0p3));
    }
    vertex*=ii;
  }
  // mixed conventions
  else {
    // get both the spinors in the same representation (using the default choice)
    LorentzSpinorBar<double> sbart=sbar.wave().transformRep(HELASDRep);
    LorentzSpinor<double>    spt  =sp  .wave().transformRep(HELASDRep);
    // first the left piece as this is virtually always needed
    if(_left!=0.) {
      vertex = _left*(+sbart.s3()*(spt.s1()*e0p3+spt.s2()*e1m2)
		      +sbart.s4()*(spt.s1()*e1p2+spt.s2()*e0m3)); 
    }
    // then the right piece (often not needed eg W vertex)
    if(_right!=0.) {
      vertex += _right*(+sbart.s1()*(spt.s3()*e0m3-spt.s4()*e1m2)
			-sbart.s2()*(spt.s3()*e1p2-spt.s4()*e0p3));
    }
    vertex*=ii;
  }
  // final factors
  return vertex*getNorm();
}

// evaluate an off-shell spinor
SpinorWaveFunction FFVVertex::evaluate(Energy2 q2, int iopt,tcPDPtr  out,
				       const SpinorWaveFunction & sp,
				       const VectorWaveFunction &vec,
				       DiracRep dirac) {
  // extract the pointers to the particle data objects
  tcPDPtr  Psp=sp.getParticle();
  tcPDPtr  Pvec=vec.getParticle();
  // first calculate the couplings
  setCoupling(q2,Psp,out,Pvec);
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = Lorentz5Momentum(sp.px()+vec.px(),sp.py()+vec.py(),
					   sp.pz()+vec.pz(),sp.e() +vec.e() ); 
  // now evaluate the contribution
  // polarization components
  Complex e0p3=vec.t() +  vec.z();
  Complex e0m3=vec.t() -  vec.z();
  Complex e1p2=vec.x()+ii*vec.y();
  Complex e1m2=vec.x()-ii*vec.y();
  // momentum components
  Energy mass  = out->mass();
  if(iopt==5) mass=Energy();
  complex<Energy> p1p2=pout.x()+ii*pout.y();
  complex<Energy> p1m2=pout.x()-ii*pout.y();
  // complex nos for for the spinor
  Complex s1(0.),s2(0.),s3(0.),s4(0.);
  // overall factor
  Energy2 p2 = pout.m2();
  Complex fact=-normPropagator(iopt,p2,out);
  // ensure the spinor is in the correct dirac representation
  LorentzSpinor<double>    spt  =sp  .wave().transformRep(dirac);
  // low energy Dirac matrix defn
  if(dirac==HaberDRep)
    {   
      // first step compute the polarization vector combined with the spinor
      Complex st[4]={0.,0.,0.,0.};
      // first the left piece as this is virtually always needed
      if(_left!=0.)
	{
	  st[0] +=_left*( e0p3*(spt.s1()-spt.s3())+e1m2*(spt.s2()-spt.s4()));
	  st[1] +=_left*( e1p2*(spt.s1()-spt.s3())+e0m3*(spt.s2()-spt.s4()));
	  st[2] +=_left*( e0p3*(spt.s1()-spt.s3())+e1m2*(spt.s2()-spt.s4()));
	  st[3] +=_left*( e1p2*(spt.s1()-spt.s3())+e0m3*(spt.s2()-spt.s4()));
	}
      // then the right piece (often not needed eg W vertex)
      if(_right!=0.)
	{
	  st[0] +=_right*( e0m3*(spt.s1()+spt.s3())-e1m2*(spt.s2()+spt.s4()));
	      st[1] +=_right*(-e1p2*(spt.s1()+spt.s3())+e0p3*(spt.s2()+spt.s4()));
	      st[2] +=_right*(-e0m3*(spt.s1()+spt.s3())+e1m2*(spt.s2()+spt.s4()));
	      st[3] +=_right*( e1p2*(spt.s1()+spt.s3())-e0p3*(spt.s2()+spt.s4()));
	}
      // then combine this with pslash+m
      Energy p0pm=pout.e()+mass;
      Energy p0mm=pout.z()*(pout.z()/p0pm);
      fact *= 0.5;
      s1 =UnitRemoval::InvE * fact*( p0pm*st[0]-pout.z()*st[2]-    p1m2*st[3]);
      s2 =UnitRemoval::InvE * fact*( p0pm*st[1]-    p1p2*st[2]+pout.z()*st[3]);
      s3 =UnitRemoval::InvE * fact*(-p0mm*st[2]+pout.z()*st[0]+    p1m2*st[1]);
      s4 =UnitRemoval::InvE * fact*(-p0mm*st[3]+    p1p2*st[0]-pout.z()*st[1]);
  }
  // high energy Dirac matrix defn
  else if(dirac==HELASDRep)
    { 
      complex<Energy> p0p3=pout.e() +   pout.z();
      complex<Energy> p0m3=pout.e() -   pout.z();
      // left piece
      if(_left!=0.)
	{
	  Complex a3=_left*fact*( spt.s1()*e0p3+spt.s2()*e1m2);
	  Complex a4=_left*fact*( spt.s1()*e1p2+spt.s2()*e0m3);
	  s1 +=UnitRemoval::InvE * (p0m3*a3-p1m2*a4);
	  s2 +=UnitRemoval::InvE * (-p1p2*a3+p0p3*a4);
	  s3 +=UnitRemoval::InvE * a3*mass;
	  s4 +=UnitRemoval::InvE * a4*mass;
	}
      // right piece
      if(_right!=0.)
	{
	  Complex a1=_right*fact*( spt.s3()*e0m3-spt.s4()*e1m2);
	  Complex a2=_right*fact*(-spt.s3()*e1p2+spt.s4()*e0p3);
	  s1 +=UnitRemoval::InvE * a1*mass;
	  s2 +=UnitRemoval::InvE * a2*mass;
	  s3 +=UnitRemoval::InvE * (p0p3*a1+p1m2*a2);
	  s4 +=UnitRemoval::InvE * (p1p2*a1+p0m3*a2);
	}
  }
  // return the wavefunction
  return SpinorWaveFunction(pout,out,s1,s2,s3,s4,dirac);
}
  
// evaluate an off-shell SpinorBar
SpinorBarWaveFunction FFVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr  out,
					  const SpinorBarWaveFunction & sbar,
					  const VectorWaveFunction & vec,
					  DiracRep dirac) {
  // extract the pointers to the particle data objects
  tcPDPtr  Psbar=sbar.getParticle();
  tcPDPtr  Pvec=vec.getParticle();
  // first calculate the couplings
  setCoupling(q2,out,Psbar,Pvec);
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = Lorentz5Momentum(sbar.px()+vec.px(),sbar.py()+vec.py(),
					   sbar.pz()+vec.pz(),sbar.e() +vec.e()); 
  // now evaluate the contribution
  // polarization components
  Complex e0p3=vec.t() +  vec.z();
  Complex e0m3=vec.t() -  vec.z();
  Complex e1p2=vec.x()+ii*vec.y();
  Complex e1m2=vec.x()-ii*vec.y();
  // momentum components
  Energy mass  = out->mass();
  if(iopt==5) mass=Energy();
  complex<Energy> p1p2=pout.x()+ii*pout.y();
  complex<Energy> p1m2=pout.x()-ii*pout.y();
  // complex numbers for the spinor
  Complex s1(0.),s2(0.),s3(0.),s4(0.);
  // overall factor
  Energy2 p2 = pout.m2();
  Complex fact=-normPropagator(iopt,p2,out);
  // ensure the spinorbar is in the correct dirac representation
  LorentzSpinorBar<double> sbart=sbar.wave().transformRep(dirac);
  // low energy convention
  if(dirac==HaberDRep)
    {
      // first step compute the polarization vector combined with the spinorbar
      Complex st[4]={0.,0.,0.,0.};
      // first the left piece as this is virtually always needed
      if(_left!=0.)
	{
	  st[0] += _left*( e0p3*(sbart.s1()+sbart.s3())+e1p2*(sbart.s2()+sbart.s4()));
	  st[1] += _left*( e1m2*(sbart.s1()+sbart.s3())+e0m3*(sbart.s2()+sbart.s4()));
	  st[2] += _left*(-e0p3*(sbart.s1()+sbart.s3())-e1p2*(sbart.s2()+sbart.s4()));
	  st[3] += _left*(-e1m2*(sbart.s1()+sbart.s3())-e0m3*(sbart.s2()+sbart.s4()));
	}
      // then the right piece (often not needed eg W vertex)
      if(_right!=0.)
	{
	  st[0] +=_right*( e0m3*(sbart.s1()-sbart.s3())-e1p2*(sbart.s2()-sbart.s4()));
	  st[1] +=_right*(-e1m2*(sbart.s1()-sbart.s3())+e0p3*(sbart.s2()-sbart.s4()));
	  st[2] +=_right*(-e0m3*(sbart.s1()-sbart.s3())-e1p2*(sbart.s2()-sbart.s4()));
	  st[3] +=_right*( e1m2*(sbart.s1()-sbart.s3())+e0p3*(sbart.s2()-sbart.s4()));
	}
      // then combine this with -pslash+m 
      Energy p0pm=pout.e()+mass;
      Energy p0mm=pout.z()*(pout.z()/p0pm);
      fact *= 0.5;
      s1 =UnitRemoval::InvE*fact*(-p0mm*st[0]-pout.z()*st[2]-    p1p2*st[3]);
      s2 =UnitRemoval::InvE*fact*(-p0mm*st[1]-    p1m2*st[2]+pout.z()*st[3]);
      s3 =UnitRemoval::InvE*fact*( p0pm*st[2]+pout.z()*st[0]+    p1p2*st[1]);
      s4 =UnitRemoval::InvE*fact*( p0pm*st[3]+    p1m2*st[0]-pout.z()*st[1]);
  }
  // high energy convention
  else if(dirac==HELASDRep)
    {
      Energy p0p3=pout.e() +   pout.z();
      Energy p0m3=pout.e() -   pout.z();
      // left piece
      if(_left!=0.)
	{
	  Complex a1 =  _left*fact*( sbart.s3()*e0p3+sbart.s4()*e1p2);
	  Complex a2 =  _left*fact*( sbart.s3()*e1m2+sbart.s4()*e0m3);
	  s1 += UnitRemoval::InvE*a1*mass;
	  s2 += UnitRemoval::InvE*a2*mass;
	  s3 += UnitRemoval::InvE*(-p0m3*a1+p1p2*a2);
	  s4 += UnitRemoval::InvE*(+p1m2*a1-p0p3*a2);
	}
      // right piece
      if(_right!=0.)
	{
	  Complex a3 = _right*fact*( sbart.s1()*e0m3-sbart.s2()*e1p2);
	  Complex a4 = _right*fact*(-sbart.s1()*e1m2+sbart.s2()*e0p3);
	  s1 += UnitRemoval::InvE*(-p0p3*a3-p1p2*a4);
	  s2 += UnitRemoval::InvE*(-p1m2*a3-p0m3*a4);
	  s3 += UnitRemoval::InvE*a3*mass;
	  s4 += UnitRemoval::InvE*a4*mass;
	}
  }
  return SpinorBarWaveFunction(pout,out,s1,s2,s3,s4,dirac);
}

// off-shell vector
VectorWaveFunction FFVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr  out,
				       const SpinorWaveFunction & sp,
				       const SpinorBarWaveFunction & sbar) {
  // extract the pointers to the particle data objects
  tcPDPtr  Psbar=sbar.getParticle();
  tcPDPtr  Psp=sp.getParticle();
  // first calculate the couplings
  setCoupling(q2,Psp,Psbar,out);
  Complex ii(0.,1.);
  // work out the momentum of the off-shell particle
  Lorentz5Momentum pout = Lorentz5Momentum(sbar.px()+sp.px(),sbar.py()+sp.py(),
					   sbar.pz()+sp.pz(),sbar.e() +sp.e()); 
  // momentum components
  Energy mass  = out->mass();
  if(iopt==5) mass=Energy();
  Energy2 mass2=mass*mass;
  // overall factor
  Energy2 p2 = pout.m2();
  // the vector for the fermion-antifermion
  Complex vec[4];
  if(sp.wave().Rep()==HaberDRep&&sbar.wave().Rep()==HaberDRep) {
    // left coupling
    if(_left!=0.) {
      Complex s2m4=sp.s2()-sp.s4();
      Complex s1m3=sp.s1()-sp.s3();
      vec[0] =   0.5*_left*(-sbar.s1()*s2m4-sbar.s2()*s1m3
			    -sbar.s3()*s2m4-sbar.s4()*s1m3);
      vec[1] =ii*0.5*_left*(+sbar.s1()*s2m4-sbar.s2()*s1m3
			    +sbar.s3()*s2m4-sbar.s4()*s1m3);
      vec[2] =   0.5*_left*(-sbar.s1()*s1m3+sbar.s2()*s2m4
			    -sbar.s3()*s1m3+sbar.s4()*s2m4);
      vec[3] =   0.5*_left*(+sbar.s1()*s1m3+sbar.s2()*s2m4
			    +sbar.s3()*s1m3+sbar.s4()*s2m4);
    }
    // right coupling
    if(_right!=0.) {
      Complex s1p3=sp.s1()+sp.s3();
      Complex s2p4=sp.s2()+sp.s4();
      vec[0] +=    +0.5*_right*(+sbar.s1()*s2p4+sbar.s2()*s1p3
				-sbar.s3()*s2p4-sbar.s4()*s1p3);
      vec[1] += +ii*0.5*_right*(-sbar.s1()*s2p4+sbar.s2()*s1p3
				+sbar.s3()*s2p4-sbar.s4()*s1p3);
      vec[2] +=    +0.5*_right*(+sbar.s1()*s1p3-sbar.s2()*s2p4
				-sbar.s3()*s1p3+sbar.s4()*s2p4);
      vec[3] +=    +0.5*_right*(+sbar.s1()*s1p3+sbar.s2()*s2p4
				-sbar.s3()*s1p3-sbar.s4()*s2p4);
    }
  }
  else if(sp.wave().Rep()==HELASDRep&&sbar.wave().Rep()==HELASDRep) {
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
  }
  else {
    LorentzSpinorBar<double> sbart=sbar.wave().transformRep(HELASDRep);
    LorentzSpinor<double>    spt  =sp  .wave().transformRep(HELASDRep);
    // left coupling
    if(_left!=0.) {
      vec[0] =   -_left*(sbart.s3()*spt.s2()+sbart.s4()*spt.s1());
      vec[1] = ii*_left*(sbart.s3()*spt.s2()-sbart.s4()*spt.s1());
      vec[2] =   -_left*(sbart.s3()*spt.s1()-sbart.s4()*spt.s2());
      vec[3] =    _left*(sbart.s3()*spt.s1()+sbart.s4()*spt.s2());
    }
    // right coupling
    if(_right!=0.) {
      vec[0] +=    +_right*(sbart.s1()*spt.s4()+sbart.s2()*spt.s3());
      vec[1] += -ii*_right*(sbart.s1()*spt.s4()-sbart.s2()*spt.s3());
      vec[2] +=    +_right*(sbart.s1()*spt.s3()-sbart.s2()*spt.s4());
      vec[3] +=    +_right*(sbart.s1()*spt.s3()+sbart.s2()*spt.s4());
    }
  }
  // prefactor
  Complex fact = normPropagator(iopt,p2,out);
  // massless boson
  if(mass==Energy())
    {
      for(int ix=0;ix<4;++ix){vec[ix]*=fact;}
    }
  // massive boson
  else
    {
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

}
}
