// -*- C++ -*-
#ifndef ThePEG_Parameter_H
#define ThePEG_Parameter_H
//
// This is the declaration of the <!id>Parameter<!!id>,
// <!id>ParameterTBase<!!id> and <!id>ParameterBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Parameter<!!id> defines an interface to a class derived
// from the <!class>InterfacedBase<!!class>, through which simple
// member variables can be manuipulated. <!id>Parameter<!!id> is
// templated on the type of the member variable and the type of the
// class, and is derived from the <!class>InterfaceBase<!!class> class
// via <!id>ParameterTBase<!!id> (which is templated only on the class
// of the member variable) and <!id>ParameterBase<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>.
// 


#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "Parameter.xh"
#include "Parameter.fh"
#include <limits>

namespace ThePEG {

class ParameterBase: public InterfaceBase {

public:

  inline ParameterBase(string newName, string newDescription,
		       string newClassName,
		       const type_info & newTypeInfo, bool depSafe,
		       bool readonly, bool islimited);
  // Standard constructor.
  
  inline virtual ~ParameterBase();
  // The dtor.

  virtual string exec(InterfacedBase & ib, string action,
		      string arguments) const throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, 'action' can be any of "set",
  // "get", "min", "max", "def" and "setdef" and 'argument' should be
  // a something which can be read into a variable through a
  // stringstream with the standard '>>' operator.

  virtual string fullDescription(const InterfacedBase & ib) const;
  // Return a complete description of this parameter.

  virtual void set(InterfacedBase & ib, string) const
    throw(InterfaceException) = 0;
  // Set the member variable of ib to val.

  virtual string minimum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the minimum value allowed for the member variable of ib.

  virtual string maximum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the maximum value allowed for the member variable of ib.

  virtual string get(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the value of the member variable of ib.

  virtual string def(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the default value for the member variable of ib.

  virtual void setDef(InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // set the member variables of ib to its default value.

  inline bool limited() const;
  inline void setLimited();
  inline void setUnlimited();
  // Trueif there are limits associated with the variable.

private:

  bool isLimited;

};

template <typename Type>
class ParameterTBase: public ParameterBase {

public:

  inline ParameterTBase(string newName, string newDescription,
			string newClassName,
			const type_info & newTypeInfo, Type newUnit,
			bool depSafe, bool readonly, bool islimited);
    // Standard ctor.

  inline virtual ~ParameterTBase();
  // Default dtor.

  virtual string type() const;
  // Return a code for the type of this parameter.

  virtual void set(InterfacedBase & ib, string newValue)
    const throw(InterfaceException);
  virtual void tset(InterfacedBase & ib, Type) const
    throw(InterfaceException) = 0;
  // Set the member variables of ib to val. The first one uses a
  // stringstream to read the val into a Type object and then calls
  // the second.

  virtual string get(const InterfacedBase & ib) const throw(InterfaceException);
  virtual Type tget(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the value of the member variable of ib. The first one uses
  // a stringstream to write the results from the second to a vector
  // of strings which is returned.

  virtual string minimum(const InterfacedBase & ib) const
    throw(InterfaceException);
  virtual Type tminimum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the minimum value allowed for the member variable of
  // ib. The first one uses a stringstream to write the result from
  // the second to a string which is returned.

  virtual string maximum(const InterfacedBase & ib) const
    throw(InterfaceException);
  virtual Type tmaximum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;
  // Return the miaximum value allowed for the member variable of
  // ib. The first one uses a stringstream to write the result from
  // the second to a string which is returned.

  virtual string def(const InterfacedBase & ib) const throw(InterfaceException);
  virtual Type tdef(const InterfacedBase &ib) const
    throw(InterfaceException) = 0;
  // Return the default value for the member variables of ib. The
  // first one uses a stringstream to write the result from the second
  // to a string which is returned.

  inline virtual void setDef(InterfacedBase & ib)
    const throw(InterfaceException);
  // set the member variable of ib to its default value.

  inline Type unit() const;
  inline void unit(Type u);
  // Get/set the unit which an Type object is divided (multiplied) by
  // when written to (read from) a stream via a double. If unit() is
  // zero, the Type object is written/read directly.

protected:

  inline void putUnit(ostream &, Type val) const;

private:

  Type theUnit;
  // The unit which an Type object is divided (multiplied) by
  // when written to (read from) a stream via a double. If unit() is
  // zero, the Type object is written/read directly.

};

template <typename T, typename Type>
class Parameter: public ParameterTBase<Type> {

public:

  typedef void (T::*SetFn)(Type);
  typedef Type (T::*GetFn)() const;
  // The declaration of member functions which can be used by this
  // Switch interface.

  typedef Type T::* Member;
  // Declaration of a direct pointer to the member variable.

public:

  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool islimited = true, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), Type(), depSafe, readonly, islimited),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}
  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newUnit, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool islimited = true, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), newUnit, depSafe, readonly, islimited),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}
  // Standard ctors.

  inline virtual ~Parameter();
  // Default dtor.

  virtual void tset(InterfacedBase & ib, Type val)
    const throw(InterfaceException);
  // Set the member variable of ib to val.

  virtual Type tget(const InterfacedBase & ib) const throw(InterfaceException);
  // Return the value of the member variable of ib.

  virtual Type tminimum(const InterfacedBase & ib) const
    throw(InterfaceException);
  // Return the minimum value allowed for the member variable of ib.

  virtual Type tmaximum(const InterfacedBase & ib) const
    throw(InterfaceException);
  // Return the miaximum value allowed for the member variable of ib.

  virtual Type tdef(const InterfacedBase & ib) const throw(InterfaceException);
  // Return the default value for the member variable of ib.

  inline void setSetFunction(SetFn);
  // Give a pointer to a member function to be used by 'tset()'.

  inline void setGetFunction(GetFn);
  // Give a pointer to a member function to be used by 'tget()'.

  inline void setDefaultFunction(GetFn);
  // Give a pointer to a member function to be used by 'tdef()'.

  inline void setMinFunction(GetFn);
  // Give a pointer to a member function to be used by 'tminimum()'.

  inline void setMaxFunction(GetFn);
  // Give a pointer to a member function to be used by 'tmaximum()'.

private:

  Member theMember;
  // The pointer to the member variable.

  Type theDef, theMin, theMax;
  // Default, minimum and maximum values to be used if no
  // corresponding member function pointers are given.

  SetFn theSetFn;
  // A pointer to a member function to be used by 'tset()'.

  GetFn theGetFn, theDefFn, theMinFn, theMaxFn;
  // Pointers to member functions to be used by 'tget()', 'tdef()',
  // 'tminimum()' and 'tmaximum()'

};

}

#include "Parameter.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Parameter.tcc"
#endif

#endif /* ThePEG_Parameter_H */
