// -*- C++ -*-
#ifndef ThePEG_Pointers_H
#define ThePEG_Pointers_H

// This file declares typedefs of commonly used pointers in
// ThePEG. The standard way of declaring the typedefs is by using the
// <!id>ThePEG_DECLARE_CLASS_POINTERS<!!id> macro which in turn used
// the <class>Ptr<!!class> traits class to define normal pointers,
// normal const pointers, transient pointers and transient const
// pointers for a given class. For the standard classes, the following
// typedefs should be introduced for a class abbreviated with
// <!id>T<!!id>: TPtr for a normal (smart) pointer, cTPtr for a normal
// const pointer, tTPtr for a transient pointer and tcTPtr for
// transient const pointer.
//
// Do not make changes in this file. If you need to modify any of the
// standard pointer declarations used in ThePEG, edit a copy of this
// file and include it in an alternative config file which can be
// included in the main <a href="http:ThePEG.html">ThePEG.h</a>
// config file using the macro <!id>ThePEG_ALTERNATE_CONFIG<!!id>.

#include "ThePEG/Config/ThePEG.h"
// #include "Pointers.fh"
// #include "Pointers.xh"

namespace ThePEG {

// This macro helps us to declare pointers and stuff to standard classes.
#define ThePEG_DECLARE_TEMPLATE_POINTERS(full, abbrev)            \
  typedef typename Ptr<full>::pointer abbrev;                      \
  typedef typename Ptr<full>::const_pointer c ## abbrev;           \
  typedef typename Ptr<full>::transient_pointer t ## abbrev;       \
  typedef typename Ptr<full>::transient_const_pointer tc ## abbrev

#define ThePEG_DECLARE_POINTERS(full, abbrev)            \
  typedef Ptr<full>::pointer abbrev;                      \
  typedef Ptr<full>::const_pointer c ## abbrev;           \
  typedef Ptr<full>::transient_pointer t ## abbrev;       \
  typedef Ptr<full>::transient_const_pointer tc ## abbrev

#define ThePEG_DECLARE_CLASS_POINTERS(full, abbrev)             \
  class full;                                                    \
  ThePEG_DECLARE_POINTERS(full, abbrev)

ThePEG_DECLARE_CLASS_POINTERS(InterfacedBase,IBPtr);
ThePEG_DECLARE_CLASS_POINTERS(Interfaced,IPtr);
ThePEG_DECLARE_CLASS_POINTERS(ParticleData,PDPtr);
ThePEG_DECLARE_CLASS_POINTERS(MatcherBase,PMPtr);
ThePEG_DECLARE_CLASS_POINTERS(DecayMode,DMPtr);
ThePEG_DECLARE_CLASS_POINTERS(Particle,PPtr);
ThePEG_DECLARE_CLASS_POINTERS(EventHandler,EHPtr);
ThePEG_DECLARE_CLASS_POINTERS(EventGenerator,EGPtr);
ThePEG_DECLARE_CLASS_POINTERS(FullEventGenerator,FEGPtr);
ThePEG_DECLARE_CLASS_POINTERS(PartialEventGenerator,PEGPtr);
ThePEG_DECLARE_CLASS_POINTERS(CollisionHandler,CollHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(PartialCollisionHandler,PartCollHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(SubProcessHandler,SubHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(StepHandler,StepHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(Hint,HintPtr);
ThePEG_DECLARE_CLASS_POINTERS(HadronizationHandler,HadrHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(CascadeHandler,CascHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(MultipleInteractionHandler,MIHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(DecayHandler,DecayHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(PileupHandler,PileHdlPtr);
ThePEG_DECLARE_CLASS_POINTERS(LuminosityFunction,LumiFnPtr);
ThePEG_DECLARE_CLASS_POINTERS(KinematicalCuts,KinCutPtr);
ThePEG_DECLARE_CLASS_POINTERS(PartonExtractor,PExtrPtr);
ThePEG_DECLARE_CLASS_POINTERS(RandomGenerator,RanGenPtr);
ThePEG_DECLARE_CLASS_POINTERS(AnalysisHandler,AnaPtr);
ThePEG_DECLARE_CLASS_POINTERS(EventManipulator, EvtManipPtr);
ThePEG_DECLARE_CLASS_POINTERS(Decayer,DecayerPtr);
ThePEG_DECLARE_CLASS_POINTERS(Event,EventPtr);
ThePEG_DECLARE_CLASS_POINTERS(Collision,CollPtr);
ThePEG_DECLARE_CLASS_POINTERS(Step,StepPtr);
ThePEG_DECLARE_CLASS_POINTERS(SubProcess,SubProPtr);
ThePEG_DECLARE_CLASS_POINTERS(Strategy,StrategyPtr);
ThePEG_DECLARE_CLASS_POINTERS(XComb,XCombPtr);
ThePEG_DECLARE_CLASS_POINTERS(SBin,SBinPtr);
ThePEG_DECLARE_CLASS_POINTERS(RemnantHandler,RemHPtr);
ThePEG_DECLARE_CLASS_POINTERS(PDFBase,PDFPtr);
ThePEG_DECLARE_CLASS_POINTERS(MEBase,MEPtr);
ThePEG_DECLARE_CLASS_POINTERS(PhaseSpaceBase,PSPtr);
ThePEG_DECLARE_CLASS_POINTERS(StandardModelBase,SMPtr);
ThePEG_DECLARE_CLASS_POINTERS(PartonBin,PBPtr);
ThePEG_DECLARE_CLASS_POINTERS(ColourBase,CBPtr);
ThePEG_DECLARE_CLASS_POINTERS(SpinBase,SpinPtr);
ThePEG_DECLARE_CLASS_POINTERS(EventInfoBase,EIPtr);
ThePEG_DECLARE_CLASS_POINTERS(ReweightBase,ReweightPtr);
ThePEG_DECLARE_CLASS_POINTERS(ColourLine,ColinePtr);
ThePEG_DECLARE_POINTERS(Base,BPtr);

// ThePEG_DECLARE_CLASS_POINTERS(,);

}

// #include "Pointers.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Pointers.tcc"
#endif

#endif /* ThePEG_Pointers_H */
