// -*- C++ -*-
//
// LesHouchesEventHandler.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2011 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_LesHouchesEventHandler_H
#define THEPEG_LesHouchesEventHandler_H
//
// This is the declaration of the LesHouchesEventHandler class.
//

#include "ThePEG/Handlers/EventHandler.h"
#include "LesHouchesEventHandler.fh"
#include "LesHouchesReader.fh"
//#include "LesHouchesAnalysis.h"
#include "ThePEG/Utilities/CompSelector.h"
#include "ThePEG/Utilities/XSecStat.h"

namespace ThePEG {


/**
 * The LesHouchesEventHandler inherits from the general EventHandler
 * class and administers the reading of events generated by external
 * matrix element generator programs according to the Les Houches
 * accord.
 *
 * The class has a list of <code>LesHouchesReader</code>s which
 * typically are connected to files with event data produced by
 * external matrix element generator programs. When an event is
 * requested by LesHouchesEventHandler, one of the readers are chosen,
 * an event is read in and then passed to the different
 * <code>StepHandler</code> defined in the underlying
 * EventHandler class.
 *
 * @see \ref LesHouchesEventHandlerInterfaces "The interfaces"
 * defined for LesHouchesEventHandler.
 */
class LesHouchesEventHandler: public EventHandler {

public:

  /**
   * A vector of LesHouchesReader objects.
   */
  typedef vector<LesHouchesReaderPtr> ReaderVector;

  /**
   * A selector of readers.
   */
  typedef CompSelector<int,CrossSection> ReaderSelector;

  /**
   * Enumerate the weighting options.
   */
  enum WeightOpt {
    unitweight = 1,    /**< All events have unit weight. */
    unitnegweight = -1, /**< All events have wight +/- 1. */
    varweight = 2,      /**< Varying positive weights. */
    varnegweight = -2   /**< Varying positive or negative weights. */
  };

  friend class LesHouchesHandler;


public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  LesHouchesEventHandler()
    : theWeightOption(unitweight), theUnitTolerance(1.0e-6), warnPNum(true) 
  {
    selector().tolerance(unitTolerance());
  }

  /**
   * The destructor.
   */
  virtual ~LesHouchesEventHandler();
  //@}

public:

  /** @name Initialization and finalization functions. */
  //@{
  /**
   * Initialize this event handler and all related objects needed to
   * generate events.
   */
  virtual void initialize();

  /**
   * Write out accumulated statistics about intergrated cross sections
   * and stuff.
   */
  virtual void statistics(ostream &) const;

  /**
   * Histogram scale. A histogram bin which has been filled with the
   * weights associated with the Event objects should be scaled by
   * this factor to give the correct cross section.
   */
  virtual CrossSection histogramScale() const;

  /**
   * The estimated total integrated cross section of the processes
   * generated in this run.
   * @return 0 if no integrated cross section could be estimated.
   */
  virtual CrossSection integratedXSec() const;

  /**
   * The number of attempts inside the statistics object
   */
 
  virtual int ntriesinternal() const;

  /**
   * The estimated error in the total integrated cross section of the
   * processes generated in this run.
   *  @return 0 if no integrated cross section error could be estimated.
   */
  virtual CrossSection integratedXSecErr() const;

  /**
   * Map to aid the calculation of the optional weights' integrated cross section
   */

  virtual map<string,CrossSection> optintegratedXSecMap() const;

  //@}

  /** @name Functions used for the actual generation */
  //@{
  /**
   * Generate an event.
   */
  virtual EventPtr generateEvent();

  /**
   * Create the Event and Collision objects. Used by the
   * generateEvent() function.
   */
  virtual tCollPtr performCollision();

  /**
   * Continue generating an event if the generation has been stopped
   * before finishing.
   */
  virtual EventPtr continueEvent();
  //@}

  /** @name Functions to manipulate statistics. */
  //@{
  /**
   * An event has been selected. Signal that an event has been
   * selected with the given \a weight. If unit weights are requested,
   * the event will be accepted with that weight. This also takes care
   * of the statistics collection of the selected reader object.
   */
  void select(double weight);

  /**
   * Accept the current event, taking care of the statistics
   * collection of the corresponding reader objects.
   */
  void accept();

  /**
   * Reject the current event, taking care of the statistics
   * collection of the corresponding reader objects.
   */
  void reject(double weight);

