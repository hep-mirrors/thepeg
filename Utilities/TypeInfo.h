// -*- C++ -*-
#ifndef ThePEG_TypeInfo_H
#define ThePEG_TypeInfo_H

#include "DescriptionList.h"

namespace ThePEG {

struct TypeInfo {

  template <typename T>
  static inline string name(const T &);

  template <typename T>
  static inline int version(const T &);

};

}

#include "TypeInfo.icc"

#endif /* ThePEG_TypeInfo_H */
