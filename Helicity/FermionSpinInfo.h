// -*- C++ -*-
#ifndef ThePEG_FermionSpinInfo_H
#define ThePEG_FermionSpinInfo_H
//
// This is the declaration of the <!id>FermionSpinInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The FermionSpinInfo class inherits from the SpinInfo class and
//  implements the storage of the basis vectors for a spin-1/2 particle.
//  The basis states are the u spinors for a particle and the v-spinors
//  for an antiparticle. The barred spinors can be obtained from these.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
//
// Author: Peter Richardson

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzSpinor.h"
#include "FermionSpinInfo.fh"
// #include "FermionSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

class FermionSpinInfo: public SpinInfo {

public:

  inline FermionSpinInfo();
  inline FermionSpinInfo(const Lorentz5Momentum &,bool);
  inline FermionSpinInfo(const FermionSpinInfo &);
  virtual ~FermionSpinInfo();
  // Standard ctors and dtor.

public:

  // set and get methods for the basis states

  inline void setBasisState(int,LorentzSpinor) const;
  // set the basis state, this is production state

  inline LorentzSpinor getProductionBasisState(int) const;
  // get the basis state for the production

  inline LorentzSpinor getDecayBasisState(int) const;
  // get the basis state for the decay

  inline void setDecayState(int,LorentzSpinor) const;
  // set the basis state for the decay.

public:

  static void Init();
  // Standard Init function used to initialize the interfaces.

  virtual void rebind(const EventTranslationMap & trans);

  inline virtual EIPtr clone() const;
  // Standard clone method.

private:

  static NoPIOClassDescription<FermionSpinInfo> initFermionSpinInfo;
  // Describe a concrete class without persistent data.

  FermionSpinInfo & operator=(const FermionSpinInfo &);
  // Private and non-existent assignment operator.

private:

  mutable vector<LorentzSpinor> _productionstates;
  // basis states in the frame in which the particle was produced
  mutable vector<LorentzSpinor> _decaystates;
  // basis states in the frame in which the particle decays
  mutable bool _decaycalc;

};

}
}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of FermionSpinInfo.
  template <>
  struct BaseClassTrait<ThePEG::Helicity::FermionSpinInfo,1> {
    typedef ThePEG::Helicity::SpinInfo NthBase;
  };

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ThePEG::Helicity::FermionSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::FermionSpinInfo> {
  static string className() { return "ThePEG::Helicity::FermionSpinInfo"; }
  // Return the class name.
  static string library() { return "libThePEGHelicity.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "FermionSpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FermionSpinInfo.tcc"
#endif

#endif /* ThePEG_FermionSpinInfo_H */
