// -*- C++ -*-
#ifndef ThePEG_FermionSpinInfo_H
#define ThePEG_FermionSpinInfo_H
// This is the declaration of the FermionSpinInfo class.

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzSpinor.h"
#include "FermionSpinInfo.fh"
// #include "FermionSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

/**
 *  The FermionSpinInfo class inherits from the SpinInfo class and
 *  implements the storage of the basis vectors for a spin-1/2
 *  particle.  The basis states are the u-spinors for a particle and
 *  the v-spinors for an antiparticle. The barred spinors can be
 *  obtained from these.
 *
 *  These basis states should be set by either matrixelements or
 *  decayers which are capable of generating spin correlation
 *  information.
 *
 *  The basis states in the rest frame of the particles can then be
 *  accessed by decayers to produce the correct correlations.
 *
 *  N.B. in our convention 0 is the \f$-\frac12\f$ helicity state and
 *  1 is the \f$+\frac12\f$ helicity state.
 *
 * @author Peter Richardson
 */
class FermionSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline FermionSpinInfo();

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline FermionSpinInfo(const Lorentz5Momentum & p, bool time);

  /**
   * Copy-constructor.
   */
  inline FermionSpinInfo(const FermionSpinInfo &);

  /**
   * Destructor.
   */
  virtual ~FermionSpinInfo();
  //@}

public:

  /** @name Set and get methods for the basis state. */
  //@{
  /**
   * Set the basis state, this is production state.
   * @param hel the helicity (0 or 1 as described above.)
   * @param in the LorentzSpinor for the given helicity.
   */
  inline void setBasisState(unsigned int hel, LorentzSpinor in) const;

  /**
   * Set the basis state for the decay.
   * @param hel the helicity (0 or 1 as described above.)
   * @param in the LorentzSpinor for the given helicity.
   */
  inline void setDecayState(unsigned int hel, LorentzSpinor in) const;

  /**
   * Get the basis state for the production for the given helicity, \a
   * hel (which is 0 or 1 as described above.)
   */
  inline LorentzSpinor getProductionBasisState(unsigned int hel) const;

  /**
   * Get the basis state for the decay for the given helicity, \a hel
   * (which is 0 or 1 as described above.)
   */
  inline LorentzSpinor getDecayBasisState(unsigned int hel) const;
  //@}

  /**
   * Perform a lorentz rotation of the spin information
   */
  virtual void transform(const LorentzMomentum &,LorentzRotation );

public:

  /**
   * Standard Init function.
   */
  static void Init();

  /**
   * Rebind to cloned objects. If a FermionSpinInfo is cloned together
   * with a whole Event and this has pointers to other event record
   * objects, these should be rebound to their clones in this
   * function.
   */
  virtual void rebind(const EventTranslationMap & trans);

  /**
   * Standard clone method.
   */
  inline virtual EIPtr clone() const;

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<FermionSpinInfo> initFermionSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  FermionSpinInfo & operator=(const FermionSpinInfo &);

private:

  /**
   * basis states in the frame in which the particle was produced
   */
  mutable vector<LorentzSpinor> _productionstates;

  /**
   * basis states in the frame in which the particle decays
   */
  mutable vector<LorentzSpinor> _decaystates;

  /**
   * basis states in the current frame of the particle
   */
  mutable vector<LorentzSpinor> _currentstates;

  /**
   * True if the decay state has been set.
   */
  mutable bool _decaycalc;

};

}
}

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * FermionSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::FermionSpinInfo,1>
  : public ClassTraitsType {
  /** Typedef of the base class of FermionSpinInfo. */
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * FermionSpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::FermionSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::FermionSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::FermionSpinInfo"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the FermionSpinInfo class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGHelicity.so"; }

};

/** @endcond */

}

#include "FermionSpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FermionSpinInfo.tcc"
#endif

#endif /* ThePEG_FermionSpinInfo_H */
