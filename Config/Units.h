// -*- C++ -*-
#ifndef ThePEG_Units_H
#define ThePEG_Units_H

#include "ThePEG/CLHEPWrap/Lorentz5Vector.fh"
#include "ThePEG/CLHEPWrap/LorentzVector.fh"
#include "ThePEG/CLHEPWrap/ThreeVector.fh"
#include "ThePEG/CLHEPWrap/Transverse.fh"
#include "ThePEG/CLHEPWrap/SystemOfUnits.h"
#include "ThePEG/Utilities/UnitIO.h"
#include <vector>

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

using namespace CLHEP;

/** Mass will everywhere be assumed to bave the same unit as Energy. */
typedef double Mass;

/** Energy. */
typedef double Energy;

/** Time will everywhere be assumed to bave the same unit as Length. */
typedef double Time;

/** Length. */
typedef double Length;

/** Charge. */
typedef double Charge;

/** Angular momentum. */
typedef double AngularMomentum;

/** Area will be assumed to be Length\f$^2\f$. */
typedef double Area;

/** Cross section is an area. */
typedef Area CrossSection;

/** Energy\f$^2\f$. */
typedef double Energy2;

/** Energy\f$^4\f$. */
typedef double Energy4;

/** CrossSection*Energy2. */
typedef double Energy2XSec;
/** CrossSection/Energy2. */
typedef double DiffXSec;

/** CrossSection/Energy2/Energy2. */
typedef double Diff2XSec;

/** CrossSection/Energy2/Energy2/Energy2 */
typedef double Diff3XSec;

/** 1/Energy2 */
typedef double InvEnergy2;

/** 1/Energy */
typedef double InvEnergy;

/** Scale is the same as a squared energy. */
typedef Energy2 Scale;

/** A point in normal three-dimensional space. */
typedef Vector3 Point;

/** A distance in normal three-dimensional space. */
typedef Vector3 Distance;

/** A momentum in normal three-dimensional space. */
typedef Vector3 Momentum3;

/** A distance in four-dimensional space-time. */
typedef LorentzVector LorentzDistance;

/** A distance in four-dimensional space-time with an explicit
 *  invariant time component. */
typedef Lorentz5Vector<Length> Lorentz5Distance;

/** A point in four-dimensional space-time. */
typedef LorentzVector LorentzPoint;

/** A momentum in four-dimensional space-time. */
typedef LorentzVector LorentzMomentum;

/** A momentum in four-dimensional space-time with an explicit
 *  invariant mass component. */
typedef Lorentz5Vector<Energy> Lorentz5Momentum;

/** Transverse components of a momentum. */
typedef Transverse<Energy> TransverseMomentum;

/** A useful unit for squared energy (scale) */
static const Energy2 GeV2 = GeV*GeV;

}


/**
 * A traits class to be used for defining return types for
 * templated functions involving multiplication.
 */
template <typename T>
struct MultiplicationTraits {
  typedef T ResultType;
};

/** Specialization of MultiplicationTraits for Lorentz5Vector. */
template <typename T>
struct MultiplicationTraits< Lorentz5Vector<T> > {
  typedef T ResultType;
};

/** Specialization of MultiplicationTraits for LorentzVector. */
template <>
struct MultiplicationTraits< LorentzVector > {
  typedef double ResultType;
};

/** Specialization of MultiplicationTraits for Vector3. */
template <>
struct MultiplicationTraits< Vector3 > {
  typedef double ResultType;
};

}

#endif /* ThePEG_Units_H */
