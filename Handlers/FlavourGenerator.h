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

  virtual tcPDPair generateHadron(tcPDPtr quark) const = 0;
  // Given a quark(antiquark, diquark or antidiquark), choose a
  // quark-antiquark (or antidiquark-diquark) pair. Return (first) a
  // hadron formed by the original quark and the anti-quark together
  // with (second) the generated quark. Returns null pointers if the
  // generation failed.

  tcPDPair alwaysGenerateHadron(tcPDPtr quark) const;
  // Same as generateHadron(), but throws an exception if no hadron
  // could be produced.

  virtual tcPDPtr getHadron(tcPDPtr q1, tcPDPtr q2) const;
  virtual tcPDPtr getHadron(long iq1, long iq2) const;
  // Return a hadron with the flavour content given by the
  // (anti)(di)quarks in the argument. The arguments can be given
  // either as particle data pointers or PDG codes. The default
  // versions will call eachother, so one of them must be implemented
  // by a subclass to avoid an infinite loop. If no corresponding
  // hadron was formed it should return the null pointer.

  tcPDPtr alwaysGetHadron(tcPDPtr q1, tcPDPtr q2) const;
  tcPDPtr alwaysGetHadron(long iq1, long iq2) const;
  // Same as getHadron() but thows an exception if no hadron could be
  // produced.

  virtual tcPDPtr getBaryon(tcPDPtr q1, tcPDPtr q2, tcPDPtr q3) const;
  virtual tcPDPtr getBaryon(long q1, long q2, long q3) const;
  // Return a baryon with the flavour content given by the
  // (anti)quarks in the argument.  The arguments can be given either
  // as particle data pointers or PDG codes. The default versions will
  // call eachother, so one of them must be implemented by a subclass
  // to avoid an infinite loop. If no corresponding hadron was formed
  // it should return the null pointer.

  tcPDPtr alwaysGetBaryon(tcPDPtr q1, tcPDPtr q2, tcPDPtr q3) const;
  tcPDPtr alwaysGetBaryon(long q1, long q2, long q3) const;
  // Same as getBaryon(), but thros an exception if no baryon could be
  // produced.

  virtual long selectQuark() const = 0;
  // Generate a random quark flavour.

  virtual long selectFlavour() const = 0;
  // Generate a random (di)quark flavour.

public:

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

class FlavourGeneratorException: public Exception {};

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
