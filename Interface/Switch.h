// -*- C++ -*-
#ifndef ThePEG_Switch_H
#define ThePEG_Switch_H
// This is the declaration of the Switch, SwitchBase and SwitchOption classes.

#include "ThePEG/Config/ThePEG.h"
#include "Switch.fh"
#include "Switch.xh"
#include "InterfaceBase.h"

namespace ThePEG {

/**
 * SwitchOption is used by the Switch class and its base class
 * SwitchBase to define valid options in a switch.
 *
 * For each InterfacedBase class exactly one static Switch object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class. Also for each Switch object exactly one
 * static SwitchOption object should be created for each valid integer
 * option.
 *
 * @see InterfacedBase
 * @see InterfacedBase
 * @see Named
 * 
 */
class SwitchOption: public Named {

public:

  /**
   * Standard constructor.
   *
   * @param theSwitch the Switch object for which this option is
   * defined. Note thet the static Switch object must be created
   * before this is created.
   *
   * @param newName the name of the option, may only contain
   * letters [a-zA-z0-9_].
   *
   * @param newDescription a brief description of the option.
   *
   * @param newValue the integer value corresponding to this option.
   */
  inline SwitchOption(SwitchBase & theSwitch, string newName,
		      string newDescription, long newValue);

  /**
   * Default constrictor.
   */
  inline SwitchOption();

  /**
   * Copy constructors.
   */
  inline SwitchOption(const SwitchOption & o);

  /**
   * Standard assignment.
   */
  inline const SwitchOption & operator=(const SwitchOption & o);

  /**
   * The description of this option
   */
  inline string description() const;

  /**
   * The value of this option.
   */
  inline long value() const;
  /**
   * The value of this option.
   */
  inline operator long () const;

protected:

private:

  /**
   * The description of this option
   */
  string theDescription;

  /**
   * The value of this option.
   */
  long theValue;

};

/**
 * The Switch class and its base class SwitchBase defines an interface
 * to a class derived from the InterfacedBase, through which simple
 * integer member variables can be manuipulated and set to a
 * pre-defined set of values (options). Switch is
 * templated on the type of the integer member variable and the type
 * of the class, and is derived from the InterfaceBase class via
 * <code>SwitchBase</code>.
 *
 * The Switch class has a set of Named SwitchOptions,
 * which limits the values possible to set.
 *
 * For each InterfacedBase class exactly one static Switch object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class. Also for each Switch object exactly one
 * static SwitchOption object should be created for each valid integer
 * option.
 *
 * @see InterfacedBase
 * @see InterfacedBase
 * @see Named
 * 
 */
class SwitchBase: public InterfaceBase {

public:

  /** A map with SwitchOptions indexed by their values. */
  typedef map<long, SwitchOption> OptionMap;
  /** A map with SwitchOptions indexed by their names. */
  typedef map<string, SwitchOption> StringMap;

  /** SwitchOption is a friend. */
  friend class SwitchOption;

public:

  /**
   * Standard constructor.
   *
   * @param newName the name of the interface, may only contain
   * letters [a-zA-z0-9_].
   *
   * @param newDescription a brief description of the interface.
   *
   * @param newClassName the name of the corresponding class.
   *
   * @param newTypeInfo the type_info object of the corresponding
   * class.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   */
  inline SwitchBase(string newName, string newDescription,
		    string newClassName, const type_info & newTypeInfo,
		    bool depSafe, bool readonly);

  /**
   * Destructor.
   */
  inline virtual ~SwitchBase();

  /**
   * The general interface method overriding the one in
   * InterfaceBase. For this class, \a action can be any of "set",
   * "get", "def" and "setdef" and \a argument should be a something
   * which can be read into an integer variable through a stringstream
   * with the standard '>>' operator.
   */
  virtual string exec(InterfacedBase & ib, string action,
		    string arguments) const throw(InterfaceException);

  /**
   * Return a code for the type of this switch.
   */
  virtual string type() const;

  /**
   * Set the member variable of \a ib to \a val.
   */
  virtual void set(InterfacedBase & ib, long val)
    const throw(InterfaceException) = 0;

  /**
   * Return the value of the member variable of \a ib.
   */
  virtual long get(const InterfacedBase & ib)
    const throw(InterfaceException) = 0;

  /**
   * Return the default value for the member variable of \a ib.
   */
  virtual long def(const InterfacedBase & ib)
    const throw(InterfaceException) = 0;

