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
           ThePEG/Config \
           ThePEG/Persistency \
           ThePEG/PDF \
           ThePEG/Helicity \
           ThePEG/Utilities \
           ThePEG/MatrixElement \
           ThePEG/Cuts \
           ThePEG/Analysis  

CLEANFILES = done-all-links $(DIRLINKS)

## replace ThePEG with $(PACKAGE)
## replace find with explicit list of directories

done-all-links: $(DIRLINKS)

$(DIRLINKS):
@EMPTY@ifdef SHOWCOMMAND
	mkdir -p ThePEG
	cd ThePEG; \
	for i in $(DIRLINKS); \
	do \
	$(LN_S) -f ../$(top_srcdir)/`basename $$i` ; \
	done
	echo "stamp" > done-all-links
@EMPTY@else
	@echo "sym-linking header files..."
	@mkdir -p ThePEG
	@cd ThePEG; \
	for i in $(DIRLINKS); \
	do \
	$(LN_S) -f ../$(top_srcdir)/`basename $$i` ; \
	done
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
