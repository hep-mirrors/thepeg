// -*- C++ -*-
#ifndef ThePEG_ScalarSpinInfo_H
#define ThePEG_ScalarSpinInfo_H
//
// This is the declaration of the <!id>ScalarSpinInfo<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
//  The ScalarSpinInfo class is designed to be the implementation of the spin information for a 
//  scalar particle. Obviously it is pretty trival in this case.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "SpinInfo.h"
// #include "ScalarSpinInfo.fh"
// #include "ScalarSpinInfo.xh"

namespace ThePEG {
  namespace Helicity {
    using namespace ThePEG;
    ThePEG_DECLARE_CLASS_POINTERS(ScalarSpinInfo,HwSSpinPtr);
    class ScalarSpinInfo: public SpinInfo {

    public:

      inline ScalarSpinInfo();
      inline ScalarSpinInfo(const Lorentz5Momentum &,bool);
      inline ScalarSpinInfo(const ScalarSpinInfo &);
      virtual ~ScalarSpinInfo();
      // Standard ctors and dtor.
      
    public:
      
      static void Init();
      // Standard Init function used to initialize the interfaces.
      
      inline virtual EIPtr clone() const;
      // Standard clone methods.
      
      inline virtual void rebind(const EventTranslationMap & trans);
      // Change all pointers to Interfaced objects to corresponding clones.

    private:
      
      static NoPIOClassDescription<ScalarSpinInfo> initScalarSpinInfo;
      // Describe a concrete class without persistent data.
      
      ScalarSpinInfo & operator=(const ScalarSpinInfo &);
      // Private and non-existent assignment operator.
      
    };
  }
}

// CLASSDOC OFF

namespace ThePEG {
  
  // The following template specialization informs ThePEG about the
  // base class of ScalarSpinInfo.
  template <>
  struct BaseClassTrait<ThePEG::Helicity::ScalarSpinInfo,1> {
    typedef ThePEG::Helicity::SpinInfo NthBase;
  };
  
  // The following template specialization informs ThePEG about the
  // name of this class and the shared object where it is defined.
  template <>
  struct ClassTraits<ThePEG::Helicity::ScalarSpinInfo>
    : public ClassTraitsBase<ThePEG::Helicity::ScalarSpinInfo> {
    static string className() { return "ThePEG::Helicity::ScalarSpinInfo"; }
    // Return the class name.
    static string library() { return "libThePEGHelicity.so"; }
    // Return the name of the shared library to be loaded to get
    // access to this class and every other class it uses
    // (except the base class).
  };
  
}

#include "ScalarSpinInfo.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ScalarSpinInfo.tcc"
#endif

#endif /* ThePEG_ScalarSpinInfo_H */
