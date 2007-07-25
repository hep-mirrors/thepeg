// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the GeneralSVVVertex class.
//

#include "GeneralSVVVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Helicity/epsilon.h"

namespace ThePEG {
namespace Helicity {
    
AbstractNoPIOClassDescription<GeneralSVVVertex> GeneralSVVVertex::initGeneralSVVVertex;
// Definition of the static class description member.
    
void GeneralSVVVertex::Init() {
  static ClassDocumentation<GeneralSVVVertex> documentation
    ("Implementation of the SVV vertex. ");
}
    
Complex GeneralSVVVertex::evaluate(Energy2 q2, 
				   const ScalarWaveFunction & sca,
				   const VectorWaveFunction & vec1,
				   const VectorWaveFunction & vec2) {
  Lorentz5Momentum pSca = sca.getMomentum();
  Lorentz5Momentum pVec1 = vec1.getMomentum();
  Lorentz5Momentum pVec2 = vec2.getMomentum();
  if(kinematics()) {
    calculateKinematics(pSca,pVec1,pVec2);
  }
  setCoupling(q2,
	      sca.getParticle(),
	      vec1.getParticle(),
	      vec2.getParticle());

  complex<Energy> e1p1(vec1.wave().dot(pVec1)),e1p2(vec1.wave().dot(pVec2));
  complex<Energy> e2p1(vec2.wave().dot(pVec1)),e2p2(vec2.wave().dot(pVec2));
  LorentzPolarizationVectorE eps;
  eps = epsilon(vec1.wave(),vec2.wave(),pVec2);
  complex<Energy2> p1Ep2 = eps.dot(pVec1);
  Complex output=_a00*(vec1.wave().dot(vec2.wave()));
  output += UnitRemoval::InvE2 * (_a11*e1p1*e2p1
				  +_a12*e1p1*e2p2
				  +_a21*e1p2*e2p1
				  +_a22*e1p2*e2p2);
  output += UnitRemoval::InvE2 *_aEp*p1Ep2;
  return Complex(0.,1.)*getNorm()*sca.wave()*output;
}

ScalarWaveFunction GeneralSVVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr out, 
                                              const VectorWaveFunction & vec1,
                                              const VectorWaveFunction & vec2)
{
  // pointers to the particle data objects
  tcPDPtr Pvec1(vec1.getParticle());
  tcPDPtr Pvec2(vec2.getParticle());
  Lorentz5Momentum pvec1 = vec1.getMomentum();
  Lorentz5Momentum pvec2 = vec2.getMomentum();
  LorentzPolarizationVector wvec1 = vec1.wave();
  LorentzPolarizationVector wvec2 = vec2.wave();

  Energy Px=vec1.px()+vec1.px();
  Energy Py=vec1.py()+vec1.py();
  Energy Pz=vec1.pz()+vec1.pz();
  Energy E=vec1.e()+vec1.e();
  Lorentz5Momentum pout = Lorentz5Momentum(Px,Py,Pz,E);
  pout.setMass(sqrt(q2));

  // calculate kinematics
  if(kinematics()) {
    calculateKinematics(pout,pvec1,pvec2);
  }

  // calculate coupling
  setCoupling(q2,Pvec1,Pvec2,out);

  // prefactor
  Complex norm = -getNorm();

  // propagator
  Complex prop = propagator(iopt,q2,out);

  // loop factor
  Complex loop = b();

  // lorentz part
  Complex w1w2 = Complex(wvec1.t()*wvec2.t()-wvec1.x()*wvec2.x()-wvec1.y()*wvec2.y()-wvec1.z()*wvec2.z());
  Complex w1p2 = Complex(UnitRemoval::InvE*(wvec1.t()*vec2.e()-wvec1.x()*vec2.px()-wvec1.y()*vec2.py()-wvec1.z()*vec2.pz()));
  Complex w2p1 = Complex(UnitRemoval::InvE*(wvec2.t()*vec1.e()-wvec2.x()*vec1.px()-wvec2.y()*vec1.py()-wvec2.z()*vec1.pz()));
  Complex p1p2 = Complex(UnitRemoval::InvE2*pvec1*pvec2);
  Complex lorentz = p1p2*w1w2 - w1p2*w2p1;

  Complex output = norm*prop*loop*lorentz;
  return ScalarWaveFunction(pout,out,output);
}

}
}
