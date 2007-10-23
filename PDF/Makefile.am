mySOURCES = PartonExtractor.cc PDFBase.cc RemnantHandler.cc \
            BeamParticleData.cc PartonBin.cc NoPDF.cc NoRemnants.cc PDFCuts.cc \
            PartonBinInstance.cc SoftRemnantHandler.cc

DOCFILES = BeamParticleData.h \
           NoPDF.h NoRemnants.h PDFBase.h PDFCuts.h \
           PartonBin.h PartonExtractor.h RemnantHandler.h \
           PDF.h PartonBinInstance.h SoftRemnantHandler.h

INCLUDEFILES = $(DOCFILES) BeamParticleData.xh \
               NoRemnants.icc PDFBase.xh PDFCuts.icc \
               PartonExtractor.fh PartonExtractor.icc \
               PartonExtractor.xh RemnantHandler.xh \
               PDF.fh PDF.icc PartonBinInstance.icc PartonBin.fh

INPUTFILES = PDFsets.index

CLEANFILES = done-all-links

noinst_LTLIBRARIES = libThePEGPDF.la
pkglib_LTLIBRARIES = LeptonLeptonPDF.la LeptonLeptonRemnant.la \
          GRVBase.la GRV94L.la GRV94M.la BaryonRemnants.la

if USELHAPDF
LHAPDF_SOURCES = LHAPDF.cc LHAPDF.h LHAPDF.icc
libThePEGPDF_la_LDFLAGS = $(LHAPDF_LDFLAGS)
libThePEGPDF_la_LIBADD = $(LHAPDF_LIBS)
else
LHAPDF_SOURCES = 
endif

libThePEGPDF_la_SOURCES = $(mySOURCES) $(INCLUDEFILES) $(LHAPDF_SOURCES)

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonPDF_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
LeptonLeptonPDF_la_SOURCES = LeptonLeptonPDF.cc LeptonLeptonPDF.h

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonRemnant_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
LeptonLeptonRemnant_la_SOURCES = LeptonLeptonRemnant.cc LeptonLeptonRemnant.h

# Version info should be updated if any interface or persistent I/O
# function is changed
GRVBase_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRVBase_la_SOURCES = GRVBase.cc GRVBase.h GRVBase.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94L_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRV94L_la_SOURCES = GRV94L.cc GRV94L.h

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94M_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
GRV94M_la_SOURCES = GRV94M.cc GRV94M.h

# Version info should be updated if any interface or persistent I/O
# function is changed
BaryonRemnants_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
BaryonRemnants_la_SOURCES = BaryonRemnants.cc BaryonRemnants.h \
                            BaryonRemnants.icc 

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

