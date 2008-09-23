
mySOURCES = SimplePhaseSpace.cc Debug.cc DescriptionList.cc Maths.cc \
          Direction.cc DynamicLoader.cc StringUtils.cc \
          Exception.cc ClassDescription.cc CFileLineReader.cc \
          XSecStat.cc

DOCFILES = ClassDescription.h ClassTraits.h  Debug.h DescriptionList.h \
           HoldFlag.h Interval.h Maths.h Rebinder.h Selector.h \
           SimplePhaseSpace.h Triplet.h Direction.h UtilityBase.h \
           TypeInfo.h DynamicLoader.h UnitIO.h EnumIO.h \
           DIterator.h StringUtils.h SystemUtils.h Exception.h Named.h \
           VSelector.h LoopGuard.h ObjectIndexer.h \
           CFileLineReader.h CompSelector.h XSecStat.h Throw.h MaxCmp.h \
	   Level.h

INCLUDEFILES = $(DOCFILES) ClassDescription.fh \
               Interval.fh Interval.tcc Rebinder.fh \
               Selector.tcc SimplePhaseSpace.tcc SimplePhaseSpace.xh \
               Direction.xh UtilityBase.tcc \
               Exception.fh VSelector.tcc CFileLineReader.fh

noinst_LTLIBRARIES = libThePEGUtilities.la

libThePEGUtilities_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

