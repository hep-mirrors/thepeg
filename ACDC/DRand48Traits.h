// -*- C++ -*-
#ifndef DRand48Traits_H
#define DRand48Traits_H

#include <cstdlib>
#include "ACDCTraits.h"

namespace ACDCGenerator {

struct DRAND48 {};

template <>
struct ACDCRandomTraits<DRAND48> {

  static inline double rnd(DRAND48 & r) { return drand48(); }
  static inline double rnd(DRAND48 & r, double xl, double xu) {
    return xl + (xu - xl)*rnd(r);
  }
  template <typename InputIterator, typename OutputIterator>
  static inline void rnd(DRAND48 & r, InputIterator l, InputIterator lend,
			   InputIterator u, OutputIterator res) {
    for ( ; l != lend; ++l ) *res++ = *l + (*u++ - *l)*rnd(r);
  }
  template <typename OutputIterator>
  static inline void rnd(DRAND48 & r, int D, OutputIterator res) {
    for ( int d = 0; d < D; ++d ) *res++ = rnd(r);
  }
  static inline bool rndBool(DRAND48 & r, double x) { return rnd(r) < x; }
  static inline bool rndBool(DRAND48 & r, double x, double y) {
    return rndBool(r, x/(x + y)); }
  static inline long rndInt(DRAND48 & r, long x) {
    return long(rnd(r, 0.0, double(x))); }

};

}

#endif
