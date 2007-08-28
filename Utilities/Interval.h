// -*- C++ -*-
#ifndef ThePEG_Interval_H
#define ThePEG_Interval_H
// This is the declaration of the Interval class.

#include <utility>
#include <vector>
#include "Interval.fh"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

template <typename T, typename CMP>
/**
 * An <code>Interval</code> object is used to represent an interval
 * <code>[ lower(), upper() )</code> where the ordering is defined by
 * the <code>bool operator()(const T &, const T &) const</code> member
 * of the CMP class (by defaut less<T>).
 */
class Interval {

public:

  /**
   * Construct an empty interval.
   */
  inline Interval();

  /**
   * Construct interval [dn,up).
   */
  inline Interval(T dn, T up);

  /**
   * Test for equality.
   */
  inline bool operator==(const Interval & i) const;

  /**
   * Test for ordering.
   * @return true if <code>lower() < i.lower()</code> or <code>lower()
   * == i.lower()</code> and <code>upper() < i.upper()</code>.
   */
  inline bool operator<(const Interval & i) const;

  /**
   * Check consistency ie. that lower() < upper().
   */
  inline bool check() const;

  /**
   * Returns true if x is within the interval.
   */
  inline bool operator()(T x) const;

  /**
   * Returns true if x is within the interval.
   */
  inline bool includes(T x) const;

  /**
   * Returns true if the whole of i is within the interval.
   */
  inline bool includes(const Interval<T,CMP> & i) const;

  /**
   * If x is in the interval return the interval [x,upper()) and
   * change this interval to [lower(),x). If x is not within the
   * interval, return [0,0) and leave this interval as it is.
   */
  inline Interval<T,CMP> chopUpper(T x);

  /**
   * If x is in the interval return the interval [lower(),x) and
   * change this interval to [x,upper()). If x is not within the
   * interval, return [0,0) and leave this interval as it is.
   */
  inline Interval<T,CMP> chopLower(T x);

  /**
   * If this interval operlaps with i return the overlapping interval.
   */
  inline Interval<T,CMP> overlap(const Interval & i) const;

  /**
   * If this interval operlaps with i return the union of the two
   * intervals.
   */
  inline Interval<T,CMP> sum(const Interval & i) const;

  /**
   * Return the upper limit of the interval.
   */
  inline T upper() const;

  /**
   * Return the lower limit of the interval.
   */
  inline T lower() const;

  /**
   * Set the upper limit of the interval.
   */
  inline void upper(T up);

  /**
   * Set the lower limit of the interval.
   */
  inline void lower(T dn);

  /**
   * Check if any of the values in the iterator given range is
   * included in this interval.
   */
  template <typename Iterator>
  inline static bool check(Iterator first, Iterator last);

  /**
   * Check if all of the values in the given iterator range is
   * included in this interval.
   */
  template <typename Iterator>
  inline static bool checkAll(Iterator first, Iterator last);

  /**
   * If x is in the given interval, split the given interval in two,
   * otherwise return an empty list.
   */
  static std::vector< Interval<T,CMP> > split(Interval<T,CMP>, T x);
  
  /**
   * For each value in the given range is in the given interval, split
   * the interval in two, otherwise return an empty list.
   */
  template<typename Iterator>
  static std::vector< Interval<T,CMP> > split(Interval<T,CMP>,
					      Iterator first, Iterator last);

private:

  /** The lower and upper limit of this interval */
  std::pair<T,T> theLimits;

  /** The object used for comparisons. */
  static CMP cmp;

};

/** An interval of doubles. */
typedef Interval<double> DInterval;

/** Helper function to create an interval of a type determined by the
 *  parameters. */
template <typename T>
inline Interval<T> makeInterval(T dn, T up);

/** Ouptut an interval to a stream. */
template <typename OStream, typename T, typename CMP>
inline OStream & operator<<(OStream &, const Interval<T,CMP> &);

/** Input an interval from a stream. */
template <typename IStream, typename T, typename CMP>
inline IStream & operator>>(IStream &, Interval<T,CMP> &);

/** Output an interval of a diminsionful type to a stream using the
 *  given unit.
 * @param os the output stream.
 * @param i the interval.
 * @param u the unit. */
template <typename OStream, typename T, typename CMP, typename UT>
void ounitstream(OStream & os, const Interval<T,CMP> & i, UT & u) {
  os << ounit(i.lower(), u) << ounit(i.upper(), u);
}

/** Input an interval of a diminsionful type from a stream using the
 *  given unit.
 * @param is the input stream.
 * @param i the interval.
 * @param u the unit. */
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
