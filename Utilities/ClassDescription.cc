// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ClassDescription class.
//

#include "ClassDescription.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClassDescription.tcc"
#endif

using namespace ThePEG;

bool ClassDescriptionBase::isA(const ClassDescriptionBase & base) const {
  if ( base.info() == info() ) return true;
  for ( DescriptionVector::const_iterator i = descriptions().begin();
	i != descriptions().end(); ++i ) if ( (**i).isA(base) ) return true;
  return false;
}

