// -*- C++ -*-
//
// This is the implementation of the templated member functions of
// the Particle class.
//


namespace ThePEG {

struct ParticleNumLess {
  bool operator()(tPPtr p1, tPPtr p2)
    { return p1->number() < p2->number(); }
};

template <typename Iterator>
void Particle::PrintParticles(ostream & os, Iterator first, Iterator last) {
  typedef set<PPtr,ParticleNumLess, Allocator<PPtr> > NumSet;
  NumSet pset(first, last);
  for ( NumSet::iterator i = pset.begin(); i != pset.end(); ++i ) os << **i;
}

}

