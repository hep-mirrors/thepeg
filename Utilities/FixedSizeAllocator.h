// -*- C++ -*-
#ifndef ThePEG_FixedSizeAllocator_H
#define ThePEG_FixedSizeAllocator_H
//
// This is the declaration of the <!id>FixedSizeAllocator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Debug.h"
// #include "FixedSizeAllocator.fh"
// #include "FixedSizeAllocator.xh"

namespace ThePEG {

template <size_t Size, size_t ChunkSize = 1000>
class FixedSizeAllocator {

  typedef std::vector<void *> FreeStack;

public:

  inline static void * allocate();
  inline static void deallocate(void *);

private:

  inline static void grow();
  inline static void * newallocate();

  struct ChunkStack {
    typedef vector<char *> Stack;
    inline ~ChunkStack();
    Stack s;
  };


  static ChunkStack chunkstack;
  static FreeStack freestack;
  static size_t last;

};

template <typename T>
struct SizeOf8 {
  static const size_t size = sizeof(double)*(1+(sizeof(T)-1)/sizeof(double));
};

template <typename T, size_t ChunkSize = 1000>
struct FixedAllocator: public FixedSizeAllocator<SizeOf8<T>::size, ChunkSize> {

public:

  typedef FixedSizeAllocator<SizeOf8<T>::size, ChunkSize> BaseType;

  inline static T * allocate();

};

template <typename T>
class Allocator {

public:

  typedef std::allocator<T> BaseAllocator;
  typedef typename BaseAllocator::size_type size_type;
  typedef typename BaseAllocator::difference_type difference_type;
  typedef typename BaseAllocator::pointer pointer;
  typedef typename BaseAllocator::const_pointer const_pointer;
  typedef typename BaseAllocator::reference reference;
  typedef typename BaseAllocator::const_reference const_reference;
  typedef typename BaseAllocator::value_type value_type;

  template <class T1> struct rebind {
    typedef Allocator<T1> other;
  };

public:

  Allocator() throw() {}
  Allocator(const Allocator & x) throw()
    : fallback(x.fallback) {}
  template <class T1> Allocator(const Allocator<T1> & x) throw()
    : fallback(x.fallback) {}
  ~Allocator() throw() {}

  pointer address(reference x) const {
    return fallback.address(x);
  }
  const_pointer address(const_reference x) const {
    return fallback.address(x);
  }

  inline T* allocate(size_type n, const void * vp = 0);

  inline void deallocate(pointer p, size_type n);

  size_type max_size() const throw() { return fallback.max_size(); }

  void construct(pointer p, const T & val) { fallback.construct(p, val); }
  void destroy(pointer p) { fallback.destroy(val); }

public:

  BaseAllocator fallback;

};

}



#include "FixedSizeAllocator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FixedSizeAllocator.tcc"
#endif

#endif /* ThePEG_FixedSizeAllocator_H */
