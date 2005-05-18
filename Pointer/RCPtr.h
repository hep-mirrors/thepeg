// -*- C++ -*-
#ifndef ThePEG_RCPtr_H
#define ThePEG_RCPtr_H
// This is the declaration of the RCPtrBase,


#include "ReferenceCounted.h"
#include "RCPtr.fh"
#include "PtrTraits.h"

namespace ThePEG {
namespace Pointer {

/**
 * RCPtrBase is the base class of RCPtr and ConstRCPtr which are
 * reference counted (smart) pointers. The RCPtrBase class communicates with the
 * ReferenceCounted object which must be the base class of
 * all objects pointed to and which keeps count of the pointers
 * pointing to an object.
 *
 * @see ReferenceCounted
 */
class RCPtrBase {

  /** Get counter type from ReferenceCounted class. */
  typedef ReferenceCounted::CounterType CounterType;

protected:

  /**
   * Increment the counter of a reference counted object.
   */
  inline void increment(const ReferenceCounted *);
  /**
   * Decrement the counter of a reference counted object.
   */
  inline bool release(const ReferenceCounted *);

};

/**
 * RCPtr is a reference counted (smart) pointer. Objects created using
 * the RCPtr::create() methods will continue living until no RCPtr or
 * ConstRCPtr are pointing to it, at which point it will be deleted.
 *
 * @see ReferenceCounted
 */
template <typename T>
class RCPtr: public RCPtrBase {

public:

  /** Template argument typedef. */
  typedef void iterator_category;
  /** Template argument typedef. */
  typedef void difference_type;
  /** Template argument typedef. */
  typedef T * pointer;
  /** Template argument typedef. */
  typedef const T * const_pointer;
  /** Template argument typedef. */
  typedef T & reference;
  /** Template argument typedef. */
  typedef const T & const_reference;
  /** Template argument typedef. */
  typedef T value_type;

public:

  /** <code></code> */
  /**
   * Constructor for null pointer.
   */
  inline RCPtr();

  /**
   * Copy constructor.
   */
  inline RCPtr(const RCPtr & p);

  /**
   * Copy constructor for class UPtr which has operator-> defined
   * resulting in a value implicitly convertible to T *.
   */
  template <typename UPtr>
  inline RCPtr(const UPtr & u);

  /**
   * Construction from real pointer.
   */
  inline explicit RCPtr(pointer p);

  /**
   * Destructor. Deletes the object pointed to if this is the last
   * pointer to it.
   */
  inline ~RCPtr();

  /**
   * Allocate and construct an object of class T and return a RCPtr to
   * it.
   */
  inline static RCPtr Create();

  /**
   * Allocate and copy-construct an object of class T and return a
   * RCPtr to it.
   */
  inline static RCPtr Create(const_reference t);

  /**
   * Allocate and construct an object of class T and point to it,
   * possibly deleting the object pointed to before.
   */
  inline RCPtr & create();

  /**
   * Allocate and copy-construct an object of class T and point to it,
   * possibly deleting the object pointed to before.
   */
  inline RCPtr & create(const_reference t);

  /**
   * Assignment.
   */
  inline RCPtr & operator=(const RCPtr & p);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value implicitly convertible to T *.
   */
  template <typename UPtr>
  inline RCPtr & operator=(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value which can be cast dynamically to T *.
   */
  template <typename UPtr>
  inline RCPtr & assignDynamic(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value which can be const_cast'ed to T *.
   */
  template <typename UPtr>
  inline RCPtr & assignConst(const UPtr & u);

  /**
   * Assignment from bare pointer without increasing refcount.
   */
  inline void assign(pointer);

  /**
   * Make p point to the object pointed to by this and vice versa.  
   */
  inline void swap(RCPtr & p);

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const RCPtr & p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const RCPtr & p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const_pointer p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const_pointer p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const RCPtr & p) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const_pointer p) const;

  /**
   * Returns true if the underlying pointer is null.
   */
  inline bool operator!() const ;

  /**
   * Returns the underlying pointer.
   */
  inline operator T * () const ;

