// -*- C++ -*-
#ifndef ThePEG_EventHandler_H
#define ThePEG_EventHandler_H
//
// This is the declaration of the <!id>EventHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>EventHandler<!!id> class is the main class for handeling
// simple events without overlayed collisions. It is derived from the
// <!class>CollisionHandler<!!class> class and introduces a
// <!class>LuminosityFunction<!!class> to describe the momentum
// distribution of incoming particles.
//
// Besides the standard <!id>doinit<!!id> method, the
// <!id>EventHandler<!!id> needs to be separately initialized with the
// <!id>initialize<!!id> method. In the dofinish method statistics is
// written out to the <!class>EventGenerator<!!class>s default output
// file
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:CollisionHandler.html">CollisionHandler.h</a>
// <a href="http:LuminosityFunction.html">LuminosityFunction.h</a>
// <a href="http:EventGenerator.html">EventGenerator.h</a>
// <a href="http:Event.html">Event.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Handlers/CollisionHandler.h"
#include "ThePEG/Handlers/EventHandler.xh"
#include "ThePEG/Repository/Strategy.fh"
#include "ThePEG/Handlers/SamplerBase.fh"
#include <fstream>

namespace ThePEG {

class EventHandler: public CollisionHandler {

public:

public:

  EventHandler(const EventHandler &);
  EventHandler();
  ~EventHandler();
  // Standard ctors and dtor.

public:

  virtual void initialize();
  // Initialize this event handler and all that is needed to generate event.

  virtual void statistics(ostream &) const;
  // Write out accumulated statistics about intergrated cross sections
  // and stuff.

  virtual EventPtr generateEvent();
  virtual EventPtr continueEvent();
  // Generate an event.

  inline long maxLoop() const;
  // Return the maximum number attemts allowed to select a sub-process
  // for each event.

  inline int statLevel() const;
  // Controlls the amount of statistics written out after each run to
  // the EventGenerators .out file.

  inline bool weighted() const;
  // Return true if this event handler should produce weightes events

  inline bool compensating() const;
  // Returns true if we are compensating for weight larger than 1.

  inline const LuminosityFunction & lumiFn() const;
  // Access to the luminosity function.

  inline int lumiDim() const;
  // The number of phase space dimensions used by the luminosity
  // function.

  inline int nDim(int bin) const;
  // The number of dimensions of the basic phase space to generate
  // sub-processes in for a given bin.

  virtual CrossSection dSigDR(const vector<double> & r);
  // Return the cross section for the chosen phase space point.

public:

  virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods.

  inline LuminosityFunction & lumiFn();
  // Access to the luminosity function.

  void reject(double weight);
  // Reject a (partially) generated event.

  inline tSamplerPtr sampler();
  inline tcSamplerPtr sampler() const;
  // Return the sampler assigned to this event handler.

private:

  void lumiFn(LumiFnPtr);
  // Set the luminosity function

private:

  LumiFnPtr theLumiFn;
  // Pointer to the luminosity function.

  bool weightedEvents;
  // True if this event handler should produce weightes events

  long theMaxLoop;
  // The maximum number of attempts to select a sub-process allowed
  // per event.

  int theStatLevel;
  // Controlls the amount of statistics written out after each run to
  // the EventGenerators .out file.

  SamplerPtr theSampler;
  // The phase space sampler responsible for generating phase space
  // points according to the cross section given by this event
  // handler.

  int theLumiDim;
  // The number of phase space dimensions used by the luminosity
  // function.

  int theNDim;
  // The number of dimensions of the basic phase space to generate
  // sub-processes in.

  static ClassDescription<EventHandler> initEventHandler;
  // Standard Initialization object.

private:

  const EventHandler & operator=(const EventHandler &);
  // Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<EventHandler,1> {
  typedef CollisionHandler NthBase;
};

template <>
struct ClassTraits<EventHandler>: public ClassTraitsBase<EventHandler> {
  static string className() { return "/ThePEG/EventHandler"; }
};

}

#include "EventHandler.icc"

#endif /* ThePEG_EventHandler_H */
