// -*- C++ -*-
#ifndef ThePEG_CollisionHandler_H
#define ThePEG_CollisionHandler_H
//
// This is the declaration of the <!id>CollisionHandler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>CollisionHandler<!!id> is the main class for generating
// collisions, from the incoming pair of particles via the extraction
// of partons, the hard sub-process and the production of remnants. It
// is derived from the <!class>PartialCollisionHandler<!!class> which
// is used to perform all the subsequent steps needed for generating a
// full collision.
//
// The <!id>CollisionHandler<!!id> has a list of
// <!class>SubProcessHandler<!!class>s, which in turn has a
// <!class>PartonExtractor<!!class> and a list of
// <!class>PartonXSecFn<!!class>s. When initialized, the
// CollisionHandler is given a list of intervals <i>s</i> in invariant
// mass squared of the incoming particles. For each interval each
// <!class>SubProcessHandler<!!class> is asked to return a list of
// <!class>XComb<!!class> objects, one for each possible combination of
// incoming partons, interval in invariant parton-parton invariant
// mass squared <i>shat</i> and hard parton-parton matrix element,
// containing the maximum cross section and other info needed for
// selecting and generating the corresponding sub-process.
//
// When run, the <!id>CollisionHandler<!!id> picks a
// <!class>XComb<!!class> object at random and performs the
// corresponding sub-process, then uses the
// <!class>PartialCollisionHandler<!!class> base class to perform all
// subsequent steps to produce the full collision.
//
// The <!id>CollisionHandler<!!id> has also a
// <!id>KinematicalCuts<!!id> object which is responsible for
// restricting the kinematics of the sub-process and produced
// collision.
//
// The <!id>CollisionHandler<!!id> is not intended to be sub-classes
// by the user. Modify the behavior of the <!id>CollisionHandler<!!id>
// is instead achieved by assigning different
// <!class>SubProcess<!!class> and <!id>KinematicalCuts<!!id> objects.
//
// The <!id>CollisionHandler<!!id> class also inherits from the
// <!id>LastXCombInfo<!!id> class (via the
// <!class>PartialCollisionHandler<!!class> base class) to have easy
// interface to the information in the last selected
// <!class>XComb<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PartialCollisionHandler.html">PartialCollisionHandler.h</a>
// <a href="http:SubProcessHandler.html">SubProcessHandler.h</a>
// <a href="http:PartonExtractor.html">PartonExtractor.h</a>
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>
// <a href="http:XComb.html">XComb.h</a>
// <a href="http:KinematicalCuts.html">KinematicalCuts.h</a>
// <a href="http:EventHandler.html">EventHandler.h</a>
// 

#include "ThePEG/Handlers/PartialCollisionHandler.h"
#include "CollisionHandler.xh"
#include "ThePEG/Utilities/Selector.h"
#include "ThePEG/Utilities/Interval.h"
#include "ThePEG/EventRecord/Event.h"

namespace ThePEG {

class CollisionHandler: public PartialCollisionHandler {

public:

  typedef vector<SubHdlPtr> SubHandlerList;
  typedef Selector<XCombPtr> XSelector;
  typedef vector<XCombPtr> XVector;
  typedef vector<CrossSection> XSVector;
  typedef map<tMEPtr,XVector> MEXMap;

public:

  CollisionHandler();
  CollisionHandler(const CollisionHandler & ch);
  ~CollisionHandler();
  // The default ctor and dtor.

public:

  inline const cPDPair & incoming() const;
  // The pair of incoming particle types.

  void initialize(Energy maxEnergy);
  // Initialize this collision handler given the maximum cms energy allowed.

  inline const LorentzRotation & currentEventBoost() const;
  // Return the boost needed to transform the current event from the
  // CMS system to the lab system.

  inline tKinCutPtr cuts() const;
  // Return a reference to the KinematicalCuts of this
  // CollisionHandler. Note that these cuts may be overridden by the
  // SubProcess chosen.

