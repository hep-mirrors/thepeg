// -*- C++ -*-
#ifndef ThePEG_PersistentOStream_H
#define ThePEG_PersistentOStream_H
//
// This is the declaration of the <!id>PersistentOStream<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>PersistentOStream<!!id> is used to write objects persistently
// to a stream from which they can be read in again with a
// <!class>PersistentIStream<!!class>. Pointers to objects of classes
// derived from <!id>PersistentBase<!!id> may be written out if a
// static <!class>ClassDescription<!!class> object is present for the
// class. Also basic types may be written to the stream, as well as
// containers of pointers to persistent objects and basic types.
//
// The <!id>PersistentOStream<!!id> keeps a list of all pointers to
// written persistent objects, so that if several pointers to the
// smame object is written, the object will only be written once.
//
// Each base class of a given object will be asked to write its
// members to the stream starting from the least derived class going to
// the most derived one. Members may be pointers to other persistent
// objects or basic types or containers of these. The output for each
// object part should be implemented by specializing the
// <!class>ClassTraits<T>::output<!!class> method, which otherwise
// will call the non-virtual <!id>persistentOutput<!!id> function of
// the class. Note that for diamond-shaped multiple inheritance
// structures, the virtual base classes will be written out several
// times for the same object.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:PersistentIStream.html">PersistentIStream.h</a>,
// <a href="http:ClassDescription.html">ClassDescription.h</a>,
// <a href="http:ClassTraits.html">ClassTraits.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/Utilities/ClassDescription.h"
#include "ThePEG/Utilities/Exception.h"
#include "PersistentOStream.fh"
#include "PersistentOStream.xh"

namespace ThePEG {

class PersistentOStream {

public:

  ThePEG_DECLARE_POINTERS(PersistentBase,BPtr);
  //  typedef map<cBPtr, int> ObjectMap;
  //  typedef map<const ClassDescriptionBase *, int> ClassMap;
  ThePEG_DECLARE_MAP(cBPtr, int, ObjectMap);
  ThePEG_DECLARE_MAP(const ClassDescriptionBase *, int, ClassMap);
  typedef ClassDescriptionBase::DescriptionVector DescriptionVector;

public:

  PersistentOStream(ostream &);
  // Constuctor giving an output stream.

  PersistentOStream(string);
  // Constuctor giving a file name to read from or, if the first
  // character in the string is a '|', a program to which the stream
  // is piped. If the filename ends in ".gz" the file is compressed
  // with gzip.

  ~PersistentOStream();
  // The destructor

  template <typename T>
  inline PersistentOStream & operator<<(const RCPtr<T> &);
  template <typename T>
  inline PersistentOStream & operator<<(const ConstRCPtr<T> &);
  template <typename T>
  inline PersistentOStream & operator<<(const TransientRCPtr<T> &);
  template <typename T>
  inline PersistentOStream & operator<<(const TransientConstRCPtr<T> &);
  inline PersistentOStream & operator<<(char);
  inline PersistentOStream & operator<<(signed char);
  inline PersistentOStream & operator<<(unsigned char);
  inline PersistentOStream & operator<<(int);
  inline PersistentOStream & operator<<(unsigned int);
  inline PersistentOStream & operator<<(long);
  inline PersistentOStream & operator<<(unsigned long);
  inline PersistentOStream & operator<<(short);
  inline PersistentOStream & operator<<(unsigned short);
  inline PersistentOStream & operator<<(double);
  inline PersistentOStream & operator<<(float);
  inline PersistentOStream & operator<<(bool);
  inline PersistentOStream & operator<<(string);
  // operators for output of built-in types to the stream.

  template <typename Container>
  inline void putContainer(const Container & c);
  // Output of containers of streamable objects.

  PersistentOStream & outputPointer(tcBPtr);

  void putObjectPart(tcBPtr, const ClassDescriptionBase *);

  inline PersistentOStream & flush();
  // Remove all objects that have been written, except those which are
  // to be saved, from the list of written objects.

  inline PersistentOStream & push();
  // Instuct the stream to save the following objects (protecting them from
  // being flushed).

  inline PersistentOStream & pop();
  // Instuct the stream not to save the following objects.

  inline bool good() const;
  inline operator bool() const;
  inline bool operator!() const;
  // Check the state of the stream.

private:

  struct MissingClass {};
  // Internal exception classes.

  static const int version = 0;
  static const int subVersion = 0;
  static const char tBegin = '{';
  static const char tEnd = '}';
  static const char tNext = '|';
  static const char tNull = '\\';
  static const char tSep = '\n';
  static const char tNoSep = 'n';
  static const char tYes = 'y';
  static const char tNo = 'n';
  // The set of special marker characters.

  bool isToken(char c) const;

  inline void setBadState();
  // Set the stream in a bad state.

  inline void checkState();
  // Check if the state is ok.

  const ClassDescriptionBase * writeClassId(tcBPtr);
  void writeClassDescription(const ClassDescriptionBase *);
  // write out class information to the associated ostream.

  inline void beginObject();
  // Put a "begin object" marker on the associated ostream

  inline void endObject();
  // Put a "end of object" marker on the associated ostream

  inline void endBase();
  // Put an "next base class" marker on the associated ostream

  inline void put(char);
  // Put a character on the associated ostream

  inline void escape(char c);
  // Put a character on the associated ostream but escape it if it is
  // a token.

  inline ostream & os();
  inline const ostream & os() const;
  // Return a reference to the associated ostream.

  void init();
  // Write out initial metainfo on the stream.

  ObjectMap writtenObjects;
  // List of written objects.

  stack<int> lastSavedObject;
  // List of written objects that are to be saved.

  ClassMap writtenClasses;
  // List of written classes.

  ostream * theOStream;
  // A pointer to the associated ostream.

  bool badState;
  // True if no errors has occurred.

  bool allocStream;
  // True if the associated ostream should be deleted in the destructor.

private:

  inline PersistentOStream();
  inline PersistentOStream(const PersistentOStream &);
  inline PersistentOStream & operator=(const PersistentOStream &);
  // Standard ctors and assignment are private and not implemented.

};

inline PersistentOStream &
operator<<(PersistentOStream & os, PersistentOManip func);
inline PersistentOStream & flush(PersistentOStream & os);
inline PersistentOStream & push(PersistentOStream & os);
inline PersistentOStream & pop(PersistentOStream & os);
// The manipulators


template <typename T1, typename T2>
inline PersistentOStream & operator<<(PersistentOStream &, const pair<T1,T2> &);

template <typename Key, typename T, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const multimap<Key,T,Cmp,A> &);
template <typename Key, typename T, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const map<Key,T,Cmp,A> &);
template <typename Key, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const set<Key,Cmp,A> &);
template <typename Key, typename Cmp, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const multiset<Key,Cmp,A> &);
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const list<T,A> &);
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const vector<T,A> &);
template <typename T, typename A>
inline PersistentOStream & operator<<(PersistentOStream &,
				      const deque<T,A> &);
// Output of standard container classes.

}

#include "PersistentOStream.icc"

#endif /* ThePEG_PersistentOStream_H */

