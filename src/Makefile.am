
bin_SCRIPTS = runThePEG setupThePEG
pkglib_PROGRAMS = runThePEG.bin setupThePEG.bin
EXTRA_PROGRAMS = runPartial

myLDADD = $(top_builddir)/lib/libThePEG.la 
myLDFLAGS = -export-dynamic

dist_noinst_SCRIPTS = runThePEG.install setupThePEG.install

runThePEG_bin_SOURCES = runThePEG.cc
runThePEG_bin_LDADD = $(myLDADD)
runThePEG_bin_LDFLAGS = $(myLDFLAGS)

setupThePEG_bin_SOURCES = setupThePEG.cc
setupThePEG_bin_LDADD = $(myLDADD)
setupThePEG_bin_LDFLAGS = $(myLDFLAGS)

runPartial_SOURCES = runPartial.cc
runPartial_LDADD = $(myLDADD)
runPartial_LDFLAGS = $(myLDFLAGS)

dist_pkgdata_DATA = SimpleLEP.in ThePEGDefaults.in ThePEGParticles.in debugItems.txt

dist_pkglib_DATA = ThePEGDefaults.rpo

CLEANFILES = SimpleLEP.log SimpleLEP.out SimpleLEP.run SimpleLEP.tex ThePEGDefaults.rpo setupThePEG runThePEG

setupThePEG: setupThePEG.install
	sed -e s:@:$(pkglibdir):g $(srcdir)/setupThePEG.install > setupThePEG

runThePEG: runThePEG.install
	sed -e s:@:$(pkglibdir):g $(srcdir)/runThePEG.install > runThePEG

ThePEGDefaults.rpo: setupThePEG.bin ThePEGDefaults.in ThePEGParticles.in
	./setupThePEG.bin -init -r ThePEGDefaults.rpo
	cd ../lib; $(LN_S) -f ../src/ThePEGDefaults.rpo .

check-local: SimpleLEP.out

SimpleLEP.run: setupThePEG.bin ThePEGDefaults.rpo SimpleLEP.in
	./setupThePEG.bin -r ThePEGDefaults.rpo SimpleLEP.in

SimpleLEP.out: runThePEG.bin SimpleLEP.run
	time ./runThePEG.bin -d 0 SimpleLEP.run

## those need to be modified
##
##install-data-local:
##	cd $(pkglibdir); \
##      rm -f setupThePEG-$(VERSION).bin runThePEG-$(VERSION).bin; \
##      ln setupThePEG.bin setupThePEG-$(VERSION).bin; \
##     ln runThePEG.bin runThePEG-$(VERSION).bin

##uninstall-local:
##	cd $(pkglibdir); \
##       rm -f setupThePEG-$(VERSION).bin runThePEG-$(VERSION).bin

