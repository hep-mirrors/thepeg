mySOURCES = HepMCReader.cc HepMCEventHandler.cc

DOCFILES = HepMCEventHandler.h HepMCReader.h

INCLUDEFILES = $(DOCFILES) HepMCEventHandler.fh \
			   HepMCReader.fh

pkglib_LTLIBRARIES = HepMCReader.la

# Version info should be updated if any interface or persistent I/O
# function is changed
HepMCReader_la_LDFLAGS = $(AM_LDFLAGS) -module $(LIBTOOLVERSIONINFO)
HepMCReader_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

