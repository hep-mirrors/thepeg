// -*- C++ -*-
//
// Unitsystem.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad, David Grellscheid
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_Units_H
#define ThePEG_Units_H

#include "ThePEG/Vectors/Lorentz5Vector.fh"
#include "ThePEG/Vectors/LorentzVector.fh"
#include "ThePEG/Vectors/ThreeVector.fh"
#include "ThePEG/Vectors/Transverse.fh"
#include "ThePEG_Qty.h"

namespace ThePEG {

/**
 * The Units namespace contains the declaration of a number of classes
 * for variables with dimension. Currently they are all typedefs of
 * double, but in the future the SIUnits package will be used.
 *
 * The file Utilities/UnitIO.h defines helper-classes and helper
 * functions to read and write variables with dimensions. As an
 * example, to read and write an energy variable <code>e</code> in
 * units of GeV, use: <code>os << ounit(e, GeV)</code> and <code>is >>
 * iunit(e, GeV)</code>
*/
namespace Units {

/** Energy. */
typedef QTY<0,1,0>::Type Energy;

/** Mass has the same unit as Energy <=> c == 1. */
typedef Energy Mass;

/** Length. */
typedef QTY<1,0,0>::Type Length;

/** Time has the same unit as Length. <=> c == 1. */
typedef Length Time;

/** Inverse Length. */
typedef QTY<-1,0,0>::Type InvLength;

/** Velocities are dimensionless fractions of c. */
typedef double Velocity;

/** Charge. */
typedef QTY<0,0,1>::Type Charge;

/** Angular momentum. */
typedef QTY<1,1,0>::Type AngularMomentum;

/** Tension. */
typedef QTY<-1,1,0>::Type Tension;

/** Area will be assumed to be Length\f$^2\f$. */
typedef QTY<2,0,0>::Type Area;

/** Inverse Area. */
typedef QTY<-2,0,0>::Type InvArea;

/** Cross section is an area. */
typedef Area CrossSection;

/**
 * @name Higher powers of energy.
 * Even higher powers can be created with similar typedefs.
 */
//@{
typedef QTY<0, 2, 0>::Type Energy2;
typedef QTY<0, 3, 0>::Type Energy3;
typedef QTY<0, 4, 0>::Type Energy4;
typedef QTY<0, 5, 0>::Type Energy5;
typedef QTY<0, 6, 0>::Type Energy6;
typedef QTY<0, 7, 0>::Type Energy7;
typedef QTY<0, 8, 0>::Type Energy8;
typedef QTY<0, 9, 0>::Type Energy9;
typedef QTY<0,10, 0>::Type Energy10;
typedef QTY<0,11, 0>::Type Energy11;
typedef QTY<0,12, 0>::Type Energy12;

typedef QTY<0, 1,0, 1,2,1>::Type SqrtEnergy;
typedef QTY<0,-1,0, 1,2,1>::Type InvSqrtEnergy;

typedef QTY<0, -1, 0>::Type InvEnergy;
typedef QTY<0, -2, 0>::Type InvEnergy2;
typedef QTY<0, -3, 0>::Type InvEnergy3;
typedef QTY<0, -4, 0>::Type InvEnergy4;
typedef QTY<0, -5, 0>::Type InvEnergy5;
typedef QTY<0, -6, 0>::Type InvEnergy6;
typedef QTY<0, -7, 0>::Type InvEnergy7;
typedef QTY<0, -8, 0>::Type InvEnergy8;
typedef QTY<0, -9, 0>::Type InvEnergy9;
typedef QTY<0,-10, 0>::Type InvEnergy10;
typedef QTY<0,-11, 0>::Type InvEnergy11;
typedef QTY<0,-12, 0>::Type InvEnergy12;
//@}

/** CrossSection*Energy2. */
typedef QTY<2,2,0>::Type Energy2XSec;

/** CrossSection/Energy2. */
typedef QTY<2,-2,0>::Type DiffXSec;

/** CrossSection/Energy4. */
typedef QTY<2,-4,0>::Type Diff2XSec;

/** CrossSection/Energy6 */
typedef QTY<2,-6,0>::Type Diff3XSec;

/** Scale is the same as a squared energy. */
typedef Energy2 Scale;

/** A point in three-dimensional euclidean space. */
typedef ThreeVector<Length> Point;

/** A distance in three-dimensional euclidean space. */
typedef ThreeVector<Length> Distance;

/** A direction in three-dimensional euclidean space. */
typedef ThreeVector<double> Axis;

/** A momentum in three-dimensional euclidean space. */
typedef ThreeVector<Energy> Momentum3;

/** A three-dimensional boost vector. */
typedef ThreeVector<double> Boost;

/** A distance in four-dimensional space-time. */
typedef LorentzVector<Length> LorentzDistance;

/** A distance in four-dimensional space-time with an explicit
 *  invariant time component. */
typedef Lorentz5Vector<Length> Lorentz5Distance;

/** A point in four-dimensional space-time. */
typedef LorentzVector<Length> LorentzPoint;

/** A momentum in four-dimensional space-time. */
typedef LorentzVector<Energy> LorentzMomentum;

/** A momentum in four-dimensional space-time with an explicit
 *  invariant mass component. */
typedef Lorentz5Vector<Energy> Lorentz5Momentum;

/** Transverse components of a momentum. */
typedef Transverse<Energy> TransverseMomentum;

/// @name Pre-defined basic units.
//@{
constexpr Length operator "" _mm( long double x ) {
	return Length{TypeTraits<Length>::baseunit, 
								static_cast<double>(x)};
}
constexpr Length operator "" _mm( unsigned long long x ) {
	return Length{TypeTraits<Length>::baseunit, 
								static_cast<double>(x)};
}

constexpr Length meter      = 1.0e+3_mm;
constexpr Length millimeter = 1_mm;
constexpr Length mm         = 1_mm;
constexpr Length centimeter = 10_mm;
constexpr Length micrometer = 1.0e-3_mm;
constexpr Length nanometer  = 1.0e-6_mm;
constexpr Length picometer  = 1.0e-9_mm;
constexpr Length femtometer = 1.0e-12_mm;
 
constexpr Energy operator "" _MeV( long double x ) {
	return Energy{TypeTraits<Energy>::baseunit, static_cast<double>(x)};
}
constexpr Energy operator "" _MeV( unsigned long long x ) {
	return Energy{TypeTraits<Energy>::baseunit, static_cast<double>(x)};
}

constexpr Energy operator "" _GeV( long double x ) {
	return Energy{1000_MeV, static_cast<double>(x)};
}
constexpr Energy operator "" _GeV( unsigned long long x ) {
	return Energy{1000_MeV, static_cast<double>(x)};
}

constexpr Energy keV = 1.0e-3_MeV;
constexpr Energy MeV = 1_MeV;
constexpr Energy GeV = 1_GeV;
constexpr Energy TeV = 1.0e+6_MeV;



constexpr Energy2 operator "" _MeV2( long double x ) {
	return Energy2{TypeTraits<Energy2>::baseunit,	static_cast<double>(x)};
}
constexpr Energy2 operator "" _MeV2( unsigned long long x ) {
	return Energy2{TypeTraits<Energy2>::baseunit,	static_cast<double>(x)};
}

constexpr Energy2 operator "" _GeV2( long double x ) {
	return Energy2{1.0e+6_MeV2, static_cast<double>(x)};
}
constexpr Energy2 operator "" _GeV2( unsigned long long x ) {
	return Energy2{1.0e+6_MeV2, static_cast<double>(x)};
}

constexpr Energy2 MeV2 = 1_MeV2;
constexpr Energy2 GeV2 = 1_GeV2;


constexpr InvEnergy InvGeV = 1/GeV;

constexpr Area picobarn  = 1.0e-40 * meter * meter;
constexpr Area nanobarn  = 1.0e3  * picobarn;
constexpr Area microbarn = 1.0e6  * picobarn;
constexpr Area millibarn = 1.0e9  * picobarn;
constexpr Area barn      = 1.0e12 * picobarn; 
constexpr Area femtobarn = 1.0e-3 * picobarn;

constexpr Charge eplus = TypeTraits<Charge>::baseunit;
//@}

/// Planck's constant times c (PDG 2006 value 197.326968(17) MeV fm)
constexpr QTY<1,1,0>::Type hbarc = 197.326968e-15 * MeV * meter;
/// Planck's constant (PDG 2006 value 197.326968(17) MeV fm)
constexpr QTY<1,1,0>::Type hbar_Planck = hbarc / 1.0; // c is one
}

/** 
 * Use symbols from this namespace to make forced breaks of unit
 * consistency explicit.
 */
namespace UnitRemoval {
  /// @name Helper units to make breaks of unit consistency explicit.
  //@{
  constexpr Units::Energy E = Units::MeV;

  constexpr Units::Energy2 E2 = E*E;
  constexpr Units::Energy3 E3 = E*E2;
  constexpr Units::Energy4 E4 = E2*E2;

  constexpr Units::InvEnergy InvE = 1.0/E;
  constexpr Units::InvEnergy2 InvE2 = 1.0/E2;
  constexpr Units::InvEnergy3 InvE3 = 1.0/E3;
  constexpr Units::InvEnergy4 InvE4 = 1.0/E4;

  constexpr Units::SqrtEnergy SqrtE 
  						= TypeTraits<Units::SqrtEnergy>::baseunit;
  constexpr Units::InvSqrtEnergy InvSqrtE 
  						= TypeTraits<Units::InvSqrtEnergy>::baseunit;
  //@}
}

}

#endif /* ThePEG_Units_H */
