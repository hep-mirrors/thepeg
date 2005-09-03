// -*- C++ -*-
#ifndef ThePEG_InterfacedBase_H
#define ThePEG_InterfacedBase_H
// This is the declaration of the InterfacedBase class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/HoldFlag.h"
// #include "InterfacedBase.fh"
#include "InterfacedBase.xh"

namespace ThePEG {

/**
 * InterfacedBase is the base class of all Interfaced objects to be
 * handled by the BaseRepository class. InterfacedBase
 * objects can be manipulated through objects of the InterfaceBase
 * class dealing with setting parameters, switches and pointers to
 * other InterfacedBase objects.
 *
 * The InterfacedBase has a number of virtual methods to be
 * implemented by sub classes for checking the state of the object,
 * initializing the object etc.
 *
 * The InterfacedBase is derived from the PersistentBase class to
 * allow for persistent I/O, and from the Named for handling the name
 * of the object. The full name of the object is of the form
 * <code>/dir/subdir/name</code> analogous to the file name in a Unix
 * file system.
 *
 * It is possible to lock an InterfacedBase object in which case the
 * BaseRepository will not do anything that will change the state of
 * this object.
 *
 * @see BaseRepository
 * @see InterfaceBase
 */
class InterfacedBase: public PersistentBase, public Named {

  /** THe BaseRepository is a close friend. */
  friend class BaseRepository;

  /**
   * Enumeration reflecting the state of an InterfacedBase object.
   */
  enum InitState {
    initializing = -1, /**< The object is currently being
			    initialized. I.e. either of update(),
			    init(), initrun() or finish() are being
			    run. */
    uninitialized = 0, /**< The object has not been initialized. */
    initialized = 1,   /**< The object has been initialized. */
    runready = 2       /**< The object is initialized and the
			    initrun() method has been called. */
  };

public:

  /**
   * The virtual (empty) destructor;
   */
  virtual ~InterfacedBase();

  /**
   * Returns the full name of this object including its path, e.g.
   * <code>/directory/subdirectory/name</code>.
   */
  inline string fullName() const;

  /**
   * Returns the name of this object, without the path.
   */
  inline string name() const;

  /**
   * Returns the path to this object including the trailing
   * '/'. <code>fullName() = path() + name()</code>.
   */
  inline string path() const;

  /**
   * Returns a comment assigned to this object.
   */
  inline string comment() const;

  /**
   * Read setup info from a standard istream \a is. May be called by
   * the Repository to initialize an object. This function first calls
   * the virtual readSetup() function to allow the sub classes the
   * part \a is to initialize themselves. What ever is left in \a is
   * after that will be assigned to the comment() of the object.
   */
  inline void setup(istream & is) throw(SetupException);

protected:

  /** @name Standard InterfacedBase virtual functions. */
  //@{
  /**
   * Read setup info from a standard istream \a is. May be called by
   * the Repository to initialize an object. This function is called
   * by the non virtual setup() function. A sub-class implementing it
   * should first call the base class version before parsing the \a
   * is. If the \a is is not empty after readSetup is called the
   * remaining string will be assigned to the comment() of the object.
   */
  virtual void readSetup(istream & is) throw(SetupException);

  /**
   * Check sanity of the object during the setup phase. This method
   * may be called by the user interface during the setup phase
   * through the update() method after manipulating objects to check
   * the sanity of the object. When implemented by a sub class it is
   * important that the doupdate() method of the base class is called,
   * then if the sanity of this object depend on other objects, the
   * update() method of these should be called. Then if touched() is
   * true for this object or for the ones on which this depends, it is
   * an indication that some things have changed since last time
   * doupdate() was called, and the actual checking of the state of
   * this object is called for. To avoid circular loops, it is
   * important that the doupdate() method is called for the base
   * class, while the update() method is called for other objects.
   * @throws UpdateException if the setup is such that the object
   * would not work properly.
   */
  virtual void doupdate() throw(UpdateException) = 0;

  /**
   * Initialize this object. This method is called after the setup
   * phase through the init() method to indicate that the setup of a
   * run is finished. This is typpically done in a setup program
   * before this object has been saved to a run file. It must
   * therefore be made sure that the state of this object after this
   * method has been executed will not be changed if it is written to
   * a file and read in again. When implemented by a sub class it is
   * important that the doinit() method of the base class is called
   * first and then, if the initialization of this object depends on
   * other objects, that the init() method of these objects are
   * called. Only then should the class-local initialization
   * proceed. To avoid circular loops, it is important that the
   * doinit() method is called for the base class, while the init()
   * method is called for other objects.
   * @throws InitException if object could not be initialized properly.
   */
  virtual void doinit() throw (InitException) = 0;

  /**
   * Initialize this object. This method is called juast before
   * running starts through the initrun() method to indicate that the
   * actual running is to start. When implemented by a sub class it is
   * important that the doinitrun() method of the base class is called
   * first and then, if the initialization of this object depends on
   * other objects, that the initrun() method of these objects are
   * called. Only then should the class-local initialization
   * proceed. To avoid circular loops, it is important that the
   * doinitrun() method is called for the base class, while the
   * initrun() method is called for other objects.
   */
  virtual void doinitrun();

