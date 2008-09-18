// -*- C++ -*-
//
// SpinorWaveFunction.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_SpinorWaveFunction_H
#define ThePEG_SpinorWaveFunction_H
//
// This is the declaration of the SpinorWaveFunction class.
//
#include "WaveFunctionBase.h"
#include <ThePEG/Helicity/LorentzSpinor.h>
#include <ThePEG/Helicity/FermionSpinInfo.h>
#include <ThePEG/EventRecord/Particle.h>
#include <ThePEG/Helicity/RhoDMatrix.h>

namespace ThePEG {

namespace Helicity {

/**
 *  Forward declaration of the SpinorBarWaveFunction class
 */
class SpinorBarWaveFunction;

/** \ingroup Helicity
 *  \author Peter Richardson
 *
 *  The SpinorWaveFunction class is designed to store the wavefunction
 *  of a spinor in a form suitable for use in helicity amplitude calculations 
 *  of the matrix element using a similar philosophy to the FORTRAN HELAS code.
 *
 *  In addition to storing the spinor using the LorentzSpinor class
 *  it inherits from the WaveFunctionBase class to provide storage of
 *  the momentum and particleData for the fermion.
 *
 *  This class also contains the code which does the actually calculation 
 *  of the spinor for an external particle using either of the Dirac matrix 
 *  representations currently supported in the HelicityDefinitions class.
 *
 *  When calculating the wavefunction the direction of the particle is used,
 *
 *  \e i.e. 
 *  - incoming calculates a \f$u\f$ spinor.
 *  - outgoing calculates a \f$v\f$ spinor.
 *
 *  N.B. In our convention 0 is the \f$-\frac12\f$ helicity state and 
 *        1 is the \f$+\frac12\f$ helicity state
 *
 *  @see WaveFunctionBase
 *  @see LorentzSpinor
 *  @see HelicityDefinitions
 */
class SpinorWaveFunction : public WaveFunctionBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Constructor, set the momentum and the components of the spinor and Dirac
   * matrix representation.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param s1 The first component
   * @param s2 The second component
   * @param s3 The third component
   * @param s4 The fourth component
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,complex<double> s1,
		     complex<double> s2,complex<double> s3,complex<double> s4,
		     DiracRep drep=defaultDRep) {
    direction(intermediate);
    setMomentum(p);
    checkParticle(part);
    _wf = LorentzSpinor<double>(s1,s2,s3,s4,drep);
  }

  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param wave The wavefunction.
   * @param dir The direction of the particle
   */
  SpinorWaveFunction(const Lorentz5Momentum & p, const tcPDPtr & part,
		     const LorentzSpinor<double> & wave,
		     Direction dir=intermediate) {
    direction(dir);
    setMomentum(p);
    checkParticle(part); 
    _wf=wave;
  }

  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The particle
   * @param wave The wavefunction.
   * @param dir The direction of the particle
   */
  SpinorWaveFunction(const tPPtr & p, const LorentzSpinor<SqrtEnergy> & wave,
		     Direction dir=intermediate) {
    direction(dir);
    setMomentum(p->momentum());
    checkParticle(p->dataPtr()); 
    _wf = LorentzSpinor<double>(wave.Type(), wave.Rep());
    for (unsigned int i=0; i<4; ++i)
      _wf[i]=wave[i]*UnitRemoval::InvSqrtE;
  }

