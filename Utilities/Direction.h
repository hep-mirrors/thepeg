// -*- C++ -*-
#ifndef ThePEG_Direction_H
#define ThePEG_Direction_H
//
// This is the declaration of the <!id>Direction<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// A <!id>Direction<!!id> object can be used to specify that some
// following operations should be assumed to be performed with the
// z-direction of the momenta reversed. As an example, if
// <!id>Direction<0>::pos()<!!id> is true, the method
// <!id>Lorentz5Momentum::dirPlus()<!!id> will return the positive,
// light-cone component, and <!id>Lorentz5Momentum::dirMinus()<!!id>
// the negativewhile, while if <!id>Direction<0>::pos()<!!id> is false
// the behavior of the methods are reversed.
//
// <!id>Direction<!!id> is templated with an integer template argument
// (default = 0), and only one object per class can be instatiated at
// the time. Attempts to instatiate a second object of a
// <!id>Direction<!!id> class will result in an exception being
// thrown. To have several different directions classes with different
// template arguments must be instantiated. <!id>Direction<0><!!id> is
// reserved for <!id>Lorentz5Momentum<!!id>. Attempts to use the
// static methods of a <!id>Direction<!!id> class when no object has
// been instatiated will result in an exception being thrown.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Lorentz5Momentum.html">Lorentz5Momentum.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "Direction.fh"
#include "Direction.xh"

namespace ThePEG {

template <int I>
class Direction {

public:

  enum Dir { Neg = -1, Negative = -1, Undefined = 0, Pos = 1, Positive = 1 };

public:

  inline Direction(Dir newDirection)
    throw(MultipleDirectionException, UndefinedDirectionException);
  // Create an object with a given direction.

  inline Direction(double rnd) throw(MultipleDirectionException);
  // Create an object with a positive direction if rnd > 0.5,
  // otherwise set the negative direction.

  inline Direction(bool p) throw(MultipleDirectionException);
  // Create an object with a positive direction if p is true,
  // otherwise set the negative direction.

  inline ~Direction();
  // Destructure makeing the static variable undefined.

public:

  inline static void set(Dir newDirection) throw(UndefinedDirectionException);
  // Set the direction.

  inline static void reverse() throw(UndefinedDirectionException);
  // Reverse the direction.

  inline static bool pos() throw(UndefinedDirectionException);
  // Return true if the direction is positive.

  inline static bool neg() throw(UndefinedDirectionException);
  // Return true if the direction is negative.

  inline static Dir dir() throw(UndefinedDirectionException);
  // Return the direction.

private:

  static Dir theDirection;
  // The direction.

private:

  Direction();
  Direction(const Direction &);
  Direction & operator=(const Direction &);
  // Default ctors and assignment is private and not implemented.

};

}

#include "Direction.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Direction.tcc"
#endif

#endif /* ThePEG_Direction_H */
