// -*- C++ -*-
#ifndef ThePEG_RCPtr_H
#define ThePEG_RCPtr_H
//
// This is the declaration of the <!id>RCPtrBase<!!id>,
// <!id>RCPtr<!!id>, <!id>ConstRCPtr<!!id>, <!id>TransientRCPtr<!!id>
// and <!id>TransientConstRCPtr<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>RCPtr<!!id> and <!id>ConstRCPtr<!!id> are reference counted
// (smart) pointers. Objects created using the
// <!id>RCPtr::create()<!!id> methods will continue lving until no
// <!id>RCPtr<!!id> or <!id>ConstRCPtr<!!id> are pointing to it, at
// which point it will be deleted. <!id>TransientRCPtr<!!id> and
// <!id>TransientConstRCPtr<!!id> are just simple wrappers around
// basic pointers used to facilitate conversions between smart and
// dumb pointers.
//
// <!id>RCPtr<!!id> and <!id>ConstRCPtr<!!id> both derive from the
// <!id>RCPtrBase<!!id> class which communicate with the
// <!class>ReferenceCounted<!!class> which must be the base class of
// all objects pointed to and which keeps count of the pointers
// pointing to an object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ReferenceCounted.html">ReferenceCounted.h</a>.
// 


#include "ReferenceCounted.h"
#include "RCPtr.fh"
#include "PtrTraits.h"
// #include "RCPtr.xh"

namespace ThePEG {
namespace Pointer {

class RCPtrBase {

  typedef ReferenceCounted::CounterType CounterType;

protected:

  inline void increment(const ReferenceCounted *);
  inline bool release(const ReferenceCounted *);
  // Increment and decrement the counters of a reference counted
  // object.

};

template <typename T>
class RCPtr: public RCPtrBase {

public:

  typedef void iterator_category;
  typedef void difference_type;
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T value_type;

public:

  inline RCPtr();
  // Constructor for null pointer.

  inline RCPtr(const RCPtr & p);
  // Copy constructor.

  template <typename UPtr>
  inline RCPtr(const UPtr & u);
  // Copyconstructor for class UPtr which has operator-> defined
  // resulting in a value implicitly convertible to T *.

  inline explicit RCPtr(pointer p);
  // Construction from real pointer.

  inline ~RCPtr();
  // Destructor. Deletes the object pointed to if this is the last
  // pointer to it.

  inline static RCPtr Create();
  inline static RCPtr Create(const_reference t);
  // Allocate and construct an object of class T and return a RCPtr to
  // it.

  inline RCPtr & create();
  inline RCPtr & create(const_reference t);
  // Allocate and construct an object of class T and point to it,
  // possibly deleting the object pointed to before.

  inline RCPtr & operator=(const RCPtr & p);
  // Assignment.

