// -*- C++ -*-
#ifndef THEPEG_LesHouchesFileReader_H
#define THEPEG_LesHouchesFileReader_H
//
// This is the declaration of the <!id>LesHouchesFileReader<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>LesHouchesFileReader<!!id> is an abstract base class to be
// used for objects which reads event files from matrix element
// generators. It inherits from <!class>LesHouchesReader<!!class> and
// extends it by defining a file handle to be read from, which is
// opened and closed by the <!id>open<!!id> and <!id>close<!!id>
// functions.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:LesHouchesReader.html">LesHouchesReader.h</a>.
// 

#include "ThePEG/LesHouches/LesHouchesReader.h"
#include "LesHouchesFileReader.fh"
#include <stdio.h>

namespace ThePEG {

class LesHouchesFileReader: public LesHouchesReader {

public:

  inline LesHouchesFileReader();
  inline LesHouchesFileReader(const LesHouchesFileReader &);
  virtual ~LesHouchesFileReader();
  // Standard ctors and dtor.

public:

  virtual void open();
  // Open a file with events. Derived classes should overwrite it and
  // first calling it before reading in the run information into the
  // corresponding protected variables.

  virtual void close();
  // Close the file from which events have been read.

  inline string filename() const;
  // Return the name of the file from where to read events.

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual void doupdate() throw(UpdateException);
  inline virtual void doinit() throw(InitException);
  inline virtual void doinitrun();
  inline virtual void dofinish();
  // Standard Interfaced virtual functions.

  inline virtual void rebind(const TranslationMap & trans)
    throw(RebindException);
  // Change all pointers to Interfaced objects to corresponding clones.

  inline virtual IVector getReferences();
  // Return pointers to all Interfaced objects refered to by this.

protected:

  FILE * theFile;
  // The file handle from which derived classes should read.

private:

  string theFileName;
  // The name of the file from where to read events.

  bool isGZipped;
  // If true the file is alsways assumed to be gzipped. Otherwise the
  // file will be assumed to be gzipped if the name ends with '.gz'

  bool isPipe;
  // Internal flag to decide how to close the file.

private:

  static AbstractClassDescription<LesHouchesFileReader> initLesHouchesFileReader;
  // Describe an abstract base class with persistent data.

  LesHouchesFileReader & operator=(const LesHouchesFileReader &);
  // Private and non-existent assignment operator.

public:

class LesHouchesFileError: public Exception {};

};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of LesHouchesFileReader.
template <>
struct BaseClassTrait<LesHouchesFileReader,1> {
  typedef LesHouchesReader NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<LesHouchesFileReader>
  : public ClassTraitsBase<LesHouchesFileReader> {
  static string className() { return "ThePEG::LesHouchesFileReader"; }
  // Return the class name.
  static string library() { return "libThePEGLesHouches.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "LesHouchesFileReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "LesHouchesFileReader.tcc"
#endif

#endif /* THEPEG_LesHouchesFileReader_H */
