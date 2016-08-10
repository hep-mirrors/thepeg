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
  else addTimelike(pd, nextOrig);
  return *this;
}

void BlobDiagram::addTimelike(tcPDPtr pd, size_type orig) {
  if ( allPartons().size() < theNSpace ||
       orig >= allPartons().size())
    throw BlobDiagramError();
  thePartons.push_back(pd);
  theParents.push_back(orig);
}

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
  
  /* the following loop (i) starts at the last particle in allPartons, which should be a time-like particle
    and moves backwards until it reaches the first time-like particle. */
  /*for ( int i = allPartons().size() - 1; i >=  nSpace(); --i ) {
    int it = i - nSpace(); //it is a counter that should start at the number of time-like partons and count down to zero. 
    pair<int,int> ch = children(i); //ch contains all the children of the particle with index i in the loop. 
    bool iso = ch.first < 0; //the boolean is true if the first child returns a negative number, i.e. has no children (see later, children() function)
    if ( iso ) { //if iso is true, i.e. if the first child is < 0 (no children):
      tlike[it] = allPartons()[i]->produceParticle(pout[--io]); //"produce the particle", not sure what this means
      done.insert(tlike[it]); //and insert it into the ParticleSet done
    } else { //otherwise if iso is false, i.e. first child has value >= 0 (=> has children)
      Lorentz5Momentum p = tlike[ch.first - nSpace()]->momentum() +
	tlike[ch.second - nSpace()]->momentum(); //instead sum the momenta of the children 
      tlike[it] = allPartons()[i]->produceParticle(p); //and use the summed momentum to "produce" the particle 
    }
    if ( parent(i) < nSpace() ) { //if the parent of the particle i is a space-like particle:
      slike[parent(i)]->addChild(tlike[it]); //add the time-like particle i as a child 
      if ( parent(i) == nSpace() - 2 ) //don't understand what's special about nSpace() - 2
	slike[parent(i) + 1]->addChild(tlike[it]);
    }
    if ( !iso ) { //if iso is false, i.e. first child has value >= 0, i.e. has children (why isn't this in the "else" part above?)
      tlike[it]->addChild(tlike[ch.first - nSpace()]); //set the children of the time-like particle 
      tlike[it]->addChild(tlike[ch.second - nSpace()]);
    }
    if ( iso ) out.push_back(tlike[it]); //again, iso is true (i.e. if the first child is < 0) then push the time-like particle to the tPVector out
    else sp->addIntermediate(tlike[it], false); //if not, then add it as an intermediate to the SubProPtr sp
    }*/
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

  /*the following loop goes through the the space-like particles from the first to penultimate
    and sets the momentum according to the momenta of the children 
  */
  for ( PVector::size_type i = 0; i < slike.size() - 2; ++i ) {
    pair<int,int> ch = children(i);
    slike[ch.first]->set5Momentum(slike[i]->momentum() -
				  tlike[ch.second - nSpace()]->momentum());
  }

  //Perform the colour connections?
  cl.connect(ret);

  return out;
}

tcPDVector BlobDiagram::outgoing() const {
  tcPDVector pdv;
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i).first < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
}

tcPDVector BlobDiagram::external() const {
  tcPDVector pdv;
  pdv.push_back(allPartons()[0]);
  pdv.push_back(allPartons()[nSpace() - 1]);
  for ( size_type i = nSpace(); i < allPartons().size(); ++i )
    if ( children(i).first < 0 ) pdv.push_back(allPartons()[i]);
  return pdv;
}

tcPDPair BlobDiagram::incoming() const {
  return tcPDPair(allPartons()[0], allPartons()[nSpace() - 1]);
}


/*the function returns a pair of integers that should 
  be the children of particle with position ii*/
pair<int,int> BlobDiagram::children(int ii) const {
  pair<int,int> ret = make_pair(-1, -1); //the default values of the integers is -1, -1
  //loop over all particles in theParents array (defined when particles are added with addSpacelike or addTimelike)
  for ( size_type i = 0; i < theParents.size(); ++i ) {
    if ( parent(i) == ii ) { //if the parent of the particle at hand (ii) is the particle i, then 
      if ( ret.first < 0 ) ret.first = i; //if the first child index of ii is still -1, then set the child as i 
      else if ( ret.second < 0 ) ret.second = i; //otherwise if the second child index is still -1, set it to i
      else throw BlobDiagramError(); //otherwise throw an error (how is the possible?)
    }
  }
  return ret;
}

/*the function returns a pair of integers that should 
  be the children of particle with position ii*/
