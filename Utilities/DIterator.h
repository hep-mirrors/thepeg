// -*- C++ -*-
#ifndef ThePEG_DIterator_H
#define ThePEG_DIterator_H
//
// This is the declaration of the <!id>DIterator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>DIterator<!!id> is an iterator adaptor class. It can be used
// whenever one has a container with pointers to facilitate member
// selection. The only requirement is that the underlying pointer is
// pointing to a valid object. Given e.g. a vector of pointers,
// <!id>vector<A*> pv<!!id>, it can be used as follows:
// 
// <!id>typedef DIterator<vector<A*>::iterator It;<!!id><BR> <!id>for
// ( It i = dv.begin(), i != dv.end(), ++i )
// i->dosomething();<!!id><BR>
// 

#include <iterator>

namespace ThePEG {

template <typename BaseIterator>
class DIterator {

public:

  typedef std::iterator_traits<BaseIterator>  	Traits;
  typedef typename Traits::iterator_category 	iterator_category;
  typedef typename Traits::difference_type 	difference_type;
  typedef typename Traits::value_type 		PtrType;
  typedef std::iterator_traits<PtrType>         PtrTraits;
  typedef typename PtrTraits::value_type 	value_type;
  typedef typename PtrTraits::pointer          	pointer;
  typedef typename PtrTraits::reference         reference;

public:

  DIterator(const BaseIterator & in): i(in) {}
  DIterator(const DIterator & pi): i(pi.i) {}
    
public:

  reference operator*() const { return **i; }
  pointer operator->() const { return *i; }

  DIterator & operator=(const DIterator & pi) { i = pi.i; return *this; }
  DIterator & operator=(const BaseIterator & pi) { i = pi; return *this; }

  DIterator & operator++() { ++i; return *this; }
  DIterator operator++(int) { DIterator tmp(*this); ++i; return tmp; }
  DIterator & operator--() { --i; return *this; }
  DIterator operator--(int) { DIterator tmp(*this); --i; return tmp; }

  reference operator[](difference_type n) { return *(i[n]); }

  DIterator & operator+=(int n) { i += n; return *this; }
  DIterator operator+(int n) { return DIterator(i + n); }
  DIterator & operator-=(int n) { i -= n; return *this; }
  DIterator operator-(int n) { return DIterator(i - n); }

  int operator-(const DIterator & pi) { return i - pi.i; }

  bool operator==(const DIterator & pi) { return i == pi.i; }
  bool operator!=(const DIterator & pi) { return i != pi.i; }
  bool operator<(const DIterator & pi) { return i < pi.i; }
  bool operator>(const DIterator & pi) { return i > pi.i; }
  bool operator<=(const DIterator & pi) { return i <= pi.i; }
  bool operator>=(const DIterator & pi) { return i >= pi.i; }
  bool operator==(const BaseIterator & bi) { return i == bi; }
  bool operator!=(const BaseIterator & bi) { return i != bi; }
  bool operator<(const BaseIterator & bi) { return i < bi; }
  bool operator>(const BaseIterator & bi) { return i > bi; }
  bool operator<=(const BaseIterator & bi) { return i <= bi; }
  bool operator>=(const BaseIterator & bi) { return i >= bi; }

private:

  BaseIterator i;

private:

  DIterator() {}

};

}

#endif /* ThePEG_DIterator_H */
