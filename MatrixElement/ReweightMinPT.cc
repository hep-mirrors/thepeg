// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ReweightMinPT class.
//

#include "ReweightMinPT.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Handlers/StandardXComb.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightMinPT.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

ReweightMinPT::~ReweightMinPT() {}

double ReweightMinPT::weight() const {
  Energy minPt = Constants::MaxEnergy;
  for ( int i = 0, N = subProcess()->outgoing().size(); i < N; ++i )
    minPt = min(minPt, subProcess()->outgoing()[i]->momentum().perp());
  return pow(minPt/scale, power);
}

void ReweightMinPT::persistentOutput(PersistentOStream & os) const {
  os << power << ounit(scale,GeV);
}

void ReweightMinPT::persistentInput(PersistentIStream & is, int) {
  is >> power >> iunit(scale,GeV);
}

ClassDescription<ReweightMinPT> ReweightMinPT::initReweightMinPT;
// Definition of the static class description member.

void ReweightMinPT::Init() {

  static ClassDocumentation<ReweightMinPT> documentation
    ("There is no documentation for the ThePEG::ReweightMinPT class");

  static Parameter<ReweightMinPT,double> interfacePower
    ("Power",
     "The power to which the minimum tranverse momentum (divided by a "
     "<interface>Scale</interface>) is raised to give the weight.",
     &ReweightMinPT::power, 4.0, -10.0, 10.0, false, false, true);

  static Parameter<ReweightMinPT,Energy> interfaceScale
    ("Scale",
     "The scale with which the minimum transverse momentum is divided "
     "befor it is raised to a <interface>Power</interface> to give the "
     "weight..",
     &ReweightMinPT::scale, GeV, 50.0*GeV, 0.0*GeV, 0.0*GeV,
     false, false, Interface::lowerlim);

  interfacePower.rank(10);
  interfaceScale.rank(9);

}

