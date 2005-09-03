mySOURCES = ParticleData.cc DecayMode.cc MatcherBase.cc Matcher.cc Decayer.cc \
          MassGenerator.cc WidthGenerator.cc DummyDecayer.cc \
          ConstituentParticleData.cc FlatDecayer.cc PDT.cc

DOCFILES = CombinedMatcher.h DecayMode.h WidthGenerator.h Decayer.h \
           EnumParticles.h MassGenerator.h Matcher.h MatcherBase.h PDT.h \
           ParticleData.h StandardMatchers.h DummyDecayer.h \
           ConstituentParticleData.h FlatDecayer.h 

INCLUDEFILES = $(DOCFILES) DecayMode.fh DecayMode.icc \
               DecayMode.xh WidthGenerator.fh WidthGenerator.icc Decayer.fh \
               Decayer.icc MassGenerator.fh MassGenerator.icc Matcher.icc \
               Matcher.tcc MatcherBase.icc PDT.icc \
               DummyDecayer.icc ParticleData.icc ParticleData.tcc \
               ParticleData.xh ConstituentParticleData.icc FlatDecayer.icc

noinst_LTLIBRARIES = libThePEGPDT.la
pkglib_LTLIBRARIES = BreitWignerMass.la OmegaPhi3PiDecayer.la \
          V2PPDecayer.la DalitzDecayer.la Tau2HadronsDecayer.la \
          Onium3GDecayer.la QuarksToHadronsDecayer.la ColourPairDecayer.la \
          WeakToHadronsDecayer.la

libThePEGPDT_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

# Version info should be updated if any interface or persistent I/O
# function is changed
BreitWignerMass_la_LDFLAGS = -module -version-info 1:0:0
BreitWignerMass_la_SOURCES = BreitWignerMass.cc BreitWignerMass.h  BreitWignerMass.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
OmegaPhi3PiDecayer_la_LDFLAGS = -module -version-info 1:0:0
OmegaPhi3PiDecayer_la_SOURCES = OmegaPhi3PiDecayer.cc OmegaPhi3PiDecayer.h OmegaPhi3PiDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
V2PPDecayer_la_LDFLAGS = -module -version-info 1:0:0
V2PPDecayer_la_SOURCES = V2PPDecayer.cc V2PPDecayer.h V2PPDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
DalitzDecayer_la_LDFLAGS = -module -version-info 1:0:0
DalitzDecayer_la_SOURCES = DalitzDecayer.cc DalitzDecayer.h  DalitzDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
Tau2HadronsDecayer_la_LDFLAGS = -module -version-info 1:0:0
Tau2HadronsDecayer_la_SOURCES = Tau2HadronsDecayer.cc Tau2HadronsDecayer.h Tau2HadronsDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
Onium3GDecayer_la_LDFLAGS = -module -version-info 1:0:0
Onium3GDecayer_la_SOURCES = Onium3GDecayer.cc Onium3GDecayer.h Onium3GDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
QuarksToHadronsDecayer_la_LDFLAGS = -module -version-info 1:0:0
QuarksToHadronsDecayer_la_SOURCES = QuarksToHadronsDecayer.cc QuarksToHadronsDecayer.h QuarksToHadronsDecayer.icc

# Version info should be updated if any interface or persistent I/O
# function is changed
ColourPairDecayer_la_LDFLAGS = -module -version-info 1:0:0
ColourPairDecayer_la_SOURCES = ColourPairDecayer.cc ColourPairDecayer.h  ColourPairDecayer.icc 

# Version info should be updated if any interface or persistent I/O
# function is changed
WeakToHadronsDecayer_la_LDFLAGS = -module -version-info 1:0:0
WeakToHadronsDecayer_la_SOURCES = WeakToHadronsDecayer.cc WeakToHadronsDecayer.h WeakToHadronsDecayer.icc