  CrossSection dSigDR(const pair<double,double> ll, Energy2 maxS,
		      int ibin, int nr, const double * r);
  // Generate a phase space point and return the corresponding cross
  // section.

  void select(int bin, double weight);
  // Select an XComb.

  int nBins() const;
  // Return the number of separate bins to sample.

  inline int maxDim(int bin) const;
  // Return the number of phase space dimensions needed for the
  // sampling of indicated bin.

public:

  virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  void addME(Energy maxEnergy, tSubHdlPtr sub, tPExtrPtr extractor,
	     tKinCutPtr cuts, tMEPtr me, const PBPair & pBins);
  // Add XComb's corrsponding to the given arguments.

  tCollPtr performCollision();
  // For the sub-procss and phase-space point selected in the previous
  // call to 'dSigDR', produce the first step of an actual Collision.

  virtual void initGroups();
  // initialize groups of step handlers. This overrides the method in
  // the PartialCollisionHandler, and the step handlers given in the
  // currently selected SubProcess take precedence ofer the ones
  // specified in the PartialCollisionHandler sub class.

  inline LorentzRotation & currentEventBoost();
  // Return the boost needed to transform the current collision from
  // the CMS system to the lab system. By default this is the unit
  // transformation, but an EventHandler derived from this class may
  // override it.

  inline void createIncoming();
  // Produce instances of the specified incoming particle types.

  void setScale(Energy2);
  // Set information about the current sub-process.

  virtual IBPtr clone() const;
  // Standard clone methods

protected:

  inline const XVector & xCombs() const;
  inline XVector & xCombs();
  inline const XSVector & xSecs() const;
  inline XSVector & xSecs();
  // Manipulate the list of XCombs.

  inline int binStrategy() const;
  // Return the strategy to be used when sampling different XComb
  // objects. 0 means all XComb objects are sampled together. 1 means
  // all XComb objects which have the same matrix element object are
  // sampled together. 2 means all XComb objects are sampled separately.


private:

  inline const SubHandlerList & subProcesses() const;
  inline SubHandlerList & subProcesses();
  // Access to the list of sub-process handlers.

private:

  PDPtr theIncomingA;
  PDPtr theIncomingB;
  cPDPair theIncoming;
  // The incoming particles. The pair is assigned the A and B pointers
  // in doinit().

  SubHandlerList theSubProcesses;
  // The list of sub-process handlers.

  KinCutPtr theCuts;
  // The kinematica cuts used for this collision handler.

  XVector theXCombs;
  // The XComb objects.

  XSVector theXSecs;
  // The (incrementally summed) cross sections associated with the
  // XComb objects for the last selected phase space point.

  int theBinStrategy;
  // The strategy to be used when sampling different XComb objects. 0
  // means all XComb objects are sampled together. 1 means all XComb
  // objects which have the same matrix element object are sampled
  // together. 2 means all XComb objects are sampled separately.

  MEXMap theMEXMap;
  // The map used to store all XBins with the same matrix element for
  // option 1 in theBinStrategy.

  vector<int> theMaxDims;
  // The number of degrees of freedom needed to generate the phase
  // space for the different bins.

  LorentzRotation theCurrentEventBoost;
  // The boost needed to transform the current collision from the CMS
  // system to the lab system.

private:

  static ClassDescription<CollisionHandler> initCollisionHandler;
  // Standard Initialization object.

  const CollisionHandler & operator=(const CollisionHandler &);
  // Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<CollisionHandler,1> {
  typedef PartialCollisionHandler NthBase;
};

template <>
struct ClassTraits<CollisionHandler>: public ClassTraitsBase<CollisionHandler> {
  static string className() {
    return "/ThePEG/CollisionHandler";
  }
};

}

#include "CollisionHandler.icc"

#endif /* ThePEG_CollisionHandler_H */
