// -*- C++ -*-
#ifndef ThePEG_FullEventGenerator_H
#define ThePEG_FullEventGenerator_H
//
// This is the declaration of the <!id>FullEventGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>FullEventGenerator<!!id> inherits from the
// <!class>EventGenerator<!!class> class and has a pointer to an
// <!class>EventHandler<!!class> which is able to generate complete
// events. It also has a list of <!class>AnalysisHandler<!!class>s to
// perform analysis on the generated <!class>Event<!!class>s, and an
// <!class>EventManipulator<!!class> to externally manipulate the
// generated events.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:EventGenerator.html">EventGenerator.h</a>,
// <a href="http:EventHandler.html">EventHandler.h</a>,
// <a href="http:AnalysisHandler.html">AnalysisHandler.h</a>,
// <a href="http:Event.html">Event.h</a>,
// <a href="http:EventManipulator.html">EventManipulator.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Repository/EventGenerator.h"
// #include "FullEventGenerator.fh"
// #include "FullEventGenerator.xh"

namespace ThePEG {

class FullEventGenerator: public EventGenerator {

public:

  FullEventGenerator();
  FullEventGenerator(const FullEventGenerator &);
  virtual ~FullEventGenerator();
  // Standard ctors and dtor

public:

  virtual Energy maximumCMEnergy() const;
  // Return the maximum center of mass energy possible for an
  // event. Return zero if this is only a partial generator.

  inline tEHPtr eventHandler() const;
  // Return a pointer to the EventHandler.

  inline AnalysisVector & analysisHandlers();
  // Return the vector of analysis objects to be used in the run.

  inline tEvtManipPtr manipulator() const;

  virtual tcEventPtr currentEvent() const;
  // Return the event being generated.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual EventPtr doShoot();
  // Generate one event. 

  virtual EventPtr doPartialEvent(tEventPtr);
  // Finish generating an event constructed from the outside. 

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  virtual void doinitrun();
  virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  EHPtr theEventHandler;
  // Pointer to the event handler used to generate the indivudual
  // events.

  AnalysisVector theAnalysisHandlers;
  // A vector of all analysis handlers to be called after each event.

  EvtManipPtr theEventManipulator;
  // A pointer to an optional event manipulator object.

  int printEvent;
  // If the debug level is higher than 0, print the first 'printEvent'
  // events to the logfile.

  long dumpPeriod;
  // If the dubug level is higher than 0, dump the complete state of
  // this run to the default dump file every 'dumpPeriod' events.

  long debugEvent;
  // If the dubug level is higher than 0, step up to the highest debug
  // level befor 'debugEvent' event is performed.

private:

  static ClassDescription<FullEventGenerator> initFullEventGenerator;

  FullEventGenerator & operator=(const FullEventGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<FullEventGenerator,1> {
  typedef EventGenerator NthBase;
};

template <>
struct ClassTraits<FullEventGenerator>:
    public ClassTraitsBase<FullEventGenerator> {
  static string className() { return "/ThePEG/FullEventGenerator"; }
};

}

#include "FullEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FullEventGenerator.tcc"
#endif

#endif /* ThePEG_FullEventGenerator_H */
