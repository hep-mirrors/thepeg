// -*- C++ -*-
#ifndef ThePEG_XComb_H
#define ThePEG_XComb_H
//
// This is the declaration of the <!id>XComb<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>XComb<!!id> class stores all information about the
// generation of a hard sub-proces for a given pair of incoming
// particles, a pair of extracted partons, intervals in total
// particle-particle energy squared and total parton-parton energy
// squared, a <!class>ParonExtractor<!!class> and a
// <!class>PartonXSecFn<!!class>.
//
// In the initialization the <!id>XComb<!!id> calculates an upper limit
// of the integrated cross-section using approximate information
// provided about the momentum distribution of the incoming particles,
// the momentum of the partons in the particles and the hard
// parton-parton cross-section together with a
// <!class>KinematicalCuts<!!class> object.
//
// For each event an <!id>XComb<!!id> is selected by the CollisionHandler
// according to the upper limit calculated, and a phase-space point is
// generated according to the approximate functions used in the
// intialization, and a weight is calculated in the XComb and the
// phase-space point is kept with a probability given by this weight
// and other weights calculated by the <!class>ParonExtractor<!!class>
// and <!class>PartonXSecFn<!!class>. The Monte Carlo integrated cross
// section is obtained by the ratio of accepted to attempted
// phase-space points multiplied with the calculated upper limit of.
// the cross-section
//
// Here is also defined the <!id>XCombInfo<!!id> class to be used as a
// base class of other classes which need easy access to information
// about the last generated phase-space point.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ParonExtractor.html">ParonExtractor.h</a>
// <a href="http:PartonXSecFn.html">PartonXSecFn.h</a>
// <a href="http:KinematicalCuts.html">KinematicalCuts.h</a>
// 

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

class XComb: public Base {

public:

  typedef MEBase::DiagramVector DiagramVector;
  typedef MEBase::DiagramIndex DiagramIndex;

  friend class MEBase;

public:

  XComb(Energy newMaxEnergy, const cPDPair & inc,
	tCollHdlPtr newCollisionHandler,tSubHdlPtr newSubProcessHandler,
	tPExtrPtr newExtractor,	const PBPair & newPartonBins,
	tKinCutPtr newCuts, tMEPtr newME, const DiagramVector & newDiagrams,
	bool mir);
  // Standard constructor.

  XComb(const XComb &);
  XComb();
  ~XComb();
  // Default ctors and dtor.

  XComb(tMEPtr me, const tPVector & parts, DiagramIndex i);
  // Constructor used by MEBase to create a temporary object to store info.

  void clean();
  // Reset all saved data about last generated phasespace point;

  inline const CollisionHandler & collisionHandler() const;
  // Return a reference to the corresponding collision handler

  inline const SubProcessHandler & subProcessHandler() const;
  // Return a reference to the corresponding sub-process handler

  inline const cPDPair & particles() const;
  // The incoming particle types.

  inline const cPDPair & partons() const;
  // The incoming parton types.

  inline const PBPair & partonBins() const;
  inline const PBIPair & partonBinInstances() const;
  // Additional information about the incoming partons.

  inline tPExtrPtr pExtractor() const;
  // A pointer to the parton extractor.

  inline tKinCutPtr cuts() const;
  // A pointer to the kinematical cuts.

  inline long nAccepted() const;
  inline long nAttempted() const;
  inline double sumWeight() const;
  // The number of accepted and attempted generations so far.

  inline void accept();
  // Accept the last generated phase-space point.

  inline void sumWeight(double w);
  // Sum weight of the last generated phase-space point.

  inline void unAccept();
  // The last generated phase-space point was vetoed.

  inline const PPair & lastParticles() const;
  // Return the pair of incoming particle instances.

  inline const PPair & lastPartons() const;
  // Return the pair of incoming parton instances.

  inline Energy2 lastS() const;
  // The last generated total energy squared of the incoming particles.

  inline Energy2 lastSHat() const;
  // The last generated total energy squared of the incoming prtons.

  inline double lastTau() const;
  // lastSHat()/lastS().

  inline double lastY() const;
  // The last generated rapidity of the hard scattering sub-system.

  inline double lastP1() const;
  inline double lastP2() const;
  // Log of one over the momentum fraction of the incoming particles.

  inline double lastL1() const;
  inline double lastL2() const;
  // Log of one over the incoming partons momentum fraction wrt. the
  // incoming particles.

  inline double lastX1() const;
  inline double lastX2() const;
  // The incoming partons momentum fraction wrt. the incoming
  // particles.

  inline double lastE1() const;
  inline double lastE2() const;
  // 1-lastX1() and 1-lastX2() to highest possible precision for x->1.

  inline Energy2 lastScale() const;
  inline void lastScale(Energy2);
  // Get/set the last chosen scale of the hard scattering.

  void prepare(const PPair &);
  // prepare this XComb for producing a sub-process.

  void construct(tSubProPtr);
  // Construct a sub-process object from the information available.

  inline bool empty() const;
  // Returns true if this XComb does not correspond to a proper
  // subprocess generation. I.e. if we are only generating a partial
  // event.

