// -*- C++ -*-
#ifndef HELICITY_GeneralVVSVertex_H
#define HELICITY_GeneralVVSVertex_H
//
// This is the declaration of the GeneralVVSVertex class.
//

#include "ThePEG/Helicity/Vertex/AbstractVVSVertex.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/VectorWaveFunction.h"
#include "GeneralVVSVertex.fh"

namespace ThePEG {
namespace Helicity {

using namespace ThePEG;

/**
 * The GeneralVVSVertex class implements a
 * general Vector-Vector-Scalar vertex allowing for decay modes 
 * that only enter at the one-loop level
 * 
 * The loop integral is calculated by Passarino-Veltman reduction 
 * and the coefficients are stored here. They must be calculated
 * in the inheriting class along with implementation of the
 * setCoupling member.
 */
class GeneralVVSVertex: public AbstractVVSVertex {

public:

  /**
   * The default constructor.
   */
  inline GeneralVVSVertex();

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
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
   * @param vec1 The wavefunction for the first  vector.
   * @param vec2 The wavefunction for the second vector.
   * @param sca3 The wavefunction for the scalar.
   */
  virtual Complex evaluate(Energy2 q2,const VectorWaveFunction & vec1,
			   const VectorWaveFunction & vec2,
			   const ScalarWaveFunction & sca3);

  /**
   * Evaluate the off-shell vector coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell vector.
   * @param out The ParticleData pointer for the off-shell vector.
   * @param vec2 The wavefunction for the vector.
   * @param sca3 The wavefunction for the scalar.
   */
  virtual VectorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				      const VectorWaveFunction & vec2,
				      const ScalarWaveFunction & sca3);

  /**
   * Evaluate the off-shell scalar coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell scalar.
   * @param out The ParticleData pointer for the off-shell scalar.
   * @param vec1 The wavefunction for the first  vector.
   * @param vec2 The wavefunction for the second vector.
   */
  virtual ScalarWaveFunction evaluate(Energy2 q2,int iopt, tcPDPtr out,
				      const VectorWaveFunction & vec1,
				      const VectorWaveFunction & vec2);
  //@}

  /**
   * Calculate coupling.
   * @param q2 Scale at which to evaluate couplings
   * @param part1 ParticleDataPointer to first particle 
   * @param part2 ParticleDataPointer to second particle
   * @param part3 ParticleDataPointer to third particle 
   */
  virtual void setCoupling(Energy2 q2,tcPDPtr part1, tcPDPtr part2,
                           tcPDPtr part3)=0;

public:

  /**@name Set and Get tensor coefficients.*/
  //@{
  /**
   * Access coefficient of \f$g^{\mu\nu}\f$
   */
  inline Complex a00() const;
      
  /**
   * Access coefficient of \f$p_1^\mu p_1^\nu\f$
   */
  inline Complex a11() const;
      
  /**
   * Access coefficient of \f$p_1^\mu p_2^\nu\f$
   */
  inline Complex a12() const;
      
  /**
   * Access coefficient of \f$p_2^\mu p_1^\nu\f$
   */
  inline Complex a21() const;
      
  /**
   * Access coefficient of \f$p_2^\mu p_2^\nu\f$
   */
  inline Complex a22() const;
      
  /**
   * Access coefficient of \f$\epsilon^{\mu\nu\alpha\beta}p_1\alpha p_2\beta\f$
   */
  inline Complex aEp() const;
      
  /**
   * Set tensor coefficient of \f$g^{\mu\nu}\f$
   */
  inline void a00(const Complex & val);
      
  /**
   * Set tensor coefficient of \f$p_1^\mu p_1^\nu\f$
   */
  inline void a11(const Complex & val);
      
  /**
   * Set tensor coefficient of \f$p_1^\mu p_2^\nu\f$
   */
  inline void a12(const Complex & val);
      
  /**
   * Set tensor coefficient of \f$p_2^\mu p_1^\nu\f$
   */
  inline void a21(const Complex & val);
      
  /**
   * Set tensor coefficient of \f$p_2^\mu p_2^\nu\f$
   */ 
  inline void a22(const Complex & val);
      
  /**
   * Set tensor coefficient of \f$\epsilon^{\mu\nu\alpha\beta}p_1\alpha p_2\beta\f$
   */
  inline void aEp(const Complex & val);

  /**
   */
  inline void setCoefScheme(unsigned int representation);
  //@}

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<GeneralVVSVertex> initGeneralVVSVertex;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  GeneralVVSVertex & operator=(const GeneralVVSVertex &);

      
private:
  
  /** @name Store tensor coefficients.*/
  //@{
  /**
   * Coefficient of \f$g^{\mu\nu}\f$
   */
  Complex _a00;

  /**
   * Coefficient of \f$p_1^\mu p_1^\nu\f$
   */
  Complex _a11;

  /**
   * Coefficient of \f$p_1^\mu p_2^\nu\f$
   */
  Complex _a12;

  /**
   * Coefficient of \f$p_2^\mu p_1^\nu\f$
   */
  Complex _a21;

  /**
   * Coefficient of \f$p_2^\mu p_2^\nu\f$
   */
  Complex _a22;

  /**
   * Coefficient of \f$\epsilon^{\mu\nu\alpha\beta}p_1\alpha p_2\beta\f$
   */
  Complex _aEp;
  //@}

  /**
   * Switch between two representations of coefficients (_a00,_a11,_a12,_a21,_a22,_aEp):
    suitable for the simplified H-g-g and H-gamma-gamma vertices and 
    suitable for the Passarino-Veltman tensor reduction scheme
   */
  unsigned int _representation;
  //@}
};

}
}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of GeneralVVSVertex. */
template <>
struct BaseClassTrait<Helicity::GeneralVVSVertex,1> {
  /** Typedef of the first base class of GeneralVVSVertex. */
  typedef Helicity::AbstractVVSVertex NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the GeneralVVSVertex class and the shared object where it is defined. */
template <>
struct ClassTraits<Helicity::GeneralVVSVertex>
  : public ClassTraitsBase<Helicity::GeneralVVSVertex> {
  /** Return a platform-independent class name */
  static string className() { return "Helicity::GeneralVVSVertex"; }
};

/** @endcond */

}

#include "GeneralVVSVertex.icc"

#endif /* HELICITY_GeneralVVSVertex_H */