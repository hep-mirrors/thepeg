// -*- C++ -*-
#ifndef ACDCTraits_H
#define ACDCTraits_H

namespace ACDCGenerator {

template <typename FncPtr>
struct ACDCFncTraits {

  static inline double value(const FncPtr & f, const DVector & x) {
    return (*f)(x);
  }

};

template <typename Rnd>
struct ACDCRandomTraits {

  static inline double rnd(Rnd & r) { return r.flat(); }
  static inline double rnd(Rnd & r, double xl, double xu) {
    return xl + (xu - xl)*rnd(r);
  }
  template <typename InputIterator, typename OutputIterator>
  static inline void rnd(Rnd & r, InputIterator l, InputIterator lend,
			   InputIterator u, OutputIterator res) {
    for ( ; l != lend; ++l ) *res++ = *l + (*u++ - *l)*rnd(r);
  }
  template <typename OutputIterator>
  static inline void rnd(Rnd & r, int D, OutputIterator res) {
    for ( int d = 0; d < D; ++d ) *res++ = rnd(r);
  }
  static inline bool rndBool(Rnd & r, double x) { return rnd(r) < x; }
  static inline bool rndBool(Rnd & r, double x, double y) {
    return rndBool(r, x/(x + y)); }
  static inline long rndInt(Rnd & r, long x) {
    return long(rnd(r, 0.0, double(x)));
  }

};

}

#endif
