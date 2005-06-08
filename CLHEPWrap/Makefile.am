mySOURCES = GenEventConverter.cc

DOCFILES = JamesRandom.h Lorentz5Vector.h LorentzRotation.h LorentzVector.h \
           PhysicalConstants.h RandomEngine.h Rotation.h SystemOfUnits.h \
           ThreeVector.h Transverse.h CLHEP.h GenEventConverter.h \
           RandExponential.h RandBreitWigner.h Matrix.h RandPoisson.h

INCLUDEFILES = $(DOCFILES) JamesRandom.fh Lorentz5Vector.fh \
               Lorentz5Vector.icc LorentzRotation.fh LorentzVector.fh \
               RandomEngine.fh Rotation.fh ThreeVector.fh Transverse.icc \
               Transverse.fh GenEventConverter.icc RandExponential.fh \
               RandBreitWigner.fh Matrix.fh RandPoisson.fh


noinst_LTLIBRARIES = libThePEGCLHEPWrap.la

libThePEGCLHEPWrap_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)
