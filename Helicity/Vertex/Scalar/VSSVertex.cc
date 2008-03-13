// -*- C++ -*-
//
// VSSVertex.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the VSSVertex class.
//

#include "VSSVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;
using namespace Helicity;
    
AbstractNoPIOClassDescription<VSSVertex> VSSVertex::initVSSVertex;
// Definition of the static class description member.
     
VSSVertex::VSSVertex() {
  setNpoint(3);
  setSpin(3,1,1);
  setName(VSS); 
}

void VSSVertex::Init() {
      
static ClassDocumentation<VSSVertex> documentation
  ("The VSSVertex class is hte implementation of the"
   "vector-scalar-scalar vertex for helicity amplitude calculations."
   " all such vertices should inherit from it");
 
}

// evaluate the vertex
Complex VSSVertex::evaluate(Energy2 q2, const VectorWaveFunction & vec,
			    const ScalarWaveFunction & sca1,
			    const ScalarWaveFunction & sca2) {
  // calculate the coupling
  setCoupling(q2,vec.getParticle(),sca1.getParticle(),sca2.getParticle());
  Complex norm=getNorm();
  // calculate the vertex
  Complex vertex(0.);
  vertex = UnitRemoval::InvE * -Complex(0.,1.) * norm * sca1.wave()*sca2.wave()*
    vec.wave().dot(sca1.getMomentum()-sca2.getMomentum());
  return vertex;
}

// off-shell vector
VectorWaveFunction VSSVertex::evaluate(Energy2 q2, int iopt, tcPDPtr out,
				       const ScalarWaveFunction & sca1,
				       const ScalarWaveFunction & sca2,
				       Energy mass, Energy width) {
  // outgoing momentum 
  Lorentz5Momentum pout(sca1.getMomentum()+sca2.getMomentum());
  // calculate the coupling
  setCoupling(q2,out,sca1.getParticle(),sca2.getParticle());
  // mass and width
  if(mass<0.*GeV) mass   = out->mass();
  Energy2 mass2 = sqr(mass);
  // calculate the prefactor
  Energy2 p2    = pout.m2();
  Complex fact = getNorm()*sca1.wave()*sca2.wave()*propagator(iopt,p2,out,mass,width);
  // compute the vector
  LorentzPolarizationVector vec;
  // massive outgoing vector
  if(mass!=Energy()) {
    vec = UnitRemoval::InvE * fact * (sca2.getMomentum()-sca1.getMomentum());
  }
  // massless outgoing vector
  else {
    // first the dot product for the second term
    double dot = (sca1.m2()-sca2.m2())/mass2;
    // compute the vector
    vec = UnitRemoval::InvE * fact * (sca2.getMomentum()-sca1.getMomentum()+dot*pout);
  }
  return VectorWaveFunction(pout,out,vec);
}

// return an off-shell scalar
ScalarWaveFunction VSSVertex::evaluate(Energy2 q2, int iopt, tcPDPtr out,
				       const VectorWaveFunction & vec,
				       const ScalarWaveFunction & sca,
				       Energy mass, Energy width ) {
  // momentum of the particle
  Lorentz5Momentum pout = sca.getMomentum()+vec.getMomentum(); 
  // calculate the coupling
  setCoupling(q2,vec.getParticle(),sca.getParticle(),out);
  // calculate the prefactor
  Energy2 p2   = pout.m2();
  Complex fact = getNorm()*sca.wave()*propagator(iopt,p2,out,mass,width);
  // compute the wavefunction
  fact = UnitRemoval::InvE * fact*vec.wave().dot(sca.getMomentum()+pout);
  return ScalarWaveFunction(pout,out,fact);
}
