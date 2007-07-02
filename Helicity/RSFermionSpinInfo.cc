// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RSFermionSpinInfo class.
//
// Author: Peter Richardson
//

#include "RSFermionSpinInfo.h"
#include "ThePEG/Repository/CurrentGenerator.h"
#include "ThePEG/Interface/ClassDocumentation.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RSFermionSpinInfo.tcc"
#endif


using namespace ThePEG;
using namespace ThePEG::Helicity;

RSFermionSpinInfo::~RSFermionSpinInfo() {}

NoPIOClassDescription<RSFermionSpinInfo> RSFermionSpinInfo::initRSFermionSpinInfo;
// Definition of the static class description member.

void RSFermionSpinInfo::Init() {

  static ClassDocumentation<RSFermionSpinInfo> documentation
    ("There is no documentation for the \\classname{RSFermionSpinInfo} class");

}

void RSFermionSpinInfo::transform(const LorentzMomentum & m, LorentzRotation r)
{
  if(isNear(m))
    {
      for(unsigned int ix=0;ix<4;++ix){_currentstates[ix].transform(r);}
      SpinInfo::transform(m,r);
    }
}

