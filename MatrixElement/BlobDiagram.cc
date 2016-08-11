// -*- C++ -*-
//
// BlobDiagram.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the BlobDiagram class.
//

#include "BlobDiagram.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/Utilities/UtilityBase.h"
#include "ThePEG/Handlers/StandardXComb.h"
#include "ThePEG/PDT/EnumParticles.h"

using namespace ThePEG;

BlobDiagram::~BlobDiagram() {}

BlobDiagram & BlobDiagram::add(tcPDPtr pd) {
  if ( thePartons.size() < theNSpace ) addSpacelike(pd);
  else addTimelike(pd);
  return *this;
}

void BlobDiagram::addTimelike(tcPDPtr pd) {
  if ( allPartons().size() < theNSpace) throw BlobDiagramError();
  thePartons.push_back(pd);
}

/*void BlobDiagram::addTimelike(tcPDPtr pd, size_type orig) {
  if ( allPartons().size() < theNSpace ||
       orig >= allPartons().size())
    throw BlobDiagramError();
  thePartons.push_back(pd);
  theParents.push_back(orig);
}*/

tPVector BlobDiagram::
construct(SubProPtr sp, const StandardXComb & xc, const ColourLines & cl) const {
  tPVector out;
  vector<Lorentz5Momentum> pout(xc.meMomenta().begin() + 2,
				xc.meMomenta().end()); //outgoing momenta
  //not sure what the following 4 lines do: perhaps they order the momenta in some specific order expected later on 
  if ( xc.needsReshuffling() )
    xc.reshuffle(pout); 
  tPPair in = xc.lastPartons();
  if ( xc.mirror() ) swap(in.first, in.second); // in seems to be the incoming particles (?)


  /*if the incoming particles from in do not match the first space-like parton 
    or the last space-like parton (which should be the incoming particles,
    then it throws an error
  */
  tPVector ret;
  if ( in.first->dataPtr() != allPartons()[0] ||
       in.second->dataPtr() != allPartons()[nSpace() - 1] )
    throw BlobDiagramError();

  /* now it starts looking at space-like partons */
  PVector slike;
  slike.push_back(in.first); //puts the first incoming one in
  /*the following loop starts from the second space-like parton and goes up to the penultimate one:
    it seems to end up in a PVector containing firstly the first incoming parton, then all the other spacelike partons and then 
    in the last entry the second incoming parton*/
  for ( int i = 1; i < nSpace() - 1; ++i )
    slike.push_back(allPartons()[i]->produceParticle()); //what exactly is produceParticle?
  slike.push_back(in.second);

  /* in what follows, ret seems to be a vector containing all the space-like partons,
     as constructed in PVector above */
  ret = tPVector(slike.begin(), slike.end());
  /*for each space-like parton, starting from the first incoming, the space-like parton that follows it
    is defined as its child*/
  for ( size_type i = 1; i < slike.size() - 1; ++i ) {
    slike[i-1]->addChild(slike[i]);
    /* not quite sure what the following line does but my guess is that it
       adds to the SubProPtr (subprocess pointer?) a space-like parton,
       as intermediate particle, excluding the first or last one (i.e. the incoming ones) */
    sp->addIntermediate(slike[xc.mirror()? i: slike.size() - 1 - i], false); 
  }

  //the int io is simply the size of the outgoing momenta
  int io = pout.size();
  //the PVector tlike has the size of # of all partons minus the # of space-like ones
  PVector tlike(allPartons().size() - nSpace());
  //Not sure what a ParticleSet is!
  ParticleSet done;
  
  for ( int i = allPartons().size() - 1; i >=  nSpace(); --i ) {
    int it = i - nSpace(); //it is a counter that should start at the number of time-like partons and count down to zero. 
    tlike[it] = allPartons()[i]->produceParticle(pout[--io]);
    done.insert(tlike[it]);
    //add the time-like parton as the child of both incoming (space-like) partons. 
    slike[0]->addChild(tlike[it]);
    slike[1]->addChild(tlike[it]);
    out.push_back(tlike[it]); 
  }

  
  //the next line adds the time-like partons as found above to tPVector ret. 
  ret.insert(ret.end(), tlike.begin(), tlike.end());
  //the next line seems to loop through the tPVector out and add the particles to the SubProPtr sp as outgoing, given some condition I need to think about. 
  for ( int i = 0, N = out.size(); i < N; ++i )
    sp->addOutgoing(out[xc.mirror()? i: out.size() - i - 1], false);

  //Perform the colour connections?
  cl.connect(ret);

  return out;
}


tcPDPair BlobDiagram::incoming() const {
  return tcPDPair(allPartons()[0], allPartons()[nSpace() - 1]);
}

tcPDVector BlobDiagram::outgoing() const {
  tcPDVector pdv;
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i)[0] < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
}

tcPDVector BlobDiagram::external() const {
  tcPDVector pdv;
  pdv.push_back(allPartons()[0]);
  pdv.push_back(allPartons()[nSpace() - 1]);
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i)[0] < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
  }

vector<int> BlobDiagram::children(int ii) const {
  vector<int> ret;
  /*loop through all the parents and check whether particle ii is the parent of parrticle i,
    if so, push it into the vector ret
  */
  for ( size_type i = 0; i < theParents.size(); ++i ) {
    if ( parent(i) == ii ) {
      ret.push_back(i);
    } 
  }
  if(ret.size() == 0) {
    ret.push_back(-1);
  }
  return ret;
}

void BlobDiagram::check() {
  vector< pair<int,int> > children(allPartons().size(), make_pair(-1, -1));
  theNOutgoing = 0;
 
  cPDVector parts(2);
  parts[0] = incoming().first;
  parts[1] = incoming().second;
  tcPDVector out(outgoing());
  parts.insert(parts.end(), out.begin(), out.end());
  partons(2, parts, nextOrig + 1);
}
 
ClassDescription<BlobDiagram> BlobDiagram::initBlobDiagram;

void BlobDiagram::persistentInput(PersistentIStream & is, int) {
  is >> theNSpace >> theNOutgoing >> thePartons >> theParents >> nextOrig;
}

void BlobDiagram::persistentOutput(PersistentOStream & os) const {
  os << theNSpace << theNOutgoing << thePartons << theParents << nextOrig;
}

BlobDiagramError::BlobDiagramError() {
  theMessage << "An error occurred while setting up a diagram of class "
	     << "'BlobDiagram'.";
  severity(abortnow);
}

