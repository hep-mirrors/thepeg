// -*- C++ -*-
#ifndef ThePEG_Ptr_H
#define ThePEG_Ptr_H
// This is the declaration of the Ptr class.

#include "RCPtr.fh"

namespace ThePEG {

/** The namespace for the reference counted pointer classes */
namespace Pointer {

/**
 * Ptr is a templated class to provide typedefs for pointers types
 * ThePEG should use for a given type. If you want to use ThePEG with
 * another kind of (smart) pointers than those provided you have to
 * provide an alternative ThePEG.h file which includes an alternative
 * Ptr class. It may also be possible to specialize this Ptr class for
 * using different pointer classes for different classes.
 *
 * @see RCPtr
 * @see ConstRCPtr
 * @see TransientRCPtr
 * @see TransientConstRCPtr
 * 
 */
template <typename T>
struct Ptr {

  typedef RCPtr<T> pointer;
  typedef ConstRCPtr<T> const_pointer;
  typedef TransientRCPtr<T> transient_pointer;
  typedef TransientConstRCPtr<T> transient_const_pointer;
  typedef pointer ptr;
  typedef const_pointer cptr;
  typedef transient_pointer tptr;
  typedef transient_const_pointer tcptr;
  typedef pointer p;
  typedef const_pointer cp;
  typedef transient_pointer tp;
  typedef transient_const_pointer tcp;

};

}
}

#endif /* ThePEG_Ptr_H */
