// -*- C++ -*-
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
  inline SpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,complex<double> s1,
			    complex<double> s2,complex<double> s3,complex<double> s4,DiracRep drep=defaultDRep);

  /**
   * Constructor, set the momentum and the wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param wave The wavefunction.
   * @param dir The direction of the particle
   */
  inline SpinorWaveFunction(const Lorentz5Momentum & p, const tcPDPtr & part,
			    const LorentzSpinor<double> & wave,
			    Direction dir=intermediate);
  inline SpinorWaveFunction(const Lorentz5Momentum & p, const tcPDPtr & part,
			    const LorentzSpinor<SqrtEnergy> & wave,
			    DummyType,
			    Direction dir=intermediate);

  /**
   * Constructor, set the momentum, helicity, direction and Dirac representation.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(const Lorentz5Momentum & p,const tcPDPtr & part,
			    unsigned int ihel,
			    Direction dir,DiracRep drep=defaultDRep);

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
  inline SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
			    const tcPDPtr & part,unsigned int ihel,Direction dir,
			    DiracRep drep=defaultDRep);

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
  inline SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,const tcPDPtr & part,
			    unsigned int ihel,Direction dir,DiracRep drep=defaultDRep);

  /**
   * Constructor, set the 4-momentum, helicity, direction and
   * Dirac representation.
   * @param p the 4-momentum
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(LorentzMomentum p,const tcPDPtr & part,unsigned int ihel,
			    Direction dir,DiracRep drep=defaultDRep);

  /**
   * Constructor, set the mass and zero the momentum, set the helicity, direction and
   * Dirac representation.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param ihel The helicity (0,1 as described above.)
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(Energy m,const tcPDPtr & part,unsigned int ihel,
			    Direction dir, DiracRep drep=defaultDRep);

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
  inline SpinorWaveFunction(LorentzMomentum p,Energy m,const tcPDPtr & part,
			    unsigned int ihel,
			    Direction dir, DiracRep drep=defaultDRep);

  /**
   * Constructor, set the momentum, direction and Diracrepresentation, zero the 
   * wavefunction.
   * @param p The momentum.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(Lorentz5Momentum p,const tcPDPtr & part,Direction dir,
			    DiracRep drep=defaultDRep); 

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
  inline SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,Energy m,
			    const tcPDPtr & part,
			    Direction dir,DiracRep drep=defaultDRep);

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
  inline SpinorWaveFunction(Energy px,Energy py,Energy pz,Energy E,const tcPDPtr & part,
			    Direction dir,DiracRep drep=defaultDRep);

  /**
   * Constructor set the 4-momentum, direction and
   * Dirac representation, zero the wavefunction.
   * @param p The 4-momentum
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(LorentzMomentum p,const tcPDPtr & part,Direction dir,
			    DiracRep drep=defaultDRep);

  /**
   * Constructor set the mass, direction and
   * Dirac representation, zero the momentum and wavefunction.
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(Energy m,const tcPDPtr & part,Direction dir,
			    DiracRep drep=defaultDRep);

  /**
   * Constructor set the 4-momentum, mass, direction and
   * Dirac representation, zero the wavefunction.
   * @param p The 4-momentum
   * @param m The mass.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(LorentzMomentum p,Energy m,const tcPDPtr & part,Direction dir,
			    DiracRep drep=defaultDRep);

  /**
   * Special constructor which calculates all the helicities as a vector of
   * LorentzSpinor and sets up a particle's SpinInfo.
   * @param wave The spinors for the different helicities.
   * @param part The particle to setup
   * @param dir The direction.
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(vector<LorentzSpinor<SqrtEnergy> >& wave, tPPtr part,Direction dir,
			    bool time, bool vertex, DiracRep drep=defaultDRep);

  /**
   * Special constructor which calculates all the helicities as a vector of 
   * LorentzSpinor and sets up a particle's SpinInfo.
   * @param wave The spinors for the different helicities.
   * @param rho The \f$\rho\f$ matrix for the particle
   * @param part The particle to setup
   * @param dir The direction.
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(vector<LorentzSpinor<SqrtEnergy> >& wave, RhoDMatrix& rho,tPPtr part,
			    Direction dir,bool time, bool vertex,
			    DiracRep drep=defaultDRep);

  /**
   * Special constructor which calculates all the helicities as a vector of 
   * SpinorWaveFunction and sets up a particle's
   * SpinInfo.
   * @param wave The spinors for the different helicities.
   * @param part The particle to setup
   * @param dir The direction.
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(vector<SpinorWaveFunction>& wave, tPPtr part,Direction dir,
			    bool time, bool vertex, DiracRep drep=defaultDRep);

  /**
   * Special constructor which calculates all the helicities as a vector of 
   * SpinorWaveFunction and sets up a particle's
   * SpinInfo.
   * @param wave The spinors for the different helicities.
   * @param rho The \f$\rho\f$ matrix for the particle
   * @param part The particle to setup
   * @param dir The direction.
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   * @param drep The Dirac representation.
   */
  inline SpinorWaveFunction(vector<SpinorWaveFunction>& wave, RhoDMatrix& rho,tPPtr part,
			    Direction dir,bool time, bool vertex,
			    DiracRep drep=defaultDRep);

  /**
   * Default constructor.
   */
  inline SpinorWaveFunction(DiracRep=defaultDRep);

  /**
   * Destructor.
   */
  inline ~SpinorWaveFunction();
  //@}

  /**
   * Assignment. 
   */
  inline SpinorWaveFunction & operator = (const SpinorWaveFunction &);

  /**
   *  Access to the wavefunction and its components.
   */
  //@{
  /**
   * Subscript operator for the wavefunction.
   */
  inline complex<double> operator ()(int ) const;

  /**
   * Set components by index.
   */
  inline complex<double> & operator () (int);

  /**
   * Return wavefunction as LorentzSpinor.
   */
  inline LorentzSpinor<double> wave() const;
  inline LorentzSpinor<SqrtEnergy> dimensionedWave() const;

  /**
   * Get the first spin component component.
   */
  inline complex<double> s1() const;

  /**
   * Get the second spin component component.
   */
  inline complex<double> s2() const;

  /**
   * Get the third spin component component.
   */
  inline complex<double> s3() const;

  /**
   * Get the fourth spin component component.
   */
  inline complex<double> s4() const;

  /**
   * Set first spin component.
   */
  inline void setS1(complex<double>);

  /**
   * Set second spin component.
   */
  inline void setS2(complex<double>);

  /**
   * Set third spin component.
   */
  inline void setS3(complex<double>);

  /**
   * Set fourth spin component.
   */
  inline void setS4(complex<double>);
  //@}

  /**
   * Take the conjugate of the spinor \f$u_c=C\bar{u}^T\f$. This operation
   * transforms u-spinors to v-spinors and vice-versa and is required when
   * dealing with majorana particles.
   */
  void conjugate();

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
  inline void reset(const Lorentz5Momentum & p, const tcPDPtr & part, Direction dir);

  /** 
   * Reset the momentum and direction
   * @param p The momentum.
   * @param dir The direction
   */
  inline void reset(const Lorentz5Momentum & p,Direction dir);

  /**
   * Reset the momentum.
   * @param p The momentum.
   */
  inline void reset(const Lorentz5Momentum & p);

  /**
   * Reset the helicity (calculates the new spinor).
   * @param ihel The helicity (0,1 as described above.)
   * @param drep The Dirac matrix representation.
   */
  inline void reset(unsigned int ihel,DiracRep drep=defaultDRep);

  /**
   * Reset particle type and direction.
   * @param part The ParticleData pointer.
   * @param dir The direction.
   */
  inline void reset(const tcPDPtr & part,Direction dir);

  /**
   * Reset particle type.
   * @param part The ParticleData pointer.
   */
  inline void reset(const tcPDPtr & part);
  //@}

  /**
   * Calculate the spinors, as LorentzSpinor objects,
   * for all helicities, create and set up the SpinInfo object
   * @param wave The spinors for the different helicities.
   * @param part The particle to setup
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   */
  void constructSpinInfo(vector<LorentzSpinor<SqrtEnergy> >& wave,tPPtr part,bool time,
			 bool vertex=true);

  /**
   * Calculate the spinors, as LorentzSpinor objects,
   * for all helicities, create and set up the SpinInfo object
   * @param wave The spinors for the different helicities.
   * @param rho The \f$\rho\f$ matrix for the decaying particle.
   * @param part The particle to setup
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   */
  void constructSpinInfo(vector<LorentzSpinor<SqrtEnergy> >& wave,RhoDMatrix& rho,tPPtr part,
			 bool time,bool vertex=true);

  /**
   * Calculate the spinors, as SpinorWaveFunction objects,
   * for all helicities, create and set up the SpinInfo object
   * @param wave The spinors for the different helicities.
   * @param part The particle to setup
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   */
  void constructSpinInfo(vector<SpinorWaveFunction>& wave,tPPtr part,bool time,
			 bool vertex=true);

  /**
   * Calculate the spinors, as SpinorWaveFunction objects,
   * for all helicities, create and set up the SpinInfo object
   * @param wave The spinors for the different helicities.
   * @param rho The \f$\rho\f$ matrix for the decaying particle.
   * @param part The particle to setup
   * @param time Is this is timelike (true) or spacelike (false ) particle?
   * @param vertex Whether or not to create the FermionSpinInfo object 
   */
  void constructSpinInfo(vector<SpinorWaveFunction>& wave,RhoDMatrix& rho,
			 tPPtr part,bool time,bool vertex=true);
