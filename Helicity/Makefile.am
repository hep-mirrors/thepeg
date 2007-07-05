SUBDIRS = WaveFunction Vertex

mySOURCES = HelicityVertex.cc LorentzSpinor.cc \
          LorentzSpinorBar.cc LorentzTensor.cc RhoDMatrix.cc SpinInfo.cc \
          FermionSpinInfo.cc VectorSpinInfo.cc ScalarSpinInfo.cc TensorSpinInfo.cc \
          LorentzRSSpinor.cc LorentzRSSpinorBar.cc RSFermionSpinInfo.cc

DOCFILES = HelicityVertex.h LorentzPolarizationVector.h LorentzSpinor.h \
           LorentzSpinorBar.h LorentzTensor.h RhoDMatrix.h SpinInfo.h \
           FermionSpinInfo.h VectorSpinInfo.h ScalarSpinInfo.h TensorSpinInfo.h \
           LorentzRSSpinor.h LorentzRSSpinorBar.h RSFermionSpinInfo.h \
	   epsilon.h

INCLUDEFILES = $(DOCFILES) epsilon.icc HelicityVertex.fh HelicityVertex.icc \
               LorentzSpinor.fh LorentzSpinor.tcc LorentzSpinorBar.tcc \
               LorentzSpinor.icc LorentzSpinorBar.fh LorentzSpinorBar.icc \
               LorentzTensor.icc FermionSpinInfo.fh RhoDMatrix.icc \
               SpinInfo.fh SpinInfo.icc LorentzTensor.fh \
               FermionSpinInfo.icc VectorSpinInfo.fh VectorSpinInfo.icc \
               ScalarSpinInfo.fh ScalarSpinInfo.icc \
               TensorSpinInfo.fh TensorSpinInfo.icc LorentzTensor.tcc \
               HelicityDefinitions.h LorentzRSSpinor.icc LorentzRSSpinorBar.icc \
               LorentzRSSpinor.fh LorentzRSSpinorBar.fh RSFermionSpinInfo.fh \
               RSFermionSpinInfo.icc LorentzRSSpinor.tcc LorentzRSSpinorBar.tcc

noinst_LTLIBRARIES = libThePEGHelicity.la

libThePEGHelicity_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)
libThePEGHelicity_la_LIBADD = Vertex/libThePEGVertex.la \
			      WaveFunction/libThePEGWaveFunction.la

include $(top_srcdir)/Config/Makefile.aminclude

