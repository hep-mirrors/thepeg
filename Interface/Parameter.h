// -*- C++ -*-
#ifndef ThePEG_Parameter_H
#define ThePEG_Parameter_H
// This is the declaration of the Parameter, ParameterTBase and
// ParameterBase classes.


#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "Parameter.xh"
#include "Parameter.fh"
#include "ThePEG/Utilities/StringUtils.h"
#include <limits>

namespace ThePEG {

/**
 * The Parameter and its base classes ParameterTBase and ParameterBase
 * defines an interface to a class derived from the InterfacedBase,
 * through which simple member variables can be
 * manuipulated. Parameter is templated on the type of the member
 * variable and the type of the InterfacedBase class, and is derived
 * from the InterfaceBase class via ParameterTBase (which is templated
 * only on the type of the member variable) and ParameterBase.
 *
 * For each InterfacedBase class exactly one static Parameter object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class.
 *
 * @see InterfacedBase
 * @see InterfaceBase
 * 
 */
class ParameterBase: public InterfaceBase {

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
   *
   * @param limits determines if the values of the parameters are
   * limited from above and/or below. The possible values are given by
   * Interface::Limits.
   */
  inline ParameterBase(string newName, string newDescription,
		       string newClassName,
		       const type_info & newTypeInfo, bool depSafe,
		       bool readonly, int limits);  
  /**
   * The destructor.
   */
  inline virtual ~ParameterBase();

  /**
   * The general interface method overriding the one in
   * InterfaceBase. For this class, \a action can be any of "set",
   * "get", "min", "max", "def" and "setdef" and \a argument should be
   * a something which can be read into a variable through a
   * stringstream with the standard '>>' operator.
   */
  virtual string exec(InterfacedBase & ib, string action,
		      string arguments) const throw(InterfaceException);

  /**
   * Return a complete description of this parameter.
   */
  virtual string fullDescription(const InterfacedBase & ib) const;

  /**
   * Set the member variable of \a ib to \a val.
   */
  virtual void set(InterfacedBase & ib, string) const
    throw(InterfaceException) = 0;

