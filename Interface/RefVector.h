// -*- C++ -*-
#ifndef ThePEG_RefVector_H
#define ThePEG_RefVector_H
//
// This is the declaration of the <!id>RefVector<!!id> and
// <!id>RefVectorBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>RefVector<!!id> defines an interface to a class derived
// from the <!class>InterfacedBase<!!class>, through which vectors (or
// any other container) of pointers to other
// <!class>InterfacedBase<!!class> objects may be manipulated.
// <!id>RefVector<!!id> is templated on the type of the class and the
// class of the objects pointed to, and is derived from the
// <!class>InterfaceBase<!!class> class via <!id>RefVectorBase<!!id>
// and <!id>RefInterfaceBase<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "RefVector.xh"
#include "RefVector.fh"

namespace ThePEG {

class RefVectorBase: public RefInterfaceBase {

public:

  RefVectorBase(string newName, string newDescription,
		string newClassName,
		const type_info & newTypeInfo,
		string newRefClassName,
		const type_info & newRefTypeInfo, 
		int newSize, bool depSafe,
		bool readonly, bool norebind, bool nullable, bool defnull);
  // Standard constructor.

  inline virtual ~RefVectorBase();
  // Default dtor.

  virtual string exec(InterfacedBase & ib, string action,
		      string arguments) const throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, 'action' can be any of "set",
  // "get", "erase" and "insert" and 'argument' should be a something
  // which can be read into an integer while the rest of 'argument'
  // should correspond to the name of an InterfacedBase object in the
  // BaseRepository.

  virtual string type() const;
  // Return a code for the type of this reference.

  virtual void set(InterfacedBase & ib, IBPtr ip, int i, bool chk = true)
    const throw(InterfaceException) = 0;
  // Set the i'th element of a container of pointers of ib
  // to ip.

  virtual void insert(InterfacedBase & ib, IBPtr ip, int i, bool chk = true)
    const throw(InterfaceException) = 0;
  // Insert a new pointer before the i'th element of a container of
  // pointers of ib and set it to ip.

  virtual void erase(InterfacedBase & ib, int i)
    const throw(InterfaceException) = 0;
  // Remove the i'th element of a container of pointers of ib.

  virtual IVector get(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return a vector of pointers corresponding to the container of
  // pointers of ib.

  virtual bool check(const InterfacedBase & ib, cIBPtr ip, int i) const
    throw(InterfaceException) = 0;
  // Check if set(ib, ip, i) will be successfull but do not do
  // anything.

  virtual void rebind(InterfacedBase & ib, const TranslationMap & trans,
		      const IVector & defs) const;
  // In the object ib, replace all pointers to objects in this
  // interface with the translated ones provided by trans. If a
  // pointer is null, and defaultIfNull() is truem, replace it with
  // the first alowed object found in defs.

  virtual IVector getReferences(const InterfacedBase & ib) const;
  // Return pointers to other objects in ib.

  inline int size() const;
  inline void setSize(int);
  inline void setVariableSize();
  // Get/set the size of the container being interfaced. If the size()
  // is less than 0, the size is allowed to vary.

private:

  int theSize;
  // The size of the container being interfaced.

};


template <class T, class R>
class RefVector: public RefVectorBase {

public:

  typedef typename Ptr<R>::pointer RefPtr;
  typedef typename Ptr<R>::const_pointer cRefPtr;
  typedef void (T::*SetFn)(RefPtr, int);
  typedef void (T::*InsFn)(RefPtr, int);
  typedef void (T::*DelFn)(int);
  typedef bool (T::*CheckFn)(cRefPtr, int) const;
  typedef vector<RefPtr> (T::*GetFn)() const;
  typedef vector<RefPtr> T::* Member;

public:

  RefVector(string newName, string newDescription,
	    Member newMember, int newSize, bool depSafe = false,
	    bool readonly = false, bool rebind = true, bool nullable = true,
	    SetFn newSetFn = 0, InsFn newInsFn = 0, DelFn newDelFn = 0,
	    GetFn newGetFn = 0, CheckFn newCheckFn = 0);
  RefVector(string newName, string newDescription,
	    Member newMember, int newSize, bool depSafe,
	    bool readonly, bool rebind, bool nullable, bool defnull,
	    SetFn newSetFn = 0, InsFn newInsFn = 0, DelFn newDelFn = 0,
	    GetFn newGetFn = 0, CheckFn newCheckFn = 0);
  // Standard constructors.

  virtual void set(InterfacedBase & ib, IBPtr ip, int i, bool chk = true)
    const throw(InterfaceException);
  // Set the i'th element of a container of pointers of ib
  // to ip.

  virtual void insert(InterfacedBase & ib, IBPtr ip, int i, bool chk = true)
    const throw(InterfaceException);
  // Insert a new pointer before the i'th element of a container of
  // pointers of ib and set it to ip.

  virtual void erase(InterfacedBase & ib, int i)
    const throw(InterfaceException);
  // Remove the i'th element of a container of pointers of ib.

  virtual IVector get(const InterfacedBase & ib) const
    throw(InterfaceException);
  // Return a vector of pointers corresponding to the container of
  // pointers of ib.

  virtual bool check(const InterfacedBase & ib, cIBPtr, int i) const
    throw(InterfaceException);
  // Check if set(ib, ip, i) will be successfull but do not do
  // anything.

  inline void setSetFunction(SetFn);
  // Give a pointer to a member function to be used by 'set()'.

  inline void setInsertFunction(InsFn);
  // Give a pointer to a member function to be used by 'insert()'.

  inline void setGetFunction(GetFn);
  // Give a pointer to a member function to be used by 'get()'.

  inline void setEraseFunction(DelFn);
  // Give a pointer to a member function to be used by 'erase()'.

  inline void setCheckFunction(CheckFn);
  // Give a pointer to a member function to be used by 'check()'.

private:

  Member theMember;
  // The pointer to the member variable.

  SetFn theSetFn;
  // A pointer to a member function to be used by 'set()'.

  InsFn theInsFn;
  // Give a pointer to a member function to be used by 'insert()'.

  DelFn theDelFn;
  // Give a pointer to a member function to be used by 'erase()'.

  GetFn theGetFn;
  // Give a pointer to a member function to be used by 'get()'.

  CheckFn theCheckFn;
  // Give a pointer to a member function to be used by 'check()'.

};

}

#include "RefVector.icc"
#include "RefVector.tcc"

#endif /* ThePEG_RefVector_H */
