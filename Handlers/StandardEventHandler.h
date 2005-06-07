// -*- C++ -*-
#ifndef ThePEG_StandardEventHandler_H
#define ThePEG_StandardEventHandler_H
// This is the declaration of the StandardEventHandler class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/Repository/Strategy.fh"
#include "ThePEG/Handlers/SamplerBase.fh"
#include "ThePEG/PDF/PartonBin.fh"
#include "ThePEG/MatrixElement/MEBase.fh"
#include "SubProcessHandler.fh"
#include "StandardXComb.fh"
#include "StandardEventHandler.fh"
#include <fstream>

namespace ThePEG {

/**
 * The StandardEventHandler class is the main class for generating simple
 * events without overlayed collisions. It is derived from the
 * basic EventHandler class.
 *
 * Besides the standard doinit() method, the StandardEventHandler needs to be
 * separately initialized with the initialize() method. In the
 * dofinish() method statistics is written out to the EventGenerators
 * default output file.
 *
 * @see \ref EventHandlerInterfaces "The interfaces"
 * defined for StandardEventHandler.
 * @see EventHandler
 * @see EventGenerator
 * @see Event
 * 
 */
class StandardEventHandler: public EventHandler {

public:

  /** A vector of <code>SubProcessHandler</code>s. */
  typedef vector<SubHdlPtr> SubHandlerList;

  /** A weighted list of pointers to StandardXComb objects. */
  typedef Selector<StdXCombPtr> XSelector;

  /** A vector of pointers to StandardXComb objects. */
  typedef vector<StdXCombPtr> XVector;

  /** A vector of cross sections. */
  typedef vector<CrossSection> XSVector;

  /** Map of pointers to StandardXComb objects indexed by pointers to
   *  the corresponding MEBase object. */
  typedef map<tMEPtr,XVector> MEXMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Copy-constructor.
   */
  StandardEventHandler(const StandardEventHandler &);

  /**
   * Default constructor.
   */
  StandardEventHandler();

  /**
   * Destructor.
   */
  ~StandardEventHandler();
  //@}

public:

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

  /** @name Functions used for the actual generation */
  //@{
  /**
   * Return the cross section for the chosen phase space point.
   * @param r a vector of random numbers to be used in the generation
   * of a phase space point.
   */
  virtual CrossSection dSigDR(const vector<double> & r);

  /**
   * Generate an event.
   */
  virtual EventPtr generateEvent();

  /**
   * Continue generating an event if the generation has been stopped
   * before finishing.
   */
  virtual EventPtr continueEvent();

  /**
   * Return the boost needed to transform the current event from the
   * CMS system to the lab system.
   */
  inline const LorentzRotation & currentEventBoost() const;
  //@}

  /** @name Simple access functions */
  //@{
  /**
   * Return a reference to the KinematicalCuts of this
   * EventHandler. Note that these cuts may be overridden by the
   * SubProcess chosen.
   */
  inline tKinCutPtr cuts() const;

  /**
   * Return the number of separate bins of StandardXComb objects to
   * sample.
   */
  int nBins() const;

  /**
   * Return the number of phase space dimensions needed for the
   * sampling of indicated bin of StandardXComb objects.
   */
  inline int maxDim(int bin) const;

  /**
   * Return true if this event handler should produce weightes events
   */
  inline bool weighted() const;

  /**
   * Returns true if we are currently in a compensating mode after
   * encountering a weight larger than 1.
   */
  inline bool compensating() const;

  /**
   * The number of phase space dimensions used by the luminosity
   * function.
   */
  inline int lumiDim() const;

  /**
   * The number of dimensions of the basic phase space to generate
   * sub-processes in for a given bin of StandardXComb objects.
   */
  inline int nDim(int bin) const;
  //@}

protected:

  /**
   * Generate a phase space point and return the corresponding cross
   * section. Is called from sSigDR(const vector<double> &).
   * @param ll a pair of doubles giving the logarithms of the (inverse
   * energy fractions of the maximum CMS energy of the incoming
   * particles.
   * @param maxS the maximum squared CMS energy of the incoming particles.
   * @param ibin the preselected bin of StandardXComb objects to choose
   * sub-process from
   * @param nr the number of random numbers availiable in \a r.
   * @param r an array of random numbers to be used to generate a
   * phase-space point.
   */
  virtual CrossSection dSigDR(const pair<double,double> ll, Energy2 maxS,
		      int ibin, int nr, const double * r);

  /**
   * Select an StandardXComb. Given a preselected bin, \a ibin of
   * StandardXComb objects pick one to generate the corresponding
   * sub-process with the given \a weight.
   */
  tStdXCombPtr select(int bin, double weight);

  /**
   * Create and add <code>StandardXComb</code> objects.
   *
   * @param maxEnergy the maximum CMS energy of the incoming particles.
   * @param sub a pointer to the SubProcessHandler object.
   * @param extractor a pointer to the PartonExtractor object.
   * @param cuts a pointer to the KinematicalCuts object.
   * @param me a pointer to the MEBase object.
   * @param pBins a pair of <code>PartonBin</code>s describing the
   * partons extracted from the particles
   */
  void addME(Energy maxEnergy, tSubHdlPtr sub, tPExtrPtr extractor,
	     tKinCutPtr cuts, tMEPtr me, const PBPair & pBins);

