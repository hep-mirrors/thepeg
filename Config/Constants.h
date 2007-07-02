// -*- C++ -*-
#ifndef ThePEG_Constants_H
#define ThePEG_Constants_H

// This file defines a number of useful constants, placed in the
// namespace <!id>ThePEG::Constants<!!id>.

#include "Unitsystem.h"
#include <cmath>
#include <cfloat>

namespace ThePEG {

/**
 * The Constants namespace containing some useful physical constants
 * with suitable units.
 */
namespace Constants {

using namespace ThePEG::Units;

/** A really large length. */
const Length MaxLength = 1.0e20*meter;

/** A really large energy. */
const Energy MaxEnergy = 100000.0*GeV;

/** A really large squared energy. */
const Energy2 MaxEnergy2 = MaxEnergy*MaxEnergy;

/** The largest possible double. */
const double MaxDouble = DBL_MAX;

/** A really large double. */
const double HugeDouble = DBL_MAX/10000.0;

/** The largest possible float. */
const double MaxFloat = FLT_MAX;

/** A really large floa.t */
const double HugeFloat = FLT_MAX/100.0;

/** A really large rapidity */
const double MaxRapidity = 100.0;

/** Good old \f$\pi\f$. */
const double pi    = M_PI;
const double twopi = 2.0 * pi;

/** A really large integer */
const long MaxInt = 1000000000L;

/** The smallest non-zero double. */
const double epsilon = DBL_EPSILON;

/** The Euler gamma */
const double EulerGamma = 0.577215664901532861;

}

}

#endif /* ThePEG_Constants_H */
