LIBRARIES = libThePEG.so

SODIRS = EventRecord Handlers Interface MatrixElement PDF PDT Repository \
         StandardModel

OBJECTS = ../Utilities/ClassDescription.o ../Config/Containers.o \
          ../Utilities/Debug.o ../Utilities/DescriptionList.o \
          ../Utilities/Direction.o ../Utilities/DynamicLoader.o \
          ../Utilities/Exception.o ../CLHEPWrap/GenEventConverter.o \
          ../Utilities/Math.o ../Persistency/PersistentIStream.o \
          ../Persistency/PersistentOStream.o ../Utilities/SimplePhaseSpace.o \
          ../Utilities/StringUtils.o ../Utilities/SystemUtils.o \
          ../Utilities/Timer.o

DISTFILES = Makefile fixCLHEP g++dep ThePEG.el

include ../Config/Makefile.common

lib: libThePEG.so libCLHEP.so
	@for dir in $(SODIRS); do for sofile in ../$$dir/*.so; do ln -s -f $$sofile .; done; done;

libCLHEP.so:
	./fixCLHEP $(CLHEPPATH) $(CLHEPLIB)

LIBFILES = libThePEG.so

libThePEG.so: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CXXDEBUGFLAG) $(CXXOPTFLAG) $(CXXDLFLAGS) $^ -o $@

install-local:
	mkdir -p $(INSTALLLIB); cp g++dep ThePEG.el $(INSTALLLIB)
	ln -sfn $(INSTALLLIB) $(PREFIX)/lib/ThePEG/current
	SRCDIR=`pwd`; cd $(INSTALLLIB); $$SRCDIR/fixCLHEP $(CLHEPPATH) $(CLHEPLIB)

