// -*- C++ -*-
//
#ifndef ThePEG_VSelector_H
#define ThePEG_VSelector_H
//
// This is the definition of the <B><TT>ThePEG::VSelector</TT></B> class.
//
// <B><TT>VSelector</TT></B> is a templated class for storing objects
// associated with probabilities in a way such that, given a random
// number between 0 and 1, an object can be selected according to its
// relative probability. Internally, the objects of class
// <B><TT>T</TT></B> are stored in an
// <B><TT>std::map&lt;double,T&gt;</TT></B> where the key is the
// probability of the corresponding object plus the accumulated sum of
// probabilities of all objects before the current one in the
// map. This allows for fast retreival of an object according to its
// probability. Where fast means that the time increases as a
// logarithm of the number of objects in the selector.
//
// CLASSDOC SUBSECTION Usage:
//
// <B><TT>double random();</TT></B> // A random generator returning a
// number between 0 and 1.<BR>
// <B><TT>class foo;</TT></B> // A class which can be used in std::map.<BR>
// <B><TT>VSelector&lt;foo*&gt; bar;</TT></B> // A selector.<BR>
// <B><TT>foo f1, f2;</TT></B> <BR>
// <B><TT>bar.insert(0.5,&f1)</TT></B> // assign probability 0.5<BR>
// <B><TT>bar.insert(0.5,&f2)</TT></B> // to each of f1 and f2<BR>
// <B><TT>foo * f = bar.select(random())</TT></B> // randomly returns
// a pointer to f1 or f2<BR>
//
// CLASSDOC SUBSECTION Author:
//
// Leif L&ouml;nnblad
//

#include "ThePEG/Config/ThePEG.h"
#include <stdexcept>
#include <algorithm>
#include <stdexcept>

namespace ThePEG {

template <typename T, typename WeightType = double>
class VSelector {

public:

  typedef vector<WeightType> WeightVector;
  typedef typename WeightVector::const_iterator WIterator;
  typedef vector<T> ObjectVector;
  typedef typename ObjectVector::iterator iterator;
  typedef typename ObjectVector::const_iterator const_iterator;
  typedef typename ObjectVector::size_type size_type;

public:

  inline VSelector(size_type reserved = 0);
  inline VSelector(const VSelector &);
  // Trivial constructors.

  inline ~VSelector();
  // Trivial destructor.

  inline const VSelector & operator = (const VSelector &);
  // Trivial assignment.

  inline void swap(VSelector &);
  // Trivial swap.

  inline WeightType insert(WeightType, const T &);
  // Insert an object given a probability for this object. If the
  // probability is zero or negative, the object will not be inserted
  // and the probability itself is returned. Otherwise the sum of
  // probabilities is returned.

  WeightType reweight(WeightType, const T &);
  // Reweight an object previously inserted giving it a new weight. If
  // several equivalent objects exists, all of them will be
  // reweighted.

  WeightType erase(const T &);
  // Erase an object, previously inserted. If the object had not been
  // inserted, nothing will happen. If several copies of the object
  // has been inserted, all will be removed removed. In all cases the
  // sum of probabilities is returned.

  void replace(const T & told, const T & tnew);
  // Replace all occurencies of told with tnew without changing the
  // probability for the entry.

  T & select(double rnd, double * remainder = 0) throw(range_error);
  inline T & operator[](double rnd) throw(range_error);
  const T & select(double rnd, double * remainder = 0) const throw(range_error);
  inline const T & operator[](double rnd) const throw(range_error);
  // Given a random number flatly distributed in ]0,1[ Select an
  // object according to the individual probabilities specified when
  // they were inserted. If rnd <= 0 or if rnd >= 1 or the VSelector is
  // empty, a range_error will be thrown. There is one const and one
  // non-const version. operator[](rnd) is just an alias for
  // select(rnd).

  template <typename RNDGEN>
  inline T & select(RNDGEN & rnd) throw(range_error);
  template <typename RNDGEN>
  inline const T & select(RNDGEN & rnd) const throw(range_error);
  // Same as above but give the actual random generator which should
  // be able to push_back unused values.

  inline WeightType sum() const;
  // Return the sum of probabilities of the objects inserted. Note
  // that probabilities specified when objects are inserted are
  // rescaled with this number to give unit probability for
  // 'select()'.

  inline const_iterator begin() const;
  inline const_iterator end() const;
  // Access to the first and last iterator in the underlying
  // vector of objects.

  inline bool empty() const;
  // Returns true if the VSelector is empty.

  inline size_type size() const;
  // Returns the number of objects in the selector.

  inline void reserve(size_type reserved);
  // Allocate space for a number of objects in the underlying vectors.

  inline void clear();
  // Erases all objects.

  template <typename OStream>
  void output(OStream &) const;

  template <typename IStream>
  void input(IStream &);

protected:

  size_type iselect(double rnd, double * remainder) const throw(range_error);
  // Internal selection engine.

private:

  WeightVector theSums;
  // The vector of accumulated weights for the objects in the selector

  WeightVector theWeights;
  // The vector of weights for the objects in the selector

  ObjectVector theObjects;
  // The vector of objects in the selector.

  WeightType theSum;
  // The sum of all weights.

};

template <typename OStream, typename T, typename WeightType>
inline OStream & operator<<(OStream &, const VSelector<T,WeightType> &);

template <typename IStream, typename T, typename WeightType>
inline IStream & operator>>(IStream &, VSelector<T,WeightType> &);


}

#include "VSelector.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "VSelector.tcc"
#endif

#endif /* ThePEG_VSelector_H */
