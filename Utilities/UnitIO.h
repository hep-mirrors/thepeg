// -*- C++ -*-
#ifndef ThePEG_UnitIO_H
#define ThePEG_UnitIO_H
//
// This is the declaration of the <!id>IUnit<!!id> and
// <!id>OUnit<!!id> classes and associated templated functions..
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>IUnit<!!id> and <!id>OUnit<!!id> classes are used to
// facilitate input and output of unitful numbers from and to
// persistent streams. An Energy can hence be read and written like
// this:<BR> <!id>is &lt;&lt; iunit(x, GeV);<!!id><BR> <!id>os
// &gt;&gt; ounit(x, GeV);<!!id><BR> Also containers of unitful
// numbers may be written like this, as well as Lorentz and three
// vectors.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentOStream.html">PersistentOStream.h</a>,
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "UnitIO.fh"
// #include "UnitIO.xh"

namespace ThePEG {

template <typename T, typename UT>
struct OUnit {
  OUnit(const T & t, const UT & u): theX(t), theUnit(u) {}
  OUnit(const OUnit<T,UT> & iu): theX(iu.theX), theUnit(iu.theUnit) {}
  const T & theX;
  const UT & theUnit;
};

template <typename T, typename UT>
struct IUnit {
  IUnit(T & t, const UT & u): theX(t), theUnit(u) {}
  IUnit(const IUnit<T,UT> & iu): theX(iu.theX), theUnit(iu.theUnit) {}
  T & theX;
  const UT & theUnit;
};

template <typename T, typename UT>
inline OUnit<T,UT> ounit(const T & t, const UT & ut) {
  return OUnit<T,UT>(t, ut);
}

template <typename T, typename UT>
inline IUnit<T,UT> iunit(T & t, const UT & ut) {
  return IUnit<T,UT>(t, ut);
}

template <typename OStream, typename T, typename UT>
void ounitstream(OStream & os, const T & t, UT & u) {
  os << t/u;
}

template <typename IStream, typename T, typename UT>
void iunitstream(IStream & is, T & t, UT & u) {
  double d;
  is >> d;
  t = d*u;;
}

template <typename OStream, typename T, typename UT>
OStream & operator<<(OStream & os, const OUnit<T,UT> & u) {
  ounitstream(os, u.theX, u.theUnit);
  return os;
}

template <typename IStream, typename T, typename UT>
IStream & operator>>(IStream & is, const IUnit<T,UT> & u) {
  iunitstream(is, u.theX, u.theUnit);
  return is;
}

}

#endif /* ThePEG_UnitIO_H */