  /**
   * Finalize this object. This method is called after the running
   * phase through the finish() and can eg. be used to write out
   * statistics. When implemented by a sub class it is important that
   * the dofinish() method of the base class is called while the
   * finish() methd is called for other objects.
   */
  virtual void dofinish() = 0;

  /**
   * Return a vector of all pointers to Interfaced objects used in this
   * object.
   * @return a vector of pointers.
   */
  inline virtual IVector getReferences();

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
  //@}

public:

  /** @name Inlined access function. */
  //@{
  /**
   * Calls the doupdate() function with recursion prevention.
   */
  inline void update() throw(UpdateException);

  /**
   * Calls the doinit() function with recursion prevention.
   */
  inline void init() throw (InitException);

  /**
   * Calls the doinitrun() function with recursion prevention.
   */
  inline void initrun();

  /**
   * Calls the dofinish() function with recursion prevention.
   */
  inline void finish();

  /**
   * This function should be called every time something in this
   * object has changed in a way that a sanity check with update() is
   * needed
   */
  inline void touch();

  /**
   * Set the state of this object to uninitialized.
   */
  inline void reset();

  /**
   * Calls reset() and unTouch().
   */
  inline void clear();

  /**
   * Return true if the BaseRepository is not allowed to change the
   * state of this object.
   */
  inline bool locked() const;

  /**
   * Return true if the state of this object has been changed since
   * the last call to update().
   */
  inline bool touched() const;
  //@}

  /**
   * Return a full clone of this object possibly doing things to the
   * clone to make it sane.
   */
  inline virtual IBPtr fullclone() const;

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
   * Standard Init function.
   */
  static void Init();

protected:

  /**
   * Return a simple clone of this object. Should be implemented as
   * <code>return new_ptr(*this);</code> by a derived class.
   */
  virtual IBPtr clone() const = 0;

  /**
   * Protected default constructor.
   */
  inline InterfacedBase();

  /**
   * Protected constructor with the name given as argument.
   */
  inline InterfacedBase(string newName);

  /**
   * Protected copy-constructor.
   */
  inline InterfacedBase(const InterfacedBase &);

private:

  /**
   * Set a new name (full name including path).
   */
  inline void name(string newName);

  /**
   * Lock this object.
   */
  inline void lock();

  /**
   * Unlock this object.
   */
  inline void unlock();

  /**
   * Clear the isTouched flag.
   */
  inline void untouch();

private:

  /**
   * Used by the interface to add comments.
   */
  string addComment(string);

private:

  /**
   * True if this object is not to be changed by the user interface.
   */
  bool isLocked;

  /**
   * True if this object has been chaged since the last call to
   * update().
   */
  bool isTouched;

  /**
   * Indicate if this object has been initialized or not, or if it is
   * being initialized.
   */
  InitState initState;

  /**
   * A comment assigned to this object.
   */
  string theComment;

private:

  /**
   * Standard Initialization object.
   */
  static AbstractClassDescription<InterfacedBase> initInterfacedBase;

  /**
   *  Private and non-existent assignment operator.
   */
  InterfacedBase & operator=(const InterfacedBase &);

protected:

  /**
   * Functor class to be used to update a range of dependent object.
   */
  struct UpdateChecker {
    /** Constructor. */
    UpdateChecker(bool & touched) : isTouched(touched) {}
    /** Constructor. */
    UpdateChecker(const UpdateChecker & uc) : isTouched(uc.isTouched) {}
    /** Call the check function for an object. */
    static void check(tIBPtr, bool &);
    /** Function call operator. */
    template <typename ptr> void operator()(const ptr & i) {
      check(i, isTouched);
    }
    /** set to false if any check() call fails. */
    bool & isTouched;
  };

  /**
   * Functor class to be used to update a range of dependent object in a map.
   */
  struct UpdateMapChecker {
    /** Constructor. */
    UpdateMapChecker(bool & touched) : isTouched(touched) {}
    /** Constructor. */
    UpdateMapChecker(const UpdateMapChecker & uc) : isTouched(uc.isTouched) {}
    /** Function call operator. */
    template <typename ref> void operator()(const ref & i) {
      UpdateChecker::check(i.second, isTouched);
    }
    /** Reference to the bool variable to be set. */
    bool & isTouched;
  };

};

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of InterfacedBase.
 */
template <>
struct BaseClassTrait<InterfacedBase,1>: public ClassTraitsType {
  /** Typedef of the base class of InterfacedBase. */
  typedef PersistentBase NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * InterfacedBase class.
 */
template <>
struct ClassTraits<InterfacedBase>: public ClassTraitsBase<InterfacedBase> {
  /** Return the class name. */
  static string className() { return "ThePEG::InterfacedBase"; }
};

/** @endcond */

}

#include "InterfacedBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InterfacedBase.tcc"
#endif

#endif /* ThePEG_InterfacedBase_H */
