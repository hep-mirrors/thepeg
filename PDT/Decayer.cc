// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the Decayer class.
//

#include "Decayer.h"
#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Utilities/UtilityBase.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "Decayer.tcc"
#endif

using namespace ThePEG;

Decayer::~Decayer() {}

double Decayer::brat(const DecayMode &,
		     const ParticleData &, double b) const {
  return b;

}

ParticleVector Decayer::getChildren(const DecayMode & dm,
					const Particle & parent) const {
  return dm.produceProducts();
}

void Decayer::finalBoost(const Particle & parent,
			 const ParticleVector & children) const {
  Utilities::setMomentum(children.begin(), children.end(),
			 (Momentum3 &)(parent.momentum()), 1.0e-12);
}  

void Decayer::setScales(const Particle & parent,
			 const ParticleVector & children) const {
  for ( ParticleVector::size_type i = 0; i < children.size(); ++i )
    children[i]->scale(parent.momentum().mass2());
}  

double Decayer::brat(const DecayMode &, const Particle &, double b) const {
  return b;
}

AbstractNoPIOClassDescription<Decayer> Decayer::initDecayer;

void Decayer::Init() {

  static ClassDocumentation<Decayer> documentation
    ("There is no documentation for the ThePEG::Decayer class");

  static Reference<Decayer,Amplitude> interfaceAmplitude
    ("Amplitude",
     "The eventual amplitude associated to this decay matrix element.",
     &Decayer::theAmplitude, false, false, true, true);

}

void Decayer::persistentOutput(PersistentOStream & os) const {
  os << theAmplitude;
}

void Decayer::persistentInput(PersistentIStream & is, int) {
  is >> theAmplitude;
}

