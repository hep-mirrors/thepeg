// -*- C++ -*-
#ifndef ThePEG_ParVector_H
#define ThePEG_ParVector_H
//
// This is the declaration of the <!id>ParVector<!!id>,
// <!id>ParVectorTBase<!!id> and <!id>ParVectorBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>ParVector<!!id> defines an interface to a class derived
// from the <!class>InterfacedBase<!!class>, through which vectors (or
// any other container) of simple member variables can be
// manuipulated.  <!id>ParVector<!!id> is
// templated on the type of the member variable and the type of the
// class, and is derived from the <!class>InterfaceBase<!!class> class
// via <!id>ParVectorTBase<!!id> (which is templated only on the class
// of the member variable) and <!id>ParVectorBase<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "ParVector.fh"
#include <limits>

namespace ThePEG {

class ParVectorBase: public InterfaceBase {

public:

  typedef vector<string> StringVector;

public:

  inline ParVectorBase(string newName, string newDescription,
		       string newClassName,
		       const type_info & newTypeInfo, int newSize,
		       bool depSafe, bool readonly, bool islimited);
  // Standard constructor.

  inline virtual ~ParVectorBase();
  // Default dtor.

  virtual string exec(InterfacedBase &, string action,
		      string arguments) const throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, 'action' can be any of "set",
  // "get", "min", "max", "def" and "setdef" and 'argument' should be
  // a something which can be read into an integer and into a variable
  // through a stringstream with the standard '>>' operator.

  virtual void set(InterfacedBase & ib, string val, int i)
    const throw(InterfaceException) = 0;
  // Set the i'th element of a container of member variables of ib
  // to val.

  virtual void insert(InterfacedBase & ib, string val, int i)
    const throw(InterfaceException) = 0;
  // Insert a new object before the i'th element of a container of
  // member variables of ib and set it to val.

  virtual void erase(InterfacedBase & ib, int i)
    const throw(InterfaceException) = 0;
  // Remove the i'th element of a container of
  // member variables of ib.

