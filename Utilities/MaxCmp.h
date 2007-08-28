// -*- C++ -*-
#ifndef THEPEG_MaxCmp_H
#define THEPEG_MaxCmp_H
//
// This is the declaration of the MaxCmp class.
//

namespace ThePEG {

/**
 * MaxCmp is a helper class to be used in a loop where one would like
 * to keep track of the largest value so far of a certain
 * expression. The class simply checks if the given value to the
 * operator() is the largest so far (in which case true is
 * returned). It is mainly useful if is unclear what the smallest
 * possible value would be.
 */
template <typename T>
class MaxCmp {

public:

  /**
   * The default constructor.
   */
  inline MaxCmp() : init(false), max(T()) {}

  /**
   * Constructor specifying an initial maximum value, \a t.
   */
  inline MaxCmp(const T & t) : init(true), max(t) {}

public:

  /**
   * If \a t is the largest value sen so far return true. Otherwise
   * return false.
   */
  bool operator()(const T & t)
  {
    if ( !init || t > max ) {
      max = t;
      init = true;
      return true;
    }
    return false;
  }

  /**
   * Return the largest value so far.
   */
  operator const T & () const { return max; }

private:

  /**
   * True if a first value has been given;
   */
  bool init;

  /**
   * The largest value seen so far.
   */
  T max;

};

}

#endif /* THEPEG_MaxCmp_H */
