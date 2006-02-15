mySOURCES = Cuts.cc OneCutBase.cc TwoCutBase.cc MultiCutBase.cc

DOCFILES = Cuts.h OneCutBase.h TwoCutBase.h MultiCutBase.h

INCLUDEFILES = $(DOCFILES) Cuts.icc Cuts.fh OneCutBase.icc OneCutBase.fh \
                TwoCutBase.icc TwoCutBase.fh MultiCutBase.icc MultiCutBase.fh

noinst_LTLIBRARIES = libThePEGCuts.la
# pkglib_LTLIBRARIES = JetKTClusCuts.la

libThePEGCuts_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

pkglib_LTLIBRARIES = SimpleKTCut.la KTClus.la V2LeptonsCut.la SimpleDISCut.la

SimpleKTCut_la_LDFLAGS = -module -version-info 1:0:0
SimpleKTCut_la_SOURCES = SimpleKTCut.cc SimpleKTCut.h SimpleKTCut.icc

KTClus_la_LDFLAGS = -module -version-info 1:0:0
KTClus_la_SOURCES = KTClus.cc KTClus.h KTClus.icc

V2LeptonsCut_la_LDFLAGS = -module -version-info 1:0:0
V2LeptonsCut_la_SOURCES = V2LeptonsCut.cc V2LeptonsCut.h V2LeptonsCut.icc

SimpleDISCut_la_LDFLAGS = -module -version-info 1:0:0
SimpleDISCut_la_SOURCES = SimpleDISCut.cc SimpleDISCut.h SimpleDISCut.icc

