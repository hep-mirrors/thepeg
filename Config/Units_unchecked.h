// -*- C++ -*-
#ifndef ThePEG_Units_H
#define ThePEG_Units_H

#include "ThePEG/Vectors/Lorentz5Vector.fh"
#include "ThePEG/Vectors/LorentzVector.fh"
#include "ThePEG/Vectors/ThreeVector.fh"
#include "ThePEG/Vectors/Transverse.fh"
#include <cmath>

namespace ThePEG {

// pow<P,R>(double) --- required for consistency
template<int P, int R>
double pow(double q) {
  return std::pow(q,double(P)/double(R));
}

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

/** Mass will everywhere be assumed to bave the same unit as Energy. */
typedef double Energy;

/** Energy. */
typedef Energy Mass;

/** Time will everywhere be assumed to bave the same unit as Length. */
typedef double Length;

/** Length. */
typedef Length Time;

typedef double Velocity;

/** Charge. */
typedef double Charge;

/** Angular momentum. */
typedef double AngularMomentum;

/** Tension */
typedef double Tension;

/** Area will be assumed to be Length\f$^2\f$. */
typedef double Area;

/** Cross section is an area. */
typedef Area CrossSection;

/** Energy\f$^2\f$. */
typedef double Energy2;
typedef double Energy3;

/** Energy\f$^4\f$. */
typedef double Energy4;
typedef double Energy5;
typedef double Energy6;
typedef double Energy7;
typedef double Energy8;
typedef double Energy9;
typedef double Energy10;
typedef double Energy11;
typedef double Energy12;

typedef double SqrtEnergy;
typedef double InvSqrtEnergy;

/** CrossSection*Energy2. */
typedef double Energy2XSec;
/** CrossSection/Energy2. */
typedef double DiffXSec;

/** CrossSection/Energy2/Energy2. */
typedef double Diff2XSec;

/** CrossSection/Energy2/Energy2/Energy2 */
typedef double Diff3XSec;

/** 1/Energy. */
typedef double InvEnergy;

/** 1/Energy<sup>2</sup>. */
typedef double InvEnergy2;
typedef double InvEnergy3;

/** 1/Energy<sup>4</sup>. */
typedef double InvEnergy4;
typedef double InvEnergy5;
typedef double InvEnergy6;
typedef double InvEnergy7;
typedef double InvEnergy8;
typedef double InvEnergy9;
typedef double InvEnergy10;
typedef double InvEnergy11;
typedef double InvEnergy12;

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

const Energy MeV = 1.0;
const Energy2 MeV2 = MeV * MeV;

const Energy GeV = 1.0e3 * MeV;
const Energy2 GeV2 = GeV * GeV;

const InvEnergy InvGeV = 1/GeV;

const Charge eplus = 1.0;

const Length mm = 1.0;
const Length meter = 1.0e3 * mm;

const Area picobarn = 1.0e-40 * meter * meter;
const Area nanobarn = 1.0e3 * picobarn;

// PDG 2006 value 197.326968(17) MeV fm
const double hbarc = 197.326968e-15 * MeV * meter;
const double hbar_Planck = hbarc / 1.0;

}

// Used for temporary removal of unit checking in Herwig Helicity code
namespace UnitRemoval {
  const Units::Energy E = Units::MeV;

  const Units::Energy2 E2 = E*E;
  const Units::Energy3 E3 = E*E2;
  const Units::Energy4 E4 = E2*E2;
  const Units::InvEnergy InvE = 1.0/E;
  const Units::InvEnergy2 InvE2 = 1.0/E2;
  const Units::InvEnergy3 InvE3 = 1.0/E3;
  const Units::InvEnergy4 InvE4 = 1.0/E4;

  const Units::SqrtEnergy SqrtE = std::sqrt(E);
  const Units::InvSqrtEnergy InvSqrtE = 1.0/std::sqrt(E);
}

}

#endif /* ThePEG_Units_H */
