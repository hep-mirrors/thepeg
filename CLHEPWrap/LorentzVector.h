// -*- C++ -*-
#ifndef ThePEG_LorentzVector_H
#define ThePEG_LorentzVector_H

/** @file LorentzVector.h is a wrapper around the header file of the
 *  <code>HepLorentzVector</code> class in CLHEP. The class is aliased
 *  as CLHEP::LorentzVector and made available in the ThePEG
 *  namespace. The file also declares some functions involving
 *  Direction. */

#include "LorentzVector.fh"
#include "ThePEG/CLHEPWrap/Transverse.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

/** Return the positive light-cone component. Or negative if the
 *  current Direction<0> is reversed. */
inline double dirPlus(const LorentzVector & p) {
  return Direction<0>::pos()? p.plus(): p.minus();
}

/** Return the negative light-cone component. Or positive if the
 *  current Direction<0> is reversed. */
inline double dirMinus(const LorentzVector & p) {
  return Direction<0>::neg()? p.plus(): p.minus();
}

/** Return the component along the positive z-axis. Or the negative
 *  z-axis if the current Direction<0> is reversed. */
inline double dirZ(const LorentzVector & p) {
  return Direction<0>::dir()*p.z();
}

/** Return the polar angle wrt. the positive z-axis. Or the negative
 *  z-axis if the current Direction<0> is reversed. */
inline double dirTheta(const LorentzVector & p) {
  return Direction<0>::pos()? p.theta(): Constants::pi - p.theta();
}

/** Return the cosine of the polar angle wrt. the positive z-axis. Or
 *  the negative z-axis if the current Direction<0> is reversed. */
inline double dirCosTheta(const LorentzVector & p) {
  return Direction<0>::pos()? p.cosTheta():  -p.cosTheta();
}

/** Get the boost vector for the LorentzVector. If the current
 *  Direction<0> is reversed, so is the z-component. */
inline Vector3 dirBoostVector(const LorentzVector & p) {
  Vector3 b(p.boostVector());
  if ( Direction<0>::neg() ) b.setZ(-b.z());
  return b;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. */
template <typename FloatType>
inline LorentzVector
lightCone(FloatType plus, FloatType minus,
	  FloatType x = FloatType(), FloatType y = FloatType()) {
  LorentzVector r(x, y, 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. */
template <typename FloatType>
inline LorentzVector
lightCone(FloatType plus, FloatType minus, Transverse<FloatType> pt) {
  LorentzVector r(pt.x(), pt.y(), 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. If the current Direction<0> is reversed, so is the
 *  z-component. */
template <typename FloatType>
inline LorentzVector
lightConeDir(FloatType plus, FloatType minus,
	     FloatType x = FloatType(), FloatType y = FloatType()) {
  LorentzVector r(x, y, Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;
}

/** Create a LorentzVector giving its light-cone and transverse
 *  components. If the current Direction<0> is reversed, so is the
 *  z-component. */
template <typename FloatType>
inline LorentzVector
lightConeDir(FloatType plus, FloatType minus, Transverse<FloatType> pt) {
  LorentzVector r(pt.x(), pt.y(), Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;

}

/** Output a LorentzVector with units to a stream. */
template <typename OStream, typename UnitT>
void ounitstream(OStream & os, const LorentzVector & p, UnitT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u)
     << ounit(p.e(), u);
}

/** Input a LorentzVector with units from a stream. */
template <typename IStream, typename UnitT>
void iunitstream(IStream & is, LorentzVector & p, UnitT & u) {
  double x, y, z, e;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u) >> iunit(e, u);
  p = LorentzVector(x, y, z, e);
}

}


#endif /* ThePEG_LorentzVector_H */
