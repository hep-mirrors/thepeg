// -*- C++ -*-
#ifndef THEPEG_TensorSpinInfo_H
#define THEPEG_TensorSpinInfo_H
//
// This is the declaration of the <!id>TensorSpinInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  This is the implementation of the spin information for tensor
//  particles.  It inherits from the SpinInfo class and implements the
//  storage of the basis tensors.
//
//  These basis states should be set by either matrix elements or decayers
//  which are capable of generating spin correlation information.
//
//  The basis states in the rest frame of the particles can then be accessed by
//  decayers to produce the correct correlation
//
// CLASSDOC SUBSECTION See also:
//
// <a href="SpinInfo.html">SpinInfo.h</a>.
//
// Author: Peter Richardson
//

#include "SpinInfo.h"
#include "ThePEG/Helicity/LorentzTensor.h"
#include "TensorSpinInfo.fh"
// #include "TensorSpinInfo.xh"

namespace ThePEG {
namespace Helicity {

class TensorSpinInfo: public SpinInfo {

public:

  inline TensorSpinInfo();
  inline TensorSpinInfo(const TensorSpinInfo &);
  inline TensorSpinInfo(const Lorentz5Momentum &,bool);
  virtual ~TensorSpinInfo();
  // Standard ctors and dtor.

public:

  // set and get methods for the basis states

  inline void setBasisState(int,LorentzTensor) const;
  // set the basis state, this is production state

  inline void setDecayState(int,LorentzTensor) const;
  // set the decay basis state

  inline LorentzTensor getProductionBasisState(int) const;
  // get the basis state for the production

  inline LorentzTensor getDecayBasisState(int) const;
  // get the basis state for the decay

public:

  static void Init();
  // Standard Init function used to initialize the interfaces.

  virtual void rebind(const EventTranslationMap & trans);

  inline virtual EIPtr clone() const;
  // Standard clone method.

private:

  static NoPIOClassDescription<TensorSpinInfo> initTensorSpinInfo;
  // Describe a concrete class without persistent data.

  TensorSpinInfo & operator=(const TensorSpinInfo &);
  // Private and non-existent assignment operator.

private:

  mutable vector<LorentzTensor> _productionstates;
  // basis states in the frame in which the particle was produced

  mutable vector<LorentzTensor> _decaystates;
  // basis states in the frame in which the particle decays

  mutable bool _decaycalc;

};

}
}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of TensorSpinInfo.
template <>
struct BaseClassTrait<ThePEG::Helicity::TensorSpinInfo,1> {
  typedef ThePEG::Helicity::SpinInfo NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ThePEG::Helicity::TensorSpinInfo>
  : public ClassTraitsBase<ThePEG::Helicity::TensorSpinInfo> {
  static string className() { return "ThePEG::Helicity::TensorSpinInfo"; }
  // Return the class name.
  static string library() { return "libThePEGHelicity.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "TensorSpinInfo.icc"

#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "TensorSpinInfo.tcc"
#endif

#endif /* THEPEG_TensorSpinInfo_H */
