// -*- C++ -*-
#ifndef ThePEG_Rebinder_H
#define ThePEG_Rebinder_H

#include "ThePEG/Config/ThePEG.h"
#include "Rebinder.fh"
#include <stdexcept>
// #include "Rebinder.xh"

namespace ThePEG {

/**
 * Rebinder is a class associating pairs of pointers to objects. It is
 * typically used when cloning a set of objects which have pointers to
 * eachother. The Rebinder is then set up so that a cloned object can
 * easily be retrieved given a pointer to the original one. The cloned
 * objects can then use the Rebinder to change their pointers so that
 * they henceforth points to the cloned copies.
 */
template <typename T>
class Rebinder {

public:

  ThePEG_DECLARE_TEMPLATE_POINTERS(T,TPtr);

  /** Map associating pairs of objects. */
  typedef map<cTPtr,TPtr> MapType;

  /** The iterator of the underlying map. */
  typedef typename MapType::const_iterator const_iterator;

public:

  /** Default constructor. */
  inline Rebinder();

public:

  /**
   * Return a pointer to the object associated with the argument.
   */
  inline TPtr & operator[](tcTPtr);

  /**
   * Return a pointer to the object associated with the argument. If
   * no corresponding object is found a null pointer given by R() is
   * returned.
   * @param r a pointer to an object of a type which is derived from T.
   */
  template <typename R>
  inline R translate(const R & r) const;

  /**
   * Insert pointers to objects into the output iterator, pointers to
   * objects corresponding to the ones given by the range of input
   * iterators. If a given object in the input iterator range does not
   * exists, a null pointer will be inserted in the output iterator.
   */
  template <typename OutputIterator, typename InputIterator>
  inline void translate(OutputIterator ouptut,
			InputIterator first, InputIterator last) const;

  /**
   * Return a pointer to the object associated with the argument. If
   * no corresponding object is found an exception is thrown.
   * @param r a pointer to an object of a type which is derived from T.
   */
  template <typename R>
  inline R alwaysTranslate(const R & r) const throw(std::runtime_error);

  /**
   * Insert pointers to objects into the output iterator, pointers to
   * objects corresponding to the ones given by the range of input
   * iterators. If a given object in the input iterator range does not
   * exists, an exception will be thrown.
   */
  template <typename OutputIterator, typename InputIterator>
  inline void alwaysTranslate(OutputIterator, InputIterator, InputIterator)
    const throw(std::runtime_error);

  /**
   * Acces the underlying map representation.
   */
  inline const MapType & map() const;

private:


  /**
   * The underlying map representation.
   */
  MapType theMap;

private:

  /** The copy constructor is private and not implemented */
  inline Rebinder(const Rebinder &);

  /** The assignment operator is private and not implemented */
  inline Rebinder & operator=(const Rebinder &);

};


}

#include "Rebinder.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Rebinder.tcc"
#endif

#endif /* ThePEG_Rebinder_H */
