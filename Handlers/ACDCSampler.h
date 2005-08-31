// -*- C++ -*-
#ifndef ThePEG_ACDCSampler_H
#define ThePEG_ACDCSampler_H
// This is the declaration of the ACDCSampler class.

#include "ThePEG/Handlers/SamplerBase.h"
#include "ThePEG/ACDC/ACDCGen.h"
#include "ThePEG/Handlers/StandardEventHandler.h"
#include "ThePEG/Repository/RandomGenerator.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/Utilities/SimplePhaseSpace.xh"
// #include "ACDCSampler.fh"
// #include "ACDCSampler.xh"

namespace ThePEG {

/**
 * This class inherits from SampleBase and implements
 * the Auto Compensating Divide-and-Conquer phase space generator,
 * ACDCGen.
 *
 * @see \ref ACDCSamplerInterfaces "The interfaces"
 * defined for ACDCSampler.
 * @see ACDCGen
 */
class ACDCSampler: public SamplerBase {

public:

  /** Typedef the underlying ACDCGen class. */
  typedef ACDCGenerator::ACDCGen<UseRandom,tStdEHPtr> SamplerType;

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline ACDCSampler();

  /**
   * The copy constructor.
   */
  inline ACDCSampler(const ACDCSampler &);

  /**
   * The destructor.
   */
  virtual ~ACDCSampler();
  //@}

public:

  /** @name Virtual functions needed for SamplerBase */
  //@{
  /**
   * Initialize the the sampler, possibly doing presampling of the
   * phase space.
   */
  virtual void initialize();

  /**
   * Generarate a new phase space point and return a weight associated
   * with it. This weight should preferably be 1.
   */
  virtual double generate();

  /**
   * ACDCSampler is able to sample several different functions
   * separately. This function returns the last chosen
   * function.
   */
  virtual int lastBin() const;

  /**
   * Reject the last chosen phase space point.
   */
  virtual void rejectLast();

  /**
   * Return the total integrated cross section determined from the
   * Monte Carlo sampling so far.
   */
  virtual CrossSection integratedXSec() const;

  /**
   * Return the sum of the weights returned by generate() so far (of
   * the events that were not rejeted).
   */
  virtual double sumWeights() const;

  //@}

public:

  /** @name Functions used by the persistent I/O system. */
  //@{
  /**
   * Function used to write out object persistently.
   * @param os the persistent output stream written to.
   */
  void persistentOutput(PersistentOStream & os) const;

  /**
   * Function used to read in object persistently.
   * @param is the persistent input stream read from.
   * @param version the version number of the object when written.
   */
  void persistentInput(PersistentIStream & is, int version);
  //@}

  /**
   * The standard Init function used to initialize the interfaces.
   * Called exactly once for each class by the class description system
   * before the main function starts or
   * when this class is dynamically loaded.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  inline virtual IBPtr fullclone() const;

  //@}

protected:

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving an
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  virtual void dofinish();


  /**
   * Rebind pointer to other Interfaced objects. Called in the setup phase
   * after all objects used in an EventGenerator has been cloned so that
   * the pointers will refer to the cloned objects afterwards.
   * @param trans a TranslationMap relating the original objects to
   * their respective clones.
   * @throws RebindException if no cloned object was found for a given pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The actual sampler object.
   */
  SamplerType theSampler;

  /**
   * The smallest possible division allowed.
   */
  double theEps;

  /**
   * The factor controlling the loss of efficiency when compensating.
   */
  double theMargin;

  /**
   * The number of points to use to find initial average.  
   */
  int theNTry;

protected:

  /** Exception class used by ACDCSampler if the undelying ACDCGen was
      still in a compensating mode when the run was finished */
  struct ACDCStillCompensating: public Exception {};

  /** Exception class used by ACDCSampler if a StandardEventHandler
      was not able to produce a non-zero cross section. */
  struct EventInitNoXSec: public Exception {};

  /** Exception class used if ACDCSampler was not able to produce a
      phase space point within the maximum allowed number of
      attempts. */
  struct EventLoopException: public Exception {};

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<ACDCSampler> initACDCSampler;

  /**
   *  Private and non-existent assignment operator.
   */
  ACDCSampler & operator=(const ACDCSampler &);

};

}


namespace ThePEG {

/**
 * The following template specialization informs ThePEG about the
 * base class of ACDCSampler.
 */
template <>
struct BaseClassTrait<ACDCSampler,1>: public ClassTraitsType {
  /** Typedef of the first base class of ACDCSampler. */
  typedef SamplerBase NthBase;
};

/**
 * The following template specialization informs ThePEG about the
 * name of this class and the shared object where it is defined.
 */
template <>
struct ClassTraits<ACDCSampler>: public ClassTraitsBase<ACDCSampler> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::ACDCSampler"; }
  /** Return the name of the shared library to be loaded to get
   * access to this class and every other class it uses
   * (except the base class).
   */
  static string library() { return "ACDCSampler.so"; }

};

}

