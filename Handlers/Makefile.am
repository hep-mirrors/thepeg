mySOURCES = EventHandler.cc SubProcessHandler.cc \
            HandlerGroup.cc Hint.cc XComb.cc AnalysisHandler.cc \
            CascadeHandler.cc MultipleInteractionHandler.cc DecayHandler.cc \
            EventManipulator.cc StepHandler.cc HadronizationHandler.cc \
            HandlerBase.cc \
            FlavourGenerator.cc LuminosityFunction.cc \
            FixedCMSLuminosity.cc StandardEventHandler.cc  \
            SamplerBase.cc  ClusterCollapser.cc \
            PtGenerator.cc ZGenerator.cc   \
            StandardXComb.cc

DOCFILES = AnalysisHandler.h CascadeHandler.h \
           DecayHandler.h EventHandler.h EventManipulator.h \
           FixedCMSLuminosity.h FlavourGenerator.h HadronizationHandler.h \
           HandlerBase.h HandlerGroup.h Hint.h \
           LuminosityFunction.h \
           MultipleInteractionHandler.h StandardEventHandler.h \
           StepHandler.h SubProcessHandler.h XComb.h LastXCombInfo.h \
           SamplerBase.h  ClusterCollapser.h \
           PtGenerator.h ZGenerator.h   \
           StandardXComb.h

INCLUDEFILES = $(DOCFILES) AnalysisHandler.icc CascadeHandler.icc \
               DecayHandler.icc DecayHandler.xh \
               EventHandler.icc EventManipulator.icc \
               FixedCMSLuminosity.icc FlavourGenerator.icc \
               HadronizationHandler.icc HandlerBase.icc HandlerGroup.icc \
               HandlerGroup.tcc Hint.icc \
               LuminosityFunction.icc \
               MultipleInteractionHandler.icc StandardEventHandler.icc \
               StandardEventHandler.fh StepHandler.icc \
               SubProcessHandler.fh SubProcessHandler.icc XComb.icc \
               EventHandler.fh  \
               LastXCombInfo.icc SamplerBase.icc SamplerBase.fh \
                ClusterCollapser.fh ClusterCollapser.icc \
               PtGenerator.icc ZGenerator.icc  \
                StandardXComb.fh \
               StandardXComb.icc


noinst_LTLIBRARIES = libThePEGHandlers.la
pkglib_LTLIBRARIES = FixedCMSLuminosity.la \
          ACDCSampler.la SimpleFlavour.la GaussianPtGenerator.la \
          SimpleZGenerator.la


libThePEGHandlers_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
FixedCMSLuminosity_la_LDFLAGS = -module -version-info 1:0:0
FixedCMSLuminosity_la_SOURCES = FixedCMSLuminosity.cc FixedCMSLuminosity.h FixedCMSLuminosity.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
ACDCSampler_la_LDFLAGS = -module -version-info 1:0:0
ACDCSampler_la_SOURCES = ACDCSampler.cc ACDCSampler.h ACDCSampler.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
SimpleFlavour_la_LDFLAGS = -module -version-info 1:0:0
SimpleFlavour_la_SOURCES = SimpleFlavour.cc SimpleFlavour.h SimpleFlavour.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
GaussianPtGenerator_la_LDFLAGS = -module -version-info 1:0:0
GaussianPtGenerator_la_SOURCES = GaussianPtGenerator.cc GaussianPtGenerator.h GaussianPtGenerator.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
SimpleZGenerator_la_LDFLAGS = -module -version-info 1:0:0
SimpleZGenerator_la_SOURCES = SimpleZGenerator.cc SimpleZGenerator.h SimpleZGenerator.icc
