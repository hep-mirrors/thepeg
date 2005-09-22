mySOURCES = Amplitude.cc ColourLines.cc DiagramBase.cc Tree2toNDiagram.cc \
            MEBase.cc ReweightBase.cc ME2to2Base.cc ME2to2QCD.cc \
            ReweightConstant.cc

myQCDSOURCES = MEGG2GG.cc MEQG2QG.cc MEQQ2QQ3.cc MEQq2Qq4.cc MEGG2QQ.cc \
               MEQQ2GG.cc MEQQ2qq2.cc MEqq2qq1.cc 

DOCFILES = Amplitude.h ColourLines.h DiagramBase.h Tree2toNDiagram.h MEBase.h \
           ReweightBase.h ME2to2Base.h ME2to2QCD.h MEGG2GG.h MEQG2QG.h \
           MEQQ2QQ3.h MEQq2Qq4.h MEGG2QQ.h MEQQ2GG.h MEQQ2qq2.h MEqq2qq1.h \
           ReweightConstant.h

INCLUDEFILES = $(DOCFILES) Amplitude.icc ColourLines.xh ColourLines.icc \
               DiagramBase.icc DiagramBase.xh DiagramBase.fh \
               Tree2toNDiagram.icc Tree2toNDiagram.xh MEBase.icc \
               ReweightBase.icc ME2to2Base.icc ME2to2QCD.icc \
               MEGG2GG.icc MEQG2QG.icc MEQQ2QQ3.icc MEQq2Qq4.icc MEGG2QQ.icc \
               MEQQ2GG.icc MEQQ2qq2.icc MEqq2qq1.icc \
               ReweightConstant.icc MEBase.fh

noinst_LTLIBRARIES = libThePEGME.la
pkglib_LTLIBRARIES = MEQCD.la MEee2gZ2qq.la \
                     ReweightConstant.la

libThePEGME_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
MEQCD_la_LDFLAGS = -module -version-info 1:0:0
MEQCD_la_SOURCES = $(myQCDSOURCES) 

# Version info should be updated if any interface or persistent I/O
# function is changed
MEee2gZ2qq_la_LDFLAGS = -module -version-info 1:0:0
MEee2gZ2qq_la_SOURCES = MEee2gZ2qq.cc MEee2gZ2qq.h MEee2gZ2qq.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
ReweightConstant_la_LDFLAGS = -module -version-info 1:0:0
ReweightConstant_la_SOURCES = MEee2gZ2qq.cc MEee2gZ2qq.h MEee2gZ2qq.icc
