// -*- C++ -*-
#ifndef ACDCGenConfig_H
#define ACDCGenConfig_H

// This is the main config header file for ACDCGen. Do not make
// changes in this file. If you need to modify anything, edit a copy
// of the file which can be included instead of this file using the
// macro <!id>ACDC_ALT_CONFIG<!!id>.

#ifndef ACDC_ALT_CONFIG

#include <vector>
#include <map>
#include <limits>

namespace ACDCGenerator {

// ACDCGen uses some classes and functions from the standard
// library. These are here imported into the ACDCGenerator
// namespace. If alternative classes with the same API are needed
// these should be imported into the namespace in the ACDC_ALT_CONFIG
// file with the same name.

using std::vector;
using std::multimap;
using std::numeric_limits;
using std::map;
using std::max;
using std::min;
using std::swap;
using std::make_pair;

// What are we going to use to represent the dimension of the
// functions to be sampled?
typedef short DimType;

}

#else

#include ACDC_ALT_CONFIG

#endif

namespace ACDCGenerator {

typedef vector<double> DVector;

}

#endif
