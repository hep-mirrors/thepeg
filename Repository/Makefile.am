mySOURCES = EventGenerator.cc RandomGenerator.cc Strategy.cc BaseRepository.cc \
          Repository.cc StandardRandom.cc  \
           UseRandom.cc CurrentGenerator.cc Main.cc

DOCFILES = BaseRepository.h EventGenerator.h RandomGenerator.h \
           Repository.h StandardRandom.h Strategy.h  \
            UseRandom.h CurrentGenerator.h Main.h

INCLUDEFILES = $(DOCFILES) BaseRepository.icc BaseRepository.tcc \
               BaseRepository.xh EventGenerator.fh EventGenerator.icc \
               EventGenerator.tcc EventGenerator.xh RandomGenerator.icc \
               Repository.icc \
               Repository.tcc StandardRandom.icc Strategy.fh Strategy.icc \
               RandomGenerator.fh UseRandom.icc UseRandom.fh \
               CurrentGenerator.icc CurrentGenerator.fh \
               Main.icc

noinst_LTLIBRARIES = libThePEGRepo.la
pkglib_LTLIBRARIES = ThePEGStrategy.la MultiEventGenerator.la

libThePEGRepo_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
ThePEGStrategy_la_LDFLAGS = -module -version-info 1:0:0
ThePEGStrategy_la_SOURCES = ThePEGStrategy.cc  ThePEGStrategy.h ThePEGStrategy.icc 


# Version info should be updated if any interface or persistent I/O
# function is changed
MultiEventGenerator_la_LDFLAGS = -module -version-info 1:0:0
MultiEventGenerator_la_SOURCES = MultiEventGenerator.cc MultiEventGenerator.h MultiEventGenerator.icc 