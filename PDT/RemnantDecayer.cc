// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the RemnantDecayer class.
//

#include "RemnantDecayer.h"
#include "ThePEG/PDT/DecayMode.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Switch.h"
#include "ThePEG/PDT/RemnantData.h"
#include "ThePEG/Utilities/EnumIO.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "RemnantDecayer.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

RemnantDecayer::~RemnantDecayer() {}

bool RemnantDecayer::accept(const DecayMode &) const {
  return false;
}

bool RemnantDecayer::needsFullStep() const {
  return true;
}

bool RemnantDecayer::
canHandle(tcPDPtr, tcPDPtr) const {
  return false;
}

bool RemnantDecayer::multiCapable() const {
  return false;
}

ParticleVector RemnantDecayer::
decay(const DecayMode &, const Particle &) const {
  return ParticleVector();
}

ParticleVector RemnantDecayer::
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

void RemnantDecayer::
fillChildren(const Particle & p, set<tPPtr> & children) const {
  for ( int i = 0, N = p.children().size(); i < N; ++i ) {
    children.insert(p.children()[i]);
    fillChildren(*p.children()[i], children);
  }
  for ( int i = 0, N = p.parents().size(); i < N; ++i ) {
    tPPtr parent = p.parents()[i];
    if ( member(children, parent) ) continue;
    for ( int j = 0, M = p.children().size(); j < M; ++j )
      if ( dynamic_ptr_cast<tcRemPPtr>(p.children()[j]) ) {
	parent = tPPtr();
	break;
      }
    if ( parent ) fillChildren(*parent, children);
  }
}

void RemnantDecayer::persistentOutput(PersistentOStream & os) const {
  os << oenum(theRecoilOption) << respectDIS;
}

void RemnantDecayer::persistentInput(PersistentIStream & is, int) {
  is >> ienum(theRecoilOption) >> respectDIS;
}

AbstractClassDescription<RemnantDecayer> RemnantDecayer::initRemnantDecayer;
// Definition of the static class description member.

void RemnantDecayer::Init() {

  static ClassDocumentation<RemnantDecayer> documentation
    ("The RemnantDecayer class is the base class to be used for all "
     "decayers capable of decaying a RemnantParticle object produced by a "
     "SoftRemnantHandler object.");

  static Switch<RemnantDecayer,RecoilOption> interfaceRecoilOption
    ("RecoilOption",
     "Different options for how to distribute recoils in the hard subsystem "
     "when taking energy to produce remnants.",
     &RemnantDecayer::theRecoilOption, copyFinal, true, false);
  static SwitchOption interfaceRecoilOptionCopyFinal
    (interfaceRecoilOption,
     "CopyFinal",
     "Boost copies of final state particles in hard subsystem.",
     copyFinal);
  static SwitchOption interfaceRecoilOptionBoostFinal
    (interfaceRecoilOption,
     "BoostFinal",
     "Boost only final state particles in hard subsystem.",
     boostFinal);
  static SwitchOption interfaceRecoilOptionBoostAll
    (interfaceRecoilOption,
     "BoostAll",
     "Boost all particles in the hard subsystem.",
     boostAll);

  static Switch<RemnantDecayer,bool> interfaceRespectDISKinematics
    ("RespectDISKinematics",
     "If true, do not boost a scattered lepton (and possible radiated "
     "photons) in a DIS event, to ensure that \f$x\f$ and \f$Q^2\f$ is "
     "unmodified.",
     &RemnantDecayer::respectDIS, true, true, false);
  static SwitchOption interfaceRespectDISKinematicsYes
    (interfaceRespectDISKinematics,
     "Yes",
     "Do not boost scattered lepton.",
     true);
  static SwitchOption interfaceRespectDISKinematicsNo
    (interfaceRespectDISKinematics,
     "No",
     "Boost scattered lepton together with the rest of the hard subsystem.",
     false);

}

