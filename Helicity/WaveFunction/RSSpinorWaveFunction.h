// -*- C++ -*-
//
// RSSpinorWaveFunction.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 2003-2007 Peter Richardson, Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef ThePEG_RSSpinorWaveFunction_H
#define ThePEG_RSSpinorWaveFunction_H
// This is the declaration of the RSSpinorWaveFunction class.

#include "WaveFunctionBase.h"
#include <ThePEG/Helicity/LorentzRSSpinor.h>
#include <ThePEG/Helicity/RSFermionSpinInfo.h>
#include <ThePEG/EventRecord/Particle.h>
#include <ThePEG/Helicity/RhoDMatrix.h>

namespace ThePEG {

namespace Helicity {

/** \ingroup Helicity
 *
 *  The RSSpinorWaveFunction class is designed to store the wavefunction
 *  of a spin-3/2 particle in a form suitable for use in helicity amplitude
 *  calculations of the matrix element using a similar philosophy to the 
 *  FORTRAN HELAS code.
 *
 *  In addition to storing the spinor using the LorentzRSSpinor class
 *  it inherits from the <code>WaveFunctionBase</code> class to provide storage of
 *  the momentum and particleData for the fermion.
 *
 *  This class also contains the code which does the actually calculation of the
 *  spinor for an external particle using either of the Dirac matrix representations
 *  currently supported in the <code>HelicityDefinitions</code> class.
 *
 *  When calculating the wavefunction the direction of the particle is used,
 *
 *  \e i.e. 
 *  - incoming calculates a \f$u\f$ spinor.
 *  - outgoing calculates a \f$v\f$ spinor.
 *
 *  The spinors are calculated using a Clebsch-Gordon decomposition in the rest-frame
 *  for a massive particle and boosted to the lab-frame. For massless particles the
 *  calculation is performed in the lab-frame (N.B. there are only two helicities
 *  \f$\pm\frac32\f$ in this case.)
 *
 *  N.B. In our convention 0 is the \f$-\frac32\f$ helicity state,
 *        1 is the \f$-\frac12\f$ helicity state,
 *        2 is the \f$+\frac12\f$ helicity state
 *        3 is the \f$+\frac32\f$ helicity state and 
 *
 * @see WaveFunctionBase
 * @see LorentzRSSpinor
 * @see HelicityDefinitions
 * 
 */
class RSSpinorWaveFunction: public WaveFunctionBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Constructor, set the momentum and the components of the spinor and Dirac
   * matrix representation.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param xs1 The first  spinor component of the \f$x\f$ vector.
   * @param xs2 The second spinor component of the \f$x\f$ vector.
   * @param xs3 The third  spinor component of the \f$x\f$ vector.
   * @param xs4 The fourth spinor component of the \f$x\f$ vector.
   * @param ys1 The first  spinor component of the \f$y\f$ vector.
   * @param ys2 The second spinor component of the \f$y\f$ vector.
   * @param ys3 The third  spinor component of the \f$y\f$ vector.
   * @param ys4 The fourth spinor component of the \f$y\f$ vector.
   * @param zs1 The first  spinor component of the \f$z\f$ vector.
   * @param zs2 The second spinor component of the \f$z\f$ vector.
   * @param zs3 The third  spinor component of the \f$z\f$ vector.
   * @param zs4 The fourth spinor component of the \f$z\f$ vector.
   * @param ts1 The first  spinor component of the \f$t\f$ vector.
   * @param ts2 The second spinor component of the \f$t\f$ vector.
   * @param ts3 The third  spinor component of the \f$t\f$ vector.
   * @param ts4 The fourth spinor component of the \f$t\f$ vector.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		       complex<double> xs1, complex<double> xs2,
		       complex<double> xs3, complex<double> xs4,
		       complex<double> ys1, complex<double> ys2,
		       complex<double> ys3, complex<double> ys4,
		       complex<double> zs1, complex<double> zs2,
		       complex<double> zs3, complex<double> zs4,
		       complex<double> ts1, complex<double> ts2,
		       complex<double> ts3, complex<double> ts4,
		       DiracRep drep=defaultDRep) {
    direction(intermediate);
    setMomentum(p);
    checkParticle(part);
    _wf = LorentzRSSpinor<double>(xs1,xs2,xs3,xs4,ys1,ys2,ys3,ys4,
				  zs1,zs2,zs3,zs4,ts1,ts2,ts3,ts4,drep);
  }

  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param wave The wavefunction.
   * @param dir The direction of the particle
   */
  RSSpinorWaveFunction(const Lorentz5Momentum & p, const tcPDPtr & part,
		       const LorentzRSSpinor<double> & wave,
		       Direction dir=intermediate) {
    direction(dir);
    setMomentum(p);
    checkParticle(part); 
    _wf=wave;
  }
  
  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param wave The wavefunction.
   * @param dir The direction of the particle
   */
  RSSpinorWaveFunction(const tPPtr & p,
		       const LorentzRSSpinor<SqrtEnergy> & wave,
		       Direction dir=intermediate) {
    direction(dir);
    setMomentum(p->momentum());
    checkParticle(p->dataPtr());  
    _wf = LorentzRSSpinor<double>(wave.Type(), wave.Rep());
    for (unsigned int i=0; i<4; ++i)
      for(unsigned int j=0; j<4; ++j)
	_wf(i,j)=wave(i,j)*UnitRemoval::InvSqrtE;
  }
  
  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param wave The wavefunction.
   */
  RSSpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		       LorentzRSSpinor<double> & wave) {
    direction(intermediate);
    setMomentum(p);
    checkParticle(part); 
    _wf=wave;
  }

  /**
   * Constructor, set the momentum, helicity, direction and Dirac representation.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
		       unsigned int ihel, Direction dir,DiracRep drep=defaultDRep) {
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
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
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
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,
		       const tcPDPtr & part,unsigned int ihel,Direction dir,
		       DiracRep drep=defaultDRep) {
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
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(const LorentzMomentum & p,const tcPDPtr & part,
		       unsigned int ihel,
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
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(Energy m,const tcPDPtr & part,unsigned int ihel,
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
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  RSSpinorWaveFunction(const LorentzMomentum & p,Energy m,const tcPDPtr & part,
		       unsigned int ihel,
		       Direction dir,DiracRep drep=defaultDRep) {
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
  RSSpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,Direction dir,
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
  RSSpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
		       const tcPDPtr & part,Direction dir,
		       DiracRep drep=defaultDRep) {
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
  RSSpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,
		       const tcPDPtr & part,Direction dir,
		       DiracRep drep=defaultDRep) {
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
  RSSpinorWaveFunction(const LorentzMomentum & p,const tcPDPtr & part,Direction dir,
		       DiracRep drep=defaultDRep) {
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
  RSSpinorWaveFunction(Energy m,const tcPDPtr & part,Direction dir,
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
  RSSpinorWaveFunction(const LorentzMomentum & p,Energy m,const tcPDPtr & part,
		       Direction dir,DiracRep drep=defaultDRep) {
    direction(dir);
    setMomentum(p,m);
    checkParticle(part);
    zeroWaveFunction(drep);
  }


  /**
   * Default constructor
   */
  RSSpinorWaveFunction(DiracRep dirac=defaultDRep) {
    direction(intermediate);
    setMomentum();
    zeroWaveFunction(dirac);
  }
  //@}

  /**
   *  Access to the wavefunction and its components.
   */
  //@{
  /**
   * subscript operator for the wavefunction
   * Set components by index.
   */
  complex<double> operator ()(int i, int j) const {
    assert(  i>=0 && i<=3 && j>=0 && j<=3);
    return _wf(i,j);
  }

  /**
   * subscript operator for the wavefunction
   * Set components by index.
   */
  complex<double> & operator () (int i, int j) {
    assert(  i>=0 && i<=3 && j>=0 && j<=3);
    return _wf(i,j);
  }

  /**
   * return wavefunction as LorentzRSSpinor
   */
  const LorentzRSSpinor<double> & wave() const {return _wf;}

  /**
   * Get first spinor component for the x vector
   */
  complex<double> xs1() const {return _wf.xs1();}

  /**
   * Get second spinor component for the x vector
   */
  complex<double> xs2() const {return _wf.xs2();}

  /**
   * Get third  spinor component for the x vector
   */
  complex<double> xs3() const {return _wf.xs3();}

  /**
   * Get fourth  spinor component for the x vector
   */
  complex<double> xs4() const {return _wf.xs4();}

  /**
   * Get first spinor component for the y vector
   */
  complex<double> ys1() const {return _wf.ys1();}

  /**
   * Get second spinor component for the y vector
   */
  complex<double> ys2() const {return _wf.ys2();}
  
  /**
   * Get third spinor component for the y vector
   */
  complex<double> ys3() const {return _wf.ys3();}
  
  /**
   * Get fourth spinor component for the y vector
   */
  complex<double> ys4() const {return _wf.ys4();}
  
  /**
   * Get first spinor component for the z vector
   */
  complex<double> zs1() const {return _wf.zs1();}
  
  /**
   * Get second spinor component for the z vector
   */
  complex<double> zs2() const {return _wf.zs2();}
  
  /**
   * Get third spinor component for the z vector
   */
  complex<double> zs3() const {return _wf.zs3();}
  
  /**
   * Get fourth spinor component for the z vector
   */
  complex<double> zs4() const {return _wf.zs4();}
  
  /**
   * Get first spinor component for the t vector
   */
  complex<double> ts1() const {return _wf.ts1();}
  
  /**
   * Get second spinor component for the t vector
   */
  complex<double> ts2() const {return _wf.ts2();}
  
  /**
   * Get third spinor component for the t vector
   */
  complex<double> ts3() const {return _wf.ts3();}
  
  /**
   * Get fourth spinor component for the t vector
   */
  complex<double> ts4() const {return _wf.ts4();}
  
  /**
   * Set first spinor component for the x vector
   */
  void setXS1(complex<double> in) {_wf.setXS1(in);}
  
  /**
   * Set second spinor component for the x vector
   */
  void setXS2(complex<double> in) {_wf.setXS2(in);}
  
  /**
   * Set third spinor component for the x vector
   */
  void setXS3(complex<double> in) {_wf.setXS3(in);}
  
  /**
   * Set fourth spinor component for the x vector
   */
  void setXS4(complex<double> in) {_wf.setXS4(in);}
  
  /**
   * Set first spinor component for the y vector
   */
  void setYS1(complex<double> in) {_wf.setYS1(in);}
  
  /**
   * Set second spinor component for the y vector
   */
  void setYS2(complex<double> in) {_wf.setYS2(in);}
  
  /**
   * Set third spinor component for the y vector
   */
  void setYS3(complex<double> in) {_wf.setYS3(in);}
  
  /**
   * Set fourth spinor component for the y vector
   */
  void setYS4(complex<double> in) {_wf.setYS4(in);}
  
  /**
   * Set first spinor component for the z vector
   */
  void setZS1(complex<double> in) {_wf.setZS1(in);}
  
  /**
   * Set second spinor component for the z vector
   */
  void setZS2(complex<double> in) {_wf.setZS2(in);}
  
  /**
   * Set third spinor component for the z vector
   */
  void setZS3(complex<double> in) {_wf.setZS3(in);}
  
  /**
   * Set fourth spinor component for the z vector
   */
  void setZS4(complex<double> in) {_wf.setZS4(in);}
  
  /**
   * Set first spinor component for the t vector
   */
  void setTS1(complex<double> in) {_wf.setTS1(in);}
  
  /**
   * Set second spinor component for the t vector
   */
  void setTS2(complex<double> in) {_wf.setTS2(in);}
  
  /**
   * Set third spinor component for the t vector
   */
  void setTS3(complex<double> in) {_wf.setTS3(in);}
  
  /**
   * Set fourth spinor component for the t vector
   */
  void setTS4(complex<double> in) {_wf.setTS4(in);}
  //@}

  /**
   * reset functions
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
   * @param ihel The helicity (0,1,2,3 as described above.)
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

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<LorentzRSSpinor<SqrtEnergy> > & waves,
				     tPPtr particle,Direction);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<RSSpinorWaveFunction> & waves,
				     tPPtr particle,Direction);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<LorentzRSSpinor<SqrtEnergy> > & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction);

  /**
   *  Calculate the wavefunctions
   */
  static void calculateWaveFunctions(vector<RSSpinorWaveFunction> & waves,
				     RhoDMatrix & rho,
				     tPPtr particle,Direction);

  /**
   *  Construct the SpinInfo object
   */
  static void constructSpinInfo(const vector<LorentzRSSpinor<SqrtEnergy> > & waves,
				tPPtr part,Direction dir, bool time);

