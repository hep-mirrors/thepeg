AIDAWRAPPERS = AIAnalysisFactory.h AIAxis.h AIHistogram1D.h \
               AIHistogramFactory.h AITree.h AITreeFactory.h

LWHHEADERS = AnalysisFactory.h Axis.h DummyTree.h DummyTreeFactory.h \
             Hist1D.h HistFactory.h

mySOURCES = HistogramFactory.cc LWHFactory.cc

DOCFILES = $(AIDAWRAPPERS) $(LWHHEADERS) HistogramFactory.h LWHFactory.h

INCLUDEFILES = $(DOCFILES) HistogramFactory.fh HistogramFactory.icc \
               LWHFactory.icc

noinst_LTLIBRARIES = libThePEGHist.la
libThePEGHist_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

LWH.tgz: $(AIDAWRAPPERS) $(LWHHEADERS)
	tar czf LWH.tgz  $(AIDAWRAPPERS) $(LWHHEADERS)


