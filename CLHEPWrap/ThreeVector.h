// -*- C++ -*-
#ifndef ThePEG_ThreeVector_H
#define ThePEG_ThreeVector_H

// Wrapper around the header file of the <!id>HepThreeVector<!!id>
// class in CLHEP. The class is aliased as <!id>CLHEP::Vector3<!!id>
// and made available in the <!id>ThePEG<!!id> namespace.

#include "ThreeVector.fh"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

template <typename OStream, typename UT>
void ounitstream(OStream & os, const Vector3 & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u);
}

template <typename IStream, typename UT>
void iunitstream(IStream & is, Vector3 & p, UT & u) {
  double x, y, z;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u);
  p = Vector3(x, y, z);
}

}

#endif /* ThePEG_ThreeVector_H */
