// -*- C++ -*-
#ifndef ThePEG_Interval_H
#define ThePEG_Interval_H
//
// This is the declaration of the <!id>Interval<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// An <!id>Interval<!!id> object are used to represent an interval [
// lower(), upper() ) where the ordering is defined by the 'bool
// operator()(const T &, const T &) const' member of the CMP class (by
// defaut less<T>).
//

#include <utility>
#include <vector>
#include "Interval.fh"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

template <typename T, typename CMP>
class Interval {

public:

  inline Interval();
  // Construct an empty interval.

  inline Interval(T dn, T up);
  // Construct interval [dn,up).

  inline Interval(const Interval & i);
  // Copy constructor.

  inline const Interval & operator=(const Interval & i);
  // Assignment.

  inline bool operator==(const Interval & i) const;
  inline bool operator<(const Interval & i) const;
  // Equality and ordering.

  inline bool check() const;
  // Check consistency ie. that lower() < upper().

  inline bool operator()(T x) const;
  inline bool includes(T x) const;
  // Returns true if x is within the interval.

  inline bool includes(const Interval<T,CMP> & i) const;
  // Returns true if the whole of i is within the interval.

  inline Interval<T,CMP> chopUpper(T x);
  // If x is in the interval return the interval [x,upper()) and
  // change this interval to [lower(),x). If x is not within the
  // interval, return [0,0) and leave this interval as it is.

  inline Interval<T,CMP> chopLower(T x);
  // If x is in the interval return the interval [lower(),x) and
  // change this interval to [x,upper()). If x is not within the
  // interval, return [0,0) and leave this interval as it is.

  inline Interval<T,CMP> overlap(const Interval & i) const;
  // If this interval operlaps with i return the overlapping interval.

  inline Interval<T,CMP> sum(const Interval & i) const;
  // If this interval operlaps with i return the union of the two
  // intervals.

  inline T upper() const;
  inline T lower() const;
  // Return the limits of the interval.

  inline void upper(T up);
  inline void lower(T dn);
  // Set the limits of the interval.

  template <typename Iterator>
  inline static bool check(Iterator first, Iterator last);
  // Check if any of the values in the given range is included in this
  // interval.

  template <typename Iterator>
  inline static bool checkAll(Iterator first, Iterator last);
  // Check if all of the values in the given range is included in this
  // interval.

  static std::vector< Interval<T,CMP> > split(Interval<T,CMP>, T x);
  // If x is in the given interval, split the interval in two,
  // otherwise return an empty list.
  
  template<typename Iterator>
  static std::vector< Interval<T,CMP> > split(Interval<T,CMP>,
					      Iterator first, Iterator last);
  // For each value in the given range is in the given interval, split
  // the interval in two, otherwise return an empty list.

private:

  std::pair<T,T> theLimits;

  static CMP cmp;

};

typedef Interval<double> DInterval;

template <typename T>
inline Interval<T> makeInterval(T dn, T up);
// Create an interval [dn, up)

template <typename OStream, typename T, typename CMP>
inline OStream & operator<<(OStream &, const Interval<T,CMP> &);

template <typename IStream, typename T, typename CMP>
inline IStream & operator>>(IStream &, Interval<T,CMP> &);

template <typename OStream, typename T, typename CMP, typename UT>
void ounitstream(OStream & os, const Interval<T,CMP> & i, UT & u) {
  os << ounit(i.lower(), u) << ounit(i.upper(), u);
}

template <typename IStream, typename T, typename CMP, typename UT>
void iunitstream(IStream & is, Interval<T,CMP> & i, UT & u) {
  T low, upp;
  is >> iunit(low, u) >> iunit(upp, u);
  i = Interval<T,CMP>(low, upp);
}

}

#include "Interval.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Interval.tcc"
#endif

#endif /* ThePEG_Interval_H */
