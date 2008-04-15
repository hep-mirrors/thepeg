mySOURCES = LesHouchesReader.cc LesHouchesFileReader.cc  \
          LesHouchesEventHandler.cc

DOCFILES = LesHouchesReader.h LesHouchesFileReader.h  \
           LesHouchesEventHandler.h LesHouches.h

INCLUDEFILES = $(DOCFILES) LesHouchesReader.fh LesHouchesReader.icc \
               LesHouchesFileReader.fh LesHouchesFileReader.icc \
                LesHouchesEventHandler.fh \
               LesHouchesEventHandler.icc LesHouches.icc

pkglib_LTLIBRARIES = LesHouches.la MadGraphReader.la

# Version info should be updated if any interface or persistent I/O
# function is changed
MadGraphReader_la_LDFLAGS = -module $(LIBTOOLVERSIONINFO)
MadGraphReader_la_SOURCES = MadGraphReader.cc MadGraphReader.h \
                            MadGraphReader.icc MadGraphOneCut.cc \
                            MadGraphOneCut.icc MadGraphOneCut.h \
                            MadGraphTwoCut.cc MadGraphTwoCut.icc \
                            MadGraphTwoCut.h

# Version info should be updated if any interface or persistent I/O
# function is changed
LesHouches_la_LDFLAGS = -module -version-info 4:1:0
LesHouches_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

