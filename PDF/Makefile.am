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

LeptonLeptonPDF_la_LDFLAGS = -module
LeptonLeptonPDF_la_SOURCES = LeptonLeptonPDF.cc LeptonLeptonPDF.h LeptonLeptonPDF.icc 

LeptonLeptonRemnant_la_LDFLAGS = -module
LeptonLeptonRemnant_la_SOURCES = LeptonLeptonRemnant.cc LeptonLeptonRemnant.h LeptonLeptonRemnant.icc 

GRVBase_la_LDFLAGS = -module
GRVBase_la_SOURCES = GRVBase.cc GRVBase.h GRVBase.icc 

GRV94L_la_LDFLAGS = -module
GRV94L_la_SOURCES = GRV94L.cc GRV94L.h GRV94L.icc 

GRV94M_la_LDFLAGS = -module
GRV94M_la_SOURCES = GRV94M.cc GRV94M.h GRV94M.icc 

BaryonRemnants_la_LDFLAGS = -module
BaryonRemnants_la_SOURCES = BaryonRemnants.cc BaryonRemnants.h BaryonRemnants.icc 
