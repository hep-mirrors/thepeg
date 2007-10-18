// -*- C++ -*-
#ifndef ThePEG_FFSVertex_H
#define ThePEG_FFSVertex_H
//
// This is the declaration of the FFSVertex class.

#include "ThePEG/Helicity/Vertex/VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/SpinorWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/SpinorBarWaveFunction.h"
#include "FFSVertex.fh"

namespace ThePEG {

namespace Helicity{

/** \ingroup Helicity
 *
 *  The FFSVertex class is the implementation of the interact of a
 *  scalar boson and a fermion-antifermion pair. It inherits from the VertexBase
 *  class for storage of the particles interacting at the vertex and implements
 *  the helicity calculations.
 *
 *  Implementations of specific interactions should inherit from this and implement
 *  the virtual setCoupling member.
 *
 *  The form of the vertex is
 *  \f[ic\bar{f_2}a^\lambda P_\lambda f_1\phi_3\f]
 *  where \f$a^\pm\f$ are the right and left couplings and \f$P_\pm=(1\pm\gamma_5)\f$
 *  are the chirality projection operators.
 *
 *  @see VertexBase
 */
class FFSVertex: public VertexBase {
      
public:

  /**
   * Default constructor.
   */
  FFSVertex() { setNpoint(3); setSpin(2,2,1); setName(FFS); }
  
  /**
   * Standard Init function used to initialize the interfaces.
   */
  static void Init();
  
public:      

  /**
   * Members to calculate the helicity amplitude expressions for vertices
   * and off-shell particles.
   */
  //@{
  /**
   * Evalulate the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param sp1   The wavefunction for the ferimon.
   * @param sbar2 The wavefunction for the antifermion.
   * @param sca3  The wavefunction for the scalar.
   */
  Complex evaluate(Energy2 q2,const SpinorWaveFunction & sp1,
		   const SpinorBarWaveFunction & sbar2,
		   const ScalarWaveFunction & sca3);

  /**
   * Evaluate the off-shell spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell spinor.
   * @param out The ParticleData pointer for the off-shell spinor.
   * @param sp1   The wavefunction for the ferimon.
   * @param sca3  The wavefunction for the scalar.
   * @param drep The Dirac matrix representation
   */
  SpinorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
			      const SpinorWaveFunction & sp1, 
			      const ScalarWaveFunction & sca3,
			      DiracRep drep=defaultDRep);

  /**
   * Evaluate the off-shell barred spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell barred spinor.
   * @param out The ParticleData pointer for the off-shell barred spinor.
   * @param sbar2 The wavefunction for the antifermion.
   * @param sca3  The wavefunction for the scalar.
   * @param drep The Dirac matrix representation
   */
  SpinorBarWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				 const SpinorBarWaveFunction & sbar2,
				 const ScalarWaveFunction & sca3,
				 DiracRep drep=defaultDRep);

  /**
   * Evaluate the off-shell scalar coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell scalar.
   * @param out The ParticleData pointer for the off-shell scalar.
   * @param sp1   The wavefunction for the ferimon.
   * @param sbar2 The wavefunction for the antifermion.
   */
  ScalarWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
			      const SpinorWaveFunction & sp1, 
			      const SpinorBarWaveFunction & sbar2);
  //@}

  /**
   * Calculate the couplings. This method is virtual and must be implemented in 
   * classes inheriting from this.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param part1 The ParticleData pointer for the first  particle.
   * @param part2 The ParticleData pointer for the second particle.
   * @param part3 The ParticleData pointer for the third  particle.
   * @param ioff An integer referring to which particle in the list is 
   * offshell if applicable.
   */
  virtual void setCoupling(Energy2 q2,tcPDPtr part1,tcPDPtr part2,tcPDPtr part3,int ioff)=0;
   
  /**
   *  Get the couplings
   */
  //@{
  /**
   * Get the left coupling.
   */
  Complex getLeft() { return _left; }
  
  /**
   * Get the right coupling.
   */
  Complex getRight() { return _right; }
  
protected:

  /**
   *  Set the couplings
   */
  //@{
  /**
   * Set the left coupling.
   */
  void setLeft(Complex in) { _left = in; }

  /**
   * Set the right coupling.
   */
  void setRight(Complex in) { _right = in; }
  //@}
  
private:
  
  /**
   * Describe an abstract base class with persistent data.
   */
  static AbstractNoPIOClassDescription<FFSVertex> initFFSVertex;
  
  /**
   * Private and non-existent assignment operator.
   */
  FFSVertex & operator=(const FFSVertex &);
  
private:

  /**
   * Storage of the left coupling.
   */
  Complex _left;

  /**
   * Storage of the right coupling.
   */
  Complex _right;

};
}

/** @cond TRAITSPECIALIZATIONS */

/**
 * The following template specialization informs ThePEG about the
 * base class of FFSVertex.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::FFSVertex,1> {
  /** Typedef of the base class of FFSVertex. */
  typedef ThePEG::Helicity::VertexBase NthBase;
};

/** 
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::FFSVertex>
  : public ClassTraitsBase<ThePEG::Helicity::FFSVertex> {

  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::FFSVertex"; }
};

/** @endcond */

}


#endif /* ThePEG_FFSVertex_H */