// -*- C++ -*-
#ifndef THEPEG_VectorSpinInfo_H
#define THEPEG_VectorSpinInfo_H
//
// This is the declaration of the <!id>VectorSpinInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  This is the implementation of the spin information for vector particles.
//  It inherits from the SpinInof class and implements the storage of the basis vectors.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "SpinInfo.h"
#include "ThePEG/Helicity/Lorentz/LorentzPolarizationVector.h"
// #include "VectorSpinInfo.fh"
// #include "VectorSpinInfo.xh"

namespace ThePEG {
  namespace Helicity {
    using namespace ThePEG;
    ThePEG_DECLARE_CLASS_POINTERS(VectorSpinInfo,HwVSpinPtr);
    class VectorSpinInfo: public SpinInfo {
      
    public:
      
      inline VectorSpinInfo();
      inline VectorSpinInfo(const VectorSpinInfo &);
      inline VectorSpinInfo(const Lorentz5Momentum &,bool);
      virtual ~VectorSpinInfo();
      // Standard ctors and dtor.

    public:

      // set and get methods for the basis states
      inline void setBasisState(int,LorentzPolarizationVector) const;
      // set the basis state, this is production state
      inline void setDecayState(int,LorentzPolarizationVector) const;
      // set the decay basis state
      inline LorentzPolarizationVector getProductionBasisState(int) const;
      // get the basis state for the production
      inline LorentzPolarizationVector getDecayBasisState(int) const;
      // get the basis state for the decay

    public:
      
      static void Init();
      // Standard Init function used to initialize the interfaces.

      virtual void rebind(const EventTranslationMap & trans);

      inline virtual EIPtr clone() const;
      // Standard clone method.

    private:
      
      static NoPIOClassDescription<VectorSpinInfo> initVectorSpinInfo;
      // Describe a concrete class without persistent data.
      
      VectorSpinInfo & operator=(const VectorSpinInfo &);
      // Private and non-existent assignment operator.

    private:

      mutable vector<LorentzPolarizationVector> _productionstates;
      // basis states in the frame in which the particle was produced
      mutable vector<LorentzPolarizationVector> _decaystates;
      // basis states in the frame in which the particle decays 
      mutable bool _decaycalc;      
    };
  }
}

// CLASSDOC OFF

namespace ThePEG {
  
  // The following template specialization informs ThePEG about the
  // base class of VectorSpinInfo.
  template <>
  struct BaseClassTrait<ThePEG::Helicity::VectorSpinInfo,1> {
    typedef ThePEG::Helicity::SpinInfo NthBase;
  };
  
  // The following template specialization informs ThePEG about the
  // name of this class and the shared object where it is defined.
  template <>
  struct ClassTraits<ThePEG::Helicity::VectorSpinInfo>
    : public ClassTraitsBase<ThePEG::Helicity::VectorSpinInfo> {
    static string className() { return "ThePEG::Helicity::VectorSpinInfo"; }
    // Return the class name.
    static string library() { return "libThePEGHelicity.so"; }
    // Return the name of the shared library to be loaded to get
    // access to this class and every other class it uses
    // (except the base class).
  };
  
}

#include "VectorSpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "VectorSpinInfo.tcc"
#endif

#endif /* THEPEG_VectorSpinInfo_H */
