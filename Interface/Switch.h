// -*- C++ -*-
#ifndef ThePEG_Switch_H
#define ThePEG_Switch_H
//
// This is the declaration of the <!id>Switch<!!id>,
// <!id>SwitchBase<!!id> and <!id>SwitchOption<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Switch<!!id> defines an interface to a class derived from
// the <!class>InterfacedBase<!!class>, through which simple integer
// member variables can be manuipulated and set to a pre-defined set
// of values (options). <!id>Switch<!!id> is templated on the type of
// the integer member variable and the type of the class, and is
// derived from the <!class>InterfaceBase<!!class> class via
// <!id>SwitchBase<!!id>.
//
// The Switch class has a set of <!class>Named<!!class> SwitchOptions,
// which limits the values possible to set.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:Named.html">Named.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "Switch.fh"
#include "Switch.xh"
#include "InterfaceBase.h"

namespace ThePEG {

class SwitchOption: public Named {

public:

  inline SwitchOption(SwitchBase & theSwitch, string newName,
		      string newDescription, long newValue);
  // Standard ctor. This option is automatically registered with
  // theSwitch.

  inline SwitchOption();
  inline SwitchOption(const SwitchOption & o);
  // Default ctors.

  inline const SwitchOption & operator=(const SwitchOption & o);
  // Standard assignment.

  inline string description() const;
  // The description of this option

  inline long value() const;
  inline operator long () const;
  // The value of this option.

protected:

private:

  string theDescription;
  // The description of this option

  long theValue;
  // The value of this option.

};

class SwitchBase: public InterfaceBase {

public:

  typedef map<long, SwitchOption> OptionMap;
  typedef map<string, SwitchOption> StringMap;

  friend class SwitchOption;

public:

  inline SwitchBase(string newName, string newDescription,
		    string newClassName, const type_info & newTypeInfo,
		    bool depSafe, bool readonly);
  // Standard ctor.

  inline virtual ~SwitchBase();
  // Default dtor.

  virtual string exec(InterfacedBase & ib, string action,
		    string arguments) const throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, 'action' can be any of "set",
  // "get", "def" and "setdef" and 'argument' should be a something
  // which can be read into an integer variable through a stringstream
  // with the standard '>>' operator.

  virtual string type() const;
  // Return a code for the type of this switch.

  virtual void set(InterfacedBase & ib, long val)
    const throw(InterfaceException) = 0;
  // Set the member variable of ib to val.

  virtual long get(const InterfacedBase & ib)
    const throw(InterfaceException) = 0;
  // Return the value of the member variable of ib.

  virtual long def(const InterfacedBase & ib)
    const throw(InterfaceException) = 0;
  // Return the default value for the member variable of ib.

  inline void setDef(InterfacedBase & ib) const throw(InterfaceException);
  // Trueif there are limits associated with the variable.

  inline bool check(long val) const;
  // Check if val is among the listed options.

  inline const OptionMap & options() const;
  // Return the map relating options to their values

protected:

  inline void registerOption(const SwitchOption & o);
  // Register a new option.

private:

  OptionMap theOptions;
  // The map relating options to their values

  StringMap theOptionNames;
  // The map relating options to their names

};

template <typename T, typename Int>
class Switch: public SwitchBase {

public:

  typedef void (T::*SetFn)(Int);
  typedef Int (T::*GetFn)() const;
  // The declaration of member functions which can be used by this
  // Switch interface.

  typedef Int T::* Member;
  // Declaration of a direct pointer to the member variable.

public:

  inline Switch(string newName, string newDescription,
		Member newMember, Int newDef, bool depSafe = false,
		bool readonly = false, SetFn newSetFn = 0, GetFn newGetFn = 0,
		GetFn newDefFn = 0)
  : SwitchBase(newName, newDescription, ClassTraits<T>::className(),
	       typeid(T), depSafe, readonly),
    theMember(newMember), theDef(newDef), theSetFn(newSetFn),
    theGetFn(newGetFn), theDefFn(newDefFn) {}
  // Standard ctor.

  inline virtual ~Switch();
  // Default dtor.

  virtual void set(InterfacedBase & ib, long val) const
    throw(InterfaceException);
  // Set the member variable of ib to val.

  virtual long get(const InterfacedBase & ib) const throw(InterfaceException);
  // Return the value of the member variable of ib.

  virtual long def(const InterfacedBase & ib) const throw(InterfaceException);
  // Return the default value for the member variable of ib.

  inline void setSetFunction(SetFn);
  // Give a pointer to a member function to be used by 'set()'.

  inline void setGetFunction(GetFn);
  // Give a pointer to a member function to be used by 'get()'.

  inline void setDefaultFunction(GetFn);
  // Give a pointer to a member function to be used by 'def()'.

private:

  Member theMember;
  // The pointer to the member variable.

  Int theDef;
  // Default value to be used if no corresponding member function
  // pointers are given.

  SetFn theSetFn;
  // A pointer to a member function to be used by 'set()'.

  GetFn theGetFn, theDefFn;  
  // Pointers to member functions to be used by 'get()' and 'def()'

};

}

#include "Switch.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Switch.tcc"
#endif

#endif /* ThePEG_Switch_H */
