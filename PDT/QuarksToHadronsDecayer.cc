// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the QuarksToHadronsDecayer class.
//

#include "QuarksToHadronsDecayer.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/PDT/StandardMatchers.h"
#include "ThePEG/Repository/EventGenerator.h"
#include "ThePEG/Utilities/SimplePhaseSpace.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "QuarksToHadronsDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

QuarksToHadronsDecayer::~QuarksToHadronsDecayer() {}

bool QuarksToHadronsDecayer::accept(const DecayMode & dm) const {
  return false;
}

PVector QuarksToHadronsDecayer::decay(const DecayMode & dm,
				      const Particle & parent) const {
  PVector children;
  tcPDVector quarks;
  PDVector prods = dm.orderedProducts();
  Energy summq = 0.0*GeV;
  Energy summp = 0.0*GeV;
  for ( int i = 0, N = prods.size(); i < N; ++i )
    if ( QuarkMatcher::Check(*prods[i]) ) {
      quarks.push_back(prods[i]);
      summq += quarks.back()->mass();
    } else {
      children.push_back(prods[i]->produceParticle());
      summp += children.back()->mass();
    }

  Energy summh = 0.0*GeV;
  PVector hadrons;

  do {

    hadrons = getHadrons(getN(parent.mass(), summq, quarks.size()), quarks);

    for ( int i = 0, N = hadrons.size(); i < N; ++i )
      summh += hadrons[i]->mass();

  } while ( summp + summh >= parent.mass() );

  children.insert(children.end(), hadrons.begin(), hadrons.end());

  distribute(parent, children);

  return children;

}

int QuarksToHadronsDecayer::getN(Energy m0, Energy summq, int Nq) const {
  int Nh = fixedN();
  if ( Nh >= 2 ) return Nh;

  double c = c1()*log((m0 - summq)/c2()) + c3();
  while ( true ) {
    using namespace Constants;
    Nh = int(0.5 + double(Nq)/4.0 + c +
	     sqrt(-2.0*c*log(max(1.0e-10, rnd())))*sin(2.0*pi*rnd()));
    if ( Nh >= minN() ) return Nh;
  }
  return 0;
}

PVector QuarksToHadronsDecayer::
getHadrons(int Nh, tcPDVector quarks) const {
  PVector hadrons;
  Nh -= quarks.size()/2;
  while ( Nh-- > 0 ) {
    int i = irnd(quarks.size() - 1);
    tcPDPair hq = flavourGenerator()->alwaysGenerateHadron(quarks[i]);
    hadrons.push_back(hq.first->produceParticle());
    quarks[i] = hq.second;
  }
  hadrons.push_back(flavourGenerator()->
		    alwaysGetHadron(quarks[0], quarks[1])->produceParticle());
  if ( quarks.size() <= 2 ) return hadrons;
  hadrons.push_back(flavourGenerator()->
		    alwaysGetHadron(quarks[2], quarks[3])->produceParticle());
  return hadrons;
}

void QuarksToHadronsDecayer::
distribute(const Particle & parent, PVector & children) const {
  do {
    try {
      SimplePhaseSpace::CMSn(children, parent.mass());
    }
    catch ( ImpossibleKinematics ) {
      children.clear();
      return;
    }
  } while ( reweight(parent, children) > rnd() );
}

double QuarksToHadronsDecayer::
reweight(const Particle &, const PVector &) const {
  return 1.0;
}

void QuarksToHadronsDecayer::persistentOutput(PersistentOStream & os) const {
  os << theFixedN << theMinN << theC1 << theC2 << theC3 << theFlavourGenerator;
}

void QuarksToHadronsDecayer::persistentInput(PersistentIStream & is, int) {
  is >> theFixedN >> theMinN >> theC1 >> theC2 >> theC3 >> theFlavourGenerator;
}

ClassDescription<QuarksToHadronsDecayer> QuarksToHadronsDecayer::initQuarksToHadronsDecayer;
// Definition of the static class description member.

void QuarksToHadronsDecayer::Init() {

  static ClassDocumentation<QuarksToHadronsDecayer> documentation
    ("This class decays particles to nq (2 or 4) quarks which then are "
     "decayes to hadrons according to phase space. The number of final "
     "hadrons can either be given by a fixed number or as a Gaussian "
     "multiplicity distribution centered around c+nq/4+c3 and a width "
     "sqrt(c), where c = c1 log((m - summ)/c2), m is the mass of the "
     "decaying particle, summ the sum of the quark masses and ci real "
     "parameters.");

  static Parameter<QuarksToHadronsDecayer,int> interfaceFixedN
    ("FixedN",
     "The fixed number of hadrons to be produced. If less than 2, the "
     "number is instead given by a gaussian multiplicity distribution.",
     &QuarksToHadronsDecayer::theFixedN, 0, 0, 10,
     true, false, true);

  static Parameter<QuarksToHadronsDecayer,int> interfaceMinN
    ("MinN",
     "The minimum hadrons to be produced.",
     &QuarksToHadronsDecayer::theMinN, 2, 2, 10,
     true, false, true);

  static Parameter<QuarksToHadronsDecayer,double> interfaceC1
    ("C1",
     "The c1 parameter of the gaussian multiplicity distribution centered "
     "around c1 log((m - summ)/c2) +c3.",
     &QuarksToHadronsDecayer::theC1, 4.5, 0.0, 10.0,
     true, false, true);

  static Parameter<QuarksToHadronsDecayer,Energy> interfaceC2
    ("C2",
     "The c2 parameter of the gaussian multiplicity distribution centered "
     "around c1 log((m - summ)/c2) +c3.",
     &QuarksToHadronsDecayer::theC2, GeV, 0.7*GeV, 0.0*GeV, 10.0*GeV,
     true, false, true);

  static Parameter<QuarksToHadronsDecayer,double> interfaceC3
    ("C3",
     "The c3 parameter of the gaussian multiplicity distribution centered "
     "around c1 log((m - summ)/c2) +c3.",
     &QuarksToHadronsDecayer::theC3, 0.0, 0.0, 10.0,
     true, false, true);

  static Reference<QuarksToHadronsDecayer,FlavourGenerator>
    interfaceFlavourGenerator
    ("FlavourGenerator",
     "The object in charge of generating hadrons spieces from given quark "
     "flavours.",
     &QuarksToHadronsDecayer::theFlavourGenerator,
     true, false, true, false, true);

}

