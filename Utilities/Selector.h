// -*- C++ -*-
#ifndef ThePEG_Selector_H
#define ThePEG_Selector_H
// This is the declaration of the Selector class.

#include "ThePEG/Config/ThePEG.h"
#include <stdexcept>
#include <algorithm>
#include <stdexcept>

namespace ThePEG {

/**
 * Selector is a templated class for storing objects associated with
 * probabilities in a way such that, given a flat random number
 * between 0 and 1, an object can be selected according to its
 * relative probability. Internally, the objects of class
 * <code>T</code> are stored in a map where the key is the
 * probability of the corresponding object plus the accumulated sum of
 * probabilities of all objects before the current one in the
 * map. This allows for fast retreival of an object according to its
 * probability. Where fast means that the time increases as a
 * logarithm of the number of objects in the selector.
 *
 * Here is an example on how to use the class:<br>
 * <code>double random();</code> // A random generator returning a
 * number between 0 and 1.<br>
 * <code>class foo;</code>  // Any class.<BR>
 * <code>Selector<foo*> bar;</code>  // A selector.<BR>
 * <code>foo f1, f2;</code> <BR>
 * <code>bar.insert(0.5,&f1)</code>  // assign probability 0.5<BR>
 * <code>bar.insert(0.5,&f2)</code>  // to each of f1 and f2<BR>
 * <code>foo * f = bar.select(random())</code>  // randomly returns
 * a pointer to f1 or f2<BR>
 *
 * @see VSelector
 */
template <typename T, typename WeightType = double>
class Selector {

public:

  /** Map doubles to objects. */
  typedef map<WeightType, T, less<WeightType>,
    Allocator<std::pair<WeightType const, T> > > MapType;

  /** Iterator corresponding to the underlying map. */
  typedef typename MapType::const_iterator const_iterator;

  /** Iterator corresponding to the underlying map. */
  typedef typename MapType::iterator iterator;

  /** Size type of the underlying map. */
  typedef typename MapType::size_type size_type;

public:

  /**
   * Default constructor.
   */
  inline Selector();

  /**
   * Copy constructor.
   */
  inline Selector(const Selector &);

  /**
   * Destructor.
   */
  inline ~Selector();

  /**
   * Assignment.
   */
  inline const Selector & operator = (const Selector &);

  /**
   * Swap the underlying representation with the argument.
   */
  inline void swap(Selector &);

  /**
   * Insert an object given a probability for this object. If the
   * probability is zero or negative, the object will not be inserted
   * and the probability itself is returned. Otherwise the sum of
   * probabilities so far is returned.
   */
  inline WeightType insert(WeightType, const T &);

  /**
   * Reweight an object previously inserted giving it a new
   * weight. Semantically <code>reweight(w,o);</code> is equivalent to
   * <code>erase(o); insert(w,o);</code>
   */
  inline WeightType reweight(WeightType, const T &);

  /**
   * Erase an object, previously inserted. If the object had not been
   * inserted, nothing will happen. If several copies of the object
   * has been inserted, all will be removed removed. In all cases the
   * sum of the remaining probabilities is returned.
   */
  WeightType erase(const T &);

  /**
   * Replace all occurencies of oldObject with newObject without
   * changing the probability for the entry.
   */
  void replace(const T & oldObject, const T & newObject);

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
   * map. Dereferenced, it will give a std::pair<WeightType, T>, where
   * 'first' is the sum of all probabilities up to this one, and
   * 'second' is the object inserted.
   */
  inline const_iterator begin() const;

  /**
   * Access to the <code>end()</code> iterator in the underlying
   * map.
   */
  inline const_iterator end() const;

  /**
   * Returns true if the Selector is empty.
   */
  inline bool empty() const;

  /**
   * Returns the number of objects in the selector.
   */
  inline size_type size() const;

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

private:

  /**
   * The underlying map relating sums of probabilities to inserted objects.
   */
  MapType theMap;

  /**
   * The sum of all probabilities assicialted with inserted objects.
   */
  WeightType theSum;

};

/**
 * Output a Selector to a stream.
 */
template <typename OStream, typename T, typename WeightType>
inline OStream & operator<<(OStream &, const Selector<T,WeightType> &);

/**
 * Input a Selector from a stream.
 */
template <typename IStream, typename T, typename WeightType>
inline IStream & operator>>(IStream &, Selector<T,WeightType> &);


}

#include "Selector.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Selector.tcc"
#endif

#endif /* ThePEG_Selector_H */
