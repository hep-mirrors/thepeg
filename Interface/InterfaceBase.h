// -*- C++ -*-
#ifndef ThePEG_InterfaceBase_H
#define ThePEG_InterfaceBase_H
//
// This is the declaration of the <!id>InterfaceBase<!!id> and
// <!id>RefInterfaceBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>InterfaceBase<!!id> class defines a generic interface to
// any class derived from the <!class>InterfacedBase<!!class>
// class. Using the pure virtual <!id>exec<!!id> function, it is
// possible to manipulate any <!class>InterfacedBase<!!class>
// object. <!id>InterfaceBase<!!id> is an abstract base class and
// derived classes such as <!class>Command<!!class>,
// <!class>Parameter<!!class> and <!class>Reference<!!class>.
//
// For interfaces dealing with references in one
// <!class>InterfacedBase<!!class> to an object of another, there is a
// intermediate base class called <!id>RefInterfaceBase<!!id>.
//
// <!id>InterfaceBase<!!id> objects are managed by the
// <!class>BaseRepository<!!class>.
//
// <!id>InterfaceBase<!!id> is derived from the <!class>Named<!!class>
// to manage the name of the interface..
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:Command.html">Command.h</a>,
// <a href="http:Parameter.html">Parameter.h</a>,
// <a href="http:Reference.html">Reference.h</a>,
// <a href="http:BaseRepository.html">BaseRepository.h</a>.
// <a href="http:Named.html">Named.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.fh"
#include "InterfaceBase.xh"
#include "ThePEG/Utilities/Named.h"
#include "ThePEG/Utilities/ClassTraits.h"

namespace ThePEG {

class InterfaceBase: public Named {

public:

  InterfaceBase(string newName, string newDescription,
		string newClassName,
		const type_info & newTypeInfo, bool depSafe,
		bool readonly);
  // Standard ctor.

  inline virtual ~InterfaceBase();
  // Default dtor.

  virtual string exec(InterfacedBase &, string action, string arguments) const
    throw(InterfaceException) = 0;
  // Execute the 'action' command with the given arguments for the
  // given object.

  virtual string type() const = 0;
  // Return a code for the type of this interface.

  inline virtual void rebind(InterfacedBase & ib, const TranslationMap & trans,
			     const IVector & defs = IVector()) const;
  // Rebind all references in ib according to the translation
  // map. Only used by derived classed interfacing references.

  virtual IVector getReferences(const InterfacedBase & is) const;
  // For derived classes interfacing references between interfaced
  // objects, return the references for this interface.

  inline string description() const;
  // Return the description of this interface.

  virtual string fullDescription(const InterfacedBase & ib) const;
  // Return a complete description of this interface.

  inline string className() const;
  // Return the class name for the class this interface is defined
  // for.

  inline bool dependencySafe() const;
  inline void setDependencySafe();
  inline void setDependencySensitive();
  // Set/get the flag saying whether changing an object with this
  // interface may change the state of a dependent object .

  inline bool readOnly() const;
  inline void setReadOnly();
  inline void setReadWrite();
  // Set/get the flag saying whether this interface is allowed to
  // change an object.

  inline bool anonymous() const;
  // Return true if this interface is anonyous, ie. invisible for the
  // user interface.

  static bool NoReadOnly;
  // If set to true, all read-only interfaces can be changed.

private:

  string theDescription;
  // The description of this interface.

  string theClassName;
  // The class name and for the class this interface is defined for.

protected:

  mutable bool isDependencySafe;
  // Set/get the flag saying whether changing an object with this
  // interface may change the state of a dependent object .

  mutable bool isReadOnly;
  // The flag saying whether this interface is allowed to change an
  // object.


};

class RefInterfaceBase: public InterfaceBase {

public:

  inline RefInterfaceBase(string newName, string newDescription,
			  string newClassName, const type_info & newTypeInfo,
			  string newRefClassName,
			  const type_info & newRefTypeInfo,
			  bool depSafe, bool readonly,
			  bool norebind, bool nullable, bool defnull);
  // Standard ctor.

  inline string refClassName() const;
  inline const type_info & refTypeInfo() const;
  // Return the class name and type_info of the class referred to by
  // this interface.

  inline bool noRebind() const;
  inline void setNoRebind();
  inline void setRebind();
  // Set/get the flag saying whether the interface is responsible for
  // rebinding refenerces.

  inline bool noNull() const;
  inline void setNullable();
  inline void setNotNullable();
  // Set/get the flag saying whether it is allowed to set the
  // reference to null.

  inline bool defaultIfNull() const;
  inline void setDefaultIfNull();
  inline void setNoDefaultIfNull();
  // Set/get the flag saying wether a null pointer should be replaced
  // by a default of suitable class when rebind is called.

private:

  string theRefClassName;
  const type_info & theRefTypeInfo;
  // The class name and type_info of the class referred to by this
  // interface.

  bool dontRebind;
  // The flag saying whether the interface is responsible for
  // rebinding refenerces.

  bool isNullable;
  // The flag saying whether it is allowed to set the
  // reference to null.

  bool theDefaultIfNull;
  // A flag saying wether a null pointer should be replaced
  // by a default of suitable class when rebind is called.

};

inline double operator/(string,string) { return 0.0; }
inline string operator*(double,string) { return ""; }
// Dummy operators needed to be able to use stings as parameters.

}

#include "InterfaceBase.icc"

#endif /* ThePEG_InterfaceBaseH */
