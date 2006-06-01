// -*- C++ -*-
#ifndef LWH_DummyTree_H
#define LWH_DummyTree_H
//
// This is the declaration of the DummyTree class.
//

#include "AITree.h"
#include <fstream>
#include <iostream>
#include "HistFactory.h"

namespace LWH {

using namespace AIDA;

/**
 * The DummyTree class is a dummy implementation of the AIDA::ITree
 * interface. Most of the functions are pure dummies. The only thing
 * that it is used for is to keep track of the filename where the
 * histograms of the an associated HistogramFactory should be stored.
 */
class DummyTree: public ITree {

public:

  /** The AnalysisFactory is a friend. */
  friend class AnalysisFactory;

public:

  /**
   * The standard constructor.
   */
  DummyTree(std::string storename, bool xml = true)
    : name(storename), histfac(0), flat(!xml) {}

  /**
   * The default constructor.
   */
  DummyTree(): name(""), histfac(0), flat(false) {}

  /**
   * The copy constructor.
   */
  DummyTree(const DummyTree & dt)
    : name(dt.name), histfac(dt.histfac), flat(dt.flat) {}

  /// Destructor.
  virtual ~DummyTree() {}

  /**
   * Get the name of the store.
   * @return The store's name.
   */
  std::string storeName() const {
    return name;
  }

  /**
   * LWH cannot get the IManagedObject at a given path in the ITree.
   * @return     0 always.
   *
   */
  IManagedObject * find(const std::string &) {
    return 0;
  }

  /**
   * LWH cannot get a mounted ITree at a given path in the current ITree.
   * @return     0 always.
   */
  ITree * findTree(const std::string &) {
    return 0;
  }

  /**
   * LWH cannot change to a given directory.
   * @return false always.
   *
   */
  bool cd(const std::string &) {
    return false;
  }

  /**
   * Get the path of the current working directory.
   * @return "/" always.
   *
   */
  std::string pwd() const {
    return "/";
  }

  /** 
   * Not implemented in LWH.
   * @return false always.
   *
   */
  bool ls(const std::string & = ".", bool = false,
	  std::ostream & = std::cout) const {
    return false;
  }

  /**
   * Not implemented in LWH.
   */
  std::vector<std::string> listObjectNames(const std::string & = ".",
					   bool = false) const {
    return std::vector<std::string>();
  }

  /**
   * Not implemented in LWH.
   */
  std::vector<std::string> listObjectTypes(const std::string & = ".",
					   bool = false) const {
    return std::vector<std::string>();
  }

  /**
   * Not implemented in LWH.
   * @return true always
   *
   */   
  bool mkdir(const std::string &) {
    return true;
  }

  /**
   * Not implemented in LWH.
   * @return true always
   */
  bool mkdirs(const std::string &) {
    return true;
  }

  /**
   * Not implemented in LWH.
   * @return true always
   */
  bool rmdir(const std::string &) {
    return true;
  }

  /**
   * Not implemented in LWH.
   * @return false always
   */
  bool rm(const std::string &) {
    return false;
  }

  /**
   * Not implemented in LWH.
   * @return the empty string always
   */
  std::string findPath(const IManagedObject &) const {
    return "";
  }

  /**
   * Not implemented in LWH.
   * @return false always
   */
  bool mv(const std::string &, const std::string &) {
    return false;
  }

  /**
   * Print all histograms to the current filename.
   * @return false if something went wrong.
   */
  bool commit() {
    if ( !histfac ) return false;
    std::ofstream of(name.c_str());
    if ( flat )
      histfac->writeFLAT(of);
    else
      histfac->writeXML(of);
    return of.good();
  }

  /**
   * Not implemented in LWH.
   */
  void setOverwrite(bool = true) {}

  /**
   * Not implemented in LWH.
   * @return false always.
   */
  bool cp(const std::string &, const std::string &, bool = false) {
    return false;
  }

  /**
   * Not implemented in LWH.
   * @return false always.
   */
  bool symlink(const std::string &, const std::string &) {
    return false;
  }

  /**
   * Not implemented in LWH.
   * @return false always.
   */
  bool mount(const std::string &, ITree &, const std::string &) {
    return false;
  }

  /**
   * Not implemented in LWH.
   * @return false always.
   */
  bool unmount(const std::string &) {
    return false;
  }

  /**
   * Calls commit().
   */
  bool close() {
    return commit();
  }

  /**
   * Not implemented in LWH.
   * @return null pointer always.
   */ 
  void * cast(const std::string &) const {
    return 0;
  }

private:

  /** The filename to print histograms to. */
  std::string name;

  /** Only one HistFactory can be associated. */
  HistFactory * histfac;

  /** If true write histograms in FLAT format, otherwise in XML. */
  bool flat;

};

}

#endif /* LWH_DummyTree_H */
