// -*- C++ -*-
#ifndef LWH_AITree_H
#define LWH_AITree_H

#ifndef LWH_USING_AIDA

/** @cond DONT_DOCUMENT_STRIPPED_DOWN_AIDA_INTERFACES */

namespace AIDA {

class IManagedObject;

class ITree {

public:

  virtual ~ITree() {}

  virtual std::string storeName() const = 0;
  virtual bool commit() = 0;
  virtual bool close() = 0;
  virtual bool mkdir(const std::string &) = 0;
  virtual bool mkdirs(const std::string &) = 0;

};

}

/** @endcond */

#else
#include "AIDA/ITree.h"
#endif

#endif /* LWH_AITree_H */