private:

  /**
   * Zero the wavefunction.
   */
  void zeroWaveFunction(DiracRep drep=defaultDRep) {
    _wf=LorentzRSSpinor<double>(drep);
  }

  /**
   * Calcuate the wavefunction.
   * @param ihel The helicity (0,1,2,3 as described above.)
   * @param drep The Dirac matrix representation.
   */
  void calculateWaveFunction(unsigned int ihel,DiracRep drep=defaultDRep);

  /**
   * Check particle spin and set pointer.
   * @param part The ParticleData pointer.
   */
  void checkParticle(const tcPDPtr & part) {
    setParticle(part);
    assert(iSpin()==4);
  }

private:

  /**
   * storage of the Lorentz RSSpinor
   */
  LorentzRSSpinor<double> _wf;

  /// Return wavefunction as LorentzRSSpinor<SqrtEnergy>
  LorentzRSSpinor<SqrtEnergy> dimensionedWf() {
    LorentzRSSpinor<SqrtEnergy> temp(_wf.Type(),_wf.Rep());
    for (unsigned int i=0; i<4; ++i)
      for (unsigned int j=0; j<4; ++j)
	temp(i,j) = _wf(i,j)*UnitRemoval::SqrtE;
    return temp;
  }
};

}
}

#endif /* ThePEG_RSSpinorWaveFunction_H */
