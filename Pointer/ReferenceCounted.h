// -*- C++ -*-
#ifndef ThePEG_ReferenceCounted_H
#define ThePEG_ReferenceCounted_H
// This is the declaration of the ReferenceCounted class.


#include "RCPtr.fh"

namespace ThePEG {
namespace Pointer {

/**
 * ReferenceCounted must be the (virtual) base class of all
 * classes which may be pointed to by the RCPtr smart
 * pointer class. It keeps track of all RCPtr and
 * ConstRCPtr pointers which are currently pointing to an
 * object.
 *
 * @see RCPtr
 * @see ConstRCPtr
 */
class ReferenceCounted {

  /** The RCPtrBase class needs to acces the private parts of ReferenceCounted. */
  friend class RCPtrBase;

public:

  /**
   * The integer type used for counting.
   */
  typedef unsigned int CounterType;

protected:

  /** @name Standard constructors and assignment. */
  //@{
  /**
   * Default constructor.
   */
  inline ReferenceCounted();

  /**
   * Copy-constructor.
   */
  inline ReferenceCounted(const ReferenceCounted &);

  /**
   * Assignment.
   */
  inline ReferenceCounted & operator=(const ReferenceCounted &);
  //@}

public:

  /**
   * Return the reference count.
   */
  inline CounterType referenceCount() const;

private:

  /**
   * Increment the reference count.
   */
  inline void incrementReferenceCount() const;

  /**
   * Decrement with the reference count.
   */
  inline bool decrementReferenceCount() const;

private:

  /**
   * The reference count.
   */
  mutable CounterType theReferenceCounter;

};


}
}

#include "ReferenceCounted.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReferenceCounted.tcc"
#endif

#endif /* ThePEG_ReferenceCounted_H */

