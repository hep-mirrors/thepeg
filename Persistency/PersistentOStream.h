// -*- C++ -*-
#ifndef ThePEG_PersistentOStream_H
#define ThePEG_PersistentOStream_H
// This is the declaration of the PersistentOStream class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Config/Complex.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Exception.h"
#include "PersistentOStream.fh"
#include "PersistentOStream.xh"

namespace ThePEG {

/**
 * <code>PersistentOStream</code> is used to write objects persistently
 * to a stream from which they can be read in again with a
 * PersistentIStream. Pointers to objects of classes
 * derived from <code>PersistentBase</code> may be written out if a
 * static ClassDescription object is present for the
 * class. Also basic types may be written to the stream, as well as
 * containers of pointers to persistent objects and basic types.
 *
 * The <code>PersistentOStream</code> keeps a list of all pointers to
 * written persistent objects, so that if several pointers to the
 * smame object is written, the object will only be written once.
 *
 * Each base class of a given object will be asked to write its
 * members to the stream starting from the least derived class going to
 * the most derived one. Members may be pointers to other persistent
 * objects or basic types or containers of these. The output for each
 * object part should be implemented by specializing the
 * ClassTraits<T>::output method, which otherwise
 * will call the non-virtual <code>persistentOutput</code> function of
 * the class. Note that for diamond-shaped multiple inheritance
 * structures, the virtual base classes will be written out several
 * times for the same object.
 *
 * @see PersistentIStream,
 * @see ClassDescription,
 * @see ClassTraits.
 */
class PersistentOStream {

public:

  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);
  ThePEG_DECLARE_MAP(cBPtr, int, ObjectMap);
  ThePEG_DECLARE_MAP(const ClassDescriptionBase *, int, ClassMap);

  /** A vector of bare pointers to InputDescription objects. */
  typedef ClassDescriptionBase::DescriptionVector DescriptionVector;

public:

  /**
   * Constuctor giving an output stream.
   */
  PersistentOStream(ostream &);

  /**
   * Constuctor giving a file name to read. If the first
   * character in the string is a '|', the corresponding program is
   * run and its standard input is used instead. If the filename ends
   * in ".gz" the file is compressed with gzip.
   */
  PersistentOStream(string);

  /**
   * The destructor
   */
  ~PersistentOStream();

  /**
   * Operator for writing persistent objects to the stream.
   * @param p a pointer to the object to be written.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentOStream & operator<<(const RCPtr<T> &);

  /**
   * Operator for writing persistent objects to the stream.
   * @param p a pointer to the object to be written.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentOStream & operator<<(const ConstRCPtr<T> &);

  /**
   * Operator for writing persistent objects to the stream.
   * @param p a pointer to the object to be written.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentOStream & operator<<(const TransientRCPtr<T> &);

  /**
   * Operator for writing persistent objects to the stream.
   * @param p a pointer to the object to be written.
   * @return a reference to the stream.
   */
  template <typename T>
  inline PersistentOStream & operator<<(const TransientConstRCPtr<T> &);

  /** @name Operators for extracting built-in types from the stream. */
  //@{
  /**
   * Write a character string.
   */
  inline PersistentOStream & operator<<(string);

  /**
   * Write a character.
   */
  inline PersistentOStream & operator<<(char);

  /**
   * Write a signed character.
   */
  inline PersistentOStream & operator<<(signed char);

  /**
   * Write an unsigned character.
   */
  inline PersistentOStream & operator<<(unsigned char);

  /**
   * Write an integer.
   */
  inline PersistentOStream & operator<<(int);

  /**
   * Write an unsigned integer.
   */
  inline PersistentOStream & operator<<(unsigned int);

  /**
   * Write a long integer.
   */
  inline PersistentOStream & operator<<(long);

  /**
   * Write an unsigned long integer.
   */
  inline PersistentOStream & operator<<(unsigned long);

  /**
   * Write a short integer.
   */
  inline PersistentOStream & operator<<(short);

  /**
   * Write an unsigned short integer.
   */
  inline PersistentOStream & operator<<(unsigned short);

  /**
   * Write a double.
   */
  inline PersistentOStream & operator<<(double);

  /**
   * Write a float.
   */
  inline PersistentOStream & operator<<(float);

  /**
   * Write a boolean.
   */
  inline PersistentOStream & operator<<(bool);

  /**
   * Write a Complex.
   */
  inline PersistentOStream & operator<<(Complex);
  //@}

  /**
   * Output of containers of streamable objects.
   */
  template <typename Container>
  inline void putContainer(const Container & c);

  /**
   * Write out a persistent object given a pointer to it.
   */
  PersistentOStream & outputPointer(tcBPtr);