  /**
   * Return the minimum value allowed for the member variable of \a ib.
   */
  virtual string minimum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the maximum value allowed for the member variable of \a ib.
   */
  virtual string maximum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the value of the member variable of \a ib.
   */
  virtual string get(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the default value for the member variable of \a ib.
   */
  virtual string def(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Set the member variable of \a ib to its default value.
   */
  virtual void setDef(InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * True if there the variable is limited from above and below.
   */
  inline bool limited() const;

  /**
   * True if there the variable is limited from abovew.
   */
  inline bool upperLimit() const;

  /**
   * True if there the variable is limited from  below.
   */
  inline bool lowerLimit() const;

  /**
   * Set flag indicating that there are limits associated with the
   * variable.
   */
  inline void setLimited();

  /**
   * Set flag indicating that there are no limits associated with the
   * variable.
   */
  inline void setUnlimited();

private:

  /**
   * Determines if the values of the parameters are
   * limited from above and/or below. The possible values are given by
   * Interface::Limits.
   */
  int limit;

};

/**
 * The Parameter and its base classes ParameterTBase and ParameterBase
 * defines an interface to a class derived from the InterfacedBase,
 * through which simple member variables can be
 * manuipulated. Parameter is templated on the type of the member
 * variable and the type of the InterfacedBase class, and is derived
 * from the InterfaceBase class via ParameterTBase (which is templated
 * only on the type of the member variable) and ParameterBase.
 *
 * For each InterfacedBase class exactly one static Parameter object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class.
 *
 * @see InterfacedBase
 * @see InterfaceBase
 * 
 */
template <typename Type>
class ParameterTBase: public ParameterBase {

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
   * @param newUnit the unit assumed when a number is read or written
   * to a stream.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param limits determines if the values of the parameters are
   * limited from above and/or below. The possible values are given by
   * Interface::Limits.
   */
  inline ParameterTBase(string newName, string newDescription,
			string newClassName,
			const type_info & newTypeInfo, Type newUnit,
			bool depSafe, bool readonly, int limits);

  /**
   * Destructor.
   */
  inline virtual ~ParameterTBase();

  /**
   * Return a code for the type of this parameter.
   */
  virtual string type() const;

private:

  /// Implementation of set() for standard types.
  inline void setImpl (InterfacedBase & i, 
		       string newValue, StandardT) 
    const throw(InterfaceException);

  /// Implementation of set() for dimensioned types.
  inline void setImpl (InterfacedBase & i, 
		       string newValue, DimensionT) 
    const throw(InterfaceException);

public:

  /**
   * Set the member variables of \a ib to \a val. Uses a stringstream
   * to read the \a val into a Type object and then calls
   * tset(InterfacedBase &, Type).
   */
  virtual void set(InterfacedBase & ib, string newValue)
    const throw(InterfaceException);

  /**
   * Set the member variables of \a ib to \a val.
   */
  virtual void tset(InterfacedBase & ib, Type) const
    throw(InterfaceException) = 0;

  /**
   * Return the value of the member variable of \a ib. Calls
   * tget(const InterfacedBase &) and converts the returned value with
   * an ostringstream.
   */
  virtual string get(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the value of the member variable of \a ib.
   */
  virtual Type tget(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the minimum value allowed for the member variable of \a
   * ib. Calls tmimimum(const InterfacedBase &) and converts the
   * returned value with an ostringstream.
   */
  virtual string minimum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the minimum value allowed for the member variable of \a
   * ib.
   */
  virtual Type tminimum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the maximum value allowed for the member variable of \a
   * ib. Calls tmaximum(const InterfacedBase &) and converts the
   * returned value with an ostringstream.
   */
  virtual string maximum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the maximum value allowed for the member variable of
   * \a ib.
   */
  virtual Type tmaximum(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the default value for the member variables of \a ib. Calls
   * tdef(const InterfacedBase &) and converts the returned value with
   * an ostringstream.
   */
  virtual string def(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the default value for the member variables of \a ib.
   */
  virtual Type tdef(const InterfacedBase &ib) const
    throw(InterfaceException) = 0;

  /**
   * set the member variable of \a ib to its default value.
   */
  inline virtual void setDef(InterfacedBase & ib)
    const throw(InterfaceException);

  /**
   * Get the unit which an Type object is divided (multiplied) by when
   * written to (read from) a stream via a double. If unit() is zero,
   * the Type object is written/read directly.
   */
  inline Type unit() const;

  /**
   * Set the unit which an Type object is divided (multiplied) by when
   * written to (read from) a stream via a double. If unit() is zero,
   * the Type object is written/read directly.
   */
  inline void unit(Type u);

  /**
   * Return a string describing the type of interface to be included
   * in the Doxygen documentation.
   */
  virtual string doxygenType() const;

protected:

  /**
   * Write a numer to a stream with the unit specified with unit().
   */
  inline void putUnit(ostream &, Type val) const;

private:

  /**
   * The unit which an Type object is divided (multiplied) by
   * when written to (read from) a stream via a double. If unit() is
   * zero, the Type object is written/read directly.
   */
  Type theUnit;

};

/**
 * The Parameter and its base classes ParameterTBase and ParameterBase
 * defines an interface to a class derived from the InterfacedBase,
 * through which simple member variables can be
 * manuipulated. Parameter is templated on the type of the member
 * variable and the type of the InterfacedBase class, and is derived
 * from the InterfaceBase class via ParameterTBase (which is templated
 * only on the type of the member variable) and ParameterBase.
 *
 * For each InterfacedBase class exactly one static Parameter object
 * should created for each member variable which should be
 * interfaced. This object will automatically register itself with the
 * BaseRepository class.
 *
 * @see InterfacedBase
 * @see InterfaceBase
 * 
 */
template <typename T, typename Type>
class Parameter: public ParameterTBase<Type> {

public:

  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'set' action.
   */
  typedef void (T::*SetFn)(Type);
  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'get', 'def', 'min' and 'max' actions.
   */
  typedef Type (T::*GetFn)() const;

  /**
   * Declaration of a direct pointer to the member variable.
   */
  typedef Type T::* Member;

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
   * @param newMin the minimum value for the member variable.
   *
   * @param newMax the maximum value for the member variable.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param limits determines if the values of the parameters are
   * limited from above and below.
   *
   * @param newSetFn optional pointer to the member function for the
   * 'set' action.
   *
   * @param newGetFn optional pointer to the member function for the
   * 'get' action.
   *
   * @param newMinFn optional pointer to the member function for the
   * 'min' action.
   *
   * @param newMaxFn optional pointer to the member function for the
   * 'max' action.
   *
   * @param newDefFn optional pointer to the member function for the
   * 'def' action.
   */
  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool limits = true, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), Type(), depSafe, readonly, limits),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}

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
   * @param newUnit the unit assumed when a number is read or written
   * to a stream.
   *
   * @param newDef the default value for the member variable.
   *
   * @param newMin the minimum value for the member variable.
   *
   * @param newMax the maximum value for the member variable.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param limits determines if the values of the parameters are
   * limited from above and below.
   *
   * @param newSetFn optional pointer to the member function for the
   * 'set' action.
   *
   * @param newGetFn optional pointer to the member function for the
   * 'get' action.
   *
   * @param newMinFn optional pointer to the member function for the
   * 'min' action.
   *
   * @param newMaxFn optional pointer to the member function for the
   * 'max' action.
   *
   * @param newDefFn optional pointer to the member function for the
   * 'def' action.
   */
  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newUnit, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   bool limits = true, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), newUnit, depSafe, readonly, limits),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}

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
   * @param newMin the minimum value for the member variable.
   *
   * @param newMax the maximum value for the member variable.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param limits determines if the values of the parameters are
   * limited from above and/or below. The possible values are given by
   * Interface::Limits.
   *
   * @param newSetFn optional pointer to the member function for the
   * 'set' action.
   *
   * @param newGetFn optional pointer to the member function for the
   * 'get' action.
   *
   * @param newMinFn optional pointer to the member function for the
   * 'min' action.
   *
   * @param newMaxFn optional pointer to the member function for the
   * 'max' action.
   *
   * @param newDefFn optional pointer to the member function for the
   * 'def' action.
   */
  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   int limits = Interface::limited, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), Type(), depSafe, readonly, limits),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}

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
   * @param newUnit the unit assumed when a number is read or written
   * to a stream.
   *
   * @param newDef the default value for the member variable.
   *
   * @param newMin the minimum value for the member variable.
   *
   * @param newMax the maximum value for the member variable.
   *
   * @param depSafe set to true if calls to this interface for one
   * object does not influence other objects.
   *
   * @param readonly if this is set true the interface will not be
   * able to manipulate objects of the corresponding class, but will
   * still be able to access information.
   *
   * @param limits determines if the values of the parameters are
   * limited from above and/or below. The possible values are given by
   * Interface::Limits.
   *
   * @param newSetFn optional pointer to the member function for the
   * 'set' action.
   *
   * @param newGetFn optional pointer to the member function for the
   * 'get' action.
   *
   * @param newMinFn optional pointer to the member function for the
   * 'min' action.
   *
   * @param newMaxFn optional pointer to the member function for the
   * 'max' action.
   *
   * @param newDefFn optional pointer to the member function for the
   * 'def' action.
   */
  inline Parameter(string newName, string newDescription,
		   Member newMember, Type newUnit, Type newDef, Type newMin,
		   Type newMax, bool depSafe = false, bool readonly = false,
		   int limits = Interface::limited, SetFn newSetFn = 0,
		   GetFn newGetFn = 0, GetFn newMinFn = 0,
		   GetFn newMaxFn = 0, GetFn newDefFn = 0)
  : ParameterTBase<Type>(newName, newDescription, ClassTraits<T>::className(),
			 typeid(T), newUnit, depSafe, readonly, limits),
    theMember(newMember), theDef(newDef), theMin(newMin), theMax(newMax),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn),
    theMinFn(newMinFn), theMaxFn(newMaxFn) {}

  /**
   * Default dtor.
   */
  inline virtual ~Parameter();

  /**
   * Set the member variable of \a ib to \a val.
   */
  virtual void tset(InterfacedBase & ib, Type val)
    const throw(InterfaceException);

  /**
   * Return the value of the member variable of ib.
   */
  virtual Type tget(const InterfacedBase & ib) const throw(InterfaceException);

  /**
   * Return the minimum value allowed for the member variable of \a ib.
   */
  virtual Type tminimum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the miaximum value allowed for the member variable of \a ib.
   */
  virtual Type tmaximum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the default value for the member variable of \a ib.
   */
  virtual Type tdef(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Give a pointer to a member function to be used by tset().
   */
  inline void setSetFunction(SetFn);

  /**
   * Give a pointer to a member function to be used by tget().
   */
  inline void setGetFunction(GetFn);

  /**
   * Give a pointer to a member function to be used by tdef().
   */
  inline void setDefaultFunction(GetFn);

  /**
   * Give a pointer to a member function to be used by tminimum().
   */
  inline void setMinFunction(GetFn);

  /**
   * Give a pointer to a member function to be used by tmaximum().
   */
  inline void setMaxFunction(GetFn);

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
   * pointer is given.
   */
  Type theDef;

  /**
   * Minimum value to be used if no corresponding member function
   * pointer is given.
   */
  Type theMin;

  /**
   * Maximum value to be used if no corresponding member function
   * pointer is given.
   */
  Type theMax;

  /**
   * A pointer to a member function to be used by tset().
   */
  SetFn theSetFn;

  /**
   * Pointer to member function to be used by tget().
   */
  GetFn theGetFn;

  /**
   * Pointer to member function to be used by tdef().
   */
  GetFn theDefFn;

  /**
   * Pointer to member function to be used by tminimum().
   */
  GetFn theMinFn;

  /**
   * Pointer to member function to be used by tmaximum().
   */
  GetFn theMaxFn;

};

