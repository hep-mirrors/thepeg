// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ClassDocumentation class.
//

#include "ClassDocumentation.h"
#include "ThePEG/Repository/BaseRepository.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClassDocumentation.tcc"
#endif

using namespace ThePEG;


ClassDocumentationBase::
ClassDocumentationBase(string newDocumentation,
		       string newModelDescription,
		       string newModelReferences,
		       const type_info & newTypeInfo)
  : theDocumentation(newDocumentation),
    theModelDescription(newModelDescription),
    theModelReferences(newModelReferences) {
  BaseRepository::Register(*this, newTypeInfo);
}

