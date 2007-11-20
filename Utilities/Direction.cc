// -*- C++ -*-
//
// Direction.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Direction class.
//

#include "Direction.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Direction.tcc"
#endif

using namespace ThePEG;

MultipleDirectionException::MultipleDirectionException(int i) {
  theMessage << "Attempted to instantiate a second object of the Direction<"
	     << i << ">. This is intolerable!";
  severity(abortnow);
}

UndefinedDirectionException::UndefinedDirectionException(int i) {
  theMessage << "Attempted to use/create a Direction<"
	     << i << "> object with undefined direction. This is intolerable!";
  severity(abortnow);
}