vector<int> BlobDiagram::vchildren(int ii) const {
  vector<int> ret;
  //loop over all particles in theParents array (defined when particles are added with addSpacelike or addTimelike)
  for ( size_type i = 0; i < theParents.size(); ++i ) {
    if ( parent(i) == ii ) { //if the parent of the particle at hand (ii) is the particle i, then 
      ret.push_back(i); //push back into the vector of children
    }
  }
  return ret;
}

void BlobDiagram::check() {
  vector< pair<int,int> > children(allPartons().size(), make_pair(-1, -1));
  theNOutgoing = 0;
  /*for ( size_type i = nSpace(); i < allPartons().size(); ++i ) {
    if ( children[parent(i)].first < 0 ) children[parent(i)].first = i;
    else if ( children[parent(i)].second < 0 ) children[parent(i)].second = i;
    else throw BlobDiagramError();
  }
  for ( size_type i = nSpace(); i < allPartons().size(); ++i ) {
    if ( children[i].first < 0 && children[i].second < 0 ) ++theNOutgoing;
    else if ( children[i].first < 0 || children[i].second < 0 )
      throw BlobDiagramError();
      }*/
  cPDVector parts(2);
  parts[0] = incoming().first;
  parts[1] = incoming().second;
  tcPDVector out(outgoing());
  parts.insert(parts.end(), out.begin(), out.end());
  partons(2, parts, nextOrig + 1);
}


bool BlobDiagram::isSame (tcDiagPtr diag) const {
  Ptr<BlobDiagram>::tcptr cmp = 
    dynamic_ptr_cast<Ptr<BlobDiagram>::tcptr>( diag );
  if ( !cmp )
    return false;
  return equals(cmp) && external() == cmp->external();
}

bool BlobDiagram::isSame (tcDiagPtr diag, map<int,int>& remap) const {
  Ptr<BlobDiagram>::tcptr cmp = 
    dynamic_ptr_cast<Ptr<BlobDiagram>::tcptr>( diag );
  if ( !cmp )
    return false;
  remap.clear();
  remap[0] = 0;
  return equals(cmp,remap);
}

bool BlobDiagram::equals(Ptr<BlobDiagram>::tcptr diag, 
			     int start, int startCmp) const {

  if ( start < 0 && startCmp < 0 )
    return true;

  if ( allPartons()[start] != diag->allPartons()[startCmp] )
    return false;

  pair<int,int> ch = children(start);
  pair<int,int> chCmp = diag->children(startCmp);

  bool match =
    equals(diag,ch.first,chCmp.first) &&
    equals(diag,ch.second,chCmp.second);

  // also try swapped legs on same vertex
  if ( !match && start > nSpace() - 1 )
    match = 
      equals(diag,ch.first,chCmp.second) &&
      equals(diag,ch.second,chCmp.first);

  return match;
    
}

bool BlobDiagram::equals(Ptr<BlobDiagram>::tcptr diag, 
			     map<int,int>& remap,
			     int start, int startCmp) const {

  if ( start < 0 && startCmp < 0 )
    return true;

  if ( allPartons()[start] != diag->allPartons()[startCmp] )
    return false;

  pair<int,int> ch = children(start);
  pair<int,int> chCmp = diag->children(startCmp);

  if ( ch.first < 0 && chCmp.first < 0 ) {
    remap[externalId(start)] = diag->externalId(startCmp);
  }

  bool match =
    equals(diag,remap,ch.first,chCmp.first) &&
    equals(diag,remap,ch.second,chCmp.second);

  // also try swapped legs on same vertex
  if ( !match && start > nSpace() - 1 )
    match = 
      equals(diag,remap,ch.first,chCmp.second) &&
      equals(diag,remap,ch.second,chCmp.first);

  return match;

}

int BlobDiagram::externalId(int id) const {
  if ( id < 0 )
    return -1;
  if ( id == 0 )
    return 0;
  if ( id == nSpace() - 1 )
    return 1;
  int k = 1;
  for ( size_type i = nSpace(); i < allPartons().size(); ++i ) {
    if ( children(i).first < 0 ) ++k;
    if ( i == size_type(id) )
      break;
  }
  return k;
}

int BlobDiagram::diagramId(int id) const {
  if ( id < 0 )
    return -1;
  if ( id == 0 ) return 0;
  if ( id == 1 ) return nSpace() - 1;
  int k = 1;
  size_type i = nSpace();
  for ( ; i < allPartons().size(); ++i ) {
    if ( children(i).first < 0 ) ++k;
    if ( k == id )
      break;
  }
  return i;
}

