// -*- C++ -*-
#ifndef ThePEG_XComb_H
#define ThePEG_XComb_H
// This is the declaration of the XComb class.

#include "SubProcessHandler.fh"
#include "ThePEG/PDF/PartonExtractor.fh"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/Utilities/VSelector.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Math.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/MatrixElement/MEBase.h"
// #include "XComb.fh"
// #include "XComb.xh"

namespace ThePEG {

/**
 * The XComb class stores all information about the generation of a
 * hard sub-proces for a given pair of incoming particles, a pair of
 * extracted partons, total parton-parton energy squared, a
 * ParonExtractor and a MEBase object.
 *
 * The main function is dSigDR() which returns the differential cross
 * section w.r.t. a given vector of random numbers in the interval
 * ]0,1[. In the initialization this is used to pre-sample the phase
 * space. In the generation phase it is used to give the cross section
 * for a phase space point, and if this XComb is chosen the
 * construct() function is called to generate the actual sub-process.
 *
 * @see ParonExtractor
 * @see MEBase
 * @see KinematicalCuts
 */
class XComb: public Base {

public:

  /** A vector of DiagramBase objects. */
  typedef MEBase::DiagramVector DiagramVector;

  /** A vector of indices. */
  typedef MEBase::DiagramIndex DiagramIndex;

  /** MEBase needs to be a friend. */
  friend class MEBase;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Standard constructor.
   */
  XComb(Energy newMaxEnergy, const cPDPair & inc,
	tCollHdlPtr newCollisionHandler,tSubHdlPtr newSubProcessHandler,
	tPExtrPtr newExtractor,	const PBPair & newPartonBins,
	tKinCutPtr newCuts, tMEPtr newME, const DiagramVector & newDiagrams,
	bool mir);

  /**
   * Standard constructor used by sub classes.
   */
  XComb(Energy newMaxEnergy, const cPDPair & inc,
	tCollHdlPtr newCollisionHandler, tSubHdlPtr newSubProcessHandler,
	tPExtrPtr newExtractor,	const PBPair & newPartonBins,
	tKinCutPtr newCuts, tMEPtr newME);

  /**
   * Copy-constructor.
   */
  XComb(const XComb &);

  /**
   * Default constructor.
   */
  XComb();

  /**
   * Destructor.
   */
  ~XComb();

  /**
   * Constructor used by MEBase to create a temporary object to store info.
   */
  XComb(tMEPtr me, const tPVector & parts, DiagramIndex i);
  //@}

  /** @name Access the assigned objects used in the generation. */
  //@{
  /**
   * Return a reference to the corresponding collision handler
   */
  inline const CollisionHandler & collisionHandler() const;

  /**
   * Return a pointer to the corresponding sub-process handler. May be
   * null if the standard process generation in ThePEG was not used.
   */
  inline tcSubHdlPtr subProcessHandler() const;

  /**
   * A pointer to the parton extractor.
   */
  inline tPExtrPtr pExtractor() const;

  /**
   * The matrix element to be used.
   */
  inline tMEPtr matrixElement() const;

  /**
   * A pointer to the kinematical cuts.
   */
  inline tKinCutPtr cuts() const;
  //@}

  /** @name Access information about incoming particles and partons. */
  //@{
  /**
   * The incoming particle types.
   */
  inline const cPDPair & particles() const;

  /**
   * The incoming parton types.
   */
  inline const cPDPair & partons() const;

  /**
   * Additional information about the incoming partons.
   */
  inline const PBPair & partonBins() const;

  /**
   * The maximum cm energy for this process.
   */
  inline Energy maxEnergy() const;

  /**
   * Returns true if this XComb does not correspond to a proper
   * subprocess generation. I.e. if we are only generating a partial
   * event and the incoming particles and partons are not used
   * explicitly.
   */
  inline bool empty() const;
  //@}

  /** @name Functions used for collecting statistics. */
  //@{
  /**
   * The number of attempted generations so far.
   */
  inline long nAccepted() const;

  /**
   * The number of accepted generations so far.
   */
  inline long nAttempted() const;

  /**
   * The sum of accumulated weights.
   */
  inline double sumWeight() const;

  /**
   * Increase the number of attempted generations.
   */
  inline void attempt();

  /**
   * Accept the last generated phase-space point.
   */
  inline void accept();

  /**
   * Sum weight of the last generated phase-space point.
   */
  inline void sumWeight(double w);

  /**
   * The last generated phase-space point was vetoed.
   */
  inline void unAccept();

  /**
   * Reset statistics.
   */
  inline void reset();
  //@}

  /** @name Acces information about the last selected phase space point. */
  //@{
  /**
   * Reset all saved data about last generated phasespace point;
   */
  void clean();

  /**
   * Return the pair of incoming particle instances.
   */
  inline const PPair & lastParticles() const;

  /**
   * Return the pair of incoming parton instances.
   */
  inline const PPair & lastPartons() const;

  /**
   * Set the pair of incoming parton instances.
   */
  inline void lastPartons(PPair);

  /**
   * Additional information about the incoming partons.
   */
  inline const PBIPair & partonBinInstances() const;

