// -*- C++ -*-
#ifndef ThePEG_ThePEGStrategy_H
#define ThePEG_ThePEGStrategy_H
//
// This is the declaration of the <!id>ThePEGStrategy<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ThePEGStrategy<!!id> class is a sub-class of the Strategy
// class, simply implementing the correct citation for ThePEG in the
// modelReferences() method.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Strategy.html">Strategy.h</a>
// 

#include "ThePEG/Repository/Strategy.h"
// #include "ThePEGStrategy.fh"
// #include "ThePEGStrategy.xh"

namespace ThePEG {

class ThePEGStrategy: public Strategy {

public:

  inline ThePEGStrategy();
  inline ThePEGStrategy(const ThePEGStrategy &);
  virtual ~ThePEGStrategy();
  // Standard ctors and dtor.

public:

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  static NoPIOClassDescription<ThePEGStrategy> initThePEGStrategy;
  // Describe concrete class without persistent data.

  ThePEGStrategy & operator=(const ThePEGStrategy &);
  //  Private and non-existent assignment operator.

};

// CLASSDOC OFF

template <>
struct BaseClassTrait<ThePEGStrategy,1> {
  typedef Strategy NthBase;
};

template <>
struct ClassTraits<ThePEGStrategy>: public ClassTraitsBase<ThePEGStrategy> {
  static string className() { return "/ThePEG/ThePEGStrategy"; }
  static string library() { return "ThePEGStrategy.so"; }
};

}

#include "ThePEGStrategy.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ThePEGStrategy.tcc"
#endif

#endif /* ThePEG_ThePEGStrategy_H */