int BlobDiagram::mergeEmission(int emitter, int id, map<int,int>& remap) {

  if ( id < 2 )
    return -1;

  if ( remap.find(emitter) != remap.end() ) {
    remap.erase(emitter);
  }
  if ( remap.find(id) != remap.end() ) {
    remap.erase(id);
  }

  for ( map<int,int>::iterator rm = remap.begin();
	rm != remap.end(); ++rm ) {
    if ( rm->first == 0 || rm->first == 1 ) {
      rm->second = rm->first;
    } else {
      rm->second = diagramId(rm->first);
    }
  }

  // translate to diagram id
  int did = diagramId(id);
  int demitter = diagramId(emitter);

  if ( children(did) != make_pair(-1,-1) )
    return -1;

  // now get the parent
  int p = parent(did);

  int npos = -1;
  if ( p == 0 || p == nSpace() - 2 ) {
    npos = ( p == 0 ? 0 : 1 );
  } else if ( p >= nSpace() ) {
    if ( id > emitter )
      npos = emitter;
    else
      npos = emitter - 1;
  }

  pair<int,int> remove;

  size_type theNSpaceBackup = theNSpace;
  int theNOutgoingBackup = theNOutgoing;
  int nextOrigBackup = nextOrig;
  cPDVector thePartonsBackup = thePartons;
  vector<int> theParentsBackup = theParents;

  int deltaFlow = 0;
  if ( npos == 1 ) {
    if ( thePartons[did]->CC() )
      deltaFlow -= ( thePartons[did]->id() < 0 ? -1 : 1 );
    if ( thePartons[nSpace()-1]->CC() )
      deltaFlow += ( thePartons[nSpace()-1]->id() < 0 ? -1 : 1 );
  }

  // emitted from spacelike
  if ( p == 0 || p == nSpace() - 2 ) {
    if ( p == 0 && p != demitter )
      return -1;
    if ( p == nSpace() - 2 && demitter != nSpace()-1 )
      return -1;
    if ( p == 0 )
      remove = make_pair(p,did);
    else
      remove = make_pair(nSpace()-1,did);
    --theNSpace;
    --theNOutgoing;
  } else if ( p >= nSpace() ) {
    remove = children(p);
    if ( remove.first != demitter )
      swap(remove.first,remove.second);
    if ( remove != make_pair(demitter,did) )
      return -1;
    --theNOutgoing;
  } else {
    return -1;
  }

  if ( remove.first > remove.second )
    swap(remove.first,remove.second);

  for ( map<int,int>::iterator rm = remap.begin();
	rm != remap.end(); ++rm ) {
    if ( rm->first > 1 ) {
      if ( rm->second > remove.first &&
	   rm->second < remove.second )
	rm->second -= 1;
      else if ( rm->second > remove.second )
	rm->second -= 2;
    }
  }

  for ( unsigned int k = remove.first + 1; k < theParents.size(); ++k ) {
    if ( theParents[k] >= remove.first && 
	 theParents[k] < remove.second &&
	 theParents[k] >= 0 )
      theParents[k] -= 1;
    else if ( theParents[k] > remove.second && theParents[k] > 0 )
      theParents[k] -= 2;
  }
  thePartons.erase(thePartons.begin() + remove.second);
  theParents.erase(theParents.begin() + remove.second);
  thePartons.erase(thePartons.begin() + remove.first);
  theParents.erase(theParents.begin() + remove.first);

  if ( npos > 1 )
    if ( npos != externalId(p) ) {
      pair<int,int> swapDiagIds(p,diagramId(npos));
      swap(thePartons[swapDiagIds.first],thePartons[swapDiagIds.second]);
      swap(theParents[swapDiagIds.first],theParents[swapDiagIds.second]);
      for ( map<int,int>::iterator rm = remap.begin();
	    rm != remap.end(); ++rm ) {
	if ( rm->first > 1 ) {
	  if ( rm->second == swapDiagIds.first ) {
	    rm->second = swapDiagIds.second;
	  } else if ( rm->second == swapDiagIds.second ) {
	    rm->second = swapDiagIds.first;
	  }
	}
      }
    }

  for ( map<int,int>::iterator rm = remap.begin();
	rm != remap.end(); ++rm ) {
    if ( rm->first > 1 ) {
      rm->second = externalId(rm->second);
    }
  }

  if ( npos == 1 ) {
    if ( thePartons[nSpace()-1]->CC() )
      deltaFlow -= ( thePartons[nSpace()-1]->id() < 0 ? -1 : 1 );

    if ( deltaFlow != 0 )
      thePartons[nSpace()-1] = thePartons[nSpace()-1]->CC();

  }

  try {
    check();
  } catch (BlobDiagramError&) {
    theNSpace = theNSpaceBackup;
    theNOutgoing = theNOutgoingBackup;
    nextOrig = nextOrigBackup;
    thePartons = thePartonsBackup;
    theParents = theParentsBackup;
    return -1;
  }

  return npos;

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

