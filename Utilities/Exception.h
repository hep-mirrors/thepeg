// -*- C++ -*-
#ifndef ThePEG_Exception_H
#define ThePEG_Exception_H
//
// This is the declaration of the <!id>Exception<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>Exception<!!id> is the base class for all exceptions to be
// used in ThePEG. It is derived from <!id>std::exception<!!id> and
// adds information about the severity of the exception to indicate to
// the <!class>Repository<!!class> and <!class>EventGenrator<!!class>
// how to act on it.
//
// To throw an exception one should inherit from <!id>Exception<!!id>
// and add information in the constructor of the base
// class. Alternatively one can use the <!id>operator&lt;&lt;<!!id>
// operator on a default constructed <!id>Exception<!!id> to add
// information as for a standard <!id>ostream<!!id> object, in which
// cas one should always end with adding an enum of the type
// <!id>Exception::Severity<!!id> to indicate the severity of the
// exception e.g. <!id>Exception() << "Something went wrong." <<
// Exception::eventerror<!!id>.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Repository.html">Repository.h</a>,
// <a href="http:EventGenrator.html">EventGenrator.h</a>.
// 

#include <exception>
#include "ThePEG/Config/ThePEG.h"
#include "Exception.fh"
#include <string>
#include "ThePEG/Utilities/sstream.h"
#include <iosfwd>

extern "C" {
  void breakThePEG();
}

namespace ThePEG {

class Exception: public exception {

public:

  enum Severity {unknown,  info, warning, eventerror, runerror, maybeabort,
		 abortnow };
  // The levels of severity.
  
public:

  Exception(const string &, Severity);
  // Standard constructor.

  inline Exception();
  inline Exception(const Exception &);
  virtual ~Exception() throw();
  // Default ctors and dtor.

public:

  inline const Exception & operator=(const Exception &);
  inline bool operator==(const Exception &) const;
  inline bool operator<(const Exception &) const;
  // Assignment and comparisons.

public:

  inline virtual const char* what () const throw();
  inline string message() const;
  void writeMessage(ostream & os = *errstream) const;
  // Return the error message or write it to a stream.

  inline Severity severity() const;
  // Return the severity.

  inline void handle() const;
  // Indicate that this exception has been taken care of.

  template <typename T>
  inline Exception & operator<<(const T & t);
  // Add info to the exception message.

  inline Exception & operator<<(Severity sev);
  // Set the severity for the exception.

protected:

  void severity(Severity);
  // set the severity.

  mutable ostringstream theMessage;
  // Stream to write the error message to.

private:

  mutable bool handled;
  // True if this exception has been taken care of.

  Severity theSeverity;
  // The severity.

  static ostream * errstream;
  // The default stream to write the error message if unhandled.

};

}

#include "Exception.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Exception.tcc"
#endif

#endif /* ThePEG_Exception_H */
