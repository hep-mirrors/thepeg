mySOURCES = InterfaceBase.cc InterfacedBase.cc Interfaced.cc ParVector.cc \
          Parameter.cc RefVector.cc Reference.cc Switch.cc Command.cc \
          ClassDocumentation.cc

DOCFILES = Command.h InterfaceBase.h Interfaced.h InterfacedBase.h ParVector.h \
           Parameter.h RefVector.h Reference.h Switch.h ClassDocumentation.h \
           Interface.h

INCLUDEFILES = $(DOCFILES) Command.fh Command.icc Command.tcc \
            Command.xh InterfaceBase.fh InterfaceBase.icc InterfaceBase.xh \
            Interfaced.icc InterfacedBase.icc InterfacedBase.xh ParVector.fh \
            ParVector.icc ParVector.tcc ParVector.xh Parameter.fh \
            Parameter.icc Parameter.tcc Parameter.xh RefVector.fh \
            RefVector.icc RefVector.tcc RefVector.xh Reference.fh \
            Reference.icc Reference.tcc Reference.xh Switch.fh Switch.icc \
            Switch.tcc Switch.xh ClassDocumentation.icc ClassDocumentation.fh

noinst_LTLIBRARIES = libThePEGInter.la

libThePEGInter_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