  virtual StringVector get(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the values of a container of member variables of ib.

  virtual string minimum(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the minimum value allowed for the i'th element of a
  // container of member variables of ib.

  virtual string maximum(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the maximum value allowed for the i'th element of a
  // container of member variables of ib.

  virtual string def(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the default value for the i'th element of a container of
  // member variables of ib.

  virtual void setDef(InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Set the i'th element of a container of member variables of ib to
  // its default value.

  inline bool limited() const;
  inline void setLimited();
  inline void setUnlimited();
  // Get/set a flag indicating if there are limits associated with the
  // variables.

  inline int size() const;
  inline void setSize(int);
  inline void setVariableSize();
  // Get/set the size of the container being interfaced. If the size()
  // is less than 0, the size is allowed to vary.

private:

  bool isLimited;
  // True if there are limits associated with the
  // variables.

  int theSize;
  // The size of the container being interfaced.

};

template <typename Type>
class ParVectorTBase: public ParVectorBase {

public:

  typedef vector<Type> TypeVector;

public:

  inline ParVectorTBase(string newName, string newDescription,
			string newClassName, const type_info & newTypeInfo,
			Type newUnit, int newSize, bool depSafe,
			bool readonly, bool islimited);
  // Standard ctor.

  inline virtual ~ParVectorTBase();
  // Default dtor.

  virtual string type() const;
  // Return a code for the type of this parameter.

  virtual void set(InterfacedBase & ib, string val, int i) const
    throw(InterfaceException);
  virtual void tset(InterfacedBase & ib, Type val, int i)
    const throw(InterfaceException) = 0;
  // Set the i'th element of a container of member variables of ib to
  // val. The first one uses a stringstream to read the val into a
  // Type object and then calls the second.

  virtual void insert(InterfacedBase & ib, string val, int i) const
    throw(InterfaceException);
  virtual void tinsert(InterfacedBase & ib, Type val, int i)
    const throw(InterfaceException) = 0;
  // Insert a new object before the i'th element of a container of
  // member variables of ib and set it to val. The first one uses a
  // stringstream to read the val into a Type object and then calls
  // the second.

  virtual StringVector get(const InterfacedBase & ib) const
    throw(InterfaceException);
  virtual TypeVector tget(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the values of a container of member variables of ib. The
  // first one uses a stringstream to write the results from the second
  // to a vector of strings which is returned.

  virtual string minimum(const InterfacedBase & ib, int i) const
    throw(InterfaceException);
  virtual Type tminimum(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the minimum value allowed for the i'th element of a
  // container of member variables of ib. The first one uses a
  // stringstream to write the result from the second to a string
  // which is returned.

  virtual string maximum(const InterfacedBase & ib, int i) const
    throw(InterfaceException);
  virtual Type tmaximum(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the maximum value allowed for the i'th element of a
  // container of member variables of ib. The first one uses a
  // stringstream to write the result from the second to a string
  // which is returned.

  virtual string def(const InterfacedBase & ib, int i) const
    throw(InterfaceException);
  virtual Type tdef(const InterfacedBase & ib, int i) const
    throw(InterfaceException) = 0;
  // Return the default value for the i'th element of a container of
  // member variables of ib. The first one uses a stringstream to
  // write the result from the second to a string which is returned.

  virtual inline void setDef(InterfacedBase & ib, int i) const
    throw(InterfaceException);
  // set the i'th element of a container of member variables of ib to
  // its default value.

  inline Type unit() const;
  inline void unit(Type u);
  // Get/set the unit which an Type object is divided (multiplied) by
  // when written to (read from) a stream via a double. If unit() is
  // zero, the Type object is written/read directly.

private:

  Type theUnit;
  // The unit which an Type object is divided (multiplied) by
  // when written to (read from) a stream via a double. If unit() is
  // zero, the Type object is written/read directly.

};


template <typename T, typename Type>
class ParVector: public ParVectorTBase<Type> {

public:

  typedef void (T::*SetFn)(Type, int);
  typedef void (T::*InsFn)(Type, int);
  typedef void (T::*DelFn)(int);
  typedef vector<Type> TypeVector;
  typedef TypeVector (T::*GetFn)() const;
  typedef vector<string> StringVector;
  typedef StringVector (T::*StringGetFn)() const;
  typedef Type (T::*DefFn)(int) const;
  // The declaration of member functions which can be used by this
  // ParVector interface.

  typedef TypeVector T::* Member;
  // Declaration of a direct pointer to the member variable in case it
  // is a vector.

public:

  inline ParVector(string newName, string newDescription,
		   Member newMember, int newSize, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool islimited = true, SetFn newSetFn = 0,
		   InsFn newInsFn = 0, DelFn newDelFn = 0, GetFn newGetFn = 0,
		   DefFn newDefFn = 0, DefFn newMinFn = 0, DefFn newMaxFn = 0,
		   StringGetFn newStringGetFn = 0)
    : ParVectorTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			   typeid(T), Type(), newSize, depSafe, readonly,
			   islimited),
      theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
      theSetFn(newSetFn), theInsFn(newInsFn), theDelFn(newDelFn),
      theGetFn(newGetFn), theDefFn(newDefFn), theMinFn(newMinFn),
      theMaxFn(newMaxFn), theStringGetFn(newStringGetFn) {}
  // Standard ctor without giving a unit.

  inline ParVector(string newName, string newDescription, Member newMember,
		   Type newUnit, int newSize, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool islimited = true, SetFn newSetFn = 0,
		   InsFn newInsFn = 0, DelFn newDelFn = 0, GetFn newGetFn = 0,
		   DefFn newDefFn = 0, DefFn newMinFn = 0, DefFn newMaxFn = 0,
		   StringGetFn newStringGetFn = 0)
    : ParVectorTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			   typeid(T), newUnit, newSize, depSafe, readonly,
			   islimited),
      theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
      theSetFn(newSetFn), theInsFn(newInsFn), theDelFn(newDelFn),
      theGetFn(newGetFn), theDefFn(newDefFn), theMinFn(newMinFn),
      theMaxFn(newMaxFn), theStringGetFn(newStringGetFn) {}
  // Standard ctor with a given a unit.

  virtual void tset(InterfacedBase & ib, Type val, int i) const
    throw(InterfaceException);
  // Set the i'th element of a container of member variables of ib
  // to val.

  virtual void tinsert(InterfacedBase & ib, Type val, int i) const
    throw(InterfaceException);
  // Insert a new object before the i'th element of a container of
  // member variables of ib and set it to val.

  virtual void erase(InterfacedBase & ib, int i)
    const throw(InterfaceException);
  // Remove the i'th element of a container of
  // member variables of ib.

  virtual StringVector get(const InterfacedBase & ib) const
    throw(InterfaceException);
  virtual TypeVector tget(const InterfacedBase & ib) const
    throw(InterfaceException);
  // Return the values of a container of member variables of ib. The
  // first returns a vector of strings, while the second returns a
  // vector of Type.

  virtual Type tminimum(const InterfacedBase & ib, int i) const
    throw(InterfaceException);
  // Return the minimum value allowed for the i'th element of a
  // container of member variables of ib.

  virtual Type tmaximum(const InterfacedBase & ib, int i) const
    throw(InterfaceException);
  // Return the maximum value allowed for the i'th element of a
  // container of member variables of ib.

  virtual Type tdef(const InterfacedBase &, int) const
    throw(InterfaceException);
  // Return the default value allowed for the i'th element of a
  // container of member variables of ib.


  inline void setSetFunction(SetFn);
  // Give a pointer to a member function to be used by 'tset()'.

  inline void setInsertFunction(InsFn);
  // Give a pointer to a member function to be used by 'tinsert()'.

  inline void setGetFunction(GetFn);
  // Give a pointer to a member function to be used by 'tget()'.

  inline void setEraseFunction(DelFn);
  // Give a pointer to a member function to be used by 'terase()'.

  inline void setDefaultFunction(GetFn);
  // Give a pointer to a member function to be used by 'tdef()'.

  inline void setMinFunction(GetFn);
  // Give a pointer to a member function to be used by 'tminimum()'.

  inline void setMaxFunction(GetFn);
  // Give a pointer to a member function to be used by 'tmaximum()'.

  inline void setStringGetFunction(StringGetFn);
  // Give a pointer to a member function to be used by 'get()'.

private:

  Member theMember;
  // The pointer to the member variable.

  Type theDef, theMin, theMax;
  // Default, minimum and maximum values to be used if no
  // corresponding member function pointers are given.

  SetFn theSetFn;
  // A pointer to a member function to be used by 'tset()'.

  InsFn theInsFn;
  // A pointer to a member function to be used by 'tinsert()'.

  DelFn theDelFn;
  // A pointer to a member function to be used by 'terase()'.

  GetFn theGetFn;
  // A pointer to a member function to be used by 'tget()'.

  DefFn theDefFn, theMinFn, theMaxFn;
  // Pointers to member functions to be used by 'tdef()', 'tminimum()' and
  // 'tmaximum()'

  StringGetFn theStringGetFn;
  // A pointer to a member function to be used by 'set()'.

};

}

#include "ParVector.icc"
#include "ParVector.tcc"

#endif /* ThePEG_ParVector_H */
