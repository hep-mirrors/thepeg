// -*- C++ -*-
#ifndef ThePEG_Direction_H
#define ThePEG_Direction_H
// This is the declaration of the Direction class.

#include "ThePEG/Config/ThePEG.h"
// #include "Direction.fh"
#include "Direction.xh"

namespace ThePEG {

template <int I>
/**
 * A <code>Direction</code> object can be used to specify that some
 * following operations should be assumed to be performed with the
 * z-direction of the momenta reversed. As an example, if
 * <code>Direction<0>::pos()</code> is true, the method
 * <code>Lorentz5Momentum::dirPlus()</code> will return the positive,
 * light-cone component, and <code>Lorentz5Momentum::dirMinus()</code>
 * the negative, while if <code>Direction<0>::pos()</code> is false
 * the behavior of the methods are reversed.
 *
 * <code>Direction</code> is templated with an integer template argument
 * (default = 0), and only one object per class can be instatiated at
 * the time. Attempts to instatiate a second object of a
 * <code>Direction</code> class will result in an exception being
 * thrown. To have several different directions classes with different
 * template arguments must be instantiated. <code>Direction<0></code> is
 * reserved for <code>Lorentz5Momentum</code>. Attempts to use the
 * static methods of a <code>Direction</code> class when no object has
 * been instatiated will result in an exception being thrown.
 *
 * @see Lorentz5Momentum.
 */
class Direction {

public:

  /** The enum defining the directions. */
  enum Dir { /** Reversed direction. */ Neg = -1,
	     /** Reversed direction. */ Negative = -1,
	     /** No direction has been defined. */ Undefined = 0,
	     /** Standard (positive) direction. */ Pos = 1,
	     /** Standard (positive) direction. */ Positive = 1
  };

public:

  /**
   * Create an object with a given direction.
   */
  inline Direction(Dir newDirection)
    throw(MultipleDirectionException, UndefinedDirectionException);

  /**
   * Create an object with a positive direction if rnd > 0.5,
   * otherwise set the negative direction.
   */
  inline Direction(double rnd) throw(MultipleDirectionException);

  /**
   * Create an object with a positive direction if p is true,
   * otherwise set the negative direction.
   */
  inline Direction(bool p) throw(MultipleDirectionException);

  /**
   * Destructure makeing the static variable undefined.
   */
  inline ~Direction();

public:

  /**
   * Set the direction.
   */
  inline static void set(Dir newDirection) throw(UndefinedDirectionException);

  /**
   * Reverse the direction.
   */
  inline static void reverse() throw(UndefinedDirectionException);

  /**
   * Return true if the direction is positive.
   */
  inline static bool pos() throw(UndefinedDirectionException);

  /**
   * Return true if the direction is negative (reversed).
   */
  inline static bool neg() throw(UndefinedDirectionException);

  /**
   * Return the direction.
   */
  inline static Dir dir() throw(UndefinedDirectionException);

private:

  /**
   * The direction.
   */
  static Dir theDirection;

private:

  /**
   * Default ctors and assignment is private and not implemented.
   */
  Direction();
  /**
   * Default ctors and assignment is private and not implemented.
   */
  Direction(const Direction &);
  /**
   * Default ctors and assignment is private and not implemented.
   */
  Direction & operator=(const Direction &);

};

}

#include "Direction.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Direction.tcc"
#endif

#endif /* ThePEG_Direction_H */
