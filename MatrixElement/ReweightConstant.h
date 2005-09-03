// -*- C++ -*-
#ifndef THEPEG_ReweightConstant_H
#define THEPEG_ReweightConstant_H
//
// This is the declaration of the ReweightConstant class.
//

#include "ThePEG/MatrixElement/ReweightBase.h"

namespace ThePEG {

/**
 * The ReweightConstant class is a simple ReweightBase sub-class which
 * simply reweight an event with a constant.
 *
 * @see \ref ReweightConstantInterfaces "The interfaces"
 * defined for ReweightConstant.
 */
class ReweightConstant: public ReweightBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * The default constructor.
   */
  inline ReweightConstant();

  /**
   * The copy constructor.
   */
  inline ReweightConstant(const ReweightConstant &);

  /**
   * The destructor.
   */
  virtual ~ReweightConstant();
  //@}

public:

  /**
   * Return the wieght for the kinematical configuation
   * previously provided by the last call to setKinematics().
   */
  virtual double weight() const;

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
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /**
   * The constant to reweight with.
   */
  double C;

private:

  /**
   * The static object used to initialize the description of this class.
   * Indicates that this is a concrete class with persistent data.
   */
  static ClassDescription<ReweightConstant> initReweightConstant;

  /**
   * The assignment operator is private and must never be called.
   * In fact, it should not even be implemented.
   */
  ReweightConstant & operator=(const ReweightConstant &);

};

}

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/** This template specialization informs ThePEG about the
 *  base classes of ReweightConstant. */
template <>
struct BaseClassTrait<ReweightConstant,1> {
  /** Typedef of the first base class of ReweightConstant. */
  typedef ReweightBase NthBase;
};

/** This template specialization informs ThePEG about the name of
 *  the ReweightConstant class and the shared object where it is defined. */
template <>
struct ClassTraits<ReweightConstant>
  : public ClassTraitsBase<ReweightConstant> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::ReweightConstant"; }
  /** Return the name of the shared library be loaded to get
   *  access to the ReweightConstant class and every other class it uses
   *  (except the base class). */
  static string library() { return "ReweightConstant.so"; }
};

/** @endcond */

}

#include "ReweightConstant.icc"

#endif /* THEPEG_ReweightConstant_H */
