SOURCES = runThePEG.cc runPartial.cc setupThePEG.cc

OBJECTS = runThePEG.o runPartial.o setupThePEG.o

PROGS = runThePEG.exe setupThePEG.exe runPartial

DISTFILES = Makefile SimpleLEP.in setupThePEG.cc setupThePEG \
            setupThePEG.install runPartial.cc runThePEG.cc runThePEG \
            runThePEG.install ThePEGDefaults.in ThePEGParticles.in

.PHONY: Lib save

%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $(COMPILER_FLAG) $(CXXDEBUGFLAG) $(CXXOPTFLAG) $(DEFS) $(INCLUDES) $(CXXEXT) $<

include ../Config/Makefile.common

LIBFILES = ../lib/ThePEGDefaults.rpo ThePEGParticles.in ThePEGDefaults.in setupThePEG.exe runThePEG.exe

install-local: ../lib/ThePEGDefaults.rpo runThePEG.exe setupThePEG.exe
	mkdir -p $(INSTALLBIN)
	sed -e s:@:$(INSTALLLIB):g setupThePEG.install > $(INSTALLBIN)/setupThePEG
	sed -e s:@:$(INSTALLLIB):g runThePEG.install > $(INSTALLBIN)/runThePEG
	chmod 755 $(INSTALLBIN)/setupThePEG $(INSTALLBIN)/runThePEG

Lib:
	cd .. ; $(MAKE) -$(MAKEFLAGS) lib

progs: $(PROGS)

current: setupThePEG.exe runThePEG.exe 

test: SimpleLEP.out

check: SimpleLEP.out

init: ../lib/ThePEGDefaults.rpo

$(PROGS): ../lib/libThePEG.so ../lib/libThePEGPDF.so ../lib/libThePEGME.so ../lib/libThePEGRepo.so ../lib/libThePEGHandlers.so ../lib/libThePEGEvent.so ../lib/libThePEGPDT.so ../lib/libThePEGSM.so ../lib/libThePEGInter.so ../lib/libThePEGHelicity.so 

SimpleLEP.out: SimpleLEP.run runThePEG.exe
	time ./runThePEG -d 0 SimpleLEP.run

SimpleLHC.out: SimpleLHC.run runThePEG.exe
	time ./runThePEG -d 1 SimpleLHC.run

SimpleLEP.run: SimpleLEP.in ../lib/ThePEGDefaults.rpo setupThePEG.exe
	./setupThePEG SimpleLEP.in

SimpleLHC.run: SimpleLHC.in ../lib/ThePEGDefaults.rpo setupThePEG.exe
	./setupThePEG SimpleLHC.in

../lib/ThePEGDefaults.rpo: ThePEGParticles.in ThePEGDefaults.in setupThePEG.exe
	./setupThePEG -init

setupThePEG.exe: setupThePEG.o 
	$(CXX) $(CXXEXT) $(LINKFLAGS) -o $@ $< -L$(LIBDIR) $(THEPEGLIBS) $(LIBS)

runThePEG.exe: runThePEG.o 
	$(CXX) $(CXXEXT) $(LINKFLAGS) -o $@ $< -L$(LIBDIR) $(THEPEGLIBS) $(LIBS)

runPartial: runPartial.o 
	export LD_RUN_PATH=$(RPATH); $(CXX) $(CXXEXT) $(LINKFLAGS) -o $@ $< -L$(LIBDIR) $(THEPEGLIBS) $(LIBS)

testrun: testrun.o 
	export LD_RUN_PATH=$(RPATH); $(CXX) $(CXXEXT) $(LINKFLAGS) -o $@ $< -L$(LIBDIR) $(THEPEGLIBS) $(LIBS)

save:
	mkdir -p save
	csh -c "cp -f ../lib/ThePEGDefaults.rpo *.out *.log *.run *.dump *.tex save"

distclean:
	rm -f *.log *.out *.run *.exe *.tex ../lib/ThePEGDefaults.rpo

