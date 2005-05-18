SUBDIRS = CLHEPWrap Config Utilities Repository Interface PDT EventRecord \
          Persistency StandardModel Handlers PDF MatrixElement Pointer ACDC \
          Helicity LesHouches

DISTFILES = README Makefile configure configure.in

VERSION = 1.0ab

TAG = ThePEG-$(VERSION)

.PHONY: lib all depend clean nodebug setup

all: check

check: setup lib
	@cd src ;  $(MAKE) check ; cd ..

init: setup lib
	@cd src ;  $(MAKE) init ; cd ..

lib: setup
	@for dir in $(SUBDIRS) lib; do cd $$dir ; $(MAKE) lib; cd .. ; done

clean: setup
	@for dir in $(SUBDIRS) lib src; do cd $$dir ; $(MAKE) clean ; cd .. ; done

distclean: setup clean
	@cd src ; $(MAKE) distclean ; cd .. 
	@cd Doc ; $(MAKE) distclean ; cd .. 
	rm -f config.cache config.status config.log Config/Makefile.common Config/config.h

depend: setup
	@for dir in $(SUBDIRS) src ; do cd $$dir ; $(MAKE) depend ; cd .. ; done

install: check
	@for dir in $(SUBDIRS) lib src ; do cd $$dir ; $(MAKE) VERSION=$(VERSION) install ; cd .. ; done

doc: init
	@cd Doc ; $(MAKE) doc ; cd ..

setup: Config/Makefile.common Config/config.h

Config/Makefile.common: Config/Makefile.common.in configure
	./configure

Config/config.h: Config/config.h.in configure
	./configure

configure: configure.in
	autoconf

dist: doc
	rm -rf $(TAG)
	mkdir -p $(TAG)/ThePEG
	cp ../Makefile $(TAG)
	cp ../configure $(TAG)
	cp $(DISTFILES) $(TAG)/ThePEG
	for dir in $(SUBDIRS) src Doc lib ; do cd $$dir ; $(MAKE) TAGDIR=$(TAG)/ThePEG VERSION=$(VERSION) Dist ; cd .. ; done
	tar czf $(TAG).tgz $(TAG)
	rm -rf $(TAG)

snapshot:
	$(MAKE) thesnapshot SNAPTAG=ThePEG-`/bin/date '+%y%m%d'`

thesnapshot:
	rm -rf $(SNAPTAG)
	mkdir $(SNAPTAG)
	cvs export -D today ThePEG
	mv ThePEG/ThePEG $(SNAPTAG)
	mv ThePEG/Makefile $(SNAPTAG)
	mv ThePEG/configure $(SNAPTAG)
	rm -rf ThePEG
	tar czf $(SNAPTAG).tgz $(SNAPTAG)
	rm -rf $(SNAPTAG)