  /**
   * The last generated total energy squared of the incoming particles.
   */
  inline Energy2 lastS() const;

  /**
   * Set the last generated total energy squared of the incoming
   * particles.
   */
  inline void lastS(Energy2);

  /**
   * The last generated total energy squared of the incoming prtons.
   */
  inline Energy2 lastSHat() const;

  /**
   * Set the last generated total energy squared of the incoming
   * prtons.
   */
  inline void lastSHat(Energy2);

  /**
   * lastSHat()/lastS().
   */
  inline double lastTau() const;

  /**
   * The last generated rapidity of the hard scattering sub-system.
   */
  inline double lastY() const;

  /**
   * Set the last generated rapidity of the hard scattering sub-system.
   */
  inline void lastY(double);

  /**
   * Log of one over the momentum fraction of the first incoming
   * particle w.r.t. the maximum allowed energy.
   */
  inline double lastP1() const;

  /**
   * Log of one over the momentum fraction of the second incoming
   * particle w.r.t. the maximum allowed energy.
   */
  inline double lastP2() const;

  /**
   * Set log of one over the momentum fraction of the incoming
   * particles w.r.t. the maximum allowed energy.
   */
  inline void lastP1P2(pair<double,double>);

  /**
   * Log of one over the first incoming parton momentum fraction
   * w.r.t. the first incoming particle.
   */
  inline double lastL1() const;

  /**
   * Log of one over the second incoming parton momentum fraction
   * w.r.t. the second incoming particle.
   */
  inline double lastL2() const;

  /**
   * Set log of one over the incoming parton momentum fractions
   * w.r.t. the incoming particles.
   */
  inline void lastL1L2(pair<double,double>);

  /**
   * The first incoming parton momentum fraction w.r.t. the
   * first incoming particle.
   */
  inline double lastX1() const;

  /**
   * The second incoming parton momentum fraction
   * w.r.t. the second incoming particle.
   */
  inline double lastX2() const;

  /**
   * Set the incoming parton momentum fractions w.r.t. the incoming
   * particles.
   */
  inline void lastX1X2(pair<double,double>);

  /**
   * Return 1-lastX1() to highest possible precision for
   * x\f$\rightarrow\f$1.
   */
  inline double lastE1() const;

  /**
   * Return 1-lastX2() to highest possible precision for
   * x\f$\rightarrow\f$1.
   */
  inline double lastE2() const;

  /**
   * Set one minus the incoming parton momentum fractions w.r.t. the
   * incoming particles.
   */
  inline void lastE1E2(pair<double,double>);

  /**
   * Get the last chosen scale of the hard scattering.
   */
  inline Energy2 lastScale() const;
  /**
   * Set the last chosen scale of the hard scattering.
   */
  inline void lastScale(Energy2);
  //@}

  /** @name Main functions used for the generation. */
  //@{
  /**
   * Try to determine if this subprocess is at all possible.
   */
  bool checkInit();

  /**
   * The number of dimensions of the phase space used to generate this
   * process.
   */
  inline int nDim() const;

  /**
   * Prepare this XComb for producing a sub-process.
   */
  void prepare(const PPair &);

  /**
   * Generate a phase space point from a vector \a r of \a nr numbers
   * in the interval ]0,1[ and return the corresponding differential
   * cross section.
   */
  CrossSection dSigDR(const pair<double,double> ll, int nr, const double * r);

  /**
   * Construct a sub-process object from the information available.
   */
  void construct(tSubProPtr);
  //@}

  /** @name Access information used by the MEBase object. */
  //@{
  /**
   * The diagrams used by the matrix element.
   */
  inline const DiagramVector & diagrams() const;

  /**
   * True if the TreeDiagram's for this matrix element should in fact
   * be mirrored before used to create an actual sub-rocess.
   */
  inline bool mirror() const;

  /**
   * Return the momenta of the partons to be used by the matrix
   * element object, in the order specified by the TreeDiagram objects
   * given by the matrix element.
   */
  inline const vector<Lorentz5Momentum> & meMomenta() const;

  /**
   * Return the partons to be used by the matrix element object, in the order
   * specified by the TreeDiagram objects given by the matrix element.
   */
  inline const tPVector & mePartons() const;

  /**
   * Return the parton types to be used by the matrix element object,
   * in the order specified by the TreeDiagram objects given by the
   * matrix element.
   */
  inline const cPDVector & mePartonData() const;

  /**
   * Return the last selected diagram.
   */
  inline tcDiagPtr lastDiagram() const;

  /**
   * Return the index of the last selected diagram.
   */
  inline DiagramIndex lastDiagramIndex() const;

  /**
   * Get information saved by the matrix element in the calculation of
   * the cross section to be used later when selecting diagrams and
   * colour flow.
   */
  inline const DVector & meInfo() const;

  /**
   * Set information saved by the matrix element in the calculation of
   * the cross section to be used later when selecting diagrams and
   * colour flow.
   */
  inline void meInfo(const DVector & info);
  //@}

protected:

