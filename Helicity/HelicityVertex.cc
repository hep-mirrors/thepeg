// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HelicityVertex class.
//

#include "HelicityVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Helicity/SpinInfo.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HelicityVertex.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;
    
HelicityVertex::~HelicityVertex() {}
    
AbstractNoPIOClassDescription<HelicityVertex>
HelicityVertex::initHelicityVertex;
// Definition of the static class description member.
    
void HelicityVertex::Init() {
      
  static ClassDocumentation<HelicityVertex> documentation
    ("There is no documentation for the \\classname{HelicityVertex} class");
}

// methods to calculate the rho and D matrices
// method to get the rho matrix for a given outgoing particle
RhoDMatrix HelicityVertex::getRhoMatrix(int i)
{
  RhoDMatrix temp;
  return temp;
}

// method to get the D matrix for an incoming particle
RhoDMatrix HelicityVertex::getDMatrix(int i)
{
  RhoDMatrix temp;
  return temp;
}



