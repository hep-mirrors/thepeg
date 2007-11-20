// -*- C++ -*-
//
// AIHistogramFactory.h is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
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
