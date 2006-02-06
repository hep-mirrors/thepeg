mySOURCES = PartonExtractor.cc PDFBase.cc RemnantHandler.cc BeamParticleData.cc \
          PartonBin.cc NoPDF.cc NoRemnants.cc PDFCuts.cc \
          PartonBinInstance.cc

DOCFILES = BeamParticleData.h \
           NoPDF.h NoRemnants.h PDFBase.h PDFCuts.h \
           PartonBin.h PartonExtractor.h RemnantHandler.h \
           PDF.h PartonBinInstance.h

INCLUDEFILES = $(DOCFILES) BeamParticleData.icc \
               BeamParticleData.xh \
               NoPDF.icc \
               NoRemnants.icc PDFBase.icc  PDFBase.xh PDFCuts.icc \
               PartonBin.icc PartonExtractor.fh PartonExtractor.icc \
               PartonExtractor.xh RemnantHandler.icc RemnantHandler.xh \
               PDF.fh PDF.icc PartonBinInstance.icc PartonBin.fh

noinst_LTLIBRARIES = libThePEGPDF.la
pkglib_LTLIBRARIES = LeptonLeptonPDF.la LeptonLeptonRemnant.la \
          GRVBase.la GRV94L.la GRV94M.la BaryonRemnants.la

libThePEGPDF_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonPDF_la_LDFLAGS = -module -version-info 1:0:0
LeptonLeptonPDF_la_SOURCES = LeptonLeptonPDF.cc LeptonLeptonPDF.h LeptonLeptonPDF.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
LeptonLeptonRemnant_la_LDFLAGS = -module -version-info 1:0:0
LeptonLeptonRemnant_la_SOURCES = LeptonLeptonRemnant.cc LeptonLeptonRemnant.h LeptonLeptonRemnant.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
GRVBase_la_LDFLAGS = -module -version-info 1:0:0
GRVBase_la_SOURCES = GRVBase.cc GRVBase.h GRVBase.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94L_la_LDFLAGS = -module -version-info 1:0:0
GRV94L_la_SOURCES = GRV94L.cc GRV94L.h GRV94L.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
GRV94M_la_LDFLAGS = -module -version-info 1:0:0
GRV94M_la_SOURCES = GRV94M.cc GRV94M.h GRV94M.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
BaryonRemnants_la_LDFLAGS = -module -version-info 1:0:0
BaryonRemnants_la_SOURCES = BaryonRemnants.cc BaryonRemnants.h \
                            BaryonRemnants.icc 