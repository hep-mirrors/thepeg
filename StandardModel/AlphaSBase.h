// -*- C++ -*-
#ifndef ThePEG_AlphaSBase_H
#define ThePEG_AlphaSBase_H
//
// This is the declaration of the <!id>AlphaSBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>AlphaSBase<!!id> is used by the
// <!class>StandardModelBase<!!class> to implement the QCD
// coupling. The <!id>AlphaSBase<!!id> also encodes the number of
// active flavours at a given scale and the Lambda<SUB>QCD</SUB> for a
// given number of active flavours or for a given scale.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:StandardModelBase.html">StandardModelBase.h</a>.
// 

#include "ThePEG/Interface/Interfaced.h"
#include "StandardModelBase.fh"
// #include "AlphaSBase.fh"
// #include "AlphaSBase.xh"

namespace ThePEG {

class AlphaSBase: public Interfaced {

public:

  inline AlphaSBase();
  inline AlphaSBase(const AlphaSBase &);
  virtual ~AlphaSBase();
  // Standard ctors and dtor

public:

  virtual double value(Energy2 scale, const StandardModelBase &) const = 0;
  // Return the alpha_S for a given scale.

  virtual vector<Energy2> flavourThresholds() const = 0;
  // Return the flavour thresholds used.

  virtual vector<Energy> LambdaQCDs() const = 0;
  // Return the lambda_QCD used for different numbers of active flavours.

  inline unsigned int Nf(Energy2 scale) const;
  // Return the number of avtive quark flavours.

  inline Energy LambdaQCD(unsigned int nflav) const;
  inline Energy LambdaQCD(Energy2 scale) const;
  // Return the \Lambda_{QCD} for the number of active flavours
  // (corresponding to the given scale).

public:

  inline virtual void doupdate() throw(UpdateException);
  virtual void doinit() throw(InitException);
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

private:

  vector<Energy2> theFlavourThresholds;
  vector<Energy> theLambdaQCDs;
  // flavour thresholds and the corresponding lambdas, set from
  // theRunningAlphaS at initialization.

private:

  static AbstractClassDescription<AlphaSBase> initAlphaSBase;

  AlphaSBase & operator=(const AlphaSBase &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<AlphaSBase,1> {
  typedef Interfaced NthBase;
};

template <>
struct ClassTraits<AlphaSBase>: public ClassTraitsBase<AlphaSBase> {
  static string className() { return "/ThePEG/AlphaSBase"; }
};

}

#include "AlphaSBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AlphaSBase.tcc"
#endif

#endif /* ThePEG_AlphaSBase_H */
