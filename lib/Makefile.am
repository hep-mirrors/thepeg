## workaround for OS X, automake doesn't realize it's meant to use c++
LINK = $(LIBTOOL) --tag=CXX --mode=link $(CXX) $(AM_CXXFLAGS) \
	$(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@

dist_pkgdata_DATA = ThePEG.el

pkglib_LTLIBRARIES = libThePEG.la

libThePEG_la_SOURCES =
libThePEG_la_LDFLAGS = -export-dynamic -L$(CLHEPPATH)/lib 
libThePEG_la_LIBADD = \
	$(top_builddir)/Utilities/libThePEGUtilities.la \
	$(top_builddir)/CLHEPWrap/libThePEGCLHEPWrap.la \
	$(top_builddir)/Persistency/libThePEGPersistency.la \
	$(top_builddir)/Config/libThePEGConfig.la \
	$(top_builddir)/PDF/libThePEGPDF.la \
	$(top_builddir)/MatrixElement/libThePEGME.la \
	$(top_builddir)/Repository/libThePEGRepo.la \
	$(top_builddir)/Handlers/libThePEGHandlers.la \
	$(top_builddir)/EventRecord/libThePEGEvent.la \
	$(top_builddir)/PDT/libThePEGPDT.la \
	$(top_builddir)/StandardModel/libThePEGSM.la \
	$(top_builddir)/Interface/libThePEGInter.la \
	$(top_builddir)/Helicity/libThePEGHelicity.la \
	$(CLHEPLIB) -ldl 

all-local: done-all-links

done-all-links:
	$(LN_S) -f ../*/.libs/*.so .
	echo "stamp" > done-all-links

clean-local:
	rm -f *.so done-all-links
