// -*- C++ -*-
//
// Tree2toNDiagram.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Tree2toNDiagram class.
//

#include "Tree2toNDiagram.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/PDT/EnumParticles.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Tree2toNDiagram.tcc"
#endif


using namespace ThePEG;

Tree2toNDiagram & Tree2toNDiagram::add(tcPDPtr pd) {
  if ( thePartons.size() < theNSpace ) addSpacelike(pd);
  else addTimelike(pd, nextOrig);
  return *this;
}

void Tree2toNDiagram::addTimelike(tcPDPtr pd, size_type orig) {
  if ( allPartons().size() < theNSpace ||
       orig >= allPartons().size())
    throw Tree2toNDiagramError();
  thePartons.push_back(pd);
  theParents.push_back(orig);
}

tPVector Tree2toNDiagram::
construct(SubProPtr sp, const StandardXComb & xc, const ColourLines & cl) const {
  tPVector out;
  vector<Lorentz5Momentum> pout(xc.meMomenta().begin() + 2,
				xc.meMomenta().end());
//   Utilities::transform(pout.begin(), pout.end(),
// 		       Utilities::getBoostFromCM(xc.lastPartons()));
  tPPair in = xc.lastPartons();
  if ( xc.mirror() ) swap(in.first, in.second);

  tPVector ret;
  if ( in.first->dataPtr() != allPartons()[0] ||
       in.second->dataPtr() != allPartons()[nSpace() - 1] )
    throw Tree2toNDiagramError();

  PVector slike;
  slike.push_back(in.first);
  for ( int i = 1; i < nSpace() - 1; ++i )
    slike.push_back(allPartons()[i]->produceParticle());
  slike.push_back(in.second);
  ret = tPVector(slike.begin(), slike.end());
  for ( size_type i = 1; i < slike.size() - 1; ++i ) {
    slike[i-1]->addChild(slike[i]);
    sp->addIntermediate(slike[xc.mirror()? i: slike.size() - 1 - i], false);
  }
  int io = pout.size();
  PVector tlike(allPartons().size() - nSpace());
  ParticleSet done;
  for ( int i = allPartons().size() - 1; i >=  nSpace(); --i ) {
    int it = i - nSpace();
    pair<int,int> ch = children(i);
    bool iso = ch.first < 0;
    if ( iso ) {
      tlike[it] = allPartons()[i]->produceParticle(pout[--io]);
      done.insert(tlike[it]);
    } else {
      Lorentz5Momentum p = tlike[ch.first - nSpace()]->momentum() +
	tlike[ch.second - nSpace()]->momentum();
      tlike[it] = allPartons()[i]->produceParticle(p);
    }
    if ( parent(i) < nSpace() ) {
      slike[parent(i)]->addChild(tlike[it]);
      if ( parent(i) == nSpace() - 2 )
	slike[parent(i) + 1]->addChild(tlike[it]);
    }
    if ( !iso ) {
      tlike[it]->addChild(tlike[ch.first - nSpace()]);
      tlike[it]->addChild(tlike[ch.second - nSpace()]);
    }
    if ( iso ) out.push_back(tlike[it]);
    else sp->addIntermediate(tlike[it], false);
  }
  ret.insert(ret.end(), tlike.begin(), tlike.end());
  for ( int i = 0, N = out.size(); i < N; ++i )
    sp->addOutgoing(out[xc.mirror()? i: out.size() - i - 1], false);
  for ( PVector::size_type i = 0; i < slike.size() - 2; ++i ) {
    pair<int,int> ch = children(i);
    slike[ch.first]->set5Momentum(slike[i]->momentum() -
				  tlike[ch.second - nSpace()]->momentum());
  }

  cl.connect(ret);

  return out;
}

tcPDVector Tree2toNDiagram::outgoing() const {
  tcPDVector pdv;
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i).first < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
}

tcPDVector Tree2toNDiagram::external() const {
  tcPDVector pdv;
  pdv.push_back(allPartons()[0]);
  pdv.push_back(allPartons()[nSpace() - 1]);
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i).first < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
}

tcPDPair Tree2toNDiagram::incoming() const {
  return tcPDPair(allPartons()[0], allPartons()[nSpace() - 1]);
}

pair<int,int> Tree2toNDiagram::children(int ii) const {
  pair<int,int> ret = make_pair(-1, -1);
  for ( size_type i = 0; i < theParents.size(); ++i ) {
    if ( parent(i) == ii ) {
      if ( ret.first < 0 ) ret.first = i;
      else if ( ret.second < 0 ) ret.second = i;
      else throw Tree2toNDiagramError();
    }
  }
  return ret;
}

void Tree2toNDiagram::check() {
  vector< pair<int,int> > children(allPartons().size(), make_pair(-1, -1));
  theNOutgoing = 0;
  for ( size_type i = nSpace(); i < allPartons().size(); ++i ) {
    if ( children[parent(i)].first < 0 ) children[parent(i)].first = i;
    else if ( children[parent(i)].second < 0 ) children[parent(i)].second = i;
    else throw Tree2toNDiagramError();
  }
  for ( size_type i = nSpace(); i < allPartons().size(); ++i ) {
    if ( children[i].first < 0 && children[i].second < 0 ) ++theNOutgoing;
    else if ( children[i].first < 0 || children[i].second < 0 )
      throw Tree2toNDiagramError();
  }
  cPDVector parts(2);
  parts[0] = incoming().first;
  parts[1] = incoming().second;
  tcPDVector out(outgoing());
  parts.insert(parts.end(), out.begin(), out.end());
  partons(2, parts, nextOrig + 1);
}
 
ClassDescription<Tree2toNDiagram> Tree2toNDiagram::initTree2toNDiagram;

void Tree2toNDiagram::persistentInput(PersistentIStream & is, int) {
  is >> theNSpace >> theNOutgoing >> thePartons >> theParents >> nextOrig;
}

void Tree2toNDiagram::persistentOutput(PersistentOStream & os) const {
  os << theNSpace << theNOutgoing << thePartons << theParents << nextOrig;
}

Tree2toNDiagramError::Tree2toNDiagramError() {
  theMessage << "An error occurred while setting up a diagram of class "
	     << "'Tree2toNDiagram'.";
  severity(abortnow);
}

