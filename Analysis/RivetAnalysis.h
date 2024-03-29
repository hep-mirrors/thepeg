// -*- C++ -*-
#ifndef THEPEG_RivetAnalysis_H
#define THEPEG_RivetAnalysis_H
//
// This is the declaration of the RivetAnalysis class.
//

#include "ThePEG/Handlers/AnalysisHandler.h"
#include "Rivet/AnalysisHandler.hh"

namespace ThePEG {

/**
 * Here is the documentation of the RivetAnalysis class.
 *
 * @see \ref RivetAnalysisInterfaces "The interfaces"
 * defined for RivetAnalysis.
 */
class RivetAnalysis: public ThePEG::AnalysisHandler {

public:
  
  /**
   * The default constructor.
   */
  RivetAnalysis();
  
public:
  
  /** @name Virtual functions required by the AnalysisHandler class. */
  //@{
  /**
   * Analyze a given Event. Note that a fully generated event
   * may be presented several times, if it has been manipulated in
   * between. The default version of this function will call transform
   * to make a lorentz transformation of the whole event, then extract
   * all final state particles and call analyze(tPVector) of this
   * analysis object and those of all associated analysis objects. The
   * default version will not, however, do anything on events which
   * have not been fully generated, or have been manipulated in any
   * way.
   * @param event pointer to the Event to be analyzed.
   * @param ieve the event number.
   * @param loop the number of times this event has been presented.
   * If negative the event is now fully generated.
   * @param state a number different from zero if the event has been
   * manipulated in some way since it was last presented.
   */
  virtual void analyze(ThePEG::tEventPtr event, long ieve, int loop, int state);
  //@}
  
public:
  
  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(ThePEG::PersistentOStream & os) const;
  
  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(ThePEG::PersistentIStream & is, int version);
  //@}

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual ThePEG::IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual ThePEG::IBPtr fullclone() const;
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Initialize this object. Called in the read phase.
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

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ThePEG::ClassDescription<RivetAnalysis> initRivetAnalysis;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  RivetAnalysis & operator=(const RivetAnalysis &) = delete;

private:

  /**
   *  The Analyses to use
   */
  vector<string> _analyses;

  /**
   *   Yoda files to be preloaded
   */
  vector<string> _preload;

  /**
   * Search paths for finding rivet analyses. 
   */
  vector<string> _paths;

  /**
   * The base name of the output file.
   */
  string _filename;

  /**
   * Enable debugging information from Rivet
   */
  bool _debug;

  /**
   *  The RivetAnalysisHandler
   */
  Rivet::AnalysisHandler * _rivet;

  /**
   *  Event count
   */
  unsigned long _nevent;

  /**
   *  Disable beam check
   */
  bool _checkBeams;
};

}

#endif /* THEPEG_RivetAnalysis_H */
