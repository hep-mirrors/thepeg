CLEANFILES = AllInterfaces.h MoreInterfaces.h

docdir = $(pkgdatadir)/Doc

doc_DATA = refman.conf refman.h

dist_doc_DATA = repository.hlp MakeDocs.in

doc_SCRIPTS = fixinterfaces.pl

clean-local: html-clean

html-clean:
	rm -rf refman-html refman-latex ThePEG-refman.tag

html-local: refman-html

pdf-local: refman-html
	if test -d refman-latex; then cd refman-latex; make refman.pdf; fi

AllInterfaces.h: MakeDocs.in
	$(top_builddir)/src/setupThePEG --init --exitonerror -L$(top_builddir)/lib MakeDocs.in

MoreInterfaces.h: MakeDocs.in
	$(top_builddir)/src/setupThePEG --init --exitonerror -L$(top_builddir)/lib MakeDocs.in

refman-html: refman.conf refman.h AllInterfaces.h MoreInterfaces.h
	$(srcdir)/fixinterfaces.pl AllInterfaces.h
	$(srcdir)/fixinterfaces.pl MoreInterfaces.h
	doxygen $<

install-data-local:
	if test -d refman-html; then $(mkdir_p) $(DESTDIR)$(docdir);\
	find refman-html -follow -name '*.*' \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(docdir)/\{\} \;; \
	$(install_sh_DATA) ThePEG-refman.tag $(DESTDIR)$(docdir)/ThePEG-refman.tag; fi
	if test -d refman-latex -a -f refman-latex/refman.pdf; then \
	$(install_sh_DATA) refman-latex/refman.pdf $(DESTDIR)$(docdir)/refman.pdf; fi

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)/refman-html \
	$(DESTDIR)$(docdir)/ThePEG-refman.tag \
	$(DESTDIR)$(docdir)/refman.pdf

