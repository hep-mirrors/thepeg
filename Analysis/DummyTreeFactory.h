// -*- C++ -*-
#ifndef LWH_DummyTreeFactory_H
#define LWH_DummyTreeFactory_H
//
// This is the declaration of the DummyTreeFactory class.
//

#include "AITreeFactory.h"
#include <string>
#include <set>
#include "DummyTree.h"

namespace LWH {

using namespace AIDA;

/**
 * The creator of trees.
 */
class DummyTreeFactory: public ITreeFactory {

public:

  /// Destructor.
  virtual ~DummyTreeFactory() {
    clear();
  }

  /**
   * Creates a new tree that is not associated with a store.
   */
  ITree * create() {
    DummyTree * tree = new DummyTree;
    trees.insert(tree);
    return tree;
  }

  /**
   * Creates a new DummyTree and associates it with a store.
   * The store is assumed to be write-only.
   * The store will be created.
   * @param storeName The name of the store, if empty (""), the tree is
   *                  created in memory and therefore will not be associated
   *                  with a file.
   */
  DummyTree * createDummyTree(const std::string & storeName) {
    return new DummyTree(storeName);
  }

  /**
   * Creates a new DummyTree and associates it with a store.
   * The store is assumed to be write-only.
   * The store will be created.
   * @param storeName The name of the store, if empty (""), the tree is
   *                  created in memory and therefore will not be associated
   *                  with a file.
   * @param storeType must be "xml".
   * @param readOnly  must be false since we cannot read in trees.
   * @param createNew must be true indicating that the file will be created
   */
  ITree * create(const std::string & storeName,
		 const std::string & storeType = "",
		 bool readOnly = false, bool createNew = false,
		 const std::string & = "") {
    if ( storeType != "xml" && storeType != "" && storeType != "flat" )
      throw std::runtime_error("Can only store trees in xml or flat format.");
    if ( readOnly || !createNew )
      throw std::runtime_error("Cannot read in trees.");
    return new DummyTree(storeName, storeType != "flat");
  }

private:

  /** Delete all trees. */
  void clear() {
    for ( std::set<DummyTree *>::iterator it = trees.begin();
	  it != trees.end(); ++it ) delete *it;
    trees.clear();
  }

  /** The created trees. */
  std::set<DummyTree *> trees;

};

}

#endif /* LWH_DummyTreeFactory_H */
