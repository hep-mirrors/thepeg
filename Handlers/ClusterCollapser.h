// -*- C++ -*-
#ifndef ThePEG_ClusterCollapser_H
#define ThePEG_ClusterCollapser_H
// This is the declaration of the ClusterCollapser class.

#include "ThePEG/Handlers/StepHandler.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
#include "ThePEG/EventRecord/ColourSinglet.h"
#include "ClusterCollapser.fh"
// #include "ClusterCollapser.xh"


namespace ThePEG {

/**
 * ClusterCollapser is a general StepHandler which can be called
 * anywhere in the event generation (typically as a pre-handler to the
 * hadronization or a post-hadnler to the cascade) to find colour-less
 * clusters of partons which are deemed to have to small invariant
 * mass to be hadronized in the normal way. Instead these clusters are
 * allowed to collapse into hadrons. Possible energy imbalance du to
 * the clustering is compensated by shifting the momenta of nearby
 * particles.
 * 
 * @see \ref ClusterCollapserInterfaces "The interfaces"
 * defined for ClusterCollapser.
 */
class ClusterCollapser: public StepHandler {

public:

  /** Declare a pointer to a FlavourGenerator object. */
  typedef Ptr<FlavourGenerator>::pointer FlavGenPtr;

  /** Declare a multimap of singlets indexed by their mass. */
  typedef multimap<Energy,ColourSinglet> SingletMap;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline ClusterCollapser();

  /**
   * The copy constructor.
   */
  inline ClusterCollapser(const ClusterCollapser &);

  /**
   * The destructor.
   */
  virtual ~ClusterCollapser();
  //@}

public:

  /** @name Virtual functions required by the StepHandler class. */
  //@{
  /**
    * The main function called by the EventHandler class to
    * perform a step. This function simply calls the collapse() function.
    * @param eh the EventHandler in charge of the Event generation.
    * @param tagged if not empty these are the only particles which should
    * be considered by the StepHandler.
    * @param hint a Hint object with possible information from previously
    * performed steps.
    * @throws Veto if the StepHandler requires the current step to be discarded.
    * @throws Stop if the generation of the current Event should be stopped
    * after this call.
    * @throws Exception if something goes wrong.
    */
  virtual void handle(EventHandler & eh, const tPVector & tagged,
		      const Hint & hint) throw(Veto, Stop, Exception);
  //@}

  /**
   * Perform all necessary collapses. Return the uncollapsed clusters.
   */
  virtual vector<ColourSinglet> collapse(tPVector tagged,
					 tStepPtr newstep);

  /**
   * Go through the tagged partons and extract all colour singlet
   * combination of partons. Order them in invariant mass (minus the
   * constituent masses of the partons).
   */
  virtual SingletMap getSinglets(const tPVector & tagged) const;

  /**
   * If a singlet contains at least one diquark and a junction, split
   * the diquark and split off a new colour singlet.
   */
  virtual ColourSinglet splitDiQuarkJunction(ColourSinglet & cs,
					     tStepPtr newStep) const;

  /**
   * If a singlet contains a simple string with diquarks in both ends,
   * split them into quarks and split off a new colour singlet.
   */
  virtual ColourSinglet splitDiDiQuark(ColourSinglet & cs,
				       tStepPtr newStep) const;

  /**
   * Returns true iff the given singlet contains a junction and at
   * least one diquark.
   */
  static bool diQuarkJunction(const ColourSinglet & cs);

  /**
   * Returns true iff the given singlet contains one string piece with
   * diquarks in both ends.
   */
  static bool diDiQuark(const ColourSinglet & cs);

  /**
   * If the invariant mass of a cluster, minus the constituent masses
   * of its partons is below this cut, it will be collapsed into one
   * or two particles.
   */
  inline Energy cut() const;

  /**
   * The number of attempts to collapse a cluster into two particles,
   * before it is collapsed into one particle.
   */
  inline int nTry2() const;

  /**
   * Return the invariant mass of a cluster minus the constituent
   * masses of its partons.
   */
  static Energy mass(const ColourSinglet & cl);