  inline Energy maxEnergy() const;
  // The maximum cm energy for this process.

  inline tMEPtr matrixElement() const;
  // The matrix element to be used.

  inline const DiagramVector & diagrams() const;
  // The diagrams used by the matrix element.

  inline bool mirror() const;
  // True if the TreeDiagram's for this matrix element should in fact
  // be mirrored before used to create an actual sub-rocess.

  inline int nDim() const;
  // The number of dimensions of the phase space used to generate this
  // process.

  CrossSection dSigDR(const pair<double,double> ll, int nr, const double * r);
  // Generate a phase space point and return the corresponding cross
  // section.

  inline const vector<Lorentz5Momentum> & meMomenta() const;
  inline const tPVector & mePartons() const;
  inline const cPDVector & mePartonData() const;
  // Return the momenta of the partons and the partons themselves to
  // be used by the matrix element object, in the order specified by
  // the TreeDiagram objects given by the matrix element.

  inline tcDiagPtr lastDiagram() const;
  inline DiagramIndex lastDiagramIndex() const;
  // Return the last selected diagram.

  inline const DVector & meInfo() const;
  inline void meInfo(const DVector & info);
  // Get/set information saved by the matrix element in the
  // calculation of the cross section to be used later when selecting
  // diagrams and colour flow.

protected:

  inline vector<Lorentz5Momentum> & meMomenta();
  inline tPVector & mePartons();
  // Return the momenta of the partons and the partons themselves to
  // be used by the matrix element object, in the order specified by
  // the TreeDiagram objects given by the matrix element.  

  inline void lastDiagramIndex(DiagramIndex);
  // Set the last selected diagram.

  void setPartonBinInfo();
  // Set the local parton bin info objects for this XComb.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  tCollHdlPtr theCollisionHandler;
  // The corresponding collision handler

  SubHdlPtr theSubProcessHandler;
  // The corresponding sub-process handler

  PExtrPtr thePartonExtractor;
  // A pointer to the parton extractor.

  KinCutPtr theCuts;
  // A pointer to the parton extractor.

  cPDPair theParticles;
  // The incoming particle types.

  cPDPair thePartons;
  // The incoming parton types.

  PBPair thePartonBins;
  // Additional information about the incoming partons.

  PBPair theParticleBins;
  // Additional information about the origins of the incoming partons.

  PBIPair thePartonBinInstances;
  // Additional information about the incoming partons.

  long theNAttempted;
  long theNAccepted;
  double theSumWeight;
  // The number of accepted and attempted generations so far.

  PPair theLastParticles;
  // The pair of incoming particle instances.

  PPair theLastPartons;
  // The pair of incoming parton instances.

  Energy2 theLastS;
  // The last generated total energy squared of the incoming particles.

  Energy2 theLastSHat;
  // The last generated total energy squared of the incoming prtons.

  double theLastY;
  // theLastSHat/theLastS.

  DPair theLastP1P2;
  // Log of one over the momentum fraction of the incoming particles.

  DPair theLastL1L2;
  // Log of one over the incoming partons momentum fraction wrt. the
  // incoming particles.

  DPair theLastX1X2;
  // The incoming partons momentum fraction wrt. the incoming
  // particles.

  DPair theLastE1E2;
  // 1-lastX1() and 1-lastX2() to highest possible precision for x->1.

  Energy2 theLastScale;
  // The last chosen scale of the hard scattering.

  vector<Lorentz5Momentum> theLastOutgoing;
  // The last generated outgoing partons.

  Energy theMaxEnergy;
  // The maximum cm energy for this process.

  tMEPtr theME;
  // The matrix element to be used.

  DiagramVector theDiagrams;
  // The diagrams used by the matrix element.

  bool isMirror;
  // True if the TreeDiagram's for this matrix element should in fact
  // be mirrored before used to create an actual sub-rocess.

  int theNDim;
  // The number of dimensions of the phase space used to generate this
  // process.

  pair<int,int> partonDims;
  // The number of dimensions of the phase space used for each of the
  // incoming partons.

  vector<Lorentz5Momentum> theMEMomenta;
  tPVector theMEPartons;
  cPDVector theMEPartonData;
  // The momenta of the partons and the partons themselves to be used
  // by the matrix element object, in the order specified by the
  // TreeDiagram objects given by the matrix element.

  DiagramIndex theLastDiagramIndex;
  // The last selected tree diagram.

  DVector theMEInfo;
  // Information saved by the matrix element in the calculation of the
  // cross section to be used later when selecting diagrams and colour
  // flow.

private:

  static ClassDescription<XComb> initXComb;
  // Standard Initialization object.
 

  XComb & operator=(const XComb &);
  // Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<XComb,1> {
  typedef Base NthBase;
};

template <>
struct ClassTraits<XComb>:
    public ClassTraitsBase<XComb> {
  static string className() { return "/ThePEG/XComb"; }
};

}

#include "XComb.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "XComb.tcc"
#endif

#endif /* ThePEG_XComb_H */
