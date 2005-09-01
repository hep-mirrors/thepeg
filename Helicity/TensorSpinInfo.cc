// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the TensorSpinInfo class.
//
// Author: Peter Richardson
//

#include "TensorSpinInfo.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "TensorSpinInfo.tcc"
#endif

using namespace ThePEG;
using namespace Helicity;

TensorSpinInfo::~TensorSpinInfo() {}

NoPIOClassDescription<TensorSpinInfo> TensorSpinInfo::initTensorSpinInfo;
// Definition of the static class description member.

void TensorSpinInfo::Init() {}

void TensorSpinInfo::transform(const LorentzMomentum & m, LorentzRotation r)
{
  if(currentMomentum()==m)
    {
      for(unsigned int ix=0;ix<5;++ix){_currentstates[ix].transform(r.one());}
      SpinInfo::transform(m,r);
    }
}
