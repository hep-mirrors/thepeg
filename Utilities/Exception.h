// -*- C++ -*-
#ifndef ThePEG_Exception_H
#define ThePEG_Exception_H
// This is the declaration of the Exception class.

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

/**
 * <code>Exception</code> is the base class for all exceptions to be
 * used in ThePEG. It is derived from <code>std::exception</code> and
 * adds information about the severity of the exception to indicate to
 * the Repository and EventGenrator how to act on it.
 *
 * To throw an exception one should inherit from
 * <code>Exception</code> and add information in the constructor of
 * the base class. Alternatively one can use the <code>operator<<
 * </code> operator on a default constructed <code>Exception</code> to
 * add information as for a standard <code>ostream</code> object, in
 * which case one should always end with adding an enum of the type
 * <code>Exception::Severity</code> to indicate the severity of the
 * exception e.g.<br> <code>Exception() << "Something went wrong." <<
 * Exception::eventerror</code>.
 *
 * @see Repository,
 * @see EventGenrator. 
 */
class Exception: public exception {

public:

  /**
   * The levels of severity.
   */
  enum Severity {unknown,    /** Unknown severity */
		 info,       /** Not severe. But the user should be
			      *  informed. */
		 warning,    /** Possibly severe. The user should be
			      *  warned. */
		 eventerror, /** Severe error. The event being
			      *  generated should be discarded. */
		 runerror,   /** Severe error. The run should be
			      *  terminated */
		 maybeabort, /** Severe error. The run should be
			      *  terminated, possibly dumping core. */
		 abortnow    /** Severe error. The run is aborted
			      *  immediately, before the exception is
			      *  thrown. */
  };
  
public:

  /**
   * Standard constructor.
   * @param str an error message.
   * @param sev the severity.
   */
  Exception(const string & str, Severity sev);

  /**
   * Default constructor.
   */
  inline Exception();

  /**
   * The copy constructor.
   */
  inline Exception(const Exception &);

  /**
   * The destructor
   */
  virtual ~Exception() throw();

public:

  /**
   * Assignment.
   */
  inline const Exception & operator=(const Exception &);

  /**
   * Comparison
   */
  inline bool operator==(const Exception &) const;

  /**
   * Compare severity. If equal compare error message
   * lexicographically.
   */
  inline bool operator<(const Exception &) const;

public:

  /**
   * Return the error message.
   */
  inline virtual const char* what () const throw();

  /**
   * Return the error message.
   */
  inline string message() const;

  /**
   * Write the error message to a stream.
   */
  void writeMessage(ostream & os = *errstream) const;

  /**
   * Return the severity.
   */
  inline Severity severity() const;

  /**
   * Indicate that this exception has been taken care of.
   */
  inline void handle() const;

  /**
   * Add info to the exception message.
   */
  template <typename T>
  inline Exception & operator<<(const T & t);

  /**
   * Set the severity for the exception.
   */
  inline Exception & operator<<(Severity sev);

protected:

  /**
   * set the severity.
   */
  void severity(Severity);

  /**
   * Stream to write the error message to.
   */
  mutable ostringstream theMessage;

private:

  /**
   * True if this exception has been taken care of.
   */
  mutable bool handled;

  /**
   * The severity.
   */
  Severity theSeverity;

  /**
   * The default stream to write the error message if unhandled.
   */
  static ostream * errstream;

};

}

#include "Exception.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Exception.tcc"
#endif

#endif /* ThePEG_Exception_H */
