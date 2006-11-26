// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the SimpleBaryonRemnantDecayer class.
//

#include "SimpleBaryonRemnantDecayer.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Reference.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/PDT/StandardMatchers.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "SimpleBaryonRemnantDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

SimpleBaryonRemnantDecayer::~SimpleBaryonRemnantDecayer() {}

bool SimpleBaryonRemnantDecayer::accept(const DecayMode &) const {
  return true;
}

bool SimpleBaryonRemnantDecayer::
canHandle(tcPDPtr particle, tcPDPtr parton) const {
  return BaryonMatcher::Check(*particle) &&
    StandardQCDPartonMatcher::Check(*parton);
}

ParticleVector SimpleBaryonRemnantDecayer::
decay(const DecayMode & dm, const Particle & p, Step &) const {
  ParticleVector children;
  tcRemPPtr remnant = dynamic_ptr_cast<tcRemPPtr>(&p);
  if ( !remnant ) return children;
  tRemPDPtr rpd = data(remnant);
  PVector ex = extracted(remnant);
  tPPtr par = parent(remnant);
  if ( !par || ex.empty() || !rpd ) return children;
  children= dm.produceProducts();
  return children;
}

void SimpleBaryonRemnantDecayer::
persistentOutput(PersistentOStream & os) const {
  os << theZGenerator << theFlavourGenerator << theMargin << useSpecialValence;
}

void SimpleBaryonRemnantDecayer::
persistentInput(PersistentIStream & is, int) {
  is >> theZGenerator >> theFlavourGenerator >> theMargin >> useSpecialValence;
}

ClassDescription<SimpleBaryonRemnantDecayer> SimpleBaryonRemnantDecayer::initSimpleBaryonRemnantDecayer;
// Definition of the static class description member.

void SimpleBaryonRemnantDecayer::Init() {

  static ClassDocumentation<SimpleBaryonRemnantDecayer> documentation
    ("The SimpleBaryonRemnantDecayer class inherits from the RemnantDecayer "
     "class and is able to decay RemnantParticles produced by the "
     "SoftRemnantHandler class for the cases when a single parton has been "
     "extracted from a baryon.");

  static Reference<SimpleBaryonRemnantDecayer,ZGenerator> interfaceZGenerator
    ("ZGenerator",
     "The object responsible for generating momentum fractions in case "
     "of more than one remnant.",
     &SimpleBaryonRemnantDecayer::theZGenerator, false, false, true, false, true);

  static Reference<SimpleBaryonRemnantDecayer,FlavourGenerator>
    interfaceFlavourGenerator
    ("FlavourGenerator",
     "The object responsible for handling the flavour contents of a baryon.",
     &SimpleBaryonRemnantDecayer::theFlavourGenerator,
     false, false, true, false, true);

  static Parameter<SimpleBaryonRemnantDecayer,Energy> interfaceMargin
    ("EnergyMargin",
     "The energy margin (in GeV) to be added to the sum of the parent and "
     "parton masses to determine if it is possible to construct the remnants "
     "with the given (upper limit of the) virtuality of the extracted parton.",
     &SimpleBaryonRemnantDecayer::theMargin, GeV, 1.0*GeV, 0.0*GeV, 10.0*GeV,
     false, false, true);

  static Switch<SimpleBaryonRemnantDecayer,bool> interfaceSpecialValence
    ("SpecialValence",
     "If true, an extracted valence quark will always give a di-quark remnant.",
     &SimpleBaryonRemnantDecayer::useSpecialValence, false, true, false);
  static SwitchOption interfaceSpecialValenceYes
    (interfaceSpecialValence,
     "Yes",
     "An extracted valence quark will always give a di-quark remnant.",
     true);
  static SwitchOption interfaceSpecialValenceNo
    (interfaceSpecialValence,
     "No",
     "An extracted valence flavour may be considered to be a sea-quark.",
     false);

  interfaceZGenerator.rank(8);
  interfaceFlavourGenerator.rank(7);

}

