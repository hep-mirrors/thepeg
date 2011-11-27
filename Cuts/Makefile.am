mySOURCES = Cuts.cc OneCutBase.cc TwoCutBase.cc MultiCutBase.cc JetFinder.cc

DOCFILES = Cuts.h OneCutBase.h TwoCutBase.h MultiCutBase.h JetFinder.h

INCLUDEFILES = $(DOCFILES) Cuts.fh OneCutBase.fh \
                TwoCutBase.fh MultiCutBase.fh

noinst_LTLIBRARIES = libThePEGCuts.la
# pkglib_LTLIBRARIES = JetKTClusCuts.la

libThePEGCuts_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

pkglib_LTLIBRARIES = SimpleKTCut.la KTClus.la V2LeptonsCut.la SimpleDISCut.la \
                     KTRapidityCut.la NLOKTJetFinder.la \
		     DeltaMeasureCuts.la

SimpleKTCut_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
SimpleKTCut_la_SOURCES = SimpleKTCut.cc SimpleKTCut.h

KTRapidityCut_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
KTRapidityCut_la_SOURCES = KTRapidityCut.cc KTRapidityCut.h

KTClus_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
KTClus_la_SOURCES = KTClus.cc KTClus.h

V2LeptonsCut_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
V2LeptonsCut_la_SOURCES = V2LeptonsCut.cc V2LeptonsCut.h

SimpleDISCut_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
SimpleDISCut_la_SOURCES = SimpleDISCut.cc SimpleDISCut.h

NLOKTJetFinder_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
NLOKTJetFinder_la_SOURCES = NLOKTJetFinder.cc NLOKTJetFinder.h

DeltaMeasureCuts_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
DeltaMeasureCuts_la_SOURCES = DeltaMeasureCuts.cc DeltaMeasureCuts.h

include $(top_srcdir)/Config/Makefile.aminclude

