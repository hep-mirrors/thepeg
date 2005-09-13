// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the VectorSpinInfo class.
//
// Author: Peter Richardson
//

#include "VectorSpinInfo.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "VectorSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

VectorSpinInfo::~VectorSpinInfo() {}

NoPIOClassDescription<VectorSpinInfo> VectorSpinInfo::initVectorSpinInfo;
// Definition of the static class description member.

void VectorSpinInfo::Init() {}

void VectorSpinInfo::transform(const LorentzMomentum & m, LorentzRotation r)
{
  if(isNear(m))
    {
      for(unsigned int ix=0;ix<3;++ix){_currentstates[ix].transform(r.one());}
      SpinInfo::transform(m,r);
    }
}
