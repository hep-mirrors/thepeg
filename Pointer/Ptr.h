// -*- C++ -*-
#ifndef ThePEG_Ptr_H
#define ThePEG_Ptr_H
//
// This is the declaration of the <!id>Ptr<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Ptr<!!id> is a templated class to provide typedefs for
// pointers ThePEG should use for a given type. If you want to use
// ThePEG with another kind of (smart) pointers than those provided
// you have to provide an alternative <!id>ThePEG.h<!!id> file which
// includes an alternative <!id>Ptr<!!id> class. It may also be
// possible to specialize this Ptr class for using different pointer
// classes for different classes.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ThePEG.html">ThePEG.h</a>.
// 

#include "RCPtr.fh"

namespace ThePEG {
namespace Pointer {

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