/**
 * This is a specialization of ParameterTBase for the string case.
 *
 * @see ParameterTBase
 * 
 */
template <>
class ParameterTBase<string>: public ParameterBase {

public:

  /**
   * Enumerated variables to determine of a string parameter
   * corresponds to a file or a directory.
   */
  enum FileType {
    NoFile,    /**< Neither file nor directory. */
    File,      /**< The parameter corresponds to a file. */
    Directory  /**< The parameter corresponds to a directory. */
  };

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
  inline ParameterTBase(string newName, string newDescription,
			string newClassName,
			const type_info & newTypeInfo,
			bool depSafe, bool readonly);

  /**
   * Destructor.
   */
  inline virtual ~ParameterTBase();

  /**
   * Return a code for the type of this parameter.
   */
  inline virtual string type() const;

  /**
   * Indicate that this parameter corresponds to a file. 
   */
  inline void fileType();

  /**
   * Indicate that this parameter corresponds to a directory. 
   */
  inline void directoryType();

  /**
   * Indicate if this parameter corresponds to a file or directory. 
   */
  inline void file(FileType t);

  /**
   * See if this parameter corresponds to a file or directory.
   */
  inline FileType file() const;

  /**
   * Set the member variables of \a ib to \a val. Uses a stringstream
   * to read the \a val into a Type object and then calls
   * tset(InterfacedBase &, Type).
   */
  inline virtual void set(InterfacedBase & ib, string newValue)
    const throw(InterfaceException);

