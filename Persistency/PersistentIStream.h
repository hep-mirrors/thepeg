// -*- C++ -*-
#ifndef ThePEG_PersistentIStream_H
#define ThePEG_PersistentIStream_H
// This is the declaration of the PersistentIStream class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "InputDescription.h"
#include "PersistentIStream.fh"
#include "ThePEG/Utilities/Exception.h"
#include <climits>

namespace ThePEG {

/** \ingroup Persistency
 * PersistentIStream is used to read persistent objects from a stream
 * where they were previously written using PersistentOStream. Basic
 * types and pointers to objects derived from
 * <code>PersistentBase</code> should be read in the same order they
 * were written out. If <code>pedantic()</code> is true the same
 * classes that were written out must be present in the current
 * program. If <code>pedantic()</code> is false anf if an object is
 * read for which only a base class is present in the current program,
 * only the parts corresponding to the base class will be read, and
 * the rest will be gracefully skipped.
 *
 * Each base class of a given object will be asked to read its
 * members from the stream starting from the least derived class going to
 * the most derived one. Members may be pointers to other persistent
 * objects or basic types or containers of these. The output for each
 * object part should be implemented by specializing the
 * ClassTraits<T>::input method, which otherwise
 * will call the non-virtual <code>persistentInput</code> function of
 * the class. Note that for diamond-shaped multiple inheritance
 * structures, the virtual base classes will be written out several
 * times for the same object.
 *
 * @see PersistentOStream,
 * @see ClassTraits.
 */
class PersistentIStream {

public:

  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);

  /** A vector of pointers to persistent objects */
  typedef vector<BPtr> ObjectVector;

  /** A vector of bare pointers to InputDescription objects. */
  typedef InputDescription::DescriptionVector DescriptionVector;

public:

  /**
   * Constuctor giving an input stream to be used as an underlying
   * istream.
   */
  inline PersistentIStream(istream &);

  /**
   * Constuctor giving a file name to read from. If the first
   * character in the string is a '|', the corresponding program is
   * run and its standard output is used instead. If the filename ends
   * in ".gz" the file is uncompressed with gzip.
   */
  PersistentIStream(string);

  /**
   * The destructor.
   */
  inline ~PersistentIStream();

  /**
   * Operator for extracting persistent objects from the stream.
   * @param p this pointer will refer to the extracted object.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentIStream & operator>>(RCPtr<T> & p);

  /**
   * Operator for extracting persistent objects from the stream.
   * @param p this pointer will refer to the extracted object.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentIStream & operator>>(ConstRCPtr<T> & p);

  /**
   * Operator for extracting persistent objects from the stream.
   * @param p this pointer will refer to the extracted object.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentIStream & operator>>(TransientRCPtr<T> & p);

  /**
   * Operator for extracting persistent objects from the stream.
   * @param p this pointer will refer to the extracted object.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentIStream & operator>>(TransientConstRCPtr<T> & p);

  /** @name Operators for extracting built-in types from the stream. */
  //@{
  /**
   * Read a character string.
   */
  inline PersistentIStream & operator>>(string &);

  /**
   * Read a character.
   */
  inline PersistentIStream & operator>>(char &);

  /**
   * Read a signed character.
   */
  inline PersistentIStream & operator>>(signed char &);

  /**
   * Read an unsigned character.
   */
  inline PersistentIStream & operator>>(unsigned char &);

  /**
   * Read an integer.
   */
  inline PersistentIStream & operator>>(int &);

  /**
   * Read an unsigned integer.
   */
  inline PersistentIStream & operator>>(unsigned int &);

  /**
   * Read a long integer.
   */
  inline PersistentIStream & operator>>(long &);

  /**
   * Read an unsigned long integer.
   */
  inline PersistentIStream & operator>>(unsigned long &);

  /**
   * Read a short integer.
   */
  inline PersistentIStream & operator>>(short &);

  /**
   * Read an unsigned short integer.
   */
  inline PersistentIStream & operator>>(unsigned short &);

  /**
   * Read a double.
   */
  inline PersistentIStream & operator>>(double &);

  /**
   * Read a float.
   */
  inline PersistentIStream & operator>>(float &);

  /**
   * Read a bool.
   */
  inline PersistentIStream & operator>>(bool &);

  /**
   * Read a Complex.
   */
  inline PersistentIStream & operator>>(Complex &);

  //@}

  /**
   * Intput of containers streamable objects.
   * @param c the container into which objects are added.
   */
  template <typename Container>
  void getContainer(Container & c);

  /**
   * Read in an object. Create an object and read its data from the
   * stream.
   * @return a pointer to the read object.
   */
  BPtr getObject();

  /**
   * For a given object, read the member variables corresponding to a
   * given InputDescription object.
   * @param obj the object to be read into.
   * @param pid a pointer to an InputDescription describing the
   * (sub)class to be read.
   */
  void getObjectPart(tBPtr obj, const InputDescription * pid);

  /**
   * Read a class description from the underlying stream and return a
   * corresponding InputDescription object
   */
  const InputDescription * getClass();
  