  /**
   * Member access.
   */
  inline pointer operator->() const;

  /**
   * Dereferencing.
   */
  inline reference operator*() const;

private:

  /**
   * Increment the counter of the object pointed to.
   */
  void increment();

  /**
   * Stop pointing to the current object and delete it if this was the
   * last pointer to it.
   */
  inline void release();
   
  /**
   * The actual pointer.
   */
  pointer ptr;

};

/**
 * ConstRCPtr is a reference counted (smart) const pointer. Objects
 * created using the RCPtr::create() methods will continue living
 * until no RCPtr or ConstRCPtr are pointing to it, at which point it
 * will be deleted.
 *
 * @see ReferenceCounted
 */
template <typename T>
class ConstRCPtr : public RCPtrBase {

public:

  /** Template argument typedef. */
  typedef void iterator_category;
  /** Template argument typedef. */
  typedef void difference_type;
  /** Template argument typedef. */
  typedef T * pointer;
  /** Template argument typedef. */
  typedef const T * const_pointer;
  /** Template argument typedef. */
  typedef T & reference;
  /** Template argument typedef. */
  typedef const T & const_reference;
  /** Template argument typedef. */
  typedef T value_type;

public:

  /**
   * Constructor for null pointer.
   */
  inline ConstRCPtr();

  /**
   * Copy constructor.
   */
  inline ConstRCPtr(const ConstRCPtr & p);

  /**
   * Copyconstructor for class UPtr which has operator-> defined
   * resulting in a value implicitly convertible to const T *.
   */
  template <typename UPtr>
  inline ConstRCPtr(const UPtr & u);

  /**
   * Construction from real pointer.
   */
  inline explicit ConstRCPtr(const_pointer p);

  /**
   * Destructor. Deletes the object pointed to if this is the last
   * pointer to it.
   */
  inline ~ConstRCPtr();

  /**
   * Assignment.
   */
  inline ConstRCPtr & operator=(const ConstRCPtr & p);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value implicitly convertible to const T *.
   */
  template <typename UPtr>
  inline ConstRCPtr & operator=(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value which can be cast dynamically to const T *.
   */
  template <typename UPtr>
  inline ConstRCPtr & assignDynamic(const UPtr & u);

  /**
   * Make p point to the object pointed to by this and vice versa.  
   */
  inline void swap(ConstRCPtr & p);

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const ConstRCPtr & p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const ConstRCPtr & p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const_pointer p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const_pointer p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const ConstRCPtr & p) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const_pointer p) const;

  /**
   * Returns true if the underlying pointer is null.
   */
  inline bool operator!() const ;

  /**
   * Returns the underlying pointer.
   */
  inline operator const T * () const ;

  /**
   * Member access.
   */
  inline const_pointer operator->() const;

  /**
   * Dereferencing.
   */
  inline const_reference operator*() const;

private:

  /**
   * Increment the counter of the object pointed to.
   */
  void increment();

  /**
   * Stop pointing to the current object and delete it if this was the
   * last pointer to it.
   */
  inline void release();
   
  /**
   * The actual pointer.
   */
  const_pointer ptr;

};

/**
 * TransientRCPtr is a simple wrapper around a bare pointer which can
 * be assigned to and from an RCPtr and ConstRCPtr without problem.
 *
 * @see RCPtr
 * @see ConstRCPtr
 */
template <typename T>
class TransientRCPtr {

public:

  /** Template argument typedef. */
  typedef void iterator_category;
  /** Template argument typedef. */
  typedef void difference_type;
  /** Template argument typedef. */
  typedef T * pointer;
  /** Template argument typedef. */
  typedef const T * const_pointer;
  /** Template argument typedef. */
  typedef T & reference;
  /** Template argument typedef. */
  typedef const T & const_reference;
  /** Template argument typedef. */
  typedef T value_type;

public:

  /**
   * Constructor for null pointer.
   */
  inline TransientRCPtr();

  /**
   * Copy constructor.
   */
  inline TransientRCPtr(const TransientRCPtr & p);

