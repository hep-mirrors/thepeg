// -*- C++ -*-
#ifndef ThePEG_Reference_H
#define ThePEG_Reference_H
//
// This is the declaration of the <!id>Reference<!!id> and
// <!id>ReferenceBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Reference<!!id> defines an interface to a class derived
// from the <!class>InterfacedBase<!!class>, through which pointers to
// other <!class>InterfacedBase<!!class> objects may be manipulated.
// <!id>Reference<!!id> is templated on the type of the class and the
// class of the objects pointed to, and is derived from the
// <!class>InterfaceBase<!!class> class via <!id>ReferenceBase<!!id>
// and <!id>RefInterfaceBase<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "Reference.xh"
#include "Reference.fh"

namespace ThePEG {

class ReferenceBase: public RefInterfaceBase {

public:

  ReferenceBase(string newName, string newDescription,
		string newClassName,
		const type_info & newTypeInfo, 
		string newRefClassName,
		const type_info & newRefTypeInfo, bool depSafe,
		bool readonly, bool norebind, bool nullable, bool defnull);
  // Standard constructor.

  inline virtual ~ReferenceBase();
  // Default dtor.

  virtual string exec(InterfacedBase & ib, string action,
		      string arguments) const throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, 'action' can be any of "set" and
  // "get" and 'argument' should correspond to the name of an
  // InterfacedBase object in the BaseRepository.

  virtual string type() const;
  // Return a code for the type of this reference.

  virtual void set(InterfacedBase & ib, IBPtr ip, bool chk = true)
    const throw(InterfaceException) = 0;
  // Set the pointer of ib to ip.

  virtual IBPtr get(const InterfacedBase & ib)
    const throw(InterfaceException) = 0;
  // Return the pointer of ib.

  virtual bool check(const InterfacedBase & ib, cIBPtr ip) const
    throw(InterfaceException) = 0;
  // Check if set(ib, ip) will be successfull but do not do
  // anything.

  virtual void rebind(InterfacedBase & ib, const TranslationMap & trans,
		      const IVector & defs) const;
  // In the object ib, replace the pointer in this interface with one
  // of the translated ones provided by trans. If the pointer is null,
  // and defaultIfNull() is truem, replace it with the first alowed
  // object found in defs.

  virtual IVector getReferences(const InterfacedBase & ib) const;
  // Return pointers to other objects in ib.

};


template <class T, class R>
class Reference: public ReferenceBase {

public:

  typedef typename Ptr<R>::pointer RefPtr;
  typedef typename Ptr<R>::const_pointer cRefPtr;
  typedef void (T::*SetFn)(RefPtr);
  typedef bool (T::*CheckFn)(cRefPtr) const;
  typedef RefPtr (T::*GetFn)() const;
  typedef RefPtr T::* Member;

public:

  Reference(string newName, string newDescription,
	    Member newMember, bool depSafe = false,
	    bool readonly = false, bool rebind = true, bool nullable = true,
	    SetFn newSetFn = 0, GetFn newGetFn = 0,
	    CheckFn newCheckFn = 0)
    : ReferenceBase(newName, newDescription,
		    ClassTraits<T>::className(), typeid(T),
		    ClassTraits<R>::className(), typeid(R),
		    depSafe, readonly, !rebind, nullable, false),
      theMember(newMember), theSetFn(newSetFn), theGetFn(newGetFn),
      theCheckFn(newCheckFn) {}

  Reference(string newName, string newDescription,
	    Member newMember, bool depSafe, bool readonly, bool rebind,
	    bool nullable, bool defnull, SetFn newSetFn = 0, GetFn newGetFn = 0,
	    CheckFn newCheckFn = 0)
    : ReferenceBase(newName, newDescription,
		    ClassTraits<T>::className(), typeid(T),
		    ClassTraits<R>::className(), typeid(R),
		    depSafe, readonly, !rebind, nullable, defnull),
      theMember(newMember), theSetFn(newSetFn), theGetFn(newGetFn),
      theCheckFn(newCheckFn) {}
  // Standard constructors.

  virtual void set(InterfacedBase & ib, IBPtr ip, bool chk = true) const
    throw(InterfaceException);
  // Set the pointer of ib to ip.

  virtual IBPtr get(const InterfacedBase & ib) const throw(InterfaceException);
  // Return the pointer of ib.

  virtual bool check(const InterfacedBase & ib, cIBPtr newRef) const
    throw(InterfaceException);
  // Check if set(ib, ip) will be successfull but do not do
  // anything.

  inline void setSetFunction(SetFn);
  // Give a pointer to a member function to be used by 'set()'.

  inline void setGetFunction(GetFn);
  // Give a pointer to a member function to be used by 'get()'.

  inline void setCheckFunction(CheckFn);
  // Give a pointer to a member function to be used by 'check()'.

private:

  Member theMember;
  // The pointer to the member variable.

  SetFn theSetFn;
  // A pointer to a member function to be used by 'set()'.

  GetFn theGetFn;
  // Give a pointer to a member function to be used by 'get()'.

  CheckFn theCheckFn;
  // Give a pointer to a member function to be used by 'check()'.


};

}

#include "Reference.icc"
#include "Reference.tcc"

#endif /* ThePEG_Reference_H */
