DISTFILES = *.html h2html.in h2html.awk keywords.sed


include ../Config/Makefile.common

doc: refman

distclean: clean
	rm -f *.html h2html

%: %.conf
	doxygen $<
