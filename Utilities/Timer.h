// -*- C++ -*-
#ifndef ThePEG_Timer_H
#define ThePEG_Timer_H
// This is the declaration of the Timer class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/Debug.h"
// #include "Timer.fh"
// #include "Timer.xh"
#include <ctime>

namespace ThePEG {

/**
 * The TimerCounter class is used by the Timer and MainTimer classes
 * to collect statistics.
 */
class TimeCounter: public Named {

public:

  /**
   * Constructor given the name of the function where it is used.
   */
  inline TimeCounter(string newName = "");

  /**
   * Copy constructor..
   */
  inline TimeCounter(const TimeCounter &);

  /**
   * Destructor.
   */
  inline ~TimeCounter();

  /**
   * Assignment.
   */
  inline TimeCounter & operator=(const TimeCounter &);

public:

  /**
   * Signal the creation of the corresponding Timer object.
   */
  inline void enter();

  /**
   * Start the stop-watch.
   */
  inline void start();

  /**
   * Stop the stop-watch.
   */
  inline void stop();

  /**
   * Return the number of calls made to the corresponding timer.
   */
  inline unsigned int nCalls() const;

  /**
   * Return the total time (in seconds) spent in the corresponding
   * timer.
   */
  inline double timeTot() const;

  /**
   * Return the total time (in seconds) spent per call in the corresponding
   * timer.
   */
  inline double timePer() const;

private:

  /**
   * The number of calls made to the corresponding timer.
   */
  unsigned int theNCalls;

  /**
   * The clock at the last call to start.
   */
  clock_t startClock;

  /**
   * The total time spent in the corresponding timer.
   */
  unsigned long totTime;

  /**
   * The loop level
   */
  unsigned int loop;

};

/**
 * The MainTimer class defines a class of which only one object should
 * be created in the <code>main()</code> to initialize and administer
 * the Timer objects used in the run.
 */
class MainTimer {

  /** A map relating TimerCounter objects to corresponding template
  integer arguments. */
  typedef map<unsigned int,TimeCounter> CounterMap;

public:

  /**
   * Constructor. The argument is the name of the file to which
   * statistics is written.
   */
  inline MainTimer(string file = ".timer");

  /**
   * Destructor.
   */
  inline ~MainTimer();

public:

  /**
   * Get the counter object with the given name.
   */
  static TimeCounter * getCounter(unsigned int i, string);

  /**
   * Return true if the MainTimer object has been constructed.
   */
  inline static bool running();

private:

  /**
   * The map of counters.
   */
  static CounterMap & counters();

  /**
   * Write out the accumulated statistics to a file.
   */
  static void statistics(string file);

  /**
   * True if the MainTimer object has been constructed.
   */
  static bool isRunning;

  /**
   * The name of the file to which statistics is written.
   */
  string filename;

  /**
   * The TimeCounter for the main function.
   */
  static TimeCounter * theCounter;

private:

  /**
   * MainTimer should be a singleton object and copying is private and
   * unimplemented.
   */
  inline MainTimer(const MainTimer &);

  /**
   * MainTimer should be a singleton object and copying is private and
   * unimplemented.
   */
  inline MainTimer & operator=(const MainTimer &);

};

/**
 * The Timer class is used to time functions. If a Timer object is
 * placed in the beginning of a function and if there is a
 * <code>MainTImer</code> object in <code>main()</code> (and if the
 * debug level in the Debug class is non-zero) the time spent in the
 * function and the number of calls to the function will be reopted in
 * the end of the run. To avoid confusion, only one Timer object of
 * each template integer argument should be created.
 *
 * @see Debug.
 * 
 */
template <unsigned int I>
class Timer {

public:

  /**
   * Constructor taking the name of the function where it is being
   * used as argument.
   */
  inline Timer(string name);

  /**
   * Destructor.
   */
  inline ~Timer();

public:

  /**
   * Temporarily stop this timer.
   */
  inline void stop();

  /**
   * Restart this timer after a temporary stop.
   */
  inline void start();

private:

  /**
   * True if the time counting is running.
   */
  bool started;

  /**
   * The counter.
   */
  static TimeCounter * theCounter;

private:

  /**
   * Default constructor is private and unimplemented.
   */
  inline Timer();

  /**
   * Copy constructor is private and unimplemented.
   */
  inline Timer(const Timer &);

  /**
   * Assignment is private and unimplemented.
   */
  inline Timer & operator=(const Timer &);

};

}

#include "Timer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Timer.tcc"
#endif

#endif /* ThePEG_Timer_H */
