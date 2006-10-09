mySOURCES = Event.cc Collision.cc SubProcess.cc Step.cc Particle.cc \
          EventInfoBase.cc ColourLine.cc ColourBase.cc SpinBase.cc \
          EventConfig.cc ColourSinglet.cc RemnantParticle.cc MultiColour.cc

DOCFILES = EventConfig.h Collision.h Event.h Particle.h ParticleTraits.h \
           SelectorBase.h StandardSelectors.h Step.h SubProcess.h \
           EventInfoBase.h ColourLine.h ColourBase.h SpinBase.h \
           ColourSinglet.h TmpTransform.h RemnantParticle.h MultiColour.h

INCLUDEFILES = $(DOCFILES) Collision.icc Collision.tcc Event.icc \
               Event.tcc Particle.fh Particle.icc Particle.tcc \
               SelectorBase.icc Step.icc Step.tcc SubProcess.icc \
               SubProcess.tcc EventInfoBase.icc ColourLine.icc ColourBase.icc \
               SpinBase.icc ColourSinglet.icc TmpTransform.icc \
               RemnantParticle.icc RemnantParticle.fh MultiColour.icc

noinst_LTLIBRARIES = libThePEGEvent.la
libThePEGEvent_la_SOURCES = $(mySOURCES) $(INCLUDEFILES)

include $(top_srcdir)/Config/Makefile.aminclude