  template <typename UPtr>
  inline RCPtr & operator=(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value implicitly convertible to T *.

  template <typename UPtr>
  inline RCPtr & assignDynamic(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value which can be cast dynamically to T *.

  template <typename UPtr>
  inline RCPtr & assignConst(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value which can be const_cast'ed to T *.

  inline void assign(pointer);
  // Assignment from bare pointer without increasing refcount.

  inline void swap(RCPtr & p);
  // Make u point to the object pointed to by this and vice versa.  

  inline bool operator==(const RCPtr & p) const;
  inline bool operator!=(const RCPtr & p) const;
  inline bool operator==(const_pointer p) const;
  inline bool operator!=(const_pointer p) const;
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;
  // Test for equality of the underlying pointers.

  inline bool operator<(const RCPtr & p) const;
  inline bool operator<(const_pointer p) const;
  // Test for ordering.

  inline bool operator!() const ;
  inline operator T * () const ;
  // Returns (not) the underlying pointer.

  inline pointer operator->() const;
  // Member access.

  inline reference operator*() const;
  // Dereferencing.

private:

  void increment();
  // Increment the counter of the object pointed to.

  inline void release();
  // Stop pointing to the current object and delete it if this was the
  // last pointer to it.
   
  pointer thePointer;
  // The actual pointer.

};



template <typename T>
class ConstRCPtr : public RCPtrBase {

public:

  typedef void iterator_category;
  typedef void difference_type;
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T value_type;

public:

  inline ConstRCPtr();
  // Constructor for null pointer.

  inline ConstRCPtr(const ConstRCPtr & p);
  // Copy constructor.

  template <typename UPtr>
  inline ConstRCPtr(const UPtr & u);
  // Copyconstructor for class UPtr which has operator-> defined
  // resulting in a value implicitly convertible to const T *.

  inline explicit ConstRCPtr(const_pointer p);
  // Construction from real pointer.

  inline ~ConstRCPtr();
  // Destructor. Deletes the object pointed to if this is the last
  // pointer to it.

  inline ConstRCPtr & operator=(const ConstRCPtr & p);
  // Assignment.

  template <typename UPtr>
  inline ConstRCPtr & operator=(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value implicitly convertible to const T *.

  template <typename UPtr>
  inline ConstRCPtr & assignDynamic(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value which can be cast dynamically to const T *.

  inline void swap(ConstRCPtr & p);
  // Make p point to the object pointed to by this and vice versa.  

  inline bool operator==(const ConstRCPtr & p) const;
  inline bool operator!=(const ConstRCPtr & p) const;
  inline bool operator==(const_pointer p) const;
  inline bool operator!=(const_pointer p) const;
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;
  // Test for equality of the underlying pointers.

  inline bool operator<(const ConstRCPtr & p) const;
  inline bool operator<(const_pointer p) const;
  // Test for ordering.

  inline bool operator!() const ;
  inline operator const T * () const ;
  // Returns (not) the underlying pointer.

  inline const_pointer operator->() const;
  // Member access.

  inline const_reference operator*() const;
  // Dereferencing.

private:

  void increment();
  // Increment the counter of the object pointed to.

  inline void release();
  // Stop pointing to the current object and delete it if this was the
  // last pointer to it.
   
  const_pointer thePointer;
  // The actual pointer.

};

template <typename T>
class TransientRCPtr {

public:

  typedef void iterator_category;
  typedef void difference_type;
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T value_type;

public:

  inline TransientRCPtr();
  // Constructor for null pointer.

  inline TransientRCPtr(const TransientRCPtr & p);
  // Copy constructor.

  template <typename UPtr>
  inline TransientRCPtr(const UPtr & u);
  // Copyconstructor for class UPtr which has operator-> defined
  // resulting in a value implicitly convertible to T *.

  inline explicit TransientRCPtr(pointer p);
  // Construction from real pointer.

  inline ~TransientRCPtr();
  // Destructor. Does not delete the object pointed to.

  inline TransientRCPtr & operator=(const TransientRCPtr & p);
  // Assignment.

  template <typename UPtr>
  inline TransientRCPtr & operator=(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value implicitly convertible to T *.

  template <typename UPtr>
  inline TransientRCPtr & assignDynamic(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value which can be cast dynamically to T *.

  template <typename UPtr>
  inline TransientRCPtr & assignConst(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value whcih can be const_cast'ed to T *.

  inline bool operator==(const TransientRCPtr & p) const;
  inline bool operator!=(const TransientRCPtr & p) const;
  inline bool operator==(const_pointer p) const;
  inline bool operator!=(const_pointer p) const;
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;
  // Test for equality of the underlying pointers.

  inline bool operator<(const TransientRCPtr & p) const;
  inline bool operator<(const_pointer p) const;
  // Test for ordering.

  inline bool operator!() const ;
  inline operator T * () const ;
  // Returns (not) the underlying pointer.

  inline pointer operator->() const;
  // Member access.

  inline reference operator*() const;
  // Dereferencing.

private:

  pointer thePointer;
  // The actual pointer.

};

template <typename T>
class TransientConstRCPtr {

public:

  typedef void iterator_category;
  typedef void difference_type;
  typedef T * pointer;
  typedef const T * const_pointer;
  typedef T & reference;
  typedef const T & const_reference;
  typedef T value_type;

public:

  inline TransientConstRCPtr();
  // Constructor for null pointer.

  inline TransientConstRCPtr(const TransientConstRCPtr & p);
  // Copy constructor.

  template <typename UPtr>
  inline TransientConstRCPtr(const UPtr & u);
  // Copyconstructor for class UPtr which has operator-> defined
  // resulting in a value implicitly convertible to const T *.

  inline explicit TransientConstRCPtr(const_pointer p);
  // Construction from real pointer.

  inline ~TransientConstRCPtr();
  // Destructor. Does not delete the object pointed to.

  inline TransientConstRCPtr & operator=(const TransientConstRCPtr & p);
  // Assignment.

  template <typename UPtr>
  inline TransientConstRCPtr & operator=(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value implicitly convertible to const T *.

  template <typename UPtr>
  inline TransientConstRCPtr & assignDynamic(const UPtr & u);
  // Assignment from class UPtr which has operator-> defined resulting
  // in a value which can be cast dynamically to const T *.

  inline bool operator==(const TransientConstRCPtr & p) const;
  inline bool operator!=(const TransientConstRCPtr & p) const;
  inline bool operator==(const_pointer p) const;
  inline bool operator!=(const_pointer p) const;
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;
  // Test for equality of the underlying pointers.

  inline bool operator<(const TransientConstRCPtr & p) const;
  inline bool operator<(const_pointer p) const;
  // Test for ordering.

  inline bool operator!() const ;
  inline operator const T * () const ;
  // Returns (not) the underlying pointer.

  inline const_pointer operator->() const;
  // Member access.

  inline const_reference operator*() const;
  // Dereferencing.

private:

  const_pointer thePointer;
  // The actual pointer.

};

template <typename T>
struct PtrTraits< RCPtr<T> > {
  // Partial specialization of the PtrTraits class.
  typedef typename RCPtr<T>::value_type value_type;
  typedef typename RCPtr<T>::reference reference;
  typedef typename RCPtr<T>::const_reference const_reference;
  typedef RCPtr<T> pointer;
  typedef ConstRCPtr<T> const_pointer;
  typedef TransientRCPtr<T> transient_pointer;
  typedef TransientConstRCPtr<T> transient_const_pointer;

  static T * barePointer(const RCPtr<T> & p) { return p.operator->(); }

  static pointer create() { return RCPtr<T>::Create(); }
  static pointer create(const_reference t) { return RCPtr<T>::Create(t); }
  static void destroy(pointer tp) {}

  template <typename UPtr>
  static pointer DynamicCast(const UPtr & u) {
    pointer t;
    t.assignDynamic(u);
    return t;
  }

  template <typename UPtr>
  static pointer ConstCast(const UPtr & u) {
    pointer t;
    t.assignConst(u);
    return t;
  }

  static pointer PtrCast(T * t) {
    return pointer(t);
  }

  static const bool reference_counted = true;

}; 

template <typename T>
struct PtrTraits< ConstRCPtr<T> > {
  // Partial specialization of the PtrTraits class.
  typedef typename ConstRCPtr<T>::value_type value_type;
  typedef typename ConstRCPtr<T>::reference reference;
  typedef typename ConstRCPtr<T>::const_reference const_reference;
  typedef RCPtr<T> pointer;
  typedef ConstRCPtr<T> const_pointer;
  typedef TransientRCPtr<T> transient_pointer;
  typedef TransientConstRCPtr<T> transient_const_pointer;

  static const T * barePointer(const ConstRCPtr<T> & p) {
    return p.operator->();
  }

  static const_pointer create() {
    return RCPtr<T>::Create();
  }

  static const_pointer create(const_reference t) {
    return RCPtr<T>::Create(t);
  }

  static void destroy(const_pointer tp) {}

  template <typename UPtr>
  static const_pointer DynamicCast(const UPtr & u) {
    const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  template <typename UPtr>
  static const_pointer ConstCast(const UPtr & u) {
    const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  static const_pointer PtrCast(const T * t) {
    return const_pointer(t);
  }

  static const bool reference_counted = true;

}; 

template <typename T>
struct PtrTraits< TransientRCPtr<T> > {
  // Partial specialization of the PtrTraits class.
  typedef typename TransientRCPtr<T>::value_type value_type;
  typedef typename TransientRCPtr<T>::reference reference;
  typedef typename TransientRCPtr<T>::const_reference const_reference;
  typedef RCPtr<T> pointer;
  typedef ConstRCPtr<T> const_pointer;
  typedef TransientRCPtr<T> transient_pointer;
  typedef TransientConstRCPtr<T> transient_const_pointer;

  static T * barePointer(const TransientRCPtr<T> & p) {
    return p.operator->();
  }

  static void destroy(transient_pointer tp) {}

  template <typename UPtr>
  static transient_pointer DynamicCast(const UPtr & u) {
    transient_pointer t;
    t.assignDynamic(u);
    return t;
  }

  static transient_pointer ConstCast(transient_const_pointer c) {
    transient_pointer t;
    t.assignConst(c);
    return t;
  }

  static transient_pointer PtrCast(T * t) {
    return transient_pointer(t);
  }

  static const bool reference_counted = false;

}; 

template <typename T>
struct PtrTraits< TransientConstRCPtr<T> > {
  // Partial specialization of the PtrTraits class.
  typedef typename TransientConstRCPtr<T>::value_type value_type;
  typedef typename TransientConstRCPtr<T>::reference reference;
  typedef typename TransientConstRCPtr<T>::const_reference const_reference;
  typedef RCPtr<T> pointer;
  typedef ConstRCPtr<T> const_pointer;
  typedef TransientRCPtr<T> transient_pointer;
  typedef TransientConstRCPtr<T> transient_const_pointer;

  static const T * barePointer(const TransientConstRCPtr<T> & p) {
    return p.operator->();
  }

  static void destroy(transient_const_pointer tp) {}

  template <typename UPtr>
  static transient_const_pointer DynamicCast(const UPtr & u) {
    transient_const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  template <typename UPtr>
  static transient_const_pointer ConstCast(const UPtr & u) {
    transient_const_pointer t;
    t.assignConst(u);
    return t;
  }

  static transient_const_pointer PtrCast(const T * t) {
    return transient_const_pointer(t);
  }

  static const bool reference_counted = false;

}; 

}
}

namespace std {

template <typename T>
void swap(ThePEG::Pointer::RCPtr<T> &, ThePEG::Pointer::RCPtr<T> &);
template <typename T>
void swap(ThePEG::Pointer::ConstRCPtr<T> &,
	       ThePEG::Pointer::ConstRCPtr<T> &);
// Specialization of std::swap to avoid unnecessary (in/de)crements of
// the reference count.

}

#include "RCPtr.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RCPtr.tcc"
#endif

#endif /* ThePEG_RCPtr_H */
