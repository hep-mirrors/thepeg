// -*- C++ -*-
#ifndef ThePEG_GenEventConverter_H
#define ThePEG_GenEventConverter_H
//
// This is the declaration of the <!id>GenEventConverter<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// The <!id>GenEventConverter<!!id> defines only one public static
// function which converts a
// <!id>ThePEG::<!!id><!class>Event<!!class> object to a
// <!id>HepMC::GenEvent<!!id>. All mother-daughter relationships and
// colour information is preserved.
//
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Event.html">Event.h</a>,
// <a href="http:Particle.html">Particle.h</a>.
// 

#include "ThePEG/Config/ThePEG.h"
#include "CLHEP/HepMC/GenEvent.h"
#include "ThePEG/EventRecord/Event.h"
// #include "GenEventConverter.fh"
// #include "GenEventConverter.xh"

namespace ThePEG {

namespace CLHEPMC = HepMC;

class GenEventConverter  {

public:

  struct GenEventConverterException: public Exception {
    GenEventConverterException() {
      theMessage << "In GenEventConverter: ";
    }
  };

  struct Vertex {
    // Help class to represent a temporary vertex which can be
    // converted to a Genvertex.
    tcParticleSet in, out;
  };

  typedef CLHEPMC::GenParticle GenParticle;
  typedef CLHEPMC::GenEvent GenEvent;
  typedef CLHEPMC::GenVertex GenVertex;
  typedef map<tcPPtr,GenParticle*> ParticleMap;
  typedef map<tcColinePtr,long> FlowMap;
  typedef map<tcPPtr,Vertex*> VertexMap;
  typedef map<const Vertex *, GenVertex*> GenVertexMap;

public:

  static GenEvent * convert(const Event & ev);
  // Convert a ThePEG::Event to a HepMC::GenEvent. The caller is
  // responsible for deleting the GenEvent object.

private:

private:

  GenEventConverter(const Event & ev);
  // The only proper constructor is private. The class is only
  // instantiated within the convert method.

  GenEventConverter();
  GenEventConverter(const GenEventConverter &);
  GenEventConverter & operator=(const GenEventConverter &);
  // These are unimplemented and private and should never be used.

private:

  GenParticle * createParticle(tcPPtr p) const;
  // Create a GenParticle from a ThePEG Particle.

  void join(tcPPtr parent, tcPPtr child);
  // Join the decay vertex of the parent with the decay vertex of the
  // child.

  GenVertex * createVertex(Vertex * v);
  // Create a GenVertex from a temporary Vertex.

private:

  GenEvent * geneve;
  // The constructed GenEvent.

  ParticleMap pmap;
  // The translation table between the ThePEG particles and the
  // GenParticles.

  FlowMap flowmap;
  // Thetranslation table between ThePEG ColourLine objects and HepMC
  // Flow indices.

  vector<Vertex> vertices;
  // All temporary vertices created.

  VertexMap prov;
  VertexMap decv;
  // The mapping of particles to their production and decy vertices.

  GenVertexMap vmap;
  // The mapping between our vertices and the created GenVertex Objects.

};

}


#include "GenEventConverter.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GenEventConverter.tcc"
#endif

#endif /* ThePEG_GenEventConverter_H */
