// -*- C++ -*-
#ifndef ThePEG_UnitIO_H
#define ThePEG_UnitIO_H
// This is the declaration of the IUnit and OUnit classes and
// associated templated functions.

#include "ThePEG/Config/ThePEG.h"
// #include "UnitIO.fh"
// #include "UnitIO.xh"

namespace ThePEG {

/**
 * The OUnit< class is used to
 * facilitate output of unitful numbers to a
 * persistent stream. An Energy can hence be written like
 * this:<BR> <code>os
 * << ounit(x, GeV);</code><BR> Also containers of unitful
 * numbers may be written like this, as well as LorentzVector and
 * Vector3.
 *
 * @see PersistentOStream
 * @see PersistentIStream
 * 
 */
template <typename T, typename UT>
struct OUnit {

  /** Constructor given an object to be written assuming the given
   *  unit. */
  OUnit(const T & t, const UT & u): theX(t), theUnit(u) {}

  /** Copy constructor */
  OUnit(const OUnit<T,UT> & iu): theX(iu.theX), theUnit(iu.theUnit) {}

  /** Reference to the object to be written. */
  const T & theX;

  /** The unit assumed when writing the object. */
  const UT & theUnit;
};

/**
 * The IUnit class is used to facilitate input of unitful numbers from
 * and to a persistent stream. An Energy can hence be read like
 * this:<BR> <code>is >> iunit(x, GeV);</code><BR> Also containers of
 * unitful numbers may be read like this, as well as LorentzVector and
 * Vector3.
 *
 * @see PersistentOStream
 * @see PersistentIStream
 * 
 */
template <typename T, typename UT>
struct IUnit {

  /** Constructor given an object to be read assuming the given
   *  unit. */
  IUnit(T & t, const UT & u): theX(t), theUnit(u) {}

  /** Copy constructor */
  IUnit(const IUnit<T,UT> & iu): theX(iu.theX), theUnit(iu.theUnit) {}

  /** Reference to the object to be read. */
  T & theX;

  /** The unit assumed when reading the object. */
  const UT & theUnit;

};

/** Helper function creating a OUnit object given an object and a
 *  unit. */
template <typename T, typename UT>
inline OUnit<T,UT> ounit(const T & t, const UT & ut) {
  return OUnit<T,UT>(t, ut);
}

/** Helper function creating a IUnit object given an object and a
 *  unit. */
template <typename T, typename UT>
inline IUnit<T,UT> iunit(T & t, const UT & ut) {
  return IUnit<T,UT>(t, ut);
}

/** Helper function writing out an object with a given unit to an
 *  output stream. */
template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const T & t, UT & u) {
  os << t/u;
}

/** Helper function reading an object with a given unit from an
 *  input stream. */
template <typename IStream, typename T, typename UT>
void iunitstream(IStream & is, T & t, UT & u) {
  double d;
  is >> d;
  t = d*u;;
}

/** Output an OUnit object to a stream. */
template <typename OStream, typename T, typename UT>
OStream & operator<<(OStream & os, const OUnit<T,UT> & u) {
  ounitstream(os, u.theX, u.theUnit);
  return os;
}

/** Input an IUnit object from a stream. */
template <typename IStream, typename T, typename UT>
IStream & operator>>(IStream & is, const IUnit<T,UT> & u) {
  iunitstream(is, u.theX, u.theUnit);
  return is;
}

}

#endif /* ThePEG_UnitIO_H */
