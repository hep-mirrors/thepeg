// -*- C++ -*-
#ifndef ThePEG_LorentzVector_H
#define ThePEG_LorentzVector_H

// Wrapper around the header file of the <!id>HepLorentzVector<!!id>
// class in CLHEP. The class is aliased as
// <!id>CLHEP::LorentzVector<!!id> and made available in the
// <!id>ThePEG<!!id> namespace.

#include "LorentzVector.fh"
#include "ThePEG/CLHEPWrap/Transverse.h"
#include "ThePEG/Utilities/Direction.h"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

inline double dirPlus(const LorentzVector & p) {
  return Direction<0>::pos()? p.plus(): p.minus();
}

inline double dirMinus(const LorentzVector & p) {
  return Direction<0>::neg()? p.plus(): p.minus();
}

inline double dirZ(const LorentzVector & p) {
  return Direction<0>::dir()*p.z();
}

inline double dirTheta(const LorentzVector & p) {
  return Direction<0>::pos()? p.theta(): Constants::pi - p.theta();
}

inline double dirCosTheta(const LorentzVector & p) {
  return Direction<0>::pos()? p.cosTheta():  -p.cosTheta();
}

inline Vector3 dirBoostVector(const LorentzVector & p) {
  Vector3 b(p.boostVector());
  if ( Direction<0>::neg() ) b.setZ(-b.z());
  return b;
}

template <typename FloatType>
inline LorentzVector
lightCone(FloatType plus, FloatType minus,
	  FloatType x = FloatType(), FloatType y = FloatType()) {
  LorentzVector r(x, y, 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

template <typename FloatType>
inline LorentzVector
lightCone(FloatType plus, FloatType minus, Transverse<FloatType> pt) {
  LorentzVector r(pt.x(), pt.y(), 0.5*(plus-minus), 0.5*(plus+minus));
  return r;
}

template <typename FloatType>
inline LorentzVector
lightConeDir(FloatType plus, FloatType minus,
	     FloatType x = FloatType(), FloatType y = FloatType()) {
  LorentzVector r(x, y, Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;
}

template <typename FloatType>
inline LorentzVector
lightConeDir(FloatType plus, FloatType minus, Transverse<FloatType> pt) {
  LorentzVector r(pt.x(), pt.y(), Direction<0>::dir()*0.5*(plus - minus),
		  0.5*(plus + minus));
  return r;

}

template <typename OStream, typename UT>
void ounitstream(OStream & os, const LorentzVector & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u)
     << ounit(p.e(), u);
}

template <typename IStream, typename UT>
void iunitstream(IStream & is, LorentzVector & p, UT & u) {
  double x, y, z, e;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u) >> iunit(e, u);
  p = LorentzVector(x, y, z, e);
}

}


#endif /* ThePEG_LorentzVector_H */
