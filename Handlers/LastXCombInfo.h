// -*- C++ -*-
//
// LastXCombInfo.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_LastXCombInfo_H
#define ThePEG_LastXCombInfo_H
// This is the declaration of the LastXCombInfo class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Cuts/Cuts.fh"
#include "XComb.h"

namespace ThePEG {

/**
 * LastXCombInfo is a templated class giving easy access to the
 * information in an XComb object. The default template argument is
 * the basic XComb class, but also subclasses of XComb can be
 * used. Classes which need to have easy access to the last selected
 * XComb object with information about the sub-process which is being
 * generated, should (possibly multiple) inherit from the
 * LastXCombInfo class. The LastXCombInfo is templated to enable
 * derived classes to only include dependencies necessary for the
 * access function which are actually used.
 * 
 */
template <typename XC = XComb>
class LastXCombInfo {

public:

  ThePEG_DECLARE_TEMPLATE_POINTERS(XC,XCPtr);

public:

  /** @name Acces to the actual XComb object. */
  //@{
  /**
   * Return a reference to the last selected XComb.
   */
  inline const XC & lastXComb() const;

  /**
   * Return a pointer to the last selected XComb.
   */
  inline tXCPtr lastXCombPtr() const;
  //@}

  /** @name Access the objects used by the XComb object. */
  //@{
  /**
   * Return a reference to the currently used EventHandler
   */
  inline const EventHandler & lastEventHandler() const;

  /**
   * A pointer to the currently used parton extractor.
   */
  inline tPExtrPtr lastExtractor() const;

  /**
   * Return the parton density used to extract the given parton. This
   * function is templated to avoid having to include the PDF.h and
   * all its dependencies in this header.
   */
  template <typename PDFT>
  inline PDFT pdf(tcPPtr parton) const;

  /**
   * A reference to the currently used kinematical cuts.
   */
  inline const Cuts & lastCuts() const;

  /**
   * A pointer to the currently used kinematical cuts.
   */
  inline tCutsPtr lastCutsPtr() const;
  //@}

  /** @name Access information about the incoming particles and partons. */
  //@{
  /**
   * Return the pair of incoming parton instances.
   */
  inline const PPair & lastParticles() const;

  /**
   * The last generated total energy squared of the incoming particles.
   */
  inline Energy2 lastS() const;

  /**
   * Return the pair of incoming parton instances.
   */
  inline const PPair & lastPartons() const;

  /**
   * The last used interval in total parton-parton energy squared
   */
  inline Energy2 lastSHat() const;

  /**
   * Return lastSHat()/lastS().
   */
  inline double lastTau() const;

  /**
   * The generated rapidity of the hard scattering sub-system.
   */
  inline double lastY() const;

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
   * Log of one over the first incoming parton momentum fraction w.r.t. the
   * first incoming particle.
   */
  inline double lastL1() const;

  /**
   * Log of one over the second incoming parton momentum fraction
   * w.r.t. the second incoming particle.
   */
  inline double lastL2() const;

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
   * Return 1-lastX1() to highest possible precision for
   * x \f$\rightarrow\f$ 1.
   */
  inline double lastE1() const;

  /**
   * Return 1-lastX2() to highest possible precision for
   * x\f$\rightarrow\f$ 1.
   */
  inline double lastE2() const;

  /**
   * The product of the parton density functions at the last generated
   * phase-space point.
   */
  inline double lastFL1L2() const;
  //@}

  /** @name Access information of the hard sub-process. */
  //@{
  /**
   * The chosen scale of the hard scattering.
   */
  inline Energy2 lastScale() const;

  /**
   * Get the \f$\alpha_S\f$ used in the hard scattering. Is negative
   * if no value has been set.
   */
  inline double lastAlphaS() const;

  /**
   * Get the \f$\alpha_{EM}\f$ used in the hard scattering. Is negative
   * if no value has been set.
   */
  inline double lastAlphaEM() const;

  /**
   * Return the momenta of the incoming and outgoing partons to be
   * used by the matrix element object, in the order specified by the
   * TreeDiagram objects given by the matrix element.
   */
  inline const vector<Lorentz5Momentum> & meMomenta() const;

  /**
   * Return the SubProcess object corresponding to the last generated
   * sub-process.
   */
  inline tSubProPtr subProcess() const;

  /**
   * Return the incoming and outgoing parton types to be used by the
   * matrix element object, in the order specified by the TreeDiagram
   * objects given by the matrix element.
   */
  inline const cPDVector & mePartonData() const;

  //@}

protected:

  /**
   * The pointer to the last selected XComb.
   */
  XCPtr theLastXComb;

};

}

#include "LastXCombInfo.icc"

#endif /* ThePEG_LastXCombInfo_H */
