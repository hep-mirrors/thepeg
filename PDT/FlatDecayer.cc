// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the FlatDecayer class.
//

#include "FlatDecayer.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"
#include "ThePEG/Repository/UseRandom.h"
#include "ThePEG/EventRecord/Particle.h"
#include "ThePEG/CLHEPWrap/LorentzRotation.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Utilities/Timer.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "FlatDecayer.tcc"
#endif


using namespace ThePEG;

FlatDecayer::~FlatDecayer() {}


bool FlatDecayer::accept(const DecayMode & dm) const {
  if ( dm.products().size() == 1 && 
       ( dm.parent()->massMax() > (**(dm.products().begin())).massMax() ||
	 dm.parent()->massMin() < (**(dm.products().begin())).massMin() ) )
    return false;
  return dm.products().size() > 0 && dm.cascadeProducts().empty() &&
    dm.productMatchers().empty() && !dm.wildProductMatcher();
}

ParticleVector FlatDecayer::decay(const DecayMode & dm,
				  const Particle & parent) const {
  Timer<48> timer("FlatDecayer::decay");
  ParticleVector children = getChildren(dm, parent);
  try {
    do {
      if ( children.size() == 1 ) {
	children[0]->setMomentum(parent.momentum());
	children[0]->scale(parent.momentum().mass2());
	return children;
      }
      else {
	Timer<50> timern("FlatDecayer::decay::CMSn");
	SimplePhaseSpace::CMSn(children, parent.mass());
      }
    } while ( reweight(dm, parent, children) < UseRandom::rnd() );
  }
  catch ( ImpossibleKinematics & ) {
    children.clear();
    return children;
  }

  finalBoost(parent, children);
  setScales(parent, children);

  return children;
}

NoPIOClassDescription<FlatDecayer> FlatDecayer::initFlatDecayer;
// Definition of the static class description member.

void FlatDecayer::Init() {

  static ClassDocumentation<FlatDecayer> documentation
    ("The ThePEG::FlatDecayer class describes the decay of a "
     "ThePEG::Particle into a set of specified children according "
     "to a flat distribution in phase space.");

}

