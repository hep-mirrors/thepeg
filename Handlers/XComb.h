// -*- C++ -*-
//
// XComb.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_XComb_H
#define ThePEG_XComb_H
// This is the declaration of the XComb class.

#include "ThePEG/PDF/PartonExtractor.fh"
#include "ThePEG/PDF/PartonBin.h"
#include "ThePEG/PDF/PartonBinInstance.h"
#include "ThePEG/Utilities/VSelector.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Maths.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/Handlers/EventHandler.fh"
#include "ThePEG/Cuts/Cuts.fh"
// #include "XComb.fh"
// #include "XComb.xh"

namespace ThePEG {

/**
 * The XComb class stores all information about the generation of a
 * hard sub-proces for a given pair of incoming particles, a pair of
 * extracted partons, total parton-parton energy squared and a
 * PartonExtractor object.
 *
 * When an event is generated, the objects used in the generation can
 * be assigned an XComb object for easy acces to the corresponding
 * information. To facilitate this, the corresponding classes inherits
 * from the LastXCombInfo class which provides the relefant access
 * functions.
 *
 * @see PartonExtractor
 * @see Cuts
 * @see LastXCombInfo
 */
class XComb: public Base {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Standard constructor.
   */
  XComb(Energy newMaxEnergy, const cPDPair & inc,
	tEHPtr newEventHandler,	tPExtrPtr newExtractor, tCascHdlPtr newCKKW,
	const PBPair & newPartonBins,	tCutsPtr newCuts);

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
  //@}



  /** @name Access the assigned objects used in the generation. */
  //@{
  /**
   * Return a reference to the corresponding collision handler
   */
  inline const EventHandler & eventHandler() const;

  /**
   * A pointer to the parton extractor.
   */
  inline tPExtrPtr pExtractor() const;

  /**
   * A pointer to the kinematical cuts.
   */
  inline tCutsPtr cuts() const;

  /**
   * Return a possibly null pointer to a CascadeHandler to be used for
   * CKKW-reweighting.
   */
  inline tCascHdlPtr CKKWHandler() const;
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

  /** @name Manipulate and acces information about the last selected
      phase space point. */
  //@{

  /**
   * Reset all saved data about last generated phasespace point;
   */
  void clean();

  /**
   * Set information about currently generated partons.
   */
  void setPartonBinInstances(PBIPair pbis, Energy2 scale);

  /**
   * Prepare this XComb for producing a sub-process.
   */
  void prepare(const PPair &);

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
   * Return the SubProcess object corresponding to the last generated
   * sub-process.
   */
  inline tSubProPtr subProcess() const;

  /**
   * Set the SubProcess object corresponding to the last generated
   * sub-process.
   */
  void subProcess(tSubProPtr);

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
   * x\f$\rightarrow\f$ 1.
   */
  inline double lastE1() const;

  /**
   * Return 1-lastX2() to highest possible precision for
   * x\f$\rightarrow\f$ 1.
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

  /**
   * Get the \f$\alpha_S\f$ used in the hard scattering. Is negative
   * if no value has been set.
   */
  inline double lastAlphaS() const;

  /**
   * Set the \f$\alpha_S\f$ used in the hard scattering.
   */
  inline void lastAlphaS(double);

  /**
   * Get the \f$\alpha_{EM}\f$ used in the hard scattering. Is negative
   * if no value has been set.
   */
  inline double lastAlphaEM() const;

  /**
   * Set the \f$\alpha_{EM}\f$ used in the hard scattering.
   */
  inline void lastAlphaEM(double);
  //@}

protected:

  /**
   * Set the local parton bin info objects for this XComb.
   */
  void setPartonBinInfo();

  /**
   * Create PartonBinInstance objects for this XComb.
   */
  void createPartonBinInstances();

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
  tEHPtr theEventHandler;

  /**
   * A pointer to the parton extractor.
   */
  tPExtrPtr thePartonExtractor;

  /**
   * A pointer to a CascadeHandler to be used for CKKW-reweighting.
   */
  tCascHdlPtr theCKKW;

  /**
   * A pointer to the kinematical cuts used.
   */
  tCutsPtr theCuts;

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
   * The last rapidity of the sub process, log(x1/x2)/2.
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
   * x\f$\rightarrow\f$ 1.
   */
  DPair theLastE1E2;

  /**
   * The last chosen scale of the hard scattering.
   */
  Energy2 theLastScale;

  /**
   * The \f$\alpha_S\f$ used in the hard scattering.
   */
  double theLastAlphaS;

  /**
   * The \f$\alpha_{EM}\f$ used in the hard scattering.
   */
  double theLastAlphaEM;

  /**
   * The maximum cm energy for this process.
   */
  Energy theMaxEnergy;

  /**
   * Information saved by the matrix element in the calculation of the
   * cross section to be used later when selecting diagrams and colour
   * flow.
   */
  DVector theMEInfo;

  /**
   * The SubProcess object corresponding to the last generated
   * sub-process.
   */
  SubProPtr theSub;

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

/** @cond TRAITSPECIALIZATIONS */

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

/** @endcond */

}

#include "XComb.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "XComb.tcc"
#endif

#endif /* ThePEG_XComb_H */
