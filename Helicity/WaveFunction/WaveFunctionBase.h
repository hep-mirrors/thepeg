// -*- C++ -*-
//
// WaveFunctionBase.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_WaveFunctionBase_H
#define ThePEG_WaveFunctionBase_H
//
// This is the declaration of the WaveFunctionBase class.

#include <ThePEG/Vectors/Lorentz5Vector.h>
#include <ThePEG/Vectors/LorentzVector.h>
#include <ThePEG/PDT/ParticleData.h>
#include <ThePEG/Helicity/HelicityDefinitions.h>

namespace ThePEG {
namespace Helicity {

/** \ingroup Helicity
 *  Definition of the enumerated values used for the direction of the 
 *  particles in the calculation of the wavefunction.
 */
enum Direction 
{
  incoming, /**< An incoming particle. */
  outgoing, /**< An outgoing particle. */
  intermediate /**< An intermediate particle. */
};

/** \ingroup Helicity
 *  \author Peter Richardson
 *
 * This class is the base class for all wavefunctions for use in helicity amplitude
 * calculations. The general approach is to use a similar philosophy 
 * to the FORTRAN HELAS code but with additional structure.
 *
 * This class contains the storage of the particle type and 5-momentum 
 * and methods to set/access this information.
 *
 * The methods for the wavefunction itself will be implemented in the classes
 * derived from this one for the specific spin type, for example scalar, spinor,
 * vector and tensor. 
 *
 *  @see ScalarWaveFunction
 *  @see SpinorWaveFunction
 *  @see SpinorBarWaveFunction
 *  @see VectorWaveFunction
 *  @see RSSpinorWaveFunction
 *  @see RSSpinorBarWaveFunction
 *  @see TensorWaveFunction
 */
class WaveFunctionBase{

public:

  /**
   * Access to the momentum components and mass
   */
  //@{
  /**
   * Get the x component of the momentum.
   */
  Energy px() const {return _momentum.x();}

  /**
   * Get the y component of the momentum.
   */
  Energy py() const {return _momentum.y();}

  /**
   * Get the z component of the momentum.
   */
  Energy pz() const {return _momentum.z();}

  /**
   * Get the energy.
   */
  Energy e()  const {return _momentum.e();}

  /**
   * Get the mass.
   */
  Energy mass() const {return _momentum.mass();}

  /**
   * Get off-shell mass squared.
   */
  Energy2 m2() const {return _momentum.m2();}

  /**
   *  Access to the 5-momentum
   */
  const Lorentz5Momentum & getMomentum() const {return _momentum;}
  //@}

  /**
   * Set the components of the momentum and the mass
   */
  //@{
  /**
   * Set the x component of the momentum.
   */
  void setPx(Energy x) {_momentum.setX(x);}

  /**
   * Set the y component of the momentum.
   */
  void setPy(Energy y) {_momentum.setY(y);}

  /**
   * Set the z component of the momentum.
   */
  void setPz(Energy z) {_momentum.setZ(z);}

  /**
   * Set the energy.
   */
  void setE(Energy t) {_momentum.setT(t);}

  /**
   * Set the mass.
   */
  void setMass(Energy m) {_momentum.setMass(m);}

  /**
   * Set 5 momentum.
   */
  void setMomentum(const Lorentz5Momentum & pin) {
    if(_dir==outgoing)
      _momentum=Lorentz5Momentum(-pin.x(),-pin.y(),-pin.z(),
				 -pin.t(),pin.mass());
    else if(_dir==incoming||_dir==intermediate)
      _momentum=pin;
  }

  /**
   * Set all components of momentum.
   * @param px The x-component of the momentum.
   * @param py The x-component of the momentum.
   * @param pz The x-component of the momentum.
   * @param E  The energy.
   * @param m  The mass.
   */
  void setMomentum(Energy px,Energy py,Energy pz,Energy E,Energy m) {
    if(_dir==outgoing)                
      _momentum=Lorentz5Momentum(-px,-py,-pz,-E,m);
    else if(_dir==incoming||_dir==intermediate) 
      _momentum=Lorentz5Momentum( px, py, pz, E,m);
  }

  /** 
   * Set 4-momentum components.
   * @param px The x-component of the momentum.
   * @param py The x-component of the momentum.
   * @param pz The x-component of the momentum.
   * @param E  The energy.
   */
  void setMomentum(Energy px,Energy py,Energy pz,Energy E) {
    if(_dir==outgoing)
      _momentum=Lorentz5Momentum(-px,-py,-pz,-E);
    else if(_dir==incoming||_dir==intermediate)
      _momentum=Lorentz5Momentum( px, py, pz, E);
  }

  /** 
   * Set 4-momentum using a vector.
   * @param p The momentum.
   */
  void setMomentum(const LorentzMomentum & p) {
    if(_dir==outgoing)
      _momentum=Lorentz5Momentum(-p);
    else if(_dir==incoming||_dir==intermediate)
      _momentum=Lorentz5Momentum(p);
  }
  
  /**
   * Set mass and zero momentum.
   * @param m The mass
   */
  void setMomentum(Energy m) {
    _momentum=Lorentz5Momentum(m);
    if(_dir==outgoing) _momentum.setT(-_momentum.t());
  }
  
  /**
   * Set 4 momentum and mass.
   * @param p The momentum.
   * @param m The mass
   */
  void setMomentum(const LorentzMomentum & p,Energy m) {
    if(_dir==outgoing) 
      _momentum=Lorentz5Momentum(-p,m);
    else if(_dir==incoming||_dir==intermediate) 
      _momentum=Lorentz5Momentum(p,m);
  }
  
  /**
   * Zero the 4 momentum and mass.
   */
  void setMomentum() {
    _momentum=Lorentz5Momentum();
  }
  //@}

  /**
   *  Access to the particle properties
   */
  //@{
  /** 
   * Get the particle id.
   */
  int id() {return _particle->id();}

  /** 
   * Get 2s+1 for the particle.
   */
  PDT::Spin iSpin() {return _particle->iSpin();}

  /**
   * Get the particle pointer.
   */
  const tcPDPtr & getParticle() const {return _particle;}

  /** 
   * Get the direction of particle.
   */
  ThePEG::Helicity::Direction direction() const {return _dir;}

  /**
   * Set the direction of the particle
   */
  void direction(ThePEG::Helicity::Direction in) {_dir=in;}
  //@}

protected:

  /**
   * Set the particle pointer.
   */
  void setParticle(const tcPDPtr & in) {
    if(_dir==incoming) {
      tcPDPtr anti((in->CC()));
      _particle = anti ? anti : in;
    }
    else
      _particle=in;
  }
  
private:

  /**
   * Check particle type and set pointer.
   */
  void checkParticle(const tcPDPtr & in) {setParticle(in);}

private:

  /**
   * Constant pointer to the particle info.
   */
  tcPDPtr _particle;

  /**
   * Lorentz 5 momentum.
   */
  Lorentz5Momentum _momentum;

  /**
   * Incoming or outgoing.
   */
  Direction _dir;
};
}
}

#endif
