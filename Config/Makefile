SOURCES = Containers.cc

OBJECTS = Containers.o

DEBUGOBJECTS =

DOCFILES = ThePEG.h Constants.h Containers.h Pointers.h Units.h algorithm.h \
           std.h Complex.h

INCLUDEFILES = $(DOCFILES) config.h

DISTFILES = $(SOURCES) $(DOCFILES) Makefile.common.in Makefile \
            Makefile.install config.h.in

INCLUDEDIR = Config

install-local:
	mkdir -p $(INSTALLLIB)
	sed -e s:@:$(INSTALLLIB):g Makefile.install > $(INSTALLLIB)/Makefile
	sed -e s:../../ThePEG/lib:$(INSTALLLIB):g -e s:-I../../:-I$(INCLUDEINSTALL):g Makefile.common > $(INSTALLLIB)/Makefile.common

include ../Config/Makefile.common

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

  Containers.o: \
  Containers.cc \
  ThePEG.h \
  ../../ThePEG/Config/config.h \
  ../../ThePEG/Pointer/Ptr.h \
  ../../ThePEG/Pointer/RCPtr.fh \
  ../../ThePEG/Pointer/PtrTraits.h \
  ../../ThePEG/Pointer/RCPtr.h \
  ../../ThePEG/Pointer/ReferenceCounted.h \
  ../../ThePEG/Pointer/ReferenceCounted.icc \
  ../../ThePEG/Pointer/RCPtr.icc \
  ../../ThePEG/Utilities/Rebinder.fh \
  ../../ThePEG/Utilities/Interval.fh \
  ../../ThePEG/Utilities/ClassDescription.fh \
  ../../ThePEG/Config/ThePEG.h \
  ../../ThePEG/Interface/InterfaceBase.fh \
  ../../ThePEG/Persistency/PersistentOStream.fh \
  ../../ThePEG/Persistency/PersistentIStream.fh \
  Units.h \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.fh \
  ../../ThePEG/CLHEPWrap/LorentzVector.fh \
  ../../ThePEG/CLHEPWrap/ThreeVector.fh \
  ../../ThePEG/CLHEPWrap/Transverse.fh \
  ../../ThePEG/CLHEPWrap/SystemOfUnits.h \
  ../../ThePEG/CLHEPWrap/CLHEP.h \
  ../../ThePEG/Utilities/UnitIO.h \
  Constants.h \
  std.h \
  Pointers.h \
  Containers.h \
  ../../ThePEG/Utilities/FixedSizeAllocator.h \
  ../../ThePEG/Utilities/Debug.h \
  ../../ThePEG/Utilities/Debug.icc \
  ../../ThePEG/Utilities/FixedSizeAllocator.icc \
  ../../ThePEG/PDT/ParticleData.h \
  ../../ThePEG/PDT/PDT.h \
  ../../ThePEG/PDT/PDT.icc \
  ../../ThePEG/CLHEPWrap/PhysicalConstants.h \
  ../../ThePEG/CLHEPWrap/LorentzVector.h \
  ../../ThePEG/CLHEPWrap/Transverse.h \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.h \
  ../../ThePEG/Utilities/Math.h \
  ../../ThePEG/Utilities/Math.icc \
  ../../ThePEG/Utilities/Direction.h \
  ../../ThePEG/Utilities/Direction.xh \
  ../../ThePEG/Utilities/Exception.h \
  ../../ThePEG/Utilities/Exception.fh \
  ../../ThePEG/Utilities/sstream.h \
  ../../ThePEG/Utilities/Exception.icc \
  ../../ThePEG/Utilities/Direction.icc \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.icc \
  ../../ThePEG/CLHEPWrap/Transverse.icc \
  ../../ThePEG/Interface/Interfaced.h \
  ../../ThePEG/Interface/InterfacedBase.h \
  ../../ThePEG/Utilities/Named.h \
  ../../ThePEG/Utilities/Named.icc \
  ../../ThePEG/Utilities/ClassDescription.h \
  ../../ThePEG/Utilities/ClassTraits.h \
  ../../ThePEG/Utilities/DescriptionList.h \
  ../../ThePEG/Utilities/DescriptionList.icc \
  ../../ThePEG/Utilities/ClassDescription.icc \
  ../../ThePEG/Utilities/ClassDescription.tcc \
  ../../ThePEG/Utilities/HoldFlag.h \
  ../../ThePEG/Utilities/HoldFlag.icc \
  ../../ThePEG/Interface/InterfacedBase.xh \
  ../../ThePEG/Interface/InterfaceBase.h \
  ../../ThePEG/Interface/InterfaceBase.xh \
  ../../ThePEG/Interface/InterfaceBase.icc \
  ../../ThePEG/Interface/InterfacedBase.icc \
  ../../ThePEG/Interface/Interfaced.icc \
  ../../ThePEG/Utilities/Selector.h \
  ../../ThePEG/Utilities/Selector.icc \
  ../../ThePEG/Utilities/Selector.tcc \
  ../../ThePEG/PDT/WidthGenerator.fh \
  ../../ThePEG/PDT/MassGenerator.fh \
  ../../ThePEG/PDT/DecayMode.fh \
  ../../ThePEG/PDT/ParticleData.icc \
  ../../ThePEG/PDT/MatcherBase.h \
  ../../ThePEG/EventRecord/Particle.h \
  ../../ThePEG/EventRecord/EventConfig.h \
  ../../ThePEG/CLHEPWrap/LorentzRotation.h \
  ../../ThePEG/CLHEPWrap/LorentzRotation.fh \
  ../../ThePEG/EventRecord/ColourBase.h \
  ../../ThePEG/EventRecord/EventInfoBase.h \
  ../../ThePEG/EventRecord/EventInfoBase.icc \
  ../../ThePEG/EventRecord/ColourLine.h \
  ../../ThePEG/EventRecord/ColourSinglet.h \
  ../../ThePEG/EventRecord/ColourSinglet.icc \
  ../../ThePEG/EventRecord/ColourLine.icc \
  ../../ThePEG/EventRecord/ColourBase.icc \
  ../../ThePEG/EventRecord/SpinBase.h \
  ../../ThePEG/EventRecord/SpinBase.icc \
  ../../ThePEG/EventRecord/Particle.icc \
  ../../ThePEG/EventRecord/Particle.tcc \
  ../../ThePEG/PDT/MatcherBase.icc \
  ../../ThePEG/PDT/DecayMode.h \
  ../../ThePEG/PDT/Decayer.h \
  ../../ThePEG/PDT/Decayer.fh \
  ../../ThePEG/Handlers/HandlerBase.h \
  ../../ThePEG/Handlers/HandlerBase.icc \
  ../../ThePEG/MatrixElement/Amplitude.h \
  ../../ThePEG/Config/Complex.h \
  ../../ThePEG/MatrixElement/Amplitude.icc \
  ../../ThePEG/PDT/Decayer.icc \
  ../../ThePEG/PDT/DecayMode.icc \
  ../../ThePEG/Repository/EventGenerator.h \
  ../../ThePEG/Repository/EventGenerator.fh \
  ../../ThePEG/Repository/RandomGenerator.h \
  ../../ThePEG/CLHEPWrap/RandomEngine.fh \
  ../../ThePEG/Repository/RandomGenerator.icc \
  ../../ThePEG/Repository/UseRandom.h \
  ../../ThePEG/Repository/UseRandom.icc \
  ../../ThePEG/Repository/CurrentGenerator.fh \
  ../../ThePEG/Repository/EventGenerator.xh \
  ../../ThePEG/Repository/EventGenerator.icc \
  ../../ThePEG/Repository/EventGenerator.tcc

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
