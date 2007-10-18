// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FFVTVertex class.
//

#include "FFVTVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

namespace ThePEG {
namespace Helicity {

AbstractNoPIOClassDescription<FFVTVertex> FFVTVertex::initFFVTVertex;
// Definition of the static class description member.

void FFVTVertex::Init() {
  
  static ClassDocumentation<FFVTVertex> documentation
    ("The FFVTVertex class is the implementation of the"
     "helicity amplitude calculation of the fermion-antifermion-vector-tensor"
     "vertex. All such vertices should inherit from it.");

}

// function to evaluate the vertex
Complex FFVTVertex::evaluate(Energy2 q2, const SpinorWaveFunction & sp,
    				 const SpinorBarWaveFunction & sbar,
    				 const VectorWaveFunction & vec,
    				 const TensorWaveFunction & ten)
{
  // pointers to the particles
  tcPDPtr Psp   = sp.getParticle();
  tcPDPtr Psbar = sbar.getParticle();
  tcPDPtr Pvec  = vec.getParticle();
  tcPDPtr Pten  =  ten.getParticle();
  // set the couplings
  setCoupling(q2,Psp,Psbar,Pvec,Pten);
  Complex norm=getNorm();
  Complex ii(0.,1.);
  // spinor vector
  // low energy convention
  Complex aspin[4];
  LorentzSpinorBar<double> sbart=sbar.wave();
  LorentzSpinor<double>    spt  =sp.wave();
  if(sp.wave().Rep()==HaberDRep&&sbar.wave().Rep()==HaberDRep) {
    aspin[3] = sbart.s1()*spt.s1()+sbart.s2()*spt.s2()
      -sbart.s3()*spt.s3()-sbart.s4()*spt.s4();
  }
  // high energy convention
  else if(sp.wave().Rep()==HELASDRep&&sbar.wave().Rep()==HELASDRep) {
    aspin[3] = sbart.s1()*spt.s3()+sbart.s2()*spt.s4()
      +sbart.s3()*spt.s1()+sbart.s4()*spt.s2();
  }
  else {
    spt.changeRep(HELASDRep);
    sbart.changeRep(HELASDRep);
    aspin[3] = sbart.s1()*spt.s3()+sbart.s2()*spt.s4()
      +sbart.s3()*spt.s1()+sbart.s4()*spt.s2();
  }
  // spatial components are the same in both conventions
  aspin[0] =     +sbart.s1()*spt.s4()+sbart.s2()*spt.s3()
                 -sbart.s3()*spt.s2()-sbart.s4()*spt.s1();
  aspin[1] = ii*(-sbart.s1()*spt.s4()+sbart.s2()*spt.s3()
		 +sbart.s3()*spt.s2()-sbart.s4()*spt.s1());
  aspin[2] =     +sbart.s1()*spt.s3()-sbart.s2()*spt.s4()
                 -sbart.s3()*spt.s1()+sbart.s4()*spt.s2();
  // trace of the tensor
  Complex trace=ten.tt()-ten.xx()-ten.yy()-ten.zz();
  // dot product
  Complex dotav = 
    aspin[3]*vec.t()-aspin[0]*vec.x()-aspin[1]*vec.y()-aspin[2]*vec.z();
  // components of the tensor
  Complex tentx = ten.tx()+ten.xt();
  Complex tenty = ten.ty()+ten.yt();
  Complex tentz = ten.tz()+ten.zt();
  Complex tenxy = ten.xy()+ten.yx();
  Complex tenxz = ten.xz()+ten.zx();
  Complex tenyz = ten.yz()+ten.zy();
  // dot product of wavefunctions and momenta with the tensor
  Complex tenav =
    2.*(+ten.tt()*vec.t()*aspin[3]+ten.xx()*vec.x()*aspin[0]
	+ten.yy()*vec.y()*aspin[1]+ten.zz()*vec.z()*aspin[2])
    -tentx*(vec.t()*aspin[0]+vec.x()*aspin[3])
    -tenty*(vec.t()*aspin[1]+vec.y()*aspin[3])
    -tentz*(vec.t()*aspin[2]+vec.z()*aspin[3])
    +tenxy*(vec.x()*aspin[1]+vec.y()*aspin[0])
    +tenxz*(vec.x()*aspin[2]+vec.z()*aspin[0])
    +tenyz*(vec.y()*aspin[2]+vec.z()*aspin[1]);
  // return the vertex
  return ii*0.25*norm*(tenav-2.*trace*dotav);
}

}
}
