// -*- C++ -*-
#ifndef ThePEG_PersistentIStream_H
#define ThePEG_PersistentIStream_H
//
// This is the declaration of the <!id>PersistentIStream<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// Read persistent objects from a stream where they were previously
// written using <!class>PersistentOStream<!!class>. Basic types and
// pointers to objects derived from <!id>PersistentBase<!!id> should
// be read in the same order they were written out. If
// <!id>pedantic()<!!id> is true the same classes that wre written out
// must be present in the current program. If <!id>pedantic()<!!id> is
// false, if an object is read for which only a base class is present
// in the current program, only the parts corresponding to the base
// class will be read, and the rest will be gracefully skipped.
//
// Each base class of a given object will be asked to read its
// members tfromthe stream starting from the least derived class going to
// the most derived one. Members may be pointers to other persistent
// objects or basic types or containers of these. The output for each
// object part should be implemented by specializing the
// <!class>ClassTraits<T>::input<!!class> method, which otherwise
// will call the non-virtual <!id>persistentInput<!!id> function of
// the class. Note that for diamond-shaped multiple inheritance
// structures, the virtual base classes will be written out several
// times for the same object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentOStream.html">PersistentOStream.h</a>,
// <a href="http:ClassTraits.html">ClassTraits.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "InputDescription.h"
#include "PersistentIStream.fh"
#include "ThePEG/Utilities/Exception.h"
#include <climits>

namespace ThePEG {

class PersistentIStream {

public:

  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);
  typedef vector<BPtr> ObjectVector;
  typedef vector<const InputDescription *> ClassVector;
  typedef InputDescription::DescriptionVector DescriptionVector;

public:

  inline PersistentIStream(istream &);
  // Constuctor giving an input stream.

  PersistentIStream(string);
  // Constuctor giving a file name to read from or, if the first
  // character in the string is a '|', a program, reading from its
  // standard output. If the filename ends in ".gz" the file is
  // uncompressed with gzip.

  inline ~PersistentIStream();
  // The destructor

  template <typename T>
  inline PersistentIStream & operator>>(RCPtr<T> &);
  template <typename T>
  inline PersistentIStream & operator>>(ConstRCPtr<T> &);
  template <typename T>
  inline PersistentIStream & operator>>(TransientRCPtr<T> &);
  template <typename T>
  inline PersistentIStream & operator>>(TransientConstRCPtr<T> &);
  inline PersistentIStream & operator>>(string &);
  inline PersistentIStream & operator>>(char &);
  inline PersistentIStream & operator>>(signed char &);
  inline PersistentIStream & operator>>(unsigned char &);
  inline PersistentIStream & operator>>(int &);
  inline PersistentIStream & operator>>(unsigned int &);
  inline PersistentIStream & operator>>(long &);
  inline PersistentIStream & operator>>(unsigned long &);
  inline PersistentIStream & operator>>(short &);
  inline PersistentIStream & operator>>(unsigned short &);
  inline PersistentIStream & operator>>(double &);
  inline PersistentIStream & operator>>(float &);
  inline PersistentIStream & operator>>(bool &);
  // operators for extracting built-in types from the stream.

  template <typename Container>
  void getContainer(Container &);
  // Iutput of containers of streamable objects. Argument is a
  // reference to the container and an output iterator for insertions.

  BPtr getObject();
  void getObjectPart(tBPtr obj, const InputDescription * pid);
  const InputDescription * getClass();
  
  inline PersistentIStream & setPedantic();
  inline PersistentIStream & setTolerant();
  // If the stream is set to be tolerant it is allowed to read an object from
  // the stream even if the corresponding class is not known to the running
  // executable, under the condition that a public base class of the unknown
  // class is known. If the stream is set to be pedantic this is not allowed.
  // By default, the stream is pedantic.

  inline bool good() const;
  inline bool operator!() const;
  inline operator bool() const;
  // Check the state of the stream.

  inline bool pedantic() const;

private:

  struct MissingClass {};
  struct MissingObject {};
  struct ReadFailior {};
  // Internal exception classes.

  void init();
  // Internal initialization.

  inline char get();
  // Get the next character from the associated istream.

  inline char escaped();
  // Get the next character from the associated istream and decode it
  // if it is escaped.

  inline void setBadState();
  // Set the stream in a bad state

  inline void getSep();
  // Read a field separator from the stream.

  inline void skipField();
  // Scan the stream for the next field separator.

  inline bool beginObject();
  // Check if the next char to be read is a tBegin marker.

  void endObject();
  // Scan the stream to the end of the current object. If any new object are
  // found these are read prom the stream to ensure that the pointer structure
  // is preserved.

  void endBase();
  // Scan stream for "end base class" marker.

  inline istream & is();
  inline const istream & is() const;
  // Return a (const) reference to the associated stream.

  ObjectVector readObjects;
  // Lists of objects that have been read.

  ClassVector readClasses;
  // Lists of classes and corresponding version strings that have been read.

  istream * theIStream;
  // A pointer to the associated istream.

  bool isPedantic;
  // Pedantic or tolerant. See description of the setPedantic and settolerant
  // methods.

  bool allocStream;
  // True if the associated istream should be deleted when the PersistentIStream
  // is destroyed.

  bool badState;
  // True if no errors has occurred.

  int version;
  int subVersion;

  static const char tBegin = '{';
  static const char tEnd = '}';
  static const char tNext = '|';
  static const char tNull = '\\';
  static const char tSep = '\n';
  static const char tNoSep = 'n';
  static const char tYes = 'y';
  static const char tNo = 'n';
  // The set of special marker characters.

private:

  inline PersistentIStream();
  inline PersistentIStream(const PersistentIStream &);
  inline PersistentIStream & operator=(const PersistentIStream &);
  // Standard ctors and assignment are private and not implemented.

};


inline PersistentIStream & operator>>(PersistentIStream &, PersistentIManip);
// operator for applying manipulators to the stream.
  
inline PersistentIStream & pedantic(PersistentIStream &);
inline PersistentIStream & tolerant(PersistentIStream &);
// The manipulators

template <typename T1, typename T2>
inline PersistentIStream & operator>>(PersistentIStream &, pair<T1,T2> &);
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, map<Key,T,Cmp,A> &);
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &,
				      multimap<Key,T,Cmp,A> &);
template <typename Key, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, set<Key,Cmp,A> &);
template <typename Key, typename Cmp, typename A>
inline PersistentIStream & operator>>(PersistentIStream &,
				      multiset<Key,Cmp,A> &);
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, list<T,A> &);
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, vector<T,A> &);
template <typename T, typename A>
inline PersistentIStream & operator>>(PersistentIStream &, deque<T,A> &);
// Partial specializations for input of std::containers.

}

#include "PersistentIStream.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
#include "PersistentIStream.tcc"
#endif

#endif /* ThePEG_PersistentIStream_H */

