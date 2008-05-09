// -*- C++ -*-
//
// SpinInfo.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SpinInfo class.
//
// Author: Peter Richardson
//
#include "SpinInfo.h"

using namespace ThePEG;
using namespace ThePEG::Helicity;

NoPIOClassDescription<SpinInfo> SpinInfo::initSpinInfo;
// Definition of the static class description member.

void SpinInfo::Init() {}

void SpinInfo::transform(const LorentzMomentum &, LorentzRotation r) {
  _currentmomentum.transform(r);
}

const double SpinInfo::_eps=1e-6;

void SpinInfo::update() const {
  // number of instances fo this object
  int nref=referenceCount();
  if(nref<2||nref>3) return;
  // work out the number of references there should be
  int nmin=0;
  // check the production pointers
  if(_production) {
    if(_timelike) { if(_production->outgoing()[_prodloc]==this) ++nmin;}
    else          { if(_production->incoming()[_prodloc]==this) ++nmin;}
  }
  // check the decay pointers
  if(_decay) {
    if(_decay->incoming()[_decayloc]==this) ++nmin;
  }
  // delete the pointers
  SpinPtr temp;
  if(nmin+1==nref) {
    // delete the production pointers
    if(_production) {
      if(_timelike) {
	if(_production->outgoing()[_prodloc]==this)
	  _production->resetOutgoing(SpinPtr(),_prodloc);
      }
      else {
	if(_production->incoming()[_prodloc]==this)
	  _production->resetIncoming(SpinPtr(),_prodloc);
      }
    }
    // delete the decay pointers
    if(_decay) {
      if(_decay->incoming()[_decayloc]==this)
	_decay->resetIncoming(SpinPtr(),_decayloc);
    }
  }
}
