// -*- C++ -*-
#ifndef ThePEG_H
#define ThePEG_H

// This is the main config header file for ThePEG. Do not make
// changes in this file. If you need to modify anything, edit a copy
// of the file which can be included instead of this file using the
// macro <!id>ThePEG_ALTERNATE_CONFIG<!!id>.

#include "ThePEG/Config/config.h"

// For some reason the gcc compiler has a very slow exception
// handling. And it is even slower if functions which have throw
// specification throws. The following macro should therefore be used
// for exception specifications.
#ifndef __GNUG__
#define ThePEG_THROW_SPEC(classes) throw classes
#else
#define ThePEG_THROW_SPEC(classes)
#endif

#ifndef ThePEG_ALTERNATE_CONFIG

#include "ThePEG/Pointer/Ptr.h"
#include "ThePEG/Pointer/PtrTraits.h"
#include "ThePEG/Pointer/RCPtr.h"
#include "ThePEG/Utilities/Rebinder.fh"
#include "ThePEG/Utilities/Interval.fh"
#include "ThePEG/Utilities/ClassDescription.fh"
#include "ThePEG/Interface/InterfaceBase.fh"
#include "ThePEG/Persistency/PersistentOStream.fh"
#include "ThePEG/Persistency/PersistentIStream.fh"
#include "Units.h"
#include "Constants.h"
#include "std.h"

namespace ThePEG {

// Introduce some identifiers in the ThePEG namespace/
using namespace ThePEG::Pointer;
using ThePEG::Pointer::Ptr;
using namespace ThePEG::Units;

// Define the base class from which all (polymorphic) classes in
// ThePEG are derived.
struct Base: public ReferenceCounted {
  virtual ~Base() {}
  static void Init() {}
};

// Define the base class from which all persistent classes in
// ThePEG are derived.
typedef Base PersistentBase;

// Define some standard exception classes.
struct Veto {
  Veto();
};
struct Stop {};

// Some standard inline functions which should have been in the C++
// standard.
template <typename T>
inline typename MultiplicationTraits<T>::ResultType sqr(const T& x) {
  return x*x;
}

template <typename T>
inline T abs(const T & t) {
  return t < T()? -t: t;
}

// Debugging in ThePEG may be swithced off completely by this
// compilation swithc, eliminating possible overhead in error
// checking.
#ifndef ThePEG_NO_DEBUG
#define ThePEG_DEBUG_LEVEL Debug::level
#define ThePEG_DEBUG_ITEM(item) Debug::debugItem(item)
#else
#define ThePEG_DEBUG_LEVEL 0
#define ThePEG_DEBUG_ITEM(item) false
#endif

}

#include "Pointers.h"
#include "Containers.h"

#else

#include ThePEG_ALTERNATIVE_CONFIG

#endif

#endif /* ThePEG_H */

