// -*- C++ -*-
#ifndef THEPEG_ObjectIndexer_H
#define THEPEG_ObjectIndexer_H
//
// This is the declaration of the <!id>ObjectIndexer<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// This is a templated class which associates dynamically (reference
// counted) objects to indices.
//

#include "ThePEG/Config/ThePEG.h"
// #include "ObjectIndexer.fh"
// #include "ObjectIndexer.xh"

namespace ThePEG {

template <typename IntT, typename ObjT>
class ObjectIndexer {

public:

  ThePEG_DECLARE_TEMPLATE_POINTERS(ObjT,TPtr);
  typedef map<IntT,tTPtr> IndexObjectMap;
  typedef map<TPtr,IntT> ObjectIndexMap;

public:

  inline IntT operator()(tTPtr o);
  // Return the index for the given object. If the object is not known,
  // a new index will be created.

  inline tTPtr operator()(IntT i);
  inline tTPtr operator()(IntT i) const;
  // Return the object for the given index. If the index is not known,
  // a new object will be (default) created in the non-const version,
  // while a null pointer will be returned for the const one..

  inline void operator()(IntT i, tTPtr o);
  // Associate the given object with the given index. Possible other
  // associations involving the index or the object is removed.

  inline bool included(tTPtr o) const;
  inline bool included(IntT i) const;
  // Return true if the given object or index is known.

  inline void clear();
  // Remove all associations.

private:

  IndexObjectMap indexObject;
  // All known objects keyed by their indices.

  ObjectIndexMap objectIndex;
  // All known indices keyed by the corresponding objects.

private:

  ObjectIndexer & operator=(const ObjectIndexer &);
  // Private and non-existent assignment operator.

};

}

#include "ObjectIndexer.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ObjectIndexer.tcc"
#endif

#endif /* THEPEG_ObjectIndexer_H */
