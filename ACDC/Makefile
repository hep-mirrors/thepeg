SOURCES = test.cc

OBJECTS = 

DEBUGOBJECTS = 

DOCFILES = ACDCGenConfig.h ACDCGen.h ACDCGenCell.h ACDCTraits.h

INCLUDEFILES = $(DOCFILES) ACDCGen.icc ACDCGenCell.icc

DISTFILES = $(INCLUDEFILES) Makefile

INCLUDEDIR = ACDC

include ../Config/Makefile.common

test: test.o
	$(CXX) $(FLAGS) test.o -o test -lCLHEP

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

  test.o: \
  test.cc \
  ACDCGen.h \
  ACDCGenConfig.h \
  ACDCTraits.h \
  ACDCGenCell.h \
  ACDCGenCell.icc \
  ACDCGen.icc \
  DRand48Traits.h \
  fpudebug.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
