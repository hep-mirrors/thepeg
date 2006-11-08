
pkglib_PROGRAMS = runThePEG.bin setupThePEG.bin
EXTRA_PROGRAMS = runEventLoop

myLDADD = $(top_builddir)/lib/libThePEG.la 
myLDFLAGS = -export-dynamic -R$(CLHEPPATH)/lib

dist_noinst_SCRIPTS = runThePEG.install setupThePEG.install

runThePEG_bin_SOURCES = runThePEG.cc
runThePEG_bin_LDADD = $(myLDADD)
runThePEG_bin_LDFLAGS = $(myLDFLAGS)

runEventLoop_SOURCES = runEventLoop.cc
runEventLoop_LDADD = -lHepMC $(myLDADD)
runEventLoop_LDFLAGS = $(myLDFLAGS)

setupThePEG_bin_SOURCES = setupThePEG.cc
setupThePEG_bin_LDADD = $(myLDADD)
setupThePEG_bin_LDFLAGS = $(myLDFLAGS)

if USELHAPDF
pkglib_LTLIBRARIES = TestLHAPDF.la
TestLHAPDF_la_SOURCES = TestLHAPDF.cc TestLHAPDF.h TestLHAPDF.icc
TestLHAPDF_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
endif

dist_pkgdata_DATA = SimpleLEP.in ThePEGDefaults.in LHAPDFDefaults.in ThePEGParticles.in debugItems.txt TestLHAPDF.in

nodist_pkglib_DATA = ThePEGDefaults.rpo

CLEANFILES = SimpleLEP.log SimpleLEP.out SimpleLEP.run SimpleLEP.tex \
             ThePEGDefaults.rpo setupThePEG runThePEG done-all-links \
             TestLHAPDF.log TestLHAPDF.out TestLHAPDF.run TestLHAPDF.tex \
             .runThePEG.timer.TestLHAPDF.run 

save:
	mkdir -p save
	cp *.log *.out *.run *.tex *.rpo save

valgrind:
	valgrind --leak-check=full --num-callers=25 --track-fds=yes --freelist-vol=100000000 --leak-resolution=med --trace-children=yes ./setupThePEG.bin -L../lib -r ThePEGDefaults.rpo SimpleLEP.in &> /tmp/valgrind.out
	valgrind --leak-check=full --num-callers=25 --track-fds=yes --freelist-vol=100000000 --leak-resolution=med --trace-children=yes ./runThePEG.bin -L../lib SimpleLEP.run >> /tmp/valgrind.out 2>&1

INPUTFILES = ThePEGDefaults.in LHAPDFDefaults.in ThePEGParticles.in \
             SimpleLEP.in TestLHAPDF.in

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

setupThePEG: $(srcdir)/setupThePEG.install Makefile
	sed -e s:@:$(pkglibdir):g $(srcdir)/setupThePEG.install > setupThePEG

runThePEG: $(srcdir)/runThePEG.install Makefile
	sed -e s:@:$(pkglibdir):g $(srcdir)/runThePEG.install > runThePEG

ThePEGDefaults.rpo: done-all-links setupThePEG.bin ThePEGDefaults.in LHAPDFDefaults.in ThePEGParticles.in
	./setupThePEG.bin --init --exitonerror -L../lib -r ThePEGDefaults.rpo ThePEGDefaults.in
	cd ../lib; rm -f ThePEGDefaults.rpo; $(LN_S) -f ../src/ThePEGDefaults.rpo .
if USELHAPDF
	./setupThePEG.bin --init --exitonerror -L../lib -r ThePEGDefaults.rpo -o ThePEGDefaults.rpo LHAPDFDefaults.in
endif

check-local:
	./setupThePEG.bin --exitonerror -L../lib -r ThePEGDefaults.rpo SimpleLEP.in
	time ./runThePEG.bin -L../lib -d 0 SimpleLEP.run
if USELHAPDF
	./setupThePEG.bin --exitonerror -L../lib -r ThePEGDefaults.rpo TestLHAPDF.in
	time ./runThePEG.bin -L../lib -d 1 -x .libs/TestLHAPDF.so TestLHAPDF.run
endif

SimpleLEP.run: done-all-links setupThePEG.bin ThePEGDefaults.rpo SimpleLEP.in
	./setupThePEG.bin --exitonerror -L../lib -r ThePEGDefaults.rpo SimpleLEP.in

SimpleLEP.out: runThePEG.bin SimpleLEP.run
	time ./runThePEG.bin -L../lib -d 0 SimpleLEP.run

if USELHAPDF
TestLHAPDF.run: done-all-links setupThePEG.bin ThePEGDefaults.rpo TestLHAPDF.in 
	./setupThePEG.bin --exitonerror -L../lib -r ThePEGDefaults.rpo TestLHAPDF.in

TestLHAPDF.out: runThePEG.bin TestLHAPDF.run
	time ./runThePEG.bin -L../lib -d 1 -x .libs/TestLHAPDF.so TestLHAPDF.run
endif

install-data-local:
	sed -e s:@:$(DESTDIR)$(pkglibdir):g $(srcdir)/setupThePEG.install > setupThePEG
	sed -e s:@:$(DESTDIR)$(pkglibdir):g $(srcdir)/runThePEG.install > runThePEG
	test -z "$(bindir)" || $(mkdir_p) "$(DESTDIR)$(bindir)"
	$(INSTALL) setupThePEG $(DESTDIR)$(bindir)/setupThePEG
	$(INSTALL) runThePEG $(DESTDIR)$(bindir)/runThePEG
	cd $(DESTDIR)$(pkglibdir); \
	rm -f setupThePEG-$(VERSION).bin runThePEG-$(VERSION).bin ThePEGDefaults-$(VERSION).rpo; \
	ln setupThePEG.bin setupThePEG-$(VERSION).bin; \
	ln runThePEG.bin runThePEG-$(VERSION).bin; \
	cp ThePEGDefaults.rpo ThePEGDefaults-$(VERSION).rpo

uninstall-local:
	rm -f  $(DESTDIR)$(bindir)/setupThePEG $(DESTDIR)$(bindir)/runThePEG
	cd $(DESTDIR)$(pkglibdir); \
	rm -f setupThePEG-$(VERSION).bin runThePEG-$(VERSION).bin ThePEGDefaults-$(VERSION).rpo 

installcheck-local:
	$(mkdir_p) _test_thepeg_installation_
	cd _test_thepeg_installation_; $(DESTDIR)$(bindir)/setupThePEG --exitonerror $(DESTDIR)$(pkgdatadir)/SimpleLEP.in; $(DESTDIR)$(bindir)/runThePEG SimpleLEP.run
if USELHAPDF
	cd _test_thepeg_installation_; $(DESTDIR)$(bindir)/setupThePEG --exitonerror $(DESTDIR)$(pkgdatadir)/TestLHAPDF.in; $(DESTDIR)$(bindir)/runThePEG -x $(DESTDIR)$(pkglibdir)/TestLHAPDF.so TestLHAPDF.run
endif
	rm -rf _test_thepeg_installation_
