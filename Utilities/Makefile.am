
mySOURCES = SimplePhaseSpace.cc Debug.cc DescriptionList.cc Maths.cc \
          Direction.cc DynamicLoader.cc Timer.cc StringUtils.cc \
          Exception.cc ClassDescription.cc CFileLineReader.cc \
          XSecStat.cc

DOCFILES = ClassDescription.h ClassTraits.h  Debug.h DescriptionList.h \
           HoldFlag.h Interval.h Maths.h Rebinder.h Selector.h \
           SimplePhaseSpace.h Triplet.h Direction.h UtilityBase.h \
           TypeInfo.h DynamicLoader.h Timer.h UnitIO.h EnumIO.h \
           DIterator.h StringUtils.h SystemUtils.h Exception.h Named.h \
           FixedSizeAllocator.h VSelector.h LoopGuard.h ObjectIndexer.h \
           CFileLineReader.h CompSelector.h XSecStat.h Throw.h MaxCmp.h \
	   Level.h

INCLUDEFILES = $(DOCFILES) ClassDescription.fh ClassDescription.icc \
               ClassDescription.tcc DescriptionList.icc HoldFlag.icc \
               Interval.fh Interval.icc Interval.tcc Maths.icc Rebinder.fh \
               Rebinder.icc Selector.icc Selector.tcc \
               SimplePhaseSpace.tcc SimplePhaseSpace.xh \
               Direction.icc Direction.xh UtilityBase.icc UtilityBase.tcc \
               Timer.icc StringUtils.icc \
               Exception.icc Exception.fh FixedSizeAllocator.icc \
               VSelector.icc VSelector.tcc ObjectIndexer.icc \
               CFileLineReader.fh CFileLineReader.icc XSecStat.icc \
               CompSelector.icc

noinst_LTLIBRARIES = libThePEGUtilities.la

libThePEGUtilities_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

