// -*- C++ -*-
#ifndef ThePEG_Constants_H
#define ThePEG_Constants_H

// This file defines a number of useful constants, placed in the
// namespace <!id>ThePEG::Constants<!!id>.

#include "Units.h"
#include <cmath>
#include <cfloat>

namespace ThePEG {

namespace Constants {

using namespace ThePEG::Units;

static const Length MaxLength = 1.0e20*m;
static const Energy MaxEnergy = 100000.0*GeV;
static const Energy2 MaxEnergy2 = MaxEnergy*MaxEnergy;
static const double MaxDouble = DBL_MAX;
static const double HugeDouble = DBL_MAX/10000.0;
static const double MaxFloat = FLT_MAX;
static const double HugeFloat = FLT_MAX/100.0;
static const double MaxRapidity = 100.0;
static const double pi = M_PI;
static const long MaxInt = 1000000000L;
static const double epsilon = DBL_EPSILON;
static const double EulerGamma = 0.577215664901532861;

}

}

#endif /* ThePEG_Constants_H */
