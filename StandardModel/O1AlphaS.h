// -*- C++ -*-
#ifndef ThePEG_O1AlphaS_H
#define ThePEG_O1AlphaS_H
//
// This is the declaration of the <!id>O1AlphaS<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>O1AlphaS<!!id> inherits from <!class>AlphaSBase<!!class> and
// implements the leading order running QCD coupling.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:AlphaSBase.html">AlphaSBase.h</a>.
// 

#include "AlphaSBase.h"
// #include "O1AlphaS.fh"
// #include "O1AlphaS.xh"

namespace ThePEG {

class O1AlphaS: public AlphaSBase {

public:

  inline O1AlphaS();
  inline O1AlphaS(const O1AlphaS &);
  virtual ~O1AlphaS();
  // Standard ctors and dtor

public:

  virtual double value(Energy2 scale, const StandardModelBase &) const;
  // Return the alpha_S for a given scale.

  virtual vector<Energy2> flavourThresholds() const;
  // Return the flavour thresholds used.

  virtual vector<Energy> LambdaQCDs() const;
  // Return the lambda_QCD used for different numbers of active flavours.

public:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

  unsigned int getMaxFlav() const;

protected:

  virtual IBPtr clone() const;
  virtual IBPtr fullclone() const;
  // Standard clone methods

  inline virtual void
  rebind(const TranslationMap & trans) throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  Energy theLambdaQCD;
  unsigned int theLambdaFlavour;
  // The lambdaQCD for the number of flavours specified by theLambdaFlavour.

  unsigned int theMaxFlav;

private:

  static ClassDescription<O1AlphaS> initO1AlphaS;

  O1AlphaS & operator=(const O1AlphaS &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<O1AlphaS,1> {
  typedef AlphaSBase NthBase;
};

template <>
struct ClassTraits<O1AlphaS>: public ClassTraitsBase<O1AlphaS> {
  static string className() { return "/ThePEG/O1AlphaS"; }
  static string library() { return "O1AlphaS.so"; }
};

}

#include "O1AlphaS.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "O1AlphaS.tcc"
#endif

#endif /* ThePEG_O1AlphaS_H */
