mySOURCES = HelicityVertex.cc LorentzPolarizationVector.cc LorentzSpinor.cc \
          LorentzSpinorBar.cc LorentzTensor.cc RhoDMatrix.cc SpinInfo.cc \
          FermionSpinInfo.cc VectorSpinInfo.cc ScalarSpinInfo.cc TensorSpinInfo.cc \
          LorentzRSSpinor.cc LorentzRSSpinorBar.cc RSFermionSpinInfo.cc

DOCFILES = HelicityVertex.h LorentzPolarizationVector.h LorentzSpinor.h \
           LorentzSpinorBar.h LorentzTensor.h RhoDMatrix.h SpinInfo.h \
           FermionSpinInfo.h VectorSpinInfo.h ScalarSpinInfo.h TensorSpinInfo.h \
           LorentzRSSpinor.h LorentzRSSpinorBar.h RSFermionSpinInfo.h	

INCLUDEFILES = $(DOCFILES) HelicityVertex.fh HelicityVertex.icc \
               LorentzPolarizationVector.icc LorentzSpinor.fh \
               LorentzSpinor.icc LorentzSpinorBar.fh LorentzSpinorBar.icc \
               LorentzTensor.icc FermionSpinInfo.fh RhoDMatrix.icc \
               SpinInfo.fh SpinInfo.icc \
               FermionSpinInfo.icc VectorSpinInfo.fh VectorSpinInfo.icc \
               ScalarSpinInfo.fh ScalarSpinInfo.icc \
               TensorSpinInfo.fh TensorSpinInfo.icc \
               HelicityDefinitions.h LorentzRSSpinor.icc LorentzRSSpinorBar.icc \
               LorentzRSSpinor.fh LorentzRSSpinorBar.fh RSFermionSpinInfo.fh \
               RSFermionSpinInfo.icc

noinst_LTLIBRARIES = libThePEGHelicity.la

libThePEGHelicity_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)
