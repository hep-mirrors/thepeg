// -*- C++ -*-
#ifndef HELICITY_AbstractVVSVertex_H
#define HELICITY_AbstractVVSVertex_H
//
// This is the declaration of the AbstractVVSVertex class.
//

#include "VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/ScalarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/VectorWaveFunction.h"
#include "AbstractVVSVertex.fh"

namespace ThePEG {
namespace Helicity {

/**
 * Here is the documentation of the AbstractVVSVertex class.
 */
class AbstractVVSVertex: public VertexBase {

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
			   const ScalarWaveFunction & sca3) = 0;

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
				      const ScalarWaveFunction & sca3) = 0;

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
				      const VectorWaveFunction & vec2) = 0;
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
  static AbstractNoPIOClassDescription<AbstractVVSVertex> initAbstractVVSVertex;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  AbstractVVSVertex & operator=(const AbstractVVSVertex &);

};

}
}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of AbstractVVSVertex. */
template <>
struct BaseClassTrait<Helicity::AbstractVVSVertex,1> {
  /** Typedef of the first base class of AbstractVVSVertex. */
  typedef Helicity::VertexBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the AbstractVVSVertex class and the shared object where it is defined. */
template <>
struct ClassTraits<Helicity::AbstractVVSVertex>
  : public ClassTraitsBase<Helicity::AbstractVVSVertex> {
  /** Return a platform-independent class name */
  static string className() { return "Helicity::AbstractVVSVertex"; }
};

/** @endcond */

}

#endif /* HELICITY_AbstractVVSVertex_H */