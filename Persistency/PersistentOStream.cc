// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PersistentOStream class.
//

#include "PersistentOStream.h"
#include "ThePEG/Utilities/DynamicLoader.h"
#include <fstream>
// #include <pfstream.h>

namespace ThePEG {

PersistentOStream::PersistentOStream(ostream & os)
: theOStream(&os), badState(false), allocStream(false) {
  init();
}

PersistentOStream::PersistentOStream(string file)
  : badState(false), allocStream(true) {
//    if ( file[0] == '|' )
//      theOStream = new opfstream(file.substr(1).c_str());
//    else if ( file.substr(file.length()-3, file.length()) == ".gz" )
//      theOStream = new opfstream(string("gzip > " + file).c_str());
//    else
    theOStream = new ofstream(file.c_str());
  if ( theOStream )
    init();
  else
    setBadState();
}

void PersistentOStream::init() {
  operator<<(string("ThePEG version 1 Database"));
  operator<<(version);
  operator<<(subVersion);
  *this << DynamicLoader::appendedPaths();
  *this << DynamicLoader::prependedPaths();
}

PersistentOStream::~PersistentOStream() {
  if ( allocStream ) delete theOStream;
}

void PersistentOStream::
putObjectPart(tcBPtr obj, const ClassDescriptionBase * db) {
  ClassDescriptionBase::DescriptionVector::const_iterator bit =
    db->descriptions().begin();
  while ( bit != db->descriptions().end() ) {
    putObjectPart(obj, *bit++);
    endBase();
  }
  db->output(obj, *this);
}

PersistentOStream &
PersistentOStream::outputPointer(tcBPtr obj) {
  if ( !good() ) return *this;
  if ( !obj ) return operator<<(0);
  // It it's the  null pointer, just print a zero.

  try {

    // Check if the object has been written before. In that case just write
    // out it's number
    ObjectMap::const_iterator oit = writtenObjects.find(obj);
    if ( oit != writtenObjects.end() ) {
      *this << oit->second;
      return *this;
    }

    // This object hasn't been written before so we write it out, beginning
    // with a number, then the class information, and finally let it write
    // itself on the stream.
    beginObject();
    int oid = writtenObjects.size()+1;
    writtenObjects[obj] = oid;
    *this << oid;
    const ClassDescriptionBase * desc = writeClassId(obj);
    putObjectPart(obj, desc);
    endObject();
  }
  catch (...) {
    setBadState();
  }
  checkState();
  return *this;
}

const ClassDescriptionBase *
PersistentOStream::writeClassId(tcBPtr obj) {
  const ClassDescriptionBase * db = DescriptionList::find(typeid(*obj));
  if ( !db ) {
    throw MissingClass()
      << "PersistentOStream could not find the ClassDescription object "
      << "corresponding to the class " << typeid(*obj).name()
      << ". Please chack that the class has a properly instantiated "
      << "ClassDescription object." << Exception::runerror;
  }
  writeClassDescription(db);
  return db;
}

void PersistentOStream::
writeClassDescription(const ClassDescriptionBase * db) {
  // If objects of this class has been written out before, just write
  // the corresponding number
  ClassMap::iterator cit = writtenClasses.find(db);
  if ( cit != writtenClasses.end() ) {
    operator<<(cit->second);
    return;
  }

  // This class hasn't been written before, so append it to the list of
  // written classes and assign a number to it, before writing the string
  // containing the information
  int cid = writtenClasses.size();
  writtenClasses[db] = cid;
  operator<<(cid);
  operator<<(db->name());
  operator<<(db->version());
  operator<<(DynamicLoader::dlnameversion(db->library()));
  // Now write its base classes or a zero if the base class is PersistentBase.
  operator<<(db->descriptions().size());
  DescriptionVector::const_iterator bit = db->descriptions().begin();
  while ( bit != db->descriptions().end() ) writeClassDescription(*bit++);
}

}
