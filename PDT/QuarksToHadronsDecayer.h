// -*- C++ -*-
#ifndef THEPEG_QuarksToHadronsDecayer_H
#define THEPEG_QuarksToHadronsDecayer_H
//
// This is the declaration of the <!id>QuarksToHadronsDecayer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class decays particles to nq (2 or 4) quarks which then are
// decayes to hadrons according to phase space. The number of final
// hadrons can either be given by a fixed number or as a Gaussian
// multiplicity distribution centered around c+nq/4+c3 and a width
// sqrt(c), where c = c1 log((m - summ)/c2), m is the mass of the
// decaying particle, summ the sum of the quark masses and ci real
// parameters.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Decayer.html">Decayer.h</a>,
// <a href="http:ParticleData.html">ParticleData.h</a>.
// 

#include "ThePEG/PDT/Decayer.h"
#include "ThePEG/Handlers/FlavourGenerator.h"
// #include "QuarksToHadronsDecayer.fh"
// #include "QuarksToHadronsDecayer.xh"

namespace ThePEG {

ThePEG_DECLARE_CLASS_POINTERS(FlavourGenerator, FlavGenPtr);

class QuarksToHadronsDecayer: public Decayer {

public:

  inline QuarksToHadronsDecayer();
  inline QuarksToHadronsDecayer(const QuarksToHadronsDecayer &);
  virtual ~QuarksToHadronsDecayer();
  // Standard ctors and dtor.

public:

  virtual bool accept(const DecayMode &) const;
  // return true if this decayer can perfom the decay specified by the
  // given decay mode.

  virtual ParticleVector decay(const DecayMode &, const Particle &) const;
  // for a given decay mode and a given particle instance, perform the
  // decay and return the decay products.

  virtual int getN(Energy m0, Energy summq, int Nq) const;
  // Get the number of hadrons to be produced, given the mass of the
  // decaying particle and the number and summed masses of the quarks.

  virtual PVector getHadrons(int Nh, tcPDVector quarks) const;
  // Produce the specified number of hadrons from the specified
  // quarks. The last quark is considered to be a spectator quark.

public:

  inline int fixedN() const;
  // Return the fixed number of hadrons to be produced. If less than
  // 2, the number is instead given by a gaussian multiplicity
  // distribution.

  inline int minN() const;
  // Return the minimum number of hadrons to be produced.

  inline double c1() const;
  inline Energy c2() const;
  inline double c3() const;
  // Return the parameters used for the multiplicity distriution.

  inline tcFlavGenPtr flavourGenerator() const;
  // Return a pointer to the flavour generator to be used.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  int theFixedN;
  // The fixed number of hadrons to be produced. If less than 2, the
  // number is instead given by a gaussian multiplicity distribution.

  int theMinN;
  // The minimum hadrons to be produced.

  double theC1;
  Energy theC2;
  double theC3;
  // The parameters of the multiplicity distribution.

  FlavGenPtr theFlavourGenerator;
  // The object in charge of generating hadrons spieces from given
  // quark flavours.

private:

  static ClassDescription<QuarksToHadronsDecayer> initQuarksToHadronsDecayer;
  // Describe a concrete class with persistent data.

  QuarksToHadronsDecayer & operator=(const QuarksToHadronsDecayer &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of QuarksToHadronsDecayer.
template <>
struct BaseClassTrait<QuarksToHadronsDecayer,1> {
  typedef Decayer NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<QuarksToHadronsDecayer>
  : public ClassTraitsBase<QuarksToHadronsDecayer> {
  static string className() { return "ThePEG::QuarksToHadronsDecayer"; }
  // Return the class name.
  static string library() { return "QuarksToHadronsDecayer.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "QuarksToHadronsDecayer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "QuarksToHadronsDecayer.tcc"
#endif

#endif /* THEPEG_QuarksToHadronsDecayer_H */
