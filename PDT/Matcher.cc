// -*- C++ -*-
//
// Matcher.cc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Matcher class.
//

#include "Matcher.h"
#include "StandardMatchers.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
#include "Matcher.tcc"
#endif

using namespace ThePEG;

namespace {

void dummy() {

  static MatchAny m00;
  static MatchStandardQCDParton m01;
  static MatchLightAntiQuark m02;
  static MatchLightQuark m03;
  static MatchLepton m04;
  static MatchDiquark m05;
  static MatchMeson m06;
  static MatchBaryon m07;
  static MatchNegative m08;
  static MatchNeutral m09;
  static MatchPositive m11;
  static MatchCharged m12;
}

}
