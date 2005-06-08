mySOURCES = StandardModelBase.cc AlphaEMBase.cc CKMBase.cc AlphaSBase.cc

DOCFILES = AlphaEMBase.h AlphaSBase.h CKMBase.h  \
           StandardModelBase.h

INCLUDEFILES = $(DOCFILES) AlphaEMBase.icc AlphaSBase.icc CKMBase.icc \
               StandardModelBase.fh StandardModelBase.icc 


noinst_LTLIBRARIES = libThePEGSM.la
pkglib_LTLIBRARIES = O1AlphaS.la SimpleAlphaEM.la StandardCKM.la

libThePEGSM_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

O1AlphaS_la_LDFLAGS = -module
O1AlphaS_la_SOURCES = O1AlphaS.cc O1AlphaS.h O1AlphaS.icc 

SimpleAlphaEM_la_LDFLAGS = -module
SimpleAlphaEM_la_SOURCES = SimpleAlphaEM.cc SimpleAlphaEM.h SimpleAlphaEM.icc 

StandardCKM_la_LDFLAGS = -module
StandardCKM_la_SOURCES = StandardCKM.cc StandardCKM.h StandardCKM.icc 
