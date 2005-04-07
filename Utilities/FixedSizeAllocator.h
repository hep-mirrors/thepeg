// -*- C++ -*-
#ifndef ThePEG_FixedSizeAllocator_H
#define ThePEG_FixedSizeAllocator_H
// This is the declaration of the FixedSizeAllocator class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Debug.h"
// #include "FixedSizeAllocator.fh"
// #include "FixedSizeAllocator.xh"
#include <memory>

namespace ThePEG {

/**
 * FixedSizeAllocator is a class for fast allocattion and deallocation
 * of objects with a fixed size. It keeps a list of pre-allocated
 * memory in portions determined by <code>ChunkSize</code>. When an
 * object is deallocated the corresponding memory will be used the
 * next time an object of the same size is allocated. Rather than
 * using FixedSizeAllocator directly, it is advisable to use
 * FixedAllocator to avoid allocating objects across even word
 * boundaries. If the macro <code>ThePEG_USE_STD_ALLOCATORS</code> is
 * defined the default allocator of the platform is used instead.
 */
template <size_t Size, size_t ChunkSize = 1000>
class FixedSizeAllocator {

  /** A vector of raw memory locations. */
  typedef std::vector<void *> FreeStack;

public:

  /** Allocate memory of size <code>Size</code>. Will reuse previously
   *  deallocated memory if available. */
  inline static void * allocate();

  /** Deallocate memory previously allocated by this class. */
  inline static void deallocate(void *);

private:

  /** Increase the pre-allocated memory. */
  inline static void grow();

  /** Allocate memory of size <code>Size</code>. Do not reuse previously
   *  deallocated memory */
  inline static void * newallocate();

  /** Helper class representing a stack of pre-allocated memory */
  struct ChunkStack {
    /** The underlying stack type. */
    typedef vector<char *> Stack;
    /** The destructor. */
    inline ~ChunkStack();
    /** The stack. */
    Stack s;
  };

  /** The stack of pre-allocated memory. */
  static ChunkStack chunkstack;

  /** A stack of memory locations available for reuse. */
  static FreeStack freestack;

  /** The pointer to the last allocated memory. */
  static size_t last;

};

/** Helper class to enable FixedSizeAllocator to allocate on even word
 *  boundaries. */
template <typename T>
struct SizeOf8 {
  /** The size of type T rounded up to even 8 bytes. */
  static const size_t size = sizeof(double)*(1+(sizeof(T)-1)/sizeof(double));
};

/**
 * Inherits from FixedSizeAllocator with the size adjusted to allocate
 * on even word boundaries.
 */
template <typename T, size_t ChunkSize = 1000>
struct FixedAllocator: public FixedSizeAllocator<SizeOf8<T>::size, ChunkSize> {

public:

  /** Alias for the base class. */
  typedef FixedSizeAllocator<SizeOf8<T>::size, ChunkSize> BaseType;

  /** Allocate memory of size <code>Size</code>. Will reuse previously
   *  deallocated memory if available. */
  inline static T * allocate();

};

/**
 * A standard compliant allocator class using FixedAllocator. Note
 * that only single allocations are handles by
 * FixedAllocator. Allocation of arrays is still handled by the
 * default allocator used as fallback.
 */
template <typename T>
class Allocator {

public:

  /** @name Standard typedefs inherited from the fallback allocator. */
  //@{
  /** The fall back allocator class. */
  typedef std::allocator<T> BaseAllocator;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::size_type size_type;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::difference_type difference_type;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::pointer pointer;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::const_pointer const_pointer;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::reference reference;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::const_reference const_reference;
  /** Forward typedef from the fall back allocator class. */
  typedef typename BaseAllocator::value_type value_type;
  //@}

  /** Standard rebind construction. */
  template <typename T1> struct rebind {
    /** The corresponding allocator class. */
    typedef Allocator<T1> other;
  };

public:

  /** Default constructor. */
  Allocator() throw() {}

  /** Copy constructor. */
  Allocator(const Allocator & x) throw()
    : fallback(x.fallback) {}

  /** Copy constructor for allocator templated on another class. */
  template <typename T1> Allocator(const Allocator<T1> & x) throw()
    : fallback(x.fallback) {}

  /** The destructor. */
  ~Allocator() throw() {}

  /** Get a pointer to a given object. */
  pointer address(reference x) const {
    return fallback.address(x);
  }

  /** Get a const pointer to a given object. */
  const_pointer address(const_reference x) const {
    return fallback.address(x);
  }

  /** Allocate memory for objects. The objects are not constructed.
   * @param n the number of objects to allocate. If larger than one,
   * the fallback allocator will be used.
   * @param vp unused.
   */
  inline T* allocate(size_type n, const void * vp = 0);

  /** Deallocate n objects in the area pointed to by p. The objects
   *  must be destroyed before. */
  inline void deallocate(pointer p, size_type n);

  /** The maximum number of objects which can be allocated. */
  size_type max_size() const throw() { return fallback.max_size(); }

  /** Construct an object previously allocated with allocate(). */
  void construct(pointer p, const T & val) { fallback.construct(p, val); }

  /** Destroy an object to be deallocated by deallocate(). */
  void destroy(pointer p) { fallback.destroy(p); }

public:

  /** The fallback allocator used for allocation of arrays. */
  BaseAllocator fallback;

};

}



// #include "FixedSizeAllocator.tcc"
#include "FixedSizeAllocator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#endif

#endif /* ThePEG_FixedSizeAllocator_H */
