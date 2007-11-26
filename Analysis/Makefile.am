AIDAWRAPPERS = AIAnalysisFactory.h AIAxis.h AIHistogram1D.h \
               AIHistogramFactory.h AITree.h AITreeFactory.h \
               AIManagedObject.h AIDataPoint.h AIDataPointSet.h \
               AIDataPointSetFactory.h AIMeasurement.h

LWHHEADERS = AnalysisFactory.h Axis.h Tree.h TreeFactory.h \
             Histogram1D.h HistogramFactory.h ManagedObject.h \
             VariAxis.h DataPoint.h DataPointSet.h DataPointSetFactory.h \
             Measurement.h

mySOURCES = LWHFactory.cc

DOCFILES = $(AIDAWRAPPERS) $(LWHHEADERS) LWHFactory.h

INCLUDEFILES = $(DOCFILES) 

pkglib_LTLIBRARIES = LWHFactory.la
LWHFactory_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)
LWHFactory_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)

noinst_LTLIBRARIES = libThePEGHist.la
libThePEGHist_la_SOURCES = FactoryBase.cc FactoryBase.fh \
			FactoryBase.icc FactoryBase.h 

LWH.tgz: $(AIDAWRAPPERS) $(LWHHEADERS)
	tar czf LWH.tgz  $(AIDAWRAPPERS) $(LWHHEADERS)

include $(top_srcdir)/Config/Makefile.aminclude