  /**
   * Constructor, set the momentum, helicity, direction and Dirac representation.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		     unsigned int ihel,
		     Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Constructor, set the momentum components and mass, helicity, direction and
   * Dirac representation.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param m  The mass.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
		     const tcPDPtr & part,unsigned int ihel,Direction dir,
		     DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(px,py,pz,E,m);
    checkParticle(part); 
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Constructor, set the momentum components, helicity, direction and
   * Dirac representation.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,const tcPDPtr & part,
		     unsigned int ihel,Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(px,py,pz,E);
    checkParticle(part);
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Constructor, set the 4-momentum, helicity, direction and
   * Dirac representation.
   * @param p the 4-momentum
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const LorentzMomentum & p,
		     const tcPDPtr & part,unsigned int ihel,
		     Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Constructor, set the mass and zero the momentum, set the helicity, direction and
   * Dirac representation.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy m,const tcPDPtr & part,unsigned int ihel,
		     Direction dir, DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(m);
    checkParticle(part);
    calculateWaveFunction(ihel,drep);
  }
  
  /**
   * Constructor, set the 4-momentum, mass, helicity, direction and
   * Dirac representation.
   * @param p the 4-momentum
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const LorentzMomentum & p,
		     Energy m,const tcPDPtr & part,
		     unsigned int ihel, Direction dir,
		     DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p,m);
    checkParticle(part);
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Constructor, set the momentum, direction and Diracrepresentation, zero the 
   * wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const Lorentz5Momentum & p,
		     const tcPDPtr & part,Direction dir,
		     DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    zeroWaveFunction(drep);
  }
  
  /**
   * Constructor, set the momentum components, mass, direction and
   * Dirac representation, zero the wavefunction.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param m  The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
		     const tcPDPtr & part,
		     Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(px,py,pz,E,m);
    checkParticle(part);
    zeroWaveFunction(drep);
  }

  /**
   * Constructor, set the momentum components, direction and
   * Dirac representation, zero the wavefunction.
   * @param px The x component of the momentum.
   * @param py The y component of the momentum.
   * @param pz The z component of the momentum.
   * @param E  The energy.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,const tcPDPtr & part,
		     Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(px,py,pz,E);
    checkParticle(part);
    zeroWaveFunction(drep);
  }

  /**
   * Constructor set the 4-momentum, direction and
   * Dirac representation, zero the wavefunction.
   * @param p The 4-momentum
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const LorentzMomentum & p,
		     const tcPDPtr & part,Direction dir,
		     DiracRep drep=defaultDRep)  {
    direction(dir);
    setMomentum(p);
    checkParticle(part);
    zeroWaveFunction(drep);
  }
  
  /**
   * Constructor set the mass, direction and
   * Dirac representation, zero the momentum and wavefunction.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(Energy m,const tcPDPtr & part,Direction dir,
		     DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(m);
    checkParticle(part);
    zeroWaveFunction(drep);
  }

  /**
   * Constructor set the 4-momentum, mass, direction and
   * Dirac representation, zero the wavefunction.
   * @param p The 4-momentum
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  SpinorWaveFunction(const LorentzMomentum & p,
		     Energy m,const tcPDPtr & part,Direction dir,
		     DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p,m);
    checkParticle(part);
    zeroWaveFunction(drep);
  }
  
  /**
   * Default constructor.
   */
  SpinorWaveFunction(DiracRep drep=defaultDRep) {
    direction(intermediate);
    setMomentum();
    zeroWaveFunction(drep);
  }

  /**
   *  Special for spin correlations
   */
  SpinorWaveFunction(vector<SpinorWaveFunction> & wave,
		     tPPtr part,Direction dir,bool time,bool=true) {
    calculateWaveFunctions(wave,part,dir);
    constructSpinInfo(wave,part,dir,time);
  }
  //@}

  /**
   *  Access to the wavefunction and its components.
   */
  //@{
  /**
   * Subscript operator for the wavefunction.
   */
  complex<double> operator ()(int i) const {
    assert(i>=0 &&i<=3);
    return _wf(i);
  }

  /**
   * Set components by index.
   */
  complex<double> & operator () (int i) {
    assert(i>=0 &&i<=3);
    return _wf(i);
  }

  /**
   * Return wavefunction as LorentzSpinor<double>.
   */
  const LorentzSpinor<double> & wave() const {return _wf;}

  /**
   * Return wavefunction as LorentzSpinor<SqrtEnergy>.
   */
  LorentzSpinor<SqrtEnergy> dimensionedWave() const {return dimensionedWf();}

  /**
   * Get the first spin component component.
   */
  complex<double> s1() const {return _wf.s1();}