  /**
   * Insert a ColourSinglet object in a SingletMap.
   */
  static void insert(SingletMap & mmap, const ColourSinglet & cl);

  /**
   * Pick a random flavour. Default version picks u,d or s with ratio
   * 3:3:1.
   */
  virtual tcPDPtr pickFlavour() const;

protected:

  /**
   * Perform the actual collapse of a cluster into one hadron.  Add
   * the produced hadron to the given step as decay products of the
   * partons in the cluster. The \a tagged particles are used for
   * momentum compensation.
   */
  virtual void collapse(tStepPtr newStep, const ColourSinglet & cs,
			const tPVector & tagged) const;
  /**
   * Perform the actual collapse of a cluster into two hadrons. Add
   * the produced hadrons to the given step as decay products of the
   * partons in the cluster. The \a tagged particles are used for
   * momentum compensation.  @return false if the collapse failed in
   * some way.
   */
  virtual bool collapse2(tStepPtr newStep, const ColourSinglet & cs) const;

  /**
   * Get particles for compensation. Look through the \a tagged vector
   * for particles (which are not in the colour singlet \a cs) which can
   * be used to compensate momentum when \a cs collapses into a hadron
   * with mass \a mh. These partons are then copied into the new step so
   * that their momentum can be changed and then returned.
   */
  virtual tPVector getCompensators(Energy mh, const ColourSinglet & cs,
				   const tPVector & tagged,
				   tStepPtr newStep) const;

  /**
   * Return a hadron into which the given cluster may collapse.
   */
  virtual tcPDPtr getHadron(const ColourSinglet & cs) const;

  /**
   * Return a pair of hadrons into which the given cluster may collapse.
   */
  virtual tcPDPair getHadrons(const ColourSinglet & cs) const;

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
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;
  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

  /** Exception class used by ClusterCollapser. */
  class ClusterException: public Exception {
  public:
    /** Standard constructor. */
    ClusterException(const ClusterCollapser & cc) {
      theMessage << "In ClusterCollapser '" << cc.name() << "': ";
    }
  };

private:

  /**
   * Energy cut. If the invariant mass of a cluster, minus the
   * constituent masses of its partons is below this cut, it will be
   * collapsed into one or two particles.
   */
  Energy theEnergyCut;

  /**
   * The number of attempts to collapse a cluster into two particles,
   * before it is collapsed into one particle.
   */
  int theNTry2;

  /**
   * The flavour generator object to use to combine quarks and diqurks
   * into hadrons.
   */
  FlavGenPtr flavGen;

protected:

  /**
   * How should we respond to errors? 0 means do nothing, ie. the
   * cluster will not be collapsed, or the momentum will not be
   * consterved. Otherwise the severity will be what is defined in the
   * class Exception.
   */
  Exception::Severity errorlevel;

  /**
   * The relative probability to produce a s-sbar pair in a split as
   * compared to a u-ubar or d-dbar pair.
   */
  double pStrange;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<ClusterCollapser> initClusterCollapser;

  /**
   *  Private and non-existent assignment operator.
   */
  ClusterCollapser & operator=(const ClusterCollapser &);

};

}


namespace ThePEG {

/**
 * The following template specialization informs ThePEG about the
 * base class of ClusterCollapser.
 */
template <>
struct BaseClassTrait<ClusterCollapser,1>: public ClassTraitsType {
  /** Typedef of the first base class of ClusterCollapser. */
  typedef StepHandler NthBase;
};

/**
 * The following template specialization informs ThePEG about the name
 * of the ClusterCollapser class and the shared object where it is
 * defined.
 */
template <>
struct ClassTraits<ClusterCollapser>:
    public ClassTraitsBase<ClusterCollapser> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::ClusterCollapser"; }
  /**
   * Return the name of the shared library to be loaded to get
   * access to this class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGString.so"; }

};

}

#include "ClusterCollapser.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ClusterCollapser.tcc"
#endif

#endif /* ThePEG_ClusterCollapser_H */
