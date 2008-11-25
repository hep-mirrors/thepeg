// -*- C++ -*-
//
// VectorWaveFunction.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_VectorWaveFunction_H
#define ThePEG_VectorWaveFunction_H
//
// This is the declaration of the VectorWaveFunction class.
//
#include "WaveFunctionBase.h"
#include <ThePEG/Helicity/LorentzPolarizationVector.h>
#include <ThePEG/Helicity/VectorSpinInfo.h>
#include <ThePEG/Helicity/RhoDMatrix.h>
#include <ThePEG/EventRecord/Particle.h>

namespace ThePEG {
namespace Helicity {

/** \ingroup Helicity
 * Definition of the enumerated values of the phase to include in the 
 * calculation of the polarization vector.
 */
enum VectorPhase {
  vector_phase, /**< Include the phase factor.*/
  vector_nophase, /**< No phase-factor. */
  default_vector_phase=vector_nophase /**< Default option.*/
};

/** \ingroup Helicity
 *
 *  \author Peter Richardson
 *
 *  The VectorWaveFunction class is designed to store the wavefunction
 *  of a vector in a form suitable for use in helicity amplitude calculations 
 *  of the matrix element using a similar philosophy to the FORTRAN HELAS code.
 *
 *  In addition to storing the vector using the LorentzPolarizationVector class
 *  it inherits from the WaveFunctionBase class to provide storage of the 
 *  momentum and particleData for the vector boson.
 *
 *  This class also contains the code which does the actually calculation of the
 *  vector wavefunction.
 *
 *  There are two choices available for the calculation of the wavefunction.
 *  These are set using the VectorPhase enumeration which specifies a default choice.
 *  The first choice, vector_phase, includes a phase factor \f$\exp(\pm i \phi)\f$
 *  for the \f$\pm\f$ helicity states while the second, vector_nophase, does not.
 *
 *  N.B. In our convention 0 is the \f$-1\f$ helicity state and 
 *        1 is the \f$0\f$ helicity state
 *        2 is the \f$+1\f$ helicity state
 *
 *  @see WaveFunctionBase
 *  @see LorentzPolarizationVector
 */
class VectorWaveFunction : public WaveFunctionBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Constructor, set the momentum and Wavefunction, the direction can also
   * be specified. 
   * @param p The momentum.
   * @param part The ParticleData pointer
   * @param wave The wavefunction, \e i.e. the polarization vector.
   * @param dir The direction of the particle.
   */
  VectorWaveFunction(const Lorentz5Momentum & p,tcPDPtr part,
		     const LorentzPolarizationVector & wave,
		     Direction  dir=intermediate) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    _wf=wave;
  }

  /**
   * Constructor, set the momentum and components of the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer
   * @param x The x component of the polarization vector
   * @param y The y component of the polarization vector
   * @param z The z component of the polarization vector
   * @param t The t component of the polarization vector
   */
  VectorWaveFunction(const Lorentz5Momentum & p,tcPDPtr part,const Complex & x,
		     const Complex & y,const Complex & z, const Complex & t) {
    direction(intermediate);
    setMomentum(p);
    checkParticle(part);
    setX(x);setY(y);setZ(z);setT(t);
  }
  
  /**
   * Constructor, set the momentum, helicity and direction, optionally the choice
   * of the phase.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		     unsigned int ihel,Direction dir,
		     VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    calculateWaveFunction(ihel,phase);
  }

  /**
   * Constructor, set the momentum components and mass, helicity and direction,
   * optionally the choice of the phase.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param m  The mass.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
		     const tcPDPtr & part,unsigned int ihel,Direction dir,
		     VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(px,py,pz,E,m);
    checkParticle(part);
    calculateWaveFunction(ihel,phase);
  }

  /**
   * Constructor, set the momentum components, helicity and direction,
   * optionally the choice of the phase.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(Energy px,Energy py,Energy pz,Energy E,const tcPDPtr & part,
		     unsigned int ihel,Direction dir,
		     VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(px,py,pz,E); 
    checkParticle(part);
    calculateWaveFunction(ihel,phase);
  }
  
  /**
   * Constructor, set the 4-momentum, helicity and direction,
   * optionally the choice of the phase.
   * @param p The 4-momentum.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(const LorentzMomentum  &p,const tcPDPtr & part,
			    unsigned int ihel,Direction dir,
		     VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    calculateWaveFunction(ihel,phase);
  }

  /**
   * Constructor, set the mass, zero the momentum and set the helicity and direction,
   * optionally the choice of the phase.
   * @param m The mass. 
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(Energy m,const tcPDPtr & part,
			    unsigned int ihel,Direction dir,
			    VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(m);
    checkParticle(part);
    calculateWaveFunction(ihel,phase);
  }

  /**
   * Constructor, set the 4-momentum, mass, helicity and direction,
   * optionally the choice of the phase.
   * @param p The 4-momentum.
   * @param m The mass. 
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2 as described above.)
   * @param dir The direction.
   * @param phase The phase choice.
   */
  VectorWaveFunction(const LorentzMomentum & p,Energy m,const tcPDPtr & part,
		     unsigned int ihel,
		     Direction dir,VectorPhase phase=default_vector_phase) {
    direction(dir);
    setMomentum(p,m); 
    checkParticle(part); 
    calculateWaveFunction(ihel,phase);
  }
  
