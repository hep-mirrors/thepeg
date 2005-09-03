// -*- C++ -*-
#ifndef ThePEG_HandlerBase_H
#define ThePEG_HandlerBase_H
// This is the declaration of the HandlerBase class.

#include "ThePEG/Interface/Interfaced.h"
#include "ThePEG/Repository/UseRandom.fh"
#include <stdexcept>

namespace ThePEG {

template <typename T = UseRandom>
/**
 * HandlerBaseT is a dummy abstract templated class used as base class
 * to HandlerBase. HandlerBaseT inherits from the Interfaced class
 * adding some functionality such as easy acces to the RandomGenerator
 * and the StandardModel object of the controlling EventGenerator
 * object. The HandlerBaseT should only be used by the HandlerBase as
 * a base class. The fact that it is templated allows classes which in
 * turn inherits from HandlerBase to not explicitly depend on
 * EventGenerator class if the inlined accessor funtions are not
 * actually used. The only class which actually works as a template
 * argument is UseRandom, which is used to generate random numbers.
 *
 * @see Interfaced
 * @see RandomGenerator
 * @see StandardModel
 * @see EventGenerator
 * 
 */
class HandlerBaseT: public Interfaced {


public:

  /** HandlerBase is a friend. */
  friend class HandlerBase;

private:

  /** @name Standard constructors and destructors are private and can
   * only be used from the HandlerBase class. */
  //@{
  /**
   * Default constructor.
   */
  inline HandlerBaseT();

  /**
   * Copy-constructor.
   */
  inline HandlerBaseT(const HandlerBaseT &);

  /**
   * Destructor.
   */
  virtual ~HandlerBaseT();
  //@}

public:

  /**
   * Return a simple flat random number in the range ]0,1[.
   */
  inline double rnd() const;

  /**
   * Return a simple flat random number in the range ]0,\a xu[.
   */
  inline double rnd(double xu) const;

  /**
   * Return a simple flat random number in the range ]\a xl,\a xu[.
   */
  inline double rnd(double xl, double xu) const;

  /**
   * Return true with 50% probability.
   */
  inline bool rndbool() const;

  /**
   * Return a true with probability \a p.
   */
  inline bool rndbool(double p) const;

  /**
   * Return a true with probability \a p1/(\a p1+\a p2).
   */
  inline bool rndbool(double p1, double p2) const;

  /**
   * Return -1, 0, or 1 with relative probabilities \a p1, \a p2, \a p3.
   */
  inline int rndsign(double p1, double p2, double p3) const;

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a p1).
   */
  inline int rnd2(double p0, double p1) const;

  /**
   * Return an integer \f$i\f$ with probability p\f$i\f$/(\a p0+\a
   * p1+\a p2).
   */
  inline int rnd3(double p0, double p1, double p2) const;

  /**
   * Return an integer/ \f$i\f$ with probability p\f$i\f$(\a p0+\a
   * p1+\a p2+\a p3).
   */
  inline int rnd4(double p0, double p1, double p2, double p3) const;

  /**
   * Return a simple flat random integrer number in the range [0,\a xu[.
   */
  inline long irnd(long xu = 2) const;

  /**
   * Return a simple flat random integrer number in the range [\a xl,\a xu[.
   */
  inline long irnd(long xl, long xu) const;

  /**
   * Return a reference to the object containing the standard model
   * parameters for this run.
   */
  inline const StandardModelBase & SM() const;

  /**
   * Return a pointer to the object containing the standard model
   * parameters for this run.
   */
  inline tSMPtr standardModel() const;

};

/**
 * HandlerBase is an abstract base class derived from the Interfaced
 * class via the HandlerBaseT class adding some functionality such as
 * easy acces to the RandomGenerator and the StandardModel object of
 * the controlling EventGenerator object.
 *
 * @see Interfaced
 * @see RandomGenerator
 * @see StandardModel
 * @see EventGenerator
 * 
 */
class HandlerBase: public HandlerBaseT<UseRandom> {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline HandlerBase();

  /**
   * Copy-constructor.
   */
  inline HandlerBase(const HandlerBase &);

  /**
   * Destructor.
   */
  virtual ~HandlerBase();
  //@}

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

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
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();

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
   * Describe an abstract class without persistent data.
   */
  static AbstractNoPIOClassDescription<HandlerBase> initHandlerBase;

  /**
   *  Private and non-existent assignment operator.
   */
  HandlerBase & operator=(const HandlerBase &);

};

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of HandlerBase.
 */
template <>
struct BaseClassTrait<HandlerBase,1>: public ClassTraitsType {
  /** Typedef of the base class of HandlerBase. Note that HandlerBaseT
   *  is not treated as a base class in this respect. */
  typedef Interfaced NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * HandlerBase class.
 */
template <>
struct ClassTraits<HandlerBase>: public ClassTraitsBase<HandlerBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::HandlerBase"; }
};

/** @endcond */

}

#include "HandlerBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "HandlerBase.tcc"
#endif

#endif /* ThePEG_HandlerBase_H */
