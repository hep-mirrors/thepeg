// -*- C++ -*-
#ifndef ThePEG_SpinBase_H
#define ThePEG_SpinBase_H
//
// This is the declaration of the <!id>SpinBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>SpinBase<!!id> is the base class for adding spin information
// to a <!class>Particle<!!class>. Models may implement subclasses
// with a specific representation of the spin. The information can
// then be obtained through virtual functions in this base class or by
// dynamically casting to a specific, model dependent,
// subclass. Currently the only virtual function available in the base
// class is <!id>polarization()<!!id> which returns the polar and
// azimuth angle of the polarization vector. This is for compatibility
// with the <!id>HepMC::GenEvent<!!id> event record in CLHEP. In the
// future more functions may be added if they can be agreed upon.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Particle.html">Particle.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/EventRecord/EventInfoBase.h"
// #include "SpinBase.fh"
// #include "SpinBase.xh"

namespace ThePEG {

class SpinBase: public EventInfoBase {

public:

  inline SpinBase();
  inline SpinBase(const SpinBase &);
  virtual ~SpinBase();
  // Standard ctors and dtor.

public:

  virtual bool hasPolarization() const;
  // Returns true if the 'polarization()' has been implemented in a
  // subclass. This default version returns false.

  virtual DPair polarization() const;
  // Return the angles of the polarization vector as a pair of
  // doubles. first is the polar angle and second is the azimuth
  // wrt. the particles direction. This default version of the
  // function returns 0,0, and if a subclass implements a proper
  // function it should also implement 'hasPolarization()' to return
  // true.

  virtual void transform(const LorentzMomentum &, LorentzRotation r);
  // Perform a lorentz rotation of the spin information assuming the
  // particle has the given momentum before the boost. This default
  // method does nothing.

public:

  virtual void rebind(const EventTranslationMap & trans);

  static void Init();
  // Standard Init function used to initialize the interface.

  inline virtual EIPtr clone() const;
  // Standard clone method.

private:

  static NoPIOClassDescription<SpinBase> initSpinBase;
  // Describe concrete class without persistent data.

  SpinBase & operator=(const SpinBase &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

ThePEG_DECLARE_CLASS_TRAITS(SpinBase,EventInfoBase);

}

#include "SpinBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinBase.tcc"
#endif

#endif /* ThePEG_SpinBase_H */
