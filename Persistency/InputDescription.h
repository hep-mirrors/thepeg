// -*- C++ -*-
#ifndef ThePEG_InputDescription_H
#define ThePEG_InputDescription_H
//
// This is the declaration of the <!id>InputDescription<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>InputDescription<!!id> objects are used by the
// <!class>PersistentIStream<!!class> class to keep track of all
// classes it has read from a stream. It keeps a pointer to the
// corresponding <!class>ClassDescription<!!class> in case the class
// read in was actually present in the current program, a version
// number of the read class which may be different from the class
// present in hte current program and a list of base class
// <!id>InputDescription<!!id>s.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>,
// <a href="http:Named.html">Named.h</a>,
// <a href="http:ClassDescription.html">ClassDescription.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
// #include "InputDescription.fh"
// #include "InputDescription.xh"
#include "ThePEG/Utilities/ClassDescription.h"

namespace ThePEG {

class InputDescription: public Named {

public:

  typedef vector<const InputDescription *> DescriptionVector;
  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);

public:

  inline InputDescription(string newName, int version);
  // The standard constructor.

  inline void setDescription(const ClassDescriptionBase *);

  inline void addBaseClass(const InputDescription *);
  // Add a base class description.

  inline const DescriptionVector & descriptions() const;
  // Return the list of base class descriptions.

  inline BPtr create() const;
  // Create an object of the corresponing class.

  inline void input(tBPtr b, PersistentIStream & is) const;
  // Read an object part of the corresponding class from a stream.

private:

  DescriptionVector theBaseClasses;
  // The list of base class descriptions.

  const ClassDescriptionBase * theDescription;
  // The description of the corresponding class in the current
  // program.

  int theVersion;
  // The version of the class to be read.

};

}

#include "InputDescription.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InputDescription.tcc"
#endif

#endif /* ThePEG_InputDescription_H */
