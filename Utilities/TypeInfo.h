// -*- C++ -*-
#ifndef ThePEG_TypeInfo_H
#define ThePEG_TypeInfo_H

#include "DescriptionList.h"

namespace ThePEG {

/** TypeInfo is a simple wrapper around the ClassDescription system in
 *  ThePEG. Defines a few static functions for returning the mane and
 *  version of the class given objects of that class. */
struct TypeInfo {

  /** Return the name of the class of the given object. */
  template <typename T>
  static inline string name(const T &);

  /** Return the version number of the class of the given object. */
  template <typename T>
  static inline int version(const T &);

};

}

#include "TypeInfo.icc"

#endif /* ThePEG_TypeInfo_H */
