mySOURCES = PersistentOStream.cc PersistentIStream.cc

DOCFILES = InputDescription.h PersistentIStream.h PersistentOStream.h

INCLUDEFILES = $(DOCFILES) InputDescription.icc PersistentIStream.fh \
            PersistentIStream.icc PersistentIStream.tcc PersistentIStream.xh \
            PersistentOStream.fh PersistentOStream.icc PersistentOStream.xh 

noinst_LTLIBRARIES = libThePEGPersistency.la
libThePEGPersistency_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

