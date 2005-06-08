mySOURCES = Containers.cc

DOCFILES = ThePEG.h Constants.h Containers.h Pointers.h Units.h algorithm.h \
           std.h Complex.h

INCLUDEFILES = $(DOCFILES) config.h

noinst_LTLIBRARIES = libThePEGConfig.la
libThePEGConfig_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)




##install-local:
##	mkdir -p $(INSTALLLIB)
##	sed -e s:@:$(PREFIX)/lib/ThePEG/current:g Makefile.install > $(INSTALLLIB)/Makefile
##	sed -e s:../../ThePEG/lib:$(INSTALLLIB):g -e s:-I../../:-I$(INCLUDEINSTALL):g Makefile.common > $(INSTALLLIB)/Makefile.common