  /**
   * Set pedantic mode.  If the stream is set to be tolerant it is
   * allowed to read an object from the stream even if the
   * corresponding class is not known to the running executable, under
   * the condition that a public base class of the unknown class is
   * known. If the stream is set to be pedantic this is not allowed.
   * By default, the stream is pedantic.
   */
  inline PersistentIStream & setPedantic();
  /**
   * Set tolerant mode.  If the stream is set to be tolerant it is
   * allowed to read an object from the stream even if the
   * corresponding class is not known to the running executable, under
   * the condition that a public base class of the unknown class is
   * known. If the stream is set to be pedantic this is not allowed.
   * By default, the stream is pedantic.
   */
  inline PersistentIStream & setTolerant();

  /**
   * Check the state of the stream.
   */
  inline bool good() const;

  /**
   * Check the state of the stream.
   */
  inline bool operator!() const;

  /**
   * Check the state of the stream.
   */
  inline operator bool() const;

  /**
   * Check the tolerance. Returns true if setPedantic() has been
   * called or if not setTolerant() has been called.
   */
  inline bool pedantic() const;

private:

  /** \ingroup Persistency Thrown if a class is missing */
  struct MissingClass {};

  /** \ingroup Persistency Thrown if an object which should have been
      read in is missing. */
  struct MissingObject {};

  /** \ingroup Persistency Thrown if reading from the stream failed
      for some reason. */
  struct ReadFailior {};

  /**
   * Internal initialization.
   */
  void init();

  /**
   * Get the next character from the associated istream.
   */
  inline char get();

  /**
   * Get the next character from the associated istream and decode it
   * if it is escaped.
   */
  inline char escaped();

  /**
   * Set the stream in a bad state
   */
  inline void setBadState();

  /**
   * Read a field separator from the stream.
   */
  inline void getSep();

  /**
   * Scan the stream for the next field separator.
   */
  inline void skipField();

  /**
   * Check if the next char to be read is a tBegin marker.
   */
  inline bool beginObject();

  /**
   * Scan the stream to the end of the current object. If any new object are
   * found these are read prom the stream to ensure that the pointer structure
   * is preserved.
   */
  void endObject();

  /**
   * Scan stream for "end base class" marker.
   */
  void endBase();

  /**
   * Return a reference to the associated stream.
   */
  inline istream & is();

  /**
   * Return a const reference to the associated stream.
   */
  inline const istream & is() const;

  /**
   * Lists of objects that have been read.
   */
  ObjectVector readObjects;

  /**
   * Lists of classes and corresponding version strings that have been read.
   */
  DescriptionVector readClasses;

  /**
   * A pointer to the associated istream.
   */
  istream * theIStream;

  /**
   * Pedantic or tolerant. See description of the setPedantic() and
   * setTolerant() methods.
   */
  bool isPedantic;

  /**
   * True if the associated istream should be deleted when the PersistentIStream
   * is destroyed.
   */
  bool allocStream;

  /**
   * True if no errors has occurred.
   */
  bool badState;

  /** Version number of the PersistentOStream which has written the
   *  file being read. */
  int version;

  /** Subversion number of the PersistentOStream which has written the
   *  file being read. */
  int subVersion;

  /** @name Special marker characters */
  //@{
  /**
   * The special marker character indicating the beginning of an object.
   */
  static const char tBegin = '{';

  /**
   * The special marker character indicating the end of an object.
   */
  static const char tEnd = '}';

  /**
   * The marker character indicating the beginning of the next base
   * class in case of multiple inheritance.
   */
  static const char tNext = '|';

  /**
   * The special marker character indicating an escaped marker character.
   */
  static const char tNull = '\\';

  /**
   * The special marker character indicating the end of a value.
   */
  static const char tSep = '\n';

  /**
   * The special marker character used to avoid confusion with escaped
   * tSep markers.
   */
  static const char tNoSep = 'n';

  /**
   * The special marker character indicating a true boolean value.
   */
  static const char tYes = 'y';

  /**
   * The special marker character indicating a false boolean value.
   */
  static const char tNo = 'n';
  //@}

private:

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentIStream();

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentIStream(const PersistentIStream &);

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentIStream & operator=(const PersistentIStream &);

};


/**
 * Operator for applying manipulators to the stream.
 */
inline PersistentIStream & operator>>(PersistentIStream &, PersistentIManip);
  
/**
 * The manipulator for setting pedantic mode.
 */
inline PersistentIStream & pedantic(PersistentIStream &);

/**
 * The manipulator for setting tolerant mode.
 */
inline PersistentIStream & tolerant(PersistentIStream &);

/**
 * @name Partial specializations of operator>> for input of
 * std::containers.
 */
//@{
/** Input a pair of objects. */
template <typename T1, typename T2>
inline PersistentIStream & operator>>(PersistentIStream &, pair<T1,T2> &);

/** Input a map of key/objects pairs. */
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, map<Key,T,Cmp,A> &);

/** Input a multimap of key/objects pairs. */
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &,
				      multimap<Key,T,Cmp,A> &);

/** Input a set of objects. */
template <typename Key, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, set<Key,Cmp,A> &);

/** Input a multoset of objects. */
template <typename Key, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &,
				      multiset<Key,Cmp,A> &);

/** Input a list of objects. */
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, list<T,A> &);

/** Input a vector of objects. */
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, vector<T,A> &);

/** Input a deque of objects. */
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, deque<T,A> &);

}

#include "PersistentIStream.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "PersistentIStream.tcc"
#endif

#endif /* ThePEG_PersistentIStream_H */

