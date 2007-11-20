// -*- C++ -*-
//
// HepMCConverter.tcc is a part of ThePEG - Toolkit for HEP Event Generation
// Copyright (C) 1999-2007 Leif Lonnblad
//
// ThePEG is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the HepMCConverter class.
//

#include "HepMCConverter.h"
#include "ThePEG/StandardModel/StandardModelBase.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/EventRecord/StandardSelectors.h"
#include "ThePEG/EventRecord/Collision.h"
#include "ThePEG/EventRecord/Step.h"
#include "ThePEG/EventRecord/SubProcess.h"
#include "ThePEG/Handlers/XComb.h"
#include "ThePEG/Handlers/EventHandler.h"

namespace ThePEG {


template <typename HepMCEventT, typename Traits>
typename HepMCConverter<HepMCEventT,Traits>::GenEvent *
HepMCConverter<HepMCEventT,Traits>::convert(const Event & ev, bool nocopies) {
  HepMCConverter<HepMCEventT,Traits> converter(ev, nocopies);
  return converter.geneve;
}

template <typename HepMCEventT, typename Traits>
HepMCConverter<HepMCEventT,Traits>::
HepMCConverter(const Event & ev, bool nocopies) {

  geneve = Traits::newEvent(ev.number(), ev.weight());

  tcEHPtr eh;
  if ( ev.primaryCollision() && ( eh =
       dynamic_ptr_cast<tcEHPtr>(ev.primaryCollision()->handler()) ) ) {

    // Get general event info if present.
    Traits::setScaleAndAlphas(*geneve, eh->lastScale(),
			     eh->SM().alphaS(eh->lastScale()),
			     eh->SM().alphaEM(eh->lastScale()));
  }

  // Extract all particles.
  tcPVector all;
  ev.select(back_inserter(all), SelectAll());
  vertices.reserve(all.size()*2);

  // Create GenParticle's and map them to the ThePEG particles.
  for ( int i = 0, N = all.size(); i < N; ++i ) {
    tcPPtr p = all[i];
    if ( nocopies && p->next() ) continue;
    if ( pmap.find(p) != pmap.end() ) continue;
    GenParticle * gp = pmap[p] = createParticle(p);
    if ( p->hasColourInfo() ) {
      // Check if the particle is connected to colour lines, in which
      // case the lines are mapped to an integer and set in the
      // GenParticle's Flow info.
      tcColinePtr l;
      if ( l = p->colourLine() ) {
	if ( !member(flowmap, l) ) flowmap[l] = flowmap.size() + 500;
	Traits::setColourLine(*gp, 1, flowmap[l]);
      }
      if ( l = p->antiColourLine() ) {
	if ( !member(flowmap, l) ) flowmap[l] = flowmap.size() + 500;
	Traits::setColourLine(*gp, 2, flowmap[l]);
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
    if ( nocopies ) {
      if ( p->next() ) continue;
      for ( int i = 0, N = p->children().size(); i < N; ++i )
	join(p, p->children()[i]->final());
      tcPPtr pp = p;
      while ( pp->parents().empty() && pp->previous() ) pp = pp->previous();
      for ( int i = 0, N = pp->parents().size(); i < N; ++i )
	join(pp->parents()[i]->final(), p);
    } else {
      for ( int i = 0, N = p->children().size(); i < N; ++i )
	join(p, p->children()[i]);
      if ( p->next() ) join(p, p->next());
      for ( int i = 0, N = p->parents().size(); i < N; ++i )
	join(p->parents()[i], p);
      if ( p->previous() ) join(p->previous(), p);
    }
  }

  // Time to create the GenVertex's
  for ( typename VertexMap::iterator it = prov.begin(); it != prov.end(); ++it )
    if ( !member(vmap, it->second) )
      vmap[it->second] = createVertex(it->second);
  for ( typename VertexMap::iterator it = decv.begin(); it != decv.end(); ++it )
    if ( !member(vmap, it->second) )
      vmap[it->second] = createVertex(it->second);

  // Now find the primary signal process vertex defined to be the
  // decay vertex of the first parton coming into the primary hard
  // sub-collision.
  tSubProPtr sub = ev.primarySubProcess();
  if ( sub && sub->incoming().first ) {
    const Vertex * prim = decv[sub->incoming().first];
    Traits::setSignalProcessVertex(*geneve, vmap[prim]);
    vmap.erase(prim);
  }
  
  // Then add the rest of the vertices.
  for ( typename GenVertexMap::iterator it = vmap.begin();
	it != vmap.end(); ++it )
    Traits::addVertex(*geneve, it->second);

}

template <typename HepMCEventT, typename Traits>
typename HepMCConverter<HepMCEventT,Traits>::GenParticle *
HepMCConverter<HepMCEventT,Traits>::createParticle(tcPPtr p) const {
  int status = 1;
  if ( !p->children().empty() || p->next() ) status = 2;
  GenParticle * gp = Traits::newParticle(p->momentum(), p->id(), status);

  if ( p->spinInfo() && p->spinInfo()->hasPolarization() ) {
    DPair pol = p->spinInfo()->polarization();
    Traits::setPolarization(*gp, pol.first, pol.second);
  }

  return gp;

}

template <typename HepMCEventT, typename Traits>
void HepMCConverter<HepMCEventT,Traits>::join(tcPPtr parent, tcPPtr child) {
  Vertex * dec = decv[parent];
  Vertex * pro = prov[child];
  if ( !pro || !dec ) throw HepMCConverterException()
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

template <typename HepMCEventT, typename Traits>
typename HepMCConverter<HepMCEventT,Traits>::GenVertex *
HepMCConverter<HepMCEventT,Traits>::createVertex(Vertex * v) {
  if ( !v ) throw HepMCConverterException()
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
    Traits::addIncoming(*gv, pmap[*it]);
  }
  for ( tcParticleSet::iterator it = v->out.begin();
	it != v->out.end(); ++it ) {
    p += (**it).labVertex();
    Traits::addOutgoing(*gv, pmap[*it]);
  }

  p /= double(v->in.size() + v->out.size());
  Traits::setPosition(*gv, p);

  return gv;
}

}


