// -*- C++ -*-
#ifndef ThePEG_FlavourGenerator_H
#define ThePEG_FlavourGenerator_H
//
// This is the declaration of the <!id>FlavourGenerator<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>FlavourGenerator<!!id> is an abstract base class to be used to
// implement models describing the quark content of
// hadrons. <!id>FlavourGenerator<!!id> inherits from the
// <!class>HandlerBase<!!class> class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:HandlerBase.html">HandlerBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "FlavourGenerator.fh"
// #include "FlavourGenerator.xh"
#include "ThePEG/Handlers/HandlerBase.h"

namespace ThePEG {

class FlavourGenerator: public HandlerBase {
   
public:

  inline FlavourGenerator();
  inline FlavourGenerator(const FlavourGenerator &);
  virtual ~FlavourGenerator();
  // Standard ctors and dtor

public:

  virtual PDPtr generateHadron(tcPDPtr quark, cPDPtr & antiQuark, 
			       long curtainQid = 0 ) = 0;
  // Given a quark, choose a quark-antiquark pair. Return a meson
  // formed by the original quark and the anti-quark.

  virtual PDPtr getHadron(tcPDPtr quark, tcPDPtr antiQuark) = 0;

  virtual PDPtr getBaryon(tcPDPtr quark1, tcPDPtr quark2, tcPDPtr quark3) = 0;

  virtual vector<tcPDPtr> getHadrons(tcPDPtr quark, tcPDPtr antiQuark) = 0;

  virtual vector<tcPDPtr> getBaryons(tcPDPtr q1, tcPDPtr q2, tcPDPtr q3) = 0;

  virtual void splitHadron(tcPDPtr hadron, cPDPtr & quark,
			   cPDPtr & rest) const;
  // For a given hadron if quark is null, set 'quark' to a random
  // valens quark. Then set 'rest' to a corresponding anti-quark in
  // case of a meson and a di-quark in case of a baryon.

  //virtual void doupdate() throw(UpdateException);
  //virtual void doinit() throw(InitException);
  //virtual void dofinish();
  // Standard Interfaced virtual functions.

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.


private:

  static AbstractNoPIOClassDescription<FlavourGenerator> initFlavourGenerator;

  FlavourGenerator & operator=(const FlavourGenerator &);
  //  Private and non-existent assignment operator.

};

template <>
struct BaseClassTrait<FlavourGenerator,1> {
  typedef HandlerBase NthBase;
};

template <>
struct ClassTraits<FlavourGenerator>: public ClassTraitsBase<FlavourGenerator> {
  static string className() {
    return "/ThePEG/FlavourGenerator";
  }
};

}

#include "FlavourGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlavourGenerator.tcc"
#endif

#endif /* ThePEG_FlavourGenerator_H */
