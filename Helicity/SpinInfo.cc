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

const double SpinInfo::_eps=1e-6;

SpinInfo::SpinInfo(const SpinInfo & x)
  : SpinBase(x), _production(x._production), _decay(x._decay),
    _timelike(x._timelike),
    _prodloc(x._prodloc), _decayloc(x._decayloc),
    _decayed(x._decayed), _developed(x._developed),_rhomatrix(x._rhomatrix),
    _Dmatrix(x._Dmatrix),_spin(x._spin),
    _productionmomentum(x._productionmomentum),
    _decaymomentum(x._decaymomentum),
    _currentmomentum(x._currentmomentum) 
{
  x._production=VertexPtr();
  x._decay=VertexPtr();
  // set the vertex so it now points to the copy
  if(_production) {
    // for timelike
    if(_timelike) _production->resetOutgoing(this,_prodloc); 
    // for spacelike
    else          _production->resetIncoming(this,_prodloc);
  }
}

EIPtr SpinInfo::clone() const {
  tcSpinPtr temp=this;
  return const_ptr_cast<SpinPtr>(temp);
}

void SpinInfo::rebind(const EventTranslationMap & trans) {
  if(_production) _production = trans.translate(_production);
  if(_decay)      _decay      = trans.translate(_decay);
  SpinBase::rebind(trans);
}


NoPIOClassDescription<SpinInfo> SpinInfo::initSpinInfo;
// Definition of the static class description member.

void SpinInfo::Init() {}

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