  /**
   * Copyconstructor for class UPtr which has operator-> defined
   * resulting in a value implicitly convertible to T *.
   */
  template <typename UPtr>
  inline TransientRCPtr(const UPtr & u);

  /**
   * Construction from real pointer.
   */
  inline explicit TransientRCPtr(pointer p);

  /**
   * Destructor. Does not delete the object pointed to.
   */
  inline ~TransientRCPtr();

  /**
   * Assignment.
   */
  inline TransientRCPtr & operator=(const TransientRCPtr & p);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value implicitly convertible to T *.
   */
  template <typename UPtr>
  inline TransientRCPtr & operator=(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value which can be cast dynamically to T *.
   */
  template <typename UPtr>
  inline TransientRCPtr & assignDynamic(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value whcih can be const_cast'ed to T *.
   */
  template <typename UPtr>
  inline TransientRCPtr & assignConst(const UPtr & u);

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const TransientRCPtr & p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const TransientRCPtr & p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const_pointer p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const_pointer p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const TransientRCPtr & p) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const_pointer p) const;

  /**
   * Returns true if the underlying pointer is null.
   */
  inline bool operator!() const ;

  /**
   * Returns the underlying pointer.
   */
  inline operator T * () const ;

  /**
   * Member access.
   */
  inline pointer operator->() const;

  /**
   * Dereferencing.
   */
  inline reference operator*() const;

private:

  /**
   * The actual pointer.
   */
  pointer ptr;

};

/**
 * TransientConstRCPtr is a simple wrapper around a bare const pointer
 * which can be assigned to and from an RCPtr and ConstRCPtr without
 * problem.
 *
 * @see RCPtr
 * @see ConstRCPtr
 */
template <typename T>
class TransientConstRCPtr {

public:

  /** Template argument typedef. */
  typedef void iterator_category;
  /** Template argument typedef. */
  typedef void difference_type;
  /** Template argument typedef. */
  typedef T * pointer;
  /** Template argument typedef. */
  typedef const T * const_pointer;
  /** Template argument typedef. */
  typedef T & reference;
  /** Template argument typedef. */
  typedef const T & const_reference;
  /** Template argument typedef. */
  typedef T value_type;

public:

  /**
   * Constructor for null pointer.
   */
  inline TransientConstRCPtr();

  /**
   * Copy constructor.
   */
  inline TransientConstRCPtr(const TransientConstRCPtr & p);

  /**
   * Copyconstructor for class UPtr which has operator-> defined
   * resulting in a value implicitly convertible to const T *.
   */
  template <typename UPtr>
  inline TransientConstRCPtr(const UPtr & u);

  /**
   * Construction from real pointer.
   */
  inline explicit TransientConstRCPtr(const_pointer p);

  /**
   * Destructor. Does not delete the object pointed to.
   */
  inline ~TransientConstRCPtr();

  /**
   * Assignment.
   */
  inline TransientConstRCPtr & operator=(const TransientConstRCPtr & p);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value implicitly convertible to const T *.
   */
  template <typename UPtr>
  inline TransientConstRCPtr & operator=(const UPtr & u);

  /**
   * Assignment from class UPtr which has operator-> defined resulting
   * in a value which can be cast dynamically to const T *.
   */
  template <typename UPtr>
  inline TransientConstRCPtr & assignDynamic(const UPtr & u);

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const TransientConstRCPtr & p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const TransientConstRCPtr & p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  inline bool operator==(const_pointer p) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  inline bool operator!=(const_pointer p) const;

  /**
   * Test for equality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator==(const UPtr & u) const;

  /**
   * Test for inequality of the underlying pointers.
   */
  template <typename UPtr>
  inline bool operator!=(const UPtr & u) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const TransientConstRCPtr & p) const;

  /**
   * Test for ordering.
   */
  inline bool operator<(const_pointer p) const;

  /**
   * Returns true if the underlying pointer is null.
   */
  inline bool operator!() const ;

  /**
   * Returns (not) the underlying pointer.
   */
  inline operator const T * () const ;

  /**
   * Member access.
   */
  inline const_pointer operator->() const;

  /**
   * Dereferencing.
   */
  inline const_reference operator*() const;

private:

