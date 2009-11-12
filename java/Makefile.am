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

CLEANFILES = ThePEG.jar thepeg

nodist_pkglib_DATA = ThePEG.jar

dist_noinst_DATA = $(JAVASOURCES) jar-manifest

bin_SCRIPTS = thepeg
EXTRA_DIST = thepeg.install

clean-local:
	rm -rf ThePEG

ThePEG:
	mkdir -p ThePEG
	for file in $(JAVASOURCES) jar-manifest; do \
           cd ThePEG; $(LN_S) ../$(srcdir)/$$file $$file; cd ..; done

ThePEG.jar: ThePEG $(JAVASOURCES)
	$(JAVAC) -source 1.4 `for file in $(JAVASOURCES); do echo ThePEG/$$file; done`
	$(JAR) cmf ThePEG/jar-manifest ThePEG.jar ThePEG/*.class

thepeg: thepeg.install Makefile
	sed -e s:@pkglibdir[@]:$(pkglibdir):g \
            -e s:@bindir[@]:$(bindir):g \
            -e s:@java[@]:$(JAVA):g $(srcdir)/thepeg.install > thepeg
	chmod +x thepeg


test: ThePEG.jar
	$(JAVA) -jar ThePEG.jar ../src/setupThePEG.bin -d 1 -L../lib \
                -L../../Pythia7/lib -r ../../Pythia7/lib/Pythia7Defaults.rpo

check-local:
	$(JAVA) -Djava.awt.headless=true -jar ThePEG.jar --classcheck

installcheck-local:
	$(DESTDIR)$(bindir)/thepeg --classcheck
