// -*- C++ -*-
#ifndef ThePEG_VSelector_H
#define ThePEG_VSelector_H
// This is the definition of the ThePEG::VSelector class.

#include "ThePEG/Config/ThePEG.h"
#include <stdexcept>
#include <algorithm>
#include <stdexcept>

namespace ThePEG {

template <typename T, typename WeightType = double>
/**
 * VSelector is a templated class for storing objects associated with
 * probabilities in a way such that, given a flat random number
 * between 0 and 1, an object can be selected according to its
 * relative probability. Internally, the objects of class
 * <code>T</code> are stored in a vector parallel to a vector of the
 * probability of the corresponding object plus the accumulated sum of
 * probabilities of all objects before the current one in the
 * vector. This allows for fast retreival of an object according to
 * its probability. Where fast means that the time increases as a
 * logarithm of the number of objects in the selector.
 *
 * Here is an example on how to use the class:<br>
 * <code>double random();</code> // A random generator returning a
 * number between 0 and 1.<br>
 * <code>class foo;</code>  // Any class.<BR>
 * <code>VSelector<foo*> bar;</code>  // A selector.<BR>
 * <code>foo f1, f2;</code> <BR>
 * <code>bar.insert(0.5,&f1)</code>  // assign probability 0.5<BR>
 * <code>bar.insert(0.5,&f2)</code>  // to each of f1 and f2<BR>
 * <code>foo * f = bar.select(random())</code>  // randomly returns
 * a pointer to f1 or f2<BR>
 *
 * @see Selector
 */
class VSelector {

public:

  /** A vector of weights. */
  typedef vector<WeightType> WeightVector;

  /** The weight vector iterator type. */
  typedef typename WeightVector::const_iterator WIterator;

  /** A vector ob objects. */
  typedef vector<T> ObjectVector;

  /** The object vector iterator type. */
  typedef typename ObjectVector::iterator iterator;

  /** The object vector const iterator type. */
  typedef typename ObjectVector::const_iterator const_iterator;

  /** Size type of the underlying vector. */
  typedef typename ObjectVector::size_type size_type;

public:

  /**
   * Default constructor.
   */
  inline VSelector(size_type reserved = 0);

  /**
   * Copy constructor.
   */
  inline VSelector(const VSelector &);

  /**
   * Destructor.
   */
  inline ~VSelector();

  /**
   * Assignment.
   */
  inline const VSelector & operator = (const VSelector &);

  /**
   * Swap the underlying representation with the argument.
   */
  inline void swap(VSelector &);

  /**
   * Insert an object given a probability for this object. If the
   * probability is zero or negative, the object will not be inserted
   * and the probability itself is returned. Otherwise the sum of
   * probabilities is returned.
   */
  inline WeightType insert(WeightType, const T &);

  /**
   * Reweight an object previously inserted giving it a new weight. If
   * several equivalent objects exists, all of them will be
   * reweighted.
   */
  WeightType reweight(WeightType, const T &);

  /**
   * Erase an object, previously inserted. If the object had not been
   * inserted, nothing will happen. If several copies of the object
   * has been inserted, all will be removed removed. In all cases the
   * sum of probabilities is returned.
   */
  WeightType erase(const T &);

  /**
   * Replace all occurencies of told with tnew without changing the
   * probability for the entry.
   */
  void replace(const T & told, const T & tnew);

  /**
   * Select an object randomly. Given a random number flatly
   * distributed in the interval ]0,1[ Select an object according to
   * the individual probabilities specified when they were
   * inserted. If rnd <= 0 or if rnd >= 1 or the Selector is empty, a
   * range_error will be thrown.
   * @param rnd a flat random number in the interval ]0,1[
   * @param remainder if non-zero the double pointed to will be set to
   * a uniform random number in the interval ]0,1[ calculated from the
   * fraction of rnd which was in the range of the selected object.
   */
  T & select(double rnd, double * remainder = 0) throw(range_error);

  /**
   * Selct an object randomly. Given a random number flatly
   * distributed in the interval ]0,1[ Select an object according to
   * the individual probabilities specified when they were
   * inserted. If rnd <= 0 or if rnd >= 1 or the Selector is empty, a
   * range_error will be thrown.
   */
  inline T & operator[](double rnd) throw(range_error);

