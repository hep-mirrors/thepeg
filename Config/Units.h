// -*- C++ -*-
#ifndef ThePEG_Units_H
#define ThePEG_Units_H

// This is the declaration of a number of classes for variables with
// dimension. Currently they are all typedefs of double, but in the
// future the SIUnits package will be used.
//
// Here is also defined helper-classes and helper functions to read
// and write variables with dimensions. As an example, to read and
// write an energy variable <!id>e<!!id> in units of GeV, use: <!id>os
// &lt;&lt; ounit(e, GeV)<!!id> and <!id>is &gt;&gt; iunit(e,
// GeV)<!!id>
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Lorentz5Vector.html">Lorentz5Vector.h</a>
// <a href="http:SystemOfUnits.html">SystemOfUnits.h</a>
// 

#include "ThePEG/CLHEPWrap/Lorentz5Vector.fh"
#include "ThePEG/CLHEPWrap/LorentzVector.fh"
#include "ThePEG/CLHEPWrap/ThreeVector.fh"
#include "ThePEG/CLHEPWrap/Transverse.fh"
#include "ThePEG/CLHEPWrap/SystemOfUnits.h"
#include "ThePEG/Utilities/UnitIO.h"
#include <vector>

namespace ThePEG {
namespace Units {

using namespace CLHEP;
  
typedef double Mass;
typedef double Energy;
typedef double Time;
typedef double Length;
typedef double Charge;
typedef double AngularMomentum;
typedef double Area;
typedef Area CrossSection;
typedef double Energy2;
typedef double Energy4;
typedef double Energy2XSec;          // CrossSection*Energy2
typedef double DiffXSec;             // CrossSection/Energy2
typedef double Diff2XSec;            // CrossSection/Energy2/Energy2
typedef double Diff3XSec;            // CrossSection/Energy2/Energy2/Energy2
typedef double InvEnergy2;           // 1/Energy2
typedef double InvEnergy;           // 1/Energy2
typedef Energy2 Scale;


typedef Vector3 Point;
typedef Vector3 Distance;
typedef Vector3 Momentum3;
typedef LorentzVector LorentzDistance;
typedef Lorentz5Vector<Length> Lorentz5Distance;
typedef LorentzVector LorentzPoint;
typedef LorentzVector LorentzMomentum;
typedef Lorentz5Vector<Energy> Lorentz5Momentum;
typedef Transverse<Energy> TransverseMomentum;

static const Energy2 GeV2 = GeV*GeV;

}


// The following should be used for defining return types for
// templated functions involving multiplication.
template <typename T>
struct MultiplicationTraits {
  typedef T ResultType;
};

template <typename T>
struct MultiplicationTraits< Lorentz5Vector<T> > {
  typedef T ResultType;
};

template <>
struct MultiplicationTraits< LorentzVector > {
  typedef double ResultType;
};

template <>
struct MultiplicationTraits< Vector3 > {
  typedef double ResultType;
};

// When including the SIUnits package more specializations should be
// added for Energy, Length, etc.

}

#endif /* ThePEG_Units_H */
