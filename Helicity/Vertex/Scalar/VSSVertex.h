// -*- C++ -*-
#ifndef ThePEG_VSSVertex_H
#define ThePEG_VSSVertex_H
//
// This is the declaration of the VSSVertex class.
//
#include "ThePEG/Helicity/Vertex/VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/VectorWaveFunction.h"
#include "VSSVertex.fh"

namespace ThePEG {
namespace Helicity {

/** \ingroup Helicity
 *
 *  The VSSVertex class is the implementation of the vector-scalar-scalar
 *  vertex. It inherits from the VertexBase class for storage of the particles 
 *  and implements the helicity calculations.
 *
 *  All such vertices should inherit from this class and implement the virtual
 *  setCoupling member
 *
 *  The form of the vertex is
 * \f[-ic\left(p_2-p_3\right)\cdot\epsilon_1\phi_2\phi_3\f]
 *
 *  @see VertexBase
 */
class VSSVertex: public VertexBase {
    
public:
  
  /**
   * Default constructor.
   */
  VSSVertex() { setNpoint(3); setSpin(3,1,1); setName(VSS); }
  
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
   * Evaluate the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param vec1 The wavefunction for the vector.
   * @param sca2 The wavefunction for the first  scalar.
   * @param sca3 The wavefunction for the second scalar.
   */
  Complex evaluate(Energy2 q2,const VectorWaveFunction & vec1,
		   const ScalarWaveFunction & sca2, const ScalarWaveFunction & sca3);

  /**
   * Evaluate the off-shell vector coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell vector.
   * @param out The ParticleData pointer for the off-shell vector.
   * @param sca2 The wavefunction for the first  scalar.
   * @param sca3 The wavefunction for the second scalar.
   */
  VectorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
			      const ScalarWaveFunction & sca2,
			      const ScalarWaveFunction & sca3);

  /**
   * Evaluate the off-shell scalar coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell scalar.
   * @param out The ParticleData pointer for the off-shell scalar.
   * @param vec1 The wavefunction for the vector.
   * @param sca2 The wavefunction for the scalar.
   */
  ScalarWaveFunction evaluate(Energy2 q2,int iopt, tcPDPtr out,
			      const VectorWaveFunction & vec1,
			      const ScalarWaveFunction & sca2);
  //@}

  /**
   * Calculate the couplings. This method is virtual and must be implemented in 
   * classes inheriting from this.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param part1 The ParticleData pointer for the first  particle.
   * @param part2 The ParticleData pointer for the second particle.
   * @param part3 The ParticleData pointer for the third  particle.
   */
  virtual void setCoupling(Energy2 q2,tcPDPtr part1,tcPDPtr part2,tcPDPtr part3)=0;
  
private:
  
  /**
   * Describe an abstract class with persistent data.
   */
  static AbstractNoPIOClassDescription<VSSVertex> initVSSVertex;
  
  /**
   * Private and non-existent assignment operator.
   */
  VSSVertex & operator=(const VSSVertex &);
  
};

}

/** @cond TRAITSPECIALIZATIONS */

/**
 * The following template specialization informs ThePEG about the
 * base class of VSSVertex.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::VSSVertex,1> {
  /** Typedef of the base class of VSSVertex. */
  typedef ThePEG::Helicity::VertexBase NthBase;
};
  
/**
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::VSSVertex>
  : public ClassTraitsBase<ThePEG::Helicity::VSSVertex> {
  
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::VSSVertex"; }
};

/** @endcond */
  
}

#endif /* ThePEG_VSSVertex_H */