// -*- C++ -*-
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
