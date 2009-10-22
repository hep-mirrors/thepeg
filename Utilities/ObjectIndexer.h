// -*- C++ -*-
//
// ObjectIndexer.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
#ifndef THEPEG_ObjectIndexer_H
#define THEPEG_ObjectIndexer_H
// This is the declaration of the ObjectIndexer class.

#include "ThePEG/Config/ThePEG.h"

namespace ThePEG {

/**
 * This is a templated class which dynamically associates (reference
 * counted) objects to indices.
 */
template <typename IntT, typename ObjT>
class ObjectIndexer {

public:

  ThePEG_DECLARE_TEMPLATE_POINTERS(ObjT,TPtr);

  /** Map of objects to indices */
  typedef map<IntT,tTPtr> IndexObjectMap;

  /** Map of indices to objects. */
  typedef map<TPtr,IntT> ObjectIndexMap;

public:

  /**
   * Return the index for the given object. If the object is not known,
   * a new index will be created.
   */
  IntT operator()(tTPtr o) {
    typename ObjectIndexMap::iterator it = objectIndex.find(o);
    if ( it == objectIndex.end() ) {
      IntT i = 0;
      while ( indexObject.find(i) != indexObject.end() ) ++i;
      objectIndex[o] = i;
      indexObject[i] = o;
      return i;
    } else
      return it->second;
  }

  /**
   * Return the object for the given index. If the index is not known,
   * a new object will be (default) created.
   */
  tTPtr operator()(IntT i) {
    typename IndexObjectMap::iterator it = indexObject.find(i);
    if ( it == indexObject.end() ) {
      TPtr o = new_ptr<ObjT>();
      objectIndex[o] = i;
      indexObject[i] = o;
      return o;
    } 
    else
      return it->second;
  }

  /**
   * Return the object for the given index. If the index is not known,
   * a null pointer will be returned.
   */
  tTPtr operator()(IntT i) const {
    return find(i);
  }

  /**
   * Return the object for the given index. If the index is not known,
   * a null pointer will be returned.
   */
  tTPtr find(IntT i) const {
    typename IndexObjectMap::const_iterator it = indexObject.find(i);
    return it == indexObject.end()? tTPtr(): it->second;
  }

  /**
   * Associate the given object with the given index. Possible other
   * associations involving the index or the object is removed.
   */
  void operator()(IntT i, tTPtr o) {
    typename IndexObjectMap::iterator iit = indexObject.find(i);
    if ( iit != indexObject.end() ) objectIndex.erase(iit->second);
    typename ObjectIndexMap::iterator oit = objectIndex.find(o);
    if ( oit != objectIndex.end() ) indexObject.erase(oit->second);
    objectIndex[o] = i;
    indexObject[i] = o;
  }

  /**
   * Return true if the given object is known.
   */
  bool included(tTPtr o) const {
    return objectIndex.find(o) != objectIndex.end();
  }

  /**
   * Return true if the given index is known.
   */
  bool included(IntT i) const {
    return indexObject.find(i) != indexObject.end();
  }

  /**
   * Remove all associations.
   */
  void clear() {
    indexObject.clear();
    objectIndex.clear();
  }

  /**
   * Return true if no associations has been made.
   */
  bool empty() const {
    return indexObject.empty() && objectIndex.empty();
  }

private:

  /**
   * All known objects keyed by their indices.
   */
  IndexObjectMap indexObject;

  /**
   * All known indices keyed by the corresponding objects.
   */
  ObjectIndexMap objectIndex;

private:

  /**
   * Private and non-existent assignment operator.
   */
  ObjectIndexer & operator=(const ObjectIndexer &);

};

}

#endif /* THEPEG_ObjectIndexer_H */
