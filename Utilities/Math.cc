// -*- C++ -*-

#include "Math.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Math.tcc"
#endif
double ThePEG::Math::powi(double x, int i) {
  switch ( i ) {
  case 0: return 1.0;
  case -1: return 1/x;
  case -2: return 1/x/x;
  case -3: return 1/x/x/x;
  case 1: return x;
  case 2: return x*x;
  case 3: return x*x*x;
  default: return i > 0? powi(x, i - 1)*x: powi(x, i + 1)/x;
  }
}

double ThePEG::Math::gamma(double x) {
  static const double b[8] =
  {-0.577191652, 0.988205891, -0.897056937, 0.918206857,
   -0.756704078, 0.482199394, -0.193527818, 0.035868343};
  const long nx = long(x);
  const double dx = x - double(nx);
  double res = 1.0;
  double dxp = 1.0;
  for ( int i = 0; i < 8; ++i ) {
    dxp*=dx;
    res += b[i]*dxp;
  }
  if ( x < 0.0 ) {
    res /= x;
  } else {
    for ( long ix = 1; ix < nx; ++ix ) res *= x - double(ix);
  }
  return res;
}

double ThePEG::Math::lngamma(double x) {

#ifndef ThePEG_HAS_LGAMMA

  static const double b[6]={76.18009173, -86.50532033, 24.01409822,
			    -1.231739516, 0.120858003e-2, -0.536382e-5};
  x -= 1.0;
  double t = x + 5.5;
  t -= (x + 0.5)*log(t);
  double sum = 1.0;
  for (int j = 0; j < 6; j++) {
    x += 1.0;
    sum += b[j]/x;
  }
  return -t + log(2.50662827465*sum);

#else

  return lgamma(x);

#endif

}

