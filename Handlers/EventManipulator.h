// -*- C++ -*-
#ifndef ThePEG_EventManipulator_H
#define ThePEG_EventManipulator_H
//
// This is the declaration of the <!id>EventManipulator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// An object of the <!id>EventManipulator<!!id> class may be assigned
// to a <!class>FullEventGenerator<!!class> object. The
// <!id>manipulate<!!id> method is called for each event generated,
// after the <!class>AnalysisHandler<!!class>s have been called, and
// may manipulate the event in any way needed. The manipulator may
// alseo add <!class>StepHandler<!!class>s to the
// <!class>EventHandler<!!class> which produced the event. The
// <!id>manipulate<!!id> method returns an integer which should be
// zero if nothing was done to the event. If the
// <!class>EventHandler<!!class> has steps left to do, these are
// performed, after which the <!class>AnalysisHandler<!!class>s are
// called with the return value from the previous
// <!id>manipulate<!!id> call. Then <!id>manipulate<!!id> is
// called again and the procedure is repeated until the
// <!class>EventHandler<!!class> has no more steps to do.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:FullEventGenerator.html">FullEventGenerator.h</a>
// <a href="http:AnalysisHandler.html">AnalysisHandler.h</a>
// <a href="http:EventHandler.html">EventHandler.h</a>
// <a href="http:StepHandler.html">StepHandler.h</a>
// 

#include "ThePEG/Interface/Interfaced.h"
#include <stdexcept>
// #include "EventManipulator.fh"
// #include "EventManipulator.xh"

namespace ThePEG {

class EventManipulator: public Interfaced {

public:

  inline EventManipulator();
  inline EventManipulator(const EventManipulator &);
  virtual ~EventManipulator();
  // Standard ctors and dtor

public:

  virtual int manipulate(tEHPtr, tEventPtr) = 0;
  // Manipulate an event and the event handler. Return zero if the
  // event was not manipulated.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static AbstractNoPIOClassDescription<EventManipulator> initEventManipulator;

  EventManipulator & operator=(const EventManipulator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<EventManipulator,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<EventManipulator>: public ClassTraitsBase<EventManipulator> {
  static string className() {  return "/ThePEG/EventManipulator"; }
};

}

#include "EventManipulator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "EventManipulator.tcc"
#endif

#endif /* ThePEG_EventManipulator_H */
