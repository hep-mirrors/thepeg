// -*- C++ -*-
#ifndef THEPEG_SimpleZGenerator_H
#define THEPEG_SimpleZGenerator_H
// This is the declaration of the SimpleZGenerator class.

#include "ThePEG/Handlers/ZGenerator.h"

namespace ThePEG {

/**
 * SimpleZGenerator is a very simple concrete subclass of
 * ZGenerator. It implements a naive unphysical model to generate the
 * momentum fraction (Z) taken by hadrons produced in a hadronization
 * scenario. It should only be used for testing purposes.
 */
class SimpleZGenerator: public ZGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline SimpleZGenerator();

  /**
   * Copy-constructor.
   */
  inline SimpleZGenerator(const SimpleZGenerator &);

  /**
   * Destructor.
   */
  virtual ~SimpleZGenerator();
  //@}

public:

  /** @name Virtual functions mandated by the ZGenerator base class. */
  //@{
  /**
   * Return the momentum fraction. Assume that an initial
   * (anti-)(di-)quark \a q1 produces a hadron and leaves behind
   * another (anti-)(di-)quark \a q2. The hadron is assumed to have a
   * squared transverse mass, \a mT2, w.r.t. the initial quark
   * direction.
   * @return the energy fraction distributed as \f$\sqrt{z}\f$ (or
   * \f$1-\sqrt{z}\f$) if \a q1 (or \a q2) is a diquark. Otherwise a
   * flat distribution is used.
   */
  virtual double generate(cPDPtr q1, cPDPtr q2, Energy2 mT2 ) const;
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
   * Standard Init function used to initialize the interfaces.
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
   * Initialize this object after the setup phase before saving and
   * EventGenerator to disk.
   * @throws InitException if object could not be initialized properly.
   */
  inline virtual void doinit() throw(InitException);

  /**
   * Initialize this object. Called in the run phase just before
   * a run begins.
   */
  inline virtual void doinitrun();

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
   * Return a vector of all pointers to Interfaced objects used in
   * this object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<SimpleZGenerator> initSimpleZGenerator;

  /**
   * Private and non-existent assignment operator.
   */
  SimpleZGenerator & operator=(const SimpleZGenerator &);

};

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/**
 * This template specialization informs ThePEG about the base class of
 * SimpleZGenerator.
 */
template <>
struct BaseClassTrait<SimpleZGenerator,1>: public ClassTraitsType {
  /** Typedef of the base class of SimpleZGenerator. */
  typedef ZGenerator NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * SimpleZGenerator class and the shared object where it is defined.
 */
template <>
struct ClassTraits<SimpleZGenerator>
  : public ClassTraitsBase<SimpleZGenerator> {
  /** Return the class name.  */
  static string className() { return "ThePEG::SimpleZGenerator"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the SimpleZGenerator class and every other class it uses
   * (except the base class).
   */
  static string library() { return "SimpleZGenerator.so"; }

};

}

#include "SimpleZGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleZGenerator.tcc"
#endif

#endif /* THEPEG_SimpleZGenerator_H */
