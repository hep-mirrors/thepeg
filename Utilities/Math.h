// -*- C++ -*-
#ifndef ThePEG_Math_H
#define ThePEG_Math_H

#include <cmath>

// #include "Math.fh"
// #include "Math.xh"

namespace ThePEG {

/** The Math namespace includes the declaration of some useful
 *  mathematical functions. */
namespace Math {

/**
 * MathType is an empty non-polymorphic base class for all
 * mathematical function types.
 */
struct MathType {};

/** The gamma function */
double gamma(double);

/** The log of the gamma function */
double lngamma(double);

/** Return \f$1-e^x\f$, with highest possible precision for
 *  \f$x\rightarrow 0\f$. */
inline double exp1m(double x);

/** Return \f$1\log(1-x)\f$, with highest possible precision for
 *  \f$x\rightarrow 0\f$. */
inline double log1m(double);

/** Return x rased to the integer power p, using recursion. */
inline double powi(double x, int p);

/** Return the integral of \f$x^p dx\f$ between xl and xu. */
inline double pIntegrate(double p, double xl, double xu);

/** Return the integral of \f$x^p dx\f$ between xl and xu. */
inline double pIntegrate(int p, double xl, double xu);

/** Return the integral of \f$x^{e-1} dx\f$ between xl and xl+dx with
 *  highest possible precision for \f$dx\rightarrow 0\f$ and/or
 *  \f$e\rightarrow 0\f$. */
inline double pXIntegrate(double e, double xl, double dx);

/** Generate an x between xl and xu distributed as \f$x^p\f$. */
inline double pGenerate(double p, double xl, double xu, double rnd);

/** Generate an x between xl and xu distributed as \f$x^p\f$. */
inline double pGenerate(int p, double xl, double xu, double rnd);

/** Generate an x between xl and xl + dx distributed as \f$x^{e-1}\f$
 *  with highest possible precision for\f$dx\rightarrow 0\f$ and/or *
 *  \f$e\rightarrow 0\f$.
 * @param e the parameter defining the power in \f$x^{e-1}\f$.
 * @param xl the lower bound of the generation interval.
 * @param xu the upper bound of the generation interval.
 * @param rnd a flat random number in the interval ]0,1[. */
inline double pXGenerate(double e, double xl, double xu, double rnd);

/** Returns (x - y)/(|x| + |y|). */
template <typename FloatType>
inline double relativeError(FloatType x, FloatType y);

/** Return x if |x|<|y|, else return y. */
template <typename T>
inline T absmin(const T & x, const T & y);

/** Return x if |x|>|y|, else return y. */
template <typename T>
inline T absmax(const T & x, const T & y);

/** Templated helper class for calculating integer powers. */
template <int N, bool Inv>
struct Power: public MathType {
  /** The actual function. */
  inline static double pow(double x);
};

/** Templated function to calculate integer powers known at
 *  compile-time. */
template <int N>
inline double Pow(double x) { return Power<N, N < 0>::pow(x); }

/** This namespace introduces some useful function classes with known
 *  primitive and inverse primitive functions. Useful to sample
 *  corresponding distributions.*/
namespace Functions {

/** Class corresponding to functions of the form \f$x^N\f$ with integer N. */
template <int N>
struct PowX: public MathType {

  /** The primitive function. */
  inline static double primitive(double x);

  /** Integrate function in a given interval. */
  inline static double integrate(double x0, double x1);

  /** Sample a distribution in a given interval given a flat random
   *  number R in the interval ]0,1[. */
  inline static double generate(double x0, double x1, double R);

};

/** Class corresponding to functions of the form \f$(1-x)^N\f$
 *  with integer N. */
template <int N>
struct Pow1mX: public MathType {

  /** The primitive function. */
  inline static double primitive(double x);

  /** Integrate function in a given interval. */
  inline static double integrate(double x0, double x1);

  /** Sample a distribution in a given interval given a flat random
   *  number R in the interval ]0,1[. */
  inline static double generate(double x0, double x1, double R);

};

/** Class corresponding to functions of the form \f$1/(x(1-x))\f$ */
struct InvX1mX: public MathType {

  /** The primitive function. */
  inline static double primitive(double x);

  /** Integrate function in a given interval. */
  inline static double integrate(double x0, double x1);

  /** Sample a distribution in a given interval given a flat random
   *  number R in the interval ]0,1[. */
  inline static double generate(double x0, double x1, double R);

};

/** Class corresponding to functions of the form \f$e^x\f$ */
struct ExpX: public MathType {

  /** The primitive function. */
  inline static double primitive(double x);

  /** Integrate function in a given interval. */
  inline static double integrate(double x0, double x1);

  /** Sample a distribution in a given interval given a flat random
   *  number R in the interval ]0,1[. */
  inline static double generate(double x0, double x1, double R);

};  

/** Class corresponding to functions of the form \f$x^{N/D}\f$
 *  with integer N and D. */
template <int N, int D>
struct FracPowX: public MathType {

  /** The primitive function. */
  inline static double primitive(double x);

  /** Integrate function in a given interval. */
  inline static double integrate(double x0, double x1);

  /** Sample a distribution in a given interval given a flat random
   *  number R in the interval ]0,1[. */
  inline static double generate(double x0, double x1, double R);

};

}

}

}

#include "Math.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Math.tcc"
#endif

#endif /* ThePEG_Math_H */
