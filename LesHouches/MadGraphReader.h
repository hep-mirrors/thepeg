// -*- C++ -*-
#ifndef THEPEG_MadGraphReader_H
#define THEPEG_MadGraphReader_H
// This is the declaration of the MadGraphReader class.

#include "ThePEG/LesHouches/LesHouchesFileReader.h"

namespace ThePEG {

/**
 * MadGraphReader inherits from LesHouchesFileReader
 */
class MadGraphReader: public LesHouchesFileReader {

public:

   /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline MadGraphReader();

  /**
   * Copy-constructor.
   */
  inline MadGraphReader(const MadGraphReader &);

  /**
   * Destructor.
   */
  virtual ~MadGraphReader();
  //@}

public:

  /** @name Virtual functions specified by the LesHouchesReader base class. */
  //@{
  /**
   * Open a file or stream with events and read in the run information
   * into the corresponding protected variables.
   */
  virtual void open();

  /**
   * Read the next event form the file or stream into the
   * corresponding protected variables. Return false if there is no
   * more events.
   */
  virtual bool readEvent();

  /**
   * Scan the file or stream to obtain information about cross section
   * weights and particles etc.  
   */
  virtual void scan();
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
  static ClassDescription<MadGraphReader> initMadGraphReader;

  /**
   * Private and non-existent assignment operator.
   */
  MadGraphReader & operator=(const MadGraphReader &);

};

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/**
 * This template specialization informs ThePEG about the
 * base class of MadGraphReader.
 */
template <>
struct BaseClassTrait<MadGraphReader,1> {
  /** Typedef of the base class of MadGraphReader. */
  typedef LesHouchesFileReader NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * MadGraphReader class and the shared object where it is
 * defined.
 */
template <>
struct ClassTraits<MadGraphReader>
  : public ClassTraitsBase<MadGraphReader> {
  /** Return the class name. */
  static string className() { return "ThePEG::MadGraphReader"; }
  /** Return the name of the shared library to be loaded to get
   * access to the MadGraphReader class and every other class it uses
   * (except the base class). */
  static string library() { return "MadGraphReader.so"; }

};

}

#include "MadGraphReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MadGraphReader.tcc"
#endif

#endif /* THEPEG_MadGraphReader_H */