namespace ACDCGenerator {

/** Specialized Traits class to define the interface to the
 * StandardEventHandler object to be sampled by ACDCGen.
 */
template <>
struct ACDCFncTraits<ThePEG::tStdEHPtr>: public ACDCTraitsType {
  /** Convenient typdef. */
  typedef ThePEG::tStdEHPtr tStdEHPtr;
  /**
   * Call a function to be sampled by ACDCGen.
   * @return <code>(*f)(x)</code>.
   */
  static inline double value(const tStdEHPtr & eh, const DVector & x) {
    using namespace ThePEG::Units;
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

/** Specialized Traits class to inform ACDCGen how to use the
    RandomGenerator class. */
template <>
struct ACDCRandomTraits<ThePEG::RandomGenerator>: public ACDCTraitsType {
  /** Convenient typedef. */
  typedef ThePEG::RandomGenerator RandomGenerator;

  /**
   * Return a flat random number in the interval ]0,1[.
   */
  static inline double rnd(RandomGenerator * r) { return r->rnd(); }

  /**
   * Return a flat random number in the interval ]\a xl,\a xu[.
   */
  static inline double rnd(RandomGenerator * r, double xl, double xu) {
    return xl + (xu - xl)*rnd(r);
  }

  /**
   * Generate a set of random numbers.
   * @param r the random generator.
   * @param l an input iterator giving the lower limit of the interval
   * of the first requested random number.
   * @param lend an input iterator marking the end of the range of
   * requested random numbers.
   * @param u an input iterator giving the upper limit of the interval
   * of the first requested random number.
   * @param res the ouput iterator used to output the random numbers.
   */
  template <typename InputIterator, typename OutputIterator>
  static inline void rnd(RandomGenerator * r,
			 InputIterator l, InputIterator lend,
			 InputIterator u, OutputIterator res) {
    for ( ; l != lend; ++l ) *res++ = *l + (*u++ - *l)*rnd(r);
  }

  /**
   * Generate \a D random numbers. The numbers are put into the
   * OutputIterator \a res.
   */
  template <typename OutputIterator>
  static inline void rnd(RandomGenerator * r, int D, OutputIterator res) {
    for ( int d = 0; d < D; ++d ) *res++ = rnd(r);
  }

  /**
   * Return true with probability \a x.
   */
  static inline bool rndBool(RandomGenerator * r, double x) {
    return r->rndbool(x);
  }

  /**
   * Return true with probability \a x(\a x + \a y).
   */
  static inline bool rndBool(RandomGenerator * r, double x, double y) {
    return r->rndbool(x, y);
  }

  /**
   * Return a random integer in the interval [0,\a x[.
   */
  static inline long rndInt(RandomGenerator * r, long x) {
    return long(rnd(r, 0.0, double(x)));
  }

};

/** Specialized Traits class to inform ACDCGen how to use the
    static UseRandom class. */
template <>
struct ACDCRandomTraits<ThePEG::UseRandom>: public ACDCTraitsType {
  /** Convenient typedef. */
  typedef ThePEG::UseRandom UseRandom;

  /**
   * Return a flat random number in the interval ]0,1[.
   */
  static inline double rnd(UseRandom *) { return UseRandom::rnd(); }

  /**
   * Return a flat random number in the interval ]\a xl,\a xu[.
   */
  static inline double rnd(UseRandom * r, double xl, double xu) {
    return xl + (xu - xl)*rnd(r);
  }

  /**
   * Generate a set of random numbers.
   * @param r the random generator.
   * @param l an input iterator giving the lower limit of the interval
   * of the first requested random number.
   * @param lend an input iterator marking the end of the range of
   * requested random numbers.
   * @param u an input iterator giving the upper limit of the interval
   * of the first requested random number.
   * @param res the ouput iterator used to output the random numbers.
   */
  template <typename InputIterator, typename OutputIterator>
  static inline void rnd(UseRandom * r,
			 InputIterator l, InputIterator lend,
			 InputIterator u, OutputIterator res) {
    for ( ; l != lend; ++l ) *res++ = *l + (*u++ - *l)*rnd(r);
  }

  /**
   * Generate \a D random numbers. The numbers are put into the
   * OutputIterator \a res.
   */
  template <typename OutputIterator>
  static inline void rnd(UseRandom * r, int D, OutputIterator res) {
    for ( int d = 0; d < D; ++d ) *res++ = rnd(r);
  }

  /**
   * Return true with probability \a x.
   */
  static inline bool rndBool(UseRandom * r, double x) {
    return UseRandom::rndbool(x);
  }

  /**
   * Return true with probability \a x(\a x + \a y).
   */
  static inline bool rndBool(UseRandom * r, double x, double y) {
    return UseRandom::rndbool(x, y);
  }

  /**
   * Return a random integer in the interval [0,\a x[.
   */
  static inline long rndInt(UseRandom * r, long x) {
    return long(rnd(r, 0.0, double(x)));
  }

};

}

#include "ACDCSampler.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ACDCSampler.tcc"
#endif

#endif /* ThePEG_ACDCSampler_H */
