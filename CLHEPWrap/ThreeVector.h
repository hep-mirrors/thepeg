// -*- C++ -*-
#ifndef ThePEG_ThreeVector_H
#define ThePEG_ThreeVector_H

/** @file ThreeVector.h is a wrapper around the header file of the
 *  <code>Hep3Vector</code> class in CLHEP. The class is aliased as
 *  CLHEP::Vector3 and made available in the ThePEG namespace. */

#include "ThreeVector.fh"
#include "ThePEG/Utilities/UnitIO.h"

namespace ThePEG {

/** Output a Vector3 with units to a stream. */
template <typename OStream, typename UT>
void ounitstream(OStream & os, const Vector3 & p, UT & u) {
  os << ounit(p.x(), u) << ounit(p.y(), u) << ounit(p.z(), u);
}

/** Input a Vector3 with units from a stream. */
template <typename IStream, typename UT>
void iunitstream(IStream & is, Vector3 & p, UT & u) {
  double x, y, z;
  is >> iunit(x, u) >> iunit(y, u) >> iunit(z, u);
  p = Vector3(x, y, z);
}

}

#endif /* ThePEG_ThreeVector_H */