  /**
   * The actual pointer.
   */
  const_pointer ptr;

};

/**
 * Specialization of the PtrTraits class for RCPtr.
 */
template <typename T>
struct PtrTraits< RCPtr<T> >: public PtrTraitsType {

  /** Template argument typedef. */
  typedef typename RCPtr<T>::value_type value_type;
  /** Template argument typedef. */
  typedef typename RCPtr<T>::reference reference;
  /** Template argument typedef. */
  typedef typename RCPtr<T>::const_reference const_reference;
  /** Template argument typedef. */
  typedef RCPtr<T> pointer;
  /** Template argument typedef. */
  typedef ConstRCPtr<T> const_pointer;
  /** Template argument typedef. */
  typedef TransientRCPtr<T> transient_pointer;
  /** Template argument typedef. */
  typedef TransientConstRCPtr<T> transient_const_pointer;

  /**
   * Return the bare pointer of the given pointer object.
   */
  static T * barePointer(const RCPtr<T> & p) { return p.operator->(); }

  /**
   * Create an object and return a pointer to it.
   */
  static pointer create() { return RCPtr<T>::Create(); }

  /**
   * Create an copy of an object and return a pointer to it.
   */
  static pointer create(const_reference t) { return RCPtr<T>::Create(t); }

  /**
   * Destroy the object pointed to.
   */
  static void destroy(pointer tp) {}

  /**
   * Cast dynamically.
   */
  template <typename UPtr>
  static pointer DynamicCast(const UPtr & u) {
    pointer t;
    t.assignDynamic(u);
    return t;
  }

  /**
   * Cast away constness.
   */
  template <typename UPtr>
  static pointer ConstCast(const UPtr & u) {
    pointer t;
    t.assignConst(u);
    return t;
  }

  /**
   * Cast from a basic pointer.
   */
  static pointer PtrCast(T * t) {
    return pointer(t);
  }

  /**
   * RCPtr is reference counted.
   */
  static const bool reference_counted = true;

}; 

/**
 * Specialization of the PtrTraits class for ConstRCPtr.
 */
template <typename T>
struct PtrTraits< ConstRCPtr<T> >: public PtrTraitsType {

  /** Template argument typedef. */
  typedef typename ConstRCPtr<T>::value_type value_type;
  /** Template argument typedef. */
  typedef typename ConstRCPtr<T>::reference reference;
  /** Template argument typedef. */
  typedef typename ConstRCPtr<T>::const_reference const_reference;
  /** Template argument typedef. */
  typedef RCPtr<T> pointer;
  /** Template argument typedef. */
  typedef ConstRCPtr<T> const_pointer;
  /** Template argument typedef. */
  typedef TransientRCPtr<T> transient_pointer;
  /** Template argument typedef. */
  typedef TransientConstRCPtr<T> transient_const_pointer;

  /**
   * Return the bare pointer of the given pointer object.
   */
  static const T * barePointer(const ConstRCPtr<T> & p) {
    return p.operator->();
  }

  /**
   * Create an object and return a pointer to it.
   */
  static const_pointer create() {
    return RCPtr<T>::Create();
  }

  /**
   * Create an copy of an object and return a pointer to it.
   */
  static const_pointer create(const_reference t) {
    return RCPtr<T>::Create(t);
  }

  /**
   * Destroy the object pointed to.
   */
  static void destroy(const_pointer tp) {}

