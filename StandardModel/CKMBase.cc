// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the CKMBase class.
//

#include "CKMBase.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/ClassDocumentation.h"

using namespace ThePEG;

AbstractNoPIOClassDescription<CKMBase> CKMBase::initCKMBase;

void CKMBase::Init() {

  static ClassDocumentation<CKMBase> documentation
    ("An abstract base classused by the StandardModelBase to implement "
     "the Cabibbo-Kobayashi-Mascawa mixing matrix.");

}