# DO NOT DELETE THIS LINE -- g++dep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

  runThePEG.o: \
  runThePEG.cc \
  ../../ThePEG/Repository/EventGenerator.h \
  ../../ThePEG/Config/ThePEG.h \
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
  ../../ThePEG/Interface/InterfaceBase.fh \
  ../../ThePEG/Persistency/PersistentOStream.fh \
  ../../ThePEG/Persistency/PersistentIStream.fh \
  ../../ThePEG/Config/Units.h \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.fh \
  ../../ThePEG/CLHEPWrap/LorentzVector.fh \
  ../../ThePEG/CLHEPWrap/CLHEP.h \
  ../../ThePEG/CLHEPWrap/ThreeVector.fh \
  ../../ThePEG/CLHEPWrap/Transverse.fh \
  ../../ThePEG/CLHEPWrap/SystemOfUnits.h \
  ../../ThePEG/Utilities/UnitIO.h \
  ../../ThePEG/Config/Constants.h \
  ../../ThePEG/Config/std.h \
  ../../ThePEG/Config/Pointers.h \
  ../../ThePEG/Config/Containers.h \
  ../../ThePEG/Utilities/FixedSizeAllocator.h \
  ../../ThePEG/Utilities/Debug.h \
  ../../ThePEG/Utilities/Debug.icc \
  ../../ThePEG/Utilities/FixedSizeAllocator.icc \
  ../../ThePEG/Utilities/Named.h \
  ../../ThePEG/Utilities/Named.icc \
  ../../ThePEG/Repository/EventGenerator.fh \
  ../../ThePEG/Repository/RandomGenerator.h \
  ../../ThePEG/Interface/Interfaced.h \
  ../../ThePEG/Interface/InterfacedBase.h \
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
  ../../ThePEG/Utilities/Exception.h \
  ../../ThePEG/Utilities/Exception.fh \
  ../../ThePEG/Utilities/sstream.h \
  ../../ThePEG/Utilities/Exception.icc \
  ../../ThePEG/Interface/InterfaceBase.icc \
  ../../ThePEG/Interface/InterfacedBase.icc \
  ../../ThePEG/Interface/Interfaced.icc \
  ../../ThePEG/CLHEPWrap/RandomEngine.fh \
  ../../ThePEG/Repository/RandomGenerator.icc \
  ../../ThePEG/Repository/UseRandom.h \
  ../../ThePEG/Repository/UseRandom.icc \
  ../../ThePEG/Repository/CurrentGenerator.fh \
  ../../ThePEG/Repository/EventGenerator.xh \
  ../../ThePEG/Repository/EventGenerator.icc \
  ../../ThePEG/Repository/EventGenerator.tcc \
  ../../ThePEG/Persistency/PersistentIStream.h \
  ../../ThePEG/Config/Complex.h \
  ../../ThePEG/Persistency/InputDescription.h \
  ../../ThePEG/Persistency/InputDescription.icc \
  ../../ThePEG/Persistency/PersistentIStream.icc \
  ../../ThePEG/Persistency/PersistentIStream.tcc \
  ../../ThePEG/PDT/StandardMatchers.h \
  ../../ThePEG/PDT/Matcher.h \
  ../../ThePEG/PDT/MatcherBase.h \
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
  ../../ThePEG/Utilities/Direction.icc \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.icc \
  ../../ThePEG/CLHEPWrap/Transverse.icc \
  ../../ThePEG/Utilities/Selector.h \
  ../../ThePEG/Utilities/Selector.icc \
  ../../ThePEG/Utilities/Selector.tcc \
  ../../ThePEG/PDT/WidthGenerator.fh \
  ../../ThePEG/PDT/MassGenerator.fh \
  ../../ThePEG/PDT/DecayMode.fh \
  ../../ThePEG/PDT/ParticleData.icc \
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
  ../../ThePEG/PDT/Matcher.icc \
  ../../ThePEG/PDT/Matcher.tcc \
  ../../ThePEG/PDT/EnumParticles.h \
  ../../ThePEG/PDT/PYDECYDummy.h \
  ../../ThePEG/PDT/Decayer.h \
  ../../ThePEG/PDT/Decayer.fh \
  ../../ThePEG/Handlers/HandlerBase.h \
  ../../ThePEG/Handlers/HandlerBase.icc \
  ../../ThePEG/MatrixElement/Amplitude.h \
  ../../ThePEG/MatrixElement/Amplitude.icc \
  ../../ThePEG/PDT/Decayer.icc \
  ../../ThePEG/PDT/PYDECYDummy.icc \
  ../../ThePEG/Utilities/Timer.h \
  ../../ThePEG/Utilities/Timer.icc \
  ../../ThePEG/Utilities/DynamicLoader.h \
  ../../ThePEG/Utilities/DynamicLoader.icc \
  ../../ThePEG/Repository/Main.h \
  ../../ThePEG/Repository/Main.icc
  runPartial.o: \
  runPartial.cc \
  ../../ThePEG/Repository/EventGenerator.h \
  ../../ThePEG/Config/ThePEG.h \
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
  ../../ThePEG/Interface/InterfaceBase.fh \
  ../../ThePEG/Persistency/PersistentOStream.fh \
  ../../ThePEG/Persistency/PersistentIStream.fh \
  ../../ThePEG/Config/Units.h \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.fh \
  ../../ThePEG/CLHEPWrap/LorentzVector.fh \
  ../../ThePEG/CLHEPWrap/CLHEP.h \
  ../../ThePEG/CLHEPWrap/ThreeVector.fh \
  ../../ThePEG/CLHEPWrap/Transverse.fh \
  ../../ThePEG/CLHEPWrap/SystemOfUnits.h \
  ../../ThePEG/Utilities/UnitIO.h \
  ../../ThePEG/Config/Constants.h \
  ../../ThePEG/Config/std.h \
  ../../ThePEG/Config/Pointers.h \
  ../../ThePEG/Config/Containers.h \
  ../../ThePEG/Utilities/FixedSizeAllocator.h \
  ../../ThePEG/Utilities/Debug.h \
  ../../ThePEG/Utilities/Debug.icc \
  ../../ThePEG/Utilities/FixedSizeAllocator.icc \
  ../../ThePEG/Utilities/Named.h \
  ../../ThePEG/Utilities/Named.icc \
  ../../ThePEG/Repository/EventGenerator.fh \
  ../../ThePEG/Repository/RandomGenerator.h \
  ../../ThePEG/Interface/Interfaced.h \
  ../../ThePEG/Interface/InterfacedBase.h \
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
  ../../ThePEG/Utilities/Exception.h \
  ../../ThePEG/Utilities/Exception.fh \
  ../../ThePEG/Utilities/sstream.h \
  ../../ThePEG/Utilities/Exception.icc \
  ../../ThePEG/Interface/InterfaceBase.icc \
  ../../ThePEG/Interface/InterfacedBase.icc \
  ../../ThePEG/Interface/Interfaced.icc \
  ../../ThePEG/CLHEPWrap/RandomEngine.fh \
  ../../ThePEG/Repository/RandomGenerator.icc \
  ../../ThePEG/Repository/UseRandom.h \
  ../../ThePEG/Repository/UseRandom.icc \
  ../../ThePEG/Repository/CurrentGenerator.fh \
  ../../ThePEG/Repository/EventGenerator.xh \
  ../../ThePEG/Repository/EventGenerator.icc \
  ../../ThePEG/Repository/EventGenerator.tcc \
  ../../ThePEG/Persistency/PersistentIStream.h \
  ../../ThePEG/Config/Complex.h \
  ../../ThePEG/Persistency/InputDescription.h \
  ../../ThePEG/Persistency/InputDescription.icc \
  ../../ThePEG/Persistency/PersistentIStream.icc \
  ../../ThePEG/Persistency/PersistentIStream.tcc \
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
  ../../ThePEG/Utilities/Direction.icc \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.icc \
  ../../ThePEG/CLHEPWrap/Transverse.icc \
  ../../ThePEG/Utilities/Selector.h \
  ../../ThePEG/Utilities/Selector.icc \
  ../../ThePEG/Utilities/Selector.tcc \
  ../../ThePEG/PDT/WidthGenerator.fh \
  ../../ThePEG/PDT/MassGenerator.fh \
  ../../ThePEG/PDT/DecayMode.fh \
  ../../ThePEG/PDT/ParticleData.icc \
  ../../ThePEG/PDT/EnumParticles.h \
  ../../ThePEG/EventRecord/Event.h \
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
  ../../ThePEG/EventRecord/StandardSelectors.h \
  ../../ThePEG/EventRecord/SelectorBase.h \
  ../../ThePEG/EventRecord/SelectorBase.icc \
  ../../ThePEG/EventRecord/ParticleTraits.h \
  ../../ThePEG/EventRecord/Event.icc \
  ../../ThePEG/EventRecord/Collision.h \
  ../../ThePEG/EventRecord/Collision.icc \
  ../../ThePEG/EventRecord/Step.h \
  ../../ThePEG/EventRecord/Step.icc \
  ../../ThePEG/EventRecord/SubProcess.h \
  ../../ThePEG/EventRecord/SubProcess.icc \
  ../../ThePEG/EventRecord/SubProcess.tcc \
  ../../ThePEG/EventRecord/Step.tcc \
  ../../ThePEG/EventRecord/Collision.tcc \
  ../../ThePEG/EventRecord/Event.tcc \
  ../../ThePEG/Utilities/DynamicLoader.h \
  ../../ThePEG/Utilities/DynamicLoader.icc \
  ../../ThePEG/CLHEPWrap/GenEventConverter.h \
  ../../ThePEG/CLHEPWrap/GenEventConverter.icc
  setupThePEG.o: \
  setupThePEG.cc \
  ../../ThePEG/Repository/Repository.h \
  ../../ThePEG/Config/ThePEG.h \
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
  ../../ThePEG/Interface/InterfaceBase.fh \
  ../../ThePEG/Persistency/PersistentOStream.fh \
  ../../ThePEG/Persistency/PersistentIStream.fh \
  ../../ThePEG/Config/Units.h \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.fh \
  ../../ThePEG/CLHEPWrap/LorentzVector.fh \
  ../../ThePEG/CLHEPWrap/CLHEP.h \
  ../../ThePEG/CLHEPWrap/ThreeVector.fh \
  ../../ThePEG/CLHEPWrap/Transverse.fh \
  ../../ThePEG/CLHEPWrap/SystemOfUnits.h \
  ../../ThePEG/Utilities/UnitIO.h \
  ../../ThePEG/Config/Constants.h \
  ../../ThePEG/Config/std.h \
  ../../ThePEG/Config/Pointers.h \
  ../../ThePEG/Config/Containers.h \
  ../../ThePEG/Utilities/FixedSizeAllocator.h \
  ../../ThePEG/Utilities/Debug.h \
  ../../ThePEG/Utilities/Debug.icc \
  ../../ThePEG/Utilities/FixedSizeAllocator.icc \
  ../../ThePEG/Repository/BaseRepository.h \
  ../../ThePEG/Repository/BaseRepository.xh \
  ../../ThePEG/Interface/InterfaceBase.xh \
  ../../ThePEG/Utilities/Exception.h \
  ../../ThePEG/Utilities/Exception.fh \
  ../../ThePEG/Utilities/sstream.h \
  ../../ThePEG/Utilities/Exception.icc \
  ../../ThePEG/Interface/ClassDocumentation.fh \
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
  ../../ThePEG/Interface/InterfaceBase.icc \
  ../../ThePEG/Interface/InterfacedBase.icc \
  ../../ThePEG/Repository/BaseRepository.icc \
  ../../ThePEG/Repository/BaseRepository.tcc \
  ../../ThePEG/Repository/EventGenerator.h \
  ../../ThePEG/Repository/EventGenerator.fh \
  ../../ThePEG/Repository/RandomGenerator.h \
  ../../ThePEG/Interface/Interfaced.h \
  ../../ThePEG/Interface/Interfaced.icc \
  ../../ThePEG/CLHEPWrap/RandomEngine.fh \
  ../../ThePEG/Repository/RandomGenerator.icc \
  ../../ThePEG/Repository/UseRandom.h \
  ../../ThePEG/Repository/UseRandom.icc \
  ../../ThePEG/Repository/CurrentGenerator.fh \
  ../../ThePEG/Repository/EventGenerator.xh \
  ../../ThePEG/Repository/EventGenerator.icc \
  ../../ThePEG/Repository/EventGenerator.tcc \
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
  ../../ThePEG/Utilities/Direction.icc \
  ../../ThePEG/CLHEPWrap/Lorentz5Vector.icc \
  ../../ThePEG/CLHEPWrap/Transverse.icc \
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
  ../../ThePEG/Repository/Repository.icc \
  ../../ThePEG/Repository/Repository.tcc \
  ../../ThePEG/PDT/EnumParticles.h \
  ../../ThePEG/Utilities/DynamicLoader.h \
  ../../ThePEG/Utilities/DynamicLoader.icc \
  ../../ThePEG/Utilities/SystemUtils.h \
  ../../ThePEG/Utilities/SystemUtils.icc

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
