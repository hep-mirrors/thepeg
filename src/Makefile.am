
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

nodist_pkglib_DATA = ThePEGDefaults.rpo

CLEANFILES = SimpleLEP.log SimpleLEP.out SimpleLEP.run SimpleLEP.tex ThePEGDefaults.rpo setupThePEG runThePEG done-all-links

INPUTFILES = ThePEGDefaults.in ThePEGParticles.in SimpleLEP.in

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

theENV = ThePEG_INSTALL_PATH=$(top_builddir)/lib

ThePEGDefaults.rpo: done-all-links setupThePEG.bin ThePEGDefaults.in ThePEGParticles.in
	$(theENV) ./setupThePEG.bin --init --exitonerror -r ThePEGDefaults.rpo ThePEGDefaults.in
	cd ../lib; $(LN_S) -f ../src/ThePEGDefaults.rpo .

check-local:
	$(theENV) ./setupThePEG.bin --exitonerror -r ThePEGDefaults.rpo SimpleLEP.in
	$(theENV) time ./runThePEG.bin -d 0 SimpleLEP.run

SimpleLEP.run: done-all-links setupThePEG.bin ThePEGDefaults.rpo SimpleLEP.in
	$(theENV) ./setupThePEG.bin --exitonerror -r ThePEGDefaults.rpo SimpleLEP.in

SimpleLEP.out: runThePEG.bin SimpleLEP.run
	$(theENV) time ./runThePEG.bin -d 0 SimpleLEP.run

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
	rm -rf _test_thepeg_installation_