  /**
   * Get the second spin component component.
   */
  complex<double> s2() const {return _wf.s2();}

  /**
   * Get the third spin component component.
   */
  complex<double> s3() const {return _wf.s3();}

  /**
   * Get the fourth spin component component.
   */
  complex<double> s4() const {return _wf.s4();}

  /**
   * Set first spin component.
   */
  void setS1(complex<double> in) {_wf.setS1(in);}

  /**
   * Set second spin component.
   */
  void setS2(complex<double> in) {_wf.setS2(in);}

  /**
   * Set third spin component.
   */
  void setS3(complex<double> in) {_wf.setS3(in);}

  /**
   * Set fourth spin component.
   */
  void setS4(complex<double> in) {_wf.setS4(in);}
  //@}

  /**
   * Take the conjugate of the spinor \f$u_c=C\bar{u}^T\f$. This operation
   * transforms u-spinors to v-spinors and vice-versa and is required when
   * dealing with majorana particles.
   */
  void conjugate() {
    _wf=_wf.conjugate();
  }

  /**
   * Return the barred spinor
   */
  SpinorBarWaveFunction bar();

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
  void reset(const Lorentz5Momentum & p, const tcPDPtr & part,
	     Direction dir) {
    direction(dir);
    checkParticle(part);
    setMomentum(p);
  }

  /** 
   * Reset the momentum and direction
   * @param p The momentum.
   * @param dir The direction
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
   * Reset the helicity (calculates the new spinor).
   * @param ihel The helicity (0,1 as described above.)
   * @param drep The Dirac matrix representation.
   */
  void reset(unsigned int ihel,DiracRep drep=defaultDRep) {
    calculateWaveFunction(ihel,drep);
  }

  /**
   * Reset particle type and direction.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  void reset(const tcPDPtr & part,Direction dir) {
    direction(dir);
    checkParticle(part);
  }

  /**
   * Reset particle type.
   * @param part The ParticleData pointer.
   */
  void reset(const tcPDPtr & part) {
    checkParticle(part);
  }
  //@}

public:

  static void calculateWaveFunctions(vector<LorentzSpinor<SqrtEnergy> > & waves,
				     tPPtr particle,Direction);
  static void calculateWaveFunctions(vector<SpinorWaveFunction> & waves,
				     tPPtr particle,Direction);
  static void calculateWaveFunctions(vector<LorentzSpinor<SqrtEnergy> > & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction);
  static void calculateWaveFunctions(vector<SpinorWaveFunction> & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction);

  static void constructSpinInfo(const vector<LorentzSpinor<SqrtEnergy> > & waves,
				tPPtr part,Direction dir, bool time);
  static void constructSpinInfo(const vector<SpinorWaveFunction> & waves,
				tPPtr part,Direction dir, bool time);
  

private:

  /**
   * Zero the wavefunction.
   */
  void zeroWaveFunction(DiracRep drep=defaultDRep) {
    _wf=LorentzSpinor<double>(drep);
  }

  /**
   * Calcuate the wavefunction.
   * @param ihel The helicity (0,1 as described above.)
   * @param drep The Dirac matrix representation.
   */
  void calculateWaveFunction(unsigned int ihel,DiracRep drep=defaultDRep);

  /**
   * Check particle spin and set pointer.
   * @param part The ParticleData pointer.
   */
  void checkParticle(const tcPDPtr & part)  {
    setParticle(part);
    assert(iSpin()==2);
  }

private:

  /**
   * Storage of the Lorentz Spinor.
   */
  LorentzSpinor<double> _wf;

  /// Return wavefunction as LorentzSpinor<SqrtEnergy>
  LorentzSpinor<SqrtEnergy> dimensionedWf() const {
    LorentzSpinor<SqrtEnergy> temp(_wf.Type(),_wf.Rep());
    for (unsigned int i=0; i<4; ++i)
      temp(i) = _wf(i)*UnitRemoval::SqrtE;
    return temp;
  }
  
};

}

}
#endif




