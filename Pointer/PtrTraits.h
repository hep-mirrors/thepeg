// -*- C++ -*-
#ifndef ThePEG_PtrTraits_H
#define ThePEG_PtrTraits_H
//
// This is the declaration of the <!id>PtrTraits<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>PtrTraits<!!id> class is used everywhere in ThePEG to
// interface to the pointers which are handled. In particular, ThePEG
// never uses <!id>new<!!id> or <!id>delete<!!id> but always
// <!id>PtrTraits<P>::create<!!id> and
// <!id>PtrTraits<P>::destroy<!!id> (to be precise the destroy method
// is never used since all pointers are assumed to be reference
// counted or in another way garbage collected). Also ThePEG
// always uses <!id>dynamic_ptr_cast<!!id> (rather than the standard
// <!id>dynamic_cast<!!id>) which in torn calls the
// <!id>PtrTraits<P>::DynamicCast<!!id>.
//
// In this file is also defined the specialized std::iterator_traits
// for the reference counted pointers.
//

namespace ThePEG {
namespace Pointer {

template <class T>
struct PtrTraits;

template <class T>
struct PtrTraits<T *> {

  typedef T value_type;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T * pointer;
  typedef T * const_pointer;
  // Standard typedefs

  static T * barePointer(T * p) { return p; }
  // Return the bare pointer of the given pointer object.

  static pointer create() { return new T; }
  // Create an object and return a pointer to it.

  static pointer create(const_reference t) { return new T(t); }
  // Create an copy of an object and return a pointer to it.

  static void destroy(pointer tp) { delete tp; }
  // Destroy the object pointed to.

  template <class R>
  static pointer DynamicCast(R * r) { return dynamic_cast<pointer>(r); }
  // Cast dynamically.

  static pointer ConstCast(const T * t) { return const_cast<pointer>(t); }
  // Cast away constness.

  static pointer PtrCast(T * t) { return t; }
  // Cast from a basic pointer.

  static const bool reference_counted = false;

};

template <class T>
struct PtrTraits<const T *> {

  typedef T value_type;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T * pointer;
  typedef T * const_pointer;
  // Standard typedefs

  static const T * barePointer(const T * p) { return p; }
  // Return the bare pointer of the given pointer object.

  static pointer create() { return new T; }
  // Create an object and return a pointer to it.

  static pointer create(const_reference t) { return new T(t); }
  // Create an copy of an object and return a pointer to it.

  static void destroy(pointer tp) { delete tp; }
  // Destroy the object pointed to.

  template <class R>
  static const_pointer DynamicCast(const R * r) {
    return dynamic_cast<const_pointer>(r);
  }
  // Cast dynamically.

  static const_pointer ConstCast(const T * r) { return r; }
  // Do not cast away constness..

  static const_pointer PtrCast(const T * t) { return t; }
  // Cast from a basic pointer.

  static const bool reference_counted = false;

};

template <class T1, class T2>
T1 dynamic_ptr_cast(const T2 & t2) { return PtrTraits<T1>::DynamicCast(t2); }
// Replacement for the standard dynamic_cast

template <class T1, class T2>
T1 const_ptr_cast(const T2 & t2) { return PtrTraits<T1>::ConstCast(t2); }
// Replacement for the standard const_cast

template <typename Ptr>
inline Ptr ptr_new() { return PtrTraits<Ptr>::create(); }
// Simple interface to the PtrTraits<Ptr>::create()

template <typename Ptr>
inline Ptr ptr_new(typename PtrTraits<Ptr>::const_reference t) {
  return PtrTraits<Ptr>::create(t);
}
// Simple interface to the PtrTraits<Ptr>::create()

template <typename T>
inline typename Ptr<T>::pointer new_ptr() {
  return PtrTraits< typename Ptr<T>::pointer >::create();
}
// Simple interface to the PtrTraits<Ptr>::create()

template <typename T>
inline typename Ptr<T>::pointer new_ptr(const T & t) {
  return PtrTraits< typename Ptr<T>::pointer >::create(t);
}
// Simple interface to the PtrTraits<Ptr>::create()

template <typename TPtr, typename T>
inline TPtr ptr_cast(T * t) {
  return PtrTraits<TPtr>::PtrCast(t);
}
// Simple interface to the PtrTraits<Ptr>::PtrCast()

template <typename TPtr, typename T>
inline TPtr ptr_cast_const(const T * t) {
  return PtrTraits<TPtr>::PtrCast(const_cast<T*>(t));
}
// Simple interface to the PtrTraits<Ptr>::PtrCast()

}
}

#endif /* ThePEG_PtrTraitsH */
