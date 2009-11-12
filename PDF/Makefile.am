mySOURCES = PartonExtractor.cc PDFBase.cc RemnantHandler.cc \
            BeamParticleData.cc PartonBin.cc NoPDF.cc NoRemnants.cc PDFCuts.cc \
            PartonBinInstance.cc SoftRemnantHandler.cc

DOCFILES = BeamParticleData.h \
           NoPDF.h NoRemnants.h PDFBase.h PDFCuts.h \
           PartonBin.h PartonExtractor.h RemnantHandler.h \
           PDF.h PartonBinInstance.h SoftRemnantHandler.h

INCLUDEFILES = $(DOCFILES) BeamParticleData.xh \
               PDFBase.xh PartonExtractor.fh \
               PartonExtractor.xh RemnantHandler.xh \
               PDF.fh PartonBin.fh

INPUTFILES = PDFsets.index

CLEANFILES = done-all-links

noinst_LTLIBRARIES = libThePEGPDF.la
pkglib_LTLIBRARIES = LeptonLeptonPDF.la LeptonLeptonRemnant.la \
          GRVBase.la GRV94L.la GRV94M.la WeizsackerWilliamsPDF.la

if USELHAPDF
LHAPDF_SOURCES = LHAPDF.cc LHAPDF.h
LHAPDF_CPPFLAGS = \
-DLHAPDF_PKGDATADIR="\"$(LHAPDF_PKGDATADIR)\"" \
-DTHEPEG_PKGDATADIR="\"$(pkgdatadir)\""
libThePEGPDF_la_LDFLAGS = $(LHAPDF_LDFLAGS)
libThePEGPDF_la_LIBADD = $(LHAPDF_LIBS)
else
LHAPDF_SOURCES = 
LHAPDF_CPPFLAGS = 
endif

libThePEGPDF_la_SOURCES = $(mySOURCES) $(INCLUDEFILES) $(LHAPDF_SOURCES)
libThePEGPDF_la_CPPFLAGS = $(AM_CPPFLAGS) $(LHAPDF_CPPFLAGS)

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonPDF_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
LeptonLeptonPDF_la_SOURCES = LeptonLeptonPDF.cc LeptonLeptonPDF.h

# Version info should be updated if any interface or persistent I/O
# function is changed
WeizsackerWilliamsPDF_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
WeizsackerWilliamsPDF_la_SOURCES = WeizsackerWilliamsPDF.cc WeizsackerWilliamsPDF.h

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonRemnant_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
LeptonLeptonRemnant_la_SOURCES = LeptonLeptonRemnant.cc LeptonLeptonRemnant.h

# Version info should be updated if any interface or persistent I/O
# function is changed
GRVBase_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRVBase_la_SOURCES = GRVBase.cc GRVBase.h

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94L_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRV94L_la_SOURCES = GRV94L.cc GRV94L.h

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94M_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRV94M_la_SOURCES = GRV94M.cc GRV94M.h

dist_pkgdata_DATA = PDFsets.index

all-local: done-all-links

done-all-links:
@EMPTY@ifdef SHOWCOMMAND
	for file in $(INPUTFILES); do \
	  if test ! -f $$file; then $(LN_S) $(srcdir)/$$file $$file; fi; done
	echo "stamp" > done-all-links
@EMPTY@else
	@echo "sym-linking input files files..."
	@for file in $(INPUTFILES); do \
	  if test ! -f $$file; then $(LN_S) $(srcdir)/$$file $$file; fi; done
	@echo "stamp" > done-all-links
@EMPTY@endif

include $(top_srcdir)/Config/Makefile.aminclude

