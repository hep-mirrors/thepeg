// -*- C++ -*-
#ifndef ThePEG_Math_H
#define ThePEG_Math_H

#include <cmath>

// #include "Math.fh"
// #include "Math.xh"

namespace ThePEG {

namespace Math {

double gamma(double);
double lngamma(double);
// The (log of the) gamma function.

inline double exp1m(double x);
// 1-exp(x), with highest possible precision for x->0.

inline double log1m(double);
// log(1-x), with highest possible precision for x->0.

inline double powi(double x, int p);
// Return x rased to the integer power p, using recursion.

inline double pIntegrate(double p, double xl, double xu);
inline double pIntegrate(int p, double xl, double xu);
// Return the integral of x^p dx between xl and xu.

inline double pXIntegrate(double e, double xl, double dx);
// Return the integral of x^(e-1) dx between xl and xl+dx with highest
// possible precision for dx->0 and/or e->0.

inline double pGenerate(double p, double xl, double xu, double rnd);
inline double pGenerate(int p, double xl, double xu, double rnd);
// Generate an x between xl and xu distributed as x^p.

inline double pXGenerate(double e, double xl, double xu, double rnd);
// Generate an x between xl and xl + dx distributed as x^(e-1) with
// highest possible precision for dx->0 and/or e->0.

template <typename FloatType>
inline double relativeError(FloatType x, FloatType y);
// Returns (x - y)/(|x| + |y|)

template <typename T>
inline T absmin(const T & x, const T & y);
// Return x if |x|<|y|, else return y

template <typename T>
inline T absmax(const T & x, const T & y);
// Return x if |x|>|y|, else return y

template <int N, bool Inv>
struct Power {
  inline static double pow(double x);
};

template <int N>
inline double Pow(double x) { return Power<N, N < 0>::pow(x); }

namespace Functions {

template <int N>
struct PowX {
  // Distribution function on the form x^N
  inline static double primitive(double x);
  inline static double integrate(double x0, double x1);
  inline static double generate(double x0, double x1, double R);
};

template <int N>
struct Pow1mX {
  // Distribution function on the form (1-x)^N
  inline static double primitive(double x);
  inline static double integrate(double x0, double x1);
  inline static double generate(double x0, double x1, double R);
};

struct InvX1mX {
  // Distribution function on the form 1/(x(1-x))
  inline static double primitive(double x);
  inline static double integrate(double x0, double x1);
  inline static double generate(double x0, double x1, double R);
};

struct ExpX {
  // Distribution function on the form exp(x)
  inline static double primitive(double x);
  inline static double integrate(double x0, double x1);
  inline static double generate(double x0, double x1, double R);
};  

template <int N, int D>
struct FracPowX {
  // Distribution function on the form x^(N/D)
  inline static double primitive(double x);
  inline static double integrate(double x0, double x1);
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
