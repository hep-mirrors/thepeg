// -*- C++ -*-
#ifndef THEPEG_VectorSpinInfo_H
#define THEPEG_VectorSpinInfo_H
// This is the declaration of the VectorSpinInfo class.

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzPolarizationVector.h"
#include "VectorSpinInfo.fh"
// #include "VectorSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

/**
 *  The VectorSpinInfo class is the implementation of the spin
 *  information for vector particles.  It inherits from the SpinInfo
 *  class and implements the storage of the basis vectors.
 *
 *  These basis states should be set by either matrixelements or
 *  decayers which are capable of generating spin correlation
 *  information.
 *
 *  The basis states in the rest frame of the particles can then be
 *  accessed by decayers to produce the correct correlation.
 *
 * @author Peter Richardson
 *
 */
class VectorSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline VectorSpinInfo();

  /**
   * Copy-constructor.
   */
  inline VectorSpinInfo(const VectorSpinInfo &);

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline VectorSpinInfo(const Lorentz5Momentum & p, bool time);

  /**
   * Destructor.
   */
  virtual ~VectorSpinInfo();
  //@}

public:

  /** @name Set and get methods for the basis state. */
  //@{
  /**
   * Set the basis state, this is production state.
   * @param hel the helicity.
   * @param in the LorentzPolarizationVector for the given helicity.
   */
  inline void setBasisState(int hel, LorentzPolarizationVector in) const;

  /**
   * Set the basis state for the decay.
   * @param hel the helicity.
   * @param in the LorentzPolarizationVector for the given helicity.
   */
  inline void setDecayState(int hel, LorentzPolarizationVector in) const;

  /**
   * Get the basis state for the production for the given helicity, \a
   * hel.
   */
  inline LorentzPolarizationVector getProductionBasisState(int hel) const;

  /**
   * Get the basis state for the decay for the given helicity, \a hel.
   */
  inline LorentzPolarizationVector getDecayBasisState(int hel) const;

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
  static NoPIOClassDescription<VectorSpinInfo> initVectorSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  VectorSpinInfo & operator=(const VectorSpinInfo &);

private:

  /**
   * Basis states in the frame in which the particle was produced.
   */
  mutable vector<LorentzPolarizationVector> _productionstates;

  /**
   * Basis states in the frame in which the particle decays.
   */
  mutable vector<LorentzPolarizationVector> _decaystates;

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
 * VectorSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::VectorSpinInfo,1>
  : public ClassTraitsType {
  /** Typedef of the base class of VectorSpinInfo. */
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * VectorSpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::VectorSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::VectorSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::VectorSpinInfo"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the VectorSpinInfo class and every other class it uses
   * (except the base class).
   */
  static string library() { return "libThePEGHelicity.so"; }

};

}

#include "VectorSpinInfo.icc"

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "VectorSpinInfo.tcc"
#endif

#endif /* THEPEG_VectorSpinInfo_H */
