// -*- C++ -*-
#ifndef THEPEG_Main_H
#define THEPEG_Main_H
//
// This is the declaration of the <!id>Main<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This is a base class for classes implementing a main steering
// routine for running an EventGenerator, in case the standard 'go()'
// function in the EventGenerator is not enough. An example is a
// PartialEventGenerator where the class deriving from Main specifies
// an initial set of partons which should be cascaded and hadronized
// etc.
//
// The derived class will be dynamically loaded by the standard
// runThePEG and the static Init() function will be run. The loaded
// EventGenerator will then be available in the static
// 'eventGenerator()' function. In addition the number of events
// requested from the command line will be available from the 'N()'
// function. All other command-line arguments will be available from
// the 'arguments()' function.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Repository/EventGenerator.h"
// #include "Main.fh"
// #include "Main.xh"

namespace ThePEG {

class Main: public Base {

public:

  inline Main();
  inline Main(const Main &);
  virtual ~Main();
  // Standard ctors and dtor.

public:

  static inline void eventGenerator(tEGPtr);
  static inline tEGPtr eventGenerator();
  // The global event generator.

  static inline void N(long); 
  static inline long N(); 
  // The number of events requested.

  static inline void arguments(const vector<string> &);
  static inline const vector<string> & arguments();
  // The command-line arguments.

public:

  static void Init();
  // Standard Init function used to initialize the interfaces.

private:

  static EGPtr theEventGenerator;
  // The global event generator.

  static long theN;
  // The number of events requested.

  static vector<string> theArguments;
  // The command-line arguments.

private:

  static AbstractNoPIOClassDescription<Main> initMain;
  // Describe an abstract base class without persistent data.

  Main & operator=(const Main &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of Main.
template <>
struct BaseClassTrait<Main,1> {
  typedef int NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<Main>
  : public ClassTraitsBase<Main> {
  static string className() { return "ThePEG::Main"; }
  // Return the class name.
};

}

#include "Main.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Main.tcc"
#endif

#endif /* THEPEG_Main_H */
