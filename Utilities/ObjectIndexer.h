// -*- C++ -*-
#ifndef THEPEG_ObjectIndexer_H
#define THEPEG_ObjectIndexer_H
// This is the declaration of the ObjectIndexer class.

#include "ThePEG/Config/ThePEG.h"
// #include "ObjectIndexer.fh"
// #include "ObjectIndexer.xh"

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
  inline IntT operator()(tTPtr o);

  /**
   * Return the object for the given index. If the index is not known,
   * a new object will be (default) created.
   */
  inline tTPtr operator()(IntT i);

  /**
   * Return the object for the given index. If the index is not known,
   * a null pointer will be returned.
   */
  inline tTPtr operator()(IntT i) const;

  /**
   * Associate the given object with the given index. Possible other
   * associations involving the index or the object is removed.
   */
  inline void operator()(IntT i, tTPtr o);

  /**
   * Return true if the given object is known.
   */
  inline bool included(tTPtr o) const;

  /**
   * Return true if the given index is known.
   */
  inline bool included(IntT i) const;

  /**
   * Remove all associations.
   */
  inline void clear();

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

#include "ObjectIndexer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ObjectIndexer.tcc"
#endif

#endif /* THEPEG_ObjectIndexer_H */
