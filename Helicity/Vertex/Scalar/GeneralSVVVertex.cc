// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the GeneralSVVVertex class.
//

#include "GeneralSVVVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Switch.h"
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
  Lorentz5Momentum pvec1 = vec1.getMomentum();
  Lorentz5Momentum pvec2 = vec2.getMomentum();

  // calculate kinematics
  if(kinematics()) {
    calculateKinematics(pSca,pvec1,pvec2);
  }

  // calculate coupling
  setCoupling(q2, sca.getParticle(), vec1.getParticle(), vec2.getParticle());

  // norm factor
  Complex norm = -getNorm();

  Complex e1e2(vec1.wave().dot(vec2.wave()));
  complex<Energy> e1p1(vec1.wave().dot(pvec1));
  complex<Energy> e1p2(vec1.wave().dot(pvec2));
  complex<Energy> e2p1(vec2.wave().dot(pvec1));
  complex<Energy> e2p2(vec2.wave().dot(pvec2));
  complex<Energy2> p1p2(invariant(1,2));
  LorentzPolarizationVectorE eps = epsilon(vec1.wave(),vec2.wave(),pvec2);
  complex<Energy2> p1Ep2 = eps.dot(pvec1);

  Complex output = UnitRemoval::InvE2 * (_a00*e1e2*p1p2 + _aEp*p1Ep2 + 
  _a11*e1p1*e2p1 + _a12*e1p1*e2p2 + _a21*e1p2*e2p1+ _a22*e1p2*e2p2);
  if (2 == _representation) {
  // the standard, but inefficient(!), Passarino-Veltman tensor reduction scheme
    output = _a00*e1e2;
    output += UnitRemoval::InvE2 * (_a11*e1p1*e2p1
                                  +_a12*e1p1*e2p2
                                  +_a21*e1p2*e2p1
                                  +_a22*e1p2*e2p2);
    output += UnitRemoval::InvE2 *_aEp*p1Ep2;
  }

  output *= norm;
  return Complex(0.,1.) * sca.wave() * output;
}

ScalarWaveFunction GeneralSVVVertex::evaluate(Energy2 q2,int iopt,tcPDPtr out, 
                                              const VectorWaveFunction & vec1,
                                              const VectorWaveFunction & vec2) {
  // pointers to the particle data objects
  tcPDPtr Pvec1(vec1.getParticle());
  tcPDPtr Pvec2(vec2.getParticle());
  Lorentz5Momentum pvec1 = vec1.getMomentum();
  Lorentz5Momentum pvec2 = vec2.getMomentum();

  Lorentz5Momentum pout = pvec1 + pvec2;
  pout.rescaleMass();

  // calculate kinematics if needed
  if(kinematics()) {
    calculateKinematics(pout,pvec1,pvec2);
  }

  // calculate coupling
  setCoupling(q2,Pvec1,Pvec2,out);

  // norm factor
  Complex norm = -getNorm();

  // propagator
  Complex prop = propagator(iopt,q2,out);

  // lorentz part
  Complex e1e2(vec1.wave().dot(vec2.wave()));
  complex<Energy> e1p1(vec1.wave().dot(pvec1));
  complex<Energy> e1p2(vec1.wave().dot(pvec2));
  complex<Energy> e2p1(vec2.wave().dot(pvec1));
  complex<Energy> e2p2(vec2.wave().dot(pvec2));
  complex<Energy2> p1p2(invariant(1,2));
  LorentzPolarizationVectorE eps = epsilon(vec1.wave(),vec2.wave(),pvec2);
  complex<Energy2> p1Ep2 = eps.dot(pvec1);

  Complex output = UnitRemoval::InvE2 * (_a00*e1e2*p1p2 + _aEp*p1Ep2 + 
  _a11*e1p1*e2p1 + _a12*e1p1*e2p2 + _a21*e1p2*e2p1+ _a22*e1p2*e2p2);
  if (2 == _representation) {
  // the standard, but inefficient(!), Passarino-Veltman tensor reduction scheme
    output = _a00*e1e2;
    output += UnitRemoval::InvE2 * (_a11*e1p1*e2p1
                                  +_a12*e1p1*e2p2
                                  +_a21*e1p2*e2p1
                                  +_a22*e1p2*e2p2);
    output += UnitRemoval::InvE2 *_aEp*p1Ep2;
  }

  output *= norm*prop;
  return ScalarWaveFunction(pout,out,output);
}

}
}
