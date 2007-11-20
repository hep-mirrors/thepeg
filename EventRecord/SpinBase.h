// -*- C++ -*-
//
// SpinBase.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_SpinBase_H
#define ThePEG_SpinBase_H
// This is the declaration of the SpinBase class.

#include "ThePEG/EventRecord/EventInfoBase.h"

namespace ThePEG {

/**
 * <code>SpinBase</code> is the base class for adding spin information
 * to a Particle. Models may implement subclasses
 * with a specific representation of the spin. The information can
 * then be obtained through virtual functions in this base class or by
 * dynamically casting to a specific, model dependent,
 * subclass. Currently the only virtual function available in the base
 * class is <code>polarization()</code> which returns the polar and
 * azimuth angle of the polarization vector. This is for compatibility
 * with the <code>HepMC::GenEvent</code> event record in CLHEP. In the
 * future more functions may be added if they can be agreed upon.
 *
 * @see Particle
 */
class SpinBase: public EventInfoBase {

public:

  /**
   * Returns true if the polarization() has been implemented in a
   * subclass. This default version returns false.
   */
  virtual bool hasPolarization() const { return false; }

  /**
   * Return the angles of the polarization vector as a pair of
   * doubles. first is the polar angle and second is the azimuth
   * wrt. the particles direction. This default version of the
   * function returns 0,0, and if a subclass implements a proper
   * function it should also implement 'hasPolarization()' to return
   * true.
   */
  virtual DPair polarization() const { return DPair(); }

  /**
   * Perform a lorentz rotation of the spin information assuming the
   * particle has the given momentum before the boost. This default
   * method does nothing.
   */
  virtual void transform(const LorentzMomentum &, LorentzRotation) {}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init() {}

  /**
   * Standard clone method.
   */
  virtual EIPtr clone() const { return new_ptr(*this); }

private:

  /**
   * Describe concrete class without persistent data.
   */
  static NoPIOClassDescription<SpinBase> initSpinBase;

  /**
   *  Private and non-existent assignment operator.
   */
  SpinBase & operator=(const SpinBase &);

};


/** @cond TRAITSPECIALIZATIONS */
ThePEG_DECLARE_CLASS_TRAITS(SpinBase,EventInfoBase);
/** @endcond */

}

#endif /* ThePEG_SpinBase_H */
