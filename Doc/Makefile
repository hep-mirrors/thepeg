DISTFILES = *.html h2html.in h2html.awk keywords.sed


include ../Config/Makefile.common

distclean: clean
	rm -f *.html h2html

refman:
	doxygen refman.conf
