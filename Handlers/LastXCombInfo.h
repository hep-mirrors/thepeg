// -*- C++ -*-
#ifndef ThePEG_LastXCombInfo_H
#define ThePEG_LastXCombInfo_H
//
// This is the declaration of the <!id>LastXCombInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/PDF/PDF.fh"
// #include "LastXCombInfo.fh"
// #include "LastXCombInfo.xh"

namespace ThePEG {

class LastXCombInfoBase {

public:

  LastXCombInfoBase();
  LastXCombInfoBase(const LastXCombInfoBase &);
  ~LastXCombInfoBase();
  // Standard ctors and dtor.

protected:

  XCombPtr theLastXComb;
  // The pointer to the last selected XComb.

};

template <int I = 0>
class LastXCombInfo: public LastXCombInfoBase {

public:

  inline LastXCombInfo();
  inline LastXCombInfo(const LastXCombInfo<I> &);
  inline LastXCombInfo & operator=(const LastXCombInfo<I> &);
  // Default ctors and assignment.

  inline const XComb & lastXComb() const;
  inline tXCombPtr lastXCombPtr() const;
  // Return a reference (pointer) to the last selected XComb.

  inline const CollisionHandler & lastCollisionHandler() const;
  // Return a reference to the currently used collision handler

  inline const SubProcessHandler & lastSubHandler() const;
  // Return a reference to the currently used sub-process handler

  inline tPExtrPtr lastExtractor() const;
  // A pointer to the last used parton extractor.

  inline tMEPtr lastME() const;
  // A pointer to the last used matrix element.

  inline PDF pdf(tcPPtr parton) const;
  // Return the parton density used to extract the given parton.

  inline const KinematicalCuts & lastCuts() const;
  inline tKinCutPtr lastCutsPtr() const;
  // A reference (pointer) to the last used kinematical cuts.

  inline const PPair & lastParticles() const;
  // Return the pair of incoming parton instances.

  inline Energy2 lastS() const;
  // The last generated total energy squared of the incoming particles.

  inline const PPair & lastPartons() const;
  // Return the pair of incoming parton instances.

  inline Energy2 lastSHat() const;
  // The last used interval in total parton-parton energy squared

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

  inline double lastFL1L2() const;
  // The product of the momentum density functions at the last
  // generated phase-space point.

  inline Energy2 lastScale() const;
  // The last chosen scale of the hard scattering.

  inline const vector<Lorentz5Momentum> & meMomenta() const;
  inline const tPVector & mePartons() const;
  inline const cPDVector & mePartonData() const;
  // Return the momenta of the partons and the partons themselves to
  // be used by the matrix element object, in the order specified by
  // the TreeDiagram objects given by the matrix element.

  inline const DVector & meInfo() const;
  inline void meInfo(const DVector & info) const;
  // Get/set information saved by the matrix element in the
  // calculation of the cross section to be used later when selecting
  // diagrams and colour flow.
  

};

}

#include "LastXCombInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LastXCombInfo.tcc"
#endif

#endif /* ThePEG_LastXCombInfo_H */
