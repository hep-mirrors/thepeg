// -*- C++ -*-
#ifndef ThePEG_HoldFlag_H
#define ThePEG_HoldFlag_H
//
// This is the declaration of the <!id>HoldFlag<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>HoldFlag<!!id> object are used to temporarily change the value
// of a variable, restoring the original value when the
// <!id>HoldFlag<!!id> object is destructed.
//

// #include "ThePEG/Config/ThePEG.h"
// #include "HoldFlag.fh"
// #include "HoldFlag.xh"

namespace ThePEG {

template <typename T = bool>
class HoldFlag {

public:

  inline HoldFlag(T & newFlag, const T & holdFlag);
  // Ctor setting the newFlag to holdFlag.

  inline HoldFlag(T & newFlag, const T & holdFlag, const T & finalFlag);
  // Ctor setting the newFlag to holdFlag. newFlag will get the value
  // finalFlag when the object is destroyed.

  inline ~HoldFlag();
  // Dtor restoring the variable to its original value.

private:

  T & theFlag;
  // The variable.

  T oldFlag;
  // The value which will be restored when this is destroyed.

  inline HoldFlag();
  inline HoldFlag(const HoldFlag &);
  inline HoldFlag & operator=(const HoldFlag &);
  // Default ctors and assignment are private and not implemented.

};

template <>
class HoldFlag<bool> {

public:

  inline HoldFlag(bool & newFlag, bool holdFlag = true);
  inline HoldFlag(bool & newFlag, bool holdFlag, bool finalFlag);
  inline ~HoldFlag();

private:

  bool & theFlag;
  bool oldFlag;

  inline HoldFlag();
  inline HoldFlag(const HoldFlag &);
  inline HoldFlag & operator=(const HoldFlag &);

};

}

#include "HoldFlag.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HoldFlag.tcc"
#endif

#endif /* ThePEG_HoldFlag_H */
