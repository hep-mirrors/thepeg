// -*- C++ -*-
#ifndef ThePEG_ParticleTraits_H
#define ThePEG_ParticleTraits_H
//
// This is the declaration of the <!id>ParticleTraits<!!id> class.
//
// CLASSDOC SUBSECTION Description:
//
// <!id>ParticleTraits<!!id> is a templated class defining a general
// interface to any particle class. To make another particle type
// <!id>PType<!!id> available to some general ThePEG routines, the
// <!id>ParticleTraits<!!id> should be specialized to that class
// implementing relevant methods of the general
// <!id>ParticleTraits<!!id> class below. Typically one needs
// specialisation both for the class itself and of pointers to the
// class.
// 
// CLASSDOC SUBSECTION See also:
//
// <a href="http:Particle.html">Particle.h</a>
// <a href="http:Lorentz5Vector.html">Lorentz5Vector.h</a>
// 
#include "ThePEG/Config/ThePEG.h"
// #include "ParticleTraits.fh"
// #include "ParticleTraits.xh"

namespace ThePEG {

template <typename PType>
struct ParticleTraits {
  static PType & ref(PType & p) {
    return p;
  }
  // Return a reference to the particle.

  static LorentzMomentum momentum(const PType & p) {
    return p.momentum();
  }
  // Return the momentum of particle p.

  static Energy mass(const PType & p) {
    return p.mass();
  }
  // Return the mass of particle p.

  static void transform(PType & p, const LorentzRotation & r) {
    p.transform(r);
  }
  // Perform a Lorentz transformation on particle p.

  static void set5Momentum(PType & p, const Lorentz5Momentum & q) {
    p.set5Momentum(q);
  }
  // Set the momentum and mass of a particle.

  static void set3Momentum(PType & p, const Momentum3 & q) {
    p.set3Momentum(q);
  }
  // Set the 3-momentum and mass of a particle.

  static int iCharge(const PType & p) {
    return p.data().iCharge();
  }
  // Return charge of particle p in units of e/3.

};

template <>
struct ParticleTraits<PPtr> {
  static Particle & ref(tPPtr p) {
    return *p;
  }
  static const LorentzMomentum & momentum(tPPtr p) {
    return p->momentum();
  }
  static Energy mass(tPPtr p) {
    return p->mass();
  }
  static void transform(tPPtr p, const LorentzRotation & r) {
    p->transform(r);
  }
  static void set5Momentum(tPPtr p, const Lorentz5Momentum & q) {
    p->set5Momentum(q);
  }
  static void set3Momentum(tPPtr p, const Momentum3 & q) {
    p->set3Momentum(q);
  }
  static int iCharge(tPPtr p) {
    return p->data().iCharge();
  }
};  

template <>
struct ParticleTraits<cPPtr> {
  static const Particle & ref(tcPPtr p) {
    return *p;
  }
  static const LorentzMomentum & momentum(tcPPtr & p) {
    return p->momentum();
  }
  static Energy mass(tcPPtr p) {
    return p->mass();
  }
  static int iCharge(tcPPtr & p) {
    return p->data().iCharge();
  }
};  

template <>
struct ParticleTraits<tPPtr> {
  static Particle & ref(tPPtr p) {
    return *p;
  }
  static const LorentzMomentum & momentum(tPPtr p) {
    return p->momentum();
  }
  static Energy mass(tPPtr p) {
    return p->mass();
  }
  static void transform(tPPtr p, const LorentzRotation & r) {
    p->transform(r);
  }
  static void set5Momentum(tPPtr p, const Lorentz5Momentum & q) {
    p->set5Momentum(q);
  }
  static void set3Momentum(tPPtr p, const Momentum3 & q) {
    p->set3Momentum(q);
  }
  static int iCharge(tPPtr p) {
    return p->data().iCharge();
  }
};  

template <>
struct ParticleTraits<tcPPtr> {
  static const Particle & ref(tcPPtr p) {
    return *p;
  }
  static const LorentzMomentum & momentum(tcPPtr p) {
    return p->momentum();
  }
  static Energy mass(tcPPtr p) {
    return p->mass();
  }
  static int iCharge(tcPPtr p) {
    return p->data().iCharge();
  }
};

template <>
struct ParticleTraits<LorentzMomentum> {
  static LorentzMomentum & ref(LorentzMomentum & p) {
    return p;
  }
  static const LorentzMomentum & momentum(const LorentzMomentum & p) {
    return p;
  }
  static Energy mass(const LorentzMomentum & p) {
    return p.m();
  }
  static void transform(LorentzMomentum & p, const LorentzRotation & r) {
    p.transform(r);
  }
  static void set5Momentum(LorentzMomentum & p, const Lorentz5Momentum & q) {
    p = q;
  }
  static void set3Momentum(LorentzMomentum & p, const Momentum3 & q) {
    p = LorentzMomentum(q, sqrt(q.mag2() + p.m2()));
  }
};  

template <>
struct ParticleTraits<Lorentz5Momentum> {
  static Lorentz5Momentum & ref(Lorentz5Momentum & p) {
    return p;
  }
  static const LorentzMomentum & momentum(const Lorentz5Momentum & p) {
    return p;
  }
  static Energy mass(const Lorentz5Momentum & p) {
    return p.mass();
  }
  static void transform(Lorentz5Momentum & p, const LorentzRotation & r) {
    p.transform(r);
  }
  static void set5Momentum(Lorentz5Momentum & p, const Lorentz5Momentum & q) {
    p = q;
  }
  static void set3Momentum(Lorentz5Momentum & p, const Momentum3 & q) {
    p = Lorentz5Momentum(p.mass(), q);
  }
};  

struct Transformer {
  Transformer(const LorentzRotation & rin) : r(rin) {}
  Transformer(const Transformer & t) : r(t.r) {}
  template <typename PType>
  void operator()(const PType & p) {
    ParticleTraits<PType>::transform(p, r);
  }
  const LorentzRotation & r;
};



}

// #include "ParticleTraits.icc"
#ifndef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ParticleTraits.tcc"
#endif

#endif /* ThePEG_ParticleTraits_H */
