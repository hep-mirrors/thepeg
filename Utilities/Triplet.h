// -*- C++ -*-
#ifndef ThePEG_Triplet_H
#define ThePEG_Triplet_H

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

template <typename T1, typename T2, typename T3>
struct Triplet {
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;

  T1 first;
  T2 second;
  T3 third;

  Triplet() : first(T1()), second(T2()), third(T3()) {}

  Triplet(const T1 & t1, const T2 & t2, const T3 & t3)
    : first(t1), second(t2), third(t3) {}

  Triplet(const Triplet<T1,T2,T3> & t)
    : first(t.first), second(t.second), third(t.third) {}

  template <typename U1, typename U2, typename U3>
  Triplet(const Triplet<U1,U2,U3> & u)
    : first(u.first), second(u.second), third(u.third) {}

  bool operator==(const Triplet<T1,T2,T3> & t) const {
    return first == t.first && second == t.second && third == t.third;
  }

  bool operator<(const Triplet<T1,T2,T3> & t) const {
    return first < t.first ||
      ( !(t.first < first) && 
	( second < t.second ||
	  ( !(t.second < second) && third < t.third )));
  }

};


template <typename T1, typename T2, typename T3>
inline Triplet<T1,T2,T3>
makeTriplet (const T1 & t1, const T2 & t2, const T3 & t3)
{
  return Triplet<T1,T2,T3>(t1, t2, t3);
}

template <typename OStream, typename T1, typename T2, typename T3>
OStream & operator<<(OStream & os, const Triplet<T1,T2,T3> & t) {
  return os << t.first << t.second << t.third;
}

template <typename IStream, typename T1, typename T2, typename T3>
IStream & operator>>(IStream & is, Triplet<T1,T2,T3> & t) {
  return is >> t.first >> t.second >> t.third;
}



}


#endif /* ThePEG_Triplet_H */
