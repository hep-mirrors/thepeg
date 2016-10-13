// -*- C++ -*-
//
// ColourOutput.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2016 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_ColourOutput_H
#define ThePEG_ColourOutput_H

#include <ostream>

namespace ThePEG {

enum class Colour {
  reset    = 0,

  red      = 31,
  green  = 32,
  blue     = 34,

  fg_reset = 39,

  bg_red   = 41,
  bg_reset = 49,

  yellow   = 93
};

std::ostream& operator<<(std::ostream & os, Colour c);

}

#endif /* ThePEG_ColourOutput_H */
