// -*- C++ -*-
#ifndef ThePEG_Command_H
#define ThePEG_Command_H
//
// This is the declaration of the <!id>Command<!!id>
// and<!id>CommandBase<!!id> classes.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>Command<!!id> defines an interface to a class derived from
// the <!class>InterfacedBase<!!class>, through which arbitratru
// command strings can be sent and received. <!id>Command<!!id> is
// templated and is derived from the <!class>InterfaceBase<!!class>
// class via <!id>CommandBase<!!id>.
//
// For each command interface to be defined for a class <!id>T<!!id>,
// exactly one object of the <!id>Command&lt;T&gt;<!!id> must be
// created and initialized as follows:
//
// <!id>Command&lt;T&gt; comint(name, description, &T::memberfn,
// depsafe);<!!id>
//
// Where <!id>name<!!id> is an identifier <!id>std::string<!!id> which
// should only contain letters [a-zA-z0-9_], <!id>description<!!id> is
// an arbitrary <!id>std::string<!!id>, <!id>memberfn<!!id> should be
// a non-static member function of <!id>T<!!id> and defined as
// <!id>std::string T::memberfn(std::string)<!!id>. Finally if
// <!id>depsafe<!!id> is true it can be assumed that a call to the
// <!id>memberfn<!!id> for an object does not influence other objects
// which may depend on the first.
//
// The <!id>Command<!!id> class, as all other
// <!class>InterfaceBase<!!class> classes are mainly used in the
// <!class>BaseRepository<!!class> class.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:InterfacedBase.html">InterfacedBase.h</a>,
// <a href="http:InterfaceBase.html">InterfaceBase.h</a>,
// <a href="http:BaseRepository.html">BaseRepository.h</a>
// 

#include "ThePEG/Config/ThePEG.h"
#include "InterfaceBase.h"
#include "Command.fh"
#include "Command.xh"

namespace ThePEG {

class CommandBase: public InterfaceBase {

public:

  inline CommandBase(string newName, string newDescription,
		     string newClassName,
		     const type_info & newTypeInfo, bool depSafe);
  // Standard ctor.

  inline virtual ~CommandBase();
  // default dtor.

  virtual string exec(InterfacedBase &ib, string action, string arguments) const
    throw(InterfaceException);
  // The general interface method overriding the one in
  // InterfaceBase. For this class, the 'action' and 'argument'
  // arguments are concatenated (with a space character inserted) and
  // sent to the 'cmd' function.

  virtual string type() const;
  // Return a code for the type of this interface.

  virtual string cmd(InterfacedBase & ib, string c) const
    throw(InterfaceException) = 0;
  // For the object ib execute the memberfunction (defined in the
  // derived class) with 'c' as argument and return the return value.

};

template <class T>
class Command: public CommandBase {

public:

  typedef string (T::*ExeFn)(string);
  // The declaration of member functions which can be used by this
  // Command interface.

public:

  Command(string newName, string newDescription,
	  ExeFn newExeFn, bool depSafe = false);
  // Standard ctor.

  inline virtual ~Command();
  // Default dtor.

  virtual string cmd(InterfacedBase & ib, string)
    const throw(InterfaceException);
  // For the object ib execute the memberfunction with 'c' as argument
  // and return the return value.


private:

  ExeFn theExeFn;
  // The pointer to the member function.

};

}

#include "Command.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "Command.tcc"
#endif

#endif /* ThePEG_Command_H */
