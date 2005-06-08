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

BreitWignerMass_la_LDFLAGS = -module
BreitWignerMass_la_SOURCES = BreitWignerMass.cc BreitWignerMass.h  BreitWignerMass.icc

OmegaPhi3PiDecayer_la_LDFLAGS = -module
OmegaPhi3PiDecayer_la_SOURCES = OmegaPhi3PiDecayer.cc OmegaPhi3PiDecayer.h OmegaPhi3PiDecayer.icc

V2PPDecayer_la_LDFLAGS = -module
V2PPDecayer_la_SOURCES = V2PPDecayer.cc V2PPDecayer.h V2PPDecayer.icc

DalitzDecayer_la_LDFLAGS = -module
DalitzDecayer_la_SOURCES = DalitzDecayer.cc DalitzDecayer.h  DalitzDecayer.icc

Tau2HadronsDecayer_la_LDFLAGS = -module
Tau2HadronsDecayer_la_SOURCES = Tau2HadronsDecayer.cc Tau2HadronsDecayer.h Tau2HadronsDecayer.icc

Onium3GDecayer_la_LDFLAGS = -module
Onium3GDecayer_la_SOURCES = Onium3GDecayer.cc Onium3GDecayer.h Onium3GDecayer.icc

QuarksToHadronsDecayer_la_LDFLAGS = -module
QuarksToHadronsDecayer_la_SOURCES = QuarksToHadronsDecayer.cc QuarksToHadronsDecayer.h QuarksToHadronsDecayer.icc

ColourPairDecayer_la_LDFLAGS = -module
ColourPairDecayer_la_SOURCES = ColourPairDecayer.cc ColourPairDecayer.h  ColourPairDecayer.icc 

WeakToHadronsDecayer_la_LDFLAGS = -module
WeakToHadronsDecayer_la_SOURCES = WeakToHadronsDecayer.cc WeakToHadronsDecayer.h WeakToHadronsDecayer.icc

noinst_HEADERS = PYDECYDummy.h PYDECYDummy.icc
