AIDAWRAPPERS = AIAnalysisFactory.h AIAxis.h AIHistogram1D.h AIHistogram2D.h \
               AIHistogramFactory.h AITree.h AITreeFactory.h \
               AIManagedObject.h AIDataPoint.h AIDataPointSet.h \
               AIDataPointSetFactory.h AIMeasurement.h

LWHHEADERS = AnalysisFactory.h Axis.h Tree.h TreeFactory.h \
             Histogram1D.h Histogram2D.h HistogramFactory.h ManagedObject.h \
             VariAxis.h DataPoint.h DataPointSet.h DataPointSetFactory.h \
             Measurement.h

mySOURCES = LWHFactory.cc

pkglib_LTLIBRARIES = LWHFactory.la XSecCheck.la

if HAVE_RIVET
  DOCFILES = RivetAnalysis.h 
  pkglib_LTLIBRARIES += RivetAnalysis.la
  RivetAnalysis_la_CPPFLAGS = $(AM_CPPFLAGS) $(HEPMCINCLUDE) $(RIVETINCLUDE)
  RivetAnalysis_la_LIBADD = $(HEPMCLIBS) $(RIVETLIBS)
  RivetAnalysis_la_SOURCES = RivetAnalysis.cc $(INCLUDEFILES)
  RivetAnalysis_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
else
  DOCFILES = $(AIDAWRAPPERS) $(LWHHEADERS)
endif
DOCFILES += LWHFactory.h

INCLUDEFILES = $(DOCFILES) 

LWHFactory_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)
LWHFactory_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)

XSecCheck_la_SOURCES = XSecCheck.cc XSecCheck.h
XSecCheck_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)

noinst_LTLIBRARIES = libThePEGHist.la
libThePEGHist_la_SOURCES = FactoryBase.cc FactoryBase.fh FactoryBase.h 

LWHFactory_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
libThePEGHist_la_CPPFLAGS = $(CPPFLAGS) $(AM_CPPFLAGS)
if HAVE_RIVET
LWHFactory_la_CPPFLAGS += $(RIVETINCLUDE)
libThePEGHist_la_CPPFLAGS += $(RIVETINCLUDE)
endif

if HAVE_HEPMC
  pkglib_LTLIBRARIES += HepMCAnalysis.la
  HepMCAnalysis_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
  HepMCAnalysis_la_SOURCES = \
  HepMCFile.h    HepMCFile.cc
  HepMCAnalysis_la_CPPFLAGS = $(AM_CPPFLAGS) $(HEPMCINCLUDE)
  HepMCAnalysis_la_LIBADD = $(HEPMCLIBS)
endif

pkglib_LTLIBRARIES += GraphvizPlot.la
GraphvizPlot_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GraphvizPlot_la_SOURCES = GraphvizPlot.h GraphvizPlot.cc

LWH.tgz: $(AIDAWRAPPERS) $(LWHHEADERS)
	tar czf LWH.tgz  $(AIDAWRAPPERS) $(LWHHEADERS)

include $(top_srcdir)/Config/Makefile.aminclude






