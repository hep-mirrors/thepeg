// -*- C++ -*-
#ifndef ThePEG_UseRandom_H
#define ThePEG_UseRandom_H
//
// This is the declaration of the <!id>UseRandom<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This <!id>UseRandom<!!id> class keeps a static stack of
// <!class>RandomGenerator<!!class> which can be used anywhere by any
// class. When an <!class>EventGenerator<!!class> is initialized or
// run it adds a <!class>RandomGenerator<!!class> object to the stack
// which can be used by any other object being initialized or run
// through the static functions of the <!id>UseRandom<!!id> class. If
// someone needs to use an alternative
// <!class>RandomGenerator<!!class> object a new <!id>UseRandom<!!id>
// object can be constructed with a pointer to the desired
// <!class>RandomGenerator<!!class> objectas argument and that object
// will the be used by the static <!id>UseRandom<!!id> functions until
// the <!id>UseRandom<!!id> is destructed.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RandomGenerator.html">RandomGenerator.h</a>,
// <a href="http:EventGenerator.html">EventGenerator.h</a>.
// 

#include "ThePEG/Repository/RandomGenerator.h"
// #include "UseRandom.fh"
// #include "UseRandom.xh"

namespace ThePEG {

class UseRandom {

public:

  inline UseRandom();
  inline UseRandom(const UseRandom &);
  // Standard constructors do nothing.

  inline UseRandom(const RanGenPtr & r);
  // Construct a new object specifying a new RandomGenerator to be
  // used during this objects lifetime

  inline ~UseRandom();
  // The destructor removing the RandomGenerator specified in the
  // constructor from the stack.

public:

  inline static RandomGenerator & current();
  // Return a reference to the currently chosen RandomGenerator object.

  inline static double rnd();
  inline static double rnd(double xu);
  inline static double rnd(double xl, double xu);
  // Return a simple flat random number (from the current
  // RandomGenerator object) in the range ]0,1[, ]0,xu[ and ]xl,xu[
  // respectively.
  
  inline static bool rndbool();
  // Return 50/50 (from the current RandomGenerator object).

  inline static bool rndbool(double p);
  // Return a true with probability p (from the current
  // RandomGenerator object).

  inline static bool rndbool(double p1, double p2);
  // Return a true with probability p1/(p1+p2) (from the current
  // RandomGenerator object).

  inline static int rndsign(double p1, double p2, double p2);
  // Return -1, 0, or 1 with relative probabilities p1, p2, p3 (from
  // the current RandomGenerator object).

  inline static int rnd2(double p0, double p1);
  inline static int rnd3(double p0, double p1, double p2);
  inline static int rnd4(double p0, double p1, double p2, double p3);
  // Return a i with probability p_i/sum(p_i) (from the current
  // RandomGenerator object).

  inline static long irnd(long xu = 2);
  inline static long irnd(long xl, long xu);
  // Return a simple flat random integrer number in the range [0,xu[
  // and [xl,xu[ respectively (from the current RandomGenerator
  // object).
  

private:

  static vector<RanGenPtr> theRandomStack;
  // The stack of RandomGenerators requested.

  bool randomPushed;
  // True if this object is responsible for pushing a RandomGenerator
  // onto the stack.

private:

  UseRandom & operator=(const UseRandom &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

#include "UseRandom.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "UseRandom.tcc"
#endif

#endif /* ThePEG_UseRandom_H */
