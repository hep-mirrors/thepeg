// -*- C++ -*-
#ifndef ThePEG_InterfacedBase_H
#define ThePEG_InterfacedBase_H
//
// This is the declaration of the <!id>InterfacedBase<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>InterfacedBase<!!id> is the base class of all interfaced
// objects to be handled by the <!class>BaseRepository<!!class>
// class. <!id>InterfacedBase<!!id> objects can be manipulated through
// objects of the <!class>InterfaceBase<!!class> class dealing with
// setting parameters, switches and pointers to other
// <!id>InterfacedBase<!!id> objects.
//
// The <!id>InterfacedBase<!!id> has a number of virtual methods to be
// implemented by sub classes for checking the state of the object,
// initializing the object etc.
//
// The <!id>InterfacedBase<!!id> is derived from the
// <!id>PersistentBase<!!id> class to allow for persistent I/O, and
// from the <!class>Named<!!class> for handling the name of the
// object. The full name of the object is of the form
// <!id>/dir/subdir/name<!!id> analogous to the file name in a Unix
// file system.
//
// It is possible to lock an <!id>InterfacedBase<!!id> object in which
// case the BaseRepository will not do anything that will change the
// state of this object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:BaseRepository.html">BaseRepository.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/HoldFlag.h"
// #include "InterfacedBase.fh"
#include "InterfacedBase.xh"

namespace ThePEG {

class InterfacedBase: public PersistentBase, public Named {

  friend class BaseRepository;

  enum InitState { initializing = -1, uninitialized = 0,
		   initialized = 1, runready = 2 };

public:

  virtual ~InterfacedBase();
  // The virtual (empty) destructor;

  inline string fullName() const;
  // Returns the full name of this object including its path, e.g.
  // '/directory/subdirectory/name'

  inline string name() const;
  // Returns the name of this object, without the path

  inline string path() const;
  // Returns the path to this object includingthe trailing
  // '/'. fullName() = path() + name().

protected:

  virtual void readSetup(istream & is) throw(SetupException);
  // Read setup info from a standard stream.

  virtual void doupdate() throw(UpdateException) = 0;
  // This method may be called by the user interface during the setup
  // phase through the update() method after manipulating objects to
  // check the sanity of the object. When implemented by a sub class
  // it is important that the doupdate() method of the base class is
  // called, then if the sanity of this object depend on other
  // objects, the update() method of these should be called. Then if
  // touched() is true for this object or for the ones on which this
  // depends, it is an indication that some things have changed since
  // last time doupdate() was called, and the actual checking of the
  // state of this object is called for. To avoid circular loops, it
  // is important that the doupdate() method is called for the base
  // class, while the update() method is called for other objects.

  virtual void doinit() throw (InitException) = 0;
  // This method is called after the setup phase through the init()
  // method to indicate that the setup of a run is finished. This is
  // typpically done in a setup program before this object has been
  // saved to a run file. It must therefore be made sure that the
  // state of this object after this method has been executed will not
  // be changed if it is written to a file and read in again. When
  // implemented by a sub class it is important that the doinit()
  // method of the base class is called first and then, if the
  // initialization of this object depends on other objects, that the
  // init() method of these objects are called. Only then should the
  // class-local initialization proceed. To avoid circular loops, it
  // is important that the doinit() method is called for the base
  // class, while the init() method is called for other objects.

  virtual void doinitrun();
  // This method is called juast before running starts through the
  // initrun() method to indicate that the actual running is to
  // start. When implemented by a sub class it is important that the
  // doinitrun() method of the base class is called first and then, if
  // the initialization of this object depends on other objects, that
  // the initrun() method of these objects are called. Only then should
  // the class-local initialization proceed. To avoid circular loops,
  // it is important that the doinitrun() method is called for the base
  // class, while the initrun() method is called for other objects.

  virtual void dofinish() = 0;
  // This method is called after the running phase through the
  // finish() and can eg. be used to write out statistics. When
  // implemented by a sub class it is important that the dofinish()
  // method of the base class is called.

public:

  inline void update() throw(UpdateException);
  // Calls the 'doupdate' function with recursion prevention.

  inline void init() throw (InitException);
  // Calls the 'doinit' function with recursion prevention.

  inline void initrun();
  // Calls the 'doinitrun' function with recursion prevention.

  inline void finish();
  // Calls the 'dofinish' function with recursion prevention.

  inline void touch();
  // This function should be called every time something in this
  // object has changed in a way that a sanity check with 'update' is
  // needed

  inline void reset();
  // Set the state of this object to uninitialized.

  inline void clear();
  // reset() and unTouch().

  inline virtual IVector getReferences();
  // Returns a vector of pointers to objects which are refered to in
  // this object.

  inline virtual IBPtr fullclone() const;
  // Return a full clone of this object possibly doing things to the
  // clone to make it sane.

  inline bool locked() const;
  // Return true if the BaseRepository is not allowed to change the
  // state of this object.

  inline bool touched() const;
  // Return true if the state of this object has been changed since
  // the last call to update().

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interface.

protected:

  virtual IBPtr clone() const = 0;
  // Return a simple clone of this object. Should be implemented as
  // <!id>return new_ptr(*this);<!!id> by a derived class.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Replace all objects referenced in this object with a cloned one
  // according to the translation map. Note that this is not necessary
  // for objects which are registered via a 'Reference' or a
  // 'ReferenceVector'

  inline InterfacedBase();
  inline InterfacedBase(string newName);
  inline InterfacedBase(const InterfacedBase &);
  // Protected constructors.

private:

  inline void name(string newName);
  // Set a new name (full name including path).

  inline void lock();
  inline void unlock();
  // Loc/unlock this object.

  inline void untouch();
  // Clear the isTouched flag.

private:

  bool isLocked;
  // True if this object is not to be changed by the user interface..

  bool isTouched;
  // True if this object has been chaged since the last call to
  // update().

  InitState initState;
  // Indicate if this object has been initialized or not, or if it is
  // being initialized.

private:

  static AbstractClassDescription<InterfacedBase> initInterfacedBase;
  // Standard Initialization object.

  InterfacedBase & operator=(const InterfacedBase &);
  //  Private and non-existent assignment operator.

protected:

  // Functor class to be used to update a range of dependent object.
  struct UpdateChecker {
    UpdateChecker(bool & touched) : isTouched(touched) {}
    UpdateChecker(const UpdateChecker & uc) : isTouched(uc.isTouched) {}
    static void check(tIBPtr, bool &);
    template <typename ptr> void operator()(const ptr & i) {
      check(i, isTouched);
    }
    bool & isTouched;
  };

  // Functor class to be used to update a range of dependent object in a map..
  struct UpdateMapChecker {
    UpdateMapChecker(bool & touched) : isTouched(touched) {}
    UpdateMapChecker(const UpdateMapChecker & uc) : isTouched(uc.isTouched) {}
    template <typename ref> void operator()(const ref & i) {
      UpdateChecker::check(i.second, isTouched);
    }
    bool & isTouched;
  };

};

template <>
struct BaseClassTrait<InterfacedBase,1> {
  typedef PersistentBase NthBase;
};

template <>
struct ClassTraits<InterfacedBase>: public ClassTraitsBase<InterfacedBase> {
  static string className() { return "/ThePEG/InterfacedBase"; }
};

}

#include "InterfacedBase.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InterfacedBase.tcc"
#endif

#endif /* ThePEG_InterfacedBase_H */
