// -*- C++ -*-
#ifndef ThePEG_Constants_H
#define ThePEG_Constants_H

// This file defines a number of useful constants, placed in the
// namespace <!id>ThePEG::Constants<!!id>.

#include "Units.h"
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
static const Length MaxLength = 1.0e20*m;

/** A really large energy. */
static const Energy MaxEnergy = 100000.0*GeV;

/** A really large squared energy. */
static const Energy2 MaxEnergy2 = MaxEnergy*MaxEnergy;

/** The largest possible double. */
static const double MaxDouble = DBL_MAX;

/** A really large double. */
static const double HugeDouble = DBL_MAX/10000.0;

/** The largest possible float. */
static const double MaxFloat = FLT_MAX;

/** A really large floa.t */
static const double HugeFloat = FLT_MAX/100.0;

/** A really large rapidity */
static const double MaxRapidity = 100.0;

/** Good old \f$\pi\f$. */
static const double pi = M_PI;

/** A really large integer */
static const long MaxInt = 1000000000L;

/** The smallest non-zero double. */
static const double epsilon = DBL_EPSILON;

/** The Euler gamma */
static const double EulerGamma = 0.577215664901532861;

}

}

#endif /* ThePEG_Constants_H */