  /**
   * Cast dynamically.
   */
  template <typename UPtr>
  static const_pointer DynamicCast(const UPtr & u) {
    const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  /**
   * Cast away constness.
   */
  template <typename UPtr>
  static const_pointer ConstCast(const UPtr & u) {
    const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  /**
   * Cast from a basic pointer.
   */
  static const_pointer PtrCast(const T * t) {
    return const_pointer(t);
  }

  /**
   * ConstRCPtr is reference counted.
   */
  static const bool reference_counted = true;

}; 

/**
 * Specialization of the PtrTraits class for TransientRCPtr.
 */
template <typename T>
struct PtrTraits< TransientRCPtr<T> >: public PtrTraitsType {

  /** Template argument typedef. */
  typedef typename TransientRCPtr<T>::value_type value_type;
  /** Template argument typedef. */
  typedef typename TransientRCPtr<T>::reference reference;
  /** Template argument typedef. */
  typedef typename TransientRCPtr<T>::const_reference const_reference;
  /** Template argument typedef. */
  typedef RCPtr<T> pointer;
  /** Template argument typedef. */
  typedef ConstRCPtr<T> const_pointer;
  /** Template argument typedef. */
  typedef TransientRCPtr<T> transient_pointer;
  /** Template argument typedef. */
  typedef TransientConstRCPtr<T> transient_const_pointer;

  /**
   * Return the bare pointer of the given pointer object.
   */
  static T * barePointer(const TransientRCPtr<T> & p) {
    return p.operator->();
  }

  /**
   * Destroy the object pointed to.
   */
  static void destroy(transient_pointer tp) {}

  /**
   * Cast dynamically.
   */
  template <typename UPtr>
  static transient_pointer DynamicCast(const UPtr & u) {
    transient_pointer t;
    t.assignDynamic(u);
    return t;
  }

  /**
   * Cast away constness.
   */
  static transient_pointer ConstCast(transient_const_pointer c) {
    transient_pointer t;
    t.assignConst(c);
    return t;
  }

  /**
   * Cast from a basic pointer.
   */
   static transient_pointer PtrCast(T * t) {
    return transient_pointer(t);
  }

  /**
   * TransientRCPtr is not reference counted.
   */
  static const bool reference_counted = false;

}; 

/**
 * Specialization of the PtrTraits class for TransientConstRCPtr.
 */
template <typename T>
struct PtrTraits< TransientConstRCPtr<T> >: public PtrTraitsType {

  /** Template argument typedef. */
  typedef typename TransientConstRCPtr<T>::value_type value_type;
  /** Template argument typedef. */
  typedef typename TransientConstRCPtr<T>::reference reference;
  /** Template argument typedef. */
  typedef typename TransientConstRCPtr<T>::const_reference const_reference;
  /** Template argument typedef. */
  typedef RCPtr<T> pointer;
  /** Template argument typedef. */
  typedef ConstRCPtr<T> const_pointer;
  /** Template argument typedef. */
  typedef TransientRCPtr<T> transient_pointer;
  /** Template argument typedef. */
  typedef TransientConstRCPtr<T> transient_const_pointer;

  /**
   * Return the bare pointer of the given pointer object.
   */
  static const T * barePointer(const TransientConstRCPtr<T> & p) {
    return p.operator->();
  }

  /**
   * Destroy the object pointed to.
   */
  static void destroy(transient_const_pointer tp) {}

  /**
   * Cast dynamically.
   */
  template <typename UPtr>
  static transient_const_pointer DynamicCast(const UPtr & u) {
    transient_const_pointer t;
    t.assignDynamic(u);
    return t;
  }

  /**
   * Cast away constness.
   */
  template <typename UPtr>
  static transient_const_pointer ConstCast(const UPtr & u) {
    transient_const_pointer t;
    t.assignConst(u);
    return t;
  }

  /**
   * Cast from a basic pointer.
   */
  static transient_const_pointer PtrCast(const T * t) {
    return transient_const_pointer(t);
  }

  /**
   * TransientConstRCPtr is not reference counted.
   */
  static const bool reference_counted = false;

}; 

}
}

namespace std {

/**
 * Specialization of std::swap to avoid unnecessary (in/de)crements of
 * the reference count.
 */
template <typename T>
void swap(ThePEG::Pointer::RCPtr<T> &, ThePEG::Pointer::RCPtr<T> &);

/**
 * Specialization of std::swap to avoid unnecessary (in/de)crements of
 * the reference count.
 */
template <typename T>
void swap(ThePEG::Pointer::ConstRCPtr<T> &,
	       ThePEG::Pointer::ConstRCPtr<T> &);

}

#include "RCPtr.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RCPtr.tcc"
#endif

#endif /* ThePEG_RCPtr_H */