  /**
   * For a given object, write the member variables corresponding to a
   * given InputDescription object.
   * @param obj the object to be written.
   * @param pid a pointer to an InputDescription describing the
   * (sub)class to written.
   */
  void putObjectPart(tcBPtr, const ClassDescriptionBase *);

  /**
   * Remove all objects that have been written, except those which are
   * to be saved, from the list of written objects.
   */
  inline PersistentOStream & flush();

  /**
   * Instuct the stream to save the following objects (protecting them from
   * being flushed).
   */
  inline PersistentOStream & push();

  /**
   * Instuct the stream not to save the following objects.
   */
  inline PersistentOStream & pop();

  /**
   * Check the state of the stream.
   */
  inline bool good() const;

  /**
   * Check the state of the stream.
   */
  inline operator bool() const;

  /**
   * Check the state of the stream.
   */
  inline bool operator!() const;

private:

  /**
   * Internal exception class.
   */
  struct MissingClass {};

  /**
   * The version of this PersistentOStream implementation.
   */
  static const int version = 0;

  /**
   * The subversion of this PersistentOStream implementation.
   */
  static const int subVersion = 0;

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
  /**
   * The special marker character indicating an escaped marker character.
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

  /**
   * Return true if the given character is aspecial marker character.
   */
  bool isToken(char c) const;

  /**
   * Set the stream in a bad state.
   */
  inline void setBadState();

  /**
   * Check if the state is ok.
   */
  inline void checkState();

  /**
   * Write out class information to the associated ostream.
   */
  const ClassDescriptionBase * writeClassId(tcBPtr);

  /**
   * write out class information to the associated ostream.
   */
  void writeClassDescription(const ClassDescriptionBase *);

  /**
   * Put a "begin object" marker on the associated ostream
   */
  inline void beginObject();

  /**
   * Put a "end of object" marker on the associated ostream
   */
  inline void endObject();

  /**
   * Put an "next base class" marker on the associated ostream
   */
  inline void endBase();

  /**
   * Put a character on the associated ostream
   */
  inline void put(char);

  /**
   * Put a character on the associated ostream but escape it if it is
   * a token.
   */
  inline void escape(char c);

  /**
   * Return a reference to the associated ostream.
   */
  inline ostream & os();

  /**
   * Return a const reference to the associated ostream.
   */
  inline const ostream & os() const;

  /**
   * Write out initial metainfo on the stream.
   */
  void init();

  /**
   * List of written objects.
   */
  ObjectMap writtenObjects;

  /**
   * List of written objects that are to be saved.
   */
  stack<int> lastSavedObject;

  /**
   * List of written classes.
   */
  ClassMap writtenClasses;

  /**
   * A pointer to the associated ostream.
   */
  ostream * theOStream;

  /**
   * True if no errors has occurred.
   */
  bool badState;

  /**
   * True if the associated ostream should be deleted in the destructor.
   */
  bool allocStream;

private:

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentOStream();

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentOStream(const PersistentOStream &);

  /**
   * Standard ctors and assignment are private and not implemented.
   */
  inline PersistentOStream & operator=(const PersistentOStream &);

};

/**
 * Operator for applying manipulators to the stream.
 */
inline PersistentOStream &
operator<<(PersistentOStream & os, PersistentOManip func);

/**
 * The manipulator for calling PersistentOStream::flush().
 */
inline PersistentOStream & flush(PersistentOStream & os);

/**
 * The manipulator for calling PersistentOStream::push().
 */
inline PersistentOStream & push(PersistentOStream & os);

/**
 * The manipulator for calling PersistentOStream::pop().
 */
inline PersistentOStream & pop(PersistentOStream & os);


/**
 * @name Partial specializations of operator<< for output of
 * std::containers.
 */
//@{
/** Output a pair of objects. */
template <typename T1, typename T2>
inline PersistentOStream & operator<<(PersistentOStream &, const pair<T1,T2> &);

/**
 * Output a multimap of key/object pairs.
 */
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const multimap<Key,T,Cmp,A> &);
/**
 * Output a map of key/object pairs.
 */
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const map<Key,T,Cmp,A> &);

/**
 * Output a set of objects.
 */
template <typename Key, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const set<Key,Cmp,A> &);

/**
 * Output a multiset of objects.
 */
template <typename Key, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const multiset<Key,Cmp,A> &);

/**
 * Output a list of objects.
 */
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const list<T,A> &);

/**
 * Output a vector of objects.
 */
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const vector<T,A> &);

/**
 * Output a deque of objects.
 */
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const deque<T,A> &);
//@}

}

#include "PersistentOStream.icc"

#endif /* ThePEG_PersistentOStream_H */

