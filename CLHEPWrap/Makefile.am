mySOURCES = LorentzRotation.cc SpinHalfLorentzRotation.cc

DOCFILES = JamesRandom.h Lorentz5Vector.h LorentzRotation.h LorentzVector.h \
           PhysicalConstants.h RandomEngine.h Rotation.h SystemOfUnits.h \
           ThreeVector.h Transverse.h CLHEP.h \
           RandExponential.h RandBreitWigner.h Matrix.h RandPoisson.h \
           SpinOneLorentzRotation.h LorentzRotation.h \
           SpinHalfLorentzRotation.h HepMCTraits.h HepMCConverter.h

INCLUDEFILES = $(DOCFILES) JamesRandom.fh Lorentz5Vector.fh \
               Lorentz5Vector.icc LorentzRotation.fh LorentzVector.fh \
               RandomEngine.fh Rotation.fh ThreeVector.fh Transverse.icc \
               Transverse.fh RandExponential.fh \
               RandBreitWigner.fh Matrix.fh RandPoisson.fh \
               SpinOneLorentzRotation.fh LorentzRotation.icc \
               SpinHalfLorentzRotation.icc HepMCConverter.icc \
               HepMCConverter.tcc

noinst_LTLIBRARIES = libThePEGCLHEPWrap.la

libThePEGCLHEPWrap_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

