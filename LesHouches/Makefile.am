mySOURCES = LesHouchesReader.cc LesHouchesFileReader.cc  \
          LesHouchesEventHandler.cc

DOCFILES = LesHouchesReader.h LesHouchesFileReader.h  \
           LesHouchesEventHandler.h LesHouches.h

INCLUDEFILES = $(DOCFILES) LesHouchesReader.fh LesHouchesReader.icc \
               LesHouchesFileReader.fh LesHouchesFileReader.icc \
                LesHouchesEventHandler.fh \
               LesHouchesEventHandler.icc LesHouches.icc

pkglib_LTLIBRARIES = LesHouches.la MadGraphReader.la

MadGraphReader_la_LDFLAGS = -module
MadGraphReader_la_SOURCES = MadGraphReader.cc MadGraphReader.h MadGraphReader.icc

LesHouches_la_LDFLAGS = -module
LesHouches_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

