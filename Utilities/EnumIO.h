// -*- C++ -*-
#ifndef ThePEG_EnumIO_H
#define ThePEG_EnumIO_H
//
// This is the declaration of the <!id>IEnum<!!id> and
// <!id>OEnum<!!id> classes and associated templated functions..
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>IEnum<!!id> and <!id>OEnum<!!id> classes are used to
// facilitate input and output of enums from and to
// persistent streams. An Enum can hence be read and written like
// this:<BR> <!id>is &lt;&lt; ienum(x);<!!id><BR> <!id>os
// &gt;&gt; oenum(x);<!!id><BR>
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentOStream.html">PersistentOStream.h</a>,
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>.
// 

// #include "ThePEG/Config/ThePEG.h"
// #include "EnumIO.fh"
// #include "EnumIO.xh"

namespace ThePEG {

template <typename T>
struct OEnum {
  OEnum(const T & t): theT(t) {}
  OEnum(const OEnum & oe): theT(oe.theT) {}
  const T & theT;
};

template <typename T>
struct IEnum {
  IEnum(T & t): theT(t) {}
  IEnum(const IEnum & ie): theT(ie.theT) {}
  T & theT;
};

template <typename T>
inline OEnum<T> oenum(const T & t) {
  return OEnum<T>(t);
}

template <typename T>
inline IEnum<T> ienum(T & t) {
  return IEnum<T>(t);
}

template <typename OStream, typename T>
OStream & operator<<(OStream & os, const OEnum<T> & e) {
  os << long(e.theT);
  return os;
}

template <typename IStream, typename T>
IStream & operator>>(IStream & is, const IEnum<T> & e) {
  long l = 0;
  is >> l;
  e.theT = T(l);
  return is;
}

}

#endif /* ThePEG_EnumIO_H */
