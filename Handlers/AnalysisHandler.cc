// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the AnalysisHandler class.
//

#include "AnalysisHandler.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/RefVector.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Repository/EventGenerator.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "AnalysisHandler.tcc"
#endif

using namespace ThePEG;

AnalysisHandler::~AnalysisHandler() {}

HistogramFactory & AnalysisHandler::histogramFactory() {
  return *(generator()->histogramFactory());
}

IBPtr AnalysisHandler::clone() const {
  return new_ptr(*this);
}

IBPtr AnalysisHandler::fullclone() const {
  return new_ptr(*this);
}

void AnalysisHandler::analyze(tEventPtr event, long ieve, int loop, int state) {
  if ( loop > 0 || state != 0 || !event ) return;
  transform(event);
  tPVector particles;
  event->selectFinalState(back_inserter(particles));
  analyze(particles);
  for ( int i = 0, N = theSlaves.size(); i < N; ++i )
    theSlaves[i]->analyze(particles);
}

LorentzRotation AnalysisHandler::transform(tEventPtr event) const {
  return LorentzRotation();
}

void AnalysisHandler::analyze(const tPVector & particles) {
  for ( int i = 0, N = particles.size(); i < N; ++i ) analyze(particles[i]);
}

void AnalysisHandler::analyze(tPPtr) {}

void AnalysisHandler::persistentOutput(PersistentOStream & os) const {
  os << theSlaves;
}

void AnalysisHandler::persistentInput(PersistentIStream & is, int) {
  is >> theSlaves;
}

ClassDescription<AnalysisHandler>
AnalysisHandler::initAnalysisHandler;

void AnalysisHandler::Init() {

  static ClassDocumentation<AnalysisHandler> documentation
    ("The ThePEG::AnalysisHandler class is the base class of all "
     "analysis handlers.");

  static RefVector<AnalysisHandler,AnalysisHandler> interfaceSlaves
    ("Slaves",
     "ThePEG::AnalysisHandler objects to be called for the same extracted "
     "particles as this one.",
     &AnalysisHandler::theSlaves, 0, true, false, true, false);

  interfaceSlaves.rank(10);

}
