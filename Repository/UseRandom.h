// -*- C++ -*-
#ifndef ThePEG_UseRandom_H
#define ThePEG_UseRandom_H
// This is the declaration of the UseRandom class.

#include "ThePEG/Repository/RandomGenerator.h"
// #include "UseRandom.fh"
// #include "UseRandom.xh"

namespace ThePEG {

/**
 * This UseRandom class keeps a static stack of RandomGenerator
 * objects which can be used anywhere by any class. When an
 * EventGenerator is initialized or run it adds a RandomGenerator
 * object to the stack which can be used by any other object being
 * initialized or run through the static functions of the UseRandom
 * class. If someone needs to use an alternative RandomGenerator
 * object a new UseRandom object can be constructed with a pointer to
 * the desired RandomGenerator object as argument and that object will
 * the be used by the static UseRandom functions until the UseRandom
 * object is destructed.
 *
 * @see RandomGenerator
 * @see EventGenerator
 * 
 */
class UseRandom {

public:

  /**
   * Default constructor does nothing.
   */
  inline UseRandom();

  /**
   * Copy-constructor does nothing.
   */
  inline UseRandom(const UseRandom &);

  /**
   * Construct a new object specifying a new RandomGenerator, \a r, to
   * be used during this objects lifetime
   */
  inline UseRandom(const RanGenPtr & r);

  /**
   * The destructor removing the RandomGenerator specified in the
   * constructor from the stack.
   */
  inline ~UseRandom();

public:

  /**
   * Return a reference to the currently chosen RandomGenerator object.
   */
  inline static RandomGenerator & current();

  /**
   * Return a pointer to the currently chosen RandomGenerator object.
   */
//  inline static RandomEngine * currentEngine();

  /**
   * Return a simple flat random number (from the current
   * RandomGenerator object) in the range ]0,1[.
   */
  inline static double rnd();

  /**
   * Return \a n simple flat random number (from the current
   * RandomGenerator object) in the range ]0,1[.
   */
  inline static RandomGenerator::RndVector rndvec(int n);

  /**
   * Return a simple flat random number (from the current
   * RandomGenerator object) in the range ]0,\a xu[.
   */
  template <typename Unit>
  inline static Unit rnd(Unit xu);

  /**
   * Return a simple flat random number (from the current
   * RandomGenerator object) in the range ]\a xl,\a xu[.
   */
  template <typename Unit>
  inline static Unit rnd(Unit xl, Unit xu);
  
  /**
   * Return a true with probability 0.5.
   */
  inline static bool rndbool();

  /**
   * Return a true with probability \a p.
   */
  inline static bool rndbool(double p);

  /**
   * Return a true with probability \a p1/(\a p1+\a p2).
   */
  inline static bool rndbool(double p1, double p2);

  /**
   * Return -1, 0, or 1 with relative probabilities \a p1, \a p2, \a
   * p3.
   */
  inline static int rndsign(double p1, double p2, double p2);

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a
   * p1).
   */
  inline static int rnd2(double p0, double p1);

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a
   * p1+\a p2).
   */
  inline static int rnd3(double p0, double p1, double p2);

  /**
   * Return an integer/ \f$i\f$ with probability p\f$i\f$(\a p0+\a
   * p1+\a p2+\a p3).
   */
  inline static int rnd4(double p0, double p1, double p2, double p3);

  /**
   * Return a simple flat random integrer number in the range [0,\a xu[.
   */
  inline static long irnd(long xu = 2);

  /**
   * Return a simple flat random integrer number in the range [\a xl,\a xu[.
   */
  inline static long irnd(long xl, long xu);
  
  /**
   * Return a number between zero and infinity, distributed according
   * to \f$e^-x\f$.
   */
  inline static double rndExp();

  /**
   * Return a number between zero and infinity, distributed according
   * to \f$e^-{x/\mu}\f$ where \f$\mu\f$ is the \a mean value.
   */
  template <typename Unit>
  inline static Unit rndExp(Unit mean);

  /**
   * Return a number distributed according to a Gaussian distribution
   * with zero mean and unit variance.
   */
  inline static double rndGauss();

  /**
   * Return a number distributed according to a Gaussian distribution
   * with a given standard deviation, \a sigma, and a given \a mean.
   */
  template <typename Unit>
  inline static Unit rndGauss(Unit sigma, Unit mean = Unit());

  /**
   * Return a positive number distributed according to a
   * non-relativistic Breit-Wigner with a given width, \a gamma, and a
   * given \a mean.
   */
  template <typename Unit>
  inline static Unit rndBW(Unit mean, Unit gamma);

  /**
   * Return a positive number distributed according to a
   * non-relativistic Breit-Wigner with a given width, \a gamma, and a
   * given \a mean. The distribution is cut-off so that the number is
   * between \a mean - \a cut and \a mean + \a cut
   */
  template <typename Unit>
  inline static Unit rndBW(Unit mean, Unit gamma, Unit cut);

  /**
   * Return a positive number distributed according to a relativistic
   * Breit-Wigner with a given width, \a gamma, and a given \a mean.
   */
  template <typename Unit>
  inline static Unit rndRelBW(Unit mean, Unit gamma);

  /**
   * Return a positive number distributed according to a relativistic
   * Breit-Wigner with a given width, \a gamma, and a given \a
   * mean. The distribution is cut-off so that the number is between
   * \a mean - \a cut and \a mean + \a cut
   */
  template <typename Unit>
  inline static Unit rndRelBW(Unit mean, Unit gamma, Unit cut);

  /**
   * Return a non-negative number generated according to a Poissonian
   * distribution with a given \a mean. Warning: the method
   * implemented is very slow for large mean and large return
   * values. For this reason the maximum return value is given by \a
   * nmax.
   */
  inline static long rndPoisson(double mean, long nmax = 10000);

private:

  /**
   * The stack of RandomGenerators requested.
   */
  static vector<RanGenPtr> theRandomStack;

  /**
   * True if this object is responsible for pushing a RandomGenerator
   * onto the stack.
   */
  bool randomPushed;

private:

  /**
   *  Private and non-existent assignment operator.
   */
  UseRandom & operator=(const UseRandom &);

};

}


#include "UseRandom.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "UseRandom.tcc"
#endif

#endif /* ThePEG_UseRandom_H */
