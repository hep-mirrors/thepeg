DISTFILES = *.html h2html.in h2html.awk keywords.sed


include ../Config/Makefile.common

doc: refman

distclean: clean

%: %.conf
	./fixinterfaces.pl AllInterfaces.h
	doxygen $<
