// -*- C++ -*-
//
// This is the implementation of the non-inlined, non-templated member
// functions of the ReweightMinPT class.
//

#include "ReweightMinPT.h"
#include "ThePEG/Interface/ClassDocumentation.h"
#include "ThePEG/Interface/Parameter.h"
#include "ThePEG/Handlers/XComb.h"

#ifdef ThePEG_TEMPLATES_IN_CC_FILE
// #include "ReweightMinPT.tcc"
#endif

#include "ThePEG/Persistency/PersistentOStream.h"
#include "ThePEG/Persistency/PersistentIStream.h"

using namespace ThePEG;

ReweightMinPT::~ReweightMinPT() {}

double ReweightMinPT::weight() const {
  double minPt = 1.0;
  if ( lastXCombPtr() ) {
    for ( vector<Lorentz5Momentum>::const_iterator p = outMomentum().begin();
	  p != outMomentum().end(); ++p )
      minPt = min(minPt, p->perp()/sqrt(sHat()));
  } else {
    for ( vector<Lorentz5Momentum>::const_iterator p = meMomenta().begin();
	  p != meMomenta().end(); ++p )
      minPt = min(minPt, p->perp()/sqrt(sHat()));
  }
  breakThePEG();
  return pow(minPt, power);
}

void ReweightMinPT::persistentOutput(PersistentOStream & os) const {
  os << power;
}

void ReweightMinPT::persistentInput(PersistentIStream & is, int) {
  is >> power;
}

ClassDescription<ReweightMinPT> ReweightMinPT::initReweightMinPT;
// Definition of the static class description member.

void ReweightMinPT::Init() {

  static ClassDocumentation<ReweightMinPT> documentation
    ("There is no documentation for the \\classname{ReweightMinPT} class");

  static Parameter<ReweightMinPT,double> interfacePower
    ("Power",
     "The power to which the minimum tranverse momentum is raised to give "
     "the weight.",
     &ReweightMinPT::power, 4.0, -10.0, 10.0, false, false, true);

}