  /**
   * Increase the overestimated cross section for the selected reader.
   */
  void increaseMaxXSec(CrossSection maxxsec);

  /**
   * Skip some events. To ensure a reader file is scanned an even
   * number of times, skip a number of events for the selected reader.
   */
  void skipEvents();

  //@}

  /** @name Simple access functions. */
  //@{
  /**
   * The way weights are to be treated.
   */
  WeightOpt weightOption() const { return theWeightOption; }

  /**
   * If the weight option is set to unit weight, do not start
   * compensating unless the weight is this much larger than unity.
   */
  double unitTolerance() const { return theUnitTolerance; }

  /**
   * Access the list of readers.
   */
  const ReaderVector & readers() const { return theReaders; }

  /**
   * The selector to choose readers according to their overestimated
   * cross section.
   */
  const ReaderSelector & selector() const { return theSelector; }

  /**
   * The currently selected reader object.
   */
  tLesHouchesReaderPtr currentReader() const { return theCurrentReader; }


  /**
   * Set the currently selected reader object.
   */
  void currentReader(tLesHouchesReaderPtr x) { theCurrentReader = x; }

  //@}

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

  /**
   * The currently selected reader object.
   */
  tLesHouchesReaderPtr theCurrentReader;

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit();

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  virtual void dofinish();
  //@}

protected:

  /**
   * Access the list of readers.
   */
  ReaderVector & readers() { return theReaders; }

  /**
   * The selector to choose readers according to their overestimated
   * cross section.
   */
  ReaderSelector & selector() { return theSelector; }

  /**
   * Helper function for the interface;
   */
  void setUnitTolerance(double);

  /**
   * Collect statistics for this event handler.
   */
  XSecStat stats;

  /* 
   * Collect statistics for the optional weights
   */ 
  map<string,XSecStat> optstats;

  /* 
   * Calculate the cross section for the optional weights
   */

  map<string,CrossSection> optxs;

  /*
   * Counter for the number of tries for the purpose of statistics
   */
  
  int ntries;

  /* 
   * Return the optional weights' statistics 
   */ 
  
  map<string,XSecStat> OptStatsFunc() { return optstats; }

  /*
   * Return the optional weights' cross sections
   */

  map<string,CrossSection> OptXsFunc() { return optxs; }


  /**
   * Collect statistics for this event handler. To be used for
   * histogram scaling.
   */
  XSecStat histStats;

    /**
   * Collect statistics for this event handler's optional weights. To be used for
   * histogram scaling.
   */

  map<string,XSecStat> opthistStats;

  /*
   * The weight identifiers for the events
   */ 
  
  vector<string> weightnames;

private:

  /**
   * The list of readers.
   */
  ReaderVector theReaders;

  /**
   * The selector to choose readers according to their overestimated
   * cross section.
   */
  ReaderSelector theSelector;

  /**
   * The way weights are to be treated.
   */
  WeightOpt theWeightOption;

  /**
   * If the weight option is set to unit weight, do not start
   * compensating unless the weight is this much larger than unity.
   */
  double theUnitTolerance;


  /**
   * Warn if the same process number is used in more than one
   * LesHouchesReader.
   */
  bool warnPNum;



public:

  /** @cond EXCEPTIONCLASSES */
  /**
   * Exception class used if no readers were assigned.
   */
  class LesHouchesInitError: public InitException {};

  /**
   * Exception class used if the same process number is used by more
   * than ne reader.
   */
  class LesHouchesPNumException: public InitException {};
  /** @endcond */

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<LesHouchesEventHandler> initLesHouchesEventHandler;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  LesHouchesEventHandler & operator=(const LesHouchesEventHandler &);

};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of LesHouchesEventHandler. */
template <>
struct BaseClassTrait<LesHouchesEventHandler,1> {
  /** Typedef of the first base class of LesHouchesEventHandler. */
  typedef EventHandler NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the LesHouchesEventHandler class and the shared object where it is defined. */
template <>
struct ClassTraits<LesHouchesEventHandler>
  : public ClassTraitsBase<LesHouchesEventHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::LesHouchesEventHandler"; }
  /** Return the name of the shared library be loaded to get access to
   *  the LesHouchesEventHandler class and every other class it uses
   *  (except the base class). */
  static string library() { return "LesHouches.so"; }
};

/** @endcond */

}

#endif /* HERWIG_LesHouchesEventHandler_H */
