// -*- C++ -*-
#ifndef ThePEG_Integrator_H
#define ThePEG_Integrator_H
//
// This is the declaration of the <!id>Integrator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Integrator<!!id> calculates an approximate integral of any
// reasonable function of one variable over a simple interval. It is
// also possible to sample the function within this interval, in which
// case a rejection weight is provided to be able to get a correctly
// distributed sample and an correct Monte Carlo estimate of the
// integral.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Selector.html">Selector.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Selector.h"
// #include "Integrator.fh"
// #include "Integrator.xh"

namespace ThePEG {

template <typename FncT, typename RetT = double,
          typename ValT = double, typename ArgT = double>
class Integrator {

public:

  typedef pair<ArgT,ValT> IBin;
  typedef list<IBin> BinList;
  typedef BinList::iterator Bin;
  typedef BinList::const_iterator CBin;
  typedef Selector<CBin> SelT;
  typedef set<ArgT> PeakSet;

public:

  Integrator(const FncT & fncin, ArgT minin, ArgT maxin,
	     double weightminin = 0.999, double weightmaxin = 1.001);
  // The standard ctor.

  template <typename Iterator>
  Integrator(const FncT & fncin, ArgT minin, ArgT maxin,
	     double weightmin, double weightmax,
	     Iterator peak0in, Iterator peaknin);
  // Ctor with information about possible peaks.

  inline RetT integral() const;
  // Return the approximation of the integral.

  ArgT generate(double rnd, double & weight) const;
  // Generate a value according to the given function giving weight
  // corresponding to the overestimation used in the numerical
  // integration for this point.

  inline const FncT & function() const;
  // Return a reference to the function used.

protected:

  void init(const PeakSet & peaks);
  // Initialize.

  void checksplit(Bin lo, Bin up);
  // Split the upper bin in into two recursively until the
  // approximation x^beta agrees with the actual function value
  // withing the limits specified by the min/max weights.

  inline ArgT generate(CBin lo, CBin up, double rnd) const;
  // Generate a value in the u bin according to the x^beta
  // approximation.

  inline RetT integrate(Bin lo, Bin up) const;
  // perform the integration of the approximate x^beta in the u bin.

private:

  const FncT & fnc;
  ArgT xmin;
  ArgT xmax;
  double wmin;
  double wmax;
  BinList bins;
  SelT selector;

private:

  Integrator();
  Integrator(const Integrator &);
  const Integrator & operator=(const Integrator &);

};

}

#include "Integrator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Integrator.tcc"
#endif

#endif /* ThePEG_Integrator_H */
