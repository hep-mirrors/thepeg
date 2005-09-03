// -*- C++ -*-
#ifndef ThePEG_SpinBase_H
#define ThePEG_SpinBase_H
// This is the declaration of the SpinBase class.

#include "ThePEG/EventRecord/EventInfoBase.h"
// #include "SpinBase.fh"
// #include "SpinBase.xh"

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
   * Default constructor.
   */
  inline SpinBase();

  /**
   * Copy constructor.
   */
  inline SpinBase(const SpinBase &);

  /**
   * Destructor.
   */
  virtual ~SpinBase();

public:

  /**
   * Returns true if the polarization() has been implemented in a
   * subclass. This default version returns false.
   */
  virtual bool hasPolarization() const;

  /**
   * Return the angles of the polarization vector as a pair of
   * doubles. first is the polar angle and second is the azimuth
   * wrt. the particles direction. This default version of the
   * function returns 0,0, and if a subclass implements a proper
   * function it should also implement 'hasPolarization()' to return
   * true.
   */
  virtual DPair polarization() const;

  /**
   * Perform a lorentz rotation of the spin information assuming the
   * particle has the given momentum before the boost. This default
   * method does nothing.
   */
  virtual void transform(const LorentzMomentum &, LorentzRotation r);

public:

  /**
   * Rebind to cloned objects. If a SpinBase is cloned together
   * with a whole Event and this has pointers to other event record
   * objects, these should be rebound to their clones in this
   * function.
   */
  virtual void rebind(const EventTranslationMap & trans);

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

  /**
   * Standard clone method.
   */
  inline virtual EIPtr clone() const;

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

#include "SpinBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SpinBase.tcc"
#endif

#endif /* ThePEG_SpinBase_H */