  /**
   * Selct an object randomly. Given a random number flatly
   * distributed in the interval ]0,1[ Select an object according to
   * the individual probabilities specified when they were
   * inserted. If rnd <= 0 or if rnd >= 1 or the Selector is empty, a
   * range_error will be thrown.
   * @param rnd a flat random number in the interval ]0,1[
   * @param remainder if non-zero the double pointed to will be set to
   * a uniform random number in the interval ]0,1[ calculated from the
   * fraction of rnd which was in the range of the selected object.
   */
  const T & select(double rnd, double * remainder = 0) const throw(range_error);

  /**
   * Selct an object randomly. Given a random number flatly
   * distributed in the interval ]0,1[ select an object according to
   * the individual probabilities specified when they were
   * inserted. If rnd <= 0 or if rnd >= 1 or the Selector is empty, a
   * range_error will be thrown.
   */
  inline const T & operator[](double rnd) const throw(range_error);

  /**
   * Selct an object randomly. Given a random number generator which
   * generates flat random numbers in the interval ]0,1[ with the
   * <code>operator()()</code> function, select an object according to
   * the individual probabilities specified when they were
   * inserted. If the generated number is outside the allowed range or
   * the Selector is empty, a range_error will be thrown. The
   * generator should have a push_back function which will be used
   * push back a uniform random number in the interval ]0,1[
   * calculated from the fraction of rnd which was in the range of the
   * selected object.
   */
  template <typename RNDGEN>
  inline T & select(RNDGEN & rnd) throw(range_error);

  /**
   * Selct an object randomly. Given a random number generator which
   * generates flat random numbers in the interval ]0,1[ with the
   * <code>operator()()</code> function, select an object according to
   * the individual probabilities specified when they were
   * inserted. If the generated number is outside the allowed range or
   * the Selector is empty, a range_error will be thrown. The
   * generator should have a push_back function which will be used
   * push back a uniform random number in the interval ]0,1[
   * calculated from the fraction of rnd which was in the range of the
   * selected object.
   */
  template <typename RNDGEN>
  inline const T & select(RNDGEN & rnd) const throw(range_error);

  /**
   * Return the sum of probabilities of the objects inserted. Note
   * that probabilities specified when objects are inserted are
   * rescaled with this number to give unit probability for
   * 'select()'.
   */
  inline WeightType sum() const;

  /**
   * Access to the <code>begin()</code> iterator of the underlying
   * vector of objects.
   */
  inline const_iterator begin() const;

  /**
   * Access to the <code>end()</code> iterator in the underlying
   * vector of objects.
   */
  inline const_iterator end() const;

  /**
   * Returns true if the VSelector is empty.
   */
  inline bool empty() const;

  /**
   * Returns the number of objects in the selector.
   */
  inline size_type size() const;

  /**
   * Allocate space for a number of objects in the underlying vectors.
   */
  inline void reserve(size_type reserved);

  /**
   * Erases all objects.
   */
  inline void clear();

  /**
   * Output to a stream.
   */
  template <typename OStream>
  void output(OStream &) const;

  /**
   * Input from a stream.
   */
  template <typename IStream>
  void input(IStream &);

protected:

  /**
   * Internal selection engine.
   */
  size_type iselect(double rnd, double * remainder) const throw(range_error);

private:

  /**
   * The vector of accumulated weights for the objects in the selector
   */
  WeightVector theSums;

  /**
   * The vector of weights for the objects in the selector
   */
  WeightVector theWeights;

  /**
   * The vector of objects in the selector.
   */
  ObjectVector theObjects;

  /**
   * The sum of all weights.
   */
  WeightType theSum;

};

/**
 * Output a VSelector to a stream.
 */
template <typename OStream, typename T, typename WeightType>
inline OStream & operator<<(OStream &, const VSelector<T,WeightType> &);

/**
 * Input a VSelector from a stream.
 */
template <typename IStream, typename T, typename WeightType>
inline IStream & operator>>(IStream &, VSelector<T,WeightType> &);


}

#include "VSelector.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "VSelector.tcc"
#endif

#endif /* ThePEG_VSelector_H */
