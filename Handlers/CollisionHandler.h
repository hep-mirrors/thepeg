// -*- C++ -*-
#ifndef ThePEG_CollisionHandler_H
#define ThePEG_CollisionHandler_H
// This is the declaration of the CollisionHandler class.

#include "ThePEG/Handlers/PartialCollisionHandler.h"
#include "CollisionHandler.xh"
#include "ThePEG/Utilities/Selector.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/EventRecord/Event.h"

namespace ThePEG {

/**
 * CollisionHandler is the main class for generating collisions, from
 * the incoming pair of particles via the extraction of partons, the
 * hard sub-process and the production of remnants. It is derived from
 * the PartialCollisionHandler which is used to perform all the
 * subsequent steps needed for generating a full collision. The
 * EventHandler class inherits from CollisionHandler and is
 * responsible for full events, starting from a LuninosityFunction to
 * specify the beams.
 *
 * The CollisionHandler has a list of <code>SubProcessHandler</code>s,
 * which in turn has a PartonExtractor and a list of MEBase
 * objects. When initialized, the CollisionHandler is given a maximum
 * invariant mass squared of the incoming particles. For each
 * SubProcessHandler is asked to return a list of XComb objects, one
 * for each possible combination of incoming partons and hard
 * parton-parton matrix element, containing the maximum cross section
 * and other info needed for selecting and generating the
 * corresponding sub-process.
 *
 * When run, the <code>CollisionHandler</code> picks a XComb object at
 * random and generates the corresponding sub-process, then uses the
 * PartialCollisionHandler base class to perform all subsequent steps
 * to produce the full collision.
 *
 * The CollisionHandler has also a KinematicalCuts object which is
 * responsible for restricting the kinematics of the sub-process and
 * produced collision.
 *
 * The CollisionHandler is not intended to be sub-classes by the
 * user. Modifying the behavior of the CollisionHandler is instead
 * achieved by assigning different SubProcessHandler and
 * KinematicalCuts objects.
 *
 * The CollisionHandler class also inherits from the LastXCombInfo
 * class (via the PartialCollisionHandler base class) to have easy
 * interface to the information in the last selected XComb.
 *
 *
 * @see PartialCollisionHandler
 * @see SubProcessHandler
 * @see PartonExtractor
 * @see MEBase
 * @see XComb
 * @see KinematicalCuts
 * @see EventHandler
 * 
 */
class CollisionHandler: public PartialCollisionHandler {

public:

  /** A vector of <code>SubProcessHandler</code>s. */
  typedef vector<SubHdlPtr> SubHandlerList;

  /** A weighted list of pointers to XComb objects. */
  typedef Selector<XCombPtr> XSelector;

  /** A vector of pointers to XComb objects. */
  typedef vector<XCombPtr> XVector;

  /** A vector of cross sections. */
  typedef vector<CrossSection> XSVector;

  /** Map of pointers to XComb objects indexed by pointers to the
   *  corresponding MEBase object. */
  typedef map<tMEPtr,XVector> MEXMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  CollisionHandler();

  /**
   * The copy-constructor.
   */
  CollisionHandler(const CollisionHandler & ch);
  /**
   * The destructor.
   */
  virtual ~CollisionHandler();
  //@}

public:

  /**
   * Initialize this collision handler.
   *
   * @param maxEnergy the maximum possible invariant mass of the
   * incoming particles.
   */
  void initialize(Energy maxEnergy);

  /**
   * Return the boost needed to transform the current event from the
   * CMS system to the lab system.
   */
  inline const LorentzRotation & currentEventBoost() const;

  /**
   * Generate a phase space point and return the corresponding cross
   * section.
   * @param ll a pair of doubles giving the logarithms of the (inverse
   * energy fractions of the maximum CMS energy of the incoming
   * particles.
   * @param maxS the maximum squared CMS energy of the incoming particles.
   * @param ibin the preselected bin of XComb objects to choose
   * sub-process from
   * @param nr the number of random numbers availiable in \a r.
   * @param r an array of random numbers to be used to generate a
   * phase-space point.
   */
  CrossSection dSigDR(const pair<double,double> ll, Energy2 maxS,
		      int ibin, int nr, const double * r);

  /**
   * Select an XComb. Given a preselected bin, \a ibin of XComb
   * objects pick one to generate the corresponding sub-process with
   * the given \a weight.
   */
  void select(int bin, double weight);

  /** @name Simple access functions. */
  //@{
  /**
   * The pair of incoming particle types.
   */
  inline const cPDPair & incoming() const;

  /**
   * Return a reference to the KinematicalCuts of this
   * CollisionHandler. Note that these cuts may be overridden by the
   * SubProcess chosen.
   */
  inline tKinCutPtr cuts() const;

  /**
   * Return the number of separate bins of XComb objects to sample.
   */
  int nBins() const;

  /**
   * Return the number of phase space dimensions needed for the
   * sampling of indicated bin of XComb objects.
   */
  inline int maxDim(int bin) const;
  //@}

public:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
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
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /**
   * Create and add <code>XComb</code> objects.
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
   * the method in the PartialCollisionHandler, and the
   * <code>StepHandler</code>s given in the currently selected
   * SubProcess take precedence over the ones specified in the
   * PartialCollisionHandler sub class.
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

  /**
   * Return the vector of XComb objects.
   */
  inline const XVector & xCombs() const;

  /**
   * Return the vector of XComb objects.
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
   * Return the strategy to be used when sampling different XComb
   * objects.
   * @return 0 if all XComb objects are sampled together. 1 if
   * all XComb objects which have the same matrix element object are
   * sampled together. 2 if all XComb objects are sampled separately.
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
   * The pair of incoming particle types.
   */
  cPDPair theIncoming;

  /**
   * The list of <code>SubProcessHandler</code>s.
   */
  SubHandlerList theSubProcesses;

  /**
   * The kinematical cuts used for this collision handler.
   */
  KinCutPtr theCuts;

  /**
   * The XComb objects.
   */
  XVector theXCombs;

  /**
   * The (incrementally summed) cross sections associated with the
   * XComb objects for the last selected phase space point.
   */
  XSVector theXSecs;

  /**
   * The strategy to be used when sampling different XComb objects. 0
   * means all XComb objects are sampled together. 1 means all XComb
   * objects which have the same matrix element object are sampled
   * together. 2 means all XComb objects are sampled separately.
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

private:

  /**
   * Standard Initialization object.
   */
  static ClassDescription<CollisionHandler> initCollisionHandler;

  /**
   * Private and non-existent assignment operator.
   */
  const CollisionHandler & operator=(const CollisionHandler &);

};

/** This template specialization informs ThePEG about the
 *  base classes of CollisionHandler. */
template <>
struct BaseClassTrait<CollisionHandler,1>: public ClassTraitsType {
  /** Typedef of the base class of CollisionHandler. */
  typedef PartialCollisionHandler NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the CollisionHandler class. */
template <>
struct ClassTraits<CollisionHandler>:
    public ClassTraitsBase<CollisionHandler> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::CollisionHandler"; }
};

}

#include "CollisionHandler.icc"

#endif /* ThePEG_CollisionHandler_H */
