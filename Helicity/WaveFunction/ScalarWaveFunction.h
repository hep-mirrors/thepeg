// -*- C++ -*-
//
// ScalarWaveFunction.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_ScalarWaveFunction_H
#define ThePEG_ScalarWaveFunction_H
//
// This is the declaration of the ScalarWaveFunction class.

#include "WaveFunctionBase.h"
#include <ThePEG/Helicity/ScalarSpinInfo.h>
#include <ThePEG/EventRecord/Particle.h>
#include <ThePEG/Helicity/RhoDMatrix.h>

namespace ThePEG {
namespace Helicity {

/** \ingroup Helicity
 *  \author Peter Richardson
 * 
 *  This class is the base class for scalar wavefunctions for use in 
 *  helicity amplitude calculations. The general approach 
 *  is to use a similar philosophy to the FORTRAN HELAS code but with 
 *  additional structure.
 *
 *  This class stores the scalar wavefunction as a complex number and inherits
 *  from the WaveFunctionBase class for the storage of the particles
 *  momentum and type.
 * 
 *  @see WaveFunctionBase
 */
class ScalarWaveFunction : public WaveFunctionBase {

public:

  /** @name Standard constructors and destructors. */
  //@{

  /**
   * Constructor, set the momentum, direction and Wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer
   * @param wave The wavefunction.
   * @param dir The direction of the particle.
   */
  ScalarWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		     Complex wave,Direction dir=intermediate) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    _wf=wave;
  }

  /**
   * Constructor,set the 5-momentum and zero the wavefunction.
   * @param p The 5-momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction of the particle.
   */
  ScalarWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,Direction dir) {
    direction(dir);
    setMomentum(p);
    _wf=1.;
    checkParticle(part);
  }

  static void calculateWaveFunctions(RhoDMatrix & rho,
				     tPPtr, Direction) {
    rho=RhoDMatrix(PDT::Spin0);
  }

  static void constructSpinInfo(tPPtr part,Direction, bool time) {
    tScalarSpinPtr inspin;
    if(part->spinInfo()) inspin=dynamic_ptr_cast<tScalarSpinPtr>(part->spinInfo());
    if(inspin) return;
    assert(!part->spinInfo());
    ScalarSpinPtr temp = new_ptr(ScalarSpinInfo(part->momentum(),time));
    part->spinInfo(temp);
  }

  /**
   * Default constructor.
   */
  ScalarWaveFunction() {
    _wf=1.;
  }

  /**
   *  Special for spin correlations
   */
  ScalarWaveFunction(tPPtr part,Direction dir,bool time) {
    direction(dir);
    setMomentum(part->momentum());
    checkParticle(part->dataPtr());
    _wf=1.;
    constructSpinInfo(part,dir,time);
  }

  /**
   * Return the wavefunction.
   */
  const Complex & wave() const {return _wf;}

  /**
   * Functions to reset the wavefunction and momentum (to speed the code up).
   */
  //@{
  /**
   * Reset the momentum, particle type and direction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  void reset(const Lorentz5Momentum & p, const tcPDPtr & part, Direction dir) {
    direction(dir);
    checkParticle(part);
    setMomentum(p);
  }

  /**
   * Reset the momentum and particle type.
   * @param p The momentum.
   * @param dir The direction.
   */
  void reset(const Lorentz5Momentum & p,Direction dir) {
    direction(dir);
    setMomentum(p);
  }

  /**
   * Reset the momentum.
   * @param p The momentum.
   */
  void reset(const Lorentz5Momentum & p) {setMomentum(p);}

  /**
   * Reset the wavefunction.
   * @param wave The wavefunction
   */
  void reset(Complex wave) {_wf=wave;}

  /**
   * Reset the particle type and direction.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  void reset(const tcPDPtr & part,Direction dir) {
    direction(dir);
    checkParticle(part);
  }

  /**
   * Reset the particle type.
   * @param part The ParticleData pointer.
   */
  void reset(const tcPDPtr & part) {checkParticle(part);}
  //@}  

private:
  
  /**
   * Check the particle type.
   * @param part The ParticleData pointer.
   */
  void checkParticle(const tcPDPtr & part) {
    setParticle(part);
    assert(iSpin()==1);
  }

private:

  /**
   * Complex number to store the wavefunction.
   */
  Complex _wf;

};
}
}

#endif
