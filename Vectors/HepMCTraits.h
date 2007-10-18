// -*- C++ -*-
#ifndef ThePEG_HepMCTraits_H
#define ThePEG_HepMCTraits_H

namespace HepMC {

class GenEvent;
class GenParticle;
class GenVertex;
class Polarization;

}

namespace ThePEG {

/**
 * HepMCTraitsBase is a convenient base class for specializing the
 * HepMCTraits class to deal with different flavours of HepMC in the
 * HepMCConverter class. The default version will work for the CLHEP
 * implementation of HepMC. To use the HepMCConverter class for any
 * flavour of HepMC you have to specialize the HepMCTraits class
 * accordingly, possibly inheriting the functionality from the
 * HepMCTraitsBase class and only overriding the functions and
 * typedefs which are different. For the CLHEP flavour of HepMC you
 * only need to do <code>template&lt;&gt; struct
 * HepMCTraits&lt;HepMC::GenEvent&gt;: public
 * HepMCTraitsBase&lt;HepMC::GenEvent,HepMC::GenParticle,HepMC::GenVertex,
 * HepMC::Polarization&gt; {};</code> somewhere inside the ThePEG
 * namespace.
 */
template <typename HepMCEventT, typename HepMCParticleT,
          typename HepMCVertexT, typename HepMCPolarizationT>
struct HepMCTraitsBase {

  /** Typedef of the particle class. */
  typedef HepMCParticleT ParticleT;

  /** Typedef of the event class. */
  typedef HepMCEventT EventT;

  /** Typedef of the vertex class. */
  typedef HepMCVertexT VertexT;

  /** Typedef of the polarization class. */
  typedef HepMCPolarizationT PolarizationT;

  /** Create an event object with number \a evno and \a weight. */
  static EventT * newEvent(long evno, double weight) {
    EventT * e = new EventT();
    e->set_event_number(evno);
    e->weights().push_back(weight);
    return e;
  }

  /** Set the \a scale, \f$\alpha_S\f$ (\a aS) and \f$\alpha_{EM}\f$
      (\a aEM) for the event \a e. */
  static void setScaleAndAlphas(EventT & e, Energy2 scale,
				double aS,  double aEM) {
    e.set_event_scale(sqrt(scale)/GeV);
    e.set_alphaQCD(aS);
    e.set_alphaQED(aEM);
  }

  /** Set the primary vertex, \a v, for the event \a e. */
  static void setSignalProcessVertex(EventT & e, VertexT * v) {
    e.set_signal_process_vertex(v);
  }

  /** Set a vertex, \a v, for the event \a e. */
  static void addVertex(EventT & e, VertexT * v) {
    e.add_vertex(v);
  }

  /** Create a new particle object with momentum \a p, PDG number \a
      id and status code \a status. */
  static ParticleT * newParticle(const Lorentz5Momentum & p,
				 long id, int status) {
    // Note that according to the documentation the momentum is stored in a
    // HepLorentzVector in GeV (event though the CLHEP standard is MeV).
    LorentzVector<double> p_GeV = p/GeV;
    ParticleT * genp = new ParticleT(p_GeV, id, status);
    genp->setGeneratedMass(p.mass()/GeV);
    return genp;
  }

  /** Set the polarization directions, \a the and \a phi, for particle
      \a p. */
  static void setPolarization(ParticleT & genp, double the, double phi) {
    genp.set_polarization(PolarizationT(the, phi));
  }

  /** Set the colour line (with index \a indx) to \a coline for
      particle \a p. */
  static void setColourLine(ParticleT & p, int indx, int coline) {
    p.set_flow(indx, coline);
  }

  /** Create a new vertex. */
  static VertexT * newVertex() {
    return new VertexT();
  }

  /** Add an incoming particle, \a p, to the vertex, \a v. */
  static void addIncoming(VertexT & v, ParticleT * p) {
    v.add_particle_in(p);
  }

  /** Add an outgoing particle, \a p, to the vertex, \a v. */
  static void addOutgoing(VertexT & v, ParticleT * p) {
    v.add_particle_out(p);
  }

  /** Set the position \a p for the vertex, \a v. */
  static void setPosition(VertexT & v, const LorentzPoint & p) {
    // We assume that the position is measured in millimeters.
    LorentzVector<double> p_mm = p/mm;
    v.set_position(p_mm);
  }

};

/**
 * The HepMCTraits class is used to deal with different flavours of
 * HepMC in the HepMCConverter class. To use the HepMCConverter class
 * for any flavour of HepMC you have to specialize the
 * HepMCTraits class accordingly, possibly inheriting the
 * functionality from the HepMCTraitsBase class and only overriding
 * the functions and typedefs which are different. For the CLHEP
 * flavour of HepMC you only need to do <code>template&lt;&gt; struct
 * HepMCTraits&lt;HepMC::GenEvent&gt;: public
 * HepMCTraitsBase&lt;HepMC::GenEvent,HepMC::GenParticle,HepMC::GenVertex,
 * HepMC::Polarization&gt; {};</code> somewhere inside the ThePEG
 * namespace.
 */
template <typename HepMCEventT>
struct HepMCTraits {};

}

#endif
