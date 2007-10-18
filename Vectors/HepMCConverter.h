// -*- C++ -*-
#ifndef ThePEG_HepMCConverter_H
#define ThePEG_HepMCConverter_H
// This is the declaration of the HepMCConverter class.

#include "ThePEG/Config/ThePEG.h"
#include "ThePEG/EventRecord/Event.h"
#include "HepMCTraits.h"

namespace ThePEG {


/**
 * The HepMCConverter defines only one public static function which
 * converts a ThePEG::Event object to a
 * <code>HepMC::GenEvent</code>. All mother-daughter relationships and
 * colour information is preserved.
 *
 * @see Event
 * @see Particle
 *
 * @author Leif L�nnblad
 */
template <typename HepMCEventT, typename Traits = HepMCTraits<HepMCEventT> >
class HepMCConverter  {

public:

  /** @cond EXCEPTIONCLASSES */
  /** Exception class for HepMCConverter. */
  struct HepMCConverterException: public Exception {};
  /** @endcond */

  /**
   * Help class to represent a temporary vertex which can be
   * converted to a GenVertex.
   */
  struct Vertex {
    /** Particles going in to the vertex. */
    tcParticleSet in;
    /** Particles going out of the vertex. */
    tcParticleSet out;
  };

  /** Forward typedefs from Traits class. */
  typedef typename Traits::ParticleT GenParticle;
  /** Forward typedefs from Traits class. */
  typedef typename Traits::EventT GenEvent;
  /** Forward typedefs from Traits class. */
  typedef typename Traits::VertexT GenVertex;
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
   * responsible for deleting the constructed GenEvent object. If \a
   * nocopies is true, only final copies of particles connected with
   * Particle::previous() and Particle::next() will be entered in the
   * HepMC::GenEvent.
   */
  static GenEvent * convert(const Event & ev, bool nocopies = false);

private:

  /**
   * The only proper constructor is private. The class is only
   * instantiated within the convert method.
   */
  HepMCConverter(const Event & ev, bool nocopies);

  /**
   * Default constructor is unimplemented and private and should never be used.
   */
  HepMCConverter();

  /**
   * Copy constructor is unimplemented and private and should never be used.
   */
  HepMCConverter(const HepMCConverter &);

  /**
   * Assignment is unimplemented and private and should never be used.
   */
  HepMCConverter & operator=(const HepMCConverter &);

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

#include "HepMCConverter.tcc"

#endif /* ThePEG_HepMCConverter_H */