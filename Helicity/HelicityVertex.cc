// -*- C++ -*-
//
// HelicityVertex.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HelicityVertex class.
//
// Author: Peter Richardson
//

#include "HelicityVertex.h"
#include "ThePEG/Helicity/SpinInfo.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HelicityVertex.tcc"
#endif

using namespace ThePEG;
using namespace ThePEG::Helicity;

AbstractNoPIOClassDescription<HelicityVertex>
HelicityVertex::initHelicityVertex;
// Definition of the static class description member.

void HelicityVertex::Init() {}
