// -*- C++ -*-
#ifndef ThePEG_ACDCSampler_H
#define ThePEG_ACDCSampler_H
//
// This is the declaration of the <!id>ACDCSampler<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This class inherits from <!class>SampleBase<!!class> and implements
// the Auto Compensating Divide-and-Conquer phase space generator,
// <!class>ACDCGen<!!class>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:SampleBase.html">SampleBase.h</a>,
// <a href="http:ACDCGen.html">ACDCGen.h</a>.
// 

#include "ThePEG/Handlers/SamplerBase.h"
#include "ThePEG/ACDC/ACDCGen.h"
#include "ThePEG/Handlers/EventHandler.h"
#include "ThePEG/Repository/RandomGenerator.h"
#include "ThePEG/Utilities/SimplePhaseSpace.xh"
// #include "ACDCSampler.fh"
// #include "ACDCSampler.xh"

namespace ThePEG {

class ACDCSampler: public SamplerBase {

public:

  typedef ACDCGenerator::ACDCGen<RandomGenerator,tEHPtr> SamplerType;

  inline ACDCSampler();
  inline ACDCSampler(const ACDCSampler &);
  virtual ~ACDCSampler();
  // Standard ctors and dtor.

public:

  virtual void initialize();
  // Initialize the the sampler, possibly doing presampling of the
  // phase space.

  virtual double generate();
  // Generarate a new phase space point and return a weight associated
  // with it. This weight should preferably be 1.

  virtual int lastBin() const;
  // ACDCSampler is able to sample several different functions
  // separately. This function returns the last chosen
  // function.

  virtual void rejectLast();
  // Reject the last chosen phase space point.

  virtual CrossSection integratedXSec() const;
  // Return the total integrated cross section determined from the
  // Monte Carlo sampling so far.

  virtual double sumWeights() const;
  // Return the sum of the weights returned by generate() so far (of
  // the events that were not rejeted).

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
  virtual void doinitrun();
  virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

private:

  SamplerType theSampler;
  // The actual sampler object.

  double theEps;
  // The smallest possible division allowed.

  double theMargin;
  // The factor controlling the loss of efficiency when compensating.

  int theNTry;
  // The number of points to use to find initial average.  

private:

  static ClassDescription<ACDCSampler> initACDCSampler;
  // Describe a concrete class with persistent data.

  ACDCSampler & operator=(const ACDCSampler &);
  //  Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of ACDCSampler.
template <>
struct BaseClassTrait<ACDCSampler,1> {
  typedef SamplerBase NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<ACDCSampler>: public ClassTraitsBase<ACDCSampler> {
  static string className() { return "/ThePEG/ACDCSampler"; }
  // Return the class name.
  static string library() { return "ACDCSampler.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

namespace ACDCGenerator {

template <>
struct ACDCFncTraits<ThePEG::tEHPtr> {
  typedef ThePEG::tEHPtr tEHPtr;
  static inline double value(const tEHPtr & eh, const DVector & x) {
    try {
      return eh->dSigDR(x)*ThePEG::sqr(hbarc)/nanobarn;
    }
    catch ( ThePEG::ImpossibleKinematics & v ) {
      breakThePEG();
    }
    catch ( std::exception & e ) {
      breakThePEG();
    }
    catch ( ... ) {
      breakThePEG();
    }
    return 0.0;
  }

};

template <>
struct ACDCRandomTraits<ThePEG::RandomGenerator> {
  typedef ThePEG::RandomGenerator RandomGenerator;

  static inline double rnd(RandomGenerator & r) { return r.rnd(); }
  static inline double rnd(RandomGenerator & r, double xl, double xu) {
    return xl + (xu - xl)*rnd(r);
  }
  template <typename InputIterator, typename OutputIterator>
  static inline void rnd(RandomGenerator & r,
			 InputIterator l, InputIterator lend,
			 InputIterator u, OutputIterator res) {
    for ( ; l != lend; ++l ) *res++ = *l + (*u++ - *l)*rnd(r);
  }
  template <typename OutputIterator>
  static inline void rnd(RandomGenerator & r, int D, OutputIterator res) {
    for ( int d = 0; d < D; ++d ) *res++ = rnd(r);
  }
  static inline bool rndBool(RandomGenerator & r, double x) {
    return r.rndbool(x);
  }
  static inline bool rndBool(RandomGenerator & r, double x, double y) {
    return r.rndbool(x, y);
  }
  static inline long rndInt(RandomGenerator & r, long x) {
    return long(rnd(r, 0.0, double(x)));
  }

};

}

#include "ACDCSampler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ACDCSampler.tcc"
#endif

#endif /* ThePEG_ACDCSampler_H */
