// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AbstractFFVVertex class.
//

#include "AbstractFFVVertex.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace Helicity;

AbstractNoPIOClassDescription<AbstractFFVVertex> 
AbstractFFVVertex::initAbstractFFVVertex;
// Definition of the static class description member.

void AbstractFFVVertex::Init() {

  static ClassDocumentation<AbstractFFVVertex> documentation
    ("The AbstractFFVVertex class provides a base class for all"
     " fermion-fermion-vector interactions");

}

