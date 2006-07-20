// -*- C++ -*-
#ifndef LWH_AIHistogramFactory_H
#define LWH_AIHistogramFactory_H

#ifndef LWH_USING_AIDA

/** @cond DONT_DOCUMENT_STRIPPED_DOWN_AIDA_INTERFACES */

namespace AIDA {

class ICloud1D;
class ICloud2D;
class ICloud3D;
class IBaseHistogram;
class IHistogram1D;
class IHistogram2D;
class IHistogram3D;
class IProfile1D;
class IProfile2D;

class IHistogramFactory {

public:

  virtual ~IHistogramFactory() {}

  virtual bool destroy(IBaseHistogram * hist) = 0;
  virtual IHistogram1D *
  createHistogram1D(const std::string &, const std::string &,
		    int, double, double, const std::string & = "") = 0;
  virtual IHistogram1D *
  createHistogram1D(const std::string &, int, double, double) = 0;
  virtual IHistogram1D *
  createHistogram1D(const std::string &, const std::string & ,
		    const std::vector<double> &, const std::string & = "") = 0;
  virtual IHistogram1D *
  createCopy(const std::string &, const IHistogram1D &) = 0;
  virtual IHistogram1D * add(const std::string &,
			     const IHistogram1D &, const IHistogram1D &) = 0;
  virtual IHistogram1D * subtract(const std::string &, const IHistogram1D &,
				  const IHistogram1D &) = 0;
  virtual IHistogram1D * multiply(const std::string &, const IHistogram1D &,
			  const IHistogram1D &) = 0;
  virtual IHistogram1D * divide(const std::string &, const IHistogram1D &,
			const IHistogram1D &) = 0;

};

}

/** @endcond */

#else
#include "AIDA/IHistogramFactory.h"
#endif

#endif /* LWH_AIHistogramFactory_H */
