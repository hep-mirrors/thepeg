// -*- C++ -*-
#ifndef ThePEG_CurrentGenerator_H
#define ThePEG_CurrentGenerator_H
//
// This is the declaration of the <!id>CurrentGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This <!id>CurrentGenerator<!!id> class keeps a static stack of
// <!class>EventGenerator<!!class>a which can be used anywhere by any
// class. When an <!class>EventGenerator<!!class> is initialized or
// run it adds itself to the stack which can be used by any other
// object being initialized or run through the static functions of the
// <!id>CurrentGenerator<!!id> class. If someone needs to use an
// alternative <!class>EventGenerator<!!class> object a new
// <!id>CurrentGenerator<!!id> object can be constructed with a
// pointer to the desired <!class>RandomGenerator<!!class> objectas
// argument and that object will the be used by the static
// <!id>CurrentGenerator<!!id> functions until the
// <!id>CurrentGenerator<!!id> is destructed.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>.
// 

#include "ThePEG/Repository/EventGenerator.h"
#include "CurrentGenerator.fh"
// #include "CurrentGenerator.xh"

namespace ThePEG {

class CurrentGenerator {

public:

  inline CurrentGenerator();
  inline CurrentGenerator(const CurrentGenerator &);
  // Standard constructors do nothing.

  inline CurrentGenerator(const EGPtr & r);
  // Construct a new object specifying a new EventGenerator to be
  // used during this objects lifetime

  inline ~CurrentGenerator();
  // The destructor removing the EventGenerator specified in the
  // constructor from the stack.

public:

  inline static bool isVoid();
  // Returns true if there is no currently chosen EventGenerator
  // object.

  inline static EventGenerator & current();
  // Return a reference to the currently chosen EventGenerator object.

  inline static tSMPtr standardModel();
  // Return a pointer to the standard model parameters used by the
  // current generator.

  inline static tStrategyPtr strategy();
  // Return a pointer to the strategy object containing a set of
  // non-default particles to be used by the
  // current generator.

  static ostream & out();
  static ostream & log();
  static ostream & ref();
  // Return references to the streams connected to the files for
  // general output, logging information and references from used
  // objects of the current generator. If no file is connected, the
  // BaseRepository::cout(), BaseRepository::clog() and
  // BaseRepository::cout() will be used instead.

  template <typename T>
  inline static typename Ptr<T>::pointer getPtr(const T &);
  // Return a garbage collected pointer to a given object in the
  // current EventGenerator. If the object is not found, a null
  // pointer will be returned.

  inline static IBPtr getPointer(string name);
  // Return a pointer to an object present in the current
  // EventGenerator given its full name. Return the null pointer if
  // non-existent.

  template <typename T>
  inline static typename Ptr<T>::pointer getObject(string name);
  // Return a pointer to an object of type T present in the current
  // EventGenerator given its full name. Return the null pointer if
  // non-existent.

  template <typename T>
  inline static typename Ptr<T>::pointer getDefault();
  // Return the default object for class T in the current
  // EventGenerator. Returns the null pointer if non-existent.

  inline static RandomGenerator & random();
  // Return a reference to the default RandomGenerator object in the current
  // EventGenerator.

  inline static RandomEngine & randomEngine();
  // Return a reference to the RandomEngine object used in the default
  // RandomGenerator object in the current EventGenerator.

private:

  static vector<EGPtr> theGeneratorStack;
  // The stack of RandomGenerators requested.

  bool generatorPushed;
  // True if this object is responsible for pushing a RandomGenerator
  // onto the stack.

private:

  CurrentGenerator & operator=(const CurrentGenerator &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

#include "CurrentGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "CurrentGenerator.tcc"
#endif

#endif /* ThePEG_CurrentGenerator_H */
