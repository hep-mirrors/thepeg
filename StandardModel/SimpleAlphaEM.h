// -*- C++ -*-
#ifndef ThePEG_SimpleAlphaEM_H
#define ThePEG_SimpleAlphaEM_H
// This is the declaration of the SimpleAlphaEM class.

#include "AlphaEMBase.h"
// #include "SimpleAlphaEM.fh"
// #include "SimpleAlphaEM.xh"

namespace ThePEG {

/**
 * SimpleAlphaEM inherits from AlphaEMBase and implements a simple
 * running of the electromagnetic coupling as parameterized by
 * H.~Buckhardt et al.
 *
 *
 * @see AlphaEMBase.
 * 
 */
class SimpleAlphaEM: public AlphaEMBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline SimpleAlphaEM();

  /**
   * Copy-constructor.
   */
  inline SimpleAlphaEM(const SimpleAlphaEM &);

  /**
   * Destructor.
   */
  virtual ~SimpleAlphaEM();
  //@}

public:

  /**
   * The \f$\alpha_{EM}\f$. Return the value of the coupling at a
   * given \a scale using the given standard model object, \a sm.
   */
virtual double value(Energy2 scale, const StandardModelBase &) const;

public:

  /**
   * Standard Init function used to initialize the interface.
   */
  static void Init();

protected:

  /** @name Clone Methods. */
  //@{
  /**
   * Make a simple clone of this object.
   * @return a pointer to the new object.
   */
  virtual IBPtr clone() const;

  /** Make a clone of this object, possibly modifying the cloned object
   * to make it sane.
   * @return a pointer to the new object.
   */
  virtual IBPtr fullclone() const;
  //@}

  /** @name Standard Interfaced functions. */
  //@{
  /**
   * Check sanity of the object during the setup phase.
   */
  inline virtual void doupdate() throw(UpdateException);

  /**
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Finalize this object. Called in the run phase just after a
   * run has ended. Used eg. to write out statistics.
   */
  inline virtual void dofinish();
  //@}

private:

  /**
   * Describe a concrete class without persistent data.
   */
  static NoPIOClassDescription<SimpleAlphaEM> initSimpleAlphaEM;

  /**
   *  Private and non-existent assignment operator.
   */
  SimpleAlphaEM & operator=(const SimpleAlphaEM &);

};

/** This template specialization informs ThePEG about the base classes
 *  of SimpleAlphaEM. */
template <>
struct BaseClassTrait<SimpleAlphaEM,1>: public ClassTraitsType {
  /** Typedef of the first base class of SimpleAlphaEM. */
  typedef AlphaEMBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  SimpleAlphaEM class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<SimpleAlphaEM>: public ClassTraitsBase<SimpleAlphaEM> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::SimpleAlphaEM"; }
  /** Return the name of the shared library be loaded to get access to
   *  the SimpleAlphaEM class and every other class it uses
   *  (except the base class). */
  static string library() { return "SimpleAlphaEM.so"; }
};

}

#include "SimpleAlphaEM.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleAlphaEM.tcc"
#endif

#endif /* ThePEG_SimpleAlphaEM_H */
