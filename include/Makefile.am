BUILT_SOURCES = done-all-links

DIRLINKS = ThePEG/Repository \
           ThePEG/EventRecord \
           ThePEG/Pointer \
           ThePEG/StandardModel \
           ThePEG/CLHEPWrap \
           ThePEG/PDT \
           ThePEG/ACDC \
           ThePEG/Interface \
           ThePEG/Handlers \
           ThePEG/LesHouches \
           ThePEG/Persistency \
           ThePEG/PDF \
           ThePEG/Helicity \
           ThePEG/Utilities \
           ThePEG/MatrixElement \
           ThePEG/Cuts \
           ThePEG/Analysis

CONFIGHEADERS = ThePEG/Config/Complex.h ThePEG/Config/Constants.h \
                ThePEG/Config/Containers.h ThePEG/Config/Pointers.h \
                ThePEG/Config/ThePEG.h ThePEG/Config/Units.h \
                ThePEG/Config/algorithm.h ThePEG/Config/std.h

CLEANFILES = done-all-links $(DIRLINKS) $(CONFIGHEADERS) \
             ThePEG/Config/config.h

## replace ThePEG with $(PACKAGE)
## replace find with explicit list of directories

done-all-links: $(DIRLINKS) $(CONFIGHEADERS)


$(DIRLINKS):
@EMPTY@ifdef SHOWCOMMAND
	mkdir -p ThePEG
	cd ThePEG; \
	for i in $(DIRLINKS); \
	do \
	$(LN_S) -f ../$(top_srcdir)/`basename $$i` ; \
	done
	mkdir -p ThePEG/Config
	cd ThePEG/Config; \
        for file in $(CONFIGHEADERS); \
        do \
          $(LN_S) -f ../../$(top_srcdir)/Config/`basename $$file` . ; \
	done
	cd ThePEG/Config; $(LN_S) -f ../../../Config/config.h .
	echo "stamp" > done-all-links
@EMPTY@else
	@echo "sym-linking header files..."
	@mkdir -p ThePEG
	@cd ThePEG; \
	for i in $(DIRLINKS); \
	do \
	$(LN_S) -f ../$(top_srcdir)/`basename $$i` ; \
	done
	@mkdir -p ThePEG/Config
	@cd ThePEG/Config; \
        for file in $(CONFIGHEADERS); \
        do \
          $(LN_S) -f ../../$(top_srcdir)/Config/`basename $$file` . ; \
	done
	@cd ThePEG/Config; $(LN_S) -f ../../../Config/config.h .
	@echo "stamp" > done-all-links
@EMPTY@endif

install-data-local:
	find ThePEG -follow -name '*.h' \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(includedir)/\{\} \;
	find ThePEG -follow -name '*.icc' \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(includedir)/\{\} \;
	find ThePEG -follow -name '*.tcc' \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(includedir)/\{\} \;
	find ThePEG -follow -name '*.fh'  \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(includedir)/\{\} \;
	find ThePEG -follow -name '*.xh'  \
          -exec $(install_sh_DATA) \{\} $(DESTDIR)$(includedir)/\{\} \;

uninstall-local:
	rm -rf $(DESTDIR)$(includedir)/ThePEG
