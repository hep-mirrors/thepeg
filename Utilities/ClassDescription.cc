// -*- C++ -*-
//
// ClassDescription.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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