  /**
   * Set the member variables of \a ib to \a val.
   */
  virtual void tset(InterfacedBase & ib, string) const
    throw(InterfaceException) = 0;

  /**
   * Return the value of the member variable of \a ib. Calls
   * tget(const InterfacedBase &) and converts the returned value with
   * an ostringstream.
   */
  inline virtual string get(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the value of the member variable of \a ib.
   */
  virtual string tget(const InterfacedBase & ib) const
    throw(InterfaceException) = 0;

  /**
   * Return the minimum value allowed for the member variable of \a
   * ib. Not relevant for strings. Returns the empty string.
   */
  inline virtual string minimum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the maximum value allowed for the member variable of \a
   * ib. Not relevant for strings. Returns the empty string.
   */
  inline virtual string maximum(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the default value for the member variables of \a ib. Calls
   * tdef(const InterfacedBase &) and converts the returned value with
   * an ostringstream.
   */
  inline virtual string def(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the default value for the member variables of \a ib.
   */
  virtual string tdef(const InterfacedBase &ib) const
    throw(InterfaceException) = 0;

  /**
   * set the member variable of \a ib to its default value.
   */
  inline virtual void setDef(InterfacedBase & ib)
    const throw(InterfaceException);

  /**
   * Return a string describing the type of interface to be included
   * in the Doxygen documentation.
   */
  inline virtual string doxygenType() const;

private:

  /**
   * Indicates if this parameter corresponds to a file or directory. 
   */
  FileType isFileType;

};

/**
 * This is a partial specialization of Parameter for the string case.
 *
 * @see Parameter
 * 
 */
template <typename T>
class Parameter<T,string>: public ParameterTBase<string> {

public:

  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'set' action.
   */
  typedef void (T::*SetFn)(string);
  /**
   * The declaration of member functions which can be used by this
   * Switch interface for the 'get', 'def', 'min' and 'max' actions.
   */
  typedef string (T::*GetFn)() const;

  /**
   * Declaration of a direct pointer to the member variable.
   */
  typedef string T::* Member;

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
  inline Parameter(string newName, string newDescription,
		   Member newMember, string newDef,
		   bool depSafe = false, bool readonly = false,
		   SetFn newSetFn = 0, GetFn newGetFn = 0, GetFn newDefFn = 0)
    : ParameterTBase<string>(newName, newDescription,
			     ClassTraits<T>::className(),
			 typeid(T), depSafe, readonly),
    theMember(newMember), theDef(newDef),
    theSetFn(newSetFn), theGetFn(newGetFn), theDefFn(newDefFn) {}


  /**
   * Default dtor.
   */
  inline virtual ~Parameter();

  /**
   * Set the member variable of \a ib to \a val.
   */
  virtual void tset(InterfacedBase & ib, string val)
    const throw(InterfaceException);

  /**
   * Return the value of the member variable of ib.
   */
  virtual string tget(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Return the default value for the member variable of \a ib.
   */
  virtual string tdef(const InterfacedBase & ib) const
    throw(InterfaceException);

  /**
   * Give a pointer to a member function to be used by tset().
   */
  inline void setSetFunction(SetFn);

  /**
   * Give a pointer to a member function to be used by tget().
   */
  inline void setGetFunction(GetFn);

  /**
   * Give a pointer to a member function to be used by tdef().
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
   * Default, minimum and maximum values to be used if no
   * corresponding member function pointers are given.
   */
  string theDef;

  /**
   * A pointer to a member function to be used by tset().
   */
  SetFn theSetFn;

  /**
   * Pointer to member function to be used by tget().
   */
  GetFn theGetFn;

  /**
   * Pointer to member function to be used by tdef().
   */
  GetFn theDefFn;

};

}

#include "Parameter.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Parameter.tcc"
#endif

#endif /* ThePEG_Parameter_H */
