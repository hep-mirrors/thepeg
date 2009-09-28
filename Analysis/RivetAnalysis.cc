// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RivetAnalysis class.
//

#include "RivetAnalysis.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/ParVector.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Vectors/HepMCConverter.h"
#include "ThePEG/Config/HepMCHelper.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "HepMC/GenEvent.h"
#include "Rivet/AnalysisHandler.hh"

using namespace ThePEG;

RivetAnalysis::RivetAnalysis() : _rivet() 
{}

void RivetAnalysis::analyze(ThePEG::tEventPtr event, long ieve, int loop, int state) {
  AnalysisHandler::analyze(event, ieve, loop, state);
  // Rotate to CMS, extract final state particles and call analyze(particles).
  // convert to hepmc
  HepMC::GenEvent * hepmc = ThePEG::HepMCConverter<HepMC::GenEvent>::convert(*event);
  // analyse the event
  _rivet->analyze(*hepmc);
  // delete hepmc event
  delete hepmc;
}

ThePEG::IBPtr RivetAnalysis::clone() const {
  return new_ptr(*this);
}

ThePEG::IBPtr RivetAnalysis::fullclone() const {
  return new_ptr(*this);
}

void RivetAnalysis::persistentOutput(ThePEG::PersistentOStream & os) const {
  os << _analyses;
}

void RivetAnalysis::persistentInput(ThePEG::PersistentIStream & is, int) {
  is >> _analyses;
}

ThePEG::ClassDescription<RivetAnalysis> RivetAnalysis::initRivetAnalysis;
// Definition of the static class description member.

void RivetAnalysis::Init() {

  static ThePEG::ClassDocumentation<RivetAnalysis> documentation
    ("The RivetAnalysis class is a simple class to allow analyses"
     " from the Rivet library to be called from ThePEG");

  static ThePEG::ParVector<RivetAnalysis,string> interfaceAnalyses
    ("Analyses",
     "The names of the Rivet analyses to use",
     &RivetAnalysis::_analyses, -1, "", "","" "",
     false, false, ThePEG::Interface::nolimits);


  static Parameter<RivetAnalysis,string> interfaceFilename
    ("Filename",
     "The name of the file where the AIDA histograms are put. If empty, "
     "the run name will be used instead. '.aida' will in any case be "
     "appended to the file name.",
     &RivetAnalysis::filename, "", true, false);


  interfaceAnalyses.rank(10);

}

void RivetAnalysis::dofinish() {
  AnalysisHandler::dofinish();
  _rivet->setCrossSection(generator()->integratedXSec()/picobarn);
  _rivet->finalize();
  _rivet->tree().commit();
}

void RivetAnalysis::doinitrun() {
  AnalysisHandler::doinitrun();
  if(_analyses.empty()) 
    throw ThePEG::Exception() << "Must have at least one analysis loaded in "
			      << "RivetAnalysis::doinitrun()"
			      << ThePEG::Exception::runerror;
  // create Rivet analysis handler
  string fname = filename;
  if ( fname.empty() ) fname = generator()->runName();
  _rivet = new Rivet::AnalysisHandler(fname);
  // specify the analyses to be used
  for(unsigned int ix=0;ix<_analyses.size();++ix) {
    _rivet->addAnalysis(_analyses[ix]);
  }
  // initialize the rivet analysis handler
  _rivet->init();
}
