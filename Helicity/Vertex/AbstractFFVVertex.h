// -*- C++ -*-
#ifndef HELICITY_AbstractFFVVertex_H
#define HELICITY_AbstractFFVVertex_H
//
// This is the declaration of the AbstractFFVVertex class.
//

#include "VertexBase.h"
#include "ThePEG/Helicity/WaveFunction/SpinorWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/SpinorBarWaveFunction.h"
#include "ThePEG/Helicity/WaveFunction/VectorWaveFunction.h"
#include "AbstractFFVVertex.fh"

namespace ThePEG {
namespace Helicity {

/**
 * The AbstractFFVVertex class provides a base class for all
 * fermion-fermion-vector vertices in ThePEG.
 */
class AbstractFFVVertex: public VertexBase {
  
public:


  /**
   * Default constructor
   */
  AbstractFFVVertex() : VertexBase(VertexType::FFV) {}

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
   * @param vec3  The wavefunction for the vector.
   */
  virtual Complex evaluate(Energy2 q2,const SpinorWaveFunction & sp1,
			   const SpinorBarWaveFunction & sbar2,
			   const VectorWaveFunction & vec3) = 0;

  /**
   * Evaluate the off-shell barred spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell barred spinor.
   * @param out The ParticleData pointer for the off-shell barred spinor.
   * @param sbar2 The wavefunction for the antifermion.
   * @param vec3  The wavefunction for the vector.
   * @param mass The mass of the off-shell particle if not taken from the ParticleData
   * object
   * @param width The width of the off-shell particle if not taken from the ParticleData
   * object
   */
  virtual SpinorBarWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
					 const SpinorBarWaveFunction & sbar2,
					 const VectorWaveFunction & vec3,
					 Energy mass=-GeV, Energy width=-GeV) = 0;

  /**
   * Evaluate the off-shell vector coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell vector.
   * @param out The ParticleData pointer for the off-shell vector.
   * @param sp1   The wavefunction for the ferimon.
   * @param sbar2 The wavefunction for the antifermion.
   * @param mass The mass of the off-shell particle if not taken from the ParticleData
   * object
   * @param width The width of the off-shell particle if not taken from the ParticleData
   * object
   */
  virtual VectorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				      const SpinorWaveFunction & sp1,
				      const SpinorBarWaveFunction & sbar2,
				      Energy mass=-GeV, Energy width=-GeV) = 0;

  /**
   * Evaluate the off-shell spinor coming from the vertex.
   * @param q2 The scale \f$q^2\f$ for the coupling at the vertex.
   * @param iopt Option of the shape of the Breit-Wigner for the off-shell spinor.
   * @param out The ParticleData pointer for the off-shell spinor.
   * @param sp1   The wavefunction for the ferimon.
   * @param vec3  The wavefunction for the vector.
   * @param mass The mass of the off-shell particle if not taken from the ParticleData
   * object
   * @param width The width of the off-shell particle if not taken from the ParticleData
   * object
   */
  virtual SpinorWaveFunction evaluate(Energy2 q2,int iopt,tcPDPtr out,
				      const SpinorWaveFunction & sp1,
				      const VectorWaveFunction & vec3,
				      Energy mass=-GeV, Energy width=-GeV) = 0;
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
  static AbstractNoPIOClassDescription<AbstractFFVVertex> initAbstractFFVVertex;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  AbstractFFVVertex & operator=(const AbstractFFVVertex &);

};

}
}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of AbstractFFVVertex. */
template <>
struct BaseClassTrait<Helicity::AbstractFFVVertex,1> {
  /** Typedef of the first base class of AbstractFFVVertex. */
  typedef Helicity::VertexBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the AbstractFFVVertex class and the shared object where it is defined. */
template <>
struct ClassTraits<Helicity::AbstractFFVVertex>
  : public ClassTraitsBase<Helicity::AbstractFFVVertex> {
  /** Return a platform-independent class name */
  static string className() { return "Helicity::AbstractFFVVertex"; }
};

/** @endcond */

}

#endif /* HELICITY_AbstractFFVVertex_H */
