// -*- C++ -*-
#ifndef ThePEG_Timer_H
#define ThePEG_Timer_H
//
// This is the declaration of the <!id>Timer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Timer<!!id> class is used to time functions. If a Timer
// object is placed in the beginning of a function and if there is a
// <!id>MainTImer<!!id> object in the <!id>main()<!!id> (and if the
// debug level in the <!class>Debug<!!class> class is non-zero. the
// time spent in the function and the number of calls to the function
// will be reopted in the end of the run.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Debug.html">Debug.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/Debug.h"
// #include "Timer.fh"
// #include "Timer.xh"
#include <ctime>

namespace ThePEG {

class TimeCounter: public Named {

public:

  inline TimeCounter(string newName = "");
  inline TimeCounter(const TimeCounter &);
  inline ~TimeCounter();
  inline TimeCounter & operator=(const TimeCounter &);
  // Standard constructors, destructor and assignment.

public:

  inline void enter();
  // Signal the creation of the corresponding Timer object.

  inline void start();
  inline void stop();
  // Start and stop the stop-watch.

  inline unsigned int nCalls() const;
  // Return the number of calls made to the corresponding timer.

  inline double timeTot() const;
  inline double timePer() const;
  // Return the total time (in seconds) spent in the corresponding
  // timer and the time spent per call.

private:

  unsigned int theNCalls;
  // The number of calls made to the corresponding timer.

  clock_t startClock;
  // The clock at the last call to start.

  unsigned long totTime;
  // The total time spent in the corresponding timer.

  unsigned int loop;
  // The loop level

};

class MainTimer {

  typedef map<unsigned int,TimeCounter> CounterMap;

public:

  inline MainTimer(string file = ".timer");
  inline ~MainTimer();
  // Constructor and destructor. The argument to the constructor is
  // the name of the file to which statistics is written.

public:

  static TimeCounter * getCounter(unsigned int i, string);
  // Get the counter object with the given name.

  inline static bool running();
  // Return true if the MainTimer object has been constructed.

private:

  static CounterMap & counters();
  // The map of counters.

  static void statistics(string file);
  // Write out the accumulated statistics to a file.

  static bool isRunning;
  // True if the MainTimer object has been constructed.

  string filename;
  // The name of the file to which statistics is written.

  static TimeCounter * theCounter;
  // The TimeCounter for the main function.

private:

  inline MainTimer(const MainTimer &);
  inline MainTimer & operator=(const MainTimer &);
  // MainTimer should be a singleton object and copying is private and
  // unimplemented.

};

template <unsigned int I>
class Timer {

public:

  inline Timer(string name);
  inline ~Timer();
  // Constructor and destructor.

public:

  inline void stop();
  inline void start();
  // Temporarily stop and restart this timer.

private:

  bool started;
  // True if the time counting is running.

  static TimeCounter * theCounter;
  // The counter.

private:

  inline Timer();
  inline Timer(const Timer &);
  inline Timer & operator=(const Timer &);
  // Copying is private and unimplemented.

};

}

#include "Timer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Timer.tcc"
#endif

#endif /* ThePEG_Timer_H */
