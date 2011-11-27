// -*- C++ -*-
//
// MEGroup.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
// Copyright (C) 2009-2010 Simon Platzer
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the MEGroup class.
//

#include "MEGroup.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Utilities/Rebinder.h"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonExtractor.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Handlers/StdDependentXComb.h"
#include "ThePEG/Handlers/StdXCombGroup.h"

using namespace ThePEG;

MEGroup::MEGroup()
  : theDependent(), theNDimMap(), theNDim(0) {}

MEGroup::~MEGroup() {}

void MEGroup::doinit() {
  MEBase::doinit();
  head()->init();
  use(head());
  theNDim = head()->nDim();
  if (!uniformAdditional()) {
    int off = theNDim;
    for ( MEVector::iterator me = theDependent.begin();
	  me != theDependent.end(); ++me )
      if ( (**me).nDim() > head()->nDim() ) {
	theNDimMap[*me] = off;
	off += ((**me).nDim() - head()->nDim());
	theNDim += ((**me).nDim() - head()->nDim());
      }
  } else {
    int maxadd = 0;
    for ( MEVector::iterator me = theDependent.begin();
	  me != theDependent.end(); ++me )
      if ( (**me).nDim() - head()->nDim() > maxadd ) {
	maxadd = ((**me).nDim() - head()->nDim());
      }
    theNDim += maxadd;
  }
  if ( mcSumDependent() )
    theNDim += 1;
}

void MEGroup::rebind(const TranslationMap & trans) {
  map<tMEPtr,int> rebound;
  for (map<tMEPtr,int>::iterator it = theNDimMap.begin();
       it != theNDimMap.end(); ++it) {
    rebound.insert(make_pair(trans.translate(it->first),it->second));
  }
  theNDimMap = rebound;
  MEBase::rebind(trans);
}

IVector MEGroup::getReferences() {
  IVector ret = MEBase::getReferences();
  for (map<tMEPtr,int>::iterator it = theNDimMap.begin();
       it != theNDimMap.end(); ++it)
    ret.push_back(it->first);
  return ret;
}

int MEGroup::dependentOffset(tMEPtr dep) const {
  if ( uniformAdditional() )
    return head()->nDim();
  map<tMEPtr,int>::const_iterator it =
    theNDimMap.find(dep);
  if (it == theNDimMap.end())
    return 0;
  return it->second;
}

StdDependentXCombPtr MEGroup::makeDependentXComb (tStdXCombPtr xcHead,
						  const cPDVector& proc,
						  tMEPtr depME,
						  const PartonPairVec& pbs) const {
  
  MEBase::DiagramVector depDiags = dependentDiagrams(proc,depME);

  if ( depDiags.empty() )
    return StdDependentXCombPtr();

  PartonPairVec::const_iterator ppit = pbs.begin();
  for ( ; ppit != pbs.end(); ++ppit ) {
    if ( ppit->first->parton() == depDiags.front()->partons()[0] &&
	 ppit->second->parton() == depDiags.front()->partons()[1] )
      break;
  }

  if ( ppit == pbs.end() ) {
    generator()->logWarning(
      Exception() 
      << "Could not create a dependent XComb object"
      << " for the MEGroup '"
      << name() 
      << "' since the dependent matrix element '"
      << depME->name() 
      << "' did not match any of the incoming partons."
      << Exception::warning);
    return StdDependentXCombPtr();
  }

  StdDependentXCombPtr ret = 
    new_ptr(StdDependentXComb(xcHead,*ppit,depME,depDiags));

  return ret;

}

bool MEGroup::generateKinematics(const double * r) {
  if (!head()->generateKinematics(r))
    return false;
  MEVector::const_iterator me = dependent().begin();
  tStdXCombGroupPtr xcgroup = dynamic_ptr_cast<tStdXCombGroupPtr>(lastXCombPtr());
  StdDepXCVector::const_iterator depxc = xcgroup->dependent().begin();
  assert(xcgroup);
  if ( !mcSumDependent() ) {
    for ( ; depxc != xcgroup->dependent().end(); ++depxc, ++me ) {
      if ( !(*depxc) )
	continue;
      if ( !(**depxc).matrixElement()->apply() )
	continue;
      (**depxc).remakeIncoming();
      (**me).generateKinematics(r + dependentOffset(*me));
    }
  } else {
    size_t i = size_t(r[nDim()-1]*dependent().size());
    if ( !xcgroup->dependent()[i] )
      return false;
    if ( !xcgroup->dependent()[i]->matrixElement()->apply() )
      return false;
    xcgroup->dependent()[i]->remakeIncoming();
    lastDependentXComb(xcgroup->dependent()[i]);
    dependent()[i]->generateKinematics(r + dependentOffset(dependent()[i]));
  }
  return true;
}

void MEGroup::flushCaches() {
  head()->flushCaches();
  for ( MEVector::const_iterator dep = dependent().begin();
	dep != dependent().end(); ++dep )
    (**dep).flushCaches();
}

void MEGroup::setXComb(tStdXCombPtr xc) {
  MEBase::setXComb(xc);
  head()->setXComb(xc);
  tStdXCombGroupPtr xcgroup = dynamic_ptr_cast<tStdXCombGroupPtr>(xc);
  if ( !xcgroup )
    return;
  MEVector::const_iterator depme = dependent().begin();
  StdDepXCVector::const_iterator depxc = xcgroup->dependent().begin();
  for ( ; depxc != xcgroup->dependent().end(); ++depxc, ++depme ) {
    if ( !(*depxc) )
      continue;
    (**depme).setXComb(*depxc);
  }
}

void MEGroup::setKinematics() {
  MEBase::setKinematics();
  head()->setKinematics();
  for ( MEVector::iterator me = theDependent.begin();
	me != theDependent.end(); ++me ) {
    if ( (**me).apply() && (**me).lastXCombPtr() )
      (**me).setKinematics();
  }
}

void MEGroup::clearKinematics() {
  MEBase::clearKinematics();
  head()->clearKinematics();
  for ( MEVector::iterator me = theDependent.begin();
	me != theDependent.end(); ++me )
    (**me).clearKinematics();
}

void MEGroup::persistentOutput(PersistentOStream & os) const {
  os << theHead << theDependent << theNDimMap << theNDim;
}

void MEGroup::persistentInput(PersistentIStream & is, int) {
  is >> theHead >> theDependent >> theNDimMap >> theNDim;
}

AbstractClassDescription<MEGroup> MEGroup::initMEGroup;
// Definition of the static class description member.

void MEGroup::Init() {

  static ClassDocumentation<MEGroup> documentation
    ("The ThePEG::MEGroup class is the base class for all matrix elements "
     "to be used for generating sub process groups in ThePEG");

  static Reference<MEGroup,MEBase> interfaceHead
    ("Head",
     "The head matrix element for this matrix element group.",
     &MEGroup::theHead, false, false, true, false, false);


  static RefVector<MEGroup,MEBase> interfaceDependent
    ("Dependent",
     "The vector of dependent matrix elements in this matrix element group.",
     &MEGroup::theDependent, -1, false, false, true, false, false);

}

