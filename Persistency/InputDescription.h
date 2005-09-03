// -*- C++ -*-
#ifndef ThePEG_InputDescription_H
#define ThePEG_InputDescription_H
// This is the declaration of the InputDescription class.

#include "ThePEG/Config/ThePEG.h"
// #include "InputDescription.fh"
// #include "InputDescription.xh"
#include "ThePEG/Utilities/ClassDescription.h"

namespace ThePEG {

/** @ingroup Persistency
 * InputDescription objects are used by the PersistentIStream class to
 * keep track of all classes it has read from a stream. It keeps a
 * pointer to the corresponding ClassDescription in case the class
 * read in was actually present in the current program, a version
 * number of the read class which may be different from the class
 * present in the current program and a list of base class
 * <code>InputDescription</code>s.
 *
 * @see PersistentIStream
 * @see Named
 * @see ClassDescription
 */
class InputDescription: public Named {

public:

  /** A vector of pointers to InputDescription objects. */
  typedef vector<const InputDescription *> DescriptionVector;

  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);

public:

  /**
   * The standard constructor.
   * @param newName the name of the class being read.
   * @param version the version number of the class when written.
   */
  inline InputDescription(string newName, int version);

  /**
   * Set the ClassDescriptionBase object of the class being read.
   */
  inline void setDescription(const ClassDescriptionBase *);

  /**
   * Add a base class description.
   */
  inline void addBaseClass(const InputDescription *);

  /**
   * Return the list of base class descriptions.
   */
  inline const DescriptionVector & descriptions() const;

  /**
   * Create an object of the corresponding class.
   */
  inline BPtr create() const;

  /**
   * Read an object part of the corresponding class from a stream.
   * Will only read the part of the object corresponding to the
   * members of the class represented by this object.
   */
  inline void input(tBPtr b, PersistentIStream & is) const;

private:

  /**
   * The list of base class descriptions.
   */
  DescriptionVector theBaseClasses;

  /**
   * The description of the corresponding class in the current
   * program.
   */
  const ClassDescriptionBase * theDescription;

  /**
   * The version of the class to be read.
   */
  int theVersion;

};

}

#include "InputDescription.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "InputDescription.tcc"
#endif

#endif /* ThePEG_InputDescription_H */
