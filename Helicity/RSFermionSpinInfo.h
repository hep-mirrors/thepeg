// -*- C++ -*-
#ifndef THEPEG_RSFermionSpinInfo_H
#define THEPEG_RSFermionSpinInfo_H
// This is the declaration of the RSFermionSpinInfo class.

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzRSSpinor.h"
#include "RSFermionSpinInfo.fh"

namespace ThePEG {
namespace Helicity {

/**
 *  The RSFermionSpinInfo class inherits from the SpinInfo class and
 *  implements the storage of the basis vector for a spin-3/2 particle.
 *  The basis states are the vector u spinors for a particle and the vector
 *  v-spinors for an antiparticle. The barred spinors can be obtained from these.
 *
 *  These basis states should be set by either the matrixelements or decayers
 *  which are capable of generating spin correlation information.
 *
 *  The basis states in the rest frame of the particles can then be accessed by
 *  the decayers to produce the correct correlations.
 *
 * @see SpinInfo
 *
 * \author Peter Richardson
 *
 */
class RSFermionSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline RSFermionSpinInfo();

  /**
   * Copy-constructor.
   */
  inline RSFermionSpinInfo(const RSFermionSpinInfo &);

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline RSFermionSpinInfo(const Lorentz5Momentum & p,bool time);

  /**
   * Destructor.
   */
  virtual ~RSFermionSpinInfo();
  //@}

public:

  /** @name Set and get methods for the basis state. */
  //@{
  /**
   * Set the basis state, this is production state.
   * @param hel the helicity.
   * @param in the LorentzRSSpinor for the given helicity.
   */
  inline void setBasisState(int hel,LorentzRSSpinor in) const;

  /**
   * Set the basis state for the decay.
   * @param hel the helicity.
   * @param in the LorentzRSSpinor for the given helicity.
   */
  inline void setDecayState(int hel,LorentzRSSpinor in) const;

  /**
   * Get the basis state for the production for the given helicity, \a
   * hel.
   */
  inline LorentzRSSpinor getProductionBasisState(int hel) const;

  /**
   * Get the basis state for the decay for the given helicity, \a hel.
   */
  inline LorentzRSSpinor getDecayBasisState(int hel) const;
  //@}

public:

  /**
   * Standard Init function used to initialize the interfaces.
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
  static NoPIOClassDescription<RSFermionSpinInfo> initRSFermionSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  RSFermionSpinInfo & operator=(const RSFermionSpinInfo &);

private:

  /**
   * Basis states in the frame in which the particle was produced.
   */
  mutable vector<LorentzRSSpinor> _productionstates;

  /**
   * Basis states in the frame in which the particle decays.
   */
  mutable vector<LorentzRSSpinor> _decaystates;

  /**
   * True if the decay state has been set.
   */
  mutable bool _decaycalc;

};

}
}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/**
 * The following template specialization informs ThePEG about the
 * base class of RSFermionSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::RSFermionSpinInfo,1> {
  /** Typedef of the base class of RSFermionSpinInfo. */
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

/**
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::RSFermionSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::RSFermionSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::RSFermionSpinInfo"; }
  /**
   * Return the name of the shared library to be loaded to get
   * access to this class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGHelicity.so"; }

};

}

#include "RSFermionSpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RSFermionSpinInfo.tcc"
#endif

#endif /* THEPEG_RSFermionSpinInfo_H */