  /**
   * Constructor, set the 5-momentum and direction, zero the wavefunction.
   * @param p The 5-momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(const Lorentz5Momentum &p,
		     const tcPDPtr & part,Direction dir)  {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    zeroWaveFunction();
  }

  /**
   * Constructor, set the momentum components, mass and direction,
   * zero the wavefunction.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param m  The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
		     const tcPDPtr & part,Direction dir) {
    direction(dir);
    setMomentum(px,py,pz,E,m);
    checkParticle(part);
    zeroWaveFunction();
  }

  /**
   * Constructor, set the momentum components and direction,
   * zero the wavefunction.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(Energy px,Energy py,Energy pz,Energy E,
		     const tcPDPtr & part, Direction dir) {
    direction(dir);
    setMomentum(px,py,pz,E);
    checkParticle(part);
    zeroWaveFunction();
  }

  /**
   * Constructor, set the 4-momentum  and direction,
   * zero the wavefunction.
   * @param p The 4-momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(const LorentzMomentum & p,
		     const tcPDPtr & part,Direction dir) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    zeroWaveFunction();
  }

  /**
   * Constructor, set the mass   and direction,
   * zero the wavefunction and momentum.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(Energy m,const tcPDPtr & part,Direction dir) {
    direction(dir);
    setMomentum(m);
    checkParticle(part);
    zeroWaveFunction();
  }

  /**  
   * Constructor, set the 4-momentum, mass  and direction,
   * zero the wavefunction.
   * @param p The 4-momentum.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  VectorWaveFunction(const LorentzMomentum & p,
		     Energy m,const tcPDPtr & part,Direction dir)  {
    direction(dir);
    setMomentum(p,m);
    checkParticle(part);
    zeroWaveFunction();
  }
  
  /**
   * Default constructor.
   */
  VectorWaveFunction() {
    direction(intermediate);
    setMomentum();
    zeroWaveFunction();
  }

  /**
   *  Special for spin correlations
   */
  VectorWaveFunction(vector<VectorWaveFunction> & wave,
		     tPPtr part,Direction dir,bool time,bool massless,
		     bool=true,
		     VectorPhase phase=default_vector_phase) {
    calculateWaveFunctions(wave,part,dir,massless,phase);
    constructSpinInfo(wave,part,dir,time,massless);
  }
  //@}

  /**
   *  Access to the wavefunction and its components.
   */
  //@{
  /**
   * Return wavefunction as polarization vector. 
   */
  const LorentzPolarizationVector & wave() const { return _wf;}
  
  /**
   * Get x component.
   */
  Complex x() const {return _wf.x();}
  
  /**
   * Get y component.
   */
  Complex y() const {return _wf.y();}
  
  /**
   * Get z component.
   */
  Complex z() const {return _wf.z();}
  
  /**
   * Get t component.
   */
  Complex t() const {return _wf.t();}
  
  /**
   * Set x component
   */
  void setX(const Complex& in) {_wf.setX(in);}
  
  /**
   * Set y component
   */
  void setY(const Complex& in) {_wf.setY(in);}
  
  /**
   * Set z component
   */
  void setZ(const Complex& in) {_wf.setZ(in);}
  
  /**
   * Set t component
   */
  void setT(const Complex& in) {_wf.setT(in);}
  //@}

  /**
   * Reset functions.
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
  void reset(const Lorentz5Momentum & p) {
    setMomentum(p);
  }

  /**
   * Reset the helicity (recalculation the polarization vector).
   * @param ihel The new helicity (0,1,2 as described above.)
   * @param phase The phase choice.
   */
  void reset(unsigned int ihel,VectorPhase phase=default_vector_phase) {
    calculateWaveFunction(ihel,phase);
  }

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
  void reset(const tcPDPtr & part) {
    checkParticle(part);
  }
  //@}

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<LorentzPolarizationVector> & waves,
				     tPPtr particle,Direction,bool massless,
				     VectorPhase phase=default_vector_phase);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<VectorWaveFunction> & waves,
				     tPPtr particle,Direction,bool massless,
				     VectorPhase phase=default_vector_phase);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<LorentzPolarizationVector> & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction,bool massless,
				     VectorPhase phase=default_vector_phase);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<VectorWaveFunction> & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction,bool massless,
				     VectorPhase phase=default_vector_phase);

  /**
   *  Construct the SpinInfo object
   */
  static void constructSpinInfo(const vector<LorentzPolarizationVector> & waves,
				tPPtr part,Direction dir, bool time,bool massless);

  /**
   *  Construct the SpinInfo object
   */
  static void constructSpinInfo(const vector<VectorWaveFunction> & waves,
				tPPtr part,Direction dir, bool time,bool massless);

private:

  /** 
   * Zero the wavefunction.
   */
  void zeroWaveFunction() {
    _wf=LorentzPolarizationVector();
  }
  
  /**
   * Calculate the wavefunction
   * @param ihel The helicity  (0,1,2 as described above.)
   * @param phase The phase choice.
   */
  void calculateWaveFunction(unsigned int ihel,
			     VectorPhase phase=default_vector_phase);

  /**
   * Check the particle type.
   * @param part The ParticleData pointer.
   */
  void checkParticle(const tcPDPtr & part) {
    setParticle(part);
    assert(iSpin()==3);
  }

private:
  
  /**
   * Storage of the wavefunction as a Lorentz Vector.
   */
  LorentzPolarizationVector _wf;
  
};

}
}

#endif
