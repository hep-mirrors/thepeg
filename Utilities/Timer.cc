// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Timer class.
//

#include "Timer.h"
#include <fstream>
#include <iomanip>

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Timer.tcc"
#endif

using namespace ThePEG;

MainTimer::CounterMap & MainTimer::counters() {
  static CounterMap theMap;
  return theMap;
}

TimeCounter * MainTimer::getCounter(unsigned int i, string name) {
  return &(counters()[i] = TimeCounter(name));
}

void MainTimer::statistics(string file) {
  CounterMap & m = counters();
  ofstream os(file.c_str());
  for ( CounterMap::iterator it = m.begin(); it != m.end(); ++it ) {
    os << setw(9) << it->second.nCalls() << " "
       << setprecision(3) << setw(10) << it->second.timeTot() << " "
       << setprecision(3) << setw(10) << it->second.timePer()
       << " " << setw(3) << it->first << " " << it->second.name() << endl;
  }
}

bool MainTimer::isRunning = false;

TimeCounter * MainTimer::theCounter = MainTimer::getCounter(0, "main");


