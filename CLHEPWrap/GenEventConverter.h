// -*- C++ -*-
#ifndef ThePEG_GenEventConverter_H
#define ThePEG_GenEventConverter_H
// This is the declaration of the GenEventConverter class.

#include "ThePEG/Config/ThePEG.h"
#include "CLHEP/HepMC/GenEvent.h"
#include "ThePEG/EventRecord/Event.h"
// #include "GenEventConverter.fh"
// #include "GenEventConverter.xh"

namespace ThePEG {

/** Alias for the HepMC namespace. */
namespace CLHEPMC = HepMC;

/**
 * The GenEventConverter defines only one public static function which
 * converts a ThePEG::Event object to a
 * <code>HepMC::GenEvent</code>. All mother-daughter relationships and
 * colour information is preserved.
 *
 * @see Event
 * @see Particle
 *
 * @author Leif Lönnblad
 */
class GenEventConverter  {

public:

  /** Exception class for GenEventConverter. */
  struct GenEventConverterException: public Exception {
    /** Default constructor */
    GenEventConverterException() {
      theMessage << "In GenEventConverter: ";
    }
  };

  /**
   * Help class to represent a temporary vertex which can be
   * converted to a GenVertex.
   */
  struct Vertex {
    /** Particles going in and out of the vertex. */
    tcParticleSet in, out;
  };

  /** Forward typedefs from CLHEPMC. */
  typedef CLHEPMC::GenParticle GenParticle;
  /** Forward typedefs from CLHEPMC. */
  typedef CLHEPMC::GenEvent GenEvent;
  /** Forward typedefs from CLHEPMC. */
  typedef CLHEPMC::GenVertex GenVertex;
  /** Map ThePEG particles to HepMC particles. */
  typedef map<tcPPtr,GenParticle*> ParticleMap;
  /** Map ThePEG colour lines to HepMC colour indices. */
  typedef map<tcColinePtr,long> FlowMap;
  /** Map ThePEG particles to vertices. */
  typedef map<tcPPtr,Vertex*> VertexMap;
  /** Map vertices to GenVertex */
  typedef map<const Vertex *, GenVertex*> GenVertexMap;

public:

  /**
   * Convert a ThePEG::Event to a HepMC::GenEvent. The caller is
   * responsible for deleting the constructed GenEvent object.
   */
  static GenEvent * convert(const Event & ev);

private:

  /**
   * The only proper constructor is private. The class is only
   * instantiated within the convert method.
   */
  GenEventConverter(const Event & ev);

  /**
   * Default constructor is unimplemented and private and should never be used.
   */
  GenEventConverter();

  /**
   * Copy constructor is unimplemented and private and should never be used.
   */
  GenEventConverter(const GenEventConverter &);

  /**
   * Assignment is unimplemented and private and should never be used.
   */
  GenEventConverter & operator=(const GenEventConverter &);

private:

  /**
   * Create a GenParticle from a ThePEG Particle.
   */
  GenParticle * createParticle(tcPPtr p) const;

  /**
   * Join the decay vertex of the parent with the decay vertex of the
   * child.
   */
  void join(tcPPtr parent, tcPPtr child);

  /**
   * Create a GenVertex from a temporary Vertex.
   */
  GenVertex * createVertex(Vertex * v);

private:

  /**
   * The constructed GenEvent.
   */
  GenEvent * geneve;

  /**
   * The translation table between the ThePEG particles and the
   * GenParticles.
   */
  ParticleMap pmap;

  /**
   * The translation table between ThePEG ColourLine objects and HepMC
   * Flow indices.
   */
  FlowMap flowmap;

  /**
   * All temporary vertices created.
   */
  vector<Vertex> vertices;

  /**
   * The mapping of particles to their production vertices.
   */
  VertexMap prov;

  /**
   * The mapping of particles to their decy vertices.
   */
  VertexMap decv;

  /**
   * The mapping between temporary vertices and the created GenVertex Objects.
   */
  GenVertexMap vmap;

};

}


#include "GenEventConverter.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "GenEventConverter.tcc"
#endif

#endif /* ThePEG_GenEventConverter_H */
