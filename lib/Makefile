LIBRARIES = libThePEG.so

DISTFILES = Makefile

include ../Config/Makefile.common

lib: libThePEG.so libCLHEP.so

libCLHEP.so:
	./fixCLHEP $(CLHEPPATH) $(CLHEPLIB)

LIBFILES = libThePEG.so libCLHEP.so

libThePEG.so: *.o
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAG) $(CXXOPTFLAG) $(CXXDLFLAGS) $^ -o $@