  /**
   * For the sub-procss and phase-space point selected in the previous
   * call to dSigDR, produce the first step of an actual Collision.
   */
  tCollPtr performCollision();

  /**
   * Initialize groups of <code>StepHandler</code>s. This overrides
   * the method in the EventHandler, and the
   * <code>StepHandler</code>s given in the currently selected
   * SubProcess take precedence over the ones specified in the
   * EventHandler sub class.
   */
  virtual void initGroups();

  /**
   * Return the boost needed to transform the current collision from
   * the CMS system to the lab system. By default this is the unit
   * transformation, but an EventHandler derived from this class may
   * override it.
   */
  inline LorentzRotation & currentEventBoost();

  /**
   * Produce instances of the specified incoming particle types.
   */
  inline void createIncoming();

  /**
   * Set information about the current sub-process.
   */
  void setScale(Energy2);

  /**
   * Return the vector of StandardXComb objects.
   */
  inline const XVector & xCombs() const;

  /**
   * Return the vector of StandardXComb objects.
   */
  inline XVector & xCombs();

  /**
   * Return the vector of cross sections.
   */
  inline const XSVector & xSecs() const;

  /**
   * Return the vector of cross sections.
   */
  inline XSVector & xSecs();

  /**
   * Return the strategy to be used when sampling different StandardXComb
   * objects.
   * @return 0 if all StandardXComb objects are sampled together. 1 if
   * all StandardXComb objects which have the same matrix element object are
   * sampled together. 2 if all StandardXComb objects are sampled separately.
   */
  inline int binStrategy() const;

private:

  /**
   * Access the list of sub-process handlers.
   */
  inline const SubHandlerList & subProcesses() const;

  /**
   * Access the list of sub-process handlers.
   */
  inline SubHandlerList & subProcesses();

public:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Writes out statistics on the generation.
   */
  virtual void dofinish();
  //@}

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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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

  /**
   * Reject a (partially) generated event.
   * @param weight the weight given for the event.
   */
  void reject(double weight);

  /**
   * Return the sampler assigned to this event handler.
   */
  inline tSamplerPtr sampler();

  /**
   * Return the sampler assigned to this event handler.
   */
  inline tcSamplerPtr sampler() const;

private:

  /**
   * The first of the incoming particle types.
   */

  PDPtr theIncomingA;
  /**
   * The second of the incoming particle types.
   */

  PDPtr theIncomingB;

  /**
   * The list of <code>SubProcessHandler</code>s.
   */
  SubHandlerList theSubProcesses;

  /**
   * The kinematical cuts used for this collision handler.
   */
  KinCutPtr theCuts;

  /**
   * The StandardXComb objects.
   */
  XVector theXCombs;

  /**
   * The (incrementally summed) cross sections associated with the
   * StandardXComb objects for the last selected phase space point.
   */
  XSVector theXSecs;

  /**
   * The strategy to be used when sampling different StandardXComb
   * objects. 0 means all StandardXComb objects are sampled
   * together. 1 means all StandardXComb objects which have the same
   * matrix element object are sampled together. 2 means all
   * StandardXComb objects are sampled separately.
   */
  int theBinStrategy;

  /**
   * The map used to store all XBins with the same matrix element for
   * option 1 in theBinStrategy.
   */
  MEXMap theMEXMap;

  /**
   * The number of degrees of freedom needed to generate the phase
   * space for the different bins.
   */
  vector<int> theMaxDims;

  /**
   * The boost needed to transform the current collision from the CMS
   * system to the lab system.
   */
  LorentzRotation theCurrentEventBoost;

  /**
   * True if this event handler should produce weightes events
   */
  bool weightedEvents;

  /**
   * The phase space sampler responsible for generating phase space
   * points according to the cross section given by this event
   * handler.
   */
  SamplerPtr theSampler;

  /**
   * The number of phase space dimensions used by the luminosity
   * function.
   */
  int theLumiDim;

  /**
   * The number of dimensions of the basic phase space to generate
   * sub-processes in.
   */
  int theNDim;

  /**
   * Standard Initialization object.
   */
  static ClassDescription<StandardEventHandler> initStandardEventHandler;

protected:

  /**
   * Exception class used by EventHandler when a StepHandler of the
   * wrong class was added.
   */
  class StandardEventHandlerUpdateException: public UpdateException {};

  /**
   * Exception class used by EventHandler when a StepHandler of the
   * wrong class was added.
   */
  class StandardEventHandlerInitError: public Exception {};

private:

  /**
   * Private and non-existent assignment operator.
   */
  const StandardEventHandler & operator=(const StandardEventHandler &);

};

/**
 * The following template specialization informs ThePEG about the
 * base class of StandardEventHandler.
 */
template <>
struct BaseClassTrait<StandardEventHandler,1>: public ClassTraitsType {
  /** Typedef of the base class of StandardEventHandler. */
  typedef EventHandler NthBase;
};

/**
 * The following template specialization informs ThePEG about the name
 * of theEventHandler class and the shared object where it is defined.
 */
template <>
struct ClassTraits<StandardEventHandler>
  : public ClassTraitsBase<StandardEventHandler> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::StandardEventHandler"; }
};

}

#include "StandardEventHandler.icc"

#endif /* ThePEG_StandardEventHandler_H */