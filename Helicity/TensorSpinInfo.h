// -*- C++ -*-
#ifndef THEPEG_TensorSpinInfo_H
#define THEPEG_TensorSpinInfo_H
// This is the declaration of the TensorSpinInfo class.

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzTensor.h"
#include "TensorSpinInfo.fh"
// #include "TensorSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

/**
 *  The TensorSpinInfo class is the implementation of the spin
 *  information for tensor particles.  It inherits from the SpinInfo
 *  class and implements the storage of the basis tensors.
 *
 *  These basis states should be set by either matrix elements or
 *  decayers which are capable of generating spin correlation
 *  information.
 *
 *  The basis states in the rest frame of the particles can then be
 *  accessed by decayers to produce the correct correlation
 *
 * @author Peter Richardson
 *
 */
class TensorSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline TensorSpinInfo();

  /**
   * Copy-constructor.
   */
  inline TensorSpinInfo(const TensorSpinInfo &);

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline TensorSpinInfo(const Lorentz5Momentum & p,bool time);

  /**
   * Destructor.
   */
  virtual ~TensorSpinInfo();
  //@}

public:

  /** @name Access the basis states. */
  //@{
  /**
   * Set the basis state, this is production state.
   * @param hel the helicity.
   * @param in the LorentzTensor for the given helicity.
   */
  inline void setBasisState(int hel, LorentzTensor in) const;

  /**
   * Set the basis state for the decay.
   * @param hel the helicity.
   * @param in the LorentzTensor for the given helicity.
   */
  inline void setDecayState(int hel, LorentzTensor in) const;

  /**
   * Get the basis state for the production for the given helicity, \a
   * hel.
   */
  inline LorentzTensor getProductionBasisState(int hel) const;

  /**
   * Get the basis state for the decay for the given helicity, \a hel.
   */
  inline LorentzTensor getDecayBasisState(int hel) const;
  //@}

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
  static NoPIOClassDescription<TensorSpinInfo> initTensorSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  TensorSpinInfo & operator=(const TensorSpinInfo &);

private:

  /**
   * Basis states in the frame in which the particle was produced.
   */
  mutable vector<LorentzTensor> _productionstates;

  /**
   * Basis states in the frame in which the particle decays.
   */
  mutable vector<LorentzTensor> _decaystates;

  /**
   * True if the decay state has been set.
   */
  mutable bool _decaycalc;

};

}
}


namespace ThePEG {

/**
 * This template specialization informs ThePEG about the base class of
 * TensorSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::TensorSpinInfo,1>
  : public ClassTraitsType {
  /** Typedef of the base class of ScalarSpinInfo. */
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * TensorSpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::TensorSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::TensorSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::TensorSpinInfo"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the TensorSpinInfo class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGHelicity.so"; }

};

}

#include "TensorSpinInfo.icc"

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "TensorSpinInfo.tcc"
#endif

#endif /* THEPEG_TensorSpinInfo_H */
