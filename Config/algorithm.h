// -*- C++ -*-
#ifndef ThePEG_algorithm_H
#define ThePEG_algorithm_H

// This file implements a number of interfaces to <!id>std::<!!id>
// algorithms, modified to take a whole container as argument rather
// than a range of iterators.

#include "ThePEG/Config/ThePEG.h"
#include <algorithm>
// #include "algorithm.fh"
// #include "algorithm.xh"

namespace ThePEG {

template <typename Iterator>
struct IteratorRange: public std::pair<Iterator,Iterator> {
  typedef std::pair<Iterator,Iterator> BaseType;
  IteratorRange() {}
  IteratorRange(const IteratorRange & ir): BaseType(ir) {}
  IteratorRange(const BaseType & ir): BaseType(ir) {}
};

template <typename Container>
inline IteratorRange<typename Container::iterator>
range(Container & c) {
  return std::make_pair(c.begin(), c.end());
}

template <typename Container>
inline IteratorRange<typename Container::const_iterator>
range(const Container & c) {
  return std::make_pair(c.begin(), c.end());
}

template <typename Container>
inline IteratorRange<typename Container::reverse_iterator>
rrange(Container & c) {
  return std::make_pair(c.rbegin(), c.rend());
}

template <typename Container>
inline IteratorRange<typename Container::const_reverse_iterator>
rrange(const Container & c) {
  return std::make_pair(c.begin(), c.end());
}

template <typename Iterator, typename FNC>
inline FNC for_each(IteratorRange<Iterator> r, FNC f) {
  return std::for_each(r.first, r.second, f);
}

template <typename Iterator, typename T>
inline Iterator find(IteratorRange<Iterator> r, const T & t) {
  return std::find(r.first, r.second, t);
}

template <typename Iterator, typename Pred>
inline Iterator find_if(IteratorRange<Iterator> r, Pred p) {
  return std::find_if(r.first, r.second, p);
}

template <typename Iterator, typename T>
inline void replace(IteratorRange<Iterator> r, const T & oval, const T & nval) {
  return std::replace(r.first, r.second, oval, nval);
}

template <typename Cont, typename FNC>
inline FNC for_each(Cont & c, FNC f) {
  return std::for_each(c.begin(), c.end(), f);
}

template <typename Cont, typename FNC>
inline FNC for_each(const Cont & c, FNC f) {
  return std::for_each(c.begin(), c.end(), f);
}

template <typename Cont, typename Type>
inline typename Cont::iterator find(Cont & c, const Type & t) {
  return find(range(c), t);
}

template <typename Cont, typename Type>
inline typename Cont::const_iterator find(const Cont & c, const Type & t) {
  return find(range(c), t);
}

template <typename Cont, typename Pred>
inline typename Cont::iterator find_if(Cont & c, const Pred & p) {
  return find_if(range(c), p);
}

template <typename Cont, typename Pred>
inline typename Cont::const_iterator find_if(const Cont & c, const Pred & p) {
  return find_if(range(c), p);
}

template <typename Cont, typename T>
inline void replace(Cont & c, const T & oval, const T & nval) {
  return replace(range(c), oval, nval);
}

}

// #include "algorithm.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "algorithm.tcc"
#endif

#endif /* ThePEG_algorithm_H */
