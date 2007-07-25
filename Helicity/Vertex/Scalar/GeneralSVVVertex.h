// -*- C++ -*-
#ifndef ThePEG_GeneralSVVVertex_H
#define ThePEG_GeneralSVVVertex_H
//
// This is the declaration of the GeneralSVVVertex class.
//

#include "ThePEG/Helicity/Vertex/VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/VectorWaveFunction.h"
#include "GeneralSVVVertex.fh"

namespace ThePEG {
namespace Helicity {
    
/**
 * The GeneralSVVVertex class implements a
 * general Scalar-Vector-Vector vertex allowing for decay modes 
 * that only enter at the one-loop level
 * 
 * The loop integral is calculated by Passarino-Veltman reduction 
 * and the coefficients are stored here. They must be calculated
 * in the inheriting class along with implementation of the
 * setCoupling member.
 */
class GeneralSVVVertex: public VertexBase {
  
public:

  /**
   * The default constructor.
   */
  inline GeneralSVVVertex();
  
  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();
  
  /** @name Member functions to calculate helicity amplitudes for vertices */
  //@{
  /**
   * Evaluate the vertex
   * @param q2 Scale at which to evaluate the coupling
   * @param sca Scalar wavefunction 
   * @param vec1 Wavefunction of first vector particle
   * @param vec2 Wavefunction of second vector particle
   */
  Complex evaluate(Energy2 q2, const ScalarWaveFunction & sca,
		   const VectorWaveFunction & vec1,
		   const VectorWaveFunction & vec2);

  /**
   * Evaluate the off-shell scalar coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell scalar.
   * @param out The ParticleData pointer for the off-shell scalar.
   * @param vec1 The wavefunction for the first  vector.
   * @param vec2 The wavefunction for the second vector.
   */
  ScalarWaveFunction evaluate(Energy2 q2,int iopt, tcPDPtr out,
                              const VectorWaveFunction & vec1,
                              const VectorWaveFunction & vec2);

  /**
   * Calculate coupling.
   * @param q2 Scale at which to evaluate couplings
   * @param part1 ParticleDataPointer to first particle 
   * @param part2 ParticleDataPointer to second particle
   * @param part3 ParticleDataPointer to third particle 
   */
  virtual void setCoupling(Energy2 q2,tcPDPtr part1, tcPDPtr part2,
			   tcPDPtr part3)=0;
  //@}

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
   *  Access coefficient _b
   */
  inline Complex b() const;
    
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
   * Set coefficient _b
   */
  inline void b(const Complex & val);
  //@}

private:
      
  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class with persistent data.
   */
  static AbstractNoPIOClassDescription<GeneralSVVVertex> initGeneralSVVVertex;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  GeneralSVVVertex & operator=(const GeneralSVVVertex &);
      
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

  /**
   * Coefficient of loop coupling 
   */
  Complex _b;
  //@}
};
}
}

#include "GeneralSVVVertex.icc"

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of GeneralSVVVertex. */
template <>
struct BaseClassTrait<ThePEG::Helicity::GeneralSVVVertex,1> {
  /** Typedef of the first base class of GeneralSVVVertex. */
  typedef ThePEG::Helicity::VertexBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the GeneralSVVVertex class and the shared object where it is defined. */
template <>
struct ClassTraits<ThePEG::Helicity::GeneralSVVVertex>
  : public ClassTraitsBase<ThePEG::Helicity::GeneralSVVVertex> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::GeneralSVVVertex"; }
};

/** @endcond */

}


#endif /* ThePEG_GeneralSVVVertex_H */