private:

  /**
   * Zero the wavefunction.
   */
  inline void zeroWaveFunction(DiracRep=defaultDRep);

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
  inline void checkParticle(const tcPDPtr & part);

  /**
   * Calculate the spinors, as LorentzSpinor objects,
   * for all the helicities and set up the SpinInfo object.
   * @param wave The spinors for the different helicities
   * @param spin Pointer to the FermionSpinInfo object
   * @param vertex Whether or not to set up the FermionSpinInfo object 
   */
  inline void constructSpinInfo(vector<LorentzSpinor<SqrtEnergy> >& wave,tFermionSpinPtr spin,
				bool vertex=true);

  /**
   * Calculate the spinors, as SpinorWaveFunction objects,
   * for all the helicities and set up the SpinInfo object.
   * @param wave The spinors for the different helicities
   * @param spin Pointer to the FermionSpinInfo object
   * @param vertex Whether or not to set up the FermionSpinInfo object 
   */
  inline void constructSpinInfo(vector<SpinorWaveFunction>& wave,tFermionSpinPtr spin,
				bool vertex=true);
private:

  /**
   * Storage of the Lorentz Spinor.
   */
  LorentzSpinor<double> _wf;

  LorentzSpinor<SqrtEnergy> dimensionedWf() const {
    LorentzSpinor<SqrtEnergy> temp(_wf.Type(),_wf.Rep());
    for (unsigned int i=0; i<4; ++i)
      temp(i) = _wf(i)*UnitRemoval::SqrtE;
    return temp;
  }
  
};

}

}

#include "SpinorWaveFunction.icc"

#endif




