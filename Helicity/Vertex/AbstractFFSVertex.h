// -*- C++ -*-
#ifndef HELICITY_AbstractFFSVertex_H
#define HELICITY_AbstractFFSVertex_H
//
// This is the declaration of the AbstractFFSVertex class.
//

#include "VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/SpinorWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/SpinorBarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "AbstractFFSVertex.fh"

namespace ThePEG {
namespace Helicity {

/**
 * The AbstractFFSVertex class provides a base class for all
 * fermion-fermion-scalar vertices in ThePEG.
 */
class AbstractFFSVertex: public VertexBase {

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
  virtual Complex evaluate(Energy2 q2,const SpinorWaveFunction & sp1,
			   const SpinorBarWaveFunction & sbar2,
			   const ScalarWaveFunction & sca3) = 0;

  /**
   * Evaluate the off-shell spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell spinor.
   * @param out The ParticleData pointer for the off-shell spinor.
   * @param sp1   The wavefunction for the ferimon.
   * @param sca3  The wavefunction for the scalar.
   * @param drep The Dirac matrix representation
   */
  virtual SpinorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				      const SpinorWaveFunction & sp1, 
				      const ScalarWaveFunction & sca3,
				      DiracRep drep=defaultDRep) = 0;

  /**
   * Evaluate the off-shell barred spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell barred spinor.
   * @param out The ParticleData pointer for the off-shell barred spinor.
   * @param sbar2 The wavefunction for the antifermion.
   * @param sca3  The wavefunction for the scalar.
   * @param drep The Dirac matrix representation
   */
  virtual SpinorBarWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
					 const SpinorBarWaveFunction & sbar2,
					 const ScalarWaveFunction & sca3,
					 DiracRep drep=defaultDRep) = 0;

  /**
   * Evaluate the off-shell scalar coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell scalar.
   * @param out The ParticleData pointer for the off-shell scalar.
   * @param sp1   The wavefunction for the ferimon.
   * @param sbar2 The wavefunction for the antifermion.
   */
  virtual ScalarWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				      const SpinorWaveFunction & sp1, 
				      const SpinorBarWaveFunction & sbar2) = 0;
  //@}

public:

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<AbstractFFSVertex> initAbstractFFSVertex;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  AbstractFFSVertex & operator=(const AbstractFFSVertex &);

};

}
}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of AbstractFFSVertex. */
template <>
struct BaseClassTrait<Helicity::AbstractFFSVertex,1> {
  /** Typedef of the first base class of AbstractFFSVertex. */
  typedef VertexBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the AbstractFFSVertex class and the shared object where it is defined. */
template <>
struct ClassTraits<Helicity::AbstractFFSVertex>
  : public ClassTraitsBase<Helicity::AbstractFFSVertex> {
  /** Return a platform-independent class name */
  static string className() { return "Helicity::AbstractFFSVertex"; }
};

/** @endcond */

}

#endif /* HELICITY_AbstractFFSVertex_H */
