JAVASOURCES = SetupThePEG.java ObjectFrame.java \
              Parameter.java FullSlider.java \
              PopCardPanel.java SwitchOption.java \
              Switch.java RefRef.java Reference.java \
              Interface.java RefVector.java \
              BrowserTree.java ObjectNode.java \
              ObjectRef.java ClassSelector.java \
              ObjectSelector.java StringParameter.java \
              Command.java ParVector.java RunSelector.java \
              RunFrame.java

CLEANFILES = ThePEG.jar thepeg.sh

nodist_pkglib_DATA = ThePEG.jar

dist_noinst_DATA = $(JAVASOURCES) jar-manifest

dist_noinst_SCRIPTS = thepeg.install

nodist_bin_SCRIPTS = thepeg.sh

clean-local:
	rm -rf ThePEG

ThePEG:
	mkdir -p ThePEG
	for file in $(JAVASOURCES) jar-manifest; do \
           cd ThePEG; $(LN_S) ../$(srcdir)/$$file $$file; cd ..; done

ThePEG.jar: ThePEG $(JAVASOURCES)
	$(JAVAC) -source 1.4 `for file in $(JAVASOURCES); do echo ThePEG/$$file; done`
	$(JAR) cmf ThePEG/jar-manifest ThePEG.jar ThePEG/*.class

thepeg.sh: $(srcdir)/thepeg.install Makefile
	sed -e s:@path@:$(pkglibdir):g -e s:@java@:$(JAVA):g $(srcdir)/thepeg.install > thepeg.sh


test: ThePEG.jar
	$(JAVA) -jar ThePEG.jar ../src/setupThePEG.bin -d 1 -L../lib \
                -L../../Pythia7/lib -r ../../Pythia7/lib/Pythia7Defaults.rpo

check-local:
	$(JAVA) -jar ThePEG.jar --classcheck

installcheck-local:
	$(DESTDIR)$(bindir)/thepeg.sh --classcheck