  /**
   * Set the member variable of \a ib to its default value.
   */
  inline void setDef(InterfacedBase & ib) const throw(InterfaceException);

  /**
   * Check if \a val is among the listed options.
   */
  inline bool check(long val) const;

  /**
   * Return the map relating options to their values
   */
  inline const OptionMap & options() const;

  /**
   * Return a string describing the type of interface to be included
   * in the Doxygen documentation.
   */
  virtual string doxygenType() const;

protected:

  /**
   * Register a new option.
   */
  inline void registerOption(const SwitchOption & o);

private:

  /**
   * The map relating options to their values
   */
  OptionMap theOptions;

  /**
   * The map relating options to their names
   */
  StringMap theOptionNames;

};

/**
 * The Switch class and its base class SwitchBase defines an interface
 * to a class derived from the InterfacedBase, through which simple
 * integer member variables can be manuipulated and set to a
 * pre-defined set of values (options). Switch is templated on the
 * type of the integer member variable (also enums and bool are
 * allowed) and the type of the class, and is derived from the
 * InterfaceBase class via SwitchBase.
 *
 * The Switch class has a set of Named SwitchOptions,
 * which limits the values possible to set.
 *
 * For each InterfacedBase class exactly one static Switch object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class. Also for each Switch object exactly one
 * static SwitchOption object should be created for each valid integer
 * option.
 *
 * @see InterfacedBase
 * @see InterfacedBase
 * @see Named
 * 
 */
template <typename T, typename Int>
class Switch: public SwitchBase {

public:

  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'set' action.
   */
  typedef void (T::*SetFn)(Int);
  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'get' action.
   */
  typedef Int (T::*GetFn)() const;

  /**
   * Declaration of a direct pointer to the member variable.
   */
  typedef Int T::* Member;

public:

  /**
   * Standard constructor.
   *
   * @param newName the name of the interface, may only contain
   * letters [a-zA-z0-9_].
   *
   * @param newDescription a brief description of the interface.
   *
   * @param newMember a pointer to the member variable. May be null if
   * corresponding set/get functions are provided.
   *
   * @param newDef the default value for the member variable.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param newSetFn optional pointer to the member function for the
   * 'set' action.
   *
   * @param newGetFn optional pointer to the member function for the
   * 'get' action.
   *
   * @param newDefFn optional pointer to the member function for the
   * 'def' action.
   */
  inline Switch(string newName, string newDescription,
		Member newMember, Int newDef, bool depSafe = false,
		bool readonly = false, SetFn newSetFn = 0, GetFn newGetFn = 0,
		GetFn newDefFn = 0)
  : SwitchBase(newName, newDescription, ClassTraits<T>::className(),
	       typeid(T), depSafe, readonly),
    theMember(newMember), theDef(newDef), theSetFn(newSetFn),
    theGetFn(newGetFn), theDefFn(newDefFn) {}


  /**
   * Destructor.
   */
  inline virtual ~Switch();

  /**
   * Set the member variable of \a ib to \a val.
   */
  virtual void set(InterfacedBase & ib, long val) const
    throw(InterfaceException);

  /**
   * Return the value of the member variable of \a ib.
   */
  virtual long get(const InterfacedBase & ib) const throw(InterfaceException);

  /**
   * Return the default value for the member variable of \a ib.
   */
  virtual long def(const InterfacedBase & ib) const throw(InterfaceException);

  /**
   * Give a pointer to a member function to be used by 'set()'.
   */
  inline void setSetFunction(SetFn);

  /**
   * Give a pointer to a member function to be used by 'get()'.
   */
  inline void setGetFunction(GetFn);

  /**
   * Give a pointer to a member function to be used by 'def()'.
   */
  inline void setDefaultFunction(GetFn);

  /**
   * Print a description to be included in the Doxygen documentation
   * to the given \a stream.
   */
  virtual void doxygenDescription(ostream & stream) const;

private:

  /**
   * The pointer to the member variable.
   */
  Member theMember;

  /**
   * Default value to be used if no corresponding member function
   * pointers are given.
   */
  Int theDef;

  /**
   * A pointer to a member function to be used by 'set()'.
   */
  SetFn theSetFn;

  /**
   * Pointers to member functions to be used by 'get()' and 'def()'
   */
  GetFn theGetFn, theDefFn;  


};

}

#include "Switch.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Switch.tcc"
#endif

#endif /* ThePEG_Switch_H */
