// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SSSVertex class.
//

#include "SSSVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

namespace ThePEG {
namespace Helicity {
    
AbstractNoPIOClassDescription<SSSVertex> SSSVertex::initSSSVertex;
// Definition of the static class description member.

void SSSVertex::Init() {
  
  static ClassDocumentation<SSSVertex> documentation
    ("The SSSVertex class is the implementation of the SSS"
     "vertex. All such vertices shoud inherit from it");
}

// evaluate the vertex
Complex SSSVertex::evaluate(Energy2 q2,
			    const ScalarWaveFunction & sca1,
			    const ScalarWaveFunction & sca2, 
			    const ScalarWaveFunction & sca3)
{
  tcPDPtr Psca1 = sca1.getParticle();
  tcPDPtr Psca2 = sca2.getParticle();
  tcPDPtr Psca3 = sca3.getParticle();
  // calculate the coupling
  setCoupling(q2,Psca1,Psca2,Psca3);
  Complex norm=getNorm();
  Complex ii(0.,1.);
  // return the answer
  return ii*norm*sca1.wave()*sca2.wave()*sca3.wave();
}

// off-shell scalar
ScalarWaveFunction SSSVertex::evaluate(Energy2 q2,int iopt, tcPDPtr out, 
				       const ScalarWaveFunction & sca1,
				       const ScalarWaveFunction & sca2)
{
  tcPDPtr Psca1 = sca1.getParticle();
  tcPDPtr Psca2 = sca2.getParticle();
  // outgoing momentum 
  Lorentz5Momentum pout = Lorentz5Momentum(sca1.px()+sca2.px(),
					   sca1.py()+sca2.py(),
					   sca1.pz()+sca2.pz(),
					   sca1.e() +sca2.e() ); 
  // calculate the coupling
  setCoupling(q2,Psca1,Psca2,out);
  // wavefunction
  Energy2 p2=pout.m2();
  Complex fact=-getNorm()*sca1.wave()*sca2.wave()*propagator(iopt,p2,out);
  return ScalarWaveFunction(pout,out,fact);
}

}
}
