// -*- C++ -*-
#ifndef ThePEG_O1AlphaS_H
#define ThePEG_O1AlphaS_H
// This is the declaration of the O1AlphaS class.

#include "AlphaSBase.h"
// #include "O1AlphaS.fh"
// #include "O1AlphaS.xh"

namespace ThePEG {

/**
 * O1AlphaS inherits from AlphaSBase and implements the leading order
 * running QCD coupling.
 *
 *
 * @see AlphaSBase.
 * 
 */
class O1AlphaS: public AlphaSBase {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline O1AlphaS();

  /**
   * Copy-constructor.
   */
  inline O1AlphaS(const O1AlphaS &);

  /**
   * Destructor.
   */
  virtual ~O1AlphaS();
  //@}

public:

  /** @name Virtual functions mandated by the sub-class. */
  //@{
  /**
   * The \f$\alpha_S\f$. Return the QCD coupling for a given \a scale
   * using the given standard model object \a sm.
   */
  virtual double value(Energy2 scale, const StandardModelBase &) const;

  /**
   * Return the flavour thresholds used. The returned vector contains
   * (in position <code>i</code>) the scales when the active number of
   * flavours changes from <code>i</code> to <code>i+1</code>.
   */
  virtual vector<Energy2> flavourThresholds() const;

  /**
   * Return the \f$\Lambda_{QCD}\f$ used for different numbers of
   * active flavours.
   */
  virtual vector<Energy> LambdaQCDs() const;
  //@}

  /**
   * Return the maximum number of active flavours.
   */
  inline unsigned int getMaxFlav() const;

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

protected:


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
   * The \f$\Lambda_{QCD}\f$ for the number of flavours specified by
   * theLambdaFlavour. Other \f$\Lambda_{QCD}\f$ values for other
   * numbers of active flavours are calculated from
   * flavourThresholds() using a continuity requirement.
   */
  Energy theLambdaQCD;

  /**
   * The number of flavours for which theLambdaQCD is given..
   */
  unsigned int theLambdaFlavour;

  /**
   * The maximum number of active flavours.
   */
  unsigned int theMaxFlav;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<O1AlphaS> initO1AlphaS;

  /**
   *  Private and non-existent assignment operator.
   */
  O1AlphaS & operator=(const O1AlphaS &);

};

/** This template specialization informs ThePEG about the base classes
 *  of O1AlphaS. */
template <>
struct BaseClassTrait<O1AlphaS,1>: public ClassTraitsType {
  /** Typedef of the first base class of O1AlphaS. */
  typedef AlphaSBase NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  O1AlphaS class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<O1AlphaS>: public ClassTraitsBase<O1AlphaS> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::O1AlphaS"; }
  /** Return the name of the shared library be loaded to get access to
   *  the O1AlphaS class and every other class it uses
   *  (except the base class). */
  static string library() { return "O1AlphaS.so"; }
};

}

#include "O1AlphaS.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "O1AlphaS.tcc"
#endif

#endif /* ThePEG_O1AlphaS_H */
