// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the PersistentIStream class.
//

#include "PersistentIStream.h"
#include "PersistentOStream.xh"
#include "PersistentIStream.xh"
#include "ThePEG/Utilities/DynamicLoader.h"
#include "ThePEG/Utilities/sstream.h"
#include <fstream>
//#include <pfstream.h>

namespace ThePEG {

PersistentIStream::PersistentIStream(string file) 
: theIStream(0), isPedantic(true), allocStream(true), badState(false) {
//    if ( file[0] == '|' )
//      theIStream = new ipfstream(file.substr(1).c_str());
//    else if ( file.substr(file.length()-3, file.length()) == ".gz" )
//      theIStream = new ipfstream(string("gzip -d -c " + file).c_str());
//    else
    theIStream = new ifstream(file.c_str());
  if ( theIStream ) {
    init();
  } else
    setBadState();
}

void PersistentIStream::init() {
  string tag;
  operator>>(tag);
  if ( tag != "ThePEG version 1 Database" ) setBadState();
  operator>>(version);
  operator>>(subVersion);
}

void PersistentIStream::endObject() {
  // We have just read an object, but we may only have acces to a base class
  // of the originally written object. Therefore we must skip everything that
  // the unknown derived class may have written. So we check one field at
  // the time...
  while ( good() ) {
    switch ( is().peek() ) {
    case tEnd:
      // OK we found the end of the object, let's quit
      get();
      return;
    case tBegin:
      // it seems there is an object next on the stream. We read it in and
      // add it to the list of orphans
      getObject();
      break;
    case tSep:
    case tNext:
      // This was a field separator, check next char;
      get();
      break;
    default:
      // Just an ordinary character, this means we are in a field,
      // skip to the end of the field.
      skipField();
    }
  };
}

void PersistentIStream::endBase() {
  // We have just read an object part, but we may only have acces to a
  // base class of the originally written object. Therefore we must
  // skip everything that the unknown derived class may have
  // written. So we check one field at the time...
  if ( is().peek() != tNext && pedantic() ) throw ReadFailior();
  while ( good() ) {
    switch ( is().peek() ) {
    case tNext:
      // This is what we are looking for. 
      get();
      return;
    case tSep:
      // This was a field separator, check next char;
      get();
      break;
    case tBegin:
      // it seems there is an object next on the stream. We read it in and
      // add it to the list of orphans
      getObject();
      break;
    case tEnd:
      // OOPS we found the end of an object, something went wrong, let's quit
      throw ReadFailior();
    default:
      // Just an ordinary character, this means we are in a field,
      // skip to the end of the field.
      skipField();
    }
  }
}

PersistentIStream::BPtr PersistentIStream::getObject() {
  BPtr obj;
  if ( !good() ) return obj;
  ObjectVector::size_type oid;
  try {
    if ( !beginObject() ) {
      *this >> oid;
      if ( !oid ) return obj;
      if ( oid <= readObjects.size() ) return readObjects[oid-1];
      throw MissingObject();
    }
    get();
    *this >> oid;
    if ( oid > readObjects.size() + 1 ) throw MissingObject();
    const InputDescription * pid = getClass();
    obj = pid->create();
    readObjects.erase(readObjects.begin()+oid-1, readObjects.end());
    readObjects.push_back(obj);
    getObjectPart(obj, pid);
    endObject();
    return obj;
  }
  catch (...) {
    setBadState();
    if ( pedantic() ) throw;
    return obj;
  }
}
  
void PersistentIStream::
getObjectPart(tBPtr obj, const InputDescription * pid) {
  DescriptionVector::const_iterator bit = pid->descriptions().begin();
  while ( bit != pid->descriptions().end() ) {
    getObjectPart(obj, *bit++);
    endBase();
  }
  pid->input(obj, *this);
}

const InputDescription * PersistentIStream::getClass() {
  unsigned int cid;
  operator>>(cid);
  if ( cid < readClasses.size() ) return readClasses[cid];
  if ( cid != readClasses.size() ) throw MissingClass();
  string className;
  operator>>(className);
  int version;
  string libraries;
  operator>>(version);
  operator>>(libraries);
  InputDescription * id = new InputDescription(className, version);
  readClasses.push_back(id);
  int nBase;
  operator>>(nBase);
  while ( nBase-- ) id->addBaseClass(getClass());
  const ClassDescriptionBase * db = DescriptionList::find(className);
  if ( !db && libraries.length() ) {
    istringstream is(libraries);
    string library;
    while ( is >> library ) DynamicLoader::load(library);
  }
  db = DescriptionList::find(className);
  if ( pedantic() && !db ) throw MissingClass();
  id->setDescription(db);
  return id;
}

}
