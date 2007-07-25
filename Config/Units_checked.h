// -*- C++ -*-
#ifndef ThePEG_Units_H
#define ThePEG_Units_H

#include "ThePEG/Vectors/Lorentz5Vector.fh"
#include "ThePEG/Vectors/LorentzVector.fh"
#include "ThePEG/Vectors/ThreeVector.fh"
#include "ThePEG/Vectors/Transverse.fh"
#include "PhysicalQty.h"
#include "PhysicalQtyOps.h"
#include "PhysicalQtyComplex.h"

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
typedef Qty<0,1,0> Energy;

/** Mass has the same unit as Energy <=> c == 1 */
typedef Energy Mass;

/** Length. */
typedef Qty<1,0,0> Length;

/** Time has the same unit as Length. <=> c == 1*/
typedef Length Time;

/** Inverse Length. */
typedef Qty<-1,0,0> InvLength;

/** Velocities are dimensionless fractions of c */
typedef double Velocity;

/** Charge. */
typedef Qty<0,0,1> Charge;

/** Angular momentum. */
typedef Qty<1,1,0> AngularMomentum;

/** Tension */
typedef Qty<-1,1,0> Tension;

/** Area will be assumed to be Length\f$^2\f$. */
typedef Qty<2,0,0> Area;

/** Inverse Area */
typedef Qty<-2,0,0> InvArea;

/** Cross section is an area. */
typedef Area CrossSection;

/** Energy\f$^2\f$. */
typedef Qty<0,2,0> Energy2;
typedef Qty<0,3,0> Energy3;

/** Energy\f$^4\f$. */
typedef Qty<0,4,0> Energy4;
typedef Qty<0,5,0> Energy5;
typedef Qty<0,6,0> Energy6;
typedef Qty<0,7,0> Energy7;
typedef Qty<0,8,0> Energy8;
typedef Qty<0,9,0> Energy9;
typedef Qty<0,10,0> Energy10;
typedef Qty<0,11,0> Energy11;
typedef Qty<0,12,0> Energy12;

typedef Qty<0,1,0,1,2,1> SqrtEnergy;
typedef Qty<0,-1,0,1,2,1> InvSqrtEnergy;

/** CrossSection*Energy2. */
typedef Qty<2,2,0> Energy2XSec;
/** CrossSection/Energy2. */
typedef Qty<2,-2,0> DiffXSec;

/** CrossSection/Energy2/Energy2. */
typedef Qty<2,-4,0> Diff2XSec;

/** CrossSection/Energy2/Energy2/Energy2 */
typedef Qty<2,-6,0> Diff3XSec;

/** 1/Energy. */
typedef Qty<0,-1,0> InvEnergy;

/** 1/Energy<sup>2</sup>. */
typedef Qty<0,-2,0> InvEnergy2;
typedef Qty<0,-3,0> InvEnergy3;

/** 1/Energy<sup>4</sup>. */
typedef Qty<0,-4,0> InvEnergy4;
typedef Qty<0,-5,0> InvEnergy5;
typedef Qty<0,-6,0> InvEnergy6;
typedef Qty<0,-7,0> InvEnergy7;
typedef Qty<0,-8,0> InvEnergy8;
typedef Qty<0,-9,0> InvEnergy9;
typedef Qty<0,-10,0> InvEnergy10;
typedef Qty<0,-11,0> InvEnergy11;
typedef Qty<0,-12,0> InvEnergy12;

/** Scale is the same as a squared energy. */
typedef Energy2 Scale;

/** A point in normal three-dimensional space. */
typedef Vector3<Length> Point;

/** A distance in normal three-dimensional space. */
typedef Vector3<Length> Distance;

/** A direction in normal three-dimensional space. */
typedef Vector3<double> Axis;

/** A momentum in normal three-dimensional space. */
typedef Vector3<Energy> Momentum3;

/** A three-dimensional boost vector. */
typedef Vector3<double> Boost;

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


const Length millimeter = Length::baseunit();
const Energy MeV = Energy::baseunit();
const Charge eplus = Charge::baseunit();

const Energy keV = 1.0e-3 * MeV;
const Energy GeV = 1.0e3  * MeV;
const Energy TeV = 1.0e6  * MeV;

const Energy2 MeV2 = MeV * MeV;
const Energy2 GeV2 = GeV * GeV;
const InvEnergy InvGeV = 1/GeV;

const Length meter = 1.0e3 * millimeter;
const Length mm = millimeter;
const Length micrometer = 1.0e-3  * millimeter;
const Length nanometer  = 1.0e-6  * millimeter;
const Length picometer  = 1.0e-9  * millimeter;
const Length femtometer = 1.0e-12 * millimeter;
 
const Area picobarn  = 1.0e-40 * meter * meter;
const Area nanobarn  = 1.0e3  * picobarn;
const Area microbarn = 1.0e6  * picobarn;
const Area millibarn = 1.0e9  * picobarn;
const Area barn      = 1.0e12 * picobarn; 
const Area femtobarn = 1.0e-3 * picobarn;

// PDG 2006 value 197.326968(17) MeV fm
const Qty<1,1,0> hbarc = 197.326968e-15 * MeV * meter;
const Qty<1,1,0> hbar_Planck = hbarc / 1.0;

}

// Used for temporary removal of unit checking in Herwig Helicity code
namespace UnitRemoval {
  const Units::Energy E = Units::MeV;

  const Units::Energy2 E2 = sqr(E);
  const Units::Energy3 E3 = E*E2;
  const Units::Energy4 E4 = E2*E2;
  const Units::InvEnergy InvE = 1.0/E;
  const Units::InvEnergy2 InvE2 = 1.0/E2;
  const Units::InvEnergy3 InvE3 = 1.0/E3;
  const Units::InvEnergy4 InvE4 = 1.0/E4;

  const Units::SqrtEnergy SqrtE = sqrt(E);
  const Units::InvSqrtEnergy InvSqrtE = 1.0/sqrt(E);
}

}

#endif /* ThePEG_Units_H */
