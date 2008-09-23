// -*- C++ -*-
//
// MEBase.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MEBase class.
//

#include "MEBase.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/MatrixElement/ReweightBase.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

MEBase::MEBase()
  : theLastSHat(-1.0*GeV2), lastPreweight(1.0), theLastJacobian(1.0),
    theMaxMultCKKW(0), theMinMultCKKW(0) {}

MEBase::~MEBase() {}

void MEBase::addReweighter(tReweightPtr rw) {
  if ( rw && find(reweights.begin(), reweights.end(), rw) == reweights.end() )
    reweights.push_back(rw);
}

void MEBase::addPreweighter(tReweightPtr rw) {
  if ( rw &&
       find(preweights.begin(), preweights.end(), rw) ==  preweights.end())
    preweights.push_back(rw);
}

void MEBase::setKinematics(tPPair in, const PVector & out) {
  theLastSHat = -1.0*GeV2;
  theLastXComb = tStdXCombPtr();
  for ( int i = 0, N = diagrams().size(); i < N; ++i ) {
    tPVector parts;
    const DiagramBase & diag = *(diagrams()[i]);
    if (diag.partons().size() != out.size() + 2 ) continue;
    if ( in.first->dataPtr() == diag.partons()[0] ) {
      parts.push_back(in.first);
      if ( in.second->dataPtr() != diag.partons()[1] ) continue;
      parts.push_back(in.second);
    }
    else if ( in.second->dataPtr() == diag.partons()[0] ) {
      parts.push_back(in.second);
      if ( in.first->dataPtr() != diag.partons()[1] ) continue;
      parts.push_back(in.first);
    }
    else
      continue;

    multimap<tcPDPtr,tPPtr> omap;
    for ( int j = 0, M = out.size(); j < M; ++j )
      omap.insert(make_pair(out[j]->dataPtr(), out[j]));

    for ( int j = 2, M = diag.partons().size(); j < M; ++j ) {
      multimap<tcPDPtr,tPPtr>::iterator it = omap.find(diag.partons()[j]);
      if ( it == omap.end() ) break;
      parts.push_back(it->second);
      omap.erase(it);
    }
    if ( !omap.empty() ) continue;
    theLastXComb = new_ptr(StandardXComb(this, parts, i));
    setKinematics();
    return;
  }
  throw Exception()
    << "In 'MEBase::setKinematics(...)' for the object '" << name()
    << "': Could not set the kinematics according to the specified partons "
    << "since no matching diagram was found." << Exception::abortnow;

}

void MEBase::constructVertex(tSubProPtr) {}

void MEBase::setKinematics() {
  theLastSHat = lastSHat();
}

void MEBase::clearKinematics() {
  theLastSHat = -1.0*GeV2;
  theLastXComb = tStdXCombPtr();
}

MEBase::DiagramIndex MEBase::diagram(const DiagramVector & dv) const {
  Selector<DiagramIndex> sel = diagrams(dv);
  return sel.empty()? DiagramIndex(rnd(dv.size())): sel.select(rnd());
}

const ColourLines & MEBase::
selectColourGeometry(tcDiagPtr diag) const {
  Selector<const ColourLines *> sel = colourGeometries(diag);
  return *sel.select(rnd());
}

int MEBase::nDim() const {
  return 0;
}

void MEBase::setXComb(tStdXCombPtr xc) {
  theLastXComb = xc;
  theLastSHat = lastSHat();
}

vector<Lorentz5Momentum> & MEBase::meMomenta() {
  return lastXCombPtr()->meMomenta();
}

double MEBase::reWeight() const {
  double w = 1.0;
  for ( int i = 0, N = reweights.size(); i < N; ++i ) {
    reweights[i]->setXComb(lastXCombPtr());
    w *= reweights[i]->weight();
  }
  return w;
}

double MEBase::preWeight() const {
  double w = 1.0;
  for ( int i = 0, N = preweights.size(); i < N; ++i ) {
    preweights[i]->setXComb(lastXCombPtr());
    w *= preweights[i]->weight();
  }
  return w;
}

void MEBase::generateSubCollision(SubProcess &) {}

const DVector & MEBase::meInfo() const {
  return lastXCombPtr()->meInfo();
}

void MEBase::meInfo(const DVector & info) const {
  lastXCombPtr()->meInfo(info);
}

double MEBase::alphaS() const {
  return SM().alphaS(scale());
}

double MEBase::alphaEM() const {
  return SM().alphaEM(scale());
}

void MEBase::persistentOutput(PersistentOStream & os) const {
  os << theDiagrams << ounit(theLastSHat, GeV2) << reweights << preweights
     << lastPreweight << theAmplitude << theLastXComb << theLastJacobian
     << theMaxMultCKKW << theMinMultCKKW;
}

void MEBase::persistentInput(PersistentIStream & is, int) {
  is >> theDiagrams >> iunit(theLastSHat, GeV2) >> reweights >> preweights
     >> lastPreweight >> theAmplitude >> theLastXComb >> theLastJacobian
     >> theMaxMultCKKW >> theMinMultCKKW;
}

AbstractClassDescription<MEBase> MEBase::initMEBase;
// Definition of the static class description member.

void MEBase::Init() {

  static ClassDocumentation<MEBase> documentation
    ("The ThePEG::MEBase class is the base class for all matrix elements "
     "to be used for generating sub processes in ThePEG");

  static RefVector<MEBase,ReweightBase> interfaceReweights
    ("Reweights",
     "A list of ThePEG::ReweightBase objects to modify this matrix elements.",
     &MEBase::reweights, 0, false, false, true, false);

  static RefVector<MEBase,ReweightBase> interfacePreweights
    ("Preweights",
     "A list of ThePEG::ReweightBase objects to bias the phase space for this "
     "matrix elements without influencing the actual cross section.",
     &MEBase::preweights, 0, false, false, true, false);

  static Reference<MEBase,Amplitude> interfaceAmplitude
    ("Amplitude",
     "The eventual amplitude associated to this matrix element.",
     &MEBase::theAmplitude, false, false, true, true);

  static Parameter<MEBase,int> interfaceMaxMultCKKW
    ("MaxMultCKKW",
     "If this matrix element is to be used together with others for CKKW-"
     "reweighting and veto, this should give the multiplicity of outgoing "
     "particles in the highest multiplicity matrix element in the group. "
     "If set to zero, no CKKW procedure should be applied.",
     &MEBase::theMaxMultCKKW, 0, 0, 0,
     true, false, Interface::lowerlim);

  static Parameter<MEBase,int> interfaceMinMultCKKW
    ("MinMultCKKW",
     "If this matrix element is to be used together with others for CKKW-"
     "reweighting and veto, this should give the multiplicity of outgoing "
     "particles in the lowest multiplicity matrix element in the group. If "
     "larger or equal to <interface>MaxMultCKKW</interface>, no CKKW "
     "procedure should be applied.",
     &MEBase::theMinMultCKKW, 0, 0, 0,
     true, false, Interface::lowerlim);

  interfaceMaxMultCKKW.rank(2.0);
  interfaceMinMultCKKW.rank(1.0);

}

