// -*- C++ -*-
#ifndef THEPEG_MadGraphReader_H
#define THEPEG_MadGraphReader_H
//
// This is the declaration of the <!id>MadGraphReader<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>MadGraphReader<!!id> inherits from <!class>LesHouchesFileReader<!!class>
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:.html">.h</a>,
// <a href="http:.html">.h</a>.
// 

#include "ThePEG/LesHouches/LesHouchesFileReader.h"

namespace ThePEG {

class MadGraphReader: public LesHouchesFileReader {

public:

  inline MadGraphReader();
  inline MadGraphReader(const MadGraphReader &);
  virtual ~MadGraphReader();
  // Standard ctors and dtor.

public:

  virtual void open();
  // Open a file or stream with events and read in the run information
  // into the corresponding protected variables.

  virtual bool readEvent();
  // Read the next event form the file or stream into the
  // corresponding protected variables. Return false if there is no
  // more events.

  virtual void scan();
  // Scan the file or stream to obtain information about cross section
  // weights and particles etc.  

public:

  void persistentOutput(PersistentOStream &) const;
  void persistentInput(PersistentIStream &, int);
  // Standard functions for writing and reading from persistent streams.

  static void Init();
  // Standard Init function used to initialize the interfaces.

protected:

  inline virtual IBPtr clone() const;
  inline virtual IBPtr fullclone() const;
  // Standard clone methods.

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

private:

  static ClassDescription<MadGraphReader> initMadGraphReader;
  // Describe a concrete class with persistent data.

  MadGraphReader & operator=(const MadGraphReader &);
  // Private and non-existent assignment operator.

};

}

// CLASSDOC OFF

#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

// The following template specialization informs ThePEG about the
// base class of MadGraphReader.
template <>
struct BaseClassTrait<MadGraphReader,1> {
  typedef LesHouchesFileReader NthBase;
};

// The following template specialization informs ThePEG about the
// name of this class and the shared object where it is defined.
template <>
struct ClassTraits<MadGraphReader>
  : public ClassTraitsBase<MadGraphReader> {
  static string className() { return "ThePEG::MadGraphReader"; }
  // Return the class name.
  static string library() { return "MadGraphReader.so"; }
  // Return the name of the shared library to be loaded to get
  // access to this class and every other class it uses
  // (except the base class).
};

}

#include "MadGraphReader.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "MadGraphReader.tcc"
#endif

#endif /* THEPEG_MadGraphReader_H */
