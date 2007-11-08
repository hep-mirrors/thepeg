// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinInfo class.
//
// Author: Peter Richardson
//
#include "SpinInfo.h"


using namespace ThePEG;
using namespace ThePEG::Helicity;

SpinInfo::~SpinInfo() {}

NoPIOClassDescription<SpinInfo> SpinInfo::initSpinInfo;
// Definition of the static class description member.

void SpinInfo::Init() {}

void SpinInfo::transform(const LorentzMomentum &, LorentzRotation r)
{_currentmomentum.transform(r);}

const double SpinInfo::_eps=1e-6;