  /**
   * Return the momenta of the partons to be used by the matrix
   * element object, in the order specified by the TreeDiagram objects
   * given by the matrix element.
   */
  inline vector<Lorentz5Momentum> & meMomenta();

  /**
   * Return the parton types to be used by the matrix element object,
   * in the order specified by the TreeDiagram objects given by the
   * matrix element.
   */
  inline cPDVector & mePartonData();

  /**
   * Return the partons to be used by the matrix element object, in
   * the order specified by the TreeDiagram objects given by the
   * matrix element.
   */
  inline tPVector & mePartons();

  /**
   * Set the last selected diagram.
   */
  inline void lastDiagramIndex(DiagramIndex);

  /**
   * Set the local parton bin info objects for this XComb.
   */
  void setPartonBinInfo();

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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * The corresponding collision handler
   */
  tCollHdlPtr theCollisionHandler;

  /**
   * The corresponding sub-process handler
   */
  SubHdlPtr theSubProcessHandler;

  /**
   * A pointer to the parton extractor.
   */
  PExtrPtr thePartonExtractor;

  /**
   * A pointer to the kinematical cuts used.
   */
  KinCutPtr theCuts;

  /**
   * The incoming particle types.
   */
  cPDPair theParticles;

  /**
   * The incoming parton types.
   */
  cPDPair thePartons;

  /**
   * Additional information about the incoming partons.
   */
  PBPair thePartonBins;

  /**
   * Additional information about the origins of the incoming partons.
   */
  PBPair theParticleBins;

  /**
   * Additional information about the incoming partons.
   */
  PBIPair thePartonBinInstances;

  /**
   * The number of attempted generations so far.
   */
  long theNAttempted;

  /**
   * The number of accepted generations so far.
   */
  long theNAccepted;

  /**
   * The summed weights of the generations so far..
   */
  double theSumWeight;

  /**
   * The pair of incoming particle instances.
   */
  PPair theLastParticles;

  /**
   * The pair of incoming parton instances.
   */
  PPair theLastPartons;

  /**
   * The last generated total energy squared of the incoming particles.
   */
  Energy2 theLastS;

  /**
   * The last generated total energy squared of the incoming prtons.
   */
  Energy2 theLastSHat;

  /**
   * theLastSHat/theLastS.
   */
  double theLastY;

  /**
   * Log of one over the momentum fraction of the incoming particles.
   */
  DPair theLastP1P2;

  /**
   * Log of one over the incoming partons momentum fraction wrt. the
   * incoming particles.
   */
  DPair theLastL1L2;

  /**
   * The incoming partons momentum fraction wrt. the incoming
   * particles.
   */
  DPair theLastX1X2;

  /**
   * 1-lastX1() and 1-lastX2() to highest possible precision for
   * x\f$\rightarrow\f$1.
   */
  DPair theLastE1E2;

  /**
   * The last chosen scale of the hard scattering.
   */
  Energy2 theLastScale;

  /**
   * The last generated outgoing partons.
   */
  vector<Lorentz5Momentum> theLastOutgoing;

  /**
   * The maximum cm energy for this process.
   */
  Energy theMaxEnergy;

  /**
   * The matrix element to be used.
   */
  tMEPtr theME;

  /**
   * The diagrams used by the matrix element.
   */
  DiagramVector theDiagrams;

  /**
   * True if the TreeDiagram's for this matrix element should in fact
   * be mirrored before used to create an actual sub-rocess.
   */
  bool isMirror;

  /**
   * The number of dimensions of the phase space used to generate this
   * process.
   */
  int theNDim;

  /**
   * The number of dimensions of the phase space used for each of the
   * incoming partons.
   */
  pair<int,int> partonDims;

  /**
   * The momenta of the partons to be used by the matrix element
   * object, in the order specified by the TreeDiagram objects given
   * by the matrix element.
   */
  vector<Lorentz5Momentum> theMEMomenta;

  /**
   * The partons to be used by the matrix element object, in the order
   * specified by the TreeDiagram objects given by the matrix element.
   */
  tPVector theMEPartons;

  /**
   * The parton types to be used by the matrix element object, in the
   * order specified by the TreeDiagram objects given by the matrix
   * element.
   */
  cPDVector theMEPartonData;

  /**
   * The last selected tree diagram.
   */
  DiagramIndex theLastDiagramIndex;

  /**
   * Information saved by the matrix element in the calculation of the
   * cross section to be used later when selecting diagrams and colour
   * flow.
   */
  DVector theMEInfo;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<XComb> initXComb;
 
  /**
   * Private and non-existent assignment operator.
   */
  XComb & operator=(const XComb &);

};

/**
 * This template specialization informs ThePEG about the base class of
 * XComb.
 */
template <>
struct BaseClassTrait<XComb,1>: public ClassTraitsType {
  /** Typedef of the base class of XComb. */
  typedef Base NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * XComb class.
 */
template <>
struct ClassTraits<XComb>:
    public ClassTraitsBase<XComb> {
  /** Return the class name. */
  static string className() { return "ThePEG::XComb"; }
};

}

#include "XComb.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "XComb.tcc"
#endif

#endif /* ThePEG_XComb_H */
