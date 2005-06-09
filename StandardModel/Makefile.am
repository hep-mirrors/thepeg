mySOURCES = StandardModelBase.cc AlphaEMBase.cc CKMBase.cc AlphaSBase.cc

DOCFILES = AlphaEMBase.h AlphaSBase.h CKMBase.h  \
           StandardModelBase.h

INCLUDEFILES = $(DOCFILES) AlphaEMBase.icc AlphaSBase.icc CKMBase.icc \
               StandardModelBase.fh StandardModelBase.icc 


noinst_LTLIBRARIES = libThePEGSM.la
pkglib_LTLIBRARIES = O1AlphaS.la SimpleAlphaEM.la StandardCKM.la

libThePEGSM_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
O1AlphaS_la_LDFLAGS = -module -version-info 1:0:0
O1AlphaS_la_SOURCES = O1AlphaS.cc O1AlphaS.h O1AlphaS.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
SimpleAlphaEM_la_LDFLAGS = -module -version-info 1:0:0
SimpleAlphaEM_la_SOURCES = SimpleAlphaEM.cc SimpleAlphaEM.h SimpleAlphaEM.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
StandardCKM_la_LDFLAGS = -module -version-info 1:0:0
StandardCKM_la_SOURCES = StandardCKM.cc StandardCKM.h StandardCKM.icc 
