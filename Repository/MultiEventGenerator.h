// -*- C++ -*-
#ifndef ThePEG_MultiEventGenerator_H
#define ThePEG_MultiEventGenerator_H
// This is the declaration of the MultiEventGenerator class.

#include "FullEventGenerator.h"
// #include "MultiEventGenerator.fh"
// #include "MultiEventGenerator.xh"

namespace ThePEG {

/**
 * The MultiEventGenerator class is derived from the
 * FullEventGenerator class and is capable of making several runs with
 * a pre-defined set of parameter and switch values.
 *
 * With the Command<MultiEventGenerator> interface AddInterface set of
 * parameters for an included object can be specified as eg.
 * <code>object:interface arg1, arg2, arg3 ...</code>. The event
 * generator will then be run once with the specified objects
 * interface set to <code>arg1</code>, then once with
 * <code>arg2</code> etc. If several AddInterface commands are given
 * the event generator will be run once for each possible combination
 * arguments to object interfaces.
 *
 * @see FullEventGenerator.
 * 
 */
class MultiEventGenerator: public FullEventGenerator {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MultiEventGenerator();

  /**
   * Copy-constructor.
   */
  inline MultiEventGenerator(const MultiEventGenerator &);

  /**
   * Destructor.
   */
  virtual ~MultiEventGenerator();
  //@}

protected:

  /** @name Public virtual functions required by the base class. */
  //@{
  /**
   * Run this EventGenerator session. Is called from
   * EventGenerator::go(long,long).
   */
  virtual void doGo(long next, long maxevent);
  //@}

  /** @name Functions used by the Command<MultiEventGenerator>
      interfaces to set up the different parameters of the runs. */
  //@{
  /**
   * Used to add an interface of an object which should be used with a
   * set of different values. The argument should be given as
   * "object:interface arg1, arg2, ..."
   */
  string addInterface(string);

  /**
   * Used to remove an interface of an object which should be used
   * with a set of different values. The argument should be given as
   * "object:interface arg1, arg2, ..."
   */
  string removeInterface(string);
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
   * @throws RebindException if no cloned object was found for a given
   * pointer.
   */
  virtual void rebind(const TranslationMap & trans) throw(RebindException);

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();
  //@}

private:

  /** A vector of character strings. */
  typedef vector<string> StringVector;

  /**
   * The objects for which there are different interface settings.
   */
  IVector theObjects;

  /**
   * The interfaces to be modified for the corresponding objects in
   * theObjects.
   */
  StringVector theInterfaces;

  /**
   * If the there are positional arguments to theInterfaces these are
   * specified here.
   */
  StringVector thePosArgs;

  /**
   * The arguments to be used for each of theInterfaces.
   */
  vector<StringVector> theValues;

private:

  /**
   * Describe a concrete class with persistent data.
   */
  static ClassDescription<MultiEventGenerator> initMultiEventGenerator;

  /**
   *  Private and non-existent assignment operator.
   */
  MultiEventGenerator & operator=(const MultiEventGenerator &);

};


/** This template specialization informs ThePEG about the base classes
 *  of MultiEventGenerator. */
template <>
struct BaseClassTrait<MultiEventGenerator,1> {
  /** Typedef of the first base class of MultiEventGenerator. */
  typedef FullEventGenerator NthBase;
};

/** This template specialization informs ThePEG about the name of the
 *  MultiEventGenerator class and the shared object where it is
 *  defined. */
template <>
struct ClassTraits<MultiEventGenerator>:
    public ClassTraitsBase<MultiEventGenerator> {
  /** Return a platform-independent class name */
  static string className() { return "ThePEG::MultiEventGenerator"; }
  /** Return the name of the shared library be loaded to get access to
   *  the MultiEventGenerator class and every other class it uses
   *  (except the base class). */
  static string library() { return "MultiEventGenerator.so"; }

};

}

#include "MultiEventGenerator.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MultiEventGenerator.tcc"
#endif

#endif /* ThePEG_MultiEventGenerator_H */
