// -*- C++ -*-
//
// GraphvizPlot.cc is a part of Herwig++ - A multi-purpose Monte Carlo event generator
// Copyright (C) 2002-2007 The Herwig Collaboration
//
// Herwig++ is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the GraphvizPlot class.
//

#include "GraphvizPlot.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/EventRecord/Event.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include <HepMCHelper.h>

using namespace ThePEG;
using namespace Herwig;

namespace {
  const string header = "digraph test {\nrankdir=LR;\nranksep=1.5;\n";
}

void GraphvizPlot::dofinish() {
  AnalysisHandler::dofinish();
  cout << "\nGraphvizPlot: plots can be generated like this:\n"
       << "GraphvizPlot: 'dot -Tpng " 
       << generator()->filename() 
       << '-'
       << name() 
       << "-NNN.dot > plot.png'";
}

void GraphvizPlot::analyze(tEventPtr event, long, int, int) {
  if (event->number() != _eventNumber) return;

  ostringstream fname;
  fname << generator()->filename() << '-' 
	<< name() << '-'
	<< event->number() << ".dot";
  ofstream hepmcdotfile(fname.str().c_str());
  
  hepmcdotfile << header 
	       << "node [width=0.1,height=0.1,shape=point,label=\"\"];\n";

  HepMC::GenEvent * hepmc = 
    HepMCConverter<HepMC::GenEvent>::convert(*event);
  
  //  hepmc->print(hepmcfile);

  // loop over all vertices
  for (HepMC::GenEvent::vertex_const_iterator 
	 it = hepmc->vertices_begin();
       it !=  hepmc->vertices_end();
       ++it) {

    // loop over incoming lines
    for (HepMC::GenVertex::particles_in_const_iterator 
	   jt = (*it)->particles_in_const_begin() ;
	 jt != (*it)->particles_in_const_end() ;
	 ++jt) {

      if ((*jt)->production_vertex()) continue;
      
      hepmcdotfile << (*jt)->barcode() << " -> "
		   << (*it)->barcode() << " [label=\""
		   << generator()->
	getParticleData((*jt)->pdg_id())->PDGName()
		   << "\"]\n";
      
    }
    
    // loop over outgoing lines
    for (HepMC::GenVertex::particles_out_const_iterator 
	   jt = (*it)->particles_out_const_begin() ;
	 jt != (*it)->particles_out_const_end() ;
	 ++jt) {
      hepmcdotfile << (*it)->barcode() << " -> ";

      if ((*jt)->end_vertex())
	hepmcdotfile << (*jt)->end_vertex()->barcode();
      else
	hepmcdotfile << (*jt)->barcode();
      
      hepmcdotfile << " [label=\"" 
		   << generator()->
	getParticleData((*jt)->pdg_id())->PDGName()
		   << "\"]\n";
    }
    
    if ((*it)->check_momentum_conservation() > 1.0)
      hepmcdotfile << (*it)->barcode() 
		   << " [color=red,width=0.2,height=0.2]\n";
    
    hepmcdotfile << '\n';
  }
  hepmcdotfile << '}' << endl;
  delete hepmc;
  hepmcdotfile.close();
}

LorentzRotation GraphvizPlot::transform(tEventPtr) const {
  return LorentzRotation();
  // Return the Rotation to the frame in which you want to perform the analysis.
}


void GraphvizPlot::analyze(tPPtr) {}

void GraphvizPlot::persistentOutput(PersistentOStream & os) const {
  os << _eventNumber;
}

void GraphvizPlot::persistentInput(PersistentIStream & is, int) {
  is >> _eventNumber;
}

ClassDescription<GraphvizPlot> GraphvizPlot::initGraphvizPlot;
// Definition of the static class description member.

void GraphvizPlot::Init() {

  static ClassDocumentation<GraphvizPlot> documentation
    ("There is no documentation for the GraphvizPlot class");

  static Parameter<GraphvizPlot,long> interfaceEventNumber
    ("EventNumber",
     "The number of the event that should be drawn.",
     &GraphvizPlot::_eventNumber, 1, 1, 1,
     false, false, Interface::lowerlim);
}

