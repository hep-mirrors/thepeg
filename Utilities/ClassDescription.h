// -*- C++ -*-
#ifndef ThePEG_ClassDescription_H
#define ThePEG_ClassDescription_H
//
// This is the declaration of the <!id>ClassDescriptionBase<!!id>,
// <!id>ClassDescriptionTBase<!!id>, <!id>ClassDescription<!!id>,
// <!id>AbstractClassDescription<!!id>,
// <!id>NoPIOClassDescription<!!id> and
// <!id>AbstractNoPIOClassDescription<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ClassDescriptionBase<!!id> is the non-templated base class for
// the templated <!id>ClassDescriptionTBase<!!id>,
// <!id>ClassDescription<!!id>, <!id>AbstractClassDescription<!!id>,
// <!id>NoPIOClassDescription<!!id> and
// <!id>AbstractNoPIOClassDescription<!!id> classes. An instantiation
// of one of these classes represents a meta class encapsulating
// information about the template argument class. This information is
// obtained from the templated <!class>ClassTraits<!!class> class
// which can be specialized for any given class should the default
// information not be satisfactory. Information is also obtained from
// the templated <!id>BaseClassTraits<!!id> class which must be
// specialized for each class declaring a typedef for each of its base
// classes.
//
// The information about a class stored in a
// <!id>ClassDescriptionBase<!!id> objects is the following:<BR> a
// platform-independent class name,<BR> a reference to the
// <!id>type_info<!!id><BR> an integer version number,<BR> a vector of
// <!id>ClassDescriptionBase*<!!id> corresponding to the base
// classes,<BR> methods for reading/writing members of a class from/to
// a
// <!class>PersistentIStream<!!class>/<!class>PersistentOStream<!!class>
// and<BR> a method for creating an object of a class.
//
// The <!id>ClassDescriptionBase<!!id> objects should be created
// before <!id>main()<!!id> is executed, and shouold therfore be
// instantiated as static member variables. Only one
// <!id>ClassDescriptionBase<!!id> object should be instantiated for
// each class to be described. The <!id>ClassDescriptionBase<!!id>
// objects are automatically stored in a purely static
// <!class>DescriptionList<!!class> class.
//
// <!id>AbstractClassDescription<!!id> and
// <!id>AbstractNoPIOClassDescription<!!id> should be used for
// abstract base classes, while <!id>NoPIOClassDescription<!!id> and
// <!id>AbstractNoPIOClassDescription<!!id> should be used for classes
// which do not have any members which need to be read and written
// persistently.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:ClassTraits.html">ClassTraits.h</a>,
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>,
// <a href="http:PersistentOStream.html">PersistentOStream.h</a>,
// <a href="http:DescriptionList.html">DescriptionList.h</a>.
// 


#include "ThePEG/Config/ThePEG.h"
#include "ClassDescription.fh"
// #include "ClassDescription.xh"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Persistency/PersistentOStream.fh"
#include "ThePEG/Persistency/PersistentIStream.fh"
#include "ClassTraits.h"
#include "DescriptionList.h"

namespace ThePEG {

class ClassDescriptionBase: public Named {

public:

  typedef vector<const ClassDescriptionBase *> DescriptionVector;

protected:

  inline ClassDescriptionBase(string newName, const type_info & newInfo,
			      int newVersion, string newLibrary);
  // The ctor used by sub-classes.

public:

  inline virtual ~ClassDescriptionBase();
  // Empty dtor.

  inline const type_info & info() const;
  // The standart RTTI type_info object for the described class.

  inline int version() const;
  // The version of the described class.

  inline string library() const;

  inline bool check() const;
  // Return true if this object was set up properly.

  inline const DescriptionVector & descriptions() const;
  // Return the descriptions of the base classes of the described
  // class.

  virtual void setup() = 0;
  // Set up the base class information for this object.

  virtual BPtr create() const = 0;
  // Create an object of the described class.

  virtual void output(tcBPtr, PersistentOStream &) const = 0;
  // Output the members of an object of the described class to a
  // persistent stream.

  virtual void input(tBPtr, PersistentIStream &, int oldVersion) const = 0;
  // Read the members of an object of the described class from a
  // persistent stream.

  bool isA(const ClassDescriptionBase & base) const;
  // Return true if the class described by base is a base class of the
  // class described by this.

protected:

  inline void baseClasses(DescriptionVector::iterator first,
			  DescriptionVector::iterator last);
  // Set the base classes.

private:

  int theVersion;
  // The version of the described class.

  string theLibrary;
  // The library file where this class may be found.

  const type_info & theInfo;
  // The type_info object for the described class

  DescriptionVector theBaseClasses;
  // The vector of base classes.

  bool done;
  // True if this object was set up properly.

};

template <class T>
class ClassDescriptionTBase: public ClassDescriptionBase {

public:

  typedef ClassTraits<T> Traits;

public:

  inline ClassDescriptionTBase();
  inline virtual ~ClassDescriptionTBase();
  // Default ctor and dtor.

  inline virtual void setup();
  // Set up the base class information for this object.

};

template <class T>
class AbstractClassDescription: public ClassDescriptionTBase<T> {

public:

  typedef ClassTraits<T> Traits;

public:

  inline virtual BPtr create() const;
  // Do not create an object of the described class. Just return the
  // null pointer.

  inline virtual void output(tcBPtr b, PersistentOStream & os) const;
  // Output the members of an object of the described class to a
  // persistent stream.

  inline virtual void input(tBPtr b, PersistentIStream & is,
			    int oldVersion) const;
  // Read the members of an object of the described class from a
  // persistent stream.

};

template <class T>
class ClassDescription: public ClassDescriptionTBase<T> {

public:

  typedef ClassTraits<T> Traits;

public:

  inline virtual BPtr create() const;
  // Create an object of the described class.

  inline virtual void output(tcBPtr b, PersistentOStream & os) const;
  // Output the members of an object of the described class to a
  // persistent stream.

  inline virtual void input(tBPtr b, PersistentIStream & is,
			    int oldVersion) const;
  // Read the members of an object of the described class from a
  // persistent stream.

};

template <class T>
class NoPIOClassDescription: public ClassDescriptionTBase<T> {

public:

  typedef ClassTraits<T> Traits;

public:

  inline virtual BPtr create() const;
  // Create an object of the described class.

  inline virtual void output(tcBPtr, PersistentOStream &) const;
  // Do nothing.

  inline virtual void input(tBPtr, PersistentIStream &, int) const;
  // Do nothing.

};

template <class T>
class AbstractNoPIOClassDescription: public ClassDescriptionTBase<T> {

public:

  typedef ClassTraits<T> Traits;

public:

  inline virtual BPtr create() const;
  // Do not create an object of the described class. Just return the
  // null pointer.

  inline virtual void output(tcBPtr, PersistentOStream & ) const;
  // Do nothing.

  inline virtual void input(tBPtr, PersistentIStream &, int) const;
  // Do nothing.

};

template <class T, int IBase,
          class B = typename BaseClassTrait<T,IBase>::NthBase>
struct ClassDescriptionHelper {
  static void addBases(vector<const ClassDescriptionBase *> & c);
};
// Helper function for tracing base classes.

template <class T, int IBase>
struct ClassDescriptionHelper<T, IBase, int> {
  static void addBases(vector<const ClassDescriptionBase *> & c);
};
// Helper function for tracing base classes.

}

#define ThePEG_DECLARE_CLASS_DESCRIPTION(Class)                   \
static ClassDescription<Class> init ## Class                       \

#define ThePEG_DECLARE_ABSTRACT_CLASS_DESCRIPTION(Class)          \
static AbstractClassDescription<Class> init ## Class               \

#define ThePEG_DECLARE_NOPIO_CLASS_DESCRIPTION(Class)             \
static NoPIOClassDescription<Class> init ## Class                  \

#define ThePEG_DECLARE_ABSTRACT_NOPIO_CLASS_DESCRIPTION(Class)    \
static AbstractNoPIOClassDescription<Class> init ## Class          \

#define ThePEG_IMPLEMENT_CLASS_DESCRIPTION(Class)                 \
ClassDescription<Class> Class::init ## Class                       \

#define ThePEG_IMPLEMENT_ABSTRACT_CLASS_DESCRIPTION(Class)        \
AbstractClassDescription<Class> Class::init ## Class               \

#define ThePEG_IMPLEMENT_NOPIO_CLASS_DESCRIPTION(Class)           \
NoPIOClassDescription<Class> Class::init ## Class                  \

#define ThePEG_IMPLEMENT_ABSTRACT_NOPIO_CLASS_DESCRIPTION(Class)  \
AbstractNoPIOClassDescription<Class> Class::init ## Class          \

#include "ClassDescription.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "ClassDescription.tcc"
#endif

#endif /* ThePEG_ClassDescription_H */
