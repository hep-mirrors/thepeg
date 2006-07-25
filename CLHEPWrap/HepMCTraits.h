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

  typedef HepMCParticleT ParticleT;

  typedef HepMCEventT EventT;

  typedef HepMCVertexT VertexT;

  typedef HepMCPolarizationT PolarizationT;

  static EventT * newEvent(long evno, double weight) {
    EventT * e = new EventT();
    e->set_event_number(evno);
    e->weights().push_back(weight);
    return e;
  }

  static void setScaleAndAlphas(EventT & e, Energy2 scale,
				double aS,  double aEM) {
    e.set_event_scale(sqrt(scale)/GeV);
    e.set_alphaQCD(aS);
    e.set_alphaQED(aEM);
  }

  static void setSignalProcessVertex(EventT & e, VertexT * v) {
    e.set_signal_process_vertex(v);
  }

  static void addVertex(EventT & e, VertexT * v) {
    e.add_vertex(v);
  }

  static ParticleT * newParticle(const Lorentz5Momentum & p,
				 long id, int status) {
    // Note that according to the documentation the momentum is stored in a
    // HepLorentzVector in GeV (event though the CLHEP standard is MeV).
    ParticleT * genp = new ParticleT(p/GeV, id, status);
    genp->setGeneratedMass(p.mass()/GeV);
    return genp;
  }

  static void setPolarization(ParticleT & genp, double the, double phi) {
    genp.set_polarization(PolarizationT(the, phi));
  }

  static void setColourLine(ParticleT & p, int indx, int coline) {
    p.set_flow(indx, coline);
  }

  static VertexT * newVertex() {
    return new VertexT();
  }

  static void addIncoming(VertexT & v, ParticleT * p) {
    v.add_particle_in(p);
  }

  static void addOutgoing(VertexT & v, ParticleT * p) {
    v.add_particle_out(p);
  }

  static void setPosition(VertexT & v, const LorentzPoint & p) {
    // We assume that the position is measured in millimeters.
    v.set_position(p/mm);
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

