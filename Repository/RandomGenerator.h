// -*- C++ -*-
#ifndef ThePEG_RandomGenerator_H
#define ThePEG_RandomGenerator_H
// This is the declaration of the RandomGenerator class.

#include "ThePEG/Config/ThePEG.h"
// #include "RandomGenerator.fh"
// #include "RandomGenerator.xh"
#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/CLHEPWrap/RandomEngine.fh"

namespace ThePEG {

/**
 * RandomGenerator is an interface to the CLHEP::RandomEngine
 * classes. To avoid excessive virtual function calls, the
 * RandomGenerator caches random numbers generated by the engine which
 * are then retrieved by the non-virtual inlined rnd() method.
 *
 * Sub-classes of RandomGenerator should be used to
 * implement a particular random engine.
 *
 * RandomGenerator only provides a flat distribution between 0 and
 * 1. Any other distribution can be achieved using the CLHEP random
 * classes using the engine returned from the randomGenerator()
 * method.
 *
 *
 * @see UseRandom.
 */
class RandomGenerator: public Interfaced {

public:

  /** A vector of doubles. */
  typedef vector<double> RndVector;

  /** The size_type of RndVector. */
  typedef RndVector::size_type size_type;

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  RandomGenerator();

  /**
   * Copy-constructor.
   */
  RandomGenerator(const RandomGenerator &);

  /**
   * Destructor.
   */
  virtual ~RandomGenerator();
  //@}

  /** @name Access the underlying random engine. */
  //@{
  /**
   * Return a reference to the underlying CLHEP:RandomEngine.
   */
  virtual RandomEngine & randomGenerator() = 0;

  /**
   * Reset the underlying CLHEP random engine with the given \a seed.
   */
  virtual void setSeed(long seed) = 0;
  //@}

  /** @name Functions to return random numbers. */
  //@{
  /**
   * Return a (possibly cached) flat random number in the interval
   * \f$]0,1[\f$.
   */
  inline double rnd();

  /**
   * Return a (possibly cached) flat random number in the interval
   * \f$]0,1[\f$.
   */
  inline double operator()();

  /**
   * Return a true with probability \a p. Uses rnd(). Also uses
   * push_back(double).
   */
  bool rndbool(double p = 0.5);

  /**
   * Return a true with probability \a p1/(\a p1+\a p2). Uses
   * rnd(). Also uses push_back(double).
   */
  inline bool rndbool(double p1, double p2);

  /**
   * Return -1, 0, or 1 with relative probabilities \a p1, \a p2, \a
   * p3. Uses rnd(). Also uses push_back(double).
   */
  int rndsign(double p1, double p2, double p3);

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a
   * p1). Uses rnd().
   */
  inline int rnd2(double p0, double p1);

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a
   * p1+\a p2). Uses rnd().
   */
  inline int rnd3(double p0, double p1, double p2);

  /**
   * Return an integer/ \f$i\f$ with probability p\f$i\f$(\a p0+\a
   * p1+\a p2+\a p3). Uses rnd().
   */
  int rnd4(double p0, double p1, double p2, double p3);
  //@}

  /** @name Access the cached random numbers from the underlying engine. */
  //@{
  /**
   * Give back a partly unused random number. This is typically used
   * when generating integral random numbers. In eg. rndbool(double p)
   * a random number <code>r</code> is drawn and if it is less than
   * <code>p</code> true is returned, but <code>r</code> is still a
   * good random number in the interval <code>]0,p[</code>. Hence
   * <code>r/p</code> is still a good random number in the interval
   * <code>]0,1[</code> and this is then pushed back into the cache
   * and is used by the next call to rnd(). Note that the resulting
   * random number is of lesser quality, and successive calls to
   * push_back() should be avoided. To ensure a highest quality random
   * number random number in the next call to rnd(), pop_back() should
   * be used.
   */
  inline void push_back(double r);

  /**
   * Discard the next random number in the cache.
   */
  inline void pop_back();

  /**
   * Discard all random numbers in the cache. Typically used after the
   * internal random engine has been reinitialized for some reason.
   */
  inline void flush();

  /**
   * Generate n random numbers between 0 and 1 and put them in the
   * output iterator.
   */
  template <typename OutputIterator>
  inline void rnd(OutputIterator, size_type n);
  //@}

protected:

  /**
   * Initializes this random generator. This should be done first of
   * all before the initialization of any other object associated with
   * an event generator.
   */
  virtual void doinit() throw (InitException);

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
   * Standard Init function used to initialize the interface.
   */
  static void Init();

private:

  /**
   * Utility function for the interface.
   */
  void setSize(size_type newSize);

  /**
   * Fill the cache with random numbers.
   */
  virtual void getFlatNumbers();

  /**
   * A vector of cached numbers.
   */
  RndVector theNumbers;

  /**
   * Iterator pointing to the next number to be extracted
   */
  RndVector::iterator nextNumber;

  /**
   * The size of the cache.
   */
  size_type theSize;

  /**
   * The seed to initialize the random generator with.
   */
  long theSeed;

private:

  /**
   * Describe a concrete class with persistent data. Note that the
   * class should in principle be abstract.
   */
  static ClassDescription<RandomGenerator> initRandomGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  RandomGenerator & operator=(const RandomGenerator &);

};

/** This template specialization informs ThePEG about the base classes
 *  of RandomGenerator. */
template <>
struct BaseClassTrait<RandomGenerator,1> {
  /** Typedef of the first base class of RandomGenerator. */
  typedef Interfaced NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  RandomGenerator class. */
template <>
struct ClassTraits<RandomGenerator>:
    public ClassTraitsBase<RandomGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::RandomGenerator";
  }
  /** This class should in principle be abstract, therefore the
      create() method will throw a std::logic_error if called. */
  static TPtr create() {
    throw std::logic_error("Tried to instantiate abstract class"
			   "'Pythis7::RandomGenerator'");
    return TPtr();
  }
};

}

#include "RandomGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RandomGenerator.tcc"
#endif

#endif /* ThePEG_RandomGenerator_H */
