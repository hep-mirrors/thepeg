// -*- C++ -*-
//
// CurrentGenerator.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_CurrentGenerator_H
#define ThePEG_CurrentGenerator_H
// This is the declaration of the CurrentGenerator class.

#include "ThePEG/Repository/EventGenerator.h"
#include "CurrentGenerator.fh"
// #include "CurrentGenerator.xh"

namespace ThePEG {

/**
 * This CurrentGenerator class keeps a static stack of EventGeneratora
 * which can be used anywhere by any class. When an EventGenerator is
 * initialized or run it adds itself to the stack which can be used by
 * any other object being initialized or run through the static
 * functions of the CurrentGenerator class. If someone
 * needs to use an alternative EventGenerator object a new
 * CurrentGenerator object can be constructed with a
 * pointer to the desired EventGenerator object as argument and that
 * object will the be used by the static CurrentGenerator
 * functions until the CurrentGenerator object is destructed.
 *
 * @see EventGenerator
 * 
 */
class CurrentGenerator {

public:

  /**
   * Default constructor does nothing.
   */
  inline CurrentGenerator();

  /**
   * Copy-constructor does nothing.
   */
  inline CurrentGenerator(const CurrentGenerator &);

  /**
   * Construct a new object specifying a new EventGenerator, \a eg, to
   * be used during this objects lifetime.
   */
  inline CurrentGenerator(const EGPtr & eg);

  /**
   * The destructor removing the EventGenerator specified in the
   * constructor from the stack.
   */
  inline ~CurrentGenerator();

public:

  /**
   * Returns true if there is no currently chosen EventGenerator
   * object.
   */
  inline static bool isVoid();

  /**
   * Return a reference to the currently chosen EventGenerator object.
   */
  inline static EventGenerator & current();

  /**
   * Return a pointer to the standard model parameters used by the
   * current generator.
   */
  inline static tSMPtr standardModel();

  /**
   * Return a pointer to the strategy object containing eg. a set of
   * non-default particles to be used by the current generator.
   */
  inline static tStrategyPtr strategy();

  /**
   * Get the current standard output stream. Return a reference to the
   * stream connected to the file for general output of the current
   * generator. If no file is connected, the BaseRepository::cout()
   * will be used instead.
   */
  static ostream & out();

  /**
   * Get the current standard log stream. Return a reference to the
   * stream connected to the file for logging information of the
   * current generator. If no file is connected, the
   * BaseRepository::clog() will be used instead.
   */
  static ostream & log();

  /**
   * Get the current standard ref stream. Return a reference to the
   * stream connected to the file for references from used objects of
   * the current generator. If no file is connected, the
   * BaseRepository::cout() will be used instead.
   */
  static ostream & ref();

  /**
   * Get object. Return a garbage collected pointer to a given object
   * in the current EventGenerator. If the object is not found, a null
   * pointer will be returned.
   */
  template <typename T>
  inline static typename Ptr<T>::pointer getPtr(const T &);

  /**
   * Get object. Return a pointer to an object present in the current
   * EventGenerator given its full name. Return the null pointer if
   * non-existent.
   */
  inline static IBPtr getPointer(string name);

  /**
   * Get object. Return a pointer to an object of type T present in
   * the current EventGenerator given its full name. Return the null
   * pointer if non-existent.
   */
  template <typename T>
  inline static typename Ptr<T>::pointer getObject(string name);

  /**
   * Get default object. Return the default object for class T in the
   * current EventGenerator. Returns the null pointer if non-existent.
   */
  template <typename T>
  inline static typename Ptr<T>::pointer getDefault();

private:

  /**
   * The stack of RandomGenerators requested.
   */
  static vector<EGPtr> theGeneratorStack;

  /**
   * True if this object is responsible for pushing a RandomGenerator
   * onto the stack.
   */
  bool generatorPushed;

private:

  /**
   *  Private and non-existent assignment operator.
   */
  CurrentGenerator & operator=(const CurrentGenerator &);

};

}


#include "CurrentGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CurrentGenerator.tcc"
#endif

#endif /* ThePEG_CurrentGenerator_H */
