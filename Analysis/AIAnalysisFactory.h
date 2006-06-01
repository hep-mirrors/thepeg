// -*- C++ -*-
#ifndef LWH_AIAnalysisFactory_H
#define LWH_AIAnalysisFactory_H

#ifndef LWH_USING_AIDA

/** @cond DONT_DOCUMENT_STRIPPED_DOWN_AIDA_INTERFACES */

namespace AIDA {

class IDataPointSetFactory;
class IFitFactory;
class IFunctionFactory;
class IPlotterFactory;
class ITupleFactory;

class IAnalysisFactory {

public:

  virtual ~IAnalysisFactory() {}


};

}

/** @endcond */

#else
#include "AIDA/IAnalysisFactory.h"
#endif

#endif /* LWH_AIAnalysisFactory_H */
