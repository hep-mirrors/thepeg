// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the GenEventConverter class.
//

#include "GenEventConverter.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "CLHEP/HepMC/GenParticle.h"
#include "CLHEP/HepMC/Flow.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/StandardSelectors.h"
#include "ThePEG/EventRecord/Collision.h"
#include "ThePEG/EventRecord/Step.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/EventHandler.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GenEventConverter.tcc"
#endif


using namespace ThePEG;
using namespace CLHEPMC;

GenEvent * GenEventConverter::convert(const Event & ev) {
  GenEventConverter converter(ev);
  return converter.geneve;
}

GenEventConverter::GenEventConverter(const Event & ev) {

  geneve = new GenEvent;

  geneve->set_event_number(ev.number());
  geneve->weights().push_back(ev.weight());

  tcCollHdlPtr collh;
  if ( ev.primaryCollision() && ( collh =
       dynamic_ptr_cast<tcCollHdlPtr>(ev.primaryCollision()->handler()) ) ) {

    // Get general event info if present.
    geneve->set_event_scale(sqrt(collh->lastScale()));
    geneve->set_alphaQCD(collh->SM().alphaS(collh->lastScale()));
    geneve->set_alphaQED(collh->SM().alphaEM(collh->lastScale()));
  }

  // Extract all particles.
  tcPVector all;
  ev.select(back_inserter(all), SelectAll());
  vertices.reserve(all.size()*2);

  // Create GenParticle's and map them to the ThePEG particles.
  for ( int i = 0, N = all.size(); i < N; ++i ) {
    tcPPtr p = all[i];
    GenParticle * gp = pmap[p] = createParticle(p);
    if ( p->hasColourInfo() ) {
      // Check if the particle is connected to colour lines, in which
      // case the lines are mapped to an integer and set in the
      // GenParticle's Flow info.
      tcColinePtr l;
      if ( l = p->colourLine() ) {
	if ( !member(flowmap, l) ) flowmap[l] = flowmap.size() + 500;
	gp->set_flow(1, flowmap[l]);
      }
      if ( l = p->antiColourLine() ) {
	if ( !member(flowmap, l) ) flowmap[l] = flowmap.size() + 500;
	gp->set_flow(2, flowmap[l]);
      }
    }

    if ( !p->children().empty() || p->next() ) {
      // If the particle has children it should have a decay vertex:
      vertices.push_back(Vertex());
      decv[p] = &vertices.back();
      vertices.back().in.insert(p);
    }

    if ( !p->parents().empty() || p->previous() ||
	 (p->children().empty() && !p->next()) ) {
      // If the particle has parents it should have a production
      // vertex. If neither parents or children it should still have a
      // dummy production vertex.
      vertices.push_back(Vertex());
      prov[p] = &vertices.back();
      vertices.back().out.insert(p);
    }
  }

  // Now go through the the particles again, and join the vertices.
  for ( int i = 0, N = all.size(); i < N; ++i ) {
    tcPPtr p = all[i];
    for ( int i = 0, N = p->children().size(); i < N; ++i )
      join(p, p->children()[i]);
    for ( int i = 0, N = p->parents().size(); i < N; ++i )
      join(p->parents()[i], p);
    if ( p->next() ) join(p, p->next());
    if ( p->previous() ) join(p->previous(), p);
  }

  // Time to create the GenVertex's
  for ( VertexMap::iterator it = prov.begin(); it != prov.end(); ++it )
    if ( !member(vmap, it->second) )
      vmap[it->second] = createVertex(it->second);
  for ( VertexMap::iterator it = decv.begin(); it != decv.end(); ++it )
    if ( !member(vmap, it->second) )
      vmap[it->second] = createVertex(it->second);

  // Now find the primary signal process vertex defined to be the
  // decay vertex of the first parton coming into the primary hard
  // sub-collision.
  tSubProPtr sub = ev.primarySubProcess();
  if ( sub && sub->incoming().first ) {
    const Vertex * prim = decv[sub->incoming().first];
    geneve->set_signal_process_vertex(vmap[prim]);
    vmap.erase(prim);
  }
  
  // Then add the rest of the vertices.
  for ( GenVertexMap::iterator it = vmap.begin(); it != vmap.end(); ++it )
    geneve->add_vertex(it->second);

}

GenParticle * GenEventConverter::createParticle(tcPPtr p) const {
  int status = 1;
  if ( !p->children().empty() || p->next() ) status = 2;
  GenParticle * gp = new GenParticle(p->momentum(), p->id(), status);
  // Note according to the documentation the momentum is stored in a
  // HepLorentzVector in GeV. But the default unit in CLHEP is
  // MeV. Here we will assume that the HepLorentzVector in HepMC keeps
  // to the standard CLHEP units.

  gp->setGeneratedMass(p->momentum().mass());

  if ( p->spinInfo() && p->spinInfo()->hasPolarization() ) {
    DPair pol = p->spinInfo()->polarization();
    gp->set_polarization(Polarization(pol.first, pol.second));
  }

  return gp;

}

void GenEventConverter::join(tcPPtr parent, tcPPtr child) {
  Vertex * dec = decv[parent];
  Vertex * pro = prov[child];
  if ( !pro || !dec ) throw GenEventConverterException()
    << "Found a reference to a ThePEG::Particle which was not in the Event."
    << Exception::eventerror;
  if ( pro == dec ) return;
  while ( !pro->in.empty() ) {
    dec->in.insert(*(pro->in.begin()));
    decv[*(pro->in.begin())] = dec;
    pro->in.erase(pro->in.begin());
  }
  while ( !pro->out.empty() ) {
    dec->out.insert(*(pro->out.begin()));
    prov[*(pro->out.begin())] = dec;
    pro->out.erase(pro->out.begin());
  }
}

GenVertex * GenEventConverter::createVertex(Vertex * v) {
  if ( !v ) throw GenEventConverterException()
    << "Found internal null Vertex." << Exception::abortnow;

  GenVertex * gv = new GenVertex();

  // We assume that the vertex position is the average of the decay
  // vertices of all incoming and the creation vertices of all
  // outgoing particles in the lab. Note that this will probably not
  // be useful information for very small distances.
  LorentzPoint p;
  for ( tcParticleSet::iterator it = v->in.begin();
	it != v->in.end(); ++it ) {
    p += (**it).labDecayVertex();
    gv->add_particle_in(pmap[*it]);
  }
  for ( tcParticleSet::iterator it = v->out.begin();
	it != v->out.end(); ++it ) {
    p += (**it).labVertex();
    gv->add_particle_out(pmap[*it]);
  }

  p /= double(v->in.size() + v->out.size());
  gv->set_position(p);

  return gv;
}




