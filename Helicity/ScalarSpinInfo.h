// -*- C++ -*-
#ifndef ThePEG_ScalarSpinInfo_H
#define ThePEG_ScalarSpinInfo_H
// This is the declaration of the ScalarSpinInfo class.

#include "SpinInfo.h"
#include "ScalarSpinInfo.fh"
// #include "ScalarSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

/**
 * The ScalarSpinInfo class is designed to be the implementation of
 * the spin information for a scalar particle. Obviously it is pretty
 * trival in this case.
 *
 * @author Peter Richardson
 *
 */
class ScalarSpinInfo: public SpinInfo {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline ScalarSpinInfo();

  /**
   * Standard Constructor.
   * @param p the production momentum.
   * @param time true if the particle is time-like.
   */
  inline ScalarSpinInfo(const Lorentz5Momentum & p, bool time);

  /**
   * Copy-constructor.
   */
  inline ScalarSpinInfo(const ScalarSpinInfo &);

  /**
   * Destructor.
   */
  virtual ~ScalarSpinInfo();
  //@}

public:

  /**
   * Standard Init function.
   */
  static void Init();

  /**
   * Standard clone methods.
   */
  inline virtual EIPtr clone() const;

  /**
   * Rebind to cloned objects. If a FermionSpinInfo is cloned together
   * with a whole Event and this has pointers to other event record
   * objects, these should be rebound to their clones in this
   * function.
   */
  inline virtual void rebind(const EventTranslationMap & trans);
  
  /**
   * Perform a lorentz rotation of the spin information
   */
  virtual void transform(const LorentzMomentum &,LorentzRotation);

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<ScalarSpinInfo> initScalarSpinInfo;

  /**
   * Private and non-existent assignment operator.
   */
  ScalarSpinInfo & operator=(const ScalarSpinInfo &);

};

}
}


namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the base class of
 * ScalarSpinInfo.
 */
template <>
struct BaseClassTrait<ThePEG::Helicity::ScalarSpinInfo,1>
  : public ClassTraitsType {
  /** Typedef of the base class of ScalarSpinInfo. */
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * ScalarSpinInfo class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ThePEG::Helicity::ScalarSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::ScalarSpinInfo> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::Helicity::ScalarSpinInfo"; }
};

/** @endcond */

}

#include "ScalarSpinInfo.icc"

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ScalarSpinInfo.tcc"
#endif

#endif /* ThePEG_ScalarSpinInfo_H */
