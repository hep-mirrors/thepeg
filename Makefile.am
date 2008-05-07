if JAVAGUI
  JAVADIR = java
endif
MAINDIRS = include Config Utilities Helicity Interface LesHouches Vectors \
          PDT PDF Persistency Handlers MatrixElement Pointer ACDC \
          StandardModel Repository EventRecord Cuts Analysis lib src Doc

DIST_SUBDIRS = $(MAINDIRS) java

SUBDIRS = $(MAINDIRS) $(JAVADIR)

pkglib_SCRIPTS = libtool

EXTRA_DIST = GUIDELINES debian

DISTCHECK_CONFIGURE_FLAGS = --enable-unitchecks

dist-hook:
	rm -rf `find $(distdir)/debian -name '.svn'`
