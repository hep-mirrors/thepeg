// -*- C++ -*-
//
// LesHouchesFileReader.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_LesHouchesFileReader_H
#define THEPEG_LesHouchesFileReader_H
// This is the declaration of the LesHouchesFileReader class.

#include "ThePEG/LesHouches/LesHouchesReader.h"
#include "LesHouchesFileReader.fh"
#include "ThePEG/Utilities/CFileLineReader.h"
#include <stdio.h>

namespace ThePEG {

/**
 * LesHouchesFileReader is an base class to be used for objects which
 * reads event files from matrix element generators. It inherits from
 * LesHouchesReader and extends it by defining a file handle to be
 * read from, which is opened and closed by the open() and close()
 * functions. Note that the file handle is a standard C filehandle and
 * not a C++ stream. This is because there is no standard way in C++
 * to connect a pipe to a stream for reading eg. gzipped files. This
 * class is able to read plain event files conforming to the Les
 * Houches Event File accord.
 *
 * @see \ref LesHouchesFileReaderInterfaces "The interfaces"
 * defined for LesHouchesFileReader.
 * @see Event
 * @see LesHouchesReader
 */
class LesHouchesFileReader: public LesHouchesReader {

public:

  /** @name Standard constructors and destructors. */
  //@{
  /**
   * Default constructor.
   */
  inline LesHouchesFileReader();

  /**
   * Copy-constructor. Note that a file which is opened in the object
   * copied from will have to be reopened in this.
   */
  inline LesHouchesFileReader(const LesHouchesFileReader &);

  /**
   * Destructor.
   */
  virtual ~LesHouchesFileReader();
  //@}

public:

  /** @name Virtual functions specified by the LesHouchesReader base class. */
  //@{
  /**
   * Initialize. This function is called by the LesHouchesEventHandler
   * to which this object is assigned.
   */
  virtual void initialize(LesHouchesEventHandler & eh);

  /**
   * Open a file with events. Derived classes should overwrite it and
   * first calling it before reading in the run information into the
   * corresponding protected variables.
   */
  virtual void open();

  /**
   * Close the file from which events have been read.
   */
  virtual void close();

  /**
   * Read the next event from the file or stream into the
   * corresponding protected variables. Return false if there is no
   * more events or if this was not a LHF event file.
   */
  virtual bool doReadEvent();
  //@}

  /**
   * Return the name of the file from where to read events.
   */
  inline string filename() const;

  /**
   * The file handle to read from.
   */
  inline FILE * file();

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

protected:

  /**
   * The wrapper around the C FILE stream from which to read
   */
  CFileLineReader cfile;

protected:

  /**
   * The number of events in this file.
   */
  long neve;

  /**
   * The current event number.
   */
  long ieve;

  /**
   * If the file is a standard Les Houches formatted file (LHF) this
   * is its version number. If empty, this is not a Les Houches
   * formatted file
   */
  string LHFVersion;

  /**
   * If LHF. All lines (since the last open() or readEvent()) outside
   * the header, init and event tags.
   */
  string outsideBlock;

  /**
   * If LHF. All lines from the header block.
   */
  string headerBlock;

  /**
   * If LHF. Additional comments found in the init block.
   */
  string initComments;

  /**
   * If LHF. Map of attributes (name-value pairs) found in the init
   * tag.
   */
  map<string,string> initAttributes;

  /**
   * If LHF. Additional comments found with the last read event.
   */
  string eventComments;

  /**
   * If LHF. Map of attributes (name-value pairs) found in the last
   * event tag.
   */
  map<string,string> eventAttributes;

private:

  /**
   * The file handle from which derived classes should read.
   */
  FILE * theFile;

  /**
   * The name of the file from where to read events.
   */
  string theFileName;

private:

  /**
   * Describe an abstract base class with persistent data.
   */
  static ClassDescription<LesHouchesFileReader> initLesHouchesFileReader;

  /**
   * Private and non-existent assignment operator.
   */
  LesHouchesFileReader & operator=(const LesHouchesFileReader &);

public:

  /** @cond EXCEPTIONCLASSES */
  /** Exception class used by LesHouchesFileReader if reading the file
   *  fails. */
  class LesHouchesFileError: public Exception {};
  /** @endcond */

};

}


#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

/** @cond TRAITSPECIALIZATIONS */

/**
 * This template specialization informs ThePEG about the
 * base class of LesHouchesFileReader.
 */
template <>
struct BaseClassTrait<LesHouchesFileReader,1>: public ClassTraitsType {
  /** Typedef of the base class of LesHouchesFileReader. */
  typedef LesHouchesReader NthBase;
};

/**
 * This template specialization informs ThePEG about the name of the
 * LesHouchesFileReader class and the shared object where it is
 * defined.
 */
template <>
struct ClassTraits<LesHouchesFileReader>
  : public ClassTraitsBase<LesHouchesFileReader> {
  /**
   * Return the class name.
   */
  static string className() { return "ThePEG::LesHouchesFileReader"; }
  /**
   * Return the name of the shared library to be loaded to get access
   * to the LesHouchesFileReader class and every other class it uses
   * (except the base class).
   */
  static string library() { return "LesHouches.so"; }

};

/** @endcond */

}

// #include "LesHouchesFileReader.tcc"
#include "LesHouchesFileReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#endif

#endif /* THEPEG_LesHouchesFileReader_H */
