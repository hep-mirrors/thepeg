SUBDIRS = CLHEPWrap Config Utilities Repository Interface PDT EventRecord \
          Persistency StandardModel Handlers PDF MatrixElement Pointer

DISTFILES = README Makefile configure configure.in

VERSION = test

TAG = ThePEG-$(VERSION)

.PHONY: lib all depend clean nodebug setup

all: test

progs: setup lib
	cd src ;  $(MAKE) -$(MAKEFLAGS) progs ; cd ..

current: setup lib
	cd src ;  $(MAKE) -$(MAKEFLAGS) current ; cd ..

test: setup lib
	cd src ;  $(MAKE) -$(MAKEFLAGS) test  CXXDEBUGFLAG=-g CXXOPTFLAG="-O"; cd ..

check: setup lib
	cd src ;  $(MAKE) -$(MAKEFLAGS) check ; cd ..

lib: setup
	for dir in $(SUBDIRS) lib; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) lib; cd .. ; done

optdebug: setup
	for dir in $(SUBDIRS); do cd $$dir ; $(MAKE) -$(MAKEFLAGS) lib CXXDEBUGFLAG=-g CXXOPTFLAG=-O; cd .. ; done

fulldebug: setup
	for dir in $(SUBDIRS); do cd $$dir ; $(MAKE) -$(MAKEFLAGS) lib CXXDEBUGFLAG=-g CXXOPTFLAG=""; cd .. ; done

nodebug: setup
	for dir in $(SUBDIRS) lib; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) lib ; cd .. ; done

clean: setup
	for dir in $(SUBDIRS) lib src; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) clean ; cd .. ; done

distclean: setup clean
	cd src ; $(MAKE) -$(MAKEFLAGS) distclean ; cd .. 
	rm -f config.cache config.status config.log Config/Makefile.common Config/config.h

depend: setup
	for dir in $(SUBDIRS) src ; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) depend ; cd .. ; done

install: lib
	for dir in $(SUBDIRS) lib src ; do cd $$dir ; $(MAKE) VERSION=$(VERSION) -$(MAKEFLAGS) install ; cd .. ; done

doc: setup
	for dir in $(SUBDIRS) ; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) doc ; cd .. ; done

setup: Config/Makefile.common Doc/h2html Config/config.h

Config/Makefile.common: Config/Makefile.common.in configure
	./configure

Config/config.h: Config/config.h.in configure
	./configure

Doc/h2html: Doc/h2html.in configure
	./configure

configure: configure.in
	autoconf

dist: doc
	rm -rf $(TAG)
	mkdir -p $(TAG)/ThePEG
	cp $(DISTFILES) $(TAG)/ThePEG
	for dir in $(SUBDIRS) src Doc lib Templates Planning/ProofOfConcept ; do cd $$dir ; $(MAKE) -$(MAKEFLAGS) TAG=$(TAG) VERSION=$(VERSION) dist ; cd .. ; done
	tar czf $(TAG).tar.gz $(TAG)
	rm -rf $(TAG)

snapshot: doc
	$(MAKE) -$(MAKEFLAGS) thesnapshot SNAPTAG=ThePEG-`/bin/date '+%y%m%d'`

thesnapshot:
	rm -rf $(SNAPTAG)
	mkdir $(SNAPTAG)
	cvs export -D today ThePEG
	mv ThePEG/ThePEG $(SNAPTAG)
	cp Doc/*.html $(SNAPTAG)/ThePEG/Doc
	tar czf $(SNAPTAG).tgz $(SNAPTAG)
	rm -rf $(SNAPTAG)


