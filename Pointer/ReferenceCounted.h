// -*- C++ -*-
#ifndef ThePEG_ReferenceCounted_H
#define ThePEG_ReferenceCounted_H
//
// This is the declaration of the <!id>ReferenceCounted<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ReferenceCounted<!!id> must be the (virtual) base class of all
// classes which may be pointed to by the <!class>RCPtr<!!class> smart
// pointer class. It keeps track of all <!id>RCPtr<!!id> and
// <!id>ConstRCPtr<!!id> pointers which are currently pointing to an
// object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:RCPtr.html">RCPtr.h</a>.
// 


#include "RCPtr.fh"
// #include "ReferenceCounted.fh"
// #include "ReferenceCounted.xh"

namespace ThePEG {
namespace Pointer {

class ReferenceCounted {

  friend class RCPtrBase;

public:

  typedef unsigned int CounterType;

protected:

  inline ReferenceCounted();
  inline ReferenceCounted(const ReferenceCounted &);
  inline ReferenceCounted & operator=(const ReferenceCounted &);
  // Standard ctors and assignment.

public:

  inline CounterType referenceCount() const;
  // Return the reference count.

private:

  inline void incrementReferenceCount() const;
  inline bool decrementReferenceCount() const;
  // Mess with the reference count.

private:

  mutable CounterType theReferenceCounter;
  // The reference count.

};


}
}

#include "ReferenceCounted.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReferenceCounted.tcc"
#endif

#endif /* ThePEG_ReferenceCounted_H */
